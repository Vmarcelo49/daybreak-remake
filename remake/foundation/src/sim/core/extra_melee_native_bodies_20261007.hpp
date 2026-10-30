// Original slot6 extra melee control trees. Regenerate via tools/generate_extra_melee_native_20261007.py.
#pragma once
inline void extra_melee_body_8_2_307(RemainingMeleeContext& n)
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

inline void extra_melee_body_8_2_337(RemainingMeleeContext& n)
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0x41840000;
          n.write_scratch(0x3e, 0);
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
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40a00000);
          fVar5 = (float10) n.FUN_0042d980();
          if ((fVar5 < ((float10) remaining_real(0x47afc800u))) && (2 < n.w[0x2b81]))
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if (n.w[0x2b81] == 0)
          {
            n.w[0x15] = 0x41b40000;
          }
          if (10 < n.w[0x2b81])
          {
            n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u)));
          }
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (n.w[0x2b81] == 4)
          {
            fVar5 = (float10) n.FUN_0042d980();
            if (((((float10) remaining_real(0x471c4000u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaec3)) != '\x01'))
            {
              fVar5 = (float10) n.FUN_0042d980();
              if (((((float10) remaining_real(0x471c4000u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaebe)) != '\x01'))
              {
                fVar5 = (float10) n.FUN_0042d980();
                if (((((float10) remaining_real(0x471c4000u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaeb9)) != '\x01'))
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
        }
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

inline void extra_melee_body_8_2_338(RemainingMeleeContext& n)
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0x41840000;
          n.write_scratch(0x3e, 0);
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
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40a00000);
          fVar5 = (float10) n.FUN_0042d980();
          if ((fVar5 < ((float10) remaining_real(0x47afc800u))) && (2 < n.w[0x2b81]))
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if (n.w[0x2b81] == 0)
          {
            n.w[0x15] = 0x41b40000;
          }
          if (10 < n.w[0x2b81])
          {
            n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u)));
          }
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (n.w[0x2b81] == 4)
          {
            fVar5 = (float10) n.FUN_0042d980();
            if (((((float10) remaining_real(0x471c4000u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaec3)) != '\x01'))
            {
              fVar5 = (float10) n.FUN_0042d980();
              if (((((float10) remaining_real(0x471c4000u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaebe)) != '\x01'))
              {
                fVar5 = (float10) n.FUN_0042d980();
                if (((((float10) remaining_real(0x471c4000u)) <= fVar5) || ((fVar5 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar5))) || ((n.byte(0xaeb9)) != '\x01'))
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
        }
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

inline void extra_melee_body_8_2_342(RemainingMeleeContext& n)
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
        n.write_scratch(0x3e, 0);
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

inline void extra_melee_body_8_2_343(RemainingMeleeContext& n)
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
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x418c0000;
        fVar5 = (float10) n.FUN_0042d980();
        if (fVar5 < ((float10) remaining_real(0x48ef4200u)))
        {
          n.write_scratch(0x3c, 1);
        }
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

inline void extra_melee_body_8_2_344(RemainingMeleeContext& n)
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
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x418c0000;
        fVar5 = (float10) n.FUN_0042d980();
        if (fVar5 < ((float10) remaining_real(0x48ef4200u)))
        {
          n.write_scratch(0x3c, 1);
        }
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

inline void extra_melee_body_9_0_342(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  undefined4 uVar12;
  int local_20;
  int local_1c;
  float local_18;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 4)) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b81] < 5) && (n.w[0x2b7d] == 0))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] == 3) && (n.w[0x2b7d] == 0))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0x42340000;
        n.w[0x16] = 0x3fc00000;
        n.w[0x21d] = 0;
      }
      if (remaining_real(0x00000000u) < (remaining_real(n.w[0x10])))
      {
        n.w[0x1eb] = 3;
      }
      if ((((n.w[0x2b7d] != 4) && (n.w[0x2b7d] != 0)) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(4);
        return;
      }
      if ((n.w[0x2b7d] == 1) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.FUN_00421100(2);
        return;
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

inline void extra_melee_body_9_1_342(RemainingMeleeContext& n)
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
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  int local_2c;
  int local_28;
  float local_24;
  float local_18;
  float local_14;
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
        n.FUN_00421080(0);
        return;
      }
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 4)) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b81] < 5) && (n.w[0x2b7d] == 0))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] == 3) && (n.w[0x2b7d] == 0))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0x42340000;
        n.w[0x16] = 0x3fc00000;
        n.w[0x21d] = 0;
      }
      if (remaining_real(0x00000000u) < (remaining_real(n.w[0x10])))
      {
        n.w[0x1eb] = 3;
      }
      if ((((n.w[0x2b7d] != 4) && (n.w[0x2b7d] != 0)) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(4);
        return;
      }
      if ((n.w[0x2b7d] == 1) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.FUN_00421100(2);
        return;
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

inline void extra_melee_body_9_2_342(RemainingMeleeContext& n)
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
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_34;
  int local_30;
  float local_2c;
  float local_20;
  float local_1c;
  float local_14;
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
        n.FUN_00421080(0);
        return;
      }
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 4)) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b81] < 5) && (n.w[0x2b7d] == 0))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] == 3) && (n.w[0x2b7d] == 0))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0x42340000;
        n.w[0x16] = 0x3fc00000;
        n.w[0x21d] = 0;
      }
      if (remaining_real(0x00000000u) < (remaining_real(n.w[0x10])))
      {
        n.w[0x1eb] = 3;
      }
      if ((((n.w[0x2b7d] != 4) && (n.w[0x2b7d] != 0)) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(4);
        return;
      }
      if ((n.w[0x2b7d] == 1) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.FUN_00421100(2);
        return;
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

inline void extra_melee_body_13_0_342(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_34;
  int local_30;
  float local_2c;
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
      n.FUN_00434a70(0, 2);
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if (n.w[0x2b81] < 0x22)
      {
        n.w[0x1a1] = 2;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 0xe)
      {
        n.w[0x15] = 0x41f00000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(3, 10, 0);
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.w[0x15] = 0;
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

inline void extra_melee_body_13_1_342(RemainingMeleeContext& n)
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
  undefined4 uVar11;
  int local_3c;
  int local_38;
  float local_34;
  float local_14;
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
      n.FUN_00434a70(0, 2);
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if (n.w[0x2b81] < 0x22)
      {
        n.w[0x1a1] = 2;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 0xe)
      {
        n.w[0x15] = 0x41f00000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(3, 10, 0);
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.w[0x15] = 0;
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

inline void extra_melee_body_13_2_342(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_34;
  int local_30;
  float local_2c;
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
      n.FUN_00434a70(0, 2);
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if (n.w[0x2b81] < 0x22)
      {
        n.w[0x1a1] = 2;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 0xe)
      {
        n.w[0x15] = 0x41f00000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(3, 10, 0);
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.w[0x15] = 0;
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

inline void extra_melee_body_14_1_303(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_20;
  int local_1c;
  float local_18;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  if ((((n.byte(0x845)) == '\0') && (((char) n.w[0x211]) == '\0')) && ((n.byte(0x846)) == '\0'))
  {
    n.FUN_00434a70(0, 0);
    n.FUN_00434a70(1, 1);
  }
  else
  {
    n.FUN_00434a70(0, 2);
  }
  n.FUN_00434bd0();
  if ((((n.byte(0x845)) != '\0') || (((char) n.w[0x211]) != '\0')) || ((n.byte(0x846)) != '\0'))
  {
    n.FUN_00434b30();
  }
  iVar5 = n.w[0x2b7b];
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
        if ((n.w[0x3b] != 0) && ((n.w[0x1a1] = 2, n.w[0x2b81] < 8)))
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        n.FUN_00434a70(0, 2);
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.w[0x15] = 0;
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
        if (n.w[0x2b81] == 8)
        {
          n.FUN_0042c8b0(0x3e);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] == 7)
        {
          n.w[0x15] = 0x420c0000;
          n.w[0x21d] = 0;
        }
        if (0xc < n.w[0x2b81])
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40a00000u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          n.w[0x21d] = 0;
        }
        if ((n.w[0x2b81] < 7) || (0xe < n.w[0x2b81]))
        {
          n.FUN_00434bd0();
        }
        else
        {
          n.FUN_00434b30();
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

inline void extra_melee_body_14_1_304(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_20;
  int local_1c;
  float local_18;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  if ((((n.byte(0x845)) == '\0') && (((char) n.w[0x211]) == '\0')) && ((n.byte(0x846)) == '\0'))
  {
    n.FUN_00434a70(0, 0);
    n.FUN_00434a70(1, 1);
  }
  else
  {
    n.FUN_00434a70(0, 2);
  }
  n.FUN_00434bd0();
  if ((((n.byte(0x845)) != '\0') || (((char) n.w[0x211]) != '\0')) || ((n.byte(0x846)) != '\0'))
  {
    n.FUN_00434b30();
  }
  iVar5 = n.w[0x2b7b];
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
        if ((n.w[0x3b] != 0) && ((n.w[0x1a1] = 2, n.w[0x2b81] < 0x10)))
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        n.FUN_00434a70(0, 2);
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.w[0x15] = 0;
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
        if (n.w[0x2b81] == 0x15)
        {
          n.FUN_0042c8b0(0x3e);
          n.FUN_004223d0(3, 10, 0);
        }
        if (n.w[0x2b81] == 7)
        {
          n.w[0x15] = 0x420c0000;
          n.w[0x21d] = 0;
        }
        if (0xf < n.w[0x2b81])
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40c00000u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          n.w[0x21d] = 0;
        }
        if ((n.w[0x2b81] < 7) || (0x13 < n.w[0x2b81]))
        {
          n.FUN_00434bd0();
        }
        else
        {
          n.FUN_00434b30();
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

inline void extra_melee_body_14_1_335(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_20;
  int local_1c;
  float local_18;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  if ((((n.byte(0x845)) == '\0') && (((char) n.w[0x211]) == '\0')) && ((n.byte(0x846)) == '\0'))
  {
    n.FUN_00434a70(0, 0);
    n.FUN_00434a70(1, 1);
  }
  else
  {
    n.FUN_00434a70(0, 2);
  }
  n.FUN_00434bd0();
  if ((((n.byte(0x845)) != '\0') || (((char) n.w[0x211]) != '\0')) || ((n.byte(0x846)) != '\0'))
  {
    n.FUN_00434b30();
  }
  iVar5 = n.w[0x2b7b];
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
        n.FUN_00434a70(0, 2);
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0x41f00000;
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
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
        if ((n.w[0x2b7d] == 1) && ((fVar6 = (float10) n.FUN_0042d980(), (fVar6 < ((float10) remaining_real(0x471c4000u))) || (5 < n.w[0x2b81]))))
        {
          n.FUN_00421100(2);
          return;
        }
        if (n.w[0x2b7d] < 2)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 9))
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b7d] == 2)
        {
          if ((9 < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40000000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (n.w[0x2b81] == 9)
          {
            n.FUN_0042c8b0(0x3e);
            n.FUN_004223d0(3, 10, 0);
          }
        }
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

#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
void dispatch_extra_melee_body(RemainingMeleeContext& n,unsigned ch,unsigned we,unsigned state)
#else
inline void dispatch_extra_melee_body(RemainingMeleeContext& n,unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 26307: extra_melee_body_8_2_307(n);return;
 case 26337: extra_melee_body_8_2_337(n);return;
 case 26338: extra_melee_body_8_2_338(n);return;
 case 26342: extra_melee_body_8_2_342(n);return;
 case 26343: extra_melee_body_8_2_343(n);return;
 case 26344: extra_melee_body_8_2_344(n);return;
 case 27342: extra_melee_body_9_0_342(n);return;
 case 28342: extra_melee_body_9_1_342(n);return;
 case 29342: extra_melee_body_9_2_342(n);return;
 case 39342: extra_melee_body_13_0_342(n);return;
 case 40342: extra_melee_body_13_1_342(n);return;
 case 41342: extra_melee_body_13_2_342(n);return;
 case 43303: extra_melee_body_14_1_303(n);return;
 case 43304: extra_melee_body_14_1_304(n);return;
 case 43335: extra_melee_body_14_1_335(n);return;
 default:throw std::invalid_argument("No original extra melee DAT binding");
 }}
