#pragma once
#include "keiichi_charged_projectile.hpp"
#include "mion_full_charge_projectile.hpp"
#include "roster_cadence_projectile.hpp"
#include "roster_child_family_projectile.hpp"
#include "roster_simple_projectile.hpp"
#include "roster_motion_projectile.hpp"
#include "item7_projectile.hpp"
#include "item6_projectile.hpp"
#include "item8_projectile.hpp"
#include "item9_13_projectiles.hpp"
#include "item11_22_projectiles.hpp"
#include "item43_46_projectiles.hpp"
#include "item27_45_projectiles.hpp"
#include "item17_39_projectiles.hpp"
#include "item41_projectile.hpp"
#include "remaining_roster_projectiles.hpp"
#include "item14_projectile.hpp"
#include "item20_projectile.hpp"
#include "item24_projectile.hpp"
#include "item30_projectile.hpp"
#include "item44_projectile.hpp"
#include "item32_projectile.hpp"
#include "item40_projectile.hpp"
#include "item28_projectile.hpp"
#include "item10_projectile.hpp"
#include "item21_projectile.hpp"
#include "item15_projectile.hpp"
#include "item16_projectile.hpp"
#include "item29_projectile.hpp"
#include "item23_projectile.hpp"
#include "roster_immediate_release_projectile.hpp"
#include "roster_rotating_fragment_projectile.hpp"
#include "roster_ground_burst_projectile.hpp"
#include "roster_owner_orbit_children.hpp"
#include "roster_timed_scale_projectile.hpp"
#include "roster_linear_bolt_projectile.hpp"
#include "roster_impact_spark_projectile.hpp"
#include "item19_anchor_projectile.hpp"
#include "roster_spiral_projectile.hpp"
#include "item26_flight_projectile.hpp"
#include "item33_direct_fade_projectile.hpp"
#include "item38_secondary_projectile.hpp"
#include "item38_throw_visual_20261004.hpp"
#include "roster_pulsing_fade_projectile.hpp"
#include "roster_trail_steering_projectile.hpp"
#include "item2_5_18_34_projectiles.hpp"

