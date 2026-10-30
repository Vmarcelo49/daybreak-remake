// Generated from retained original control trees; see generator/provenance.
#pragma once
inline void remaining_body_0_2_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_2c;
  int local_28;
  float local_24;
  int local_18;
  int local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
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
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_0_2_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_2c;
  int local_28;
  float local_24;
  int local_18;
  int local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_0_2_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_2c;
  int local_28;
  float local_24;
  int local_18;
  int local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        return;
      }
      if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
      {
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_0_2_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_2c;
  int local_28;
  float local_24;
  int local_18;
  int local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.write_scratch(0x3b, 0);
        n.FUN_00422900();
        n.FUN_00423000();
      }
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b81] < 0x10) || (0x18 < n.w[0x2b81]))
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
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_0_0_332(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar5 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar5 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar3 = n.FUN_0042c7b0();
          if (sVar3 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_0_0_333(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_0_0_334(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        return;
      }
      if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
      {
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_0_0_340(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    do
    {
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
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
        n.write_scratch(0x3b, 0);
        n.FUN_00422900();
        n.FUN_00423000();
      }
      sVar3 = n.FUN_0042c7b0();
      if ((sVar3 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar4 = n.FUN_0042c7b0();
      if ((uVar4 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b81] < 0x10) || (0x18 < n.w[0x2b81]))
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
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_0_0_341(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    do
    {
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 3)) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5)) && ((n.w[0x15] = 0x41700000, n.w[0x3b] == 1)))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0x41200000;
        n.w[0x10] = 0x41900000;
        n.w[0x16] = 0x3f400000;
        n.w[0x21d] = 0;
        n.FUN_004223d0(3, 10, 0);
      }
      if (((0 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), n.w[0x2b7d] < 3))) && ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u))))
      {
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(3);
        return;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] < 0x14))
      {
        n.FUN_00434b30();
      }
      else
      {
        n.FUN_00434bd0();
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

inline void remaining_body_0_1_332(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_58;
  int local_54;
  float local_50;
  int local_48;
  int local_44;
  float local_40;
  int local_24;
  int local_20;
  float local_1c;
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
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar3 = n.FUN_0042c7b0();
          if (sVar3 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_0_1_333(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_58;
  int local_54;
  float local_50;
  int local_48;
  int local_44;
  float local_40;
  int local_24;
  int local_20;
  float local_1c;
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
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_0_1_334(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_58;
  int local_54;
  float local_50;
  int local_48;
  int local_44;
  float local_40;
  int local_24;
  int local_20;
  float local_1c;
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
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_0_1_340(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_58;
  int local_54;
  float local_50;
  int local_48;
  int local_44;
  float local_40;
  int local_24;
  int local_20;
  float local_1c;
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
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar5 = n.FUN_0042c7b0();
      if ((uVar5 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 0xc)
      {
        n.FUN_0042c880(0x43);
        n.FUN_004223d0(3, 10, 0);
      }
      if (n.w[0x2b81] < 8)
      {
        n.FUN_0042db10(0, 0x40c00000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41200000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b81] < 10) || (0x10 < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b30();
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

inline void remaining_body_0_1_341(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_58;
  int local_54;
  float local_50;
  int local_48;
  int local_44;
  float local_40;
  int local_24;
  int local_20;
  float local_1c;
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
      n.FUN_00428510();
      return;
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        uVar5 = n.FUN_0065d150();
        if ((uVar5 % 100) < 0x32)
        {
          n.FUN_00422490(0x20, 4, 0x14, 0);
        }
        else
        {
          n.FUN_00422490(0x20, 3, 0x14, 0);
        }
        n.FUN_0042c800(0);
        n.FUN_00422900();
      }
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
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
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u)));
      if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x10)
      {
        n.FUN_0042c8b0(0x40);
        n.FUN_00434fd0(8, 0, 0x428c0000, 0);
        n.FUN_004230e0();
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

inline void remaining_body_1_2_312(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41900000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042db10(0, 0x43340000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41840000;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if ((0xd < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40400000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
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

inline void remaining_body_1_2_332(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_2_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_1_2_334(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_1_2_340(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
        if (n.w[0x2b81] == 8)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_2_341(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((n.w[0x2b81] < 8) && (n.w[0x3b] == 1))
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_0_312(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41900000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042db10(0, 0x43340000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41840000;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if ((0xd < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40400000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
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

inline void remaining_body_1_0_332(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_0_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_1_0_334(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_1_0_340(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
        if (n.w[0x2b81] == 8)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_0_341(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((n.w[0x2b81] < 8) && (n.w[0x3b] == 1))
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_1_312(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042db10(0, 0x43340000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41900000;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if ((0xd < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40400000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
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

inline void remaining_body_1_1_332(RemainingMeleeContext& n)
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
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_1_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_1_1_334(RemainingMeleeContext& n)
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
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_1_1_340(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
        if (n.w[0x2b81] == 8)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41f00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_1_1_341(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41800000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((n.w[0x2b81] < 8) && (n.w[0x3b] == 1))
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_2_0_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar7 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar7;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar7 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar7 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_2_0_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_2_0_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_2_0_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        n.w[0x1a1] = 2;
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3b, 0);
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
        if (n.w[0x2b81] == 0xf)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 7)
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 9)
        {
          n.w[0x15] = 0x41700000;
        }
        if (n.w[0x2b81] == 0xf)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
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

inline void remaining_body_2_0_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 3)) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5))
      {
        n.w[0x15] = 0x41c80000;
        if (n.w[0x3b] == 1)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
      }
      else
      {
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40400000u)));
        if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b81] == 3)
      {
        n.FUN_004223d0(3, 10, 0);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.FUN_00434b30();
      }
      else
      {
        n.FUN_00434bd0();
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
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

inline void remaining_body_2_1_332(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
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
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar5 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar5 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar7 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar7;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar7 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar7 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_2_1_333(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
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
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_2_1_334(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
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
  iVar5 = n.w[0x2b7b];
  {
    {
      if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        return;
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_2_1_340(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
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
  iVar5 = n.w[0x2b7b];
  {
    do
    {
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3b, 0);
      }
      uVar4 = n.FUN_0042c7b0();
      if ((uVar4 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      sVar3 = n.FUN_0042c7b0();
      if ((sVar3 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 7)
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 9)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_2_1_341(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
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
  iVar5 = n.w[0x2b7b];
  {
    do
    {
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 3)) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5))
      {
        n.w[0x15] = 0x41c80000;
        if (n.w[0x3b] == 1)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
      }
      else
      {
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40400000u)));
        if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b81] == 3)
      {
        n.FUN_004223d0(3, 10, 0);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.FUN_00434b30();
      }
      else
      {
        n.FUN_00434bd0();
      }
      uVar4 = n.FUN_0042c7b0();
      if ((uVar4 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
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

inline void remaining_body_2_2_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_28;
  int local_24;
  float local_20;
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar7 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar7;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar7 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar7 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_2_2_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_28;
  int local_24;
  float local_20;
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_2_2_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_28;
  int local_24;
  float local_20;
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
    {
      if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        return;
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_2_2_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_28;
  int local_24;
  float local_20;
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3b, 0);
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
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 7)
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 9)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_2_2_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_28;
  int local_24;
  float local_20;
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
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 3)) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5))
      {
        n.w[0x15] = 0x41c80000;
        if (n.w[0x3b] == 1)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
      }
      else
      {
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40400000u)));
        if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b81] == 3)
      {
        n.FUN_004223d0(3, 10, 0);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.FUN_00434b30();
      }
      else
      {
        n.FUN_00434bd0();
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
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

inline void remaining_body_4_0_332(RemainingMeleeContext& n)
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          fVar6 = (float10) n.FUN_0042da30();
          fVar11 = remaining_real(n.w[0x15]);
          fVar8 = (float10) n.FUN_0042d980();
          fVar8 = (float10) n.FUN_0042de80((float) fVar8);
          n.w[0x10] = remaining_bits(float((float) (((float10) ((float) (fVar6 * ((float10) fVar11)))) / (fVar8 + ((float10) remaining_real(0x3f800000u))))));
          if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
          {
            local_38 = remaining_real(n.w[0x10]);
          }
          else
          {
            local_38 = -10.0;
          }
          if (remaining_real(0xc0000000u) <= local_38)
          {
            if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
            {
              local_40 = n.w[0x10];
            }
            else
            {
              local_40 = -0x3ee00000;
            }
            local_3c = local_40;
          }
          else
          {
            local_3c = -0x40000000;
          }
          n.w[0x10] = local_3c;
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 0x14 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_4_0_333(RemainingMeleeContext& n)
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_4_0_334(RemainingMeleeContext& n)
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_4_0_340(RemainingMeleeContext& n)
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3b, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 10))
        {
          n.FUN_0042c880(0x3d);
          fVar6 = (float10) n.FUN_0042d980();
          if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaec3)) != '\x01'))))
          {
            fVar6 = (float10) n.FUN_0042d980();
            if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaebe)) != '\x01'))))
            {
              fVar6 = (float10) n.FUN_0042d980();
              if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaeb9)) != '\x01'))))
              {
                n.FUN_004223d0(2, 10, 0);
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
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 4))
        {
          n.w[0x15] = 0x41700000;
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x3f800000);
        }
        if (((n.w[0x2b7d] == 2) && (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f400000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_4_1_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
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
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          fVar6 = (float10) n.FUN_0042da30();
          fVar12 = remaining_real(n.w[0x15]);
          fVar8 = (float10) n.FUN_0042d980();
          fVar8 = (float10) n.FUN_0042de80((float) fVar8);
          n.w[0x10] = remaining_bits(float((float) (((float10) ((float) (fVar6 * ((float10) fVar12)))) / (fVar8 + ((float10) remaining_real(0x3f800000u))))));
          if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
          {
            local_38 = remaining_real(n.w[0x10]);
          }
          else
          {
            local_38 = -10.0;
          }
          if (remaining_real(0xc0000000u) <= local_38)
          {
            if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
            {
              local_40 = n.w[0x10];
            }
            else
            {
              local_40 = -0x3ee00000;
            }
            local_3c = local_40;
          }
          else
          {
            local_3c = -0x40000000;
          }
          n.w[0x10] = local_3c;
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 0x14 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_4_1_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_4_1_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_4_1_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3b, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 10))
        {
          n.FUN_0042c880(0x3d);
          fVar6 = (float10) n.FUN_0042d980();
          if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaec3)) != '\x01'))))
          {
            fVar6 = (float10) n.FUN_0042d980();
            if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaebe)) != '\x01'))))
            {
              fVar6 = (float10) n.FUN_0042d980();
              if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaeb9)) != '\x01'))))
              {
                n.FUN_004223d0(2, 10, 0);
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
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 4))
        {
          n.w[0x15] = 0x41700000;
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x3f800000);
        }
        if (((n.w[0x2b7d] == 2) && (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f400000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_4_2_332(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(2, 10, 0);
            fVar6 = (float10) n.FUN_0042dac0(2);
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0;
            n.w[0x15] = 0;
            n.w[0x16] = 0;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x14 < n.w[0x2b81])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 10 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_4_2_333(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_4_2_334(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
    {
      do
      {
        n.w[0x1a1] = 2;
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_00423000();
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
        {
          n.FUN_004223d0(3, 10, 0);
          n.w[0x16] = 0x3ee66666;
          n.w[0x10] = 0x41200000;
          n.w[0x15] = -0x3f200000;
        }
        if ((n.w[0x2b7d] == 2) && (10 < n.w[0x2b81]))
        {
          n.FUN_00421080(0x2b);
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_4_2_340(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.FUN_0042db10(0, 0x43340000);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 1))
        {
          n.w[0x15] = 0x41f00000;
          n.FUN_0042c8b0(0x3e);
          n.FUN_004223d0(2, 10, 0);
        }
        if ((0xc < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] < 2) || (9 < n.w[0x2b81]))
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

inline void remaining_body_4_2_341(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.FUN_0042db10(0, 0x41f00000);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = 0x41a00000;
          n.FUN_0042c8b0(0x3e);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((0xc < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_3_0_332(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_14;
  int local_10;
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
        if ((((char) n.w[0x21]) == '\0') && (2 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41200000);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x16] = 0x3f400000;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
        }
        if (n.w[0x2b7d] == 1)
        {
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
          }
          n.FUN_0042db10(0, 0x41200000);
          n.w[0x15] = 0x41680000;
          if (4 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.FUN_0042c8b0(0x3d);
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
          {
            if (n.w[0x3a] == 0)
            {
              n.FUN_00423000();
              n.FUN_0042c800(0);
              n.FUN_0042c840(1);
              n.write_scratch(0x3a, 1);
              n.w[0x10] = 0x41700000;
            }
            else
            {
              n.FUN_00421100(3);
              n.w[0x10] = 0;
              n.w[0x16] = 0;
            }
          }
        }
        if (n.w[0x2b7d] < 3)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        if (n.w[0x2b7d] == 3)
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f266666u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (((char) n.w[0x21]) == '\0')
          {
            n.FUN_00421080(0x2b);
            return;
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

inline void remaining_body_3_0_333(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_14;
  int local_10;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_3_0_334(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_14;
  int local_10;
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
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_3_0_340(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_14;
  int local_10;
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
        n.write_scratch(0x3b, 0);
      }
      n.w[0x1a1] = 2;
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0xc))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 4))
      {
        n.w[0x15] = 0x41200000;
      }
      if (0x14 < n.w[0x2b81])
      {
        if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x15]))) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        n.w[0x21d] = 0;
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

inline void remaining_body_3_0_341(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_40;
  int local_3c;
  float local_38;
  int local_14;
  int local_10;
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
      if ((n.w[0x2b7d] == 2) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5)) && ((n.w[0x15] = 0x40a00000, n.w[0x3b] == 1)))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 8))
      {
        n.w[0x15] = 0x40400000;
        n.FUN_004223d0(3, 10, 0);
        n.w[0x10] = 0x41a00000;
        n.w[0x16] = 0x3f800000;
        n.w[0x21d] = 0;
      }
      if ((((n.w[0x2b7d] == 1) || ((n.w[0x2b7d] == 0) && (8 < n.w[0x2b81]))) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.particle(300, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
        n.particle(0x136, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
        n.FUN_0042c8b0(0x28);
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x15] = 0;
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

inline void remaining_body_3_1_332(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_38;
  int local_34;
  float local_30;
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
        if ((((char) n.w[0x21]) == '\0') && (2 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41200000);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x16] = 0x3f400000;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
        }
        if (n.w[0x2b7d] == 1)
        {
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
          }
          n.FUN_0042db10(0, 0x41200000);
          n.w[0x15] = 0x41680000;
          if (4 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.FUN_0042c8b0(0x3d);
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
          {
            if (n.w[0x3a] == 0)
            {
              n.FUN_00423000();
              n.FUN_0042c800(0);
              n.FUN_0042c840(1);
              n.write_scratch(0x3a, 1);
              n.w[0x10] = 0x41700000;
            }
            else
            {
              n.FUN_00421100(3);
              n.w[0x10] = 0;
              n.w[0x16] = 0;
            }
          }
        }
        if (n.w[0x2b7d] < 3)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        if (n.w[0x2b7d] == 3)
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f266666u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (((char) n.w[0x21]) == '\0')
          {
            n.FUN_00421080(0x2b);
            return;
          }
        }
        break;
      }
      while (0);
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.w[0x2bda] = remaining_add(n.w[0x2bda], -1);
  n.w[0x2bd9] = remaining_add(n.w[0x2bd9], -1);
  if (n.w[0x2bd9] < 1)
  {
    n.w[0x2bd9] = 0x78;
    n.w[0x2bd8] = remaining_add(n.w[0x2bd8], -1);
    if (n.w[0x2bd8] < 0)
    {
      n.w[0x2bd8] = 0;
    }
  }
  if (n.w[0x2bda] < 0)
  {
    n.write_scratch(0x3e, 0);
  }
  if (((n.w[0x2bda] % 0x1e) == 1) && (n.w[0x2b7b] < 100))
  {
    n.FUN_0042c8b0(0x6d);
    n.FUN_004230e0();
    if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
    {
      n.FUN_00435450(6, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_3_1_333(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_38;
  int local_34;
  float local_30;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
        }
        break;
      }
      while (0);
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.w[0x2bda] = remaining_add(n.w[0x2bda], -1);
  n.w[0x2bd9] = remaining_add(n.w[0x2bd9], -1);
  if (n.w[0x2bd9] < 1)
  {
    n.w[0x2bd9] = 0x78;
    n.w[0x2bd8] = remaining_add(n.w[0x2bd8], -1);
    if (n.w[0x2bd8] < 0)
    {
      n.w[0x2bd8] = 0;
    }
  }
  if (n.w[0x2bda] < 0)
  {
    n.write_scratch(0x3e, 0);
  }
  if (((n.w[0x2bda] % 0x1e) == 1) && (n.w[0x2b7b] < 100))
  {
    n.FUN_0042c8b0(0x6d);
    n.FUN_004230e0();
    if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
    {
      n.FUN_00435450(6, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_3_1_334(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_38;
  int local_34;
  float local_30;
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
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
      }
      while (0);
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.w[0x2bda] = remaining_add(n.w[0x2bda], -1);
  n.w[0x2bd9] = remaining_add(n.w[0x2bd9], -1);
  if (n.w[0x2bd9] < 1)
  {
    n.w[0x2bd9] = 0x78;
    n.w[0x2bd8] = remaining_add(n.w[0x2bd8], -1);
    if (n.w[0x2bd8] < 0)
    {
      n.w[0x2bd8] = 0;
    }
  }
  if (n.w[0x2bda] < 0)
  {
    n.write_scratch(0x3e, 0);
  }
  if (((n.w[0x2bda] % 0x1e) == 1) && (n.w[0x2b7b] < 100))
  {
    n.FUN_0042c8b0(0x6d);
    n.FUN_004230e0();
    if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
    {
      n.FUN_00435450(6, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_3_1_340(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_38;
  int local_34;
  float local_30;
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
        n.write_scratch(0x3b, 0);
      }
      n.w[0x1a1] = 2;
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0xc))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 4))
      {
        n.w[0x15] = 0x41200000;
      }
      if (0x14 < n.w[0x2b81])
      {
        if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x15]))) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        n.w[0x21d] = 0;
      }
    }
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.w[0x2bda] = remaining_add(n.w[0x2bda], -1);
  n.w[0x2bd9] = remaining_add(n.w[0x2bd9], -1);
  if (n.w[0x2bd9] < 1)
  {
    n.w[0x2bd9] = 0x78;
    n.w[0x2bd8] = remaining_add(n.w[0x2bd8], -1);
    if (n.w[0x2bd8] < 0)
    {
      n.w[0x2bd8] = 0;
    }
  }
  if (n.w[0x2bda] < 0)
  {
    n.write_scratch(0x3e, 0);
  }
  if (((n.w[0x2bda] % 0x1e) == 1) && (n.w[0x2b7b] < 100))
  {
    n.FUN_0042c8b0(0x6d);
    n.FUN_004230e0();
    if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
    {
      n.FUN_00435450(6, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_3_1_341(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_38;
  int local_34;
  float local_30;
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
      if ((n.w[0x2b7d] == 2) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5)) && ((n.w[0x15] = 0x40a00000, n.w[0x3b] == 1)))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 8))
      {
        n.w[0x15] = 0x40400000;
        n.FUN_004223d0(3, 10, 0);
        n.w[0x10] = 0x41a00000;
        n.w[0x16] = 0x3f800000;
        n.w[0x21d] = 0;
      }
      if ((((n.w[0x2b7d] == 1) || ((n.w[0x2b7d] == 0) && (8 < n.w[0x2b81]))) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.particle(300, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
        n.particle(0x136, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
        n.FUN_0042c8b0(0x28);
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(2);
        return;
      }
      break;
    }
    while (0);
  }
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.w[0x2bda] = remaining_add(n.w[0x2bda], -1);
  n.w[0x2bd9] = remaining_add(n.w[0x2bd9], -1);
  if (n.w[0x2bd9] < 1)
  {
    n.w[0x2bd9] = 0x78;
    n.w[0x2bd8] = remaining_add(n.w[0x2bd8], -1);
    if (n.w[0x2bd8] < 0)
    {
      n.w[0x2bd8] = 0;
    }
  }
  if (n.w[0x2bda] < 0)
  {
    n.write_scratch(0x3e, 0);
  }
  if (((n.w[0x2bda] % 0x1e) == 1) && (n.w[0x2b7b] < 100))
  {
    n.FUN_0042c8b0(0x6d);
    n.FUN_004230e0();
    if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
    {
      n.FUN_00435450(6, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (remaining_real(n.w[6])) + remaining_real(0x42480000u), n.w[7], (remaining_real(n.w[0x17])) + (remaining_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_3_2_332(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_38;
  int local_34;
  float local_30;
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
        if ((((char) n.w[0x21]) == '\0') && (2 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41200000);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x16] = 0x3f400000;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
        }
        if (n.w[0x2b7d] == 1)
        {
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
          }
          n.FUN_0042db10(0, 0x41200000);
          n.w[0x15] = 0x41680000;
          if (4 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (n.w[0x2b7d] == 2)
        {
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.FUN_0042c8b0(0x3d);
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
          {
            if (n.w[0x3a] == 0)
            {
              n.FUN_00423000();
              n.FUN_0042c800(0);
              n.FUN_0042c840(1);
              n.write_scratch(0x3a, 1);
              n.w[0x10] = 0x41700000;
            }
            else
            {
              n.FUN_00421100(3);
              n.w[0x10] = 0;
              n.w[0x16] = 0;
            }
          }
        }
        if (n.w[0x2b7d] < 3)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        if (n.w[0x2b7d] == 3)
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f266666u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (((char) n.w[0x21]) == '\0')
          {
            n.FUN_00421080(0x2b);
            return;
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

inline void remaining_body_3_2_333(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_38;
  int local_34;
  float local_30;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_3_2_334(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_38;
  int local_34;
  float local_30;
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
      if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        return;
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_3_2_340(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_38;
  int local_34;
  float local_30;
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
        n.write_scratch(0x3b, 0);
      }
      n.w[0x1a1] = 2;
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0xc))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 4))
      {
        n.w[0x15] = 0x41200000;
      }
      if (0x14 < n.w[0x2b81])
      {
        if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x15]))) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        n.w[0x21d] = 0;
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

inline void remaining_body_3_2_341(RemainingMeleeContext& n)
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
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  int local_38;
  int local_34;
  float local_30;
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
      if ((n.w[0x2b7d] == 2) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5)) && ((n.w[0x15] = 0x40a00000, n.w[0x3b] == 1)))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 8))
      {
        n.w[0x15] = 0x40400000;
        n.FUN_004223d0(3, 10, 0);
        n.w[0x10] = 0x41a00000;
        n.w[0x16] = 0x3f800000;
        n.w[0x21d] = 0;
      }
      if ((((n.w[0x2b7d] == 1) || ((n.w[0x2b7d] == 0) && (8 < n.w[0x2b81]))) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.particle(300, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
        n.particle(0x136, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
        n.FUN_0042c8b0(0x28);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x15] = 0;
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

inline void remaining_body_8_0_332(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
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
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2))
        {
          if (n.w[0x2b7d] == 0)
          {
            n.FUN_00421080(0x14e);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.FUN_00421100(2);
            n.FUN_0042c8b0(0x28);
          }
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        if (n.w[0x2b7d] < 2)
        {
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        }
        if (n.w[0x2b7d] == 2)
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (((char) n.w[0x21]) == '\0')
          {
            n.FUN_00421080(0x2b);
            n.w[0x16] = 0x3f000000;
            return;
          }
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0x418c0000;
          n.w[0x10] = 0x41700000;
          n.w[0x18] = 0;
          n.w[0x16] = 0x3f800000;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
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

inline void remaining_body_8_0_333(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
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
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_8_0_334(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
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
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_8_0_340(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
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
    {
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41a00000;
      }
      if (n.w[0x2b81] == 0x11)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_8_0_341(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
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
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if ((n.w[0x2b7d] == 2) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 10))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0x41c80000;
        n.w[0x10] = 0x41080000;
        n.w[0x16] = 0x3f19999a;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b7d] == 0) && ((fVar6 = (float10) n.FUN_0042d980(), fVar6 < ((float10) remaining_real(0x48742400u)))))
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        n.FUN_0042db10(0, 0x3f800000);
        if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.w[0x10] = 0;
          n.FUN_00421100(2);
          return;
        }
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
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

inline void remaining_body_8_1_332(RemainingMeleeContext& n)
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
        if ((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2))
        {
          if (n.w[0x2b7d] == 0)
          {
            n.FUN_00421080(0x14e);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.FUN_00421100(2);
            n.FUN_0042c8b0(0x28);
          }
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        if (n.w[0x2b7d] < 2)
        {
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        }
        if (n.w[0x2b7d] == 2)
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (((char) n.w[0x21]) == '\0')
          {
            n.FUN_00421080(0x2b);
            n.w[0x16] = 0x3f000000;
            return;
          }
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0x418c0000;
          n.w[0x10] = 0x41700000;
          n.w[0x18] = 0;
          n.w[0x16] = 0x3f800000;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
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

inline void remaining_body_8_1_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_8_1_334(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_8_1_340(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41a00000;
      }
      if (n.w[0x2b81] == 0x11)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_8_1_341(RemainingMeleeContext& n)
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
        n.FUN_00421080(0);
        return;
      }
      if ((n.w[0x2b7d] == 2) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 10))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0x41c80000;
        n.w[0x10] = 0x41080000;
        n.w[0x16] = 0x3f19999a;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b7d] == 0) && ((fVar5 = (float10) n.FUN_0042d980(), fVar5 < ((float10) remaining_real(0x48742400u)))))
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        n.FUN_0042db10(0, 0x3f800000);
        if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.w[0x10] = 0;
          n.FUN_00421100(2);
          return;
        }
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
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

