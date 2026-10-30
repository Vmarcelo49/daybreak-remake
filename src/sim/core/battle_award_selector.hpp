#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
namespace daybreak {
// Raw 0x88-byte original result-statistics record. Names/collection are separate.
// The selector normalizes floats64/68 in place. Call once per result record.
struct BattleAwardStatistics {
 std::array<std::uint32_t,34> words{};
 std::int32_t integer(unsigned offset)const{auto bits=words.at(offset/4);std::int32_t out;std::memcpy(&out,&bits,4);return out;}
 float real(unsigned offset)const{auto bits=words.at(offset/4);float out;std::memcpy(&out,&bits,4);return out;}
 void store(unsigned offset,float value){std::memcpy(&words.at(offset/4),&value,4);}
};
inline std::int32_t award_signed(std::uint32_t n){std::int32_t value;std::memcpy(&value,&n,4);return value;}
inline std::int32_t award_add(std::int32_t a,std::int32_t b){return award_signed(std::uint32_t(a)+std::uint32_t(b));}
inline std::int32_t award_multiply(std::int32_t a,std::int32_t b){return award_signed(std::uint32_t(a)*std::uint32_t(b));}
// Generated from 00430880.c; source SHA256 e9d2b7d3638bbc0655d5f01f811a5c71b24afd42a5957d001c8b23e766ad0f95
constexpr float award_006a16cc=0x1.99999a0000000p-3f;
constexpr float award_006a1984=0x1.99999a0000000p-4f;
constexpr float award_006a1c7c=0x1.0000000000000p-2f;
constexpr float award_006a24d0=0x1.0000000000000p-1f;
constexpr float award_006a27f0=0x1.99999a0000000p-5f;
constexpr double award_006a27f8=0x1.999999999999ap-5;
constexpr float award_006a2800=0x1.3333340000000p-2f;
constexpr float award_006a2804=0x1.e848000000000p+21f;
constexpr float award_006a2808=0x1.4ccccc0000000p-1f;
constexpr float award_006a280c=0x1.6666660000000p-2f;
constexpr float award_006a2810=0x1.99999a0000000p-2f;
constexpr float award_006a2814=0x1.8000000000000p-1f;
constexpr float award_006a2818=0x1.3333340000000p-3f;
template<class Random> unsigned select_battle_award(BattleAwardStatistics& s,Random& random){

  float fVar1;
  float fVar2;
  std::uint32_t uVar3;
  
  s.store(0x64, s.real(0x64) / (float)s.integer(0x7c));
  s.store(0x68, s.real(0x68) / (float)s.integer(0x7c));
  if (s.integer(0xc) < 1) {
    if (((award_multiply(s.integer(0x8), 30000)) / 100 <=
         award_add(s.integer(0x10), s.integer(0x14))) &&
       (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
       fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a24d0,
       fVar1 < fVar2 != (fVar1 == fVar2))) {
      uVar3 = random.next();
      if (uVar3 % 100 == 0) {
        return 0x28;
      }
      return 0x16;
    }
    if ((((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
          (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a1984) &&
        ((float)s.integer(0x50) <= (float)s.integer(0x28) * award_006a1984)) &&
       (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
       fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a24d0,
       fVar1 < fVar2 != (fVar1 == fVar2))) {
      uVar3 = random.next();
      if (uVar3 % 100 == 0) {
        return 0x28;
      }
      return 0x18;
    }
    if ((((award_multiply(s.integer(0x8), 20000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a24d0,
        fVar1 < fVar2 != (fVar1 == fVar2))) &&
       ((award_006a2804 <= s.real(0x64) &&
        (s.integer(0x3c) <= s.integer(0x38))))) {
      uVar3 = random.next();
      if (uVar3 % 100 == 0) {
        return 0x28;
      }
      return 0x1e;
    }
    if (14999 < s.integer(0x20)) {
      return 0x19;
    }
    if ((((award_multiply(s.integer(0x8), 25000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        ((award_multiply(s.integer(0x4), 35000)) / 100 <=
         award_add(s.integer(0x18), s.integer(0x1c)))) &&
       (s.integer(0x38) <= s.integer(0x3c))) {
      uVar3 = random.next();
      if (uVar3 % 100 < 6) {
        return 0x28;
      }
      return 0x1f;
    }
    if ((0x13 < s.integer(0x54)) &&
       (award_add(s.integer(0x18), s.integer(0x1c)) <= (award_multiply(s.integer(0x4), 15000)) / 100
       )) {
      uVar3 = random.next();
      if (uVar3 % 100 < 6) {
        return 0x28;
      }
      return 0x17;
    }
    if ((2 < s.integer(0x60)) &&
       (fVar2 = (float)(award_add(s.integer(0x4c), s.integer(0x50))),
       fVar1 = (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a2800,
       fVar1 < fVar2 != (fVar1 == fVar2))) {
      uVar3 = random.next();
      if (uVar3 % 100 < 0x10) {
        return 0x28;
      }
      return 0x15;
    }
    if (s.integer(0x60) == 0) {
      uVar3 = random.next();
      if (uVar3 % 100 < 0x33) {
        return 0x28;
      }
      return 0x14;
    }
    if (award_add(s.integer(0x2c), s.integer(0x30)) <= (award_multiply(s.integer(0x4), 0x14)) / 100)
    {
      uVar3 = random.next();
      if (uVar3 % 100 < 0x10) {
        return 0x28;
      }
      return 0x1b;
    }
    if (((award_multiply(s.integer(0x8), 25000)) / 100 <=
         award_add(s.integer(0x10), s.integer(0x14))) &&
       ((double)(award_add(s.integer(0x40), s.integer(0x44))) <=
        (double)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a27f8)) {
      uVar3 = random.next();
      if (uVar3 % 100 < 6) {
        return 0x28;
      }
      return 0x1d;
    }
    if ((0xf9 < s.integer(0x6c)) &&
       ((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
        (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a1c7c)) {
      uVar3 = random.next();
      if (uVar3 % 100 < 0x1a) {
        return 0x28;
      }
      return 0x23;
    }
    fVar1 = (float)s.integer(0x24) * award_006a24d0;
    if ((fVar1 < (float)s.integer(0x4c) != (fVar1 == (float)s.integer(0x4c))) &&
       ((float)s.integer(0x50) <= (float)s.integer(0x28) * award_006a27f0)) {
      uVar3 = random.next();
      if (uVar3 % 100 < 6) {
        return 0x28;
      }
      return 0x24;
    }
    if (((award_multiply(s.integer(0x4), 10)) / 100 <= s.integer(0x48)) &&
       (s.integer(0x20) == 0)) {
      uVar3 = random.next();
      if (uVar3 % 100 < 0xb) {
        return 0x28;
      }
      return 0x22;
    }
    fVar1 = (float)s.integer(0x7c) * award_006a2814;
    if (fVar1 < (float)s.integer(0x80) != (fVar1 == (float)s.integer(0x80))) {
      uVar3 = random.next();
      if (uVar3 % 100 < 6) {
        return 0x28;
      }
      return 0x20;
    }
    if (((((award_multiply(s.integer(0x8), 15000)) / 100 <=
           award_add(s.integer(0x10), s.integer(0x14))) &&
         (award_add(s.integer(0x18), s.integer(0x1c)) <=
          (award_multiply(s.integer(0x4), 20000)) / 100)) &&
        ((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a280c)) &&
       (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
       fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a1c7c,
       fVar1 < fVar2 != (fVar1 == fVar2))) {
      uVar3 = random.next();
      if (uVar3 % 100 < 3) {
        return 0x28;
      }
      return 0x13;
    }
    if ((((award_multiply(s.integer(0x8), 12000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (award_add(s.integer(0x18), s.integer(0x1c)) <=
         (award_multiply(s.integer(0x4), 25000)) / 100)) &&
       (((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a24d0 &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a2818,
        fVar1 < fVar2 != (fVar1 == fVar2))))) {
      uVar3 = random.next();
      if (uVar3 % 100 < 6) {
        return 0x28;
      }
      return 0x25;
    }
    fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a2814;
    if (fVar1 < (float)s.integer(0x34) != (fVar1 == (float)s.integer(0x34))) {
      uVar3 = random.next();
      if (uVar3 % 100 == 0) {
        return 0x28;
      }
      return 0x1c;
    }
    if ((((award_multiply(s.integer(0x8), 9000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (award_add(s.integer(0x18), s.integer(0x1c)) <=
         (award_multiply(s.integer(0x4), 30000)) / 100)) &&
       (((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a2808 &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a1984,
        fVar1 < fVar2 != (fVar1 == fVar2))))) {
      uVar3 = random.next();
      if (uVar3 % 100 < 0xb) {
        return 0x28;
      }
      return 0x27;
    }
  }
  else {
    if (((((award_multiply(s.integer(0x8), 35000)) / 100 <=
           award_add(s.integer(0x10), s.integer(0x14))) &&
         (award_add(s.integer(0x18), s.integer(0x1c)) <=
          (award_multiply(s.integer(0x4), 0x30d4)) / 100)) &&
        ((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a2818)) &&
       (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
       fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a24d0,
       fVar1 < fVar2 != (fVar1 == fVar2))) {
      return 6;
    }
    if ((((award_multiply(s.integer(0x8), 25000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (award_add(s.integer(0x18), s.integer(0x1c)) <=
         (award_multiply(s.integer(0x4), 25000)) / 100)) && (s.integer(0x34) == 0)) {
      return 3;
    }
    if ((((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
          (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a1984) &&
        ((float)s.integer(0x50) <= (float)s.integer(0x28) * award_006a1984)) &&
       (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
       fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a24d0,
       fVar1 < fVar2 != (fVar1 == fVar2))) {
      return 4;
    }
    if ((((award_multiply(s.integer(0x8), 30000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a2814,
        fVar1 < fVar2 != (fVar1 == fVar2))) &&
       (s.integer(0x3c) <= s.integer(0x38))) {
      return 0xd;
    }
    if ((((award_multiply(s.integer(0x8), 25000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (award_add(s.integer(0x18), s.integer(0x1c)) <=
         (award_multiply(s.integer(0x4), 0x445c)) / 100)) &&
       (((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a16cc &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a2810,
        fVar1 < fVar2 != (fVar1 == fVar2))))) {
      return 0xc;
    }
    if ((award_multiply(s.integer(0x4), 15000)) / 100 <= s.integer(0x20)) {
      return 9;
    }
    if (((award_multiply(s.integer(0x8), 40000)) / 100 <=
         award_add(s.integer(0x10), s.integer(0x14))) &&
       ((award_multiply(s.integer(0x4), 40000)) / 100 <= award_add(s.integer(0x18), s.integer(0x1c))
       )) {
      return 0x21;
    }
    if (((award_multiply(s.integer(0x8), 25000)) / 100 <=
         award_add(s.integer(0x10), s.integer(0x14))) && (0xe < s.integer(0x74))) {
      return 0xe;
    }
    if (((award_multiply(s.integer(0x8), 35000)) / 100 <=
         award_add(s.integer(0x10), s.integer(0x14))) && (1 < s.integer(0x58))) {
      return 0xb;
    }
    if ((((award_multiply(s.integer(0x8), 10000)) / 100 <= s.integer(0x14)) &&
        (s.integer(0x2c) <= s.integer(0x30))) && (1 < s.integer(0x58))) {
      return 0xf;
    }
    if ((((award_multiply(s.integer(0x8), 30000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (0x13 < award_add(s.integer(0x78), s.integer(0x74)))) &&
       (s.integer(0x3c) <= s.integer(0x38))) {
      return 5;
    }
    if ((((award_multiply(s.integer(0x8), 30000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (award_add(s.integer(0x78), s.integer(0x74)) < 0x15)) &&
       (s.integer(0x3c) <= s.integer(0x38))) {
      return 8;
    }
    if ((((award_multiply(s.integer(0x8), 30000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a1c7c,
        fVar1 < fVar2 != (fVar1 == fVar2))) &&
       (s.integer(0x38) <= s.integer(0x3c))) {
      return 2;
    }
    if (((award_add(s.integer(0x10), s.integer(0x14)) <=
          (award_multiply(s.integer(0x8), 15000)) / 100) &&
        ((award_multiply(s.integer(0x4), 35000)) / 100 <=
         award_add(s.integer(0x18), s.integer(0x1c)))) &&
       (s.integer(0x38) <= s.integer(0x3c))) {
      return 7;
    }
    if ((award_add(s.integer(0x10), s.integer(0x14)) <=
         (award_multiply(s.integer(0x8), 15000)) / 100) && (2 < s.integer(0x58))) {
      return 0x12;
    }
    if (0xe < s.integer(0x5c)) {
      return 0;
    }
    if (0x13 < s.integer(0x70)) {
      return 0x10;
    }
    if ((award_multiply(s.integer(0x4), 200)) / 100 <= s.integer(0x24)) {
      return 1;
    }
    if (((award_multiply(s.integer(0x4), 0x14)) / 100 <= s.integer(0x54)) &&
       (award_add(s.integer(0x18), s.integer(0x1c)) <= (award_multiply(s.integer(0x4), 15000)) / 100
       )) {
      return 0x11;
    }
    if (((award_multiply(s.integer(0x4), 10)) / 100 <= s.integer(0x48)) &&
       (s.integer(0x20) == 0)) {
      return 0x22;
    }
    if (((((award_multiply(s.integer(0x8), 15000)) / 100 <=
           award_add(s.integer(0x10), s.integer(0x14))) &&
         (award_add(s.integer(0x18), s.integer(0x1c)) <=
          (award_multiply(s.integer(0x4), 20000)) / 100)) &&
        ((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a280c)) &&
       (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
       fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a1c7c,
       fVar1 < fVar2 != (fVar1 == fVar2))) {
      return 0x13;
    }
    if ((((award_multiply(s.integer(0x8), 12000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (award_add(s.integer(0x18), s.integer(0x1c)) <=
         (award_multiply(s.integer(0x4), 25000)) / 100)) &&
       (((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a24d0 &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a2818,
        fVar1 < fVar2 != (fVar1 == fVar2))))) {
      return 0x25;
    }
    fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a2814;
    if (fVar1 < (float)s.integer(0x34) != (fVar1 == (float)s.integer(0x34))) {
      return 10;
    }
    if ((((award_multiply(s.integer(0x8), 9000)) / 100 <=
          award_add(s.integer(0x10), s.integer(0x14))) &&
        (award_add(s.integer(0x18), s.integer(0x1c)) <=
         (award_multiply(s.integer(0x4), 30000)) / 100)) &&
       (((float)(award_add(s.integer(0x4c), s.integer(0x50))) <=
         (float)(award_add(s.integer(0x24), s.integer(0x28))) * award_006a2808 &&
        (fVar2 = (float)(award_add(s.integer(0x40), s.integer(0x44))),
        fVar1 = (float)(award_add(s.integer(0x2c), s.integer(0x30))) * award_006a1984,
        fVar1 < fVar2 != (fVar1 == fVar2))))) {
      return 0x27;
    }
  }
  return 0x1a;

}
}
