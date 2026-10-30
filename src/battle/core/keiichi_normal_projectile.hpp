#pragma once
#include "legacy_trig.hpp"
#include "projectile_motion_length.hpp"
#include "battle_facing.hpp"
#include "roster_projectile_birth_profiles.hpp"
#include <array>
#include <cstdint>
#include <cstring>

namespace daybreak {
enum class KeiichiProjectileItem {MionPistols=2,MionWater=4,Bat=5,Iron=18,Shovel=34,MionLaser=35};
// Registered bullet 0 only. The script, free-flight motion and frame cursor are
// separate operations in the original; the battle scheduler must order them.
struct KeiichiNormalProjectile {
    KeiichiProjectileItem item=KeiichiProjectileItem::Bat;
    std::array<float,3> position{},velocity{},rotation{},scale{1,1,1};
    float speed=0,heading=0,offset=0,pitch=0,remaining_stage_distance=0,turn_rate=0;
    float orbit_angle=0,orbit_radius=0,orbit_side=0;
    std::array<std::uint16_t,4> contacts{};
    std::array<std::int32_t,4> capacity{};
    std::uint32_t frame=0,scratch_e8=0,scratch_ec=0,scratch_f0=0,scratch_f4=0,scratch_f8=0;
    unsigned owner=0,target=1;
    std::uint8_t angular=1; // Native byte+148: retain nonzero values until direct-mode conversion.
    bool released=false,ground_motion=false,surface_flag=false,wall_contact=false;
};
//Observe common5F72C0/5F71F0 during the current script only. Scope restores
//nested observers and never stores pointers in copied projectile/child state.
struct ProjectileEventObserver {
 void* context=nullptr;
 void (*reflected)(void*,const KeiichiNormalProjectile&)=nullptr;
 void (*retargeted)(void*,const KeiichiNormalProjectile&)=nullptr;
};
inline thread_local const ProjectileEventObserver* projectile_event_observer=nullptr;
class ScopedProjectileEventObserver {
 ProjectileEventObserver current_;const ProjectileEventObserver* previous_;
public:
 explicit ScopedProjectileEventObserver(ProjectileEventObserver observer):current_(observer),previous_(projectile_event_observer){projectile_event_observer=&current_;}
 ~ScopedProjectileEventObserver(){projectile_event_observer=previous_;}
 ScopedProjectileEventObserver(const ScopedProjectileEventObserver&)=delete;
 ScopedProjectileEventObserver& operator=(const ScopedProjectileEventObserver&)=delete;
};
inline void notify_projectile_retarget(const KeiichiNormalProjectile& s){if(auto* o=projectile_event_observer)if(o->retargeted)o->retargeted(o->context,s);}
inline std::int32_t projectile_signed(std::uint32_t n){std::int32_t s;std::memcpy(&s,&n,4);return s;}
inline std::uint16_t projectile_contacts(const KeiichiNormalProjectile& s){
    std::uint16_t flags=0;for(auto f:s.contacts)flags|=f;return flags;
}
// 5f72c0 + callers' 42c800/42c840. In direct mode this does not reverse
// velocity: the original changes the angle fields only.
inline void reflect_normal_projectile(KeiichiNormalProjectile& s,int contact_capacity=1){
    const float delta=-s.pitch+-s.pitch;s.pitch=delta+s.pitch;
    s.heading+=180.f;if(s.heading>180.f)s.heading-=360.f;if(s.heading< -180.f)s.heading+=360.f;
    s.target=s.owner;
    for(unsigned i=0;i<4;++i)if(s.contacts[i]&0x100)s.owner=i;
    if(auto* o=projectile_event_observer)if(o->reflected)o->reflected(o->context,s);
    s.contacts.fill(0);s.capacity.fill(contact_capacity);
}
inline void normal_projectile_direct_velocity(KeiichiNormalProjectile& s){
    if(!s.angular)return;
    const float angle=s.heading+s.offset,cp=legacy_trig(s.pitch,false);
    s.velocity={cp*legacy_trig(angle,false)*s.speed,legacy_trig(s.pitch,true)*s.speed,cp*legacy_trig(angle,true)*s.speed};
    s.angular=false;
}
// Shared safety path for weapon items whose per-item script has not yet been
// recovered. Verified normal registrations use their original item-specific
// launch speed and contact capacity; stationary, immediate-child and other
// special births keep the prior playable fallback until their scripts land.
// Age-only expiry is transferred where a whole-frame original sweep is stable.
// Later steering, children and unverified expiry remain provisional.
template<class Host> bool tick_generic_normal_projectile(KeiichiNormalProjectile& s,Host& host,unsigned registration=0){
    if(s.released)return false;
    if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
    const auto item=unsigned(s.item);
    const auto& profiles=roster_projectile_birth_profiles;
    const auto* profile=registration==0&&item<profiles.size()&&profiles[item].eligible?
        &profiles[item]:nullptr;
    if(s.frame==0){
        if(profile){
            s.speed=profile->speed;s.capacity.fill(profile->capacity);
            for(unsigned axis=0;axis<3;++axis)
                if(profile->scale_mask&(1u<<axis))s.scale[axis]=profile->scale[axis];
        }else{s.speed=45.f;s.capacity.fill(1);}
        s.scratch_e8=s.scratch_ec=0;
    }
    const auto contact=projectile_contacts(s);
    const auto age=projectile_signed(s.frame);
    const bool age_stop=profile&&profile->expiry_frame?
        age>=std::int32_t(profile->expiry_frame):age>240;
    if(age_stop||(contact!=0&&contact!=1)||host.stage_collision(s)==1){s.released=true;return false;}
    ++s.frame;host.advance_frame(s);return true;
}
// Host supplies target_state(s), target_elevation(s) (42dac0 mode 2),
// random_word() (65d150), stage_collision(s) (5f6a90 AL), and
// advance_frame(s) (5f75a0). Queries intentionally occur after reflection.
// This ports control flow, not the stage query, original RNG or CRT backend.
template<class Host> bool tick_keiichi_normal_projectile(KeiichiNormalProjectile& s,Host& host){
    if(s.released)return false;
    if(s.item!=KeiichiProjectileItem::Bat&&s.item!=KeiichiProjectileItem::Iron&&s.item!=KeiichiProjectileItem::Shovel)
        throw std::runtime_error("Unsupported normal projectile item");
    if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
    if(s.item==KeiichiProjectileItem::Shovel){ // 620e20 case 0
        if(s.frame==0){
            s.scale.fill(.5f);for(auto& a:s.rotation)a=float(host.random_word()%360u);
            s.speed=30.f;s.capacity.fill(1);s.scratch_e8=0;
        }
        if(s.frame==1)normal_projectile_direct_velocity(s);
        s.scratch_e8+=50u;s.velocity[1]-=.2f;
        // Stage query precedes both contact and age tests for this item.
        if(host.stage_collision(s)==1||projectile_contacts(s)!=0||projectile_signed(s.frame)>180){s.released=true;return false;}
    }else{ // 5fd170 / 60ea90 case 0
        const bool iron=s.item==KeiichiProjectileItem::Iron;
        const float step=iron?.2f:.1f;
        if(s.frame==0){
            const auto target_state=host.target_state(s);
            if((target_state>117&&target_state<122)||target_state==221){
                if(s.pitch-host.target_elevation(s)<10.f)s.pitch=host.target_elevation(s);
                if(s.pitch-host.target_elevation(s)>-10.f)s.pitch=host.target_elevation(s);
            }
            s.speed=iron?40.f:45.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
            if(iron)s.scale.fill(2.f);
        }
        if(iron)s.rotation[0]+=25.f;
        ++s.scratch_ec;const std::int32_t cap=iron?75:100;
        if(projectile_signed(s.scratch_ec)>cap)s.scratch_ec=std::uint32_t(cap);
        if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
        if(s.scratch_e8==0){
            // 42db10 toward zero; this branch only runs in [-90,90].
            if(std::abs(s.offset)<step)s.offset=0;
            else if(s.offset<0)s.offset+=step;
            else if(s.offset>0)s.offset-=step;
            if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=step;
            if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
        }
        const auto contact=projectile_contacts(s);
        if(projectile_signed(s.frame)>240||(contact!=0&&contact!=1)||host.stage_collision(s)==1){s.released=true;return false;}
    }
    ++s.frame;host.advance_frame(s);return true;
}
// Free-flight branch of 5f5ec0 only. Ground-constrained movement and attached
// effects belong to the eventual battle host, not this function. The caller
// must refresh the frame contact pose after this function's target-facing step.
inline void move_normal_projectile_free(KeiichiNormalProjectile& s,float target_x,float target_z){
    if(s.released)return;
    if(s.angular){
        const float angle=s.heading+s.offset,cp=legacy_trig(s.pitch,false);
        s.velocity={legacy_trig(angle,false)*cp,legacy_trig(s.pitch,true),legacy_trig(angle,true)*cp};
        for(unsigned i=0;i<3;++i){volatile float d=s.velocity[i]*s.speed;s.position[i]+=d;}
        s.remaining_stage_distance-=s.speed;
    }else{
        for(unsigned i=0;i<3;++i)s.position[i]+=s.velocity[i];
        s.remaining_stage_distance-=projectile_motion_length(s.velocity);
    }
    BattleFacing facing{s.heading,s.offset};face_battle_target(facing,s.position[0],s.position[2],target_x,target_z);
    s.heading=facing.heading;s.offset=facing.offset;
}
}
