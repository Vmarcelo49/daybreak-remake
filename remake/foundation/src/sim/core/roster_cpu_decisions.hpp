#pragma once
#include "mion_cpu.hpp"
#include "character_dispatch.hpp"
#include <cmath>
namespace daybreak {
struct RosterCpuContext: KeiichiCpuContext {int field_rank=0,field_rank_timer=0;};
namespace roster_cpu_detail {
// Original 00654b90 omits FPU_PRESERVE; native oracle uses precision24 (007f).
using uint=std::uint32_t;using ushort=std::uint16_t;using float10=float;
// Preserve the original word stores without signed-overflow arithmetic.
inline int signed_word(std::uint32_t n){return n<0x80000000u?int(n):int(std::int64_t(n)-0x100000000ll);}
inline bool is_nan(float10 n){return std::isnan(n);}
// Original 00447730; rena weapon 0. Typed policy, not an executable address.
template<class Random> void advance_rena_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 2.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 0x1c2 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 100 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 400 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 400) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)640000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 0x96 == 0) ||
          ((random_value = random.next(), random_value % 0x7d == 0 && (c.command == '\x02'))))
         && (distance = (float10)c.distance_squared,
            distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 100 != 0) {
        random_value = random.next();
        if (random_value % 0x4b != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)4000000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison >= distance && (comparison == distance) == 0) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 0044efd0; rena weapon 1. Typed policy, not an executable address.
template<class Random> void advance_rena_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 2.5;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 100 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 400 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 400) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)160000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < melee_chance) {
      comparison = (float10)c.distance_squared;
      distance = (float10)40000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        shoot_roll = random.next();
        random_value = shoot_roll / 0x96;
        if (shoot_roll % 0x96 == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 004b3570; satoko weapon 0. Typed policy, not an executable address.
template<class Random> void advance_satoko_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xf0));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x7d == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 4 + 1) * 0xc) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 4 + 1) * 0xc) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)422500.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)422500.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)202500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)62500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 0xaf == 0) ||
          ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02'))))
         && (distance = (float10)c.distance_squared,
            distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x7d != 0) {
        random_value = random.next();
        if (random_value % 100 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)2250000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 004bb500; satoko weapon 1. Typed policy, not an executable address.
template<class Random> void advance_satoko_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xf0));
    }
    if (((s.charge == 0) &&
        (distance = (float10)c.distance_squared, distance < (float10)1000000.0)) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x7d == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 4 + 1) * 0xc) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 4 + 1) * 0xc) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)422500.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)40000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)202500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)62500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 0xaf == 0) ||
          ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02'))))
         && ((distance = (float10)c.distance_squared, distance < (float10)4000000.0 &&
             (distance = (float10)c.distance_squared,
             distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)))) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x7d != 0) {
        random_value = random.next();
        if (random_value % 100 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)90000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison >= distance && (comparison == distance) == 0) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 004924f0; rika weapon 0. Typed policy, not an executable address.
template<class Random> void advance_rika_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x15e < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)10000.0 < distance &&
         (random_value = random.next(), random_value % 0x4b == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (500 < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 100 == 0 ||
        ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xf) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0x14) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xf) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0x14) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 400) < (int)((2 - (uint)(c.command != '\x05')) * 0x14))
          && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)1440000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)90000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x96 == 0) ||
          ((random_value = random.next(), random_value % 100 == 0 && (c.command == '\x01')))) &&
         (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 0x96 == 0) ||
         ((random_value = random.next(), random_value % 100 == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x87 == 0) ||
          ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 0x7d == 0) ||
          ((random_value = random.next(), random_value % 100 == 0 && (c.command == '\x02')))) &&
         (distance = (float10)c.distance_squared,
         distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x32 != 0) {
        random_value = random.next();
        if (random_value % 0x2d != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1000000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison >= distance && (comparison == distance) == 0) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 0049ce70; rika weapon 1. Typed policy, not an executable address.
template<class Random> void advance_rika_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x15e < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)10000.0 < distance &&
         (random_value = random.next(), random_value % 0x4b == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (500 < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    distance = (float10)c.distance_squared;
    if ((((float10)250000.0 < distance) && (s.charge == 0)) &&
       ((random_value = random.next(), random_value % 100 == 0 ||
        ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xf) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0x14) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xf) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0x14) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 400) < (int)((2 - (uint)(c.command != '\x05')) * 0x14))
          && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)1440000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)90000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x96 == 0) ||
          ((random_value = random.next(), random_value % 100 == 0 && (c.command == '\x01')))) &&
         (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 0x96 == 0) ||
         ((random_value = random.next(), random_value % 100 == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x87 == 0) ||
          ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 100 != 0) {
        random_value = random.next();
        if (random_value % 0x4b != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)640000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison >= distance && (comparison == distance) == 0) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 00502a50; shion weapon 0. Typed policy, not an executable address.