inline void remaining_body_8_2_332(RemainingMeleeContext& n)
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
        if ((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2))
        {
          if (n.w[0x2b7d] == 0)
          {
            n.FUN_00421080(0x14e);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.FUN_00421100(2);
            n.FUN_0042c8b0(0x28);
          }
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        if (n.w[0x2b7d] < 2)
        {
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        }
        if (n.w[0x2b7d] == 2)
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
          if (((char) n.w[0x21]) == '\0')
          {
            n.FUN_00421080(0x2b);
            n.w[0x16] = 0x3f000000;
            return;
          }
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0x418c0000;
          n.w[0x10] = 0x41700000;
          n.w[0x18] = 0;
          n.w[0x16] = 0x3f800000;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
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

inline void remaining_body_8_2_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_8_2_334(RemainingMeleeContext& n)
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
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_8_2_336(RemainingMeleeContext& n)
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

inline void remaining_body_8_2_340(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41a00000;
      }
      if (n.w[0x2b81] == 0x11)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_8_2_341(RemainingMeleeContext& n)
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
      if ((n.w[0x2b7d] == 2) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 10))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0x41c80000;
        n.w[0x10] = 0x41080000;
        n.w[0x16] = 0x3f19999a;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b7d] == 0) && ((fVar5 = (float10) n.FUN_0042d980(), fVar5 < ((float10) remaining_real(0x48742400u)))))
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        n.FUN_0042db10(0, 0x3f800000);
        if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.w[0x10] = 0;
          n.FUN_00421100(2);
          return;
        }
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
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

