// Original-source Ohishi rank/release bodies. Closed remaining bodies unchanged.
#pragma once
#include "remaining_melee_native_control.hpp"
namespace daybreak {
struct OhishiRankedContext : RemainingMeleeContext {
 using RemainingMeleeContext::RemainingMeleeContext;
 void FUN_004212f0(){RemainingMeleeContext::FUN_004212f0();emit('I',0x4212f0,w[0xadec/4],w[0xadf4/4],w[0xae04/4],w[0xae08/4]);}
};
inline void slot7_ranked_body_8_1_305(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_84;
  int local_80;
  float local_7c;
  int local_68;
  int local_64;
  float local_60;
  int local_54;
  int local_50;
  float local_4c;
  int local_38;
  int local_34;
  float local_30;
  float local_20;
  float local_18;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, 1);
          n.w[0x15] = 0x41600000;
          n.FUN_0042db10(0, 0x43340000);
          fVar5 = (float10) n.FUN_0042d980();
          if (fVar5 < ((float10) remaining_real(0x491c4000u)))
          {
            n.write_scratch(0x3c, 1);
            n.w[0x15] = 0x41a00000;
          }
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x3c] == 1))
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b7d] == 1)
        {
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x41700000);
          }
          fVar5 = (float10) n.FUN_0042d980();
          if ((fVar5 < ((float10) remaining_real(0x47afc800u))) || (n.w[0x3c] == 0))
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if ((n.w[0x2b81] < 9) && (n.w[0x3c] == 1))
          {
            n.FUN_0042db10(0, 0x41200000);
          }
          if (n.w[0x2b81] == 9)
          {
            n.FUN_0042c880(0x3d);
            fVar5 = (float10) n.FUN_0042d980();
            if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaec3)) != '\x01'))
            {
              fVar5 = (float10) n.FUN_0042d980();
              if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaebe)) != '\x01'))
              {
                fVar5 = (float10) n.FUN_0042d980();
                if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaeb9)) != '\x01'))
                {
                  n.FUN_004223d0(1, 10, 0);
                }
                else
                {
                  n.FUN_004223d0(5, 0xc, 0);
                }
              }
              else
              {
                n.FUN_004223d0(0xf, 0xc, 0);
              }
            }
            else
            {
              n.FUN_004223d0(0, 0xc, 0);
            }
          }
          if (n.w[0x2b81] == 10)
          {
            n.w[0x15] = 0;
          }
        }
        break;
      }
      while (0);
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void slot7_ranked_body_8_1_335(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_84;
  int local_80;
  float local_7c;
  int local_68;
  int local_64;
  float local_60;
  int local_54;
  int local_50;
  float local_4c;
  int local_38;
  int local_34;
  float local_30;
  float local_20;
  float local_18;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.w[0x19] = n.w[0x18];
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3c, 0);
        n.w[0x15] = 0x418c0000;
        fVar5 = (float10) n.FUN_0042d980();
        if (fVar5 < ((float10) remaining_real(0x48ef4200u)))
        {
          n.write_scratch(0x3c, 1);
        }
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if ((n.w[0x2b7d] < 2) && (n.w[0x3c] == 1))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if (((n.w[0x2b7d] == 1) && (2 < n.w[0x2b81])) && ((fVar5 = (float10) n.FUN_0042d980(), (fVar5 < ((float10) remaining_real(0x476a6000u))) || ((0x14 < n.w[0x2b81]) || (n.w[0x3c] == 0)))))
      {
        n.FUN_00421100(2);
        return;
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 9))
      {
        n.FUN_004223d0(3, 10, 0);
      }
      if ((1 < n.w[0x2b7d]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3e99999au))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void slot7_ranked_body_8_1_393(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_84;
  int local_80;
  float local_7c;
  int local_68;
  int local_64;
  float local_60;
  int local_54;
  int local_50;
  float local_4c;
  int local_38;
  int local_34;
  float local_30;
  float local_20;
  float local_18;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        if (((char) n.w[0x21]) == '\0')
        {
          n.w[0x16] = 0x3f000000;
          n.FUN_00421080(0x2b);
          return;
        }
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.w[0x16] = 0x3f000000;
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.w[0x15] = -0x3e900000;
        n.write_scratch(0x3a, 0);
      }
      if ((n.w[0x2b7d] == 0) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 10 < n.w[0x3a])))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(8, 10, 0);
      }
      if (n.w[0x2b7d] < 2)
      {
        n.w[0x21d] = 0;
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f800000u)));
        if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0;
        }
      }
      break;
    }
    while (0);
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void slot7_ranked_body_8_1_394(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_84;
  int local_80;
  float local_7c;
  int local_68;
  int local_64;
  float local_60;
  int local_54;
  int local_50;
  float local_4c;
  int local_38;
  int local_34;
  float local_30;
  float local_20;
  float local_18;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        if (((char) n.w[0x21]) == '\0')
        {
          n.w[0x16] = 0x3f000000;
          n.FUN_00421080(0x2b);
          return;
        }
        n.FUN_00421080(0);
        n.w[0x10] = 0;
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.FUN_00421080(0x2c);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.w[0x15] = -0x3e900000;
        n.w[0x10] = 0x40a00000;
        n.w[0x16] = 0x3f000000;
        n.write_scratch(0x3a, 0);
      }
      if ((n.w[0x2b7d] == 0) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 10 < n.w[0x3a])))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(8, 10, 0);
      }
      if (n.w[0x2b7d] < 2)
      {
        n.w[0x21d] = 0;
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f800000u)));
        if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0;
        }
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
      break;
    }
    while (0);
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void slot7_ranked_body_8_2_305(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  undefined4 uVar9;
  int local_28;
  int local_24;
  float local_20;
  int local_14;
  int local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  if (n.w[0x2bd8] == 1)
  {
    n.FUN_00434a70(0, 2);
  }
  if (n.w[0x2bd8] == 2)
  {
    n.FUN_00434a70(0, 3);
  }
  if (n.w[0x2bd8] == 3)
  {
    n.FUN_00434a70(0, 4);
  }
  if (n.w[0x2bd8] == 4)
  {
    n.FUN_00434a70(0, 5);
  }
  if (n.w[0x2bd8] == 5)
  {
    n.FUN_00434a70(0, 6);
  }
  if (n.w[0x2bd8] == 6)
  {
    n.FUN_00434a70(0, 7);
  }
  if (n.w[0x2bd8] == 7)
  {
    n.FUN_00434a70(0, 8);
  }
  if (n.w[0x2bd8] == 8)
  {
    n.FUN_00434a70(0, 9);
  }
  if (n.w[0x2bd8] == 9)
  {
    n.FUN_00434a70(0, 10);
  }
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, 1);
          n.w[0x15] = 0x41600000;
          n.FUN_0042db10(0, 0x43340000);
          fVar5 = (float10) n.FUN_0042d980();
          if (fVar5 < ((float10) remaining_real(0x491c4000u)))
          {
            n.write_scratch(0x3c, 1);
            n.w[0x15] = 0x41a00000;
          }
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x3c] == 1))
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b7d] == 1)
        {
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x41700000);
          }
          fVar5 = (float10) n.FUN_0042d980();
          if ((fVar5 < ((float10) remaining_real(0x47afc800u))) || (n.w[0x3c] == 0))
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if ((n.w[0x2b81] < 9) && (n.w[0x3c] == 1))
          {
            n.FUN_0042db10(0, 0x41200000);
          }
          if (n.w[0x2b81] == 9)
          {
            n.FUN_0042c880(0x3d);
            fVar5 = (float10) n.FUN_0042d980();
            if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaec3)) != '\x01'))
            {
              fVar5 = (float10) n.FUN_0042d980();
              if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaebe)) != '\x01'))
              {
                fVar5 = (float10) n.FUN_0042d980();
                if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaeb9)) != '\x01'))
                {
                  n.FUN_004223d0(1, 10, 0);
                }
                else
                {
                  n.FUN_004223d0(5, 0xc, 0);
                }
              }
              else
              {
                n.FUN_004223d0(0xf, 0xc, 0);
              }
            }
            else
            {
              n.FUN_004223d0(0, 0xc, 0);
            }
          }
          if (n.w[0x2b81] == 10)
          {
            n.w[0x15] = 0;
          }
        }
        break;
      }
      while (0);
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void slot7_ranked_body_8_2_306(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  undefined4 uVar9;
  int local_28;
  int local_24;
  float local_20;
  int local_14;
  int local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  if (n.w[0x2bd8] == 1)
  {
    n.FUN_00434a70(0, 2);
  }
  if (n.w[0x2bd8] == 2)
  {
    n.FUN_00434a70(0, 3);
  }
  if (n.w[0x2bd8] == 3)
  {
    n.FUN_00434a70(0, 4);
  }
  if (n.w[0x2bd8] == 4)
  {
    n.FUN_00434a70(0, 5);
  }
  if (n.w[0x2bd8] == 5)
  {
    n.FUN_00434a70(0, 6);
  }
  if (n.w[0x2bd8] == 6)
  {
    n.FUN_00434a70(0, 7);
  }
  if (n.w[0x2bd8] == 7)
  {
    n.FUN_00434a70(0, 8);
  }
  if (n.w[0x2bd8] == 8)
  {
    n.FUN_00434a70(0, 9);
  }
  if (n.w[0x2bd8] == 9)
  {
    n.FUN_00434a70(0, 10);
  }
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, 1);
          n.w[0x15] = 0x41600000;
          n.FUN_0042db10(0, 0x43340000);
          fVar5 = (float10) n.FUN_0042d980();
          if (fVar5 < ((float10) remaining_real(0x491c4000u)))
          {
            n.write_scratch(0x3c, 1);
            n.w[0x15] = 0x41a00000;
          }
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        sVar2 = n.FUN_0042c7b0();
        if (sVar2 != 0)
        {
          n.w[0x2bd8] = 0;
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x3c] == 1))
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b7d] == 1)
        {
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x41700000);
          }
          fVar5 = (float10) n.FUN_0042d980();
          if ((fVar5 < ((float10) remaining_real(0x47afc800u))) || (n.w[0x3c] == 0))
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if ((n.w[0x2b81] < 9) && (n.w[0x3c] == 1))
          {
            n.FUN_0042db10(0, 0x41200000);
          }
          if (n.w[0x2b81] == 9)
          {
            n.FUN_0042c880(0x3d);
            fVar5 = (float10) n.FUN_0042d980();
            if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaec3)) != '\x01'))
            {
              fVar5 = (float10) n.FUN_0042d980();
              if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaebe)) != '\x01'))
              {
                fVar5 = (float10) n.FUN_0042d980();
                if (((((float10) remaining_real(0x47afc800u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaeb9)) != '\x01'))
                {
                  n.FUN_004223d0(1, 10, 0);
                }
                else
                {
                  n.FUN_004223d0(5, 0xc, 0);
                }
              }
              else
              {
                n.FUN_004223d0(0xf, 0xc, 0);
              }
            }
            else
            {
              n.FUN_004223d0(0, 0xc, 0);
            }
          }
          if (n.w[0x2b81] == 10)
          {
            n.w[0x15] = 0;
          }
        }
        break;
      }
      while (0);
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void slot7_ranked_body_8_2_393(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  undefined4 uVar9;
  int local_28;
  int local_24;
  float local_20;
  int local_14;
  int local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  if (n.w[0x2bd8] == 1)
  {
    n.FUN_00434a70(0, 2);
  }
  if (n.w[0x2bd8] == 2)
  {
    n.FUN_00434a70(0, 3);
  }
  if (n.w[0x2bd8] == 3)
  {
    n.FUN_00434a70(0, 4);
  }
  if (n.w[0x2bd8] == 4)
  {
    n.FUN_00434a70(0, 5);
  }
  if (n.w[0x2bd8] == 5)
  {
    n.FUN_00434a70(0, 6);
  }
  if (n.w[0x2bd8] == 6)
  {
    n.FUN_00434a70(0, 7);
  }
  if (n.w[0x2bd8] == 7)
  {
    n.FUN_00434a70(0, 8);
  }
  if (n.w[0x2bd8] == 8)
  {
    n.FUN_00434a70(0, 9);
  }
  if (n.w[0x2bd8] == 9)
  {
    n.FUN_00434a70(0, 10);
  }
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        if (((char) n.w[0x21]) == '\0')
        {
          n.w[0x16] = 0x3f000000;
          n.FUN_00421080(0x2b);
          return;
        }
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.w[0x16] = 0x3f000000;
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.w[0x15] = -0x3e900000;
        n.write_scratch(0x3a, 0);
      }
      if ((n.w[0x2b7d] == 0) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 10 < n.w[0x3a])))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(8, 10, 0);
      }
      if (n.w[0x2b7d] < 2)
      {
        n.w[0x21d] = 0;
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f800000u)));
        if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0;
        }
      }
      break;
    }
    while (0);
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void slot7_ranked_body_8_2_394(OhishiRankedContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float fVar8;
  undefined4 uVar9;
  int local_28;
  int local_24;
  float local_20;
  int local_14;
  int local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  if (n.w[0x2bd8] == 1)
  {
    n.FUN_00434a70(0, 2);
  }
  if (n.w[0x2bd8] == 2)
  {
    n.FUN_00434a70(0, 3);
  }
  if (n.w[0x2bd8] == 3)
  {
    n.FUN_00434a70(0, 4);
  }
  if (n.w[0x2bd8] == 4)
  {
    n.FUN_00434a70(0, 5);
  }
  if (n.w[0x2bd8] == 5)
  {
    n.FUN_00434a70(0, 6);
  }
  if (n.w[0x2bd8] == 6)
  {
    n.FUN_00434a70(0, 7);
  }
  if (n.w[0x2bd8] == 7)
  {
    n.FUN_00434a70(0, 8);
  }
  if (n.w[0x2bd8] == 8)
  {
    n.FUN_00434a70(0, 9);
  }
  if (n.w[0x2bd8] == 9)
  {
    n.FUN_00434a70(0, 10);
  }
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        if (((char) n.w[0x21]) == '\0')
        {
          n.w[0x16] = 0x3f000000;
          n.FUN_00421080(0x2b);
          return;
        }
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.w[0x16] = 0x3f000000;
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.w[0x15] = -0x3e900000;
        n.w[0x10] = 0x40a00000;
        n.w[0x16] = 0x3f000000;
        n.write_scratch(0x3a, 0);
      }
      if ((n.w[0x2b7d] == 0) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 10 < n.w[0x3a])))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(8, 10, 0);
      }
      if (n.w[0x2b7d] < 2)
      {
        n.w[0x21d] = 0;
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f800000u)));
        if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0;
        }
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
      break;
    }
    while (0);
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline bool slot7_ranked_body_binding(unsigned ch,unsigned we,unsigned state){return ch==8&&((we==1&&state==305)||(we==1&&state==335)||(we==1&&state==393)||(we==1&&state==394)||(we==2&&state==305)||(we==2&&state==306)||(we==2&&state==393)||(we==2&&state==394));}
inline void dispatch_slot7_ranked_body(OhishiRankedContext& n,unsigned ch,unsigned we,unsigned state){if(ch!=8)throw std::invalid_argument("Invalid ranked actor");switch(we*1000+state){
case 1305:slot7_ranked_body_8_1_305(n);return;
case 1335:slot7_ranked_body_8_1_335(n);return;
case 1393:slot7_ranked_body_8_1_393(n);return;
case 1394:slot7_ranked_body_8_1_394(n);return;
case 2305:slot7_ranked_body_8_2_305(n);return;
case 2306:slot7_ranked_body_8_2_306(n);return;
case 2393:slot7_ranked_body_8_2_393(n);return;
case 2394:slot7_ranked_body_8_2_394(n);return;
default:throw std::invalid_argument("No ranked body binding");}}
inline RemainingMeleeNativeEffects advance_slot7_ranked_control(RosterNativeScratch& scratch,
 RemainingMeleeNativeMotion& m,const RemainingMeleeNativeInput& in){
 OhishiRankedContext n(in);n.contact=in.contact;
 for(unsigned i=0;i<3;++i){const unsigned offset=std::array<unsigned,3>{0xaec3,0xaebe,0xaeb9}[i];auto& word=n.w[offset/4];word=int((unsigned(word)&~(255u<<((offset%4)*8)))|(unsigned(in.voice_flags[i])<<((offset%4)*8)));}
 const auto real=[&](unsigned offset,float value){n.w.at(offset/4)=remaining_bits(value);};
 for(const auto pair:{std::pair<unsigned,float>{0x54,m.speed},{0x64,m.offset},{0x60,m.movement},{0x40,m.vertical},{0x58,m.gravity},{0x874,m.turn},{0x2c,m.pitch},{0x2d8,m.pivot},{0x30,m.yaw},{0x34,m.orientation34},{0x5c,in.heading}})real(pair.first,pair.second);
 for(unsigned axis=0;axis<3;++axis)real(0x14+axis*4,in.origin[axis]);
 for(const auto pair:{std::pair<unsigned,int>{0xe8,scratch.e8},{0xec,scratch.ec},{0xf0,scratch.f0},{0xf4,scratch.f4},{0xf8,scratch.f8},{0x684,m.contact_mode},{0xaf60,m.rank},{0xaf64,m.rank_timer},{0xaf68,m.mine_clock},{0x7ac,m.invincible},{0x830,in.direction},{0x834,m.gauge},{0x7f4,in.slow},{0x280,int(in.jump)},{0x284,int(in.held)},{0x2b4,int(in.released)},{0xadec,int(in.state)},{0xadf4,int(in.phase)},{0xae04,int(in.frame)},{0xae08,int(in.tick2)},{0x84,in.grounded?1:0},{0xa0,in.blocked?1:0}})n.w.at(pair.first/4)=pair.second;
 dispatch_slot7_ranked_body(n,in.character,in.weapon,in.state);
 const auto read=[&](unsigned offset){return remaining_real(unsigned(n.w.at(offset/4)));};
 m.speed=read(0x54);m.offset=read(0x64);m.movement=read(0x60);m.vertical=read(0x40);m.gravity=read(0x58);m.turn=read(0x874);m.pitch=read(0x2c);m.pivot=read(0x2d8);m.yaw=read(0x30);m.orientation34=read(0x34);
 m.contact_mode=n.w[0x684/4];m.gauge=n.w[0x834/4];m.rank=n.w[0xaf60/4];m.rank_timer=n.w[0xaf64/4];m.mine_clock=n.w[0xaf68/4];m.invincible=n.w[0x7ac/4];
 scratch.e8=n.w[0xe8/4];scratch.ec=n.w[0xec/4];scratch.f0=n.w[0xf0/4];scratch.f4=n.w[0xf4/4];scratch.f8=n.w[0xf8/4];scratch.known|=n.scratch_written;
 n.out.frame=n.w[0xae04/4];n.out.tick2=n.w[0xae08/4];n.out.phase=n.w[0xadf4/4];return n.out;
}
}
