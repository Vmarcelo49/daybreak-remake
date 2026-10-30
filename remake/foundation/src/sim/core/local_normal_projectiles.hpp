#pragma once
#include "development_animated_combat.hpp"
#include "projectile_asset_files.hpp"
#include "projectile_frame_cursor.hpp"
#include "projectile_contact_pose.hpp"
#include "projectile_stage_query.hpp"
#include "projectile_reflection_contact.hpp"
#include "stage_collision_mesh.hpp"
#include "battle_stage_ray_direction.hpp"
#include "battle_cpu_obstacle.hpp"
#include "projectile_birth_angles_scalar24.hpp"
#include "keiichi_charged_projectile.hpp"
#include "item36_projectile.hpp"
#include "roster_homing_projectile.hpp"
#include "roster_fade_projectile.hpp"
#include "roster_dynamic_fade_projectile.hpp"
#include "roster_cadence_projectile.hpp"
#include "roster_child_family_projectile.hpp"
#include "roster_simple_projectile.hpp"
#include "roster_motion_projectile.hpp"
#include "roster_field_projectile.hpp"
#include "roster_immediate_release_projectile.hpp"
#include "roster_rotating_fragment_projectile.hpp"
#include "roster_ground_burst_projectile.hpp"
#include "roster_owner_orbit_projectile.hpp"
#include "roster_owner_orbit_children.hpp"
#include "ground_normal_projectile_motion.hpp"
#include "mion_normal_projectile.hpp"
#include "mion_charged_projectile.hpp"
#include "mion_full_charge_projectile.hpp"
#include "projectile_script_dispatch.hpp"
#include "projectile_trail.hpp"
#include "projectile_manager_services.hpp"
#include "legacy_battle_event_codec.hpp"
#include "legacy_projectile_lifetime.hpp"
#include <optional>
#include <map>
namespace daybreak {
// Runtime scheduler for DAT-selected item/registration script families.
// projectile_script_family selects canonical handlers for all current weapons.
// Manager ownership is separate from reflected attack ownership; victim contacts
// use the shared adapter. Missing DAT keeps the documented safety fallback.
class LocalNormalProjectiles {
 AssetSearchPath* search_;
 bool native_reception_=false;
 LegacyHostBattleEvents* native_host_=nullptr;
 std::map<std::pair<unsigned,unsigned>,std::shared_ptr<const ProjectileAssetFiles>> assets_;
 std::vector<std::pair<std::string,std::string>> missing_asset_fallbacks_;
 void preload(unsigned item,unsigned registration){(void)asset_for_registration(item,registration);}
public:
 struct Live {
  KeiichiNormalProjectile state;
  std::shared_ptr<const ProjectileAssetFiles> assets;
  ProjectileFrameCursor cursor;
  std::array<float,3> cached_velocity{};
  BattleNormalHitContact geometry{};
  unsigned pool_owner=0;
  unsigned registration=0;
  bool visual_only=false; // Local unreplicated script child; network38 is an ordinary factory birth.
  bool scene_pool=false; // Explicit manager membership, independent of visual kind.
  LegacyProjectileLifetime native_lifetime;
  std::uint32_t render_argb=0xffffffff; // Original bytes144..147 A,R,G,B.
  unsigned attached_actor=4,attached_bone=0; // Original +140 live combined matrix, rendering only.
  std::optional<ProjectileTrail> trail;
  mutable ActorSkeleton pose_cache;mutable unsigned pose_frame=0;mutable bool pose_valid=false;
  const ActorSkeleton& sampled_pose()const{
   if(!pose_valid||pose_frame!=state.frame){pose_cache=assets->model_animation.sample(state.frame);pose_frame=state.frame;pose_valid=true;}
   return pose_cache;
  }
 };
 std::vector<Live> live;
 static bool bound_render_pose(const Live& p,const DevelopmentAnimatedCombat& combat,
                               const BattleWorld& world,LegacyMatrix& matrix){
  if(p.attached_actor>=world.actors.size())return false;
  matrix=combat.actor_bone_world(world,p.attached_actor,p.attached_bone);return true;
 }
 unsigned spawned=0,released=0,owner_controller_spawned=0;
 unsigned trails_spawned=0,trails_released=0;
 struct ScriptEffect {unsigned owner,id;std::array<float,3> position;};
 std::vector<ScriptEffect> script_effects;
 struct ScriptSound {unsigned owner,id;std::array<float,3> position;};
 std::vector<ScriptSound> script_sounds;
 // Both historical effect() and sound() script services are42c8b0 SE.
 // These vectors retain script evidence. Production audio is appended to
 // combat.sound_requests at the call, preserving body/pool/status/scene order.
 std::vector<ScriptSound> script_audio;
 struct VisualChild {unsigned item,slot,owner;std::array<float,3> position,velocity;};
 struct TrailRequest {unsigned owner,slot;float length;unsigned count,mode,flags;};
 std::vector<TrailRequest> trail_requests;
 std::vector<VisualChild> visual_children; //5f8cb0 births; live visual objects carry the DAT animation.
 explicit LocalNormalProjectiles(AssetSearchPath& search):search_(&search){
  for(unsigned item:{5u,18u,34u})preload(item,0);
  for(unsigned item:{5u,18u,34u})for(unsigned file:{1u,2u,4u,9u}){
   if((item==5&&file>2)||(item!=5&&file==1)||(item==34&&file==9))continue;
   preload(item,file*10u);
  }
  for(unsigned file:{6u,7u,9u})preload(34,file*10u);
  for(unsigned file:{6u,7u,8u,10u})preload(18,file*10u);
  for(unsigned file:{5u,7u,9u})preload(5,file*10u);
  for(unsigned item:{2u,4u,35u}){
   preload(item,0);
   for(unsigned file:(item==2?std::vector<unsigned>{1,2,3,4,5,7,8,9,10,11}:item==4?std::vector<unsigned>{1,2,3,4,5}:std::vector<unsigned>{1,2,3,4,5,6,7,8,9})){
    preload(item,file*10u);
   }
  }
 }
 const std::shared_ptr<const ProjectileAssetFiles>& asset_for_registration(unsigned item,unsigned registration){
  const auto key=std::make_pair(item,registration);
  auto found=assets_.find(key);if(found!=assets_.end())return found->second;
  WeaponBulletData bullet;bullet.file=registration/10u;bullet.variant=registration%10u;
  try{
   auto loaded=std::make_shared<const ProjectileAssetFiles>(load_projectile_asset_files(*search_,item,bullet));
   return assets_.emplace(key,std::move(loaded)).first->second;
  }catch(const std::runtime_error& error){
   const std::string message=error.what();
   if(key==std::make_pair(5u,0u)||message.find("Asset not found: data/bullet/")!=0)throw;
   // Some valid weapon DAT slots name bullet DAT/model files omitted from the
   // supplied archives. Keep the requested item/registration for script and
   // ownership logic, but borrow the known-good basic projectile's display
   // mesh and contact frame so an optional visual asset cannot abort a match.
   const auto& fallback=asset_for_registration(5,0);
   missing_asset_fallbacks_.emplace_back(message.substr(std::string("Asset not found: ").size()),fallback->frame_path);
   return assets_.emplace(key,fallback).first->second;
  }
 }
 const std::shared_ptr<const ProjectileAssetFiles>& asset_for_weapon_slot(unsigned item,const WeaponItemData& weapon,unsigned slot){
  const auto registration=weapon_projectile_registration(weapon,slot);
  const auto& asset=asset_for_registration(item,registration);
  char expected_path[64];std::snprintf(expected_path,sizeof expected_path,"data/bullet/%03u/%03u.dat",item,registration/10u);
  if(asset->frame_path==expected_path&&asset->selected_variant!=registration%10u)throw std::runtime_error("Projectile variant binding mismatch");
  return asset;
 }
 template<class Visit> void visit_assets(Visit&& visit)const{for(const auto& pair:assets_)visit(pair.first.first,pair.second);}
 const auto& missing_asset_fallbacks()const{return missing_asset_fallbacks_;}
 unsigned missing_asset_fallback_count()const{return unsigned(missing_asset_fallbacks_.size());}
 void configure_native_host_events(LegacyHostBattleEvents& host){if(!live.empty()||native_reception_)throw std::logic_error("Host projectiles configured after births");native_host_=&host;}
 void configure_native_reception(){native_reception_=true;for(auto& p:live)p.native_lifetime.managed=true;}
 NativeProjectileEventResult receive_native_projectile(const LegacyBattleEvent& event,const DevelopmentAnimatedCombat& combat,const BattleWorld& world){
  const int owner=event.s(8,1);if(owner<0||owner>=4)return NativeProjectileEventResult::Rejected;
  const auto serial=event.u(12);const unsigned tag=event.tag;
  if(tag==0x38){
   const int target=event.s(9,1),ordinal=event.s(16,2);
   if(target<0||target>=4||ordinal<0)return NativeProjectileEventResult::Rejected;
   const auto& data=combat.actor_assets(unsigned(owner));if(!data.weapon_item)return NativeProjectileEventResult::Unsupported;
   const auto& weapon=*data.weapon_item;if(unsigned(ordinal)>=weapon.bullets.size())return NativeProjectileEventResult::Rejected;
   if(weapon.bullets[ordinal].registration_id()<0)return NativeProjectileEventResult::Unsupported;
   for(unsigned off=20;off<=40;off+=4)if(!std::isfinite(event.f(off)))return NativeProjectileEventResult::Rejected;
   Live p;p.pool_owner=unsigned(owner);p.registration=weapon_projectile_registration(weapon,unsigned(ordinal));
   p.assets=asset_for_weapon_slot(data.parameters[3],weapon,unsigned(ordinal));
   char path[64];std::snprintf(path,sizeof path,"data/bullet/%03u/%03u.dat",data.parameters[3],p.registration/10);
   if(p.assets->frame_path!=path)return NativeProjectileEventResult::Unsupported;
   p.native_lifetime.managed=true;p.native_lifetime.serial=serial;
   auto& s=p.state;s.item=static_cast<KeiichiProjectileItem>(data.parameters[3]);s.owner=unsigned(owner);s.target=unsigned(target);
   for(unsigned axis=0;axis<3;++axis){s.position[axis]=event.f(20+4*axis);s.velocity[axis]=event.f(32+4*axis);}
   initialize_projectile_birth_angles(s,world.actors[s.target].position);
   bind_actor_frame_geometry(p.cursor.current(p.assets->selected()),projectile_contact_pose(s.position,s.velocity,s.heading,s.offset,s.pitch),p.geometry);
   //5F8CB0 appends every birth, including repeated serials. It never makes a
   //network38 object visual-only, nor leaves the temporary global serial set.
   live.push_back(std::move(p));++spawned;return NativeProjectileEventResult::Applied;
  }
  if(tag==0x3b){
   if(event.s(9,1)<0||event.s(9,1)>=4||event.s(16,2)<0||event.s(16,2)>=4)return NativeProjectileEventResult::Rejected;
   for(unsigned off=20;off<=44;off+=4)if(!std::isfinite(event.f(off)))return NativeProjectileEventResult::Rejected;
  }else if(tag!=0x39&&tag!=0x3a)return NativeProjectileEventResult::Unsupported;
  for(std::size_t index=0;index<live.size();){
   auto& p=live[index];if(p.scene_pool||p.pool_owner!=unsigned(owner)||!p.native_lifetime.managed||p.native_lifetime.serial!=serial){++index;continue;}
   if(tag==0x39){
    if(p.native_lifetime.release()){if(p.trail)++trails_released;++released;live.erase(live.begin()+index);continue;}
   }else if(tag==0x3a){
    const auto& opponents=world.actors[owner].relationships.opponents;
    auto next=std::find_if(opponents.begin(),opponents.end(),[&](unsigned actor){return actor!=p.state.target;});
    if(next==opponents.end())return NativeProjectileEventResult::Unsupported;
    p.state.target=*next;if(combat.actor_assets(unsigned(owner)).parameters[3]==10)p.state.scratch_f0=60;
   }else{
    auto& s=p.state;s.owner=unsigned(event.s(16,2));s.target=unsigned(event.s(9,1));
    for(unsigned axis=0;axis<3;++axis)s.position[axis]=event.f(20+4*axis);
    s.heading=event.f(32);s.offset=event.f(36);s.pitch=event.f(40);s.speed=event.f(44);
    //63D5E5 changes only these scalar fields. Direction, age, DAT cursor,
    //cached contact geometry and manager ownership remain as they were.
   }
   ++index;
  }
  return NativeProjectileEventResult::Applied;
 }