inline void remaining_body_9_0_332(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2))
        {
          n.FUN_00421100(2);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 2))
        {
          n.w[0x16] = 0x3f000000;
          n.FUN_00421080(0x2b);
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.w[0x15] = 0x41480000;
          if (n.w[0x2b81] == 0)
          {
            n.write_scratch(0x3c, 0);
          }
          if ((n.w[0x2b81] == 0) && ((fVar6 = (float10) n.FUN_0042d980(), fVar6 < ((float10) remaining_real(0x491c4000u)))))
          {
            n.write_scratch(0x3c, 1);
          }
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x40800000);
          }
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.w[0xc] = remaining_bits(float((remaining_real(n.w[0xc])) + remaining_real(0x40a00000u)));
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
          }
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x40800000);
          }
          if ((n.w[0x2b81] % 0xf) == 0)
          {
            n.FUN_0042c8b0(0x40);
          }
          if (0x3c < n.w[0x2b81])
          {
            n.FUN_00421080(0x2b);
            return;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - remaining_real(0x3e4ccccdu)));
        }
        if (n.w[0x2b7d] == 2)
        {
          n.w[0xc] = 0;
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3eb33333u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_9_0_333(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_9_0_334(RemainingMeleeContext& n)
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
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_9_0_339(RemainingMeleeContext& n)
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
    {
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x2c);
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        return;
      }
      n.w[0x16] = 0x3f000000;
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
      if (0x14 < n.w[0x2b81])
      {
        n.FUN_00421080(0x2b);
        return;
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

inline void remaining_body_9_0_340(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 9)
      {
        n.FUN_0042c880(0x3d);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 9)
      {
        n.FUN_004223d0(2, 10, 0);
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_9_0_341(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 7)
      {
        n.FUN_0042c880(0x3e);
      }
      if (n.w[0x2b81] == 0)
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

inline void remaining_body_9_1_332(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2))
        {
          n.FUN_00421100(2);
          n.w[0x15] = 0;
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 2))
        {
          n.w[0x16] = 0x3f000000;
          n.FUN_00421080(0x2b);
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.w[0x15] = 0x41480000;
          if (n.w[0x2b81] == 0)
          {
            n.write_scratch(0x3c, 0);
          }
          if ((n.w[0x2b81] == 0) && ((fVar5 = (float10) n.FUN_0042d980(), fVar5 < ((float10) remaining_real(0x491c4000u)))))
          {
            n.write_scratch(0x3c, 1);
          }
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x40800000);
          }
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.w[0xc] = remaining_bits(float((remaining_real(n.w[0xc])) + remaining_real(0x40a00000u)));
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
          }
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x40800000);
          }
          if ((n.w[0x2b81] % 0xf) == 0)
          {
            n.FUN_0042c8b0(0x40);
          }
          if (0x3c < n.w[0x2b81])
          {
            n.FUN_00421080(0x2b);
            return;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - remaining_real(0x3e4ccccdu)));
        }
        if (n.w[0x2b7d] == 2)
        {
          n.w[0xc] = 0;
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3eb33333u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_9_1_333(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_9_1_334(RemainingMeleeContext& n)
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
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_9_1_339(RemainingMeleeContext& n)
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
    {
      do
      {
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x2c);
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        if (0x14 < n.w[0x2b81])
        {
          n.FUN_00421080(0x2b);
          return;
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

inline void remaining_body_9_1_340(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 9)
      {
        n.FUN_0042c880(0x3d);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 9)
      {
        n.FUN_004223d0(2, 10, 0);
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_9_1_341(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 7)
      {
        n.FUN_0042c880(0x3e);
      }
      if (n.w[0x2b81] == 0)
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

inline void remaining_body_9_2_332(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2))
        {
          n.FUN_00421100(2);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 2))
        {
          n.w[0x16] = 0x3f000000;
          n.FUN_00421080(0x2b);
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.w[0x15] = 0x41480000;
          if (n.w[0x2b81] == 0)
          {
            n.write_scratch(0x3c, 0);
          }
          if ((n.w[0x2b81] == 0) && ((fVar5 = (float10) n.FUN_0042d980(), fVar5 < ((float10) remaining_real(0x491c4000u)))))
          {
            n.write_scratch(0x3c, 1);
          }
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x40800000);
          }
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.w[0xc] = remaining_bits(float((remaining_real(n.w[0xc])) + remaining_real(0x40a00000u)));
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
          }
          if (n.w[0x3c] == 1)
          {
            n.FUN_0042db10(0, 0x40800000);
          }
          if ((n.w[0x2b81] % 0xf) == 0)
          {
            n.FUN_0042c8b0(0x40);
          }
          if (0x3c < n.w[0x2b81])
          {
            n.FUN_00421080(0x2b);
            return;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - remaining_real(0x3e4ccccdu)));
        }
        if (n.w[0x2b7d] == 2)
        {
          n.w[0xc] = 0;
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3eb33333u)));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_9_2_333(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_9_2_334(RemainingMeleeContext& n)
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
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_9_2_339(RemainingMeleeContext& n)
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
    {
      do
      {
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x2c);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        if (0x14 < n.w[0x2b81])
        {
          n.FUN_00421080(0x2b);
          return;
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

inline void remaining_body_9_2_340(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 9)
      {
        n.FUN_0042c880(0x3d);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 9)
      {
        n.FUN_004223d0(2, 10, 0);
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_9_2_341(RemainingMeleeContext& n)
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 7)
      {
        n.FUN_0042c880(0x3e);
      }
      if (n.w[0x2b81] == 0)
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

inline void remaining_body_5_0_312(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
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
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = -0x3e900000;
        }
        if (0x18 < n.w[0x2b81])
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f800000u)));
          if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0xa1] == 3) || ((0 < n.w[0xad]) && (n.w[0xad] < 3)))
          {
            n.FUN_00421080(0x139);
            return;
          }
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41a00000);
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

inline void remaining_body_5_0_313(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
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
          n.w[0x15] = 0x41f00000;
          n.FUN_004223d0(3, 10, 0);
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.FUN_0042db10(0, 0x43340000);
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
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40800000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40800000);
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          if (0xf < n.w[0x3a])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_5_0_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar7 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar7;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar7 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x42020000u)))));
            fVar7 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x42020000u)))));
            fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar7 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_5_0_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_5_0_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
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
    {
      do
      {
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_5_0_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
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
        n.write_scratch(0x3b, 0);
      }
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 7)
      {
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_0042c880(0x3d);
      }
      if (n.w[0x2b81] == 0x1d)
      {
        n.FUN_00423000();
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_0042c880(0x3e);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0x12)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_5_0_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
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
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 3)) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5)) && (n.w[0x3b] == 1))
      {
        n.w[0x15] = 0;
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0x40a00000;
        n.w[0x10] = 0x41c80000;
        n.w[0x16] = 0x3fa00000;
        n.w[0x21d] = 0;
        n.FUN_004223d0(3, 10, 0);
      }
      if (((0 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), n.w[0x2b7d] < 3))) && ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u))))
      {
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(3);
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

inline void remaining_body_5_1_312(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = -0x3e900000;
        }
        if (0x18 < n.w[0x2b81])
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f800000u)));
          if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0xa1] == 3) || ((0 < n.w[0xad]) && (n.w[0xad] < 3)))
          {
            n.FUN_00421080(0x139);
            return;
          }
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41a00000);
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

inline void remaining_body_5_1_313(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
          n.w[0x15] = 0x41f00000;
          n.FUN_004223d0(3, 10, 0);
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.FUN_0042db10(0, 0x43340000);
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
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40800000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40800000);
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          if (0xf < n.w[0x3a])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_5_1_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
        n.FUN_00421080(0x2b);
        n.w[0xb] = 0;
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
      {
        n.FUN_00421080(0x14d);
        n.w[0xb] = 0;
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        return;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.w[0x10] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (n.w[0x2b7d] == 1)
      {
        iVar5 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
        if (iVar5 != 0)
        {
          n.FUN_0042db10(0, 0x3f800000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422490(3, 0, 10, 0);
          fVar6 = (float10) n.FUN_0042da80();
          local_10 = (float) fVar6;
          if (remaining_real(0xc0a00000u) < local_10)
          {
            local_10 = -5.0;
          }
          if (local_10 < remaining_real(0xc1a00000u))
          {
            local_10 = -20.0;
          }
          fVar6 = (float10) n.FUN_0065d050(local_10);
          n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x42020000u)))));
          fVar6 = (float10) n.FUN_0065d010(local_10);
          n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x42020000u)))));
          fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
          n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
          if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
          {
            n.w[0xb] = 0;
          }
          n.w[0xb6] = 0x428c0000;
        }
        sVar2 = n.FUN_0042c7b0();
        if (sVar2 != 0)
        {
          n.w[0xb] = 0;
          n.w[0x10] = 0x41200000;
          n.w[0x15] = -0x3f200000;
          n.w[0x16] = 0x3eb33333;
          n.FUN_00421080(0x14e);
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          return;
        }
        if (0x16 < n.w[0x2b81])
        {
          n.FUN_0042c840(0);
        }
        if (0x28 < n.w[0x2b81])
        {
          n.FUN_00421100(2);
          n.w[0x15] = 0x41200000;
          return;
        }
      }
      if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
      {
        if (n.w[0x2b7d] == 2)
        {
          if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
          {
            n.w[0xb] = 0;
          }
          if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
          {
            n.w[0xb] = 0;
          }
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_5_1_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
      n.w[0x10] = 0;
      n.w[0x16] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = remaining_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
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

inline void remaining_body_5_1_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        return;
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

inline void remaining_body_5_1_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
        n.write_scratch(0x3b, 0);
      }
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 7)
      {
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_0042c880(0x3d);
      }
      if (n.w[0x2b81] == 0x1d)
      {
        n.FUN_00423000();
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_0042c880(0x3e);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0x12)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_5_1_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
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
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 3)) && (((char) n.w[0x21]) == '\0'))
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
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5)) && (n.w[0x3b] == 1))
      {
        n.w[0x15] = 0;
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0x40a00000;
        n.w[0x10] = 0x41c80000;
        n.w[0x16] = 0x3fa00000;
        n.w[0x21d] = 0;
        n.FUN_004223d0(3, 10, 0);
      }
      if (((0 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), n.w[0x2b7d] < 3))) && ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u))))
      {
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(3);
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

inline void remaining_body_5_2_312(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = -0x3e900000;
        }
        if (0x18 < n.w[0x2b81])
        {
          n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f800000u)));
          if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0xa1] == 3) || ((0 < n.w[0xad]) && (n.w[0xad] < 3)))
          {
            n.FUN_00421080(0x139);
            return;
          }
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41a00000);
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