template<class Random> void advance_shion_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if (((s.charge == 0) &&
        (distance = (float10)c.distance_squared, distance < (float10)160000.0)) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x7d == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)22500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 0x7d != 0) {
        random_value = random.next();
        if (random_value % 100 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1690000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 0050a3e0; shion weapon 1. Typed policy, not an executable address.
template<class Random> void advance_shion_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if (((s.charge == 0) &&
        (distance = (float10)c.distance_squared, distance < (float10)360000.0)) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x7d == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)22500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 0x4b != 0) {
        random_value = random.next();
        if (random_value % 0x32 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)250000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 0051ede0; tomitake weapon 0. Typed policy, not an executable address.
template<class Random> void advance_tomitake_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.25;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 0xaf == 0 ||
        ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)490000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x1e == 0) ||
          ((random_value = random.next(), random_value % 0x14 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)490000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x28 == 0) ||
          ((random_value = random.next(), random_value % 0x1e == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)160000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x1e == 0) ||
          ((random_value = random.next(), random_value % 0x14 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 0x50 != 0) {
        random_value = random.next();
        if (random_value % 0x3c != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)360000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 00526de0; tomitake weapon 1. Typed policy, not an executable address.
template<class Random> void advance_tomitake_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 2.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x28 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x7d == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)490000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x1e == 0) ||
          ((random_value = random.next(), random_value % 0x14 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)490000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x28 == 0) ||
          ((random_value = random.next(), random_value % 0x1e == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)160000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x1e == 0) ||
          ((random_value = random.next(), random_value % 0x14 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 0xaf != 0) {
        random_value = random.next();
        if (random_value % 0x96 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)3062500.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 0053b180; takano weapon 0. Typed policy, not an executable address.
template<class Random> void advance_takano_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 100 == 0 ||
        ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 500) < (int)(((uint)(c.command != '\x05') * -2 + 3) * 10)
           ) && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)1000000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 100 == 0) ||
         ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 0x7d == 0) ||
          ((random_value = random.next(), random_value % 100 == 0 && (c.command == '\x02')))) &&
         (distance = (float10)c.distance_squared,
         distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 100 != 0) {
        random_value = random.next();
        if (random_value % 0x4b != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)2250000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 005454f0; takano weapon 1. Typed policy, not an executable address.
template<class Random> void advance_takano_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 100 == 0 ||
        ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 500) < (int)(((uint)(c.command != '\x05') * -2 + 3) * 10)
           ) && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)1000000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 100 == 0) ||
         ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 0x55 != 0) {
        random_value = random.next();
        if (random_value % 0x41 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1000000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 004d4ed0; ohishi weapon 1. Typed policy, not an executable address.
template<class Random> void advance_ohishi_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((-1 < c.field_rank) && (c.field_rank_timer < 0x5a)) &&
       (random_value = random.next(), random_value % 100 < 0x10)) {
      out.released[2] = signed_word(std::uint32_t(1));
      s.charge = signed_word(std::uint32_t(0));
    }
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    distance = (float10)c.distance_squared;
    if (((distance < (float10)1000000.0) && (s.charge == 0)) &&
       (random_value = random.next(), random_value % 0x4b == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 400 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if (((((int)(random_value % 400) <
             (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
           (500 < c.gauge)) &&
          (distance = (float10)c.distance_squared,
          (float10)40000.0 * (float10)range_scale * (float10)range_scale < distance)) &&
         ((s.jump < 1 && (out.dash == 0)))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 0x32;
    if (shoot_roll % 0x32 < melee_chance) {
      comparison = (float10)c.distance_squared;
      distance = (float10)90000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        shoot_roll = random.next();
        random_value = shoot_roll / 0x32;
        if (shoot_roll % 0x32 != 0) {
          random_value = random.next();
          if (random_value % 0x19 != 0) {
            return;
          }
          random_value = 1;
          if ((int)c.command != 1) {
            return;
          }
        }
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
    }
  }
  return;
}
// Original 004de400; ohishi weapon 2. Typed policy, not an executable address.
template<class Random> void advance_ohishi_2(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    distance = (float10)c.distance_squared;
    if (((distance < (float10)9000000.0) && (s.charge == 0)) &&
       (random_value = random.next(), random_value % 0x4b == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 400 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if (((((int)(random_value % 400) <
             (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
           (500 < c.gauge)) &&
          (distance = (float10)c.distance_squared,
          (float10)40000.0 * (float10)range_scale * (float10)range_scale < distance)) &&
         ((s.jump < 1 && (out.dash == 0)))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 0x32;
    if (shoot_roll % 0x32 < melee_chance) {
      comparison = (float10)c.distance_squared;
      distance = (float10)90000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        shoot_roll = random.next();
        random_value = shoot_roll / 0x32;
        if (shoot_roll % 0x32 != 0) {
          random_value = random.next();
          if (random_value % 0x19 != 0) {
            return;
          }
          random_value = 1;
          if ((int)c.command != 1) {
            return;
          }
        }
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
    }
  }
  return;
}
// Original 004e6b70; akasaka weapon 0. Typed policy, not an executable address.
template<class Random> void advance_akasaka_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 200 == 0 ||
        ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)202500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 200 == 0) ||
          ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02'))))
         && (distance = (float10)c.distance_squared,
            distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x7d != 0) {
        random_value = random.next();
        if (random_value % 0x6e != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)2250000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 004ef580; akasaka weapon 1. Typed policy, not an executable address.
template<class Random> void advance_akasaka_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if (((s.charge == 0) &&
        (distance = (float10)c.distance_squared, distance < (float10)360000.0)) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x7d == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)202500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)122500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 0x7d != 0) {
        random_value = random.next();
        if (random_value % 100 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1690000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 0057eb80; irie weapon 0. Typed policy, not an executable address.
template<class Random> void advance_irie_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 100 == 0 ||
        ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 500) < (int)(((uint)(c.command != '\x05') * -2 + 3) * 10)
           ) && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)1000000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 100 == 0) ||
         ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)62500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 0xaf == 0) ||
          ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02'))))
         && (distance = (float10)c.distance_squared,
            distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x96 != 0) {
        random_value = random.next();
        if (random_value % 0x7d != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1000000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 00589c90; irie weapon 1. Typed policy, not an executable address.
template<class Random> void advance_irie_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 100 == 0 ||
        ((random_value = random.next(), random_value % 0x55 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 500) < (int)(((uint)(c.command != '\x05') * -2 + 3) * 10)
           ) && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)1000000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)90000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 100 == 0) ||
         ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)62500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 0x96 != 0) {
        random_value = random.next();
        if (random_value % 0x7d != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)640000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 0055b350; chie weapon 0. Typed policy, not an executable address.
template<class Random> void advance_chie_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    distance = (float10)c.distance_squared;
    if (((distance < (float10)640000.0) && (s.charge == 0)) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)490000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)22500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)62500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 200 == 0) ||
          ((random_value = random.next(), random_value % 0x96 == 0 && (c.command == '\x02'))))
         && (distance = (float10)c.distance_squared,
            distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x7d != 0) {
        random_value = random.next();
        if (random_value % 0x6e != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)2250000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 00565f30; chie weapon 1. Typed policy, not an executable address.
template<class Random> void advance_chie_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 200 == 0 ||
        ((random_value = random.next(), random_value % 0xaf == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 300) <
            (int)(((uint)(c.command != '\x05') * -2 + 3) * 0xc)) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)490000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)250000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)22500.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)62500.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (((random_value % 0xaf == 0) ||
          ((random_value = random.next(), random_value % 0x82 == 0 && (c.command == '\x02'))))
         && (distance = (float10)c.distance_squared,
            distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x7d != 0) {
        random_value = random.next();
        if (random_value % 100 != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)2250000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 005b8be0; kasai weapon 0. Typed policy, not an executable address.
template<class Random> void advance_kasai_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 0x50 == 0 ||
        ((random_value = random.next(), random_value % 0x3c == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 500) < (int)(((uint)(c.command != '\x05') * -2 + 3) * 10)
           ) && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)2250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)160000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 100 == 0) ||
         ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 500 == 0) ||
          ((random_value = random.next(), random_value % 0x1c2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if ((((random_value % 200 == 0) ||
           ((random_value = random.next(), random_value % 0xaf == 0 && (c.command == '\x02'))))
          && (distance = (float10)c.distance_squared,
             distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) &&
         (distance = (float10)c.distance_squared, distance < (float10)4000000.0)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 0x96 != 0) {
        random_value = random.next();
        if (random_value % 0x7d != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1000000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 005c28b0; kasai weapon 1. Typed policy, not an executable address.
template<class Random> void advance_kasai_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 3.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 100 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 500 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 0x96 == 0 ||
        ((random_value = random.next(), random_value % 0x4bf == 0 && (c.command == '\x02'))))))
    {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if ((((int)(random_value % 500) < (int)(((uint)(c.command != '\x05') * -2 + 3) * 10)
           ) && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)2250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 100 == 0) ||
          ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)160000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if ((random_value % 100 == 0) ||
         ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 500 == 0) ||
          ((random_value = random.next(), random_value % 0x1c2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if ((((random_value % 100 == 0) ||
           ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x02'))))
          && (distance = (float10)c.distance_squared,
             distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) &&
         (distance = (float10)c.distance_squared, distance < (float10)6250000.0)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      random_value = random.next();
      if (random_value % 100 != 0) {
        random_value = random.next();
        if (random_value % 0x4b != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1000000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 005cab90; kasai weapon 2. Typed policy, not an executable address.
template<class Random> void advance_kasai_2(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 1.5;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 4.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  shoot_roll = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.action != 0x1c2) && (c.action != 0x15e)) ||
          ((distance = (float10)c.distance_squared, (float10)250000.0 <= distance ||
           (random_value = random.next(), 0x14 < random_value % 100)))) {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (shoot_roll = random.next(), shoot_roll % 100 == 1)))))) {
      shoot_roll = random.next();
      s.jump = signed_word(std::uint32_t(shoot_roll % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (shoot_roll = random.next(), shoot_roll % 100 < 10)))) {
      shoot_roll = random.next();
      s.jump = signed_word(std::uint32_t(shoot_roll % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (shoot_roll = random.next(), shoot_roll % 500 == 0)) {
      shoot_roll = random.next();
      s.charge = signed_word(std::uint32_t(shoot_roll % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((shoot_roll = random.next(), shoot_roll % 0x50 == 0 ||
        ((shoot_roll = random.next(), shoot_roll % 0x3c == 0 && (c.command == '\x02')))))) {
      shoot_roll = random.next();
      s.charge = signed_word(std::uint32_t(shoot_roll % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        shoot_roll = random.next();
        if ((shoot_roll % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        shoot_roll = random.next();
        if (((shoot_roll % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        shoot_roll = random.next();
        if (shoot_roll % 100 == 0) {
          shoot_roll = random.next();
          s.lateral = signed_word(std::uint32_t(shoot_roll % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      shoot_roll = random.next();
      if ((shoot_roll % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      shoot_roll = random.next();
      if (((shoot_roll % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 10) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        shoot_roll = random.next();
        if ((((int)(shoot_roll % 0xfa) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)1000000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          shoot_roll = random.next();
          s.forward = signed_word(std::uint32_t(shoot_roll % 300 - 0x3c));
        }
        else {
          shoot_roll = random.next();
          s.forward = signed_word(std::uint32_t(shoot_roll % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      shoot_roll = random.next();
      if (((shoot_roll % 500 < (uint)(c.command == '\x05') * 9 + 1) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      shoot_roll = random.next();
      if ((((int)(shoot_roll % 500) < (int)(((uint)(c.command != '\x05') * -2 + 3) * 10)
           ) && (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)2250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)160000.0) && (shoot_roll = random.next(), shoot_roll % 100 < melee_chance)) {
      shoot_roll = random.next();
      if (((shoot_roll % 100 == 0) ||
          ((shoot_roll = random.next(), shoot_roll % 0x4b == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)160000.0)) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      shoot_roll = random.next();
      if ((shoot_roll % 100 == 0) ||
         ((shoot_roll = random.next(), shoot_roll % 0x4b == 0 && (c.command == '\x01')))) {
        out.x = signed_word(std::uint32_t(0));
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
      shoot_roll = random.next();
      if (((shoot_roll % 500 == 0) ||
          ((shoot_roll = random.next(), shoot_roll % 0x1c2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(1));
        out.released[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    random_value = random.next();
    shoot_roll = random_value / 100;
    if (random_value % 100 < shooting_chance) {
      shoot_roll = random.next();
      if ((((shoot_roll % 200 == 0) ||
           ((shoot_roll = random.next(), shoot_roll % 0xaf == 0 && (c.command == '\x02'))))
          && (distance = (float10)c.distance_squared,
             distance < (float10)c.obstacle_distance * (float10)c.obstacle_distance)) &&
         (distance = (float10)c.distance_squared, distance < (float10)4000000.0)) {
        out.released[2] = signed_word(std::uint32_t(1));
        s.charge = signed_word(std::uint32_t(0));
      }
      shoot_roll = random.next();
      if (shoot_roll % 0x96 != 0) {
        shoot_roll = random.next();
        if (shoot_roll % 0x7d != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1000000.0;
      shoot_roll = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        shoot_roll = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          shoot_roll = 0u;
        }
      }
    }
  }
  else {
    out.x = signed_word(std::uint32_t(0));
    out.z = signed_word(std::uint32_t(0));
    out.released[1] = signed_word(std::uint32_t(1));
  }
  return;
}
// Original 0059db40; akane weapon 0. Typed policy, not an executable address.
template<class Random> void advance_akane_0(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 2.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 200 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    distance = (float10)c.distance_squared;
    if (((distance < (float10)1000000.0) && (s.charge == 0)) &&
       ((random_value = random.next(), random_value % 100 == 0 ||
        ((random_value = random.next(), random_value % 0x4b == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if (((random_value % 300 < ((uint)(c.command == '\x05') * 4 + 1) * 0xc) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)40000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)490000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x1e == 0) ||
          ((random_value = random.next(), random_value % 0x14 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)490000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.x = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(1));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 100 != 0) {
        random_value = random.next();
        if (random_value % 0x4b != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)2250000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
// Original 005a73d0; akane weapon 1. Typed policy, not an executable address.
template<class Random> void advance_akane_1(KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random)
{
  uint random_value;
  uint shoot_roll;
  float10 distance;
  float10 comparison;
  int button;
  uint melee_chance;
  float range_scale;
  uint shooting_chance;
  
  // Obstacle query is computed once by the shared driver.
  out.dash = signed_word(std::uint32_t(0));
  range_scale = 1.0;
  shooting_chance = 100;
  melee_chance = 100;
  out.target = signed_word(std::uint32_t(0));
  for (button = 0; button < 3; button = button + 1) {
    out.released[button] = signed_word(std::uint32_t(0));
    out.held[button] = signed_word(std::uint32_t(0));
  }
  switch(c.command) {
  case 0:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    break;
  case 1:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 0.25;
    shooting_chance = 0x32;
    melee_chance = 200;
    break;
  case 2:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 2.0;
    shooting_chance = 200;
    melee_chance = 0x32;
    break;
  case 3:
    if (c.target_index != c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 4:
    if (c.target_index == c.ally_target_index) {
      out.target = signed_word(std::uint32_t(1));
    }
    break;
  case 5:
    out.target = signed_word(std::uint32_t(c.nearest_target_request));
    range_scale = 7.0;
    shooting_chance = 5;
    melee_chance = 5;
  }
  random_value = 0u;
  if (((c.special845 == '\0') &&
      (c.threshold32c <= c.timer83c)) &&
     ((c.action < 100 || (299 < c.action)))) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else if (((c.special844 == '\0') &&
           (c.threshold324 <= c.timer838)) &&
          (c.action < 300)) {
    out.held[2] = signed_word(std::uint32_t(1));
    out.held[1] = signed_word(std::uint32_t(1));
  }
  else {
    if (((c.grounded != '\0') && (s.jump == 0)) &&
       ((0x28a < c.gauge &&
        ((distance = (float10)c.distance_squared, (float10)40000.0 < distance &&
         (random_value = random.next(), random_value % 0x96 == 1)))))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 10));
    }
    if ((((c.grounded != '\0') &&
         (c.obstacle_distance < 300.0 !=
          (c.obstacle_distance == 300.0))) && (0x28a < c.gauge)) &&
       ((distance = (float10)c.distance_squared, (float10)250000.0 < distance &&
        (random_value = random.next(), random_value % 100 < 10)))) {
      random_value = random.next();
      s.jump = signed_word(std::uint32_t(random_value % 0x78 + 0x3c));
    }
    if ((s.charge == 0) && (random_value = random.next(), random_value % 400 == 0)) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4 + 0xb4));
    }
    if ((s.charge == 0) &&
       ((random_value = random.next(), random_value % 0x32 == 0 ||
        ((random_value = random.next(), random_value % 0x28 == 0 && (c.command == '\x02')))))) {
      random_value = random.next();
      s.charge = signed_word(std::uint32_t(random_value % 0xb4));
    }
    if (0 < s.charge) {
      s.charge = signed_word(std::uint32_t(s.charge + -1));
      out.held[2] = signed_word(std::uint32_t(4));
    }
    if (s.lateral < 1) {
      if (s.lateral < 0) {
        s.lateral = signed_word(std::uint32_t(s.lateral + 1));
        out.x = signed_word(std::uint32_t(0xffffffff));
        random_value = random.next();
        if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
           (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
        random_value = random.next();
        if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
            (500 < c.gauge)) && (s.jump < 1)) {
          out.dash = signed_word(std::uint32_t(3));
        }
      }
      else {
        random_value = random.next();
        if (random_value % 100 == 0) {
          random_value = random.next();
          s.lateral = signed_word(std::uint32_t(random_value % 400 - 200));
        }
      }
    }
    else {
      s.lateral = signed_word(std::uint32_t(s.lateral + -1));
      out.x = signed_word(std::uint32_t(1));
      random_value = random.next();
      if ((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
         (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
      random_value = random.next();
      if (((random_value % 100 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
          (500 < c.gauge)) && (s.jump < 1)) {
        out.dash = signed_word(std::uint32_t(4));
      }
    }
    if (s.forward < 1) {
      if (s.forward < 0) {
        s.forward = signed_word(std::uint32_t(s.forward + 1));
        out.z = signed_word(std::uint32_t(1));
        random_value = random.next();
        if ((((int)(random_value % 400) < (int)((uint)(c.command != '\x05') * -2 + 3)) &&
            (s.jump < 1)) && (out.dash == 0)) {
          out.dash = signed_word(std::uint32_t(2));
        }
      }
      else {
        distance = (float10)c.distance_squared;
        if ((float10)250000.0 * (float10)range_scale * (float10)range_scale <= distance) {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0x3c));
        }
        else {
          random_value = random.next();
          s.forward = signed_word(std::uint32_t(random_value % 300 - 0xf0));
        }
      }
    }
    else {
      s.forward = signed_word(std::uint32_t(s.forward + -1));
      out.z = signed_word(std::uint32_t(0xffffffff));
      random_value = random.next();
      if (((random_value % 300 < ((uint)(c.command == '\x05') * 3 + 1) * 0xc) &&
          (s.jump < 1)) && (out.dash == 0)) {
        out.dash = signed_word(std::uint32_t(1));
      }
      random_value = random.next();
      if (((random_value % 300 < ((uint)(c.command == '\x05') * 4 + 1) * 0xc) &&
          (500 < c.gauge)) &&
         ((distance = (float10)c.distance_squared,
          (float10)250000.0 * (float10)range_scale * (float10)range_scale < distance &&
          ((s.jump < 1 && (out.dash == 0)))))) {
        out.dash = signed_word(std::uint32_t(1));
      }
    }
    if (0 < s.jump) {
      out.held[0] = signed_word(std::uint32_t(3));
      if (c.grounded == '\0') {
        out.held[0] = signed_word(std::uint32_t(4));
      }
      s.jump = signed_word(std::uint32_t(s.jump + -1));
    }
    if (((c.grounded != '\0') && (c.action != 0x28)) &&
       (c.action != 0x29)) {
      s.jump = signed_word(std::uint32_t(0));
    }
    distance = (float10)c.distance_squared;
    if ((distance < (float10)490000.0) && (random_value = random.next(), random_value % 100 < melee_chance)) {
      random_value = random.next();
      if (((random_value % 0x9c4 == 0) ||
          ((random_value = random.next(), random_value % 0x4e2 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.released[1] = signed_word(std::uint32_t(1));
        out.released[2] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        out.held[2] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x1e == 0) ||
          ((random_value = random.next(), random_value % 0x14 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)490000.0)) {
        out.z = signed_word(std::uint32_t(0));
        out.x = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)40000.0)) {
        out.z = signed_word(std::uint32_t(0xffffffff));
        out.x = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        return;
      }
      random_value = random.next();
      if (((random_value % 0x32 == 0) ||
          ((random_value = random.next(), random_value % 0x19 == 0 && (c.command == '\x01'))))
         && (distance = (float10)c.distance_squared, distance < (float10)250000.0)) {
        out.x = signed_word(std::uint32_t(1));
        out.z = signed_word(std::uint32_t(0));
        out.released[1] = signed_word(std::uint32_t(1));
        out.held[1] = signed_word(std::uint32_t(1));
        return;
      }
    }
    shoot_roll = random.next();
    random_value = shoot_roll / 100;
    if (shoot_roll % 100 < shooting_chance) {
      random_value = random.next();
      if (random_value % 100 != 0) {
        random_value = random.next();
        if (random_value % 0x4b != 0) {
          return;
        }
        if ((int)c.command != 2) {
          return;
        }
      }
      comparison = (float10)c.distance_squared;
      distance = (float10)1000000.0;
      random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 | (ushort)(is_nan(comparison) || is_nan(distance)) << 10
                            | (ushort)(comparison == distance) << 0xe);
      if (comparison < distance) {
        distance = (float10)c.distance_squared;
        comparison = (float10)c.obstacle_distance * (float10)c.obstacle_distance;
        random_value = (uint)(ushort)((ushort)(comparison < distance) << 8 |
                               (ushort)(is_nan(comparison) || is_nan(distance)) << 10 |
                              (ushort)(comparison == distance) << 0xe);
        if (comparison >= distance && (comparison == distance) == 0) {
          out.released[2] = signed_word(std::uint32_t(1));
          s.charge = signed_word(std::uint32_t(0));
          random_value = 0u;
        }
      }
    }
  }
  return;
}
} // namespace roster_cpu_detail
template<class Random> void advance_roster_cpu(unsigned character,KeiichiCpuState& s,KeiichiCpuInput& out,const RosterCpuContext& c,Random& random){
 character_action_dispatch(character,c.weapon);
 if(character==1){advance_mion_cpu(s,out,c,random);return;}
 if(character==2){advance_keiichi_cpu(s,out,c,random);return;}
 switch(character*3+c.weapon){
 case 0:roster_cpu_detail::advance_rena_0(s,out,c,random);return;
 case 1:roster_cpu_detail::advance_rena_1(s,out,c,random);return;
 case 2:roster_cpu_detail::advance_rena_0(s,out,c,random);return;
 case 9:roster_cpu_detail::advance_satoko_0(s,out,c,random);return;
 case 10:roster_cpu_detail::advance_satoko_1(s,out,c,random);return;
 case 11:roster_cpu_detail::advance_satoko_0(s,out,c,random);return;
 case 12:roster_cpu_detail::advance_rika_0(s,out,c,random);return;
 case 13:roster_cpu_detail::advance_rika_1(s,out,c,random);return;
 case 14:roster_cpu_detail::advance_rika_0(s,out,c,random);return;
 case 15:roster_cpu_detail::advance_shion_0(s,out,c,random);return;
 case 16:roster_cpu_detail::advance_shion_1(s,out,c,random);return;
 case 17:roster_cpu_detail::advance_shion_0(s,out,c,random);return;
 case 18:roster_cpu_detail::advance_tomitake_0(s,out,c,random);return;
 case 19:roster_cpu_detail::advance_tomitake_1(s,out,c,random);return;
 case 20:roster_cpu_detail::advance_tomitake_0(s,out,c,random);return;
 case 21:roster_cpu_detail::advance_takano_0(s,out,c,random);return;
 case 22:roster_cpu_detail::advance_takano_1(s,out,c,random);return;
 case 23:roster_cpu_detail::advance_takano_0(s,out,c,random);return;
 case 24:roster_cpu_detail::advance_rena_0(s,out,c,random);return;
 case 25:roster_cpu_detail::advance_ohishi_1(s,out,c,random);return;
 case 26:roster_cpu_detail::advance_ohishi_2(s,out,c,random);return;
 case 27:roster_cpu_detail::advance_akasaka_0(s,out,c,random);return;
 case 28:roster_cpu_detail::advance_akasaka_1(s,out,c,random);return;
 case 29:roster_cpu_detail::advance_akasaka_1(s,out,c,random);return;
 case 30:roster_cpu_detail::advance_irie_0(s,out,c,random);return;
 case 31:roster_cpu_detail::advance_irie_1(s,out,c,random);return;
 case 32:roster_cpu_detail::advance_irie_0(s,out,c,random);return;
 case 33:roster_cpu_detail::advance_chie_0(s,out,c,random);return;
 case 34:roster_cpu_detail::advance_chie_1(s,out,c,random);return;
 case 35:roster_cpu_detail::advance_chie_0(s,out,c,random);return;
 case 36:roster_cpu_detail::advance_kasai_0(s,out,c,random);return;
 case 37:roster_cpu_detail::advance_kasai_1(s,out,c,random);return;
 case 38:roster_cpu_detail::advance_kasai_2(s,out,c,random);return;
 case 39:roster_cpu_detail::advance_akane_0(s,out,c,random);return;
 case 40:roster_cpu_detail::advance_akane_1(s,out,c,random);return;
 case 41:roster_cpu_detail::advance_akane_0(s,out,c,random);return;
 case 42:roster_cpu_detail::advance_rika_0(s,out,c,random);return;
 case 43:roster_cpu_detail::advance_rika_0(s,out,c,random);return;
 case 45:roster_cpu_detail::advance_rena_0(s,out,c,random);return;
 case 46:roster_cpu_detail::advance_rena_0(s,out,c,random);return;
 default:throw std::invalid_argument("Unknown roster CPU policy");
 }
}
} // namespace daybreak