 std::optional<Live> prepare_owner_projectile(unsigned owner,unsigned target,unsigned slot,
                             const std::array<float,3>& position,const std::array<float,3>& direction,
                             const DevelopmentAnimatedCombat& combat,const BattleWorld& world,bool scene_pool=false,bool particle=false){
  const unsigned item=combat.actor_assets(owner).parameters[3];
  const auto& weapon=*combat.actor_assets(owner).weapon_item;
  const auto registration=weapon_projectile_registration(weapon,slot);
  Live p;p.pool_owner=owner;p.registration=registration;p.scene_pool=scene_pool;p.visual_only=particle;p.native_lifetime.managed=native_reception_||native_host_;
  auto& s=p.state;s.item=static_cast<KeiichiProjectileItem>(item);s.owner=owner;s.target=target;
  s.position=position;s.velocity=direction;
  if(particle){
   char path[64];std::snprintf(path,sizeof path,"data/bullet/%03u/%03u.dat",item,registration/10);
   // Safety policy for missing particle DAT: the original enters an empty
   // frame slot. Preserve the existing skip instead of running donor physics.
   if(!search_->contains(path))return {};
   p.assets=asset_for_weapon_slot(item,weapon,slot);
   if(p.assets->frame_path!=path)return {};
  }else{
   p.native_lifetime.serial=native_host_?native_host_->next_projectile():legacy_projectile_serial_sequence().next();
   if(native_host_)native_host_->projectile_birth(s.owner,s.target,p.native_lifetime.serial,slot,s.position,s.velocity);
   p.assets=asset_for_weapon_slot(item,weapon,slot);
  }
  //5F8BA0 sends before factory/virtual initialization; encoded direction is
  //the caller's original vector, before angle initialization normalizes it.
  initialize_projectile_birth_angles(s,world.actors.at(s.target).position);
  bind_actor_frame_geometry(p.cursor.current(p.assets->selected()),projectile_contact_pose(s.position,s.velocity,s.heading,s.offset,s.pitch),p.geometry);
  return std::move(p);
 }
 void spawn_owner_projectile(unsigned owner,unsigned target,unsigned slot,
                             const std::array<float,3>& position,const std::array<float,3>& direction,
                             const DevelopmentAnimatedCombat& combat,const BattleWorld& world,bool scene_pool=false,bool particle=false){
  if(auto p=prepare_owner_projectile(owner,target,slot,position,direction,combat,world,scene_pool,particle)){
   live.push_back(std::move(*p));++spawned;
  }
 }
 void spawn(const DevelopmentAnimatedCombat::ShotRequest& request,const DevelopmentAnimatedCombat& combat,const BattleWorld& world){
  spawn_owner_projectile(request.actor,request.target,request.shot.bullet_slot,request.position,
                         projectile_birth_direction_scalar24(request.heading,0,request.shot.pitch),combat,world);
 }
 void update(DevelopmentAnimatedCombat& combat,const BattleWorld& world,const StageCollisionMesh& stage){
  // Standalone projectile fixtures: seed requests before the script pass.
  spawn_requests(combat,world);advance_scripts(combat,world,stage);advance_motion(world,&stage);
  advance_motion(world,&stage,15,true);advance_scripts(combat,world,stage,15,true,true);
 }
 void spawn_requests(const DevelopmentAnimatedCombat& combat,const BattleWorld& world){
  for(const auto& request:combat.shot_requests)spawn(request,combat,world);
 }
 void advance_scripts(DevelopmentAnimatedCombat& combat,const BattleWorld& world,const StageCollisionMesh& stage,unsigned pool_mask=15,bool global_only=false,bool append_events=false){
  if(!append_events){
  script_effects.clear();
  script_sounds.clear();
  script_audio.clear();
  visual_children.clear();trail_requests.clear();
  }
  std::vector<Live> children;
  std::array<std::array<float,3>,4> aim{};
  if(!live.empty())for(unsigned i=0;i<4;++i)aim[i]=combat.target_position(world,i,2);
  //435a20 walks each owner's list through its live sentinel, so appended
  // children run in this same script pass. Owner scripts precede owner motion;
  // the global scene script pass follows contacts in634f60.
  //5f8cb0 appends to the emitting manager, as5f8ba0 does. Owner-born
  //particles share owner scripts/motion and the+828 gate;6cfa30 is separate.
  for(unsigned pool=0;pool<(global_only?1u:4u);++pool)if(global_only||(pool_mask&(1u<<pool)))for(std::size_t index=0;index<live.size();++index){
   if(global_only?!live[index].scene_pool:(live[index].scene_pool||live[index].pool_owner!=pool))continue;
   {auto& p=live[index];p.native_lifetime.begin_script();
   struct ObserverContext {
    LegacyHostBattleEvents* host;Live& p;
    static void reflected(void* raw,const KeiichiNormalProjectile& s){auto& c=*static_cast<ObserverContext*>(raw);if(c.host&&&s==&c.p.state)c.host->projectile_reflect(c.p.pool_owner,s.target,s.owner,c.p.native_lifetime.serial,s.position,s.heading,s.offset,s.pitch,s.speed);}
    static void retargeted(void* raw,const KeiichiNormalProjectile& s){auto& c=*static_cast<ObserverContext*>(raw);if(c.host&&&s==&c.p.state)c.host->projectile_target(s.owner,c.p.native_lifetime.serial);}
   } observer_context{native_host_,p};
   ScopedProjectileEventObserver observer({&observer_context,ObserverContext::reflected,ObserverContext::retargeted});
   struct Host : ProjectileManagerServices {
    LocalNormalProjectiles& projectiles;Live& p;DevelopmentAnimatedCombat& combat;const BattleWorld& world;const StageCollisionMesh& stage;const std::array<std::array<float,3>,4>& aim;
    std::vector<Live>& children;std::vector<ScriptEffect>& effects;std::vector<ScriptSound>& sounds;std::vector<ScriptSound>& audio;
    std::vector<VisualChild>& visuals;std::vector<TrailRequest>& trails;
    unsigned& trail_births;unsigned& trail_deaths;
    void queue_child(const KeiichiNormalProjectile& s,unsigned slot,const std::array<float,3>& position,const std::array<float,3>& direction,bool particle=false){
     //The original helper constructs/initializes now, before later script
     //notifications or the parent's release. Delay vector growth only, so
     //the active parent's references remain valid during its callback.
     if(auto child=projectiles.prepare_owner_projectile(p.pool_owner,s.target,slot,position,direction,combat,world,p.scene_pool,particle))
      children.push_back(std::move(*child));
    }
    void trail(const KeiichiNormalProjectile& s,unsigned slot,float length,unsigned count,unsigned mode,unsigned flags){
     trails.push_back({s.owner,slot,length,count,mode,flags});
     if(p.trail)++trail_deaths;++trail_births;
     p.trail.emplace();p.trail->configure(slot,length,count,mode,flags,s.position);
    }
    void visual_child(const KeiichiNormalProjectile& s,unsigned slot,bool relative=false){
     //5f6fd0/5f7110 call5f8cb0 on the parent manager. Preserve its
     //script/motion pass and let DAT extent/capacity govern contacts.
     auto velocity=s.velocity;
     if(relative){
      velocity=projectile_birth_direction_scalar24(s.heading,s.offset,s.pitch);
     }
     visuals.push_back({unsigned(s.item),slot,s.owner,s.position,velocity});
     auto source=s;source.velocity=velocity;
     queue_child(source,slot,source.position,source.velocity,true);
    }
    void particle(const KeiichiNormalProjectile& s,unsigned slot,float yaw,float pitch){
     //5f7110 ->5f8cb0 appends this particle to the parent manager list.
     visuals.push_back({unsigned(s.item),slot,s.owner,s.position,
                        projectile_birth_direction_scalar24(s.heading,s.offset,s.pitch,yaw,pitch)});
     auto source=s;source.velocity=visuals.back().velocity;
     queue_child(source,slot,source.position,source.velocity,true);
    }
    void particle_offset(const KeiichiNormalProjectile& s,unsigned slot,float x,float y,float z){
     //5f6fd0 creates a particle at this pose plus XYZ offsets and
     //inserts it in the same manager list, with an unreplicated serial.
     visuals.push_back({unsigned(s.item),slot,s.owner,
                        {s.position[0]+x,s.position[1]+y,s.position[2]+z},s.velocity});
     auto source=s;source.position=visuals.back().position;
     queue_child(source,slot,source.position,source.velocity,true);
    }
    void particle_offset_direction(const KeiichiNormalProjectile& s,unsigned slot,float x,float y,float z,float yaw,float pitch){
     // 5f7110: offsets are world coordinates, while the direction is relative
     //to the emitting projectile. DAT governs the resulting contacts.
     auto source=s;source.position={s.position[0]+x,s.position[1]+y,s.position[2]+z};
     particle(source,slot,yaw,pitch);
    }
    void child(const KeiichiNormalProjectile& s,unsigned slot,float yaw,float pitch,bool relative){
     queue_child(s,slot,s.position,relative?projectile_birth_direction_scalar24(s.heading,s.offset,s.pitch,yaw,pitch):projectile_contact_child_direction(s));
    }
    void child_offset(const KeiichiNormalProjectile& s,unsigned slot,float x,float y,float z,float yaw,float pitch){
     queue_child(s,slot,{s.position[0]+x,s.position[1]+y,s.position[2]+z},projectile_birth_direction_scalar24(s.heading,s.offset,s.pitch,yaw,pitch));
    }
    void child_position(const KeiichiNormalProjectile& s,unsigned slot,float x,float y,float z){
     queue_child(s,slot,{s.position[0]+x,s.position[1]+y,s.position[2]+z},projectile_contact_child_direction(s));
    }
    void owner_controller_shot(const KeiichiNormalProjectile& s,unsigned slot,const std::array<float,3>& position,float yaw,float pitch){
     const auto& weapon=*combat.actor_assets(p.pool_owner).weapon_item;
     const auto& bullet=weapon.bullets.at(slot);
     if(bullet.magazine_index>=0&&!consume_battle_round(combat.magazines[p.pool_owner].at(unsigned(bullet.magazine_index))))return;
     auto source=s;source.item=static_cast<KeiichiProjectileItem>(combat.actor_assets(p.pool_owner).parameters[3]);
     source.position=position;source.heading=yaw;source.pitch=pitch;source.target=world.actors.at(p.pool_owner).relationships.target;
     queue_child(source,slot,position,projectile_birth_direction_scalar24(yaw,0,pitch));
     ++projectiles.owner_controller_spawned;
    }
    void collision_geometry(KeiichiNormalProjectile& s){
     bind_actor_frame_geometry(p.cursor.current(p.assets->selected()),
       projectile_contact_pose(s.position,s.velocity,s.heading,s.offset,s.pitch),p.geometry);
     // Item42/reg0 calls the same42cc90 root/yaw ray as CPU actors.
     // 42d2c0 normalizes a distinct float3 before mesh traversal; its strict
     // nearest-distance cap is10000. Preserve the projectile's input/cache.
     s.remaining_stage_distance=BattleCpuObstacleQuery(stage).query(
       s.position,world.actors.at(s.target).position,s.heading).distance;
    }
    float collision_radius(const KeiichiNormalProjectile& s)const{return s.remaining_stage_distance;}
    std::array<float,3> target_position(const KeiichiNormalProjectile& s)const{
     return world.actors.at(s.target).position;
    }
    void effect(const KeiichiNormalProjectile& s,unsigned id){effects.push_back({s.owner,id,s.position});audio.push_back({s.owner,id,s.position});combat.queue_sound({s.owner,id,s.position,BattleSoundMode::Spatial,true});}
    void sound(const KeiichiNormalProjectile& s,unsigned id){sounds.push_back({s.owner,id,s.position});audio.push_back({s.owner,id,s.position});combat.queue_sound({s.owner,id,s.position,BattleSoundMode::Spatial,true});}
    void alpha(const KeiichiNormalProjectile& state,unsigned value){color(state,value,255,255,255);}
    void color(const KeiichiNormalProjectile&,unsigned a,unsigned r,unsigned g,unsigned b){p.render_argb=((a&255u)<<24)|((r&255u)<<16)|((g&255u)<<8)|(b&255u);}
    int target_state(const KeiichiNormalProjectile& s)const{
     const unsigned i=s.target;
     return int(combat.death_state[i]?combat.death_state[i]:combat.ground_hit_state[i]?combat.ground_hit_state[i]:combat.recovery_state[i]?combat.recovery_state[i]:combat.air_state[i]?combat.air_state[i]:combat.elapsed[i]>=0?combat.attack_state[i]:0);
    }
    float target_elevation(const KeiichiNormalProjectile& s)const{
     // 42dac0(2) ->421b90 -> cached spine contact position.
     return battle_target_elevation(s.position,aim[s.target]);
    }
    float target_head_elevation(const KeiichiNormalProjectile& s)const{
     // 42dac0(3) selects the target's head point (+2c0).
     return battle_target_elevation(s.position,combat.target_position(world,s.target,3));
    }
    float field_target_pitch(const KeiichiNormalProjectile& s)const{
     // Item 17 calls 42da80, which aims at the target's root rather than spine.
     return battle_target_elevation(s.position,world.actors.at(s.target).position);
    }
    std::uint32_t random_word(){return combat.next_battle_random();}
    void bind_model_root_bone(const KeiichiNormalProjectile& s,const char* name){
     // 006020f0/registration100 binds [target+11c]'s Bip00, not the owner.
     // Capture the bone identity once; its live world matrix is sampled at draw.
     const auto pose=combat.render_pose(s.target);const auto bone=pose.find(name);
     if(bone){p.attached_actor=s.target;p.attached_bone=unsigned(bone);}
    }
    float target_distance_squared(const KeiichiNormalProjectile& s)const{
     const auto& target=world.actors.at(s.target).position;
     const float x=s.position[0]-target[0],y=s.position[1]-target[1],z=s.position[2]-target[2];
     return x*x+y*y+z*z;
    }
    float target_horizontal_distance_squared(const KeiichiNormalProjectile& s)const{
     const auto& target=world.actors.at(s.target).position;
     const float x=s.position[0]-target[0],z=s.position[2]-target[2];
     return x*x+z*z;
    }
    float target_horizontal_distance(const KeiichiNormalProjectile& s)const{return float(std::sqrt(double(target_horizontal_distance_squared(s))));}
    unsigned stage_collision(KeiichiNormalProjectile& s){
     return query_projectile_stage(s,p.cached_velocity,[&](const auto& position,const auto& velocity){
      float distance=10000.f;
      //42d2c0 completes scalar Normalize in float3 before the portable ray.
      const CollisionPoint origin{position[0],position[1],position[2]};
      const auto direction=battle_stage_ray_direction(velocity);
      for(const auto& hit:stage.intersect(origin,direction))distance=std::min(distance,float(hit.distance));
      return distance;
     });
    }
    void advance_frame(const KeiichiNormalProjectile& s){p.cursor.advance(p.assets->selected(),s.frame);}
   } host{{combat,world,p.pool_owner},*this,p,combat,world,stage,aim,children,script_effects,script_sounds,script_audio,visual_children,trail_requests,trails_spawned,trails_released};
   bool alive=false;const auto item=unsigned(p.state.item);
   using F=ProjectileScriptFamily;
   switch(projectile_script_family(item,p.registration)){
   case F::early_item_special:alive=tick_item2_5_18_34_projectile(p.state,p.registration,host);break;
   case F::mion_normal:alive=tick_mion_normal_projectile(p.state,p.registration,host);break;
   case F::mion_charged:alive=tick_mion_charged_projectile(p.state,p.registration,host);break;
   case F::mion_full:alive=tick_mion_full_charge_projectile(p.state,p.registration,host);break;
   case F::bat_normal:case F::iron_normal:case F::shovel_normal:
    alive=tick_keiichi_normal_projectile(p.state,host);break;
   case F::bat_charged:alive=tick_bat_charged_projectile(p.state,p.registration,host);break;
   case F::bat_full:alive=tick_bat_full_charge_projectile(p.state,host);break;
   case F::bat_visual:alive=tick_bat_full_charge_visual(p.state,p.registration,host);break;
   case F::iron_lobbed:case F::shovel_lobbed:
    alive=tick_lobbed_charge_projectile(p.state,p.registration,host);break;
   case F::iron_full:alive=tick_iron_full_charge_projectile(p.state,host);break;
   case F::shovel_homing_full:
    alive=tick_shovel_homing_full_charge_projectile(p.state,p.registration,host);break;
   case F::shovel_full:alive=tick_shovel_full_charge_projectile(p.state,p.registration,host);break;
   case F::item36:alive=tick_item36_projectile(p.state,p.registration,host);break;
   case F::homing:alive=tick_roster_homing_projectile(p.state,host);break;
   case F::fade:alive=tick_roster_fade_projectile(p.state,host);break;
   case F::dynamic_fade:
    alive=tick_roster_dynamic_fade_projectile(p.state,host,p.registration);break;
   case F::cadence:alive=tick_roster_cadence_projectile(p.state,p.registration,host);break;
   case F::child:alive=tick_roster_child_family_projectile(p.state,p.registration,host);break;
   case F::simple:alive=tick_roster_simple_projectile(p.state,host,p.registration);break;
    case F::motion:alive=tick_roster_motion_projectile(p.state,host,p.registration);break;
    case F::item7:alive=tick_item7_projectile(p.state,p.registration,host);break;
    case F::item10:alive=tick_item10_projectile(p.state,p.registration,host);break;
    case F::item21:alive=tick_item21_projectile(p.state,p.registration,host);break;
    case F::item15:alive=tick_item15_projectile(p.state,p.registration,host);break;
    case F::item16:alive=tick_item16_projectile(p.state,p.registration,host);break;
    case F::item8:alive=tick_item8_projectile(p.state,p.registration,host);break;
    case F::item6:alive=tick_item6_projectile(p.state,p.registration,host);break;
    case F::item29:alive=tick_item29_projectile(p.state,p.registration,host);break;
    case F::item23:alive=tick_item23_projectile(p.state,p.registration,host);break;
    case F::item14:alive=tick_item14_projectile(p.state,p.registration,host);break;
    case F::item20:alive=tick_item20_projectile(p.state,p.registration,host);break;
   case F::item24:alive=tick_item24_projectile(p.state,p.registration,host);break;
   case F::item28:alive=tick_item28_projectile(p.state,p.registration,host);break;
   case F::item30:alive=tick_item30_projectile(p.state,p.registration,host);break;
   case F::item32:alive=tick_item32_projectile(p.state,p.registration,host);break;
   case F::item40:alive=tick_item40_projectile(p.state,p.registration,host);break;
   case F::item44:alive=tick_item44_projectile(p.state,p.registration,host);break;
   case F::item26_flight:
    alive=tick_item26_flight_projectile(p.state,p.registration,host);break;
   case F::item33_direct_fade:
    alive=tick_item33_direct_fade_projectile(p.state,p.registration,host);break;
   case F::pulsing_fade:
    alive=tick_roster_pulsing_fade_projectile(p.state,p.registration,host);break;
   case F::trail_steering:
    alive=tick_roster_trail_steering_projectile(p.state,p.registration,host);break;
   case F::timed_scale:
    alive=tick_roster_timed_scale_projectile(p.state,p.registration,host);break;
   case F::linear_bolt:
    alive=tick_roster_linear_bolt_projectile(p.state,p.registration,host);break;
   case F::impact_spark:
    alive=tick_roster_impact_spark_projectile(p.state,p.registration,host);break;
   case F::item19_anchor:
    alive=tick_item19_anchor_projectile(p.state,p.registration,host);break;
   case F::spiral:
    alive=tick_roster_spiral_projectile(p.state,p.registration,host);break;
   case F::field:alive=tick_roster_field_projectile(p.state,host);break;
   case F::field_secondary:
    alive=tick_roster_field_secondary_projectile(p.state,p.registration,host);break;
   case F::field_burst:
    alive=tick_roster_field_burst_projectile(p.state,p.registration,host);break;
   case F::field_child:
    alive=tick_roster_field_child_projectile(p.state,p.registration,host);break;
   case F::item38_secondary:
    alive=tick_item38_secondary_projectile(p.state,p.registration,host);break;
   case F::item38_throw_visual:
    alive=tick_item38_throw_visual(p.state,p.registration,host);break;
   case F::immediate_release:alive=tick_roster_immediate_release_projectile(p.state);break;
   case F::birth_only_release:
    alive=tick_roster_birth_only_release_projectile(p.state,host);break;
   case F::rotating_fragment:
    alive=tick_roster_rotating_fragment_projectile(p.state,p.registration,host);break;
   case F::ground_burst:
    alive=tick_roster_ground_burst_projectile(p.state,p.registration,host);break;
   case F::owner_orbit:alive=tick_roster_owner_orbit_projectile(p.state,host);break;
   case F::owner_orbit_child:
    alive=tick_roster_owner_orbit_child(p.state,p.registration,host);break;
   case F::generic:alive=tick_generic_normal_projectile(p.state,host,p.registration);break;
   case F::item9:alive=tick_item9_projectile(p.state,p.registration,host);break;
   case F::item13:alive=tick_item13_projectile(p.state,p.registration,host);break;
   case F::item11:alive=tick_item11_projectile(p.state,p.registration,host);break;
   case F::item22:alive=tick_item22_projectile(p.state,p.registration,host);break;
   case F::item43:alive=tick_item43_projectile(p.state,p.registration,host);break;
   case F::item46:alive=tick_item46_projectile(p.state,p.registration,host);break;
   case F::item27:alive=tick_item27_projectile(p.state,p.registration,host);break;
   case F::item17:alive=tick_item17_projectile(p.state,p.registration,host);break;
   case F::item39:alive=tick_item39_projectile(p.state,p.registration,host);break;
   case F::item41:alive=tick_item41_projectile(p.state,p.registration,host);break;
   case F::item45:alive=tick_item45_projectile(p.state,p.registration,host);break;
   case F::remaining_roster:alive=tick_remaining_roster_projectile(p.state,p.registration,host);break;
   }
   if(!alive&&native_host_)native_host_->projectile_release(p.state.owner,p.native_lifetime.serial); //before object release, not the temporary script reference
   const bool destroy=p.native_lifetime.finish_script(!alive);
   if(p.native_lifetime.managed){
    if(!alive&&p.trail){p.trail.reset();++trails_released;}
    p.state.released=destroy; //A nonzero external hold keeps the script object live.
   }
   if(destroy){
    ++released;
    if(p.trail)++trails_released;
    // Item 36 emits actor +f8 during its script, including 2/3 contact-input
    // signals; release alone does not notify that character.
    if(!p.visual_only)combat.notify_roster_shot_projectile_finished(p.pool_owner,p.registration);
   }
   }
 // Append after releasing references to the vector's current object. Erasure
 // waits until the script pass ends, keeping the index valid during growth.
  for(auto& child:children){live.push_back(std::move(child));++spawned;}
 children.clear();
 }
 live.erase(std::remove_if(live.begin(),live.end(),[pool_mask,global_only](const Live& p){return (global_only?p.scene_pool:(!p.scene_pool&&(pool_mask&(1u<<p.pool_owner))))&&p.state.released;}),live.end());
 }
 void advance_motion(const BattleWorld& world,const StageCollisionMesh* stage=nullptr,unsigned pool_mask=15,bool global_only=false){
 for(auto& p:live)if(global_only?p.scene_pool:(!p.scene_pool&&(pool_mask&(1u<<p.pool_owner)))){
  const auto& target=world.actors.at(p.state.target).position;
  if(p.state.ground_motion)move_normal_projectile_ground(p.state,target[0],target[2],stage);
  else move_normal_projectile_free(p.state,target[0],target[2]);
  bind_actor_frame_geometry(p.cursor.current(p.assets->selected()),projectile_contact_pose(p.state.position,p.state.velocity,p.state.heading,p.state.offset,p.state.pitch),p.geometry);
  if(p.trail)p.trail->advance(p.state.position);
 }
 }
 void resolve_contacts(DevelopmentAnimatedCombat& combat,BattleWorld& world){
  for(unsigned pool=0;pool<4;++pool)resolve_pool_contacts(combat,world,pool);
 }
 void resolve_pool_contacts(DevelopmentAnimatedCombat& combat,BattleWorld& world,unsigned pool,bool reuse_body_points=false){
  for(auto& p:live)if(p.pool_owner==pool&&!p.scene_pool&&!p.state.released){
   const auto& frame=p.cursor.current(p.assets->selected());
   combat.resolve_projectile_contacts(world,p.state,frame,p.geometry,reuse_body_points);
   //637774..637818: each projectile's fighter contacts precede the other
   //owner pools in ascending pool/birth order. Reflected owner != pool owner.
   if(frame.flags28&0x10000u)for(unsigned other=0;other<4;++other)if(other!=pool)
    for(auto& target:live)if(target.pool_owner==other&&!target.scene_pool&&!target.state.released)
     mark_projectile_reflection(p.state,frame,p.geometry,target.state,
      target.cursor.current(target.assets->selected()),target.geometry);
  }
 }
};
}