inline void remaining_body_5_2_313(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.w[0x15] = 0x41f00000;
          n.FUN_004223d0(3, 10, 0);
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3a, 0);
          n.FUN_0042db10(0, 0x43340000);
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
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40800000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x40800000);
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          if (0xf < n.w[0x3a])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_5_2_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_24;
  int local_20;
  float local_1c;
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
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar7 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar7;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar7 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x42020000u)))));
            fVar7 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x42020000u)))));
            fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar7 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_5_2_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_5_2_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_5_2_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        n.w[0x1a1] = 2;
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 7)
        {
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042c880(0x3d);
        }
        if (n.w[0x2b81] == 0x1d)
        {
          n.FUN_00423000();
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042c880(0x3e);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41900000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41700000;
        }
        if (n.w[0x2b81] == 0x12)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
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

inline void remaining_body_5_2_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_24;
  int local_20;
  float local_1c;
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
        if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 3)) && (((char) n.w[0x21]) == '\0'))
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
        n.w[0x1a1] = 2;
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5)) && (n.w[0x3b] == 1))
        {
          n.w[0x15] = 0;
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0x40a00000;
          n.w[0x10] = 0x41c80000;
          n.w[0x16] = 0x3fa00000;
          n.w[0x21d] = 0;
          n.FUN_004223d0(3, 10, 0);
        }
        if (((0 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), n.w[0x2b7d] < 3))) && ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u))))
        {
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x15] = 0;
          n.FUN_00421100(3);
          return;
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

inline void remaining_body_6_0_332(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_24;
  int local_20;
  float local_1c;
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
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x2b81] = 0x18;
          n.w[0x2b82] = 0x18;
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x3f800000);
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
            fVar5 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar5;
            if (remaining_real(0xc1a00000u) < local_10)
            {
              local_10 = -20.0;
            }
            if (local_10 < remaining_real(0xc20c0000u))
            {
              local_10 = -35.0;
            }
            fVar5 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar5 * ((float10) remaining_real(0x41a80000u)))));
            fVar5 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar5 * ((float10) remaining_real(0x41a80000u)))));
            fVar5 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar5 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x00000000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          if (0x2d < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (1 < n.w[0x2b7d])
        {
          if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
          {
            n.w[0xb] = 0;
          }
          if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
          {
            n.w[0xb] = 0;
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_6_0_333(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f000000u)));
        if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_6_0_334(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_6_0_339(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x2c);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        if (0x14 < n.w[0x2b81])
        {
          n.FUN_00421080(0x2b);
          return;
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

inline void remaining_body_6_0_340(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        n.w[0x1a1] = 2;
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if (n.w[0x2b81] == 0)
        {
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
        if (n.w[0x2b81] == 0xd)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41700000;
        }
        if (n.w[0x2b81] == 0xf)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
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

inline void remaining_body_6_0_341(RemainingMeleeContext& n)
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
  undefined4 uVar12;
  int local_24;
  int local_20;
  float local_1c;
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 9)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(3, 10, 0);
      }
      if ((n.w[0x2b81] < 10) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_6_1_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_28;
  int local_24;
  float local_20;
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
  iVar3 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x2b81] = 0x18;
          n.w[0x2b82] = 0x18;
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x3f800000);
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc1a00000u) < local_10)
            {
              local_10 = -20.0;
            }
            if (local_10 < remaining_real(0xc20c0000u))
            {
              local_10 = -35.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41a00000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41a00000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x00000000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          if (0x2d < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (1 < n.w[0x2b7d])
        {
          if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
          {
            n.w[0xb] = 0;
          }
          if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
          {
            n.w[0xb] = 0;
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_6_1_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_28;
  int local_24;
  float local_20;
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
  iVar3 = n.w[0x2b7b];
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f000000u)));
        if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_6_1_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_28;
  int local_24;
  float local_20;
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
  iVar3 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_6_1_339(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_28;
  int local_24;
  float local_20;
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
  iVar3 = n.w[0x2b7b];
  {
    {
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x2c);
        n.w[0x10] = 0;
        return;
      }
      n.w[0x16] = 0x3f000000;
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
      if (0x14 < n.w[0x2b81])
      {
        n.FUN_00421080(0x2b);
        return;
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

inline void remaining_body_6_1_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_28;
  int local_24;
  float local_20;
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
  iVar3 = n.w[0x2b7b];
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
        n.write_scratch(0x3b, 0);
      }
      n.w[0x1a1] = 2;
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar5 = n.FUN_0042c7b0();
      if ((uVar5 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 0xd)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_6_1_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_28;
  int local_24;
  float local_20;
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
  iVar3 = n.w[0x2b7b];
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar5 = n.FUN_0042c7b0();
      if ((uVar5 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 9)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(3, 10, 0);
      }
      if ((n.w[0x2b81] < 10) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x40000000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_6_2_332(RemainingMeleeContext& n)
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
  undefined4 uVar13;
  int local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  float local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int local_138;
  float local_134;
  int local_110;
  int local_10c;
  float local_108;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x1a]))) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) - remaining_real(0x41200000u))), (remaining_real(n.w[0x1a])) < remaining_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((remaining_real(n.w[0x1a])) < remaining_real(0x00000000u)) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) + remaining_real(0x41200000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x2b81] = 0x18;
          n.w[0x2b82] = 0x18;
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x3f800000);
          if (n.w[0x2b81] == 0)
          {
            n.FUN_004223d0(3, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc1a00000u) < local_10)
            {
              local_10 = -20.0;
            }
            if (local_10 < remaining_real(0xc20c0000u))
            {
              local_10 = -35.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41a00000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41a00000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x00000000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          if (0x2d < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        if (1 < n.w[0x2b7d])
        {
          if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
          {
            n.w[0xb] = 0;
          }
          if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
          {
            n.w[0xb] = 0;
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_6_2_333(RemainingMeleeContext& n)
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
  undefined4 uVar13;
  int local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  float local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int local_138;
  float local_134;
  int local_110;
  int local_10c;
  float local_108;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x1a]))) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) - remaining_real(0x41200000u))), (remaining_real(n.w[0x1a])) < remaining_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((remaining_real(n.w[0x1a])) < remaining_real(0x00000000u)) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) + remaining_real(0x41200000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f000000u)));
        if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_6_2_334(RemainingMeleeContext& n)
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
  undefined4 uVar13;
  int local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  float local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int local_138;
  float local_134;
  int local_110;
  int local_10c;
  float local_108;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x1a]))) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) - remaining_real(0x41200000u))), (remaining_real(n.w[0x1a])) < remaining_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((remaining_real(n.w[0x1a])) < remaining_real(0x00000000u)) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) + remaining_real(0x41200000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_6_2_339(RemainingMeleeContext& n)
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
  undefined4 uVar13;
  int local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  float local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int local_138;
  float local_134;
  int local_110;
  int local_10c;
  float local_108;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x1a]))) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) - remaining_real(0x41200000u))), (remaining_real(n.w[0x1a])) < remaining_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((remaining_real(n.w[0x1a])) < remaining_real(0x00000000u)) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) + remaining_real(0x41200000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x2c);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        if (0x14 < n.w[0x2b81])
        {
          n.FUN_00421080(0x2b);
          return;
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

inline void remaining_body_6_2_340(RemainingMeleeContext& n)
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
  undefined4 uVar13;
  int local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  float local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int local_138;
  float local_134;
  int local_110;
  int local_10c;
  float local_108;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x1a]))) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) - remaining_real(0x41200000u))), (remaining_real(n.w[0x1a])) < remaining_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((remaining_real(n.w[0x1a])) < remaining_real(0x00000000u)) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) + remaining_real(0x41200000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        n.w[0x1a1] = 2;
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if (n.w[0x2b81] == 0)
        {
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
        if (n.w[0x2b81] == 0xd)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41700000;
        }
        if (n.w[0x2b81] == 0xf)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
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

inline void remaining_body_6_2_341(RemainingMeleeContext& n)
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
  undefined4 uVar13;
  int local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  float local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int local_138;
  float local_134;
  int local_110;
  int local_10c;
  float local_108;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  if ((remaining_real(0x00000000u) < (remaining_real(n.w[0x1a]))) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) - remaining_real(0x41200000u))), (remaining_real(n.w[0x1a])) < remaining_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((remaining_real(n.w[0x1a])) < remaining_real(0x00000000u)) && ((n.w[0x1a] = remaining_bits(float((remaining_real(n.w[0x1a])) + remaining_real(0x41200000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 9)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(3, 10, 0);
      }
      if ((n.w[0x2b81] < 10) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x40000000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_7_0_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.w[0x2b81] = 6;
          n.w[0x2b82] = 6;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          if ((n.w[0x2b81] == 0) && (n.w[0x2b81] == 0))
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar7 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar7;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc20c0000u))
            {
              local_10 = -35.0;
            }
            fVar7 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41c80000u)))));
            fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar7 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x40a00000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.FUN_00421080(0x14e);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421080(0x153);
            n.w[0x15] = 0x41200000;
            return;
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

inline void remaining_body_7_0_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_7_0_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x19] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_00423000();
        }
        n.w[0x1a1] = 2;
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xb))
        {
          n.FUN_004223d0(0, 10, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xc))
        {
          n.w[0x15] = -0x3f400000;
          n.w[0x10] = 0x41200000;
        }
        if ((n.w[0x2b7d] == 1) || ((n.w[0x2b7d] == 0) && (0xc < n.w[0x2b81])))
        {
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        }
        if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 1) && (10 < n.w[0x2b81]))
        {
          n.FUN_00421080(0x2b);
          return;
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

inline void remaining_body_7_0_339(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_7_0_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_7_0_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_7_1_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_54;
  int local_50;
  float local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
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
  n.w[0x2bdb] = 0;
  iVar6 = n.w[0x2b7b];
  {
    {
      do
      {
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && ((n.FUN_0042db10(0, 0x40a00000), n.w[0x2b81] == 0)))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          if ((n.w[0x2b81] == 0) && (n.w[0x2b81] == 0))
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar7 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar7;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc20c0000u))
            {
              local_10 = -35.0;
            }
            fVar7 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41a00000u)))));
            fVar7 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar7 * ((float10) remaining_real(0x41a00000u)))));
            fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar7 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x40a00000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.FUN_00421080(0x14e);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.FUN_00421080(0x153);
            n.w[0x15] = 0x41200000;
            return;
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