namespace daybreak {
// The original weapon DAT chooses an item and a registration. Resolve that
// pair once, then run the corresponding recovered item-script family. This
// order preserves the original rebuild's special-case precedence and makes
// unsupported DAT routes visible to the whole-roster catalog.
enum class ProjectileScriptFamily {
 mion_normal, mion_charged, mion_full,
 bat_normal, bat_charged, bat_full, bat_visual,
 iron_normal, iron_lobbed, iron_full,
 shovel_normal, shovel_lobbed, shovel_homing_full, shovel_full,
 item36, homing, fade, dynamic_fade, cadence, child,
 simple, motion, item6, item7, item8, item9, item13, item11, item22, item43, item46, item27, item45, item17, item39, item41, item10, item14, item15, item16, item29, item20, item21, item23, item24, item28, item30, item32, item40, item44, item26_flight, item33_direct_fade, pulsing_fade, trail_steering, timed_scale, linear_bolt, impact_spark, item19_anchor, spiral,
 field, field_secondary, field_burst, field_child, item38_secondary, item38_throw_visual, immediate_release,
 birth_only_release, rotating_fragment, ground_burst,
 owner_orbit, owner_orbit_child, generic, remaining_roster, early_item_special
};

inline ProjectileScriptFamily projectile_script_family(unsigned item,unsigned registration){
 using F=ProjectileScriptFamily;
 if(item2_5_18_34_projectile_registration(item,registration))return F::early_item_special;
 if(remaining_roster_projectile_item(item))return F::remaining_roster;
 if(mion_projectile_item(static_cast<KeiichiProjectileItem>(item)))
  return mion_full_charge_projectile_registration(item,registration)?F::mion_full:
         mion_charged_projectile_registration(item,registration)?F::mion_charged:F::mion_normal;
 if(item==unsigned(KeiichiProjectileItem::Bat))
  return registration==0?F::bat_normal:registration==50?F::bat_full:
         (registration==70||registration==90)?F::bat_visual:F::bat_charged;
 if(item==unsigned(KeiichiProjectileItem::Iron))
  return registration==0?F::iron_normal:registration==60?F::iron_full:F::iron_lobbed;
 if(item==unsigned(KeiichiProjectileItem::Shovel))
  return registration==0?F::shovel_normal:registration==50?F::shovel_homing_full:
         registration>=60?F::shovel_full:F::shovel_lobbed;
 if(item==36)return F::item36;
 if(item6_projectile_registration(item,registration))return F::item6;
 if(item8_projectile_registration(item,registration))return F::item8;
 if(item9_projectile_registration(item,registration))return F::item9;
 if(item13_projectile_registration(item,registration))return F::item13;
 if(item11_projectile_registration(item,registration))return F::item11;
 if(item22_projectile_registration(item,registration))return F::item22;
 if(item43_projectile_registration(item,registration))return F::item43;
 if(item46_projectile_registration(item,registration))return F::item46;
 if(item27_projectile_registration(item,registration))return F::item27;
 if(item45_projectile_registration(item,registration))return F::item45;
 if(item17_projectile_registration(item,registration))return F::item17;
 if(item39_projectile_registration(item,registration))return F::item39;
 if(item41_projectile_registration(item,registration))return F::item41;
 if(item16_projectile_registration(item,registration))return F::item16;
 if(item29_projectile_registration(item,registration))return F::item29;
 if(item30_projectile_registration(item,registration))return F::item30;
 if(registration==0&&(item==1||item==29))return F::homing;
 if((item==31&&registration==80)||(registration==0&&(item==40||item==46)))return F::fade;
 if((item==21&&(registration==0||registration==10))||(item==19&&(registration==0||registration==10||registration==80)))return F::dynamic_fade;
 if(roster_cadence_projectile_registration(item,registration))return F::cadence;
 if(roster_child_family_registration(item,registration))return F::child;
 if(item32_projectile_registration(item,registration))return F::item32;
 if(item40_projectile_registration(item,registration))return F::item40;
 if(item28_projectile_registration(item,registration))return F::item28;
 if(item10_projectile_registration(item,registration))return F::item10;
 if(item21_projectile_registration(item,registration))return F::item21;
 if(item15_projectile_registration(item,registration))return F::item15;
 if(item23_projectile_registration(item,registration))return F::item23;
 if(roster_simple_projectile_registration(item,registration))return F::simple;
 if(roster_motion_projectile_registration(item,registration))return F::motion;
 if(item20_projectile_registration(item,registration))return F::item20;
 if(item44_projectile_registration(item,registration))return F::item44;
 if(item7_projectile_registration(item,registration))return F::item7;
 if(item14_projectile_registration(item,registration))return F::item14;
 if(item24_projectile_registration(item,registration))return F::item24;
 if(item26_flight_registration(item,registration))return F::item26_flight;
 if(item33_direct_fade_registration(item,registration))return F::item33_direct_fade;
 if(roster_pulsing_fade_registration(item,registration))return F::pulsing_fade;
 if(roster_trail_steering_registration(item,registration))return F::trail_steering;
 if(roster_timed_scale_projectile_registration(item,registration))return F::timed_scale;
 if(roster_linear_bolt_registration(item,registration))return F::linear_bolt;
 if(roster_impact_spark_registration(item,registration))return F::impact_spark;
 if(item19_anchor_registration(item,registration))return F::item19_anchor;
 if(roster_spiral_projectile_registration(item,registration))return F::spiral;
 if(item==17&&(registration==0||registration==10))return F::field;
 if(item==17&&(registration==60||registration==70||registration==80||registration==180))return F::field_secondary;
 if(item==17&&(registration==190||registration==200||registration==210))return F::field_burst;
 if(item==17&&(registration==90||registration==100||registration==110))return F::field_child;
 if(item38_throw_visual_registration(item,registration))return F::item38_throw_visual;
 if(item38_secondary_registration(item,registration))return F::item38_secondary;
 if(roster_immediate_release_registration(item,registration))return F::immediate_release;
 if(item==29&&registration==10)return F::birth_only_release;
 if(roster_rotating_fragment_registration(item,registration))return F::rotating_fragment;
 if(roster_ground_burst_registration(item,registration))return F::ground_burst;
 if(item==37&&registration==80)return F::owner_orbit;
 if(roster_owner_orbit_child_registration(item,registration))return F::owner_orbit_child;
 return F::generic;
}

inline const char* projectile_script_family_name(ProjectileScriptFamily value){
 using F=ProjectileScriptFamily;
 switch(value){
 case F::early_item_special:return "early_item_special";
 case F::mion_normal:return "mion_normal";case F::mion_charged:return "mion_charged";
 case F::mion_full:return "mion_full";case F::bat_normal:return "bat_normal";
 case F::bat_charged:return "bat_charged";case F::bat_full:return "bat_full";
 case F::bat_visual:return "bat_visual";case F::iron_normal:return "iron_normal";
 case F::iron_lobbed:return "iron_lobbed";case F::iron_full:return "iron_full";
 case F::shovel_normal:return "shovel_normal";case F::shovel_lobbed:return "shovel_lobbed";
 case F::shovel_homing_full:return "shovel_homing_full";case F::shovel_full:return "shovel_full";
 case F::item36:return "item36";case F::homing:return "homing";
 case F::fade:return "fade";case F::dynamic_fade:return "dynamic_fade";
 case F::cadence:return "cadence";case F::child:return "child";
 case F::simple:return "simple";case F::motion:return "motion";
 case F::item7:return "item7";
 case F::item8:return "item8";
 case F::item6:return "item6";
 case F::item10:return "item10";
 case F::item21:return "item21";
 case F::item15:return "item15";
 case F::item16:return "item16";
 case F::item29:return "item29";
 case F::item23:return "item23";
 case F::item14:return "item14";
 case F::item20:return "item20";
 case F::item24:return "item24";
 case F::item28:return "item28";
 case F::item30:return "item30";
 case F::item32:return "item32";
 case F::item40:return "item40";
 case F::item44:return "item44";
 case F::item26_flight:return "item26_flight";
 case F::item33_direct_fade:return "item33_direct_fade";
 case F::pulsing_fade:return "pulsing_fade";
 case F::trail_steering:return "trail_steering";
 case F::timed_scale:return "timed_scale";
 case F::linear_bolt:return "linear_bolt";
 case F::impact_spark:return "impact_spark";
 case F::item19_anchor:return "item19_anchor";
 case F::spiral:return "spiral";
 case F::field:return "field";case F::field_secondary:return "field_secondary";
 case F::field_burst:return "field_burst";
 case F::field_child:return "field_child";
 case F::item38_secondary:return "item38_secondary";
 case F::item38_throw_visual:return "item38_throw_visual";
 case F::immediate_release:return "immediate_release";
 case F::birth_only_release:return "birth_only_release";
 case F::rotating_fragment:return "rotating_fragment";case F::ground_burst:return "ground_burst";
 case F::owner_orbit:return "owner_orbit";case F::owner_orbit_child:return "owner_orbit_child";
 case F::generic:return "generic";
 case F::remaining_roster:return "remaining_roster";
 case F::item9:return "item9";
 case F::item13:return "item13";
 case F::item11:return "item11";
 case F::item22:return "item22";
 case F::item43:return "item43";
 case F::item46:return "item46";
 case F::item27:return "item27";
 case F::item45:return "item45";
 case F::item17:return "item17";
 case F::item39:return "item39";
 case F::item41:return "item41";
 }
 return "unknown";
}
}