inline void remaining_body_7_1_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_54;
  int local_50;
  float local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
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
  n.w[0x2bdb] = 0;
  iVar6 = n.w[0x2b7b];
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_7_1_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_54;
  int local_50;
  float local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
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
  n.w[0x2bdb] = 0;
  iVar6 = n.w[0x2b7b];
  {
    {
      do
      {
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x19] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_00423000();
        }
        n.w[0x1a1] = 2;
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xb))
        {
          n.FUN_004223d0(0, 10, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xc))
        {
          n.w[0x15] = -0x3f400000;
          n.w[0x10] = 0x41200000;
        }
        if ((n.w[0x2b7d] == 1) || ((n.w[0x2b7d] == 0) && (0xc < n.w[0x2b81])))
        {
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        }
        if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 1) && (10 < n.w[0x2b81]))
        {
          n.FUN_00421080(0x2b);
          return;
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

inline void remaining_body_7_1_339(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_54;
  int local_50;
  float local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
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
  n.w[0x2bdb] = 0;
  iVar6 = n.w[0x2b7b];
  {
    {
      do
      {
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_7_1_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_54;
  int local_50;
  float local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
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
  n.w[0x2bdb] = 0;
  iVar6 = n.w[0x2b7b];
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_7_1_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_54;
  int local_50;
  float local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
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
  n.w[0x2bdb] = 0;
  iVar6 = n.w[0x2b7b];
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_7_2_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.w[0x2b81] = 6;
          n.w[0x2b82] = 6;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          if ((n.w[0x2b81] == 0) && (n.w[0x2b81] == 0))
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc20c0000u))
            {
              local_10 = -35.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x40a00000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.FUN_00421080(0x14e);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421080(0x153);
            n.w[0x15] = 0x41200000;
            return;
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

inline void remaining_body_7_2_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_7_2_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x19] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_00423000();
        }
        n.w[0x1a1] = 2;
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xb))
        {
          n.FUN_004223d0(0, 10, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xc))
        {
          n.w[0x15] = -0x3f400000;
          n.w[0x10] = 0x41200000;
        }
        if ((n.w[0x2b7d] == 1) || ((n.w[0x2b7d] == 0) && (0xc < n.w[0x2b81])))
        {
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
        }
        if ((((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 1) && (10 < n.w[0x2b81]))
        {
          n.FUN_00421080(0x2b);
          return;
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

inline void remaining_body_7_2_339(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_7_2_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_7_2_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_11_0_312(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = -0x3e600000;
        }
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f000000u)));
        if (n.w[0x2b81] < 0x1c)
        {
          if (remaining_real(0x41700000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0x41700000;
          }
        }
        else
          if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41a00000);
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

inline void remaining_body_11_0_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_11_0_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_11_0_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_11_0_336(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        n.w[0x1a1] = 2;
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042db10(0, 0x41200000);
        }
        if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0x41200000;
          n.w[0x10] = 0x41dc0000;
        }
        if (((0 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - remaining_real(0x3fa00000u))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.FUN_00421080(0x2c);
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
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

inline void remaining_body_11_0_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        n.w[0x1a1] = 2;
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if (n.w[0x2b81] == 0)
        {
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
        if (n.w[0x2b81] == 0xb)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 0xb)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 8)
        {
          n.w[0x15] = 0x41200000;
        }
        if (n.w[0x2b81] == 0x13)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
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

inline void remaining_body_11_0_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_24;
  int local_20;
  float local_1c;
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (n.w[0x2b81] == 3)
      {
        n.w[0x15] = 0x41200000;
      }
      if (n.w[0x2b81] == 0xd)
      {
        n.w[0x15] = 0;
        n.FUN_004223d0(3, 10, 0);
        n.FUN_0042c8b0(0x3e);
      }
      if ((n.w[0x2b81] < 0xd) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x41700000);
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

inline void remaining_body_11_1_312(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = -0x3e600000;
        }
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f000000u)));
        if (n.w[0x2b81] < 0x1c)
        {
          if (remaining_real(0x41700000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0x41700000;
          }
        }
        else
          if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41a00000);
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

inline void remaining_body_11_1_313(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        n.FUN_00428510();
        return;
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        if ((((char) n.w[0x21]) == '\0') && ((n.w[0x2b7d] < 3) || (n.w[0x2b7d] == 5)))
        {
          if (remaining_real(0x41200000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0x41200000;
          }
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.w[0x15] = 0;
          n.write_scratch(0x3a, 0);
          n.FUN_0042db10(0, 0x43340000);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = 0x41f00000;
        }
        if ((n.w[0x2b7d] < 2) && (((n.w[0x2b7d] == 1) && (7 < n.w[0x2b81])) || ((fVar6 = (float10) n.FUN_0042d980(), fVar6 < ((float10) remaining_real(0x46ea6000u))))))
        {
          n.FUN_00421100(2);
          return;
        }
        if ((n.w[0x2b7d] == 3) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042c8b0(0x3e);
          n.w[0x15] = 0x41200000;
          n.w[0x10] = 0x418c0000;
          n.write_scratch(0x3a, 0);
        }
        if (((n.w[0x2b7d] == 3) || (n.w[0x2b7d] == 4)) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - remaining_real(0x3f800000u))), (((char) n.w[0x21]) != '\0') && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))))
        {
          n.FUN_00421100(5);
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          return;
        }
        if (n.w[0x2b7d] < 2)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b7d] == 3) && (n.w[0x2b81] < 2))
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        if ((n.w[0x2b7d] == 3) && (n.w[0x2b81] == 2))
        {
          n.FUN_0042c880(0x3e);
          n.FUN_004223d0(3, 10, 0);
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

inline void remaining_body_11_1_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_11_1_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_11_1_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_11_1_336(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
      if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      n.w[0x1a1] = 2;
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_0042db10(0, 0x41200000);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0x41200000;
        n.w[0x10] = 0x41dc0000;
      }
      if (((0 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - remaining_real(0x3fa00000u))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
      {
        n.FUN_00421080(0x2c);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
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

inline void remaining_body_11_1_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
        n.write_scratch(0x3b, 0);
      }
      n.w[0x1a1] = 2;
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b81] == 0)
      {
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
      if (n.w[0x2b81] == 0xb)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 0xb)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 8)
      {
        n.w[0x15] = 0x41200000;
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
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

inline void remaining_body_11_1_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined4 uVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  int local_24;
  int local_20;
  float local_1c;
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (n.w[0x2b81] == 3)
      {
        n.w[0x15] = 0x41200000;
      }
      if (n.w[0x2b81] == 0xd)
      {
        n.w[0x15] = 0;
        n.FUN_004223d0(3, 10, 0);
        n.FUN_0042c8b0(0x3e);
      }
      if ((n.w[0x2b81] < 0xd) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x41700000);
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

inline void remaining_body_11_2_312(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
        {
          n.w[0x15] = -0x3e600000;
        }
        n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) + remaining_real(0x3f000000u)));
        if (n.w[0x2b81] < 0x1c)
        {
          if (remaining_real(0x41700000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0x41700000;
          }
        }
        else
          if (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41a00000);
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

inline void remaining_body_11_2_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_24;
  int local_20;
  float local_1c;
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
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_11_2_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_24;
  int local_20;
  float local_1c;
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_11_2_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_11_2_336(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        n.w[0x1a1] = 2;
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042db10(0, 0x41200000);
        }
        if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0x41200000;
          n.w[0x10] = 0x41dc0000;
        }
        if (((0 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - remaining_real(0x3fa00000u))), ((char) n.w[0x21]) != '\0'))) && ((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)))
        {
          n.FUN_00421080(0x2c);
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
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

inline void remaining_body_11_2_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_24;
  int local_20;
  float local_1c;
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        n.w[0x1a1] = 2;
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if (n.w[0x2b81] == 0)
        {
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
        if (n.w[0x2b81] == 0xb)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 0xb)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 8)
        {
          n.w[0x15] = 0x41200000;
        }
        if (n.w[0x2b81] == 0x13)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
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

inline void remaining_body_11_2_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_24;
  int local_20;
  float local_1c;
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if (n.w[0x2b81] == 3)
      {
        n.w[0x15] = 0x41200000;
      }
      if (n.w[0x2b81] == 0xd)
      {
        n.w[0x15] = 0;
        n.FUN_004223d0(3, 10, 0);
        n.FUN_0042c8b0(0x3e);
      }
      if ((n.w[0x2b81] < 0xd) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x41700000);
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

inline void remaining_body_10_0_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_0_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_10_0_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_10_0_339(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        switchD_00571d3b_caseD_1:
        n.FUN_00428510();

        return;
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

inline void remaining_body_10_0_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_0_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_1_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_1_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_10_1_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_10_1_339(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        switchD_0057f698_caseD_1:
        n.FUN_00428510();

        return;
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

inline void remaining_body_10_1_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_1_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_2_332(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_2_333(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_10_2_334(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_10_2_339(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        switchD_0058a738_caseD_1:
        n.FUN_00428510();

        return;
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

inline void remaining_body_10_2_340(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_10_2_341(RemainingMeleeContext& n)
{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
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
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
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
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if (n.w[0x2b81] < 8)
        {
          n.FUN_0042db10(0, 0x41c80000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_13_0_332(RemainingMeleeContext& n)
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
    {
      do
      {
        n.FUN_00434a70(0, 2);
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          fVar5 = (float10) n.FUN_0042da30();
          fVar10 = remaining_real(n.w[0x15]);
          fVar7 = (float10) n.FUN_0042d980();
          fVar7 = (float10) n.FUN_0042de80((float) fVar7);
          n.w[0x10] = remaining_bits(float((float) (((float10) ((float) (fVar5 * ((float10) fVar10)))) / (fVar7 + ((float10) remaining_real(0x3f800000u))))));
          if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
          {
            local_2c = remaining_real(n.w[0x10]);
          }
          else
          {
            local_2c = -10.0;
          }
          if (remaining_real(0xc0000000u) <= local_2c)
          {
            if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
            {
              local_34 = n.w[0x10];
            }
            else
            {
              local_34 = -0x3ee00000;
            }
            local_30 = local_34;
          }
          else
          {
            local_30 = -0x40000000;
          }
          n.w[0x10] = local_30;
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 0x14 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_13_0_333(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_13_0_334(RemainingMeleeContext& n)
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
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_13_0_340(RemainingMeleeContext& n)
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
          n.w[0x16] = 0x3f000000;
          return;
        }
        if (n.w[0x2b81] < 0x22)
        {
          n.w[0x1a1] = 2;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3b, 0);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 5)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 0xc)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 4)
        {
          n.w[0x15] = 0x41a00000;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] < 0x10) || (0x18 < n.w[0x2b81]))
        {
          n.FUN_00434bd0();
        }
        else
        {
          n.FUN_00434b90(0);
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

inline void remaining_body_13_0_341(RemainingMeleeContext& n)
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
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.w[0x1a1] = 2;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
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
      if (n.w[0x2b81] == 0x10)
      {
        n.FUN_0042c880(0x3d);
      }
      if ((n.w[0x2b81] < 0x10) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b81] == 4)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0xc)
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0x11) || (0x13 < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
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

inline void remaining_body_13_1_332(RemainingMeleeContext& n)
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
    {
      do
      {
        n.FUN_00434a70(0, 2);
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          fVar5 = (float10) n.FUN_0042da30();
          fVar9 = remaining_real(n.w[0x15]);
          fVar7 = (float10) n.FUN_0042d980();
          fVar7 = (float10) n.FUN_0042de80((float) fVar7);
          n.w[0x10] = remaining_bits(float((float) (((float10) ((float) (fVar5 * ((float10) fVar9)))) / (fVar7 + ((float10) remaining_real(0x3f800000u))))));
          if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
          {
            local_34 = remaining_real(n.w[0x10]);
          }
          else
          {
            local_34 = -10.0;
          }
          if (remaining_real(0xc0000000u) <= local_34)
          {
            if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
            {
              local_3c = n.w[0x10];
            }
            else
            {
              local_3c = -0x3ee00000;
            }
            local_38 = local_3c;
          }
          else
          {
            local_38 = -0x40000000;
          }
          n.w[0x10] = local_38;
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 0x14 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_13_1_333(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_13_1_334(RemainingMeleeContext& n)
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
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_13_1_340(RemainingMeleeContext& n)
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
          n.w[0x16] = 0x3f000000;
          return;
        }
        if (n.w[0x2b81] < 0x22)
        {
          n.w[0x1a1] = 2;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.write_scratch(0x3b, 0);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 5)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 0xc)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 4)
        {
          n.w[0x15] = 0x41a00000;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] < 0x10) || (0x18 < n.w[0x2b81]))
        {
          n.FUN_00434bd0();
        }
        else
        {
          n.FUN_00434b90(0);
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

inline void remaining_body_13_1_341(RemainingMeleeContext& n)
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
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.w[0x1a1] = 2;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
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
      if (n.w[0x2b81] == 0x10)
      {
        n.FUN_0042c880(0x3d);
      }
      if ((n.w[0x2b81] < 0x10) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b81] == 4)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0xc)
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0x11) || (0x13 < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
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

inline void remaining_body_13_2_332(RemainingMeleeContext& n)
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
    {
      do
      {
        n.FUN_00434a70(0, 2);
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          fVar5 = (float10) n.FUN_0042da30();
          fVar10 = remaining_real(n.w[0x15]);
          fVar7 = (float10) n.FUN_0042d980();
          fVar7 = (float10) n.FUN_0042de80((float) fVar7);
          n.w[0x10] = remaining_bits(float((float) (((float10) ((float) (fVar5 * ((float10) fVar10)))) / (fVar7 + ((float10) remaining_real(0x3f800000u))))));
          if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
          {
            local_2c = remaining_real(n.w[0x10]);
          }
          else
          {
            local_2c = -10.0;
          }
          if (remaining_real(0xc0000000u) <= local_2c)
          {
            if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
            {
              local_34 = n.w[0x10];
            }
            else
            {
              local_34 = -0x3ee00000;
            }
            local_30 = local_34;
          }
          else
          {
            local_30 = -0x40000000;
          }
          n.w[0x10] = local_30;
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 0x14 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_13_2_333(RemainingMeleeContext& n)
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
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_13_2_334(RemainingMeleeContext& n)
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
    {
      if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        return;
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_13_2_340(RemainingMeleeContext& n)
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
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b81] < 0x22)
      {
        n.w[0x1a1] = 2;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3b, 0);
      }
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 5)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 0xc)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 4)
      {
        n.w[0x15] = 0x41a00000;
      }
      if (n.w[0x2b81] == 0xc)
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0x10) || (0x18 < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
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

inline void remaining_body_13_2_341(RemainingMeleeContext& n)
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
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.w[0x1a1] = 2;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
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
      if (n.w[0x2b81] == 0x10)
      {
        n.FUN_0042c880(0x3d);
      }
      if ((n.w[0x2b81] < 0x10) && (n.w[0x3b] == 1))
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b81] == 4)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0xc)
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0x11) || (0x13 < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
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

inline void remaining_body_12_0_332(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_0_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_12_0_334(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_12_0_340(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0;
          n.FUN_0042c840(1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.w[0x15] = 0x41400000;
        }
        if (n.w[0x2b81] == 0x12)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 0xc)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0x15)
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_0_341(RemainingMeleeContext& n)
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
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((n.w[0x2b81] < 0xc) && (n.w[0x3b] == 1))
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_1_332(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_1_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_12_1_334(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_12_1_340(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0;
          n.FUN_0042c840(1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.w[0x15] = 0x41400000;
        }
        if (n.w[0x2b81] == 0x12)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 0xc)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0x15)
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_1_341(RemainingMeleeContext& n)
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
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((n.w[0x2b81] < 0xc) && (n.w[0x3b] == 1))
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_2_332(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          n.w[0x10] = -0x3f000000;
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x1e < n.w[0x3a])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_2_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_12_2_334(RemainingMeleeContext& n)
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
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_12_2_340(RemainingMeleeContext& n)
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
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3b, 0);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0;
          n.FUN_0042c840(1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.w[0x15] = 0x41400000;
        }
        if (n.w[0x2b81] == 0x12)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 0xc)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0x15)
        {
          n.w[0x15] = 0;
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

inline void remaining_body_12_2_341(RemainingMeleeContext& n)
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
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.w[0x15] = 0x41700000;
          n.FUN_0042c840(1);
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((n.w[0x2b81] < 0xc) && (n.w[0x3b] == 1))
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_14_0_332(RemainingMeleeContext& n)
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
  undefined4 uVar13;
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar1 = n.FUN_004218c0();
        if (cVar1 != '\0')
        {
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          fVar8 = (float10) n.FUN_0042da30();
          fVar11 = remaining_real(n.w[0x15]);
          fVar7 = (float10) n.FUN_0042d980();
          fVar7 = (float10) n.FUN_0042de80((float) fVar7);
          n.w[0x10] = remaining_bits(float((float) (((float10) ((float) (fVar8 * ((float10) fVar11)))) / (fVar7 + ((float10) remaining_real(0x3f800000u))))));
          if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
          {
            local_38 = remaining_real(n.w[0x10]);
          }
          else
          {
            local_38 = -10.0;
          }
          if (remaining_real(0xc0000000u) <= local_38)
          {
            if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
            {
              local_40 = n.w[0x10];
            }
            else
            {
              local_40 = -0x3ee00000;
            }
            local_3c = local_40;
          }
          else
          {
            local_3c = -0x40000000;
          }
          n.w[0x10] = local_3c;
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 0x14 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_14_0_333(RemainingMeleeContext& n)
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
  undefined4 uVar13;
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_14_0_334(RemainingMeleeContext& n)
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
  undefined4 uVar13;
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_14_0_340(RemainingMeleeContext& n)
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
  undefined4 uVar13;
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
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
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
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3b, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c880(0x3d);
        fVar8 = (float10) n.FUN_0042d980();
        if ((((float10) remaining_real(0x471c4000u)) <= fVar8) || ((fVar8 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar8) || ((n.byte(0xaec3)) != '\x01'))))
        {
          fVar8 = (float10) n.FUN_0042d980();
          if ((((float10) remaining_real(0x471c4000u)) <= fVar8) || ((fVar8 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar8) || ((n.byte(0xaebe)) != '\x01'))))
          {
            fVar8 = (float10) n.FUN_0042d980();
            if ((((float10) remaining_real(0x471c4000u)) <= fVar8) || ((fVar8 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar8) || ((n.byte(0xaeb9)) != '\x01'))))
            {
              n.FUN_004223d0(2, 10, 0);
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
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0x10))
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0x10))
      {
        n.w[0x15] = 0x41c80000;
      }
      if ((((n.w[0x2b7d] == 0) && (0x14 < n.w[0x2b81])) && (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
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

inline void remaining_body_14_1_312(RemainingMeleeContext& n)
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
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.w[0x15] = 0;
          n.write_scratch(0x3a, 0);
          n.FUN_0042db10(0, 0x43340000);
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
        if (n.w[0x2b81] == 7)
        {
          n.w[0x15] = 0x420c0000;
        }
        if (n.w[0x2b81] < 0xf)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b81] == 0xd)
        {
          n.FUN_0042c8b0(0x3e);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((0x12 < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] < 7) || (0x14 < n.w[0x2b81]))
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

inline void remaining_body_14_1_313(RemainingMeleeContext& n)
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
        if (n.w[0x2b81] < 0xe)
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042db10(0, 0x43340000);
        }
        if (n.w[0x2b81] == 7)
        {
          n.w[0x15] = 0x420c0000;
        }
        if (n.w[0x2b81] == 0xd)
        {
          n.FUN_0042c8b0(0x3e);
          n.FUN_004223d0(2, 10, 0);
        }
        if ((0xf < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x40c00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        uVar3 = n.FUN_0042c7b0();
        if ((uVar3 & 2) != 0)
        {
          n.FUN_00421080(0x188);
          n.FUN_0042c800(0);
          return;
        }
        if ((n.w[0x2b81] < 1) || (0x17 < n.w[0x2b81]))
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

inline void remaining_body_14_1_332(RemainingMeleeContext& n)
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
          n.FUN_00421080(0x2b);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.write_scratch(0x3a, 0);
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          n.w[0x15] = 0x41c80000;
          fVar6 = (float10) n.FUN_0042da30();
          fVar12 = remaining_real(n.w[0x15]);
          fVar8 = (float10) n.FUN_0042d980();
          fVar8 = (float10) n.FUN_0042de80((float) fVar8);
          n.w[0x10] = remaining_bits(float((float) (((float10) ((float) (fVar6 * ((float10) fVar12)))) / (fVar8 + ((float10) remaining_real(0x3f800000u))))));
          if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
          {
            local_38 = remaining_real(n.w[0x10]);
          }
          else
          {
            local_38 = -10.0;
          }
          if (remaining_real(0xc0000000u) <= local_38)
          {
            if ((remaining_real(n.w[0x10])) <= remaining_real(0xc1200000u))
            {
              local_40 = n.w[0x10];
            }
            else
            {
              local_40 = -0x3ee00000;
            }
            local_3c = local_40;
          }
          else
          {
            local_3c = -0x40000000;
          }
          n.w[0x10] = local_3c;
          n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1));
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x2d < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0);
            n.FUN_00421100(2);
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3a, remaining_add(n.w[0x3a], 1)), 0x14 < n.w[0x3a])))
        {
          n.write_scratch(0x3a, 0);
          n.FUN_00421100(3);
          n.w[0x15] = 0x41200000;
          return;
        }
        if ((1 < n.w[0x2b7d]) && ((n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16])))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
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

inline void remaining_body_14_1_333(RemainingMeleeContext& n)
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_14_1_334(RemainingMeleeContext& n)
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
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_14_1_336(RemainingMeleeContext& n)
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
      n.FUN_00434a70(0, 2);
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.w[0x19] = n.w[0x18];
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3c, 0);
        n.w[0x15] = 0x418c0000;
        fVar6 = (float10) n.FUN_0042d980();
        if (fVar6 < ((float10) remaining_real(0x4945c100u)))
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
      if ((n.w[0x2b7d] == 0) && (n.w[0x3c] == 1))
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x3c] == 1)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        fVar6 = (float10) n.FUN_0042d980();
        if (((fVar6 < ((float10) remaining_real(0x47afc800u))) || (10 < n.w[0x2b81])) || (n.w[0x3c] == 0))
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        if (n.w[0x2b81] == 7)
        {
          n.w[0x15] = 0x41f00000;
        }
        if ((n.w[0x2b81] < 0x15) && (n.w[0x3c] == 1))
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if (n.w[0x2b81] == 0x15)
        {
          n.FUN_0042c8b0(0x3e);
          n.FUN_004223d0(3, 10, 0);
        }
        if ((0xc < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f800000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] < 0xb) || (0x1d < n.w[0x2b81]))
        {
          n.FUN_00434bd0();
        }
        else
        {
          n.FUN_00434b30();
        }
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

inline void remaining_body_14_1_340(RemainingMeleeContext& n)
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
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3b, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c880(0x3d);
        fVar6 = (float10) n.FUN_0042d980();
        if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaec3)) != '\x01'))))
        {
          fVar6 = (float10) n.FUN_0042d980();
          if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaebe)) != '\x01'))))
          {
            fVar6 = (float10) n.FUN_0042d980();
            if ((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), (((float10) remaining_real(0x41f00000u)) <= fVar6) || ((n.byte(0xaeb9)) != '\x01'))))
            {
              n.FUN_004223d0(2, 10, 0);
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
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0x10))
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0x10))
      {
        n.w[0x15] = 0x41f00000;
      }
      if ((((n.w[0x2b7d] == 0) && (0x14 < n.w[0x2b81])) && (remaining_real(0x00000000u) < (remaining_real(n.w[0x15])))) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3fc00000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
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

inline void remaining_body_14_1_341(RemainingMeleeContext& n)
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
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3b, 0);
      }
      if (n.w[0x2b81] < 0x15)
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if (n.w[0x2b81] == 10)
      {
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] == 0x15)
      {
        n.FUN_0042c8b0(0x3e);
        fVar6 = (float10) n.FUN_0042d980();
        if (((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar6))) || ((n.byte(0xaec3)) != '\x01'))
        {
          fVar6 = (float10) n.FUN_0042d980();
          if (((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar6))) || ((n.byte(0xaebe)) != '\x01'))
          {
            fVar6 = (float10) n.FUN_0042d980();
            if (((((float10) remaining_real(0x471c4000u)) <= fVar6) || ((fVar6 = (float10) n.FUN_0042df90(n.w[0x19]), ((float10) remaining_real(0x41f00000u)) <= fVar6))) || ((n.byte(0xaeb9)) != '\x01'))
            {
              n.FUN_004223d0(2, 10, 0);
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
      if ((0x16 < n.w[0x2b81]) && ((n.w[0x15] = remaining_bits(float((remaining_real(n.w[0x15])) - remaining_real(0x3f000000u))), (remaining_real(n.w[0x15])) < remaining_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0xb) || (0x1d < n.w[0x2b81]))
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
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_15_0_332(RemainingMeleeContext& n)
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
  int local_54;
  int local_50;
  float local_4c;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  float local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
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
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar4 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar4 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar5 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar5;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar5 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar5 * ((float10) remaining_real(0x41c80000u)))));
            fVar5 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar5 * ((float10) remaining_real(0x41c80000u)))));
            fVar5 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar5 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar2 = n.FUN_0042c7b0();
          if (sVar2 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_15_0_333(RemainingMeleeContext& n)
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
  int local_54;
  int local_50;
  float local_4c;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  float local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
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
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_15_0_334(RemainingMeleeContext& n)
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
  int local_54;
  int local_50;
  float local_4c;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  float local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar4 = n.w[0x2b7b];
  {
    {
      do
      {
        if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00421100(1);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
        {
          n.FUN_00421080(0x14d);
          n.w[0x10] = 0;
          return;
        }
        if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_15_0_340(RemainingMeleeContext& n)
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
  int local_54;
  int local_50;
  float local_4c;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  float local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
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
          if (remaining_real(0x41200000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0x41200000;
          }
          n.w[0x10] = 0;
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.write_scratch(0x3b, 0);
          n.FUN_00422900();
          n.FUN_00423000();
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        n.w[0x1a1] = 2;
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
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
        if (n.w[0x2b81] == 0xd)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41900000);
        }
        if (n.w[0x2b81] == 7)
        {
          n.w[0x15] = 0x41c80000;
        }
        if (n.w[0x2b81] == 0xf)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
        }
        if ((n.w[0x2b81] < 0xe) || (0x13 < n.w[0x2b81]))
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

inline void remaining_body_15_0_341(RemainingMeleeContext& n)
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
  int local_54;
  int local_50;
  float local_4c;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  float local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_14;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
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
          if (remaining_real(0x41200000u) < (remaining_real(n.w[0x15])))
          {
            n.w[0x15] = 0x41200000;
          }
          n.w[0x10] = 0;
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.write_scratch(0x3b, 0);
          n.FUN_00422900();
          n.FUN_00423000();
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && (n.w[0x3b] == 0))
        {
          n.write_scratch(0x3b, 1);
        }
        n.w[0x1a1] = 2;
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0;
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
        if (n.w[0x2b81] == 0xf)
        {
          n.FUN_0042c880(0x3d);
          n.FUN_004223d0(2, 10, 0);
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x41900000);
        }
        if (n.w[0x2b81] == 10)
        {
          n.w[0x15] = 0x41c80000;
        }
        if (n.w[0x2b81] == 0x14)
        {
          n.w[0x15] = 0;
          n.w[0x21d] = 0;
        }
        if ((n.w[0x2b81] < 0xd) || (0x13 < n.w[0x2b81]))
        {
          n.FUN_00434bd0();
        }
        else
        {
          n.FUN_00434b30();
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

inline void remaining_body_15_1_332(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0xb] = 0;
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b7d]))
        {
          n.FUN_00421080(0x14d);
          n.w[0xb] = 0;
          n.w[0x15] = 0;
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          return;
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
        if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
        {
          n.FUN_00422900();
          n.FUN_00423000();
          n.w[0x15] = 0;
          n.w[0x18] = 0;
          n.w[0x10] = 0;
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
        }
        if (n.w[0x2b7d] == 1)
        {
          iVar5 = n.FUN_0066b65c((remaining_real(n.w[0x19])) < remaining_real(0x42b40000u));
          if (iVar5 != 0)
          {
            n.FUN_0042db10(0, 0x3f800000);
          }
          if (n.w[0x2b81] == 0)
          {
            n.FUN_00422490(3, 0, 10, 0);
            fVar6 = (float10) n.FUN_0042da80();
            local_10 = (float) fVar6;
            if (remaining_real(0xc0a00000u) < local_10)
            {
              local_10 = -5.0;
            }
            if (local_10 < remaining_real(0xc1a00000u))
            {
              local_10 = -20.0;
            }
            fVar6 = (float10) n.FUN_0065d050(local_10);
            n.w[0x15] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_0065d010(local_10);
            n.w[0x10] = remaining_bits(float((float) (fVar6 * ((float10) remaining_real(0x41c80000u)))));
            fVar6 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
            n.w[0xb] = remaining_bits(float((float) (((fVar6 / ((float10) remaining_real(0x40490fdbu))) * ((float10) remaining_real(0x43340000u))) + ((float10) remaining_real(0x41200000u)))));
            if (remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))
            {
              n.w[0xb] = 0;
            }
            n.w[0xb6] = 0x428c0000;
          }
          sVar3 = n.FUN_0042c7b0();
          if (sVar3 != 0)
          {
            n.w[0xb] = 0;
            n.w[0x10] = 0x41200000;
            n.w[0x15] = -0x3f200000;
            n.w[0x16] = 0x3eb33333;
            n.FUN_00421080(0x14e);
            n.FUN_0042c800(0);
            n.FUN_0042c840(1);
            return;
          }
          if (0x16 < n.w[0x2b81])
          {
            n.FUN_0042c840(0);
          }
          if (0x28 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            n.w[0x15] = 0x41200000;
            return;
          }
        }
        if ((n.w[0x2b7d] == 2) || ((n.w[0x2b7d] == 1) && (0x16 < n.w[0x2b81])))
        {
          if (n.w[0x2b7d] == 2)
          {
            if ((remaining_real(0x00000000u) < (remaining_real(n.w[0xb]))) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) - remaining_real(0x40a00000u))), (remaining_real(n.w[0xb])) < remaining_real(0x00000000u))))
            {
              n.w[0xb] = 0;
            }
            if (((remaining_real(n.w[0xb])) < remaining_real(0x00000000u)) && ((n.w[0xb] = remaining_bits(float((remaining_real(n.w[0xb])) + remaining_real(0x40a00000u))), remaining_real(0x00000000u) < (remaining_real(n.w[0xb])))))
            {
              n.w[0xb] = 0;
            }
          }
          if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
          if ((remaining_real(n.w[0x15])) < remaining_real(0x00000000u))
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

inline void remaining_body_15_1_333(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      do
      {
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        n.w[0x15] = 0;
        if (n.w[0x1fd] < 1)
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 0x28);
        }
        else
        {
          n.w[0x20d] = remaining_add(n.w[0x20d], 5);
        }
        if (1000 < n.w[0x20d])
        {
          n.w[0x20d] = 1000;
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

inline void remaining_body_15_1_334(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    {
      if (((remaining_real(n.w[0x10])) < remaining_real(0x40c00000u)) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (((remaining_real(n.w[0x10])) < remaining_real(0x00000000u)) != ((remaining_real(n.w[0x10])) == remaining_real(0x00000000u))))
      {
        n.FUN_00421080(0x14d);
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        return;
      }
      if ((remaining_real(n.w[0x16])) == remaining_real(0x00000000u))
      {
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = remaining_bits(float((remaining_real(n.w[0x10])) - (remaining_real(n.w[0x16]))));
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

inline void remaining_body_15_1_340(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    do
    {
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        if (remaining_real(0x41200000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0x41200000;
        }
        n.w[0x10] = 0;
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.write_scratch(0x3b, 0);
        n.FUN_00422900();
        n.FUN_00423000();
      }
      sVar3 = n.FUN_0042c7b0();
      if ((sVar3 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(3);
      }
      uVar4 = n.FUN_0042c7b0();
      if ((uVar4 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      sVar3 = n.FUN_0042c7b0();
      if (sVar3 != 0)
      {
        n.FUN_0042c800(0);
      }
      if (n.w[0x2b81] == 0xd)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b81] == 7)
      {
        n.w[0x15] = 0x41c80000;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b81] < 0xe) || (0x13 < n.w[0x2b81]))
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
  n.w[0x2b81] = remaining_add(n.w[0x2b81], 1);
  n.w[0x2b82] = remaining_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void remaining_body_15_1_341(RemainingMeleeContext& n)
{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  if (n.w[0x28] != 0)
  {
    return;
  }
  n.w[0x1f5] = -1;
  n.FUN_00434a70(0, 0);
  n.FUN_00434a70(1, 1);
  n.FUN_00434bd0();
  iVar5 = n.w[0x2b7b];
  {
    do
    {
      cVar2 = n.FUN_004218c0();
      if (cVar2 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        if (remaining_real(0x41200000u) < (remaining_real(n.w[0x15])))
        {
          n.w[0x15] = 0x41200000;
        }
        n.w[0x10] = 0;
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.write_scratch(0x3b, 0);
        n.FUN_00422900();
        n.FUN_00423000();
      }
      sVar3 = n.FUN_0042c7b0();
      if ((sVar3 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      n.w[0x1a1] = 2;
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      uVar4 = n.FUN_0042c7b0();
      if ((uVar4 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(2, 10, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b81] == 10)
      {
        n.w[0x15] = 0x41c80000;
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.w[0x15] = 0;
        n.w[0x21d] = 0;
      }
      if ((n.w[0x2b81] < 0xd) || (0x13 < n.w[0x2b81]))
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
void dispatch_remaining_melee_body(RemainingMeleeContext& n,unsigned ch,unsigned we,unsigned state)
#else
inline void dispatch_remaining_melee_body(RemainingMeleeContext& n,unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 2332: remaining_body_0_2_332(n);return;
 case 2333: remaining_body_0_2_333(n);return;
 case 2334: remaining_body_0_2_334(n);return;
 case 2340: remaining_body_0_2_340(n);return;
 case 332: remaining_body_0_0_332(n);return;
 case 333: remaining_body_0_0_333(n);return;
 case 334: remaining_body_0_0_334(n);return;
 case 340: remaining_body_0_0_340(n);return;
 case 341: remaining_body_0_0_341(n);return;
 case 1332: remaining_body_0_1_332(n);return;
 case 1333: remaining_body_0_1_333(n);return;
 case 1334: remaining_body_0_1_334(n);return;
 case 1340: remaining_body_0_1_340(n);return;
 case 1341: remaining_body_0_1_341(n);return;
 case 5312: remaining_body_1_2_312(n);return;
 case 5332: remaining_body_1_2_332(n);return;
 case 5333: remaining_body_1_2_333(n);return;
 case 5334: remaining_body_1_2_334(n);return;
 case 5340: remaining_body_1_2_340(n);return;
 case 5341: remaining_body_1_2_341(n);return;
 case 3312: remaining_body_1_0_312(n);return;
 case 3332: remaining_body_1_0_332(n);return;
 case 3333: remaining_body_1_0_333(n);return;
 case 3334: remaining_body_1_0_334(n);return;
 case 3340: remaining_body_1_0_340(n);return;
 case 3341: remaining_body_1_0_341(n);return;
 case 4312: remaining_body_1_1_312(n);return;
 case 4332: remaining_body_1_1_332(n);return;
 case 4333: remaining_body_1_1_333(n);return;
 case 4334: remaining_body_1_1_334(n);return;
 case 4340: remaining_body_1_1_340(n);return;
 case 4341: remaining_body_1_1_341(n);return;
 case 6332: remaining_body_2_0_332(n);return;
 case 6333: remaining_body_2_0_333(n);return;
 case 6334: remaining_body_2_0_334(n);return;
 case 6340: remaining_body_2_0_340(n);return;
 case 6341: remaining_body_2_0_341(n);return;
 case 7332: remaining_body_2_1_332(n);return;
 case 7333: remaining_body_2_1_333(n);return;
 case 7334: remaining_body_2_1_334(n);return;
 case 7340: remaining_body_2_1_340(n);return;
 case 7341: remaining_body_2_1_341(n);return;
 case 8332: remaining_body_2_2_332(n);return;
 case 8333: remaining_body_2_2_333(n);return;
 case 8334: remaining_body_2_2_334(n);return;
 case 8340: remaining_body_2_2_340(n);return;
 case 8341: remaining_body_2_2_341(n);return;
 case 12332: remaining_body_4_0_332(n);return;
 case 12333: remaining_body_4_0_333(n);return;
 case 12334: remaining_body_4_0_334(n);return;
 case 12340: remaining_body_4_0_340(n);return;
 case 13332: remaining_body_4_1_332(n);return;
 case 13333: remaining_body_4_1_333(n);return;
 case 13334: remaining_body_4_1_334(n);return;
 case 13340: remaining_body_4_1_340(n);return;
 case 14332: remaining_body_4_2_332(n);return;
 case 14333: remaining_body_4_2_333(n);return;
 case 14334: remaining_body_4_2_334(n);return;
 case 14340: remaining_body_4_2_340(n);return;
 case 14341: remaining_body_4_2_341(n);return;
 case 9332: remaining_body_3_0_332(n);return;
 case 9333: remaining_body_3_0_333(n);return;
 case 9334: remaining_body_3_0_334(n);return;
 case 9340: remaining_body_3_0_340(n);return;
 case 9341: remaining_body_3_0_341(n);return;
 case 10332: remaining_body_3_1_332(n);return;
 case 10333: remaining_body_3_1_333(n);return;
 case 10334: remaining_body_3_1_334(n);return;
 case 10340: remaining_body_3_1_340(n);return;
 case 10341: remaining_body_3_1_341(n);return;
 case 11332: remaining_body_3_2_332(n);return;
 case 11333: remaining_body_3_2_333(n);return;
 case 11334: remaining_body_3_2_334(n);return;
 case 11340: remaining_body_3_2_340(n);return;
 case 11341: remaining_body_3_2_341(n);return;
 case 24332: remaining_body_8_0_332(n);return;
 case 24333: remaining_body_8_0_333(n);return;
 case 24334: remaining_body_8_0_334(n);return;
 case 24340: remaining_body_8_0_340(n);return;
 case 24341: remaining_body_8_0_341(n);return;
 case 25332: remaining_body_8_1_332(n);return;
 case 25333: remaining_body_8_1_333(n);return;
 case 25334: remaining_body_8_1_334(n);return;
 case 25340: remaining_body_8_1_340(n);return;
 case 25341: remaining_body_8_1_341(n);return;
 case 26332: remaining_body_8_2_332(n);return;
 case 26333: remaining_body_8_2_333(n);return;
 case 26334: remaining_body_8_2_334(n);return;
 case 26336: remaining_body_8_2_336(n);return;
 case 26340: remaining_body_8_2_340(n);return;
 case 26341: remaining_body_8_2_341(n);return;
 case 27332: remaining_body_9_0_332(n);return;
 case 27333: remaining_body_9_0_333(n);return;
 case 27334: remaining_body_9_0_334(n);return;
 case 27339: remaining_body_9_0_339(n);return;
 case 27340: remaining_body_9_0_340(n);return;
 case 27341: remaining_body_9_0_341(n);return;
 case 28332: remaining_body_9_1_332(n);return;
 case 28333: remaining_body_9_1_333(n);return;
 case 28334: remaining_body_9_1_334(n);return;
 case 28339: remaining_body_9_1_339(n);return;
 case 28340: remaining_body_9_1_340(n);return;
 case 28341: remaining_body_9_1_341(n);return;
 case 29332: remaining_body_9_2_332(n);return;
 case 29333: remaining_body_9_2_333(n);return;
 case 29334: remaining_body_9_2_334(n);return;
 case 29339: remaining_body_9_2_339(n);return;
 case 29340: remaining_body_9_2_340(n);return;
 case 29341: remaining_body_9_2_341(n);return;
 case 15312: remaining_body_5_0_312(n);return;
 case 15313: remaining_body_5_0_313(n);return;
 case 15332: remaining_body_5_0_332(n);return;
 case 15333: remaining_body_5_0_333(n);return;
 case 15334: remaining_body_5_0_334(n);return;
 case 15340: remaining_body_5_0_340(n);return;
 case 15341: remaining_body_5_0_341(n);return;
 case 16312: remaining_body_5_1_312(n);return;
 case 16313: remaining_body_5_1_313(n);return;
 case 16332: remaining_body_5_1_332(n);return;
 case 16333: remaining_body_5_1_333(n);return;
 case 16334: remaining_body_5_1_334(n);return;
 case 16340: remaining_body_5_1_340(n);return;
 case 16341: remaining_body_5_1_341(n);return;
 case 17312: remaining_body_5_2_312(n);return;
 case 17313: remaining_body_5_2_313(n);return;
 case 17332: remaining_body_5_2_332(n);return;
 case 17333: remaining_body_5_2_333(n);return;
 case 17334: remaining_body_5_2_334(n);return;
 case 17340: remaining_body_5_2_340(n);return;
 case 17341: remaining_body_5_2_341(n);return;
 case 18332: remaining_body_6_0_332(n);return;
 case 18333: remaining_body_6_0_333(n);return;
 case 18334: remaining_body_6_0_334(n);return;
 case 18339: remaining_body_6_0_339(n);return;
 case 18340: remaining_body_6_0_340(n);return;
 case 18341: remaining_body_6_0_341(n);return;
 case 19332: remaining_body_6_1_332(n);return;
 case 19333: remaining_body_6_1_333(n);return;
 case 19334: remaining_body_6_1_334(n);return;
 case 19339: remaining_body_6_1_339(n);return;
 case 19340: remaining_body_6_1_340(n);return;
 case 19341: remaining_body_6_1_341(n);return;
 case 20332: remaining_body_6_2_332(n);return;
 case 20333: remaining_body_6_2_333(n);return;
 case 20334: remaining_body_6_2_334(n);return;
 case 20339: remaining_body_6_2_339(n);return;
 case 20340: remaining_body_6_2_340(n);return;
 case 20341: remaining_body_6_2_341(n);return;
 case 21332: remaining_body_7_0_332(n);return;
 case 21333: remaining_body_7_0_333(n);return;
 case 21334: remaining_body_7_0_334(n);return;
 case 21339: remaining_body_7_0_339(n);return;
 case 21340: remaining_body_7_0_340(n);return;
 case 21341: remaining_body_7_0_341(n);return;
 case 22332: remaining_body_7_1_332(n);return;
 case 22333: remaining_body_7_1_333(n);return;
 case 22334: remaining_body_7_1_334(n);return;
 case 22339: remaining_body_7_1_339(n);return;
 case 22340: remaining_body_7_1_340(n);return;
 case 22341: remaining_body_7_1_341(n);return;
 case 23332: remaining_body_7_2_332(n);return;
 case 23333: remaining_body_7_2_333(n);return;
 case 23334: remaining_body_7_2_334(n);return;
 case 23339: remaining_body_7_2_339(n);return;
 case 23340: remaining_body_7_2_340(n);return;
 case 23341: remaining_body_7_2_341(n);return;
 case 33312: remaining_body_11_0_312(n);return;
 case 33332: remaining_body_11_0_332(n);return;
 case 33333: remaining_body_11_0_333(n);return;
 case 33334: remaining_body_11_0_334(n);return;
 case 33336: remaining_body_11_0_336(n);return;
 case 33340: remaining_body_11_0_340(n);return;
 case 33341: remaining_body_11_0_341(n);return;
 case 34312: remaining_body_11_1_312(n);return;
 case 34313: remaining_body_11_1_313(n);return;
 case 34332: remaining_body_11_1_332(n);return;
 case 34333: remaining_body_11_1_333(n);return;
 case 34334: remaining_body_11_1_334(n);return;
 case 34336: remaining_body_11_1_336(n);return;
 case 34340: remaining_body_11_1_340(n);return;
 case 34341: remaining_body_11_1_341(n);return;
 case 35312: remaining_body_11_2_312(n);return;
 case 35332: remaining_body_11_2_332(n);return;
 case 35333: remaining_body_11_2_333(n);return;
 case 35334: remaining_body_11_2_334(n);return;
 case 35336: remaining_body_11_2_336(n);return;
 case 35340: remaining_body_11_2_340(n);return;
 case 35341: remaining_body_11_2_341(n);return;
 case 30332: remaining_body_10_0_332(n);return;
 case 30333: remaining_body_10_0_333(n);return;
 case 30334: remaining_body_10_0_334(n);return;
 case 30339: remaining_body_10_0_339(n);return;
 case 30340: remaining_body_10_0_340(n);return;
 case 30341: remaining_body_10_0_341(n);return;
 case 31332: remaining_body_10_1_332(n);return;
 case 31333: remaining_body_10_1_333(n);return;
 case 31334: remaining_body_10_1_334(n);return;
 case 31339: remaining_body_10_1_339(n);return;
 case 31340: remaining_body_10_1_340(n);return;
 case 31341: remaining_body_10_1_341(n);return;
 case 32332: remaining_body_10_2_332(n);return;
 case 32333: remaining_body_10_2_333(n);return;
 case 32334: remaining_body_10_2_334(n);return;
 case 32339: remaining_body_10_2_339(n);return;
 case 32340: remaining_body_10_2_340(n);return;
 case 32341: remaining_body_10_2_341(n);return;
 case 39332: remaining_body_13_0_332(n);return;
 case 39333: remaining_body_13_0_333(n);return;
 case 39334: remaining_body_13_0_334(n);return;
 case 39340: remaining_body_13_0_340(n);return;
 case 39341: remaining_body_13_0_341(n);return;
 case 40332: remaining_body_13_1_332(n);return;
 case 40333: remaining_body_13_1_333(n);return;
 case 40334: remaining_body_13_1_334(n);return;
 case 40340: remaining_body_13_1_340(n);return;
 case 40341: remaining_body_13_1_341(n);return;
 case 41332: remaining_body_13_2_332(n);return;
 case 41333: remaining_body_13_2_333(n);return;
 case 41334: remaining_body_13_2_334(n);return;
 case 41340: remaining_body_13_2_340(n);return;
 case 41341: remaining_body_13_2_341(n);return;
 case 36332: remaining_body_12_0_332(n);return;
 case 36333: remaining_body_12_0_333(n);return;
 case 36334: remaining_body_12_0_334(n);return;
 case 36340: remaining_body_12_0_340(n);return;
 case 36341: remaining_body_12_0_341(n);return;
 case 37332: remaining_body_12_1_332(n);return;
 case 37333: remaining_body_12_1_333(n);return;
 case 37334: remaining_body_12_1_334(n);return;
 case 37340: remaining_body_12_1_340(n);return;
 case 37341: remaining_body_12_1_341(n);return;
 case 38332: remaining_body_12_2_332(n);return;
 case 38333: remaining_body_12_2_333(n);return;
 case 38334: remaining_body_12_2_334(n);return;
 case 38340: remaining_body_12_2_340(n);return;
 case 38341: remaining_body_12_2_341(n);return;
 case 42332: remaining_body_14_0_332(n);return;
 case 42333: remaining_body_14_0_333(n);return;
 case 42334: remaining_body_14_0_334(n);return;
 case 42340: remaining_body_14_0_340(n);return;
 case 43312: remaining_body_14_1_312(n);return;
 case 43313: remaining_body_14_1_313(n);return;
 case 43332: remaining_body_14_1_332(n);return;
 case 43333: remaining_body_14_1_333(n);return;
 case 43334: remaining_body_14_1_334(n);return;
 case 43336: remaining_body_14_1_336(n);return;
 case 43340: remaining_body_14_1_340(n);return;
 case 43341: remaining_body_14_1_341(n);return;
 case 45332: remaining_body_15_0_332(n);return;
 case 45333: remaining_body_15_0_333(n);return;
 case 45334: remaining_body_15_0_334(n);return;
 case 45340: remaining_body_15_0_340(n);return;
 case 45341: remaining_body_15_0_341(n);return;
 case 46332: remaining_body_15_1_332(n);return;
 case 46333: remaining_body_15_1_333(n);return;
 case 46334: remaining_body_15_1_334(n);return;
 case 46340: remaining_body_15_1_340(n);return;
 case 46341: remaining_body_15_1_341(n);return;
 default:throw std::invalid_argument("No original remaining melee DAT binding");
 }}
