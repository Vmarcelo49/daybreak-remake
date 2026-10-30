// NEW123 actual350..362 bodies; generation alone is not parity proof.
#pragma once
inline void full_charge_body_0_0_351(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_1_0_350(FullChargeBodyContext& n)
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
          n.FUN_00434a70(0, 0);
          n.FUN_00434a70(1, 1);
          return;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          n.FUN_00434a70(0, 0);
          n.FUN_00434a70(1, 1);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if ((n.w[0x2b7d] < 2) || ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 10)))
        {
          n.FUN_00434a70(0, 4);
          n.FUN_00434a70(1, 0xffffffff);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.w[0x15] = 0;
          n.write_scratch(0x3a, 0);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, 0);
          n.write_scratch(0x3d, 0);
          n.write_scratch(0x3e, 0);
          n.FUN_004223d0(0x21, 0x14, 0);
          n.FUN_0042c8b0(0x4c);
        }
        if (n.w[0x3a] < 10)
        {
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          n.FUN_0042db10(0, 0x41900000);
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
          if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
        }
        else
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b7d] == 1)
        {
          n.FUN_0042db10(0, 0x3f800000);
          n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          if (((0x3c < n.w[0x2b81]) && (3 < n.w[0x3b])) && (n.w[0x3c] < 100))
          {
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3d, iVar4);
            if (n.w[0x3d] < (-0x1e))
            {
              n.write_scratch(0x3d, -0x1e);
            }
            if (0x1e < n.w[0x3d])
            {
              n.write_scratch(0x3d, 0x1e);
            }
            n.FUN_0042c8b0(0x4b);
            n.write_scratch(0x3b, 0);
            n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
            n.FUN_004230e0();
            uVar9 = 0;
            uVar3 = n.FUN_0065d150(0);
            fVar8 = (((float) (((short) (((ulonglong) uVar3) % 0x32)) + (-10))) * actor_word_real(0x3dcccccdu)) + (n.source_float(0x3d));
            uVar3 = n.FUN_0065d150(fVar8);
            n.FUN_00435000(0, 5, ((float) (((short) (((ulonglong) uVar3) % 0x32)) + (-0x19))) * actor_word_real(0x3dcccccdu), fVar8, uVar9);
          }
          if (((100 < n.w[0x3e]) && (n.w[0xa2] != 0)) || (0x186 < n.w[0x3e]))
          {
            n.FUN_00421100(2);
            return;
          }
        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_0_351(FullChargeBodyContext& n)
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
        {
          n.FUN_00428510();
          return;
        }
      }
      while (0);
    }
  }
}

inline void full_charge_body_1_0_352(FullChargeBodyContext& n)
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
        {
          n.FUN_00428510();
          return;
        }
      }
      while (0);
    }
  }
}

inline void full_charge_body_1_0_360(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.w[0x10] = -0x41000000;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
        n.FUN_004223d0(0x21, 0x14, 0);
        n.FUN_0042c8b0(0x4c);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      n.FUN_00434a70(0, 4);
      n.FUN_00434a70(1, 0xffffffff);
      if (n.w[0x3a] < 10)
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.FUN_0042db10(0, 0x3f800000);
        n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        if (((0x3c < n.w[0x2b81]) && (3 < n.w[0x3b])) && (n.w[0x3c] < 100))
        {
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3d, iVar4);
          if (n.w[0x3d] < (-0x1e))
          {
            n.write_scratch(0x3d, -0x1e);
          }
          if (0x1e < n.w[0x3d])
          {
            n.write_scratch(0x3d, 0x1e);
          }
          n.FUN_0042c8b0(0x4b);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
          n.FUN_004230e0();
          uVar9 = 0;
          uVar3 = n.FUN_0065d150(0);
          fVar8 = (((float) (((short) (((ulonglong) uVar3) % 0x32)) + (-10))) * actor_word_real(0x3dcccccdu)) + (n.source_float(0x3d));
          uVar3 = n.FUN_0065d150(fVar8);
          n.FUN_00435000(0, 5, ((float) (((short) (((ulonglong) uVar3) % 0x32)) + (-0x19))) * actor_word_real(0x3dcccccdu), fVar8, uVar9);
        }
        if (((100 < n.w[0x3e]) && (n.w[0xa2] != 0)) || (0x186 < n.w[0x3e]))
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (1 < n.w[0x2b7d])
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        n.w[0x16] = 0x3f000000;
        if (((((char) n.w[0x21]) != '\0') && (1 < n.w[0x2b7d])) && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.FUN_00421080(0x169);
          return;
        }
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_0_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_1_350(FullChargeBodyContext& n)
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
      if ((n.w[0x2b7d] < 2) || ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 10)))
      {
        n.FUN_00434a70(0, 4);
        n.FUN_00434a70(1, 0xffffffff);
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.w[0x15] = 0;
          n.write_scratch(0x3a, 0x3c);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, 0);
        }
        n.FUN_0042db10(0, 0x41a00000);
        if (n.w[0x2b81] < 10)
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
          if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
        }
        else
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422490(0x21, 3, 0x14, 0);
          n.FUN_0042c8b0(0x4c);
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
        }
        if (n.w[0x2b81] < 0x14)
        {
          n.FUN_0042db10(0, 0x3f800000);
        }
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        if (n.w[0x1b7] < 1)
        {
          n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
        }
        if (((((n.w[0x2b81] == 0x1e) || (n.w[0x2b81] == 0x23)) || (n.w[0x2b81] == 0x28)) || ((n.w[0x2b81] == 0x2d) || (n.w[0x2b81] == 0x32))) || ((n.w[0x2b81] == 0x37) || (n.w[0x2b81] == 0x3c)))
        {
          if (n.w[0x2b81] == 0x1e)
          {
            n.FUN_0042c8b0(0x52);
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3d, iVar4);
          }
          if (n.w[0x3d] < (-0x1e))
          {
            n.write_scratch(0x3d, -0x1e);
          }
          if (0x1e < n.w[0x3d])
          {
            n.write_scratch(0x3d, 0x1e);
          }
          n.write_scratch(0x3b, 0);
          n.FUN_00435000(0, 2, 0, n.source_float(0x3d), 0);
        }
        n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
        if (0x82 < n.w[0x3c])
        {
          n.FUN_00421100(2);
          return;
        }
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_1_351(FullChargeBodyContext& n)
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
    do
    {
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_1_1_352(FullChargeBodyContext& n)
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
    do
    {
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_1_1_360(FullChargeBodyContext& n)
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
    do
    {
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.w[0x10] = -0x41000000;
        n.w[0x16] = 0x3f000000;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.FUN_0042c8b0(0x4c);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      n.FUN_00434a70(0, 4);
      n.FUN_00434a70(1, 0xffffffff);
      if (n.w[0x3a] < 10)
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.FUN_0042db10(0, 0x41a00000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422490(0x20, 3, 10, 0);
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
        }
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        if (n.w[0x1b7] < 1)
        {
          n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
        }
        if (n.w[0x2b81] < 0x14)
        {
          n.FUN_0042db10(0, 0x3f800000);
        }
        if ((((((n.w[0x2b81] == 0x1e) || (n.w[0x2b81] == 0x23)) || (n.w[0x2b81] == 0x28)) || ((n.w[0x2b81] == 0x2d) || (n.w[0x2b81] == 0x32))) || (n.w[0x2b81] == 0x37)) || (n.w[0x2b81] == 0x3c))
        {
          if (n.w[0x2b81] == 0x1e)
          {
            n.FUN_0042c8b0(0x52);
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3d, iVar4);
          }
          if (n.w[0x3d] < (-0x1e))
          {
            n.write_scratch(0x3d, -0x1e);
          }
          if (0x1e < n.w[0x3d])
          {
            n.write_scratch(0x3d, 0x1e);
          }
          n.write_scratch(0x3b, 0);
          n.FUN_00435000(0, 2, 0, n.source_float(0x3d), 0);
        }
        n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
        if (0x82 < n.w[0x3c])
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (((1 < n.w[0x2b7d]) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), ((char) n.w[0x21]) != '\0'))) && ((1 < n.w[0x2b7d]) && ((n.source_float(0x10)) < actor_word_real(0x00000000u))))
      {
        n.FUN_00421080(0x169);
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_1_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_2_350(FullChargeBodyContext& n)
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
      if ((n.w[0x2b7d] < 2) || ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 10)))
      {
        n.FUN_00434a70(0, 4);
        n.FUN_00434a70(1, 0xffffffff);
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.w[0x15] = 0;
          n.write_scratch(0x3a, 0x3c);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, 0);
        }
        n.FUN_0042dc20(0, 0x41a00000);
        if (n.w[0x2b81] < 10)
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
          if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
        }
        else
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422490(0x21, 3, 0x14, 0);
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
        }
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042dc20(0, 0x40000000);
        }
        if ((((n.w[0x2b81] % 5) == 0) && (9 < n.w[0x2b81])) && (n.w[0x2b81] < 0x5b))
        {
          if (n.w[0x2b81] == 10)
          {
            n.FUN_0042c8b0(0xb5);
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3d, iVar4);
          }
          if (n.w[0x3d] < (-0x1e))
          {
            n.write_scratch(0x3d, -0x1e);
          }
          if (0x1e < n.w[0x3d])
          {
            n.write_scratch(0x3d, 0x1e);
          }
          n.write_scratch(0x3b, 0);
          n.FUN_00435000(0, 8, 0, n.source_float(0x3d), 0);
        }
        if ((((n.w[0x2b81] % 5) == 0) && (0x59 < n.w[0x2b81])) && (n.w[0x2b81] < 0x79))
        {
          if (n.w[0x2b81] == 0x5a)
          {
            n.FUN_0042c8b0(0xb6);
          }
          n.FUN_00435000(0, 4, 0, n.source_float(0x3d), 0);
        }
        if ((((n.w[0x2b81] % 5) == 0) && (0x59 < n.w[0x2b81])) && (n.w[0x2b81] < 0x8d))
        {
          n.FUN_00435000(0, 9, 0, n.source_float(0x3d), 0);
        }
        n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
        if (0xbe < n.w[0x3c])
        {
          n.FUN_00421100(2);
          return;
        }
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_2_360(FullChargeBodyContext& n)
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
    do
    {
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.w[0x10] = -0x41000000;
        n.w[0x16] = 0x3f000000;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      n.FUN_00434a70(0, 4);
      n.FUN_00434a70(1, 0xffffffff);
      if (n.w[0x3a] < 10)
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.FUN_0042dc20(0, 0x41a00000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422490(0x21, 3, 0x14, 0);
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
        }
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042dc20(0, 0x40000000);
        }
        if ((((n.w[0x2b81] % 5) == 0) && (9 < n.w[0x2b81])) && (n.w[0x2b81] < 0x5b))
        {
          if (n.w[0x2b81] == 10)
          {
            n.FUN_0042c8b0(0xb5);
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3d, iVar4);
          }
          if (n.w[0x3d] < (-0x1e))
          {
            n.write_scratch(0x3d, -0x1e);
          }
          if (0x1e < n.w[0x3d])
          {
            n.write_scratch(0x3d, 0x1e);
          }
          n.write_scratch(0x3b, 0);
          n.FUN_00435000(0, 8, 0, n.source_float(0x3d), 0);
        }
        if ((((n.w[0x2b81] % 5) == 0) && (0x59 < n.w[0x2b81])) && (n.w[0x2b81] < 0x79))
        {
          if (n.w[0x2b81] == 0x3c)
          {
            n.FUN_0042c8b0(0xb6);
          }
          n.FUN_00435000(0, 4, 0, n.source_float(0x3d), 0);
        }
        if ((((n.w[0x2b81] % 5) == 0) && (0x59 < n.w[0x2b81])) && (n.w[0x2b81] < 0x8d))
        {
          n.FUN_00435000(0, 9, 0, n.source_float(0x3d), 0);
        }
        n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1));
        if (0xbe < n.w[0x3c])
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if ((((1 < n.w[0x2b7d]) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), ((char) n.w[0x21]) != '\0'))) && (1 < n.w[0x2b7d])) && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x169);
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_1_2_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_2_0_350(FullChargeBodyContext& n)
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
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 4)
      {
        n.FUN_00435000(0, 1, 0, 0, 0);
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.FUN_0042c8b0(0x58);
        n.FUN_004223d0(0x21, 0x14, 0);
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x28))
        {
          n.write_scratch(0x3c, -0x28);
        }
        if (0x28 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x28);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_00434fd0(5, 0, n.source_float(0x3c), 0);
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 0x1e))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_2_0_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) * actor_word_real(0x3e800000u)));
        n.w[0x16] = 0x3dcccccd;
      }
      if (n.w[0x2b81] == 4)
      {
        n.FUN_00435000(0, 1, 0, 0, 0);
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.w[0x18] = 0;
        n.FUN_0042c8b0(0x58);
        n.w[0x15] = -0x3f300000;
        n.w[0x10] = 0x40a00000;
        n.FUN_004223d0(0x21, 0x14, 0);
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x28))
        {
          n.write_scratch(0x3c, -0x28);
        }
        if (0x28 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x28);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_00434fd0(5, 0, n.source_float(0x3c), 0);
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 0x1e))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_2_1_350(FullChargeBodyContext& n)
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
        n.write_scratch(0x3e, 0);
        n.FUN_004223d0(0x20, 0x14, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.FUN_0042c8b0(0x5b);
        n.FUN_004230e0();
        uVar6 = 0x42700000;
        fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar8 = (float10) n.FUN_0065d010(n.w[0x17], fVar15, 0x42700000);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar13 = n.source_float(7);
        fVar9 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar13 = (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar13)))) - (fVar9 * ((float10) actor_word_real(0x42480000u))));
        fVar11 = actor_word_real(0x41a00000u) + (n.source_float(6));
        fVar8 = (float10) n.FUN_0065d050(n.w[0x17], fVar11, fVar13);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar1 = n.source_float(5);
        fVar9 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar1)))) - (fVar9 * ((float10) actor_word_real(0x42480000u)))), fVar11, fVar13, fVar15, uVar6);
        uVar6 = 0x42700000;
        fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar8 = (float10) n.FUN_0065d010(n.w[0x17], fVar15, 0x42700000);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar13 = n.source_float(7);
        fVar9 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar13 = (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar13)))) - (fVar9 * ((float10) actor_word_real(0x42480000u))));
        fVar11 = actor_word_real(0x41a00000u) + (n.source_float(6));
        fVar8 = (float10) n.FUN_0065d050(n.w[0x17], fVar11, fVar13);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar1 = n.source_float(5);
        fVar9 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(6, (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar1)))) - (fVar9 * ((float10) actor_word_real(0x42480000u)))), fVar11, fVar13, fVar15, uVar6);
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 0x19))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_2_1_351(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_2_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(0x20, 0x14, 0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) * actor_word_real(0x3e800000u)));
        n.w[0x16] = 0x3dcccccd;
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.w[0x18] = 0;
        n.FUN_0042c8b0(0x5b);
        n.w[0x15] = -0x3f300000;
        n.w[0x10] = 0x40a00000;
        n.FUN_004230e0();
        uVar6 = 0x42700000;
        fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar8 = (float10) n.FUN_0065d010(n.w[0x17], fVar15, 0x42700000);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar13 = n.source_float(7);
        fVar9 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar13 = (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar13)))) - (fVar9 * ((float10) actor_word_real(0x42480000u))));
        fVar11 = actor_word_real(0x41a00000u) + (n.source_float(6));
        fVar8 = (float10) n.FUN_0065d050(n.w[0x17], fVar11, fVar13);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar1 = n.source_float(5);
        fVar9 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar1)))) - (fVar9 * ((float10) actor_word_real(0x42480000u)))), fVar11, fVar13, fVar15, uVar6);
        uVar6 = 0x42700000;
        fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar8 = (float10) n.FUN_0065d010(n.w[0x17], fVar15, 0x42700000);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar13 = n.source_float(7);
        fVar9 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar13 = (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar13)))) - (fVar9 * ((float10) actor_word_real(0x42480000u))));
        fVar11 = actor_word_real(0x41a00000u) + (n.source_float(6));
        fVar8 = (float10) n.FUN_0065d050(n.w[0x17], fVar11, fVar13);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar1 = n.source_float(5);
        fVar9 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(6, (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar1)))) - (fVar9 * ((float10) actor_word_real(0x42480000u)))), fVar11, fVar13, fVar15, uVar6);
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 0x19))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_2_2_350(FullChargeBodyContext& n)
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
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c8b0(0xb1);
        n.FUN_004223d0(0x27, 0x14, 0);
        uVar6 = 0;
        fVar16 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar8 = (float10) n.FUN_0065d010(n.w[0x17], fVar16, 0);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar13 = n.source_float(7);
        fVar9 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar13 = (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar13)))) - (fVar9 * ((float10) actor_word_real(0x42480000u))));
        iVar4 = n.w[6];
        fVar8 = (float10) n.FUN_0065d050(n.w[0x17], iVar4, fVar13);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar15 = n.source_float(5);
        fVar9 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(6, (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar15)))) - (fVar9 * ((float10) actor_word_real(0x42480000u)))), iVar4, fVar13, fVar16, uVar6);
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 5))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_2_2_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) * actor_word_real(0x3e800000u)));
        n.w[0x16] = 0x3dcccccd;
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c8b0(0xb1);
        n.FUN_004223d0(0x27, 0x14, 0);
        uVar6 = 0;
        fVar16 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar8 = (float10) n.FUN_0065d010(n.w[0x17], fVar16, 0);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar13 = n.source_float(7);
        fVar9 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar13 = (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar13)))) - (fVar9 * ((float10) actor_word_real(0x42480000u))));
        iVar4 = n.w[6];
        fVar8 = (float10) n.FUN_0065d050(n.w[0x17], iVar4, fVar13);
        fVar7 = (float10) actor_word_real(0x00000000u);
        fVar15 = n.source_float(5);
        fVar9 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(6, (float) (((float10) ((float) ((fVar8 * fVar7) + ((float10) fVar15)))) - (fVar9 * ((float10) actor_word_real(0x42480000u)))), iVar4, fVar13, fVar16, uVar6);
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0x23)
      {
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 5))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_3_0_350(FullChargeBodyContext& n)
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x15] = 0;
        n.w[0x18] = 0;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x40800000);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c8b0(0x6b);
        n.FUN_004223d0(0x20, 0x14, 0);
        for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          uVar3 = n.FUN_0065d150();
          fVar13 = ((float) (uVar3 % 0x46)) + actor_word_real(0x41700000u);
          uVar3 = n.FUN_0065d150(fVar13);
          fVar11 = -((float) (uVar3 % 0xf));
          uVar10 = 9;
          uVar14 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar14, uVar10, fVar11, fVar13);
          uVar3 = n.FUN_0065d150();
          fVar13 = ((float) (uVar3 % 0x46)) + actor_word_real(0x41700000u);
          uVar3 = n.FUN_0065d150(fVar13);
          fVar11 = (float) (uVar3 % 0xf);
          uVar10 = 9;
          uVar14 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar14, uVar10, fVar11, fVar13);
        }

      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_3_0_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3b, 0);
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x40800000);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c8b0(0x6b);
        n.FUN_004223d0(0x20, 0x14, 0);
        for (local_14 = 0; local_14 < 6; local_14 = local_14 + 1)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          uVar3 = n.FUN_0065d150();
          fVar13 = ((float) (uVar3 % 0x46)) + actor_word_real(0x41700000u);
          uVar3 = n.FUN_0065d150(fVar13);
          fVar11 = -((float) (uVar3 % 0xf));
          uVar10 = 9;
          uVar14 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar14, uVar10, fVar11, fVar13);
          uVar3 = n.FUN_0065d150();
          fVar13 = ((float) (uVar3 % 0x46)) + actor_word_real(0x41700000u);
          uVar3 = n.FUN_0065d150(fVar13);
          fVar11 = (float) (uVar3 % 0xf);
          uVar10 = 9;
          uVar14 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar14, uVar10, fVar11, fVar13);
        }

      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_3_1_350(FullChargeBodyContext& n)
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422300(0x21, 0, 0x14, 0);
        n.FUN_00422900();
        n.w[0x15] = 0;
        n.w[0x18] = 0;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0x19))
      {
        n.FUN_0042c8b0(0x70);
        n.FUN_004230e0();
        uVar13 = 0;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
        fVar11 = (float) ((fVar7 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar11);
        n.FUN_00435450(0x12, (float) ((fVar7 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar11, fVar12, uVar13);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.w[0x2bda] = actor_word_add(n.w[0x2bda], -1);
  n.w[0x2bd9] = actor_word_add(n.w[0x2bd9], -1);
  if (n.w[0x2bd9] < 1)
  {
    n.w[0x2bd9] = 0x78;
    n.w[0x2bd8] = actor_word_add(n.w[0x2bd8], -1);
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
      n.FUN_00435450(6, n.w[5], (n.source_float(6)) + actor_word_real(0x42480000u), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (n.source_float(6)) + actor_word_real(0x42480000u), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_3_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422300(0x21, 0, 0x14, 0);
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3b, 0);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c8b0(0x70);
        n.FUN_004230e0();
        uVar13 = 0x42200000;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0x42200000);
        fVar11 = (float) ((fVar7 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar11);
        n.FUN_00435450(0x12, (float) ((fVar7 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar11, fVar12, uVar13);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.w[0x2bda] = actor_word_add(n.w[0x2bda], -1);
  n.w[0x2bd9] = actor_word_add(n.w[0x2bd9], -1);
  if (n.w[0x2bd9] < 1)
  {
    n.w[0x2bd9] = 0x78;
    n.w[0x2bd8] = actor_word_add(n.w[0x2bd8], -1);
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
      n.FUN_00435450(6, n.w[5], (n.source_float(6)) + actor_word_real(0x42480000u), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (n.source_float(6)) + actor_word_real(0x42480000u), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_3_2_350(FullChargeBodyContext& n)
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
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x15] = 0;
        n.w[0x18] = 0;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042dc20(0, 0x40800000);
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042c8b0(0x9c);
        n.FUN_004223d0(0x20, 0x14, 0);
        uVar14 = 0x42700000;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, 0x42700000);
        fVar7 = (float10) actor_word_real(0x43160000u);
        fVar11 = n.source_float(7);
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar11)))) - (fVar6 * ((float10) actor_word_real(0x00000000u))));
        fVar8 = actor_word_real(0x41200000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050(n.w[0x17], fVar8, fVar11);
        fVar7 = (float10) actor_word_real(0x43160000u);
        fVar13 = n.source_float(5);
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(7, (float) (((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar13)))) - (fVar6 * ((float10) actor_word_real(0x00000000u)))), fVar8, fVar11, fVar12, uVar14);
      }
      if ((n.w[0x2b7d] == 2) && (0x3c < n.w[0x2b81]))
      {
        n.FUN_00421100(3);
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_3_2_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.w[0x18] = 0;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042dc20(0, 0x40800000);
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042c8b0(0x9c);
        n.FUN_004223d0(0x20, 0x14, 0);
        uVar14 = 0x42700000;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, 0x42700000);
        fVar7 = (float10) actor_word_real(0x43160000u);
        fVar11 = n.source_float(7);
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar11)))) - (fVar6 * ((float10) actor_word_real(0x00000000u))));
        fVar8 = actor_word_real(0x41200000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050(n.w[0x17], fVar8, fVar11);
        fVar7 = (float10) actor_word_real(0x43160000u);
        fVar13 = n.source_float(5);
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(7, (float) (((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar13)))) - (fVar6 * ((float10) actor_word_real(0x00000000u)))), fVar8, fVar11, fVar12, uVar14);
      }
      if ((n.w[0x2b7d] == 2) && (0x3c < n.w[0x2b81]))
      {
        n.FUN_00421100(3);
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_4_0_350(FullChargeBodyContext& n)
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
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.w[0x18] = 0;
          n.FUN_004223d0(0x20, 0xf, 0);
          n.FUN_00434bd0();
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.write_scratch(0x3a, 0);
          n.write_scratch(0x3b, 0);
          n.write_scratch(0x3c, 0);
        }
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        if ((((n.w[0x3a] % 6) == 0) && (0x22 < n.w[0x3a])) && (n.w[0x3a] < 0x3d))
        {
          n.FUN_0042c8b0(0x62);
          n.FUN_004230e0();
          n.FUN_004230e0();
          fVar13 = ((n.source_float(0x3a)) + actor_word_real(0x41f00000u)) - actor_word_real(0x420c0000u);
          fVar12 = ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x430c0000u);
          fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar12, fVar13);
          fVar11 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
          fVar10 = (n.source_float(6)) + actor_word_real(0x42c80000u);
          fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar10, fVar11);
          n.FUN_00435450(6, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar10, fVar11, fVar12, fVar13);
          fVar13 = ((n.source_float(0x3a)) + actor_word_real(0x41f00000u)) - actor_word_real(0x420c0000u);
          fVar12 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
          fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar12, fVar13);
          fVar11 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
          fVar10 = (n.source_float(6)) + actor_word_real(0x42c80000u);
          fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar10, fVar11);
          n.FUN_00435450(6, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar10, fVar11, fVar12, fVar13);
        }
        if (n.w[0x2b81] < 0x1e)
        {
          n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
          n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
        }
        if (0x55 < n.w[0x2b81])
        {
          n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
          n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_4_0_360(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_004223d0(0x20, 0xf, 0);
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
      }
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      if ((((n.w[0x3a] % 6) == 0) && (0x22 < n.w[0x3a])) && (n.w[0x3a] < 0x3d))
      {
        n.FUN_0042c8b0(0x62);
        n.FUN_004230e0();
        n.FUN_004230e0();
        fVar13 = ((n.source_float(0x3a)) + actor_word_real(0x41f00000u)) - actor_word_real(0x420c0000u);
        fVar12 = ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar12, fVar13);
        fVar11 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar10 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar10, fVar11);
        n.FUN_00435450(6, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar10, fVar11, fVar12, fVar13);
        fVar13 = ((n.source_float(0x3a)) + actor_word_real(0x41f00000u)) - actor_word_real(0x420c0000u);
        fVar12 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar12, fVar13);
        fVar11 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar10 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar10, fVar11);
        n.FUN_00435450(6, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar10, fVar11, fVar12, fVar13);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
        n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
      }
      if (0x55 < n.w[0x2b81])
      {
        n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
        n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_4_1_350(FullChargeBodyContext& n)
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
          n.write_scratch(0x3e, 0);
        }
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 3);
        if (n.w[0x2b81] < 0xf)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if ((n.w[0x2b7d] == 0) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if ((0xe < n.w[0x2b81]) && (n.w[0x3e] < 0x1e))
        {
          if (n.w[0x3e] == 0)
          {
            n.FUN_0042dc20(0, 0x40000000);
            if (n.w[0x1b7] < 0xb)
            {
              n.FUN_004223d0(0x1e, 10, 0);
            }
            else
            {
              n.FUN_004223d0(0x1b, 10, 0);
            }
            n.FUN_0042c8b0(0x66);
          }
          uVar3 = n.w[0x3e] & 0x80000001;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffffe) + 1;
          }
          if (uVar3 == 0)
          {
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3c, iVar4);
            uVar3 = n.FUN_0065d150();
            n.write_scratch(0x3a, uVar3 % 10);
            uVar3 = n.FUN_0065d150();
            n.write_scratch(0x3b, uVar3 % 10);
            if (n.w[0x3c] < (-0x28))
            {
              n.write_scratch(0x3c, -0x28);
            }
            if (0x28 < n.w[0x3c])
            {
              n.write_scratch(0x3c, 0x28);
            }
            n.FUN_004230e0();
            fVar12 = ((n.source_float(0x3b)) - actor_word_real(0x40a00000u)) + (n.source_float(0x3c));
            fVar13 = (n.source_float(0x3a)) - actor_word_real(0x40a00000u);
            uVar11 = 8;
            uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
            n.FUN_00435220(uVar5, uVar11, fVar13, fVar12);
          }
          if (n.w[0x3e] < 0x3c)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          }
        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_4_1_360(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x16] = 0x3e99999a;
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3e, 0);
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x10] = 0;
        return;
      }
      n.FUN_00434a70(0, 2);
      n.FUN_00434a70(1, 3);
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      if ((0xe < n.w[0x2b81]) && (n.w[0x3e] < 0x1e))
      {
        if (n.w[0x3e] == 0)
        {
          n.FUN_0042dc20(0, 0x40000000);
          n.w[0x18] = 0;
          n.w[0x15] = -0x3f600000;
          n.w[0x10] = 0x40a00000;
          if (n.w[0x1b7] < 0xb)
          {
            n.FUN_004223d0(0x1e, 10, 0);
          }
          else
          {
            n.FUN_004223d0(0x1b, 10, 0);
          }
          n.FUN_0042c8b0(0x66);
        }
        uVar3 = n.w[0x3e] & 0x80000001;
        if (((int) uVar3) < 0)
        {
          uVar3 = ((uVar3 - 1) | 0xfffffffe) + 1;
        }
        if (uVar3 == 0)
        {
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          uVar3 = n.FUN_0065d150();
          n.write_scratch(0x3a, uVar3 % 10);
          uVar3 = n.FUN_0065d150();
          n.write_scratch(0x3b, uVar3 % 10);
          if (n.w[0x3c] < (-0x28))
          {
            n.write_scratch(0x3c, -0x28);
          }
          if (0x28 < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x28);
          }
          n.FUN_004230e0();
          fVar12 = ((n.source_float(0x3b)) - actor_word_real(0x40a00000u)) + (n.source_float(0x3c));
          fVar13 = (n.source_float(0x3a)) - actor_word_real(0x40a00000u);
          uVar11 = 8;
          uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar5, uVar11, fVar13, fVar12);
        }
        if (n.w[0x3e] < 0x3c)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        }
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_4_2_350(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_004223d0(0x20, 0xf, 0);
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0x19)
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      if (n.w[0x3a] == 1)
      {
        n.FUN_0042c8b0(0x62);
        n.FUN_004230e0();
        n.FUN_004230e0();
        uVar15 = 0xc1f00000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0xc1f00000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
        uVar15 = 0x41f00000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0x41f00000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
      }
      if (n.w[0x3a] == 3)
      {
        n.FUN_0042c8b0(0x62);
        n.FUN_004230e0();
        n.FUN_004230e0();
        uVar15 = 0xc2480000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0xc2480000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
        uVar15 = 0x42480000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0x42480000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
      }
      if (n.w[0x3a] == 5)
      {
        n.FUN_0042c8b0(0x62);
        n.FUN_004230e0();
        n.FUN_004230e0();
        uVar15 = 0xc28c0000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0xc28c0000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
        uVar15 = 0x428c0000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0x428c0000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        if (n.w[0x3e] < 4)
        {
          n.write_clock(0x2b81, 0x1a);
          n.write_clock(0x2b82, 0x1a);
          if (n.w[0x3e] == 0)
          {
            n.write_scratch(0x3d, 1);
          }
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        }
        else
        {
          n.write_scratch(0x3e, 0);
        }
      }
      if (n.w[0x2b81] == 0x28)
      {
        n.write_scratch(0x3d, 2);
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_4_2_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_004223d0(0x20, 0xf, 0);
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0x19)
      {
        n.FUN_0042dc20(0, 0x41a00000);
      }
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      if (n.w[0x3a] == 1)
      {
        n.FUN_0042c8b0(0x62);
        n.FUN_004230e0();
        n.FUN_004230e0();
        uVar15 = 0xc1f00000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0xc1f00000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
        uVar15 = 0x41f00000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0x41f00000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
      }
      if (n.w[0x3a] == 3)
      {
        n.FUN_0042c8b0(0x62);
        n.FUN_004230e0();
        n.FUN_004230e0();
        uVar15 = 0xc2480000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0xc2480000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
        uVar15 = 0x42480000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0x42480000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
      }
      if (n.w[0x3a] == 5)
      {
        n.FUN_0042c8b0(0x62);
        n.FUN_004230e0();
        n.FUN_004230e0();
        uVar15 = 0xc28c0000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0xc28c0000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
        uVar15 = 0x428c0000;
        fVar14 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x430c0000u);
        fVar6 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar14, 0x428c0000);
        fVar13 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = (n.source_float(6)) + actor_word_real(0x42c80000u);
        fVar6 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), fVar9, fVar13);
        n.FUN_00435450(8, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar13, fVar14, uVar15);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        if (n.w[0x3e] < 4)
        {
          n.write_clock(0x2b81, 0x1a);
          n.write_clock(0x2b82, 0x1a);
          if (n.w[0x3e] == 0)
          {
            n.write_scratch(0x3d, 1);
          }
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        }
        else
        {
          n.write_scratch(0x3e, 0);
        }
      }
      if (n.w[0x2b81] == 0x28)
      {
        n.write_scratch(0x3d, 2);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_0_350(FullChargeBodyContext& n)
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
      if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 2))
      {
        if (actor_word_real(0x41700000u) < (n.source_float(0x15)))
        {
          n.w[0x15] = 0x41700000;
        }
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && ((n.FUN_0042db10(0, 0x41700000), n.w[0x2b81] == 0)))
      {
        n.FUN_0042c800(0);
        n.FUN_0042c840(9);
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.FUN_00422900();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_004223d0(0x21, 0x14, 0);
          n.FUN_0042c8b0(0x77);
          fVar7 = (float10) n.FUN_0042da80();
          local_14 = (float) fVar7;
          if (actor_word_real(0x42200000u) < local_14)
          {
            local_14 = 40.0;
          }
          if (local_14 < actor_word_real(0x00000000u))
          {
            local_14 = 0.0;
          }
          fVar7 = (float10) n.FUN_0065d050(local_14);
          n.w[0x15] = actor_real_word(float((float) (fVar7 * ((float10) actor_word_real(0x41c80000u)))));
          fVar7 = (float10) n.FUN_0065d010(local_14);
          n.w[0x10] = actor_real_word(float((float) (fVar7 * ((float10) actor_word_real(0x41c80000u)))));
          fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
          n.w[0xb] = actor_real_word(float((float) ((fVar7 / ((float10) actor_word_real(0x40490fdbu))) * ((float10) actor_word_real(0x43340000u)))));
          if ((n.source_float(0xb)) < actor_word_real(0x00000000u))
          {
            n.w[0xb] = 0;
          }
          n.w[0xb6] = 0x428c0000;
        }
        iVar4 = n.FUN_0066b65c((n.source_float(0x19)) < actor_word_real(0x42340000u));
        if (iVar4 != 0)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        uVar3 = n.w[0x2b81] & 0x80000003;
        if (((int) uVar3) < 0)
        {
          uVar3 = ((uVar3 - 1) | 0xfffffffc) + 1;
        }
        if (uVar3 == 0)
        {
          iVar4 = n.w[0xb];
          uVar15 = 0;
          uVar13 = 9;
          uVar6 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar6, uVar13, uVar15, iVar4);
        }
        if ((n.w[0x2b81] % 7) == 0)
        {
          n.FUN_0042c800(0);
        }
        if (0x3c < n.w[0x2b81])
        {
          n.FUN_0042c800(0);
          n.FUN_00421100(2);
          if (((char) n.w[0x21]) != '\0')
          {
            return;
          }
          n.FUN_00421080(0x169);
          return;
        }
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_0_360(FullChargeBodyContext& n)
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
      if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 2))
      {
        if (actor_word_real(0x41700000u) < (n.source_float(0x15)))
        {
          n.w[0x15] = 0x41700000;
        }
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && ((n.FUN_0042db10(0, 0x41700000), n.w[0x2b81] == 0)))
      {
        n.FUN_0042c800(0);
        n.FUN_0042c840(9);
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.FUN_00422900();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
        n.FUN_00423000();
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_004223d0(0x21, 0x14, 0);
          n.FUN_0042c8b0(0x77);
          fVar7 = (float10) n.FUN_0042da80();
          local_18 = (float) fVar7;
          if (actor_word_real(0x42200000u) < local_18)
          {
            local_18 = 40.0;
          }
          if (local_18 < actor_word_real(0xc2200000u))
          {
            local_18 = -40.0;
          }
          fVar7 = (float10) n.FUN_0065d050(local_18);
          n.w[0x15] = actor_real_word(float((float) (fVar7 * ((float10) actor_word_real(0x41c80000u)))));
          fVar7 = (float10) n.FUN_0065d010(local_18);
          n.w[0x10] = actor_real_word(float((float) (fVar7 * ((float10) actor_word_real(0x41c80000u)))));
          fVar7 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
          n.w[0xb] = actor_real_word(float((float) ((fVar7 / ((float10) actor_word_real(0x40490fdbu))) * ((float10) actor_word_real(0x43340000u)))));
          if ((n.source_float(0xb)) < actor_word_real(0x00000000u))
          {
            n.w[0xb] = 0;
          }
          n.w[0xb6] = 0x428c0000;
        }
        iVar4 = n.FUN_0066b65c((n.source_float(0x19)) < actor_word_real(0x42340000u));
        if (iVar4 != 0)
        {
          n.FUN_0042db10(0, 0x40000000);
        }
        uVar3 = n.w[0x2b81] & 0x80000003;
        if (((int) uVar3) < 0)
        {
          uVar3 = ((uVar3 - 1) | 0xfffffffc) + 1;
        }
        if (uVar3 == 0)
        {
          iVar4 = n.w[0xb];
          uVar15 = 0;
          uVar13 = 9;
          uVar6 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar6, uVar13, uVar15, iVar4);
        }
        if ((n.w[0x2b81] % 7) == 0)
        {
          n.FUN_0042c800(0);
        }
        if (0x3c < n.w[0x2b81])
        {
          n.FUN_0042c800(0);
          n.FUN_00421100(2);
          if (((char) n.w[0x21]) != '\0')
          {
            return;
          }
          n.FUN_00421080(0x169);
          return;
        }
        if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.FUN_0042c800(0);
          n.FUN_00421100(2);
          return;
        }
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_0_361(FullChargeBodyContext& n)
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
        n.w[0x16] = 0x3f000000;
        n.FUN_00421080(0x2b);
        return;
      }
      if (((char) n.w[0x21]) != '\0')
      {
        n.FUN_00421080(0x1d5);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3f000000u)));
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_1_350(FullChargeBodyContext& n)
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
        n.FUN_004223d0(0x20, 0x14, 0);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042dc20(0, 0x41a00000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_0042c8b0(0xa9);
        }
        if (n.w[0x2b81] == 0x5a)
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 5) == 0)) && (n.w[0x2b81] < 0x29))
      {
        uVar14 = 0;
        uVar13 = 0;
        uVar11 = 7;
        uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar4, uVar11, uVar13, uVar14);
      }
      if (((n.w[0x2b7d] == 1) && (0x27 < n.w[0x2b81])) && (((n.w[0x2b81] % 5) == 0) && (n.w[0x2b81] < 0x5b)))
      {
        if (n.w[0x2b81] == 0x28)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_0042c8b0(0x7a);
        }
        uVar14 = 0;
        uVar13 = 0;
        uVar11 = 9;
        uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar4, uVar11, uVar13, uVar14);
        uVar4 = 0;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
        fVar10 = (float) ((fVar6 * ((float10) actor_word_real(0x43fa0000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
        n.FUN_00435450(6, (float) ((fVar6 * ((float10) actor_word_real(0x43fa0000u))) + ((float10) (n.source_float(5)))), fVar9, fVar10, fVar12, uVar4);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_1_360(FullChargeBodyContext& n)
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
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && (0 < n.w[0x2b81]))
      {
        n.FUN_00421080(0x193);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_004223d0(0x20, 0x14, 0);
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042dc20(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.w[0x10] = 0;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042dc20(0, 0x41a00000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_0042c8b0(0xa9);
        }
        if (n.w[0x2b81] == 0x5a)
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 5) == 0)) && (n.w[0x2b81] < 0x29))
      {
        uVar14 = 0;
        uVar13 = 0;
        uVar11 = 7;
        uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar4, uVar11, uVar13, uVar14);
      }
      if (((n.w[0x2b7d] == 1) && (0x27 < n.w[0x2b81])) && (((n.w[0x2b81] % 5) == 0) && (n.w[0x2b81] < 0x5b)))
      {
        if (n.w[0x2b81] == 0x28)
        {
          n.FUN_0042c8b0(0x7a);
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
        }
        uVar14 = 0;
        uVar13 = 0;
        uVar11 = 9;
        uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar4, uVar11, uVar13, uVar14);
        uVar4 = 0;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
        fVar10 = (float) ((fVar6 * ((float10) actor_word_real(0x43fa0000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
        n.FUN_00435450(6, (float) ((fVar6 * ((float10) actor_word_real(0x43fa0000u))) + ((float10) (n.source_float(5)))), fVar9, fVar10, fVar12, uVar4);
      }
      if ((n.source_float(0x16)) == actor_word_real(0x00000000u))
      {
        n.w[0x16] = 0x3f000000;
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_2_350(FullChargeBodyContext& n)
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
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.write_scratch(0x3e, 0);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0xd))
        {
          n.FUN_0042dc20(0, 0x41a00000);
        }
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 2)) || (n.w[0x2b7d] == 4))
        {
          if (n.w[0x2b81] == 0xc)
          {
            if (n.w[0x2b7d] == 0)
            {
              n.FUN_0042c8b0(0xb9);
            }
            n.FUN_0042c8b0(0xb8);
            n.FUN_004230e0();
            if (n.w[0x2b7d] == 0)
            {
              if (n.w[0x1b7] == 1)
              {
                n.FUN_004223d0(0x1e, 10, 0);
              }
              else
              {
                n.FUN_004223d0(0x1d, 10, 0);
              }
            }
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3c, iVar4);
            if (n.w[0x3c] < (-0x14))
            {
              n.write_scratch(0x3c, -0x14);
            }
            if (0x14 < n.w[0x3c])
            {
              n.write_scratch(0x3c, 0x14);
            }
            if (n.w[0x2b7d] == 0)
            {
              fVar16 = n.source_float(0x3c);
              fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
              fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
              fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
              fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
              fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
              n.FUN_00435450(7, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
            }
            if (n.w[0x2b7d] == 2)
            {
              fVar16 = n.source_float(0x3c);
              fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
              fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
              fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
              fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
              fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
              n.FUN_00435450(9, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
            }
            if (n.w[0x2b7d] == 4)
            {
              fVar16 = n.source_float(0x3c);
              fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
              fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
              fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
              fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
              fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
              n.FUN_00435450(0xb, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
            }
          }
          if (0xf < n.w[0x2b81])
          {
            n.FUN_00421100(n.w[0x2b7d] + 1);
            return;
          }
          if ((n.w[0x2b7d] != 0) || (9 < n.w[0x2b81]))
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
        }
        if (((n.w[0x2b7d] == 1) || (n.w[0x2b7d] == 3)) || (n.w[0x2b7d] == 5))
        {
          if (n.w[0x2b81] == 0xc)
          {
            n.FUN_0042c8b0(0xb8);
            n.FUN_004230e0();
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3c, iVar4);
            if (n.w[0x3c] < (-0x14))
            {
              n.write_scratch(0x3c, -0x14);
            }
            if (0x14 < n.w[0x3c])
            {
              n.write_scratch(0x3c, 0x14);
            }
            if (n.w[0x2b7d] == 1)
            {
              fVar16 = n.source_float(0x3c);
              fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
              fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
              fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
              fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
              fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
              n.FUN_00435450(8, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
            }
            if (n.w[0x2b7d] == 3)
            {
              fVar16 = n.source_float(0x3c);
              fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
              fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
              fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
              fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
              fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
              n.FUN_00435450(10, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
            }
            if (n.w[0x2b7d] == 5)
            {
              fVar16 = n.source_float(0x3c);
              fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
              fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
              fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
              fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
              fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
              n.FUN_00435450(0xc, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
            }
          }
          if ((6 < n.w[0x2b81]) && (n.w[0x2b81] < 0xc))
          {
            n.write_clock(0x2b81, 0xc);
            n.write_clock(0x2b82, 0xc);
            return;
          }
          if ((0x14 < n.w[0x2b81]) && (n.w[0x2b7d] < 5))
          {
            n.FUN_00421100(n.w[0x2b7d] + 1);
            return;
          }
          if ((n.w[0x2b7d] != 5) || (n.w[0x2b81] < 0xd))
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          if (((n.w[0x2b7d] == 5) && (n.w[0x2b81] == 0x1a)) && (n.w[0x3e] < 0xf))
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
        }
        n.FUN_00434b90(0);
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_2_360(FullChargeBodyContext& n)
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
      n.FUN_00434a70(0, 2);
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u))) && (n.w[0x2b7d] == 5)) && (0x1e < n.w[0x2b81]))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) * actor_word_real(0x3e800000u)));
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0xd))
      {
        n.FUN_0042dc20(0, 0x41a00000);
      }
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 2)) || (n.w[0x2b7d] == 4))
      {
        if (n.w[0x2b81] == 0xc)
        {
          if (n.w[0x2b7d] == 0)
          {
            n.FUN_0042c8b0(0xb9);
          }
          n.FUN_0042c8b0(0xb8);
          n.FUN_004230e0();
          if (n.w[0x2b7d] == 0)
          {
            if (n.w[0x1b7] == 1)
            {
              n.FUN_004223d0(0x1e, 10, 0);
            }
            else
            {
              n.FUN_004223d0(0x1d, 10, 0);
            }
          }
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x14))
          {
            n.write_scratch(0x3c, -0x14);
          }
          if (0x14 < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x14);
          }
          if (n.w[0x2b7d] == 0)
          {
            fVar16 = n.source_float(0x3c);
            fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
            fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
            fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
            n.FUN_00435450(7, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
          }
          if (n.w[0x2b7d] == 2)
          {
            fVar16 = n.source_float(0x3c);
            fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
            fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
            fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
            n.FUN_00435450(9, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
          }
          if (n.w[0x2b7d] == 4)
          {
            fVar16 = n.source_float(0x3c);
            fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
            fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
            fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
            n.FUN_00435450(0xb, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
          }
        }
        if (0xf < n.w[0x2b81])
        {
          n.FUN_00421100(n.w[0x2b7d] + 1);
          return;
        }
        if ((n.w[0x2b7d] != 0) || (9 < n.w[0x2b81]))
        {
          n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
          n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
        }
      }
      if (((n.w[0x2b7d] == 1) || (n.w[0x2b7d] == 3)) || (n.w[0x2b7d] == 5))
      {
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c8b0(0xb8);
          n.FUN_004230e0();
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x14))
          {
            n.write_scratch(0x3c, -0x14);
          }
          if (0x14 < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x14);
          }
          if (n.w[0x2b7d] == 1)
          {
            fVar16 = n.source_float(0x3c);
            fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
            fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
            fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
            n.FUN_00435450(8, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
          }
          if (n.w[0x2b7d] == 3)
          {
            fVar16 = n.source_float(0x3c);
            fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
            fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
            fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
            n.FUN_00435450(10, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
          }
          if (n.w[0x2b7d] == 5)
          {
            fVar16 = n.source_float(0x3c);
            fVar15 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar15, fVar16);
            fVar13 = (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(7))));
            fVar11 = actor_word_real(0x42c80000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar13);
            n.FUN_00435450(0xc, (float) ((fVar7 * ((float10) actor_word_real(0x41200000u))) + ((float10) (n.source_float(5)))), fVar11, fVar13, fVar15, fVar16);
          }
        }
        if ((6 < n.w[0x2b81]) && (n.w[0x2b81] < 0xc))
        {
          n.write_clock(0x2b81, 0xc);
          n.write_clock(0x2b82, 0xc);
          return;
        }
        if ((0x14 < n.w[0x2b81]) && (n.w[0x2b7d] < 5))
        {
          n.FUN_00421100(n.w[0x2b7d] + 1);
          return;
        }
        if ((n.w[0x2b7d] != 5) || (n.w[0x2b81] < 0xd))
        {
          n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
          n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
        }
        if (((n.w[0x2b7d] == 5) && (n.w[0x2b81] == 0x1a)) && (n.w[0x3e] < 0xf))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
      }
      n.FUN_00434b90(0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_5_2_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.w[0x16] = 0x3f000000;
        n.FUN_00421080(0x2b);
        return;
      }
      if (((char) n.w[0x21]) != '\0')
      {
        n.FUN_00421080(0x1d5);
        n.w[0x10] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3f000000u)));
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_6_0_350(FullChargeBodyContext& n)
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
        n.FUN_00422300(0x21, 0, 0x14, 0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0x1d)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x1e)
      {
        if (n.w[0x3e] == 0)
        {
          n.FUN_0042c8b0(0x7f);
        }
        n.FUN_0042c8b0(0x7c);
        n.FUN_004230e0();
        uVar12 = 0;
        fVar8 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
        n.FUN_00435450(4, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar9, fVar10, fVar8, uVar12);
        uVar12 = 0;
        fVar8 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
        n.FUN_00435450(5, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar9, fVar10, fVar8, uVar12);
      }
      if (n.w[0x2b81] == 0x1c)
      {
        if (n.w[0x3e] < 0x23)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0x24)
      {
        if (n.w[0x3e] < 5)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          n.write_clock(0x2b81, 0x1e);
          n.write_clock(0x2b82, 0x1e);
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x3c) && (n.w[0x3e] < 0x23))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_6_0_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00422300(0x21, 0, 0x14, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
      }
      if (n.w[0x2b81] < 0x1d)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      if ((0x27 < n.w[0x2b81]) && (0x37 < n.w[0x3e]))
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      if (n.w[0x2b81] == 0x1e)
      {
        if (n.w[0x3e] == 0)
        {
          n.FUN_0042c8b0(0x7f);
        }
        n.FUN_0042c8b0(0x7c);
        n.FUN_004230e0();
        uVar12 = 0;
        fVar8 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
        n.FUN_00435450(4, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar9, fVar10, fVar8, uVar12);
        uVar12 = 0;
        fVar8 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
        n.FUN_00435450(5, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar9, fVar10, fVar8, uVar12);
      }
      if (n.w[0x2b81] == 0x1c)
      {
        if (n.w[0x3e] < 0x23)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0x24)
      {
        if (n.w[0x3e] < 5)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          n.write_clock(0x2b81, 0x1e);
          n.write_clock(0x2b82, 0x1e);
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x3c) && (n.w[0x3e] < 0x23))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_6_1_350(FullChargeBodyContext& n)
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
      if (n.w[0x2b81] < 0x31)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 0xffffffff);
      }
      else
      {
        n.FUN_00434a70(0, 0);
        n.FUN_00434a70(1, 1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.FUN_0042c840(1);
        n.FUN_0042c800(0);
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x10] = 0;
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0x1a) || (0x2b < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
      }
      if (n.w[0x2b81] < 0x19)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f400000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x19)
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0x41b40000;
        n.FUN_0042c8b0(0x41);
      }
      if (n.w[0x2b81] == 0x31)
      {
        n.FUN_0042c8b0(0x7d);
        n.FUN_0042da80();
        iVar3 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar3);
        if (n.w[0x3c] < (-0x1e))
        {
          n.write_scratch(0x3c, -0x1e);
        }
        if (0x1e < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x1e);
        }
        n.FUN_004230e0();
        fVar11 = n.source_float(0x3c);
        uVar14 = 0;
        uVar12 = 6;
        uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar4, uVar12, uVar14, fVar11);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_6_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
        n.FUN_0042c840(1);
        n.FUN_0042c800(0);
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x10] = 0;
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
      }
      if (n.w[0x2b81] < 0x31)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 0xffffffff);
      }
      else
      {
        n.FUN_00434a70(0, 0);
        n.FUN_00434a70(1, 1);
      }
      if ((n.w[0x2b81] < 0x1a) || (0x2b < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
      }
      if (n.w[0x2b81] < 0x19)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      if ((n.w[0x2b81] < 0x1a) || (0x30 < n.w[0x2b81]))
      {
        n.w[0xc] = 0;
      }
      else
      {
        n.w[0xc] = actor_real_word(float((n.source_float(0xc)) + actor_word_real(0x40a00000u)));
      }
      if (n.w[0x2b81] < 0x31)
      {
        fVar6 = (float10) n.FUN_0042da80();
        local_14 = (float) fVar6;
        if (actor_word_real(0x41f00000u) < local_14)
        {
          local_14 = 30.0;
        }
        if (local_14 < actor_word_real(0xc1f00000u))
        {
          local_14 = -30.0;
        }
        n.w[0xb] = actor_real_word(float(local_14));
        n.w[0xb6] = 0x428c0000;
      }
      n.w[0x16] = 0x3f000000;
      if (n.w[0x2b81] == 0x31)
      {
        n.w[0x18] = 0;
        n.w[0x15] = -0x3ee00000;
        n.w[0x10] = 0x40a00000;
        n.FUN_0042c8b0(0x7d);
        n.FUN_0042da80();
        iVar3 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar3);
        if (n.w[0x3c] < (-0x1e))
        {
          n.write_scratch(0x3c, -0x1e);
        }
        if (0x1e < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x1e);
        }
        n.FUN_004230e0();
        fVar11 = n.source_float(0x3c);
        uVar14 = 0;
        uVar12 = 6;
        uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar4, uVar12, uVar14, fVar11);
      }
      if (n.w[0x2b81] < 0x32)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3e800000u)));
      }
      else
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        if (0x3c < n.w[0x2b81])
        {
          if ((actor_word_real(0x00000000u) < (n.source_float(0xb))) && ((n.w[0xb] = actor_real_word(float((n.source_float(0xb)) - actor_word_real(0x40000000u))), (n.source_float(0xb)) < actor_word_real(0x00000000u))))
          {
            n.w[0xb] = 0;
          }
          if (((n.source_float(0xb)) < actor_word_real(0x00000000u)) && ((n.w[0xb] = actor_real_word(float((n.source_float(0xb)) + actor_word_real(0x40000000u))), actor_word_real(0x00000000u) < (n.source_float(0xb)))))
          {
            n.w[0xb] = 0;
          }
        }
        if (((char) n.w[0x21]) != '\0')
        {
          n.w[0x10] = 0;
          n.w[0x15] = 0;
          n.FUN_00421080(0x1d5);
          return;
        }
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_6_2_350(FullChargeBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (n.source_float(0x1a))) && ((n.w[0x1a] = actor_real_word(float((n.source_float(0x1a)) - actor_word_real(0x41200000u))), (n.source_float(0x1a)) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((n.source_float(0x1a)) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((n.source_float(0x1a)) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (n.source_float(0x1a)))))
  {
    n.w[0x1a] = 0;
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
        if (n.w[0x2b7d] != 1)
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3f000000u)));
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.FUN_0042c840(99);
        n.FUN_0042c800(0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] < 0x1d)
        {
          n.FUN_0042db10(0, 0x41900000);
        }
        if (n.w[0x2b81] == 0x1e)
        {
          n.w[0x15] = 0x41a00000;
          n.FUN_0042c8b0(0xe7);
          n.FUN_00422300(0x13, 1, 0x14, 0);
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        if ((n.w[0x2b81] % 0x14) == 0)
        {
          n.FUN_0042c8b0(0xe8);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && ((n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1)), 0x1e < n.w[0x3e])))
        {
          n.write_scratch(0x3e, 0);
          n.FUN_0042c800(0);
        }
        if (((char) n.w[0x21]) != '\0')
        {
          if ((n.w[0x2b81] % 3) == 0)
          {
            n.FUN_00435450(9, n.w[5], n.w[6], n.w[7], 0, 0);
          }
          n.w[0x10] = 0;
          if (300 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        n.w[0x21d] = 0x40000000;
        n.FUN_00421780();
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_6_2_360(FullChargeBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (n.source_float(0x1a))) && ((n.w[0x1a] = actor_real_word(float((n.source_float(0x1a)) - actor_word_real(0x41200000u))), (n.source_float(0x1a)) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((n.source_float(0x1a)) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((n.source_float(0x1a)) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (n.source_float(0x1a)))))
  {
    n.w[0x1a] = 0;
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
        if (n.w[0x2b7d] == 1)
        {
          n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3f000000u)));
        }
        else
          if (n.w[0x2b7d] == 2)
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c840(99);
        n.FUN_0042c800(0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] < 0x1d)
        {
          n.FUN_0042db10(0, 0x41900000);
        }
        if (n.w[0x2b81] == 0x1e)
        {
          n.w[0x15] = 0x41a00000;
          n.FUN_0042c8b0(0xe7);
          n.FUN_00422300(0x13, 1, 0x14, 0);
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        if ((n.w[0x2b81] % 0x14) == 0)
        {
          n.FUN_0042c8b0(0xe8);
        }
        sVar2 = n.FUN_0042c7b0();
        if ((sVar2 != 0) && ((n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1)), 0x1e < n.w[0x3e])))
        {
          n.write_scratch(0x3e, 0);
          n.FUN_0042c800(0);
        }
        if (((char) n.w[0x21]) != '\0')
        {
          if ((n.w[0x2b81] % 3) == 0)
          {
            n.FUN_00435450(9, n.w[5], n.w[6], n.w[7], 0, 0);
          }
          n.w[0x10] = 0;
          if (300 < n.w[0x2b81])
          {
            n.FUN_00421100(2);
            return;
          }
        }
        n.w[0x21d] = 0x40000000;
        n.FUN_00421780();
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_0_350(FullChargeBodyContext& n)
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
        if ((9 < n.w[0x2b81]) && (n.w[0x2b81] < 0x1e))
        {
          n.FUN_00434a70(1, 0xffffffff);
          n.FUN_00434a70(0, 2);
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b81] < 0xf)
        {
          n.FUN_0042db10(0, 0x41800000);
        }
        if (n.w[0x2b81] < 0x1e)
        {
          n.FUN_0042db10(0, 0x40800000);
        }
        if ((0x11 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3eb33333u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.w[0x15] = 0;
          n.write_scratch(0x3d, 0);
          n.write_scratch(0x3e, 0);
          n.FUN_004223d0(0x20, 0x14, 0);
        }
        if (n.w[0x2b81] == 0x1e)
        {
          n.w[0x18] = 0;
          n.w[0x15] = -0x3e900000;
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3a, iVar4);
          if (n.w[0x3a] < (-0x28))
          {
            n.write_scratch(0x3a, -0x28);
          }
          if (0x28 < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0x28);
          }
          n.FUN_0042c8b0(0x81);
          n.FUN_004230e0();
          n.FUN_00434fd0(8, 0, n.source_float(0x3a), 0);
          n.write_scratch(0x3d, actor_word_add(n.w[0x3d], 1));
        }
        if (n.w[0x2b81] == 0x1d)
        {
          if (n.w[0x3e] < 0)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_0_360(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u))) && (0x1e < n.w[0x2b81]))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.w[0x10] = 0;
        n.FUN_004223d0(0x20, 0x14, 0);
      }
      if ((9 < n.w[0x2b81]) && (n.w[0x2b81] < 0x1e))
      {
        n.FUN_00434a70(1, 0xffffffff);
        n.FUN_00434a70(0, 2);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41500000);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042db10(0, 0x40000000);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        n.write_scratch(0x3d, actor_word_add(n.w[0x3d], 1));
        n.w[0x18] = 0;
        n.w[0x15] = -0x3ee00000;
        n.w[0x10] = 0x40a00000;
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3a, iVar4);
        if (n.w[0x3a] < (-0x28))
        {
          n.write_scratch(0x3a, -0x28);
        }
        if (0x28 < n.w[0x3a])
        {
          n.write_scratch(0x3a, 0x28);
        }
        n.FUN_0042c8b0(0x81);
        n.FUN_004230e0();
        n.FUN_00434fd0(8, 0, n.source_float(0x3a), 0);
      }
      n.w[0x16] = 0x3f000000;
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3e19999au)));
      if (n.w[0x2b81] == 0x1d)
      {
        if (n.w[0x3e] < 0)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_0_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_1_350(FullChargeBodyContext& n)
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
          n.w[0x2bdb] = 1;
          n.FUN_004223d0(0x21, 0x14, 0);
        }
        if (n.w[0x2b81] < 0x12)
        {
          n.FUN_0042db10(0, 0x41200000);
        }
        if (n.w[0x2b7d] == 0)
        {
          n.FUN_0042db10(0, 0x41700000);
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
          if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
          {
            n.w[0x15] = 0;
          }
        }
        if (n.w[0x2b81] == 0x11)
        {
          n.FUN_0042c8b0(0x9a);
          n.FUN_004230e0();
          uVar13 = 0x41f00000;
          uVar11 = 0;
          uVar10 = 0xf;
          uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar4, uVar10, uVar11, uVar13);
        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_1_360(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.FUN_00422900();
        n.w[0x2bdb] = 1;
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      if (n.w[0x2b81] == 0x11)
      {
        n.FUN_0042c8b0(0x9a);
        n.FUN_004230e0();
        uVar13 = 0x41f00000;
        uVar11 = 0;
        uVar10 = 0xf;
        uVar4 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar4, uVar10, uVar11, uVar13);
      }
      if (0x23 < n.w[0x2b81])
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        n.w[0x16] = 0x3f000000;
        if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.FUN_00421080(0x169);
          return;
        }
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_1_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_2_350(FullChargeBodyContext& n)
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
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] < 0xf)
        {
          n.FUN_0042db10(0, 0x41800000);
        }
        if (n.w[0x2b81] < 0x17)
        {
          n.FUN_0042db10(0, 0x40800000);
        }
        if (n.w[0x2b81] == 0)
        {
          n.w[0x18] = 0;
          n.w[0x15] = 0;
          n.write_scratch(0x3d, 0);
          n.write_scratch(0x3e, 0);
          n.FUN_004223d0(0x20, 0x14, 0);
        }
        if (n.w[0x2b81] == 0x17)
        {
          n.w[0x18] = 0;
          n.FUN_0042c8b0(0xc1);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3a, iVar4);
          if (n.w[0x3a] < (-0x14))
          {
            n.write_scratch(0x3a, -0x14);
          }
          if (0x14 < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0x14);
          }
          n.write_scratch(0x3e, 0);
          while (n.w[0x3e] < 7)
          {
            n.FUN_004230e0();
            uVar13 = 0;
            fVar12 = (float) (n.w[0x3e] + n.w[0x3a]);
            uVar3 = n.FUN_0065d150(fVar12, 0);
            n.FUN_00435000(0, 8, ((float) (uVar3 % 0x14)) - actor_word_real(0x41200000u), fVar12, uVar13);
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          }

        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_2_360(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u))) && (0x1e < n.w[0x2b81]))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.w[0x10] = 0;
        n.FUN_004223d0(0x20, 0x14, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41500000);
      }
      if (n.w[0x2b81] < 0x17)
      {
        n.FUN_0042db10(0, 0x40000000);
      }
      if (n.w[0x2b81] == 0x17)
      {
        n.w[0x18] = 0;
        n.FUN_0042c8b0(0xc1);
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3a, iVar4);
        if (n.w[0x3a] < (-0x14))
        {
          n.write_scratch(0x3a, -0x14);
        }
        if (0x14 < n.w[0x3a])
        {
          n.write_scratch(0x3a, 0x14);
        }
        n.write_scratch(0x3e, 0);
        while (n.w[0x3e] < 7)
        {
          n.FUN_004230e0();
          uVar13 = 0;
          fVar12 = (float) (n.w[0x3e] + n.w[0x3a]);
          uVar3 = n.FUN_0065d150(fVar12, 0);
          n.FUN_00435000(0, 8, ((float) (uVar3 % 0x14)) - actor_word_real(0x41200000u), fVar12, uVar13);
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        }

      }
      n.w[0x16] = 0x3f000000;
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3e19999au)));
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_7_2_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_0_350(FullChargeBodyContext& n)
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if (n.w[0x2b81] < 0xe)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.FUN_004230e0();
        n.FUN_0042c8b0(0xa5);
        n.FUN_004223d0(0x21, 0x14, 0);
        n.FUN_0042da80();
        iVar5 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar5);
        if (n.w[0x3c] < (-0x28))
        {
          n.write_scratch(0x3c, -0x28);
        }
        if (0x28 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x28);
        }
        n.FUN_00434fd0(6, 0, n.source_float(0x3c), 0);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_0_351(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_8_0_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.FUN_004230e0();
        n.FUN_0042c8b0(0xa5);
        n.FUN_004223d0(0x21, 0x14, 0);
        n.FUN_0042da80();
        iVar5 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar5);
        if (n.w[0x3c] < (-0x28))
        {
          n.write_scratch(0x3c, -0x28);
        }
        if (0x28 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x28);
        }
        n.FUN_00434fd0(6, 0, n.source_float(0x3c), 0);
      }
      n.w[0x16] = 0x3f000000;
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_1_350(FullChargeBodyContext& n)
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
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422900();
        n.FUN_00423000();
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.w[0x18] = 0;
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.write_scratch(0x3a, 0);
        n.w[0x15] = 0x418c0000;
      }
      if (n.w[0x2b7d] == 1)
      {
        n.FUN_0042db10(0, 0x40a00000);
        fVar5 = (float10) n.FUN_0042d980();
        if ((fVar5 < ((float10) actor_word_real(0x469c4000u))) || (0x19 < n.w[0x2b81]))
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        if (n.w[0x2b81] == 6)
        {
          n.w[0x15] = 0;
          n.FUN_004223d0(1, 10, 0);
        }
        uVar3 = n.FUN_0042c7b0();
        if (((uVar3 & 1) != 0) && ((cVar1 = n.FUN_00422950(0xbe, 1, 0), cVar1 != '\0')))
        {
          n.FUN_00421080(0x15f);
          n.w[0x1eb] = 0x3c;
        }
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_1_351(FullChargeBodyContext& n)
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
      if (n.w[0x1eb] < 0x1c)
      {
        n.w[0x1eb] = 0x1e;
      }
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if ((((char) n.w[0x21]) == '\0') && (1 < n.w[0x2b7d]))
      {
        n.FUN_00421080(0x2b);
        n.w[0x10] = 0;
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] == 1)
        {
          n.FUN_004223d0(0x20, 0x14, 0);
        }
        n.FUN_0042c840(1);
        n.FUN_0042c800(0);
        n.FUN_0042db10(0x43340000, 0x40a00000);
        if (n.w[0x2b81] == 0x12)
        {
          n.w[0x18] = 0x43340000;
          n.w[0x10] = 0x42960000;
          n.w[0x15] = 0x41200000;
        }
        if (0x12 < n.w[0x2b81])
        {
          n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x40000000u)));
        }
        if ((n.w[0x2b81] == 0x13) && (actor_word_real(0x40800000u) < (n.source_float(0x10))))
        {
          return;
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x40000000u)));
        n.w[0xc] = actor_real_word(float((n.source_float(0xc)) + actor_word_real(0x41200000u)));
        if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.w[0xc] = 0;
          n.FUN_0042c8b0(0x85);
          n.FUN_00434fd0(3, 0, 0, 0);
          n.particle(300, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
          n.particle(0x136, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
          n.FUN_00421100(2);
          n.FUN_00422bd0(0x79, 0xc4, 5000, 1, 0, 0, 0);
          n.w[0x2bd8] = 0;
          n.w[0x10] = 0;
          return;
        }
      }
      if ((0 < n.w[0x2b7d]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        n.w[0xb] = 0;
        return;
      }
      if ((n.source_float(0x16)) == actor_word_real(0x00000000u))
      {
        n.w[0x16] = 0x3f000000;
      }
      if ((n.w[0x2b7d] == 2) && (10 < n.w[0x2b81]))
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      if (((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] == 2)) && (10 < n.w[0x2b81]))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0xb] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.FUN_00422900();
        n.FUN_00423000();
        if ((n.source_float(0x10)) <= actor_word_real(0x40400000u))
        {
          local_4c = n.source_float(0x10);
        }
        else
        {
          local_4c = 3.0;
        }
        if (actor_word_real(0xc0400000u) <= local_4c)
        {
          if ((n.source_float(0x10)) <= actor_word_real(0x40400000u))
          {
            local_54 = n.w[0x10];
          }
          else
          {
            local_54 = 0x40400000;
          }
          local_50 = local_54;
        }
        else
        {
          local_50 = -0x3fc00000;
        }
        n.w[0x10] = local_50;
        n.write_scratch(0x3c, 1);
        n.FUN_0042db10(0, 0x43340000);
        fVar5 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
        local_10 = (float) ((fVar5 / ((float10) actor_word_real(0x40490fdbu))) * ((float10) actor_word_real(0x43340000u)));
        fVar5 = (float10) n.FUN_0042da80();
        fVar11 = (float) (fVar5 + ((float10) actor_word_real(0x41200000u)));
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          fVar5 = (float10) n.FUN_0042da80();
          local_10 = (float) (fVar5 + ((float10) actor_word_real(0x41200000u)));
        }
        if ((fVar11 < local_10) && ((local_10 = local_10 - actor_word_real(0x40a00000u), local_10 < fVar11)))
        {
          local_10 = fVar11;
        }
        if ((local_10 < fVar11) && ((local_10 = local_10 + actor_word_real(0x40a00000u), fVar11 < local_10)))
        {
          local_10 = fVar11;
        }
        if (actor_word_real(0x42200000u) < local_10)
        {
          local_10 = 40.0;
        }
        if (local_10 < actor_word_real(0xc20c0000u))
        {
          local_10 = -35.0;
        }
        fVar5 = (float10) n.FUN_0065d050(local_10);
        n.w[0x15] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x41780000u)))));
        fVar5 = (float10) n.FUN_0065d010(local_10);
        n.w[0x10] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x41780000u)))));
        fVar5 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
        n.w[0xb] = actor_real_word(float((float) (((fVar5 / ((float10) actor_word_real(0x40490fdbu))) * ((float10) actor_word_real(0x43340000u))) + ((float10) actor_word_real(0x41a00000u)))));
        n.w[0xb6] = 0x428c0000;
      }
      n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
      if ((n.w[0x2b7d] < 2) && (n.w[0x3c] == 1))
      {
        n.FUN_0042db10(0, 0x40000000);
      }
      if ((n.w[0x2b7d] == 1) && (7 < n.w[0x2b81]))
      {
        fVar5 = (float10) n.FUN_0042d980();
        fVar6 = (float10) n.FUN_0042da30();
        fVar7 = (float10) n.FUN_0042da30();
        if ((((fVar7 * ((float10) ((float) fVar6))) + ((float10) ((float) fVar5))) < ((float10) actor_word_real(0x47435000u))) || (0xf < n.w[0x2b81]))
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        uVar3 = n.FUN_0042c7b0();
        if (((uVar3 & 1) != 0) && ((cVar1 = n.FUN_00422950(0xbe, 1, 0), cVar1 != '\0')))
        {
          n.w[0x1eb] = 0x1e;
          n.FUN_00421080(0x169);
          return;
        }
        if (0x14 < n.w[0x2b81])
        {
          if ((actor_word_real(0x00000000u) < (n.source_float(0xb))) && ((n.w[0xb] = actor_real_word(float((n.source_float(0xb)) - actor_word_real(0x40a00000u))), (n.source_float(0xb)) < actor_word_real(0x00000000u))))
          {
            n.w[0xb] = 0;
          }
          if (((n.source_float(0xb)) < actor_word_real(0x00000000u)) && ((n.w[0xb] = actor_real_word(float((n.source_float(0xb)) + actor_word_real(0x40a00000u))), actor_word_real(0x00000000u) < (n.source_float(0xb)))))
          {
            n.w[0xb] = 0;
          }
        }
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_1_361(FullChargeBodyContext& n)
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
      if (n.w[0x1eb] < 0x1c)
      {
        n.w[0x1eb] = 0x1e;
      }
      n.FUN_004218c0();
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_00421080(0x15f);
        return;
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3f000000u)));
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_1_362(FullChargeBodyContext& n)
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
      n.w[0x1eb] = 0x1e;
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x15f);
        return;
      }
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      n.w[0x15] = 0;
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_2_350(FullChargeBodyContext& n)
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
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x27, 1, 0x14, 0);
        n.FUN_0042c800(0);
        n.w[0x18] = 0;
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.write_scratch(0x3a, 0);
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x14)
      {
        uVar3 = n.FUN_0065d150();
        n.w[0x2bd8] = actor_word_add(uVar3 % 3, 7);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_2_360(FullChargeBodyContext& n)
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
      if (((char) n.w[0x21]) != '\0')
      {
        n.FUN_00421080(0x16a);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x27, 1, 0x14, 0);
        n.FUN_0042c800(0);
        n.w[0x18] = 0;
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.write_scratch(0x3a, 0);
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3f000000u)));
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) * actor_word_real(0x3f000000u)));
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      if (n.w[0x2b81] == 0x14)
      {
        uVar3 = n.FUN_0065d150();
        n.w[0x2bd8] = actor_word_add(uVar3 % 3, 7);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_8_2_362(FullChargeBodyContext& n)
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
      n.w[0x1eb] = 0x1e;
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
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_9_0_350(FullChargeBodyContext& n)
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
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.write_scratch(0x3a, 0);
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
      }
      else
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f800000u)));
        if (actor_word_real(0x00000000u) < (n.source_float(0x15)))
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b81] == 10)
      {
        if (n.w[0x3a] < 5)
        {
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], -2));
          n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], -2));
          return;
        }
        n.write_scratch(0x3a, 0);
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.FUN_0042c8b0(0x88);
        n.w[0x18] = 0;
        n.FUN_00422490(0x20, 2, 10, 0);
        n.FUN_0042da80();
        iVar5 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar5);
        if (n.w[0x3c] < (-0x2d))
        {
          n.write_scratch(0x3c, -0x2d);
        }
        if (0x2d < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x2d);
        }
      }
      if (n.w[0x2b81] == 0x10)
      {
        n.FUN_004230e0();
        n.FUN_00434fd0(8, 0, n.source_float(0x3c), 0);
      }
      if ((n.w[0x2b81] == 0x11) && (n.w[0x3a] < 10))
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_9_0_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.w[0x10] = 0;
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
      }
      else
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f800000u)));
        if (actor_word_real(0x00000000u) < (n.source_float(0x15)))
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b81] == 10)
      {
        if (n.w[0x3a] < 5)
        {
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], -2));
          n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], -2));
          return;
        }
        n.write_scratch(0x3a, 0);
      }
      if (n.w[0x2b81] == 0xf)
      {
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_0042c8b0(0x88);
        n.w[0x18] = 0;
        n.FUN_00422490(0x20, 2, 10, 0);
        n.FUN_0042da80();
        iVar5 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar5);
        if (n.w[0x3c] < (-0x2d))
        {
          n.write_scratch(0x3c, -0x2d);
        }
        if (0x2d < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x2d);
        }
      }
      if (n.w[0x2b81] == 0x10)
      {
        n.FUN_004230e0();
        n.FUN_00434fd0(8, 0, n.source_float(0x3c), 0);
      }
      if ((n.w[0x2b81] == 0x11) && (n.w[0x3a] < 10))
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        return;
      }
      if (0x28 < n.w[0x2b81])
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_9_1_350(FullChargeBodyContext& n)
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
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x20, 4, 0x14, 0);
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422900();
        n.FUN_00423000();
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] < 0x14)
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if (n.w[0x2b81] == 0x14)
      {
        uVar15 = 0;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
        n.FUN_00435450(6, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar12, uVar15);
        n.FUN_0042c8b0(0x8b);
        n.w[0x18] = 0;
        n.w[0x15] = 0x428c0000;
        uVar13 = 0;
        uVar11 = 0;
        uVar9 = 8;
        uVar15 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar15, uVar9, uVar11, uVar13);
        n.FUN_004230e0();
      }
      if (n.w[0x2b81] == 0x1f)
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.FUN_0042c8b0(0x8c);
      }
      if (n.w[0x2b81] == 0xf)
      {
        if (n.w[0x3e] < 10)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x20) && (n.w[0x3e] < 0x23))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_9_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x20, 4, 0x14, 0);
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422900();
        n.FUN_00423000();
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
      }
      if (n.w[0x2b81] < 0x14)
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if (n.w[0x2b81] == 0x14)
      {
        fVar5 = (float10) n.FUN_0042da80();
        local_10 = (float) fVar5;
        n.w[0x18] = 0;
        if (actor_word_real(0x41200000u) < local_10)
        {
          local_10 = 10.0;
        }
        if (local_10 < actor_word_real(0xc1f00000u))
        {
          local_10 = -30.0;
        }
        fVar5 = (float10) n.FUN_0065d050(local_10);
        n.w[0x15] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x428c0000u)))));
        fVar5 = (float10) n.FUN_0065d010(local_10);
        n.w[0x10] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x428c0000u)))));
        n.w[0xb] = actor_real_word(float(local_10));
        n.w[0xb6] = 0x428c0000;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar14 = local_10;
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, local_10);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
        n.FUN_00435450(6, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar12, fVar14);
        n.FUN_0042c8b0(0x8b);
        n.w[0x18] = 0;
        uVar11 = 0;
        uVar9 = 8;
        uVar15 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar15, uVar9, uVar11, local_10);
        n.FUN_004230e0();
      }
      if (n.w[0x2b81] == 0x1f)
      {
        n.w[0x18] = 0;
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3dcccccdu)));
        n.w[0x10] = 0;
        n.FUN_0042c8b0(0x8c);
      }
      if (n.w[0x2b81] == 0xf)
      {
        if (n.w[0x3e] < 10)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if (0x1f < n.w[0x2b81])
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3e800000u)));
      }
      if ((n.w[0x2b81] == 0x20) && (n.w[0x3e] < 0x23))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_9_2_350(FullChargeBodyContext& n)
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
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x21, 0, 0x14, 0);
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422900();
        n.FUN_00423000();
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.FUN_0042db10(0, ((n.source_float(0x3d)) * actor_word_real(0x41c80000u)) + actor_word_real(0x42340000u));
        uVar14 = 0;
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
        n.FUN_00435450(6, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar12, uVar14);
        n.FUN_0042c8b0(200);
        n.w[0x18] = 0;
        n.w[0x15] = actor_real_word(float(((n.source_float(0x3d)) * actor_word_real(0x41700000u)) + actor_word_real(0x42480000u)));
        n.FUN_00423000();
      }
      if (n.w[0x2b81] == 0x1f)
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0xf) && ((uVar3 = n.FUN_0042c7b0(), (uVar3 & 2) != 0)))
      {
        n.particle(0x46, n.w[5], (n.source_float(6)) + actor_word_real(0x42c80000u), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
        n.FUN_0042c8b0(0x33);
        n.FUN_0042c800(0);
        n.write_scratch(0x3d, actor_word_add(n.w[0x3d], 1));
        if (5 < n.w[0x3d])
        {
          n.write_scratch(0x3d, 5);
        }
      }
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && (n.w[0x2b81] < 0x1f))
      {
        uVar3 = n.w[0x2b81] & 0x80000001;
        if (((int) uVar3) < 0)
        {
          uVar3 = ((uVar3 - 1) | 0xfffffffe) + 1;
        }
        if (uVar3 == 0)
        {
          uVar14 = 0;
          fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
          fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
          fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
          fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
          n.FUN_00435450(1, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar12, uVar14);
        }
      }
      if (n.w[0x2b81] == 0xe)
      {
        if (n.w[0x3e] < 0x2d)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          n.write_clock(0x2b81, 0xd);
          n.write_clock(0x2b82, 0xd);
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x20) && (n.w[0x3e] < 0xf))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_9_2_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x21, 0, 0x14, 0);
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422900();
        n.FUN_00423000();
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
      }
      if (n.w[0x2b81] == 0x14)
      {
        n.FUN_0042db10(0, ((n.source_float(0x3d)) * actor_word_real(0x41c80000u)) + actor_word_real(0x42340000u));
        fVar5 = (float10) n.FUN_0042da80();
        local_10 = (float) fVar5;
        n.w[0x18] = 0;
        if (actor_word_real(0x41200000u) < local_10)
        {
          local_10 = 10.0;
        }
        if (local_10 < actor_word_real(0xc2200000u))
        {
          local_10 = -40.0;
        }
        fVar10 = ((n.source_float(0x3d)) * actor_word_real(0x41700000u)) + actor_word_real(0x42480000u);
        fVar5 = (float10) n.FUN_0065d050(local_10);
        n.w[0x15] = actor_real_word(float((float) (fVar5 * ((float10) fVar10))));
        fVar10 = ((n.source_float(0x3d)) * actor_word_real(0x41700000u)) + actor_word_real(0x42480000u);
        fVar5 = (float10) n.FUN_0065d010(local_10);
        n.w[0x10] = actor_real_word(float((float) (fVar5 * ((float10) fVar10))));
        n.w[0xb] = actor_real_word(float(local_10));
        n.w[0xb6] = 0x428c0000;
        n.FUN_0042c8b0(200);
        fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, local_10);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
        n.FUN_00435450(6, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar12, local_10);
        n.w[0x18] = 0;
        n.FUN_00423000();
      }
      if (n.w[0x2b81] == 0x1f)
      {
        n.w[0x18] = 0;
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3dcccccdu)));
        n.w[0x10] = 0;
      }
      if ((n.w[0x2b81] < 0xf) && ((uVar3 = n.FUN_0042c7b0(), (uVar3 & 2) != 0)))
      {
        n.particle(0x46, n.w[5], (n.source_float(6)) + actor_word_real(0x42c80000u), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
        n.FUN_0042c8b0(0x33);
        n.FUN_0042c800(0);
        n.write_scratch(0x3d, actor_word_add(n.w[0x3d], 1));
        if (5 < n.w[0x3d])
        {
          n.write_scratch(0x3d, 5);
        }
      }
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && (n.w[0x2b81] < 0x1f))
      {
        uVar3 = n.w[0x2b81] & 0x80000001;
        if (((int) uVar3) < 0)
        {
          uVar3 = ((uVar3 - 1) | 0xfffffffe) + 1;
        }
        if (uVar3 == 0)
        {
          uVar14 = 0;
          fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
          fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
          fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
          fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
          n.FUN_00435450(1, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar12, uVar14);
        }
      }
      if (n.w[0x2b81] == 0xe)
      {
        if (n.w[0x3e] < 0x2d)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          n.write_clock(0x2b81, 0xd);
          n.write_clock(0x2b82, 0xd);
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b81] == 0x20) && (n.w[0x3e] < 0xf))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (0x1f < n.w[0x2b81])
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3e800000u)));
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_10_0_350(FullChargeBodyContext& n)
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
        n.FUN_004223d0(0x20, 0x14, 0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 3);
      }
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x1e)
      {
        n.FUN_0042c8b0(0x91);
        n.w[0x18] = 0;
        n.w[0x15] = -0x3ee00000;
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x1e))
        {
          n.write_scratch(0x3c, -0x1e);
        }
        if (0x1e < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x1e);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        fVar12 = n.source_float(0x3c);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x40000000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = n.source_float(0x3c);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x40000000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = (n.source_float(0x3c)) + actor_word_real(0x40a00000u);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x3f800000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = (n.source_float(0x3c)) + actor_word_real(0x40a00000u);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x3f800000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
        for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = ((float) (uVar3 % 10)) + ((float) iVar4);
          fVar11 = n.source_float(0x17);
          fVar13 = n.source_float(0x19);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = (((float) (uVar3 % 10)) + fVar11) + fVar13;
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
          fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(9, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = ((float) (uVar3 % 10)) + ((float) iVar4);
          fVar11 = n.source_float(0x17);
          fVar13 = n.source_float(0x19);
          uVar3 = n.FUN_0065d150();
          fVar10 = (fVar11 + fVar13) - ((float) (uVar3 % 10));
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17]);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
          fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17]);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(9, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
        }

      }
      if (n.w[0x2b81] == 0x16)
      {
        if (n.w[0x3e] < 0x14)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_10_0_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(0x20, 0x14, 0);
        n.FUN_00422900();
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 3);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        n.FUN_0042c8b0(0x91);
        n.w[0x18] = 0;
        n.w[0x15] = -0x3f600000;
        n.w[0x10] = 0x40a00000;
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x1e))
        {
          n.write_scratch(0x3c, -0x1e);
        }
        if (0x1e < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x1e);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        fVar12 = n.source_float(0x3c);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x40000000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = n.source_float(0x3c);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x40000000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = (n.source_float(0x3c)) + actor_word_real(0x40a00000u);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x3f800000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = (n.source_float(0x3c)) + actor_word_real(0x40a00000u);
        fVar10 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x3f800000u);
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
        for (local_14 = 0; local_14 < 10; local_14 = local_14 + 1)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = ((float) (uVar3 % 10)) + ((float) iVar4);
          fVar11 = n.source_float(0x17);
          fVar13 = n.source_float(0x19);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = (((float) (uVar3 % 10)) + fVar11) + fVar13;
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
          fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(9, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = ((float) (uVar3 % 10)) + ((float) iVar4);
          fVar11 = n.source_float(0x17);
          fVar13 = n.source_float(0x19);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = (fVar11 + fVar13) - ((float) (uVar3 % 10));
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
          fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
          fVar6 = (float10) actor_word_real(0x41200000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(9, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
        }

      }
      if (n.w[0x2b81] == 0x16)
      {
        if (n.w[0x3e] < 0x14)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if ((0x1e < n.w[0x2b81]) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), ((char) n.w[0x21]) != '\0')))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_10_1_350(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        n.FUN_00434a70(0, 0);
        n.FUN_00434a70(1, 1);
        return;
      }
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        n.FUN_00434a70(0, 0);
        n.FUN_00434a70(1, 1);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if (n.w[0x3a] < 0x1e)
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        n.FUN_0042db10(0, 0x41200000);
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
      }
      else
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] < 0x28)
      {
        n.FUN_0042dc20(0, 0x40400000);
      }
      if (n.w[0x3b] < 5)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 3);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3d, iVar4);
        if (n.w[0x3d] < (-0x1e))
        {
          n.write_scratch(0x3d, -0x1e);
        }
        if (0x1e < n.w[0x3d])
        {
          n.write_scratch(0x3d, 0x1e);
        }
        n.FUN_0042c8b0(0x92);
        n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        n.write_scratch(0x3b, 0);
        while (n.w[0x3b] < 5)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          fVar10 = ((n.source_float(0x3b)) * actor_word_real(0x40a00000u)) + actor_word_real(0x40a00000u);
          fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, fVar10);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
          fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar12, fVar10);
          fVar10 = ((n.source_float(0x3b)) * actor_word_real(0x40a00000u)) + actor_word_real(0x40a00000u);
          fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, fVar10);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
          fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17]);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar12, fVar10);
          n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        }

      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_10_1_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
      }
      if (n.w[0x3b] < 5)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 3);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042dc20(0, 0x41200000);
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
      }
      else
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u)));
        if (actor_word_real(0xc0400000u) < (n.source_float(0x15)))
        {
          n.w[0x15] = -0x3fc00000;
        }
      }
      if (n.w[0x2b81] < 0x28)
      {
        n.FUN_0042dc20(0, 0x40400000);
      }
      if (0x1d < n.w[0x2b81])
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3f000000u)));
      }
      n.w[0x16] = 0x3f000000;
      if (n.w[0x2b81] == 0x1e)
      {
        n.w[0x18] = 0;
        n.FUN_0042c8b0(0x92);
        n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        n.w[0x15] = -0x3ee00000;
        n.w[0x10] = 0x40a00000;
        n.FUN_0042c8b0(0x92);
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (0x14 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x14);
        }
        if (n.w[0x3c] < (-0x28))
        {
          n.write_scratch(0x3c, -0x28);
        }
        n.write_scratch(0x3b, 0);
        while (n.w[0x3b] < 5)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          fVar10 = ((n.source_float(0x3b)) * actor_word_real(0x40a00000u)) + (n.source_float(0x3c));
          fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, fVar10);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
          fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar12, fVar10);
          fVar10 = ((n.source_float(0x3b)) * actor_word_real(0x40a00000u)) + (n.source_float(0x3c));
          fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, fVar10);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar11 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
          fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
          n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar12, fVar10);
          n.write_scratch(0x3b, actor_word_add(n.w[0x3b], 1));
        }

      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_10_2_350(FullChargeBodyContext& n)
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
        n.FUN_004223d0(0x20, 0x14, 0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042dc20(0, 0x40c00000);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 3);
      }
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x1e)
      {
        n.FUN_0042c8b0(0x91);
        n.w[0x18] = 0;
        n.w[0x15] = -0x3ee00000;
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x1e))
        {
          n.write_scratch(0x3c, -0x1e);
        }
        if (0x1e < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x1e);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        fVar12 = n.source_float(0x3c);
        fVar10 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = n.source_float(0x3c);
        fVar10 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
      }
      if (n.w[0x2b81] == 0x16)
      {
        if (n.w[0x3e] < 0x14)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_10_2_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(0x20, 0x14, 0);
        n.FUN_00422900();
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042dc20(0, 0x40c00000);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_00434a70(0, 2);
        n.FUN_00434a70(1, 3);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        n.FUN_0042c8b0(0x91);
        n.w[0x18] = 0;
        n.w[0x15] = -0x3f600000;
        n.w[0x10] = 0x40a00000;
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x1e))
        {
          n.write_scratch(0x3c, -0x1e);
        }
        if (0x1e < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x1e);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        fVar12 = n.source_float(0x3c);
        fVar10 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17], fVar9, fVar11);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) ((fVar8 * ((float10) actor_word_real(0x42480000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar11, fVar10, fVar12);
        fVar12 = n.source_float(0x3c);
        fVar10 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar7 = (float10) n.FUN_0065d010(n.w[0x17], fVar10, fVar12);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar11 = n.source_float(7);
        fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        fVar11 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar11)))) - (fVar8 * ((float10) actor_word_real(0x42480000u))));
        fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
        fVar7 = (float10) n.FUN_0065d050(n.w[0x17]);
        fVar6 = (float10) actor_word_real(0x41200000u);
        fVar13 = n.source_float(5);
        fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + actor_word_real(0x42b40000u));
        n.FUN_00435450(10, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42480000u)))), fVar9, fVar11, fVar10, fVar12);
      }
      if (n.w[0x2b81] == 0x16)
      {
        if (n.w[0x3e] < 0x14)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if ((0x1e < n.w[0x2b81]) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), ((char) n.w[0x21]) != '\0')))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_0_350(FullChargeBodyContext& n)
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
        n.FUN_004223d0(0x20, 0x14, 0);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.write_scratch(0x3a, 0);
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] < 0x12)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b81] == 0x12)
      {
        n.FUN_0042c8b0(0x8f);
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x28))
        {
          n.write_scratch(0x3c, -0x28);
        }
        if (0x28 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x28);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        fVar10 = n.source_float(0x3c);
        uVar14 = 0;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = n.source_float(0x3c);
        uVar14 = 0;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = n.source_float(0x3c);
        uVar14 = 0xc0000000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = n.source_float(0x3c);
        uVar14 = 0x40000000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3fc00000u);
        uVar14 = 0xbf800000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3fc00000u);
        uVar14 = 0x3f800000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f000000u);
        uVar14 = 0xc0400000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f000000u);
        uVar14 = 0x40400000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f800000u);
        uVar14 = 0xc0200000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f800000u);
        uVar14 = 0x40200000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
      }
      if (n.w[0x2b81] == 9)
      {
        if (n.w[0x3a] < 10)
        {
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          return;
        }
        n.write_scratch(0x3a, 0);
      }
      if (n.w[0x2b81] == 0x1d)
      {
        if (n.w[0x3a] < 0x19)
        {
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          return;
        }
        n.write_scratch(0x3a, 0);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_0_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if (((char) n.w[0x21]) != '\0')
      {
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.FUN_00421080(0x169);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if (n.w[0x2b81] < 0x1f)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(0x20, 0x14, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.FUN_00422900();
        n.w[0x18] = 0;
      }
      if (n.w[0x2b81] == 0x1f)
      {
        n.FUN_0042c8b0(0x8f);
        n.w[0x15] = -0x3f100000;
        n.w[0x10] = 0x41000000;
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x28))
        {
          n.write_scratch(0x3c, -0x28);
        }
        if (0x28 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x28);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        fVar10 = n.source_float(0x3c);
        uVar14 = 0;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = n.source_float(0x3c);
        uVar14 = 0;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = n.source_float(0x3c);
        uVar14 = 0xc0000000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = n.source_float(0x3c);
        uVar14 = 0x40000000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3fc00000u);
        uVar14 = 0xbf800000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3fc00000u);
        uVar14 = 0x3f800000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f000000u);
        uVar14 = 0xc0400000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f000000u);
        uVar14 = 0x40400000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f800000u);
        uVar14 = 0xc0200000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
        fVar10 = (n.source_float(0x3c)) + actor_word_real(0x3f800000u);
        uVar14 = 0x40200000;
        uVar11 = 6;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar11, uVar14, fVar10);
      }
      if ((n.source_float(0x16)) == actor_word_real(0x00000000u))
      {
        n.w[0x16] = 0x3f000000;
      }
      if (0x1e < n.w[0x2b81])
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_0_361(FullChargeBodyContext& n)
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
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_1_350(FullChargeBodyContext& n)
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
        n.FUN_004223d0(0x21, 0x14, 0);
        n.w[0x18] = 0;
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0;
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] == 0xf)
        {
          n.FUN_0042c8b0(0x8d);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 10)) - actor_word_real(0x40a00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 10)) - actor_word_real(0x40a00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 10)) - actor_word_real(0x40a00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
        }
        if (((0x19 < n.w[0x2b81]) && (0 < n.w[0xae])) && (n.w[0xae] < 0x14))
        {
          n.FUN_00421100(1);
          return;
        }
        if (n.w[0x2b81] == 0x3c)
        {
          n.FUN_00421080(0);
          return;
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0x12)
        {
          n.w[0x15] = 0x41700000;
        }
        if (n.w[0x2b81] == 0x19)
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 0x15)
        {
          n.FUN_0042c8b0(0x8d);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 0xe)) - actor_word_real(0x40e00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 0xe)) - actor_word_real(0x40e00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 0xe)) - actor_word_real(0x40e00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
        }
        if (((0x1e < n.w[0x2b81]) && (0 < n.w[0xae])) && (n.w[0xae] < 0x14))
        {
          n.FUN_00421100(2);
          return;
        }
        if (n.w[0x2b81] == 0x30)
        {
          n.FUN_00421080(0);
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        if (n.w[0x2b81] == 0xc)
        {
          n.w[0x15] = 0x41a00000;
        }
        if (n.w[0x2b81] == 0x13)
        {
          n.FUN_0042c8b0(0x8d);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = -((float) (uVar3 % 0x14));
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = -((float) (uVar3 % 0x14));
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = -((float) (uVar3 % 0x14));
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150();
          fVar10 = (float) (uVar3 % 0x14);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = (float) (uVar3 % 0x14);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar12 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar12);
          fVar10 = (float) (uVar3 % 0x14);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
        }
        if (n.w[0x2b81] == 0x15)
        {
          n.w[0x15] = 0;
        }
      }
      if (n.w[0x2b81] < 0x1a)
      {
        n.FUN_0042db10(0, 0x41900000);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x10] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_004223d0(0x21, 0x14, 0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] == 0x10)
        {
          n.w[0x18] = 0;
          n.w[0x15] = -0x3f600000;
          n.w[0x10] = 0x40d00000;
          n.FUN_0042c8b0(0x8d);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 10)) - actor_word_real(0x40a00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 10)) - actor_word_real(0x40a00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 10)) + ((float) iVar4)) - actor_word_real(0x40a00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 10)) - actor_word_real(0x40a00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
        }
        if (((0x19 < n.w[0x2b81]) && (0 < n.w[0xae])) && (n.w[0xae] < 0x14))
        {
          n.FUN_00421100(1);
          return;
        }
        if (n.w[0x2b81] == 0x3c)
        {
          n.FUN_00421080(0x2b);
          return;
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0xf)
        {
          n.w[0x18] = 0;
          n.w[0x15] = -0x3f600000;
          n.w[0x10] = 0x40d00000;
          n.FUN_0042c8b0(0x8d);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 0xe)) + ((float) iVar4)) - actor_word_real(0x40e00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 0xe)) - actor_word_real(0x40e00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 0xe)) + ((float) iVar4)) - actor_word_real(0x40e00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 0xe)) - actor_word_real(0x40e00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
          iVar4 = n.w[0x3c];
          uVar3 = n.FUN_0065d150();
          fVar10 = (((float) (uVar3 % 0xe)) + ((float) iVar4)) - actor_word_real(0x40e00000u);
          uVar3 = n.FUN_0065d150(fVar10);
          fVar12 = ((float) (uVar3 % 0xe)) - actor_word_real(0x40e00000u);
          uVar9 = 7;
          uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
          n.FUN_00435220(uVar5, uVar9, fVar12, fVar10);
        }
        if (((0x14 < n.w[0x2b81]) && (0 < n.w[0xae])) && (n.w[0xae] < 0x14))
        {
          n.FUN_00421100(2);
          return;
        }
        if (n.w[0x2b81] == 0x37)
        {
          n.FUN_00421080(0x2b);
          return;
        }
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 0x13))
      {
        n.w[0x18] = 0;
        n.w[0x15] = -0x3f600000;
        n.w[0x10] = 0x40d00000;
        n.FUN_0042c8b0(0x8d);
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x1e))
        {
          n.write_scratch(0x3c, -0x1e);
        }
        if (0x1e < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x1e);
        }
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        iVar4 = n.w[0x3c];
        uVar3 = n.FUN_0065d150();
        fVar12 = (((float) (uVar3 % 0x14)) + ((float) iVar4)) - actor_word_real(0x41200000u);
        uVar3 = n.FUN_0065d150(fVar12);
        fVar10 = -((float) (uVar3 % 0x14));
        uVar9 = 7;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
        iVar4 = n.w[0x3c];
        uVar3 = n.FUN_0065d150();
        fVar12 = (((float) (uVar3 % 0x14)) + ((float) iVar4)) - actor_word_real(0x41200000u);
        uVar3 = n.FUN_0065d150(fVar12);
        fVar10 = -((float) (uVar3 % 0x14));
        uVar9 = 7;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
        iVar4 = n.w[0x3c];
        uVar3 = n.FUN_0065d150();
        fVar12 = (((float) (uVar3 % 0x14)) + ((float) iVar4)) - actor_word_real(0x41200000u);
        uVar3 = n.FUN_0065d150(fVar12);
        fVar10 = -((float) (uVar3 % 0x14));
        uVar9 = 7;
        uVar5 = n.FUN_0064e6c0("Bip01_R_Hand");
        n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
        iVar4 = n.w[0x3c];
        uVar3 = n.FUN_0065d150();
        fVar12 = (((float) (uVar3 % 0x14)) + ((float) iVar4)) - actor_word_real(0x41200000u);
        uVar3 = n.FUN_0065d150(fVar12);
        fVar10 = (float) (uVar3 % 0x14);
        uVar9 = 7;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
        iVar4 = n.w[0x3c];
        uVar3 = n.FUN_0065d150();
        fVar12 = (((float) (uVar3 % 0x14)) + ((float) iVar4)) - actor_word_real(0x41200000u);
        uVar3 = n.FUN_0065d150(fVar12);
        fVar10 = (float) (uVar3 % 0x14);
        uVar9 = 7;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
        iVar4 = n.w[0x3c];
        uVar3 = n.FUN_0065d150();
        fVar12 = (((float) (uVar3 % 0x14)) + ((float) iVar4)) - actor_word_real(0x41200000u);
        uVar3 = n.FUN_0065d150(fVar12);
        fVar10 = (float) (uVar3 % 0x14);
        uVar9 = 7;
        uVar5 = n.FUN_0064e6c0("Bip01_L_Hand");
        n.FUN_00435220(uVar5, uVar9, fVar10, fVar12);
      }
      if (n.w[0x2b81] < 0x1a)
      {
        n.FUN_0042dc20(0, 0x41900000);
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_1_361(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_11_2_350(FullChargeBodyContext& n)
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
    do
    {
      if (((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u))) && (0 < n.w[0x2b7d]))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_00422900();
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.write_scratch(0x3a, 0);
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0x40a00000;
        n.w[0x10] = 0x42020000;
        n.w[0x16] = 0x3f400000;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        if (n.w[0x2b81] == 0)
        {
          n.FUN_0042c8b0(0xbd);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          fVar12 = (n.source_float(0x3c)) + ((float) (n.w[0x3a] << 1));
          fVar14 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar14, fVar12);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar10 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          fVar10 = (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))));
          fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          n.FUN_00435450(7, (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar10, fVar14, fVar12);
          fVar12 = (n.source_float(0x3c)) + ((float) (n.w[0x3a] << 1));
          fVar14 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)));
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar10 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          fVar10 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))) - (fVar8 * ((float10) actor_word_real(0x42200000u))));
          fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)));
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          n.FUN_00435450(7, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42200000u)))), fVar9, fVar10, fVar14, fVar12);
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        if (n.w[0x2b81] < 0x1f)
        {
          n.FUN_0042dc20(0, 0x41f00000);
        }
        if (0x1e < n.w[0x2b81])
        {
          if (n.w[0x2b81] == 0x1f)
          {
            n.FUN_0042c8b0(0xbd);
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3c, iVar4);
            if (n.w[0x3c] < (-0x32))
            {
              n.write_scratch(0x3c, -0x32);
            }
            if (0x1e < n.w[0x3c])
            {
              n.write_scratch(0x3c, 0x1e);
            }
          }
          if (n.w[0x2b81] < 0x28)
          {
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            n.FUN_004230e0();
            n.FUN_004230e0();
            fVar14 = ((n.source_float(0x3c)) + actor_word_real(0x41200000u)) - ((float) (n.w[0x3a] << 1));
            fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, fVar14);
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar10 = n.source_float(7);
            fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            fVar10 = (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))));
            fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar13 = n.source_float(5);
            fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            n.FUN_00435450(7, (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar10, fVar12, fVar14);
            fVar14 = ((n.source_float(0x3c)) + actor_word_real(0x41200000u)) - ((float) (n.w[0x3a] << 1));
            fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)));
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar10 = n.source_float(7);
            fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            fVar10 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))) - (fVar8 * ((float10) actor_word_real(0x42200000u))));
            fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)));
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar13 = n.source_float(5);
            fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            n.FUN_00435450(7, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42200000u)))), fVar9, fVar10, fVar12, fVar14);
          }
        }
      }
      if ((n.w[0x2b7d] == 3) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), 5 < n.w[0x2b81])))
      {
        n.FUN_00421080(0x2b);
      }
      if ((n.w[0x2b7d] == 1) && (0x14 < n.w[0x2b81]))
      {
        n.FUN_00421100(2);
        n.write_scratch(0x3a, 0);
        n.write_clock(0x2b81, 0x14);
        n.write_clock(0x2b82, 0x14);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_2_360(FullChargeBodyContext& n)
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
    do
    {
      if (((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u))) && (0 < n.w[0x2b7d]))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_00422900();
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0);
        n.write_scratch(0x3a, 0);
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0x40a00000;
        n.w[0x10] = 0x42020000;
        n.w[0x16] = 0x3f400000;
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        if (n.w[0x2b81] == 0)
        {
          n.FUN_0042c8b0(0xbd);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
        }
        if (n.w[0x2b81] < 10)
        {
          n.FUN_004230e0();
          n.FUN_004230e0();
          fVar12 = (n.source_float(0x3c)) + ((float) (n.w[0x3a] << 1));
          fVar14 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar14, fVar12);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar10 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          fVar10 = (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))));
          fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          n.FUN_00435450(7, (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar10, fVar14, fVar12);
          fVar12 = (n.source_float(0x3c)) + ((float) (n.w[0x3a] << 1));
          fVar14 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)));
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar10 = n.source_float(7);
          fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          fVar10 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))) - (fVar8 * ((float10) actor_word_real(0x42200000u))));
          fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
          fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
          fVar6 = (float10) actor_word_real(0x42480000u);
          fVar13 = n.source_float(5);
          fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
          n.FUN_00435450(7, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42200000u)))), fVar9, fVar10, fVar14, fVar12);
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        if (n.w[0x2b81] < 0x1f)
        {
          n.FUN_0042dc20(0, 0x41f00000);
        }
        if (0x1e < n.w[0x2b81])
        {
          if (n.w[0x2b81] == 0x1f)
          {
            n.FUN_0042c8b0(0xbd);
            n.FUN_0042da80();
            iVar4 = n.FUN_0066b668();
            n.write_scratch(0x3c, iVar4);
            if (n.w[0x3c] < (-0x32))
            {
              n.write_scratch(0x3c, -0x32);
            }
            if (0x1e < n.w[0x3c])
            {
              n.write_scratch(0x3c, 0x1e);
            }
          }
          if (n.w[0x2b81] < 0x28)
          {
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            n.FUN_004230e0();
            n.FUN_004230e0();
            fVar14 = ((n.source_float(0x3c)) + actor_word_real(0x41200000u)) - ((float) (n.w[0x3a] << 1));
            fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, fVar14);
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar10 = n.source_float(7);
            fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            fVar10 = (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))));
            fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar13 = n.source_float(5);
            fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            n.FUN_00435450(7, (float) ((fVar8 * ((float10) actor_word_real(0x42200000u))) + ((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13))))), fVar9, fVar10, fVar12, fVar14);
            fVar14 = ((n.source_float(0x3c)) + actor_word_real(0x41200000u)) - ((float) (n.w[0x3a] << 1));
            fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar7 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)));
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar10 = n.source_float(7);
            fVar8 = (float10) n.FUN_0065d010(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            fVar10 = (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar10)))) - (fVar8 * ((float10) actor_word_real(0x42200000u))));
            fVar9 = actor_word_real(0x42960000u) + (n.source_float(6));
            fVar7 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar10);
            fVar6 = (float10) actor_word_real(0x42480000u);
            fVar13 = n.source_float(5);
            fVar8 = (float10) n.FUN_0065d050(((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42b40000u));
            n.FUN_00435450(7, (float) (((float10) ((float) ((fVar7 * fVar6) + ((float10) fVar13)))) - (fVar8 * ((float10) actor_word_real(0x42200000u)))), fVar9, fVar10, fVar12, fVar14);
          }
        }
      }
      if (n.w[0x2b7d] == 3)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      if ((n.w[0x2b7d] == 1) && (0x14 < n.w[0x2b81]))
      {
        n.FUN_00421100(2);
        n.write_scratch(0x3a, 0);
        n.write_clock(0x2b81, 0x14);
        n.write_clock(0x2b82, 0x14);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_11_2_361(FullChargeBodyContext& n)
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
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_0_350(FullChargeBodyContext& n)
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
        }
        if (n.w[0x2b81] < 0x11)
        {
          n.FUN_0042db10(0, 0x3f800000);
        }
        if ((0x14 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3eb33333u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 0)
        {
          n.FUN_0042db10(0, 0x43340000);
          n.write_scratch(0x3e, 0);
          n.w[0x18] = 0;
          n.w[0x15] = 0;
          n.FUN_004223d0(0x27, 0x14, 0);
        }
        if (n.w[0x2b81] == 0xf)
        {
          if (n.w[0x3e] < 10)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x17)
        {
          if (n.w[0x3e] < 5)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x12)
        {
          n.w[0x18] = 0;
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x41700000u)));
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3a, actor_word_add(iVar4, 5));
          if (n.w[0x3a] < (-0x28))
          {
            n.write_scratch(0x3a, -0x28);
          }
          if (0x3c < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0x3c);
          }
          n.FUN_0042c8b0(0x99);
          n.FUN_004230e0();
          if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
          else
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
        }
        break;
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_0_360(FullChargeBodyContext& n)
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
        if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.FUN_00421080(0x1d5);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_0042db10(0, 0x43340000);
          n.FUN_00422900();
          n.write_scratch(0x3e, 0);
          n.w[0x10] = 0;
          n.w[0x15] = 0;
          n.FUN_004223d0(0x27, 0x14, 0);
        }
        if (n.w[0x2b81] < 0x11)
        {
          n.FUN_0042db10(0, 0x3f800000);
        }
        if (0x11 < n.w[0x2b81])
        {
          n.w[0x16] = 0x3f000000;
          n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        }
        if (n.w[0x2b81] == 0xf)
        {
          if (n.w[0x3e] < 10)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x17)
        {
          if (n.w[0x3e] < 5)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x12)
        {
          n.w[0x18] = 0;
          n.w[0x15] = -0x3ee00000;
          n.w[0x10] = 0x40a00000;
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3a, actor_word_add(iVar4, 5));
          if (n.w[0x3a] < (-0x3c))
          {
            n.write_scratch(0x3a, -0x3c);
          }
          if (0x28 < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0x28);
          }
          n.FUN_0042c8b0(0x99);
          n.FUN_004230e0();
          if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
          else
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_0_361(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_1_350(FullChargeBodyContext& n)
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
        n.FUN_00434a70(0, 3);
        n.FUN_00434a70(1, 0xffffffff);
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
        }
        if (n.w[0x2b81] < 0x11)
        {
          n.FUN_0042db10(0, 0x41a00000);
        }
        if ((0x14 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3eb33333u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 0)
        {
          n.write_scratch(0x3e, 0);
          n.w[0x18] = 0;
          n.w[0x15] = 0;
          n.FUN_00422490(0x21, 0, 10, 0);
        }
        if (n.w[0x2b81] == 0xf)
        {
          if (n.w[0x3e] < 0x50)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x17)
        {
          if (n.w[0x3e] < 0x3c)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x12)
        {
          n.w[0x18] = 0;
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x41700000u)));
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3a, iVar4);
          if (n.w[0x3a] < (-0x28))
          {
            n.write_scratch(0x3a, -0x28);
          }
          if (0x28 < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0x28);
          }
          n.FUN_0042c8b0(0x9c);
          n.FUN_004230e0();
          if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
          else
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
        }
        break;
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_1_360(FullChargeBodyContext& n)
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
        if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.FUN_00421080(0x1d5);
          return;
        }
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          n.FUN_00422900();
          n.write_scratch(0x3e, 0);
          n.w[0x10] = 0;
          n.w[0x15] = 0;
          n.FUN_00422490(0x21, 0, 10, 0);
        }
        if (n.w[0x2b81] < 0xf)
        {
          n.FUN_0042dc20(0, 0x41700000);
        }
        if (n.w[0x2b81] < 0x11)
        {
          n.FUN_0042dc20(0, 0x40000000);
        }
        n.FUN_00434a70(0, 3);
        n.FUN_00434a70(1, 0xffffffff);
        if (0x11 < n.w[0x2b81])
        {
          n.w[0x16] = 0x3f000000;
          n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        }
        if (n.w[0x2b81] == 0xf)
        {
          if (n.w[0x3e] < 0x50)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x17)
        {
          if (n.w[0x3e] < 0x3c)
          {
            n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
            return;
          }
          n.write_scratch(0x3e, 0);
        }
        if (n.w[0x2b81] == 0x11)
        {
          n.w[0x18] = 0;
          n.w[0x15] = -0x3eb80000;
          n.w[0x10] = 0x41200000;
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3a, iVar4);
          if (n.w[0x3a] < (-0x28))
          {
            n.write_scratch(0x3a, -0x28);
          }
          if (0x28 < n.w[0x3a])
          {
            n.write_scratch(0x3a, 0x28);
          }
          n.FUN_0042c8b0(0x9c);
          n.FUN_004230e0();
          if (((n.byte(0x845)) == '\0') || (n.w[0x212] == 0))
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
          else
          {
            n.FUN_00435000(0, 9, 0, n.source_float(0x3a), 0);
          }
        }
      }
      while (0);
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_1_361(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_2_350(FullChargeBodyContext& n)
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
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422490(0x21, 1, 0x14, 0);
        n.w[0x15] = 0;
        n.FUN_00422900();
        n.write_scratch(0x3d, 0);
        n.write_scratch(0x3e, 0x3c);
        n.FUN_0042db10(0, 0x43340000);
        fVar5 = (float10) n.FUN_0042da80();
        n.w[0x1e8] = actor_real_word(float((float) fVar5));
        if ((n.source_float(0x1e8)) < actor_word_real(0xc2200000u))
        {
          n.w[0x1e8] = -0x3de00000;
        }
        if (actor_word_real(0x42200000u) < (n.source_float(0x1e8)))
        {
          n.w[0x1e8] = 0x42200000;
        }
      }
      if ((n.w[0x9f] < 0) && ((n.source_float(0x1e8)) < actor_word_real(0x42200000u)))
      {
        n.w[0x1e8] = actor_real_word(float((n.source_float(0x1e8)) + actor_word_real(0x3e4ccccdu)));
      }
      if ((0 < n.w[0x9f]) && (actor_word_real(0xc2200000u) < (n.source_float(0x1e8))))
      {
        n.w[0x1e8] = actor_real_word(float((n.source_float(0x1e8)) - actor_word_real(0x3e4ccccdu)));
      }
      if (0 < n.w[0x9e])
      {
        n.w[0x19] = actor_real_word(float((n.source_float(0x19)) - actor_word_real(0x3e4ccccdu)));
      }
      if (n.w[0x9e] < 0)
      {
        n.w[0x19] = actor_real_word(float((n.source_float(0x19)) + actor_word_real(0x3e4ccccdu)));
      }
      if (n.w[0x2b81] == 0x11)
      {
        n.write_scratch(0x3e, 0x3c);
        n.FUN_0042c8b0(0xcf);
        n.FUN_004230e0();
        n.FUN_00435000(0, 6, 0, n.w[0x1e8], 0);
      }
      if (n.w[0x2b81] == 0xf)
      {
        if ((0 < n.w[0x3e]) && ((n.write_scratch(0x3e, actor_word_add(n.w[0x3e], -1)), n.w[0x3e] == 0)))
        {
          n.FUN_00422ed0();
          n.FUN_0042c8b0(0xd0);
        }
        if (((n.w[0xa2] == 3) || ((0 < n.w[0xae]) && (n.w[0xae] < 3))) && (n.w[0x3e] < 1))
        {
          n.write_clock(0x2b81, 0x10);
          n.write_clock(0x2b82, 0x10);
        }
        if (n.w[0xa1] != 3)
        {
          if (n.w[0xad] < 1)
          {
            return;
          }
          if (2 < n.w[0xad])
          {
            return;
          }
        }
        n.write_clock(0x2b81, 0x27);
        n.write_clock(0x2b82, 0x27);
        return;
      }
      if ((n.w[0x2b81] == 0x25) && (n.w[0x3d] < 0x1e))
      {
        n.write_scratch(0x3d, actor_word_add(n.w[0x3d], 1));
        return;
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_2_360(FullChargeBodyContext& n)
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
    do
    {
      n.FUN_00434a70(0, 2);
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_00421080(0x1d5);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_00422490(0x21, 1, 0x14, 0);
      }
      if (n.w[0x2b81] < 0x11)
      {
        n.FUN_0042db10(0, 0x3f800000);
      }
      if (0x11 < n.w[0x2b81])
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      if (n.w[0x2b81] == 0xf)
      {
        if (n.w[0x3e] < 0x14)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0x20)
      {
        if (n.w[0x3e] < 0x3c)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0x12)
      {
        n.w[0x18] = 0;
        n.w[0x15] = -0x3ee00000;
        n.w[0x10] = 0x40a00000;
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3a, iVar4);
        if (n.w[0x3a] < (-0xf))
        {
          n.write_scratch(0x3a, -0xf);
        }
        if (0x14 < n.w[0x3a])
        {
          n.write_scratch(0x3a, 0x14);
        }
        n.FUN_0042c8b0(0xcf);
        n.FUN_004230e0();
        n.FUN_00435000(0, 0xb, 0, n.source_float(0x3a), 0);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_12_2_361(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      n.FUN_00434a70(0, 0);
      n.FUN_00434a70(1, 1);
      n.w[0x16] = 0;
      n.w[0x10] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      if ((actor_word_real(0x00000000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if (((n.source_float(0x15)) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (n.source_float(0x15)))))
      {
        n.w[0x15] = 0;
      }
      n.w[0x15] = 0;
      if (n.w[0x1fd] < 1)
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 0x28);
      }
      else
      {
        n.w[0x20d] = actor_word_add(n.w[0x20d], 5);
      }
      if (1000 < n.w[0x20d])
      {
        n.w[0x20d] = 1000;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_0_350(FullChargeBodyContext& n)
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
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.FUN_004223d0(0x20, 0x14, 0);
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3e, 0);
      }
      if ((0x32 < n.w[0x2b81]) && (n.w[0x2b81] < 0x50))
      {
        if (n.w[0x3a] < 1)
        {
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          return;
        }
        n.write_scratch(0x3a, 0);
      }
      if ((((n.w[0x2b81] == 0x11) || (n.w[0x2b81] == 0x16)) || (n.w[0x2b81] == 0x1a)) || (((n.w[0x2b81] == 0x1e) || (n.w[0x2b81] == 0x21)) || ((n.w[0x2b81] == 0x25) || (n.w[0x2b81] == 0x2a))))
      {
        n.FUN_0042da80();
        iVar4 = n.FUN_0066b668();
        n.write_scratch(0x3c, iVar4);
        if (n.w[0x3c] < (-0x14))
        {
          n.write_scratch(0x3c, -0x14);
        }
        if (0x14 < n.w[0x3c])
        {
          n.write_scratch(0x3c, 0x14);
        }
        n.FUN_004230e0();
        n.FUN_00435000(0, 8, 0, n.source_float(0x3c), 0);
        n.FUN_0042c880(0x40);
        n.FUN_0042c880(0x94);
      }
      if (n.w[0x2b81] < 0xc)
      {
        n.FUN_0042db10(0, 0x41500000);
      }
      if (n.w[0x2b81] < 0x2a)
      {
        n.FUN_0042db10(0, 0x3f800000);
      }
      if ((n.w[0x2b81] < 0x11) || (0x3c < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
      }
      if ((n.w[0x2b81] == 0xc) && (n.w[0x3e] < 0xf))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_0_351(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_13_0_352(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_13_0_360(FullChargeBodyContext& n)
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
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        n.FUN_00421080(0);
        return;
      }
      if (((char) n.w[0x21]) != '\0')
      {
        n.w[0x15] = 0;
        n.w[0x10] = 0;
      }
      if (n.w[0x2b81] < 0xc)
      {
        n.FUN_0042dc20(0, 0x41500000);
      }
      if (n.w[0x2b81] < 0x2a)
      {
        n.FUN_0042dc20(0, 0x3f800000);
      }
      n.w[0x16] = 0x3dcccccd;
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00422900();
          n.w[0x18] = 0;
          n.FUN_00434bd0();
          n.w[0x15] = 0;
          n.FUN_004223d0(0x20, 0x14, 0);
          n.write_scratch(0x3a, 0);
          n.write_scratch(0x3e, 0);
          if (actor_word_real(0x40400000u) < (n.source_float(0x10)))
          {
            n.w[0x10] = 0x40400000;
          }
          if ((n.source_float(0x10)) < actor_word_real(0xc0400000u))
          {
            n.w[0x10] = -0x3fc00000;
          }
        }
        if ((0x32 < n.w[0x2b81]) && (n.w[0x2b81] < 0x50))
        {
          if (n.w[0x3a] < 1)
          {
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            return;
          }
          n.write_scratch(0x3a, 0);
        }
        if (n.w[0x2b81] < 0x2a)
        {
          n.FUN_0042db10(0, 0x41200000);
          n.FUN_0042da80();
          iVar4 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar4);
          if (0x1e < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x1e);
          }
          if (n.w[0x3c] < (-0x1e))
          {
            n.write_scratch(0x3c, -0x1e);
          }
          n.w[0xb] = actor_real_word(float(n.source_float(0x3c)));
          n.w[0xb6] = 0x428c0000;
        }
        if (((n.w[0x2b81] == 0x11) || (n.w[0x2b81] == 0x16)) || ((n.w[0x2b81] == 0x1a) || ((((n.w[0x2b81] == 0x1e) || (n.w[0x2b81] == 0x21)) || (n.w[0x2b81] == 0x25)) || (n.w[0x2b81] == 0x2a))))
        {
          n.FUN_004230e0();
          n.FUN_00435000(0, 8, 0, n.source_float(0x3c), 0);
          n.FUN_0042c880(0x40);
          n.FUN_0042c880(0x94);
        }
        if (0x50 < n.w[0x2b81])
        {
          if ((actor_word_real(0x00000000u) < (n.source_float(0xb))) && ((n.w[0xb] = actor_real_word(float((n.source_float(0xb)) - actor_word_real(0x40000000u))), (n.source_float(0xb)) < actor_word_real(0x00000000u))))
          {
            n.w[0xb] = 0;
          }
          if (((n.source_float(0xb)) < actor_word_real(0x00000000u)) && ((n.w[0xb] = actor_real_word(float((n.source_float(0xb)) + actor_word_real(0x40000000u))), actor_word_real(0x00000000u) < (n.source_float(0xb)))))
          {
            n.w[0xb] = 0;
          }
        }
      }
      if ((n.w[0x2b81] < 0x11) || (0x3c < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
      }
      if ((n.w[0x2b81] == 0xc) && (n.w[0x3e] < 0xf))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_0_361(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_13_1_350(FullChargeBodyContext& n)
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
        if (n.w[0x3e] != 1)
        {
          return;
        }
        n.FUN_00422490(0x21, 0, 0x14, 0);
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
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422490(0x20, 1, 0x14, 0);
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.write_scratch(0x3a, 0);
        n.FUN_0042dc20(0, 0x43340000);
      }
      if (0x14 < n.w[0x2b81])
      {
        if (n.w[0x2b81] == 0x15)
        {
          n.w[0x15] = 0x41c80000;
        }
        n.w[0xc] = actor_real_word(float((n.source_float(0xc)) - actor_word_real(0x41700000u)));
        if ((n.source_float(0xc)) < actor_word_real(0xc3b40000u))
        {
          n.w[0xc] = -0x3c4c0000;
        }
      }
      if (n.w[0x2b81] == 0x15)
      {
        n.FUN_0042c8b0(0x96);
      }
      if ((0x28 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 1) != 0)
      {
        n.write_scratch(0x3e, 1);
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.particle(0x46, n.w[5], (n.source_float(6)) + actor_word_real(0x42c80000u), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + (n.source_float(0xc)), 0);
        n.FUN_0042c880(0x33);
        n.FUN_0042c800(0);
        return;
      }
      if ((n.w[0x2b81] < 0x1a) || (0x31 < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
      }
      if ((n.w[0x2b81] == 0x46) && (n.w[0x3a] < 0x2d))
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_1_351(FullChargeBodyContext& n)
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
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (((n.w[0x2b7d] == 0) || (n.w[0x2b7d] == 4)) && (((char) n.w[0x21]) == '\0'))
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
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 5))
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0x41200000;
        n.w[0x10] = 0x41a00000;
        n.w[0x16] = 0x3f000000;
        n.w[0x21d] = 0;
      }
      if ((((0 < n.w[0x2b7d]) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), n.w[0x2b7d] < 4))) && (((char) n.w[0x21]) != '\0')) && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.w[0x10] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(4);
        return;
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 1) != 0)
      {
        n.write_scratch(0x3e, 1);
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.particle(0x46, n.w[5], (n.source_float(6)) + actor_word_real(0x42c80000u), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + (n.source_float(0xc)), 0);
        n.FUN_0042c880(0x33);
        n.FUN_0042c800(0);
        return;
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f333333u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b7d] == 1)
      {
        n.FUN_00434b90(0);
      }
      else
      {
        n.FUN_00434bd0();
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_1_352(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_13_1_360(FullChargeBodyContext& n)
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
      if ((((char) n.w[0x21]) == '\0') && (0x25 < n.w[0x2b81]))
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422490(0x20, 1, 0x14, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.FUN_00422900();
        n.FUN_00423000();
        n.write_scratch(0x3a, 0);
        n.FUN_0042dc20(0, 0x43340000);
      }
      if (0x14 < n.w[0x2b81])
      {
        if (n.w[0x2b81] == 0x15)
        {
          fVar5 = (float10) n.FUN_0042da80();
          n.w[0xb] = actor_real_word(float((float) fVar5));
          n.w[0xb6] = 0x428c0000;
          if (actor_word_real(0x41200000u) < (n.source_float(0xb)))
          {
            n.w[0xb] = 0x41200000;
          }
          if ((n.source_float(0xb)) < actor_word_real(0xc1a00000u))
          {
            n.w[0xb] = -0x3e600000;
          }
          fVar5 = (float10) n.FUN_0065d050(n.w[0xb]);
          n.w[0x15] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x41c80000u)))));
          fVar5 = (float10) n.FUN_0065d010(n.w[0xb]);
          n.w[0x10] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x41c80000u)))));
        }
        n.w[0xc] = actor_real_word(float((n.source_float(0xc)) - actor_word_real(0x41700000u)));
        if ((n.source_float(0xc)) < actor_word_real(0xc3b40000u))
        {
          n.w[0xc] = -0x3c4c0000;
        }
      }
      if (n.w[0x2b81] == 0x15)
      {
        n.FUN_0042c8b0(0x96);
      }
      if ((0x28 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f400000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] < 0x1a) || (0x24 < n.w[0x2b81]))
      {
        n.FUN_00434bd0();
      }
      else
      {
        n.FUN_00434b90(0);
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3eb33333u)));
      if ((n.w[0x2b81] == 0x25) && (n.w[0x3a] < 9999))
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        if (n.w[0x3a] == 9999)
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          return;
        }
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.write_clock(0x2b81, 0x26);
        n.write_clock(0x2b82, 0x26);
        n.w[0xb] = 0;
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_1_361(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_13_2_350(FullChargeBodyContext& n)
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
      if (n.w[0x2b7d] == 2)
      {
        n.FUN_00434a70(0, 2);
      }
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 3))
      {
        n.FUN_00421080(0x2b);
        n.w[0x10] = 0;
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_0042c800(0);
        n.write_scratch(0x3e, 0);
      }
      if ((0 < n.w[0x2b7d]) || ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 0xc)))
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        n.FUN_0042db10(0, 0x3f800000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41700000;
          n.w[0x10] = 0x420c0000;
          n.w[0x16] = 0x40600000;
        }
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00421100(2);
        }
      }
      if ((actor_word_real(0x40f00000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x41200000u))))
      {
        n.w[0x15] = 0x41200000;
      }
      if (n.w[0x2b7d] == 2)
      {
        if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.FUN_00421100(3);
          n.write_clock(0x2b81, 10);
          n.write_clock(0x2b82, 10);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          n.FUN_0042c8b0(0xd3);
          n.FUN_00422490(0x27, 0, 0x14, 0);
          uVar12 = 0;
          fVar11 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, 0);
          fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
          iVar4 = n.w[6];
          fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), iVar4, fVar10);
          n.FUN_00435450(4, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), iVar4, fVar10, fVar11, uVar12);
          return;
        }
        if (n.w[0x2b81] == 0xb)
        {
          return;
        }
      }
      if (((n.w[0x2b7d] == 3) && (n.w[0x2b81] == 0x21)) && (n.w[0x3e] < 0x1e))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (((n.w[0x2b7d] == 2) && (10 < n.w[0x2b81])) || ((n.w[0x2b7d] == 3) && (n.w[0x2b81] < 0x14)))
      {
        n.FUN_00434b90(0);
      }
      else
      {
        n.FUN_00434bd0();
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_2_352(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_13_2_359(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_13_2_360(FullChargeBodyContext& n)
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
      if (n.w[0x2b7d] == 2)
      {
        n.FUN_00434a70(0, 2);
      }
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if ((((char) n.w[0x21]) == '\0') && (n.w[0x2b7d] == 3))
      {
        n.FUN_00421080(0x2b);
        n.w[0x10] = 0;
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.w[0x18] = 0;
        n.FUN_0042db10(0, 0x43340000);
        n.write_scratch(0x3e, 0);
        n.FUN_0042c800(0);
      }
      if ((0 < n.w[0x2b7d]) || ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 0xc)))
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        n.FUN_0042db10(0, 0x3f800000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] == 0)
        {
          n.w[0x15] = 0x41700000;
          n.w[0x10] = 0x420c0000;
          n.w[0x16] = 0x40600000;
        }
        if (n.w[0x2b81] == 0)
        {
          n.FUN_00421100(2);
        }
      }
      if ((actor_word_real(0x40f00000u) < (n.source_float(0x15))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x41200000u))))
      {
        n.w[0x15] = 0x41200000;
      }
      if (n.w[0x2b7d] == 2)
      {
        if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
        {
          n.FUN_00421080(0x15e);
          n.FUN_00421100(3);
          n.write_clock(0x2b81, 10);
          n.write_clock(0x2b82, 10);
          n.w[0x15] = 0;
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          n.FUN_0042c8b0(0xd3);
          uVar12 = 0;
          fVar11 = (n.source_float(0x17)) + (n.source_float(0x19));
          fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, 0);
          fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
          iVar4 = n.w[6];
          fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), iVar4, fVar10);
          n.FUN_00435450(4, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), iVar4, fVar10, fVar11, uVar12);
          return;
        }
        if (n.w[0x2b81] == 0xb)
        {
          return;
        }
      }
      if (((n.w[0x2b7d] == 3) && (n.w[0x2b81] == 0x21)) && (n.w[0x3e] < 0x1e))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (((n.w[0x2b7d] == 2) && (10 < n.w[0x2b81])) || ((n.w[0x2b7d] == 3) && (n.w[0x2b81] < 0x14)))
      {
        n.FUN_00434b90(0);
      }
      else
      {
        n.FUN_00434bd0();
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_13_2_361(FullChargeBodyContext& n)
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
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_14_1_350(FullChargeBodyContext& n)
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
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422490(0x27, 3, 0x14, 0);
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        if (n.w[0x3e] == 0)
        {
          n.FUN_0042da80();
          iVar5 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar5);
          if (n.w[0x3c] < (-0x28))
          {
            n.write_scratch(0x3c, -0x28);
          }
          if (0x28 < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x28);
          }
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_0042c8b0(0xdd);
        }
        if (((n.w[0x3e] % 7) == 0) && (n.w[0x3e] < 0x1e))
        {
          fVar13 = n.source_float(0x3c);
          fVar9 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x42200000u);
          fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar13);
          fVar12 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
          fVar11 = actor_word_real(0x42480000u) + (n.source_float(6));
          fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar12);
          n.FUN_00435450(0xb, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar11, fVar12, fVar9, fVar13);
        }
      }
      if ((n.w[0x2b81] == 0x1e) && (n.w[0x3e] < 0x3c))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_14_1_351(FullChargeBodyContext& n)
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
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422240(0x20, 0x14, 0);
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
        n.FUN_0042dc20(0, 0x43340000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c8b0(0xdd);
        uVar14 = 0;
        fVar13 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar13, 0);
        fVar12 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar12);
        n.FUN_00435450(0xd, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar12, fVar13, uVar14);
      }
      if (((n.w[0x2b81] == 0x14) && (9 < n.w[0x3e])) && (n.w[0x3e] < 0x1f))
      {
        n.FUN_004230e0();
        if ((n.w[0x3e] % 5) == 0)
        {
          n.FUN_0042c8b0(0xde);
        }
        uVar14 = 0;
        fVar13 = (((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42a00000u)) - ((float) (n.w[0x3e] << 2));
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar13, 0);
        fVar12 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar12);
        n.FUN_00435450(0xc, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar12, fVar13, uVar14);
      }
      if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0x14)) && (n.w[0x3e] < 0x2d))
      {
        n.write_clock(0x2b81, 0x13);
        n.write_clock(0x2b82, 0x13);
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_14_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422490(0x27, 3, 0x14, 0);
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 0x1e)
      {
        n.FUN_0042dc20(0, 0x41200000);
      }
      if (n.w[0x2b81] == 0x1e)
      {
        if (n.w[0x3e] == 0)
        {
          n.FUN_0042c8b0(0xdd);
          n.FUN_0042da80();
          iVar5 = n.FUN_0066b668();
          n.write_scratch(0x3c, iVar5);
          if (n.w[0x3c] < (-0x28))
          {
            n.write_scratch(0x3c, -0x28);
          }
          if (0x28 < n.w[0x3c])
          {
            n.write_scratch(0x3c, 0x28);
          }
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
          n.FUN_004230e0();
        }
        if (((n.w[0x3e] % 7) == 0) && (n.w[0x3e] < 0x1e))
        {
          fVar13 = n.source_float(0x3c);
          fVar9 = ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x42200000u);
          fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar13);
          fVar12 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
          fVar11 = actor_word_real(0x42480000u) + (n.source_float(6));
          fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, fVar12);
          n.FUN_00435450(0xb, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar11, fVar12, fVar9, fVar13);
        }
      }
      if ((n.w[0x2b81] == 0x1e) && (n.w[0x3e] < 0x3c))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_14_1_361(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422240(0x20, 0x14, 0);
        n.FUN_00422900();
        n.w[0x18] = 0;
        n.FUN_00434bd0();
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
        n.FUN_0042dc20(0, 0x43340000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c8b0(0xdd);
        uVar14 = 0;
        fVar13 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar13, 0);
        fVar12 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar12);
        n.FUN_00435450(0xd, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar12, fVar13, uVar14);
      }
      if (((n.w[0x2b81] == 0x14) && (9 < n.w[0x3e])) && (n.w[0x3e] < 0x1f))
      {
        n.FUN_004230e0();
        if ((n.w[0x3e] % 5) == 0)
        {
          n.FUN_0042c8b0(0xde);
        }
        uVar14 = 0;
        fVar13 = (((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42a00000u)) - ((float) (n.w[0x3e] << 2));
        fVar6 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar13, 0);
        fVar12 = (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(7))));
        fVar9 = actor_word_real(0x42480000u) + (n.source_float(6));
        fVar6 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar12);
        n.FUN_00435450(0xc, (float) ((fVar6 * ((float10) actor_word_real(0x42480000u))) + ((float10) (n.source_float(5)))), fVar9, fVar12, fVar13, uVar14);
      }
      if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0x14)) && (n.w[0x3e] < 0x2d))
      {
        n.write_clock(0x2b81, 0x13);
        n.write_clock(0x2b82, 0x13);
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_15_0_350(FullChargeBodyContext& n)
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
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x15] = 0x41700000;
        n.w[0x10] = 0;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b7d] == 1)
      {
        if (n.w[0x2b81] < 10)
        {
          n.FUN_0042db10(0, 0x40400000);
        }
        uVar3 = n.FUN_0042c7b0();
        if (((uVar3 & 1) != 0) && ((cVar1 = n.FUN_00422950(0xbe, 1, 0), cVar1 != '\0')))
        {
          uVar3 = n.FUN_0065d150();
          if ((uVar3 % 100) < 0x32)
          {
            n.FUN_00422490(0x21, 0, 0x14, 0);
          }
          else
          {
            n.FUN_00422490(0x21, 1, 0x14, 0);
          }
          n.w[0x1eb] = 0x1e;
          n.FUN_00421080(0x15f);
          return;
        }
        if (0x1e < n.w[0x2b81])
        {
          n.FUN_00421100(2);
        }
      }
      if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
    }
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_15_0_351(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        uVar3 = n.FUN_0065d150();
        if ((uVar3 % 100) < 0x32)
        {
          n.FUN_00422490(0x21, 2, 0x14, 0);
        }
        else
        {
          n.FUN_00422490(0x21, 3, 0x14, 0);
        }
        n.FUN_00421080(0);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3e, 0);
        n.FUN_0042c840(1);
        n.FUN_0042c800(0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 6))
      {
        n.victim_state(0xbc);
      }
      if (n.w[0x1eb] < 0x1c)
      {
        n.w[0x1eb] = 0x1e;
      }
      n.w[0x1a1] = 3;
      if (n.w[0x2b7d] == 0)
      {
        if (((char) n.w[0x21]) == '\0')
        {
          n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - actor_word_real(0x3f800000u)));
        }
        else
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40000000u)));
          n.w[0x10] = 0;
        }
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] == 6)
        {
          if ((n.source_float(0x15)) != actor_word_real(0x00000000u))
          {
            return;
          }
          if (((char) n.w[0x21]) == '\0')
          {
            return;
          }
        }
        if (n.w[0x2b81] == 7)
        {
          n.FUN_00423530("Bip01_Prop2");
        }
      }
      if (n.w[0x2b7d] == 1)
      {
        if ((n.w[0x2b81] % 9) == 3)
        {
          n.FUN_00422ab0(0xbc, 500, 1, "Bip01_Prop2");
          uVar3 = n.FUN_0065d150();
          n.FUN_0042c8b0((uVar3 % 3) + 0x14);
          fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), n.w[0x17], 0);
          fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), n.w[6], (float) ((fVar5 * ((float10) actor_word_real(0x42700000u))) + ((float10) (n.source_float(7)))));
          n.natsumi_capture_particle();
        }
        if (0x75 < n.w[0x2b81])
        {
          n.FUN_00421100(2);
        }
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 0x2b))
      {
        n.FUN_0042c8b0(0xe1);
        n.FUN_00422bd0(0x71, 0xc6, 0x9c4, 1, 0x43340000, 0x455ac000, 0);
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), n.w[0x17], 0);
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), n.w[6], (float) ((fVar5 * ((float10) actor_word_real(0x42700000u))) + ((float10) (n.source_float(7)))));
        n.natsumi_capture_particle();
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_15_0_352(FullChargeBodyContext& n)
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
    do
    {
      {
        n.FUN_00428510();
        return;
      }
    }
    while (0);
  }
}

inline void full_charge_body_15_0_360(FullChargeBodyContext& n)
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
    do
    {
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if (((char) n.w[0x21]) != '\0')
      {
        if (n.w[0x2b7d] < 2)
        {
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          n.FUN_00421080(0x15e);
          n.FUN_00421100(2);
          return;
        }
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.FUN_00421080(0x1d5);
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
        n.FUN_0042db10(0, 0x43340000);
        fVar5 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
        local_14 = (float) ((fVar5 / ((float10) actor_word_real(0x40490fdbu))) * ((float10) actor_word_real(0x43340000u)));
        n.FUN_0042da80();
        if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
        {
          fVar5 = (float10) n.FUN_0042da80();
          local_14 = (float) fVar5;
        }
        if (actor_word_real(0x41f00000u) < local_14)
        {
          local_14 = 30.0;
        }
        if (local_14 < actor_word_real(0xc20c0000u))
        {
          local_14 = -35.0;
        }
        fVar5 = (float10) n.FUN_0065d050(local_14);
        n.w[0x15] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x41700000u)))));
        fVar5 = (float10) n.FUN_0065d010(local_14);
        n.w[0x10] = actor_real_word(float((float) (fVar5 * ((float10) actor_word_real(0x41700000u)))));
        fVar5 = (float10) n.FUN_00423580(n.w[0x10], n.w[0x15]);
        n.w[0xb] = actor_real_word(float((float) (((fVar5 / ((float10) actor_word_real(0x40490fdbu))) * ((float10) actor_word_real(0x43340000u))) + ((float10) actor_word_real(0x41a00000u)))));
        n.w[0xb6] = 0x428c0000;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      sVar2 = n.FUN_0042c7b0();
      if ((sVar2 != 0) && (n.w[0x3b] == 0))
      {
        n.write_scratch(0x3b, 1);
      }
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x41700000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.FUN_0042db10(0, 0x3f800000);
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        uVar3 = n.FUN_0042c7b0();
        if (((uVar3 & 1) != 0) && ((cVar1 = n.FUN_00422950(0xbe, 1, 0), cVar1 != '\0')))
        {
          n.FUN_00423530("Bip01_Prop2");
          uVar3 = n.FUN_0065d150();
          if ((uVar3 % 100) < 0x32)
          {
            n.FUN_00422490(0x21, 0, 0x14, 0);
          }
          else
          {
            n.FUN_00422490(0x21, 1, 0x14, 0);
          }
          n.w[0x1eb] = 0x1e;
          n.FUN_00421080(0x15f);
          return;
        }
        if (0x14 < n.w[0x3a])
        {
          n.FUN_00421080(0x169);
          return;
        }
        if (n.w[0x2b81] == 5)
        {
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0x16] = 0x3f000000;
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
        if (((char) n.w[0x21]) != '\0')
        {
          n.w[0x10] = 0;
          n.w[0x16] = 0;
          n.FUN_00421080(0x15e);
          n.FUN_00421100(2);
          return;
        }
        if (n.w[0x2b81] == 8)
        {
          return;
        }
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_15_0_361(FullChargeBodyContext& n)
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
    do
    {
      if ((((char) n.w[0x21]) != '\0') && (((n.source_float(0x10)) < actor_word_real(0x00000000u)) != ((n.source_float(0x10)) == actor_word_real(0x00000000u))))
      {
        n.FUN_00421080(0x1d5);
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        return;
      }
      if ((n.source_float(0x16)) == actor_word_real(0x00000000u))
      {
        n.w[0x16] = 0x3f000000;
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      if (0x14 < n.w[0x2b81])
      {
        n.FUN_00421080(0x2b);
        return;
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_15_1_350(FullChargeBodyContext& n)
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
        n.w[0x16] = 0x3f000000;
        return;
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f400000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042c800(0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      if (n.w[0x2b81] < 0x19)
      {
        n.FUN_0042dc20(0, 0x40a00000);
      }
      if (n.w[0x2b81] == 0x19)
      {
        uVar4 = n.FUN_0065d150();
        if ((uVar4 % 100) < 0x33)
        {
          n.FUN_00422490(0x20, 2, 0x14, 0);
        }
        else
        {
          n.FUN_00422490(0x20, 1, 0x14, 0);
        }
        n.FUN_0042c8b0(0xe5);
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42700000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42f00000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x42700000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x42f00000u), 0);
      }
      if (n.w[0x2b81] == 0x10)
      {
        if (n.w[0x3e] < 1)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0x2b)
      {
        if (n.w[0x3e] < 1)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void full_charge_body_15_1_360(FullChargeBodyContext& n)
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
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.w[0x10] = 0;
        n.FUN_00421080(0x1d5);
        return;
      }
      n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.FUN_0042c800(0);
        n.FUN_00422900();
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] < 10)
      {
        n.FUN_0042dc20(0, 0x41700000);
      }
      if (n.w[0x2b81] < 0x19)
      {
        n.FUN_0042dc20(0, 0x40a00000);
      }
      if (n.w[0x2b81] == 0x19)
      {
        uVar4 = n.FUN_0065d150();
        if ((uVar4 % 100) < 0x33)
        {
          n.FUN_00422490(0x20, 2, 0x14, 0);
        }
        else
        {
          n.FUN_00422490(0x20, 1, 0x14, 0);
        }
        n.FUN_0042c8b0(0xe5);
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_004230e0();
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42700000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x42f00000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) + actor_word_real(0x43340000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x42700000u), 0);
        n.FUN_00435450(6, n.w[5], actor_word_real(0x428c0000u) + (n.source_float(6)), n.w[7], ((n.source_float(0x17)) + (n.source_float(0x19))) - actor_word_real(0x42f00000u), 0);
      }
      if (n.w[0x2b81] == 0x10)
      {
        if (n.w[0x3e] < 1)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0x2b)
      {
        if (n.w[0x3e] < 1)
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        n.write_scratch(0x3e, 0);
      }
      break;
    }
    while (0);
  }
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
bool full_charge_native_body_binding(unsigned ch,unsigned we,unsigned state)
#else
inline bool full_charge_native_body_binding(unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 351:return true;
 case 3350:return true;
 case 3351:return true;
 case 3352:return true;
 case 3360:return true;
 case 3361:return true;
 case 4350:return true;
 case 4351:return true;
 case 4352:return true;
 case 4360:return true;
 case 4361:return true;
 case 5350:return true;
 case 5360:return true;
 case 5361:return true;
 case 6350:return true;
 case 6360:return true;
 case 7350:return true;
 case 7351:return true;
 case 7360:return true;
 case 8350:return true;
 case 8360:return true;
 case 9350:return true;
 case 9360:return true;
 case 10350:return true;
 case 10360:return true;
 case 11350:return true;
 case 11360:return true;
 case 12350:return true;
 case 12360:return true;
 case 13350:return true;
 case 13360:return true;
 case 14350:return true;
 case 14360:return true;
 case 15350:return true;
 case 15360:return true;
 case 15361:return true;
 case 16350:return true;
 case 16360:return true;
 case 17350:return true;
 case 17360:return true;
 case 17361:return true;
 case 18350:return true;
 case 18360:return true;
 case 19350:return true;
 case 19360:return true;
 case 20350:return true;
 case 20360:return true;
 case 21350:return true;
 case 21360:return true;
 case 21361:return true;
 case 22350:return true;
 case 22360:return true;
 case 22361:return true;
 case 23350:return true;
 case 23360:return true;
 case 23361:return true;
 case 24350:return true;
 case 24351:return true;
 case 24360:return true;
 case 25350:return true;
 case 25351:return true;
 case 25360:return true;
 case 25361:return true;
 case 25362:return true;
 case 26350:return true;
 case 26360:return true;
 case 26362:return true;
 case 27350:return true;
 case 27360:return true;
 case 28350:return true;
 case 28360:return true;
 case 29350:return true;
 case 29360:return true;
 case 30350:return true;
 case 30360:return true;
 case 31350:return true;
 case 31360:return true;
 case 32350:return true;
 case 32360:return true;
 case 33350:return true;
 case 33360:return true;
 case 33361:return true;
 case 34350:return true;
 case 34360:return true;
 case 34361:return true;
 case 35350:return true;
 case 35360:return true;
 case 35361:return true;
 case 36350:return true;
 case 36360:return true;
 case 36361:return true;
 case 37350:return true;
 case 37360:return true;
 case 37361:return true;
 case 38350:return true;
 case 38360:return true;
 case 38361:return true;
 case 39350:return true;
 case 39351:return true;
 case 39352:return true;
 case 39360:return true;
 case 39361:return true;
 case 40350:return true;
 case 40351:return true;
 case 40352:return true;
 case 40360:return true;
 case 40361:return true;
 case 41350:return true;
 case 41352:return true;
 case 41359:return true;
 case 41360:return true;
 case 41361:return true;
 case 43350:return true;
 case 43351:return true;
 case 43360:return true;
 case 43361:return true;
 case 45350:return true;
 case 45351:return true;
 case 45352:return true;
 case 45360:return true;
 case 45361:return true;
 case 46350:return true;
 case 46360:return true;
 default:return false;
 }}
#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
void dispatch_full_charge_body(FullChargeBodyContext& n,unsigned ch,unsigned we,unsigned state)
#else
inline void dispatch_full_charge_body(FullChargeBodyContext& n,unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 351:full_charge_body_0_0_351(n);return;
 case 3350:full_charge_body_1_0_350(n);return;
 case 3351:full_charge_body_1_0_351(n);return;
 case 3352:full_charge_body_1_0_352(n);return;
 case 3360:full_charge_body_1_0_360(n);return;
 case 3361:full_charge_body_1_0_361(n);return;
 case 4350:full_charge_body_1_1_350(n);return;
 case 4351:full_charge_body_1_1_351(n);return;
 case 4352:full_charge_body_1_1_352(n);return;
 case 4360:full_charge_body_1_1_360(n);return;
 case 4361:full_charge_body_1_1_361(n);return;
 case 5350:full_charge_body_1_2_350(n);return;
 case 5360:full_charge_body_1_2_360(n);return;
 case 5361:full_charge_body_1_2_361(n);return;
 case 6350:full_charge_body_2_0_350(n);return;
 case 6360:full_charge_body_2_0_360(n);return;
 case 7350:full_charge_body_2_1_350(n);return;
 case 7351:full_charge_body_2_1_351(n);return;
 case 7360:full_charge_body_2_1_360(n);return;
 case 8350:full_charge_body_2_2_350(n);return;
 case 8360:full_charge_body_2_2_360(n);return;
 case 9350:full_charge_body_3_0_350(n);return;
 case 9360:full_charge_body_3_0_360(n);return;
 case 10350:full_charge_body_3_1_350(n);return;
 case 10360:full_charge_body_3_1_360(n);return;
 case 11350:full_charge_body_3_2_350(n);return;
 case 11360:full_charge_body_3_2_360(n);return;
 case 12350:full_charge_body_4_0_350(n);return;
 case 12360:full_charge_body_4_0_360(n);return;
 case 13350:full_charge_body_4_1_350(n);return;
 case 13360:full_charge_body_4_1_360(n);return;
 case 14350:full_charge_body_4_2_350(n);return;
 case 14360:full_charge_body_4_2_360(n);return;
 case 15350:full_charge_body_5_0_350(n);return;
 case 15360:full_charge_body_5_0_360(n);return;
 case 15361:full_charge_body_5_0_361(n);return;
 case 16350:full_charge_body_5_1_350(n);return;
 case 16360:full_charge_body_5_1_360(n);return;
 case 17350:full_charge_body_5_2_350(n);return;
 case 17360:full_charge_body_5_2_360(n);return;
 case 17361:full_charge_body_5_2_361(n);return;
 case 18350:full_charge_body_6_0_350(n);return;
 case 18360:full_charge_body_6_0_360(n);return;
 case 19350:full_charge_body_6_1_350(n);return;
 case 19360:full_charge_body_6_1_360(n);return;
 case 20350:full_charge_body_6_2_350(n);return;
 case 20360:full_charge_body_6_2_360(n);return;
 case 21350:full_charge_body_7_0_350(n);return;
 case 21360:full_charge_body_7_0_360(n);return;
 case 21361:full_charge_body_7_0_361(n);return;
 case 22350:full_charge_body_7_1_350(n);return;
 case 22360:full_charge_body_7_1_360(n);return;
 case 22361:full_charge_body_7_1_361(n);return;
 case 23350:full_charge_body_7_2_350(n);return;
 case 23360:full_charge_body_7_2_360(n);return;
 case 23361:full_charge_body_7_2_361(n);return;
 case 24350:full_charge_body_8_0_350(n);return;
 case 24351:full_charge_body_8_0_351(n);return;
 case 24360:full_charge_body_8_0_360(n);return;
 case 25350:full_charge_body_8_1_350(n);return;
 case 25351:full_charge_body_8_1_351(n);return;
 case 25360:full_charge_body_8_1_360(n);return;
 case 25361:full_charge_body_8_1_361(n);return;
 case 25362:full_charge_body_8_1_362(n);return;
 case 26350:full_charge_body_8_2_350(n);return;
 case 26360:full_charge_body_8_2_360(n);return;
 case 26362:full_charge_body_8_2_362(n);return;
 case 27350:full_charge_body_9_0_350(n);return;
 case 27360:full_charge_body_9_0_360(n);return;
 case 28350:full_charge_body_9_1_350(n);return;
 case 28360:full_charge_body_9_1_360(n);return;
 case 29350:full_charge_body_9_2_350(n);return;
 case 29360:full_charge_body_9_2_360(n);return;
 case 30350:full_charge_body_10_0_350(n);return;
 case 30360:full_charge_body_10_0_360(n);return;
 case 31350:full_charge_body_10_1_350(n);return;
 case 31360:full_charge_body_10_1_360(n);return;
 case 32350:full_charge_body_10_2_350(n);return;
 case 32360:full_charge_body_10_2_360(n);return;
 case 33350:full_charge_body_11_0_350(n);return;
 case 33360:full_charge_body_11_0_360(n);return;
 case 33361:full_charge_body_11_0_361(n);return;
 case 34350:full_charge_body_11_1_350(n);return;
 case 34360:full_charge_body_11_1_360(n);return;
 case 34361:full_charge_body_11_1_361(n);return;
 case 35350:full_charge_body_11_2_350(n);return;
 case 35360:full_charge_body_11_2_360(n);return;
 case 35361:full_charge_body_11_2_361(n);return;
 case 36350:full_charge_body_12_0_350(n);return;
 case 36360:full_charge_body_12_0_360(n);return;
 case 36361:full_charge_body_12_0_361(n);return;
 case 37350:full_charge_body_12_1_350(n);return;
 case 37360:full_charge_body_12_1_360(n);return;
 case 37361:full_charge_body_12_1_361(n);return;
 case 38350:full_charge_body_12_2_350(n);return;
 case 38360:full_charge_body_12_2_360(n);return;
 case 38361:full_charge_body_12_2_361(n);return;
 case 39350:full_charge_body_13_0_350(n);return;
 case 39351:full_charge_body_13_0_351(n);return;
 case 39352:full_charge_body_13_0_352(n);return;
 case 39360:full_charge_body_13_0_360(n);return;
 case 39361:full_charge_body_13_0_361(n);return;
 case 40350:full_charge_body_13_1_350(n);return;
 case 40351:full_charge_body_13_1_351(n);return;
 case 40352:full_charge_body_13_1_352(n);return;
 case 40360:full_charge_body_13_1_360(n);return;
 case 40361:full_charge_body_13_1_361(n);return;
 case 41350:full_charge_body_13_2_350(n);return;
 case 41352:full_charge_body_13_2_352(n);return;
 case 41359:full_charge_body_13_2_359(n);return;
 case 41360:full_charge_body_13_2_360(n);return;
 case 41361:full_charge_body_13_2_361(n);return;
 case 43350:full_charge_body_14_1_350(n);return;
 case 43351:full_charge_body_14_1_351(n);return;
 case 43360:full_charge_body_14_1_360(n);return;
 case 43361:full_charge_body_14_1_361(n);return;
 case 45350:full_charge_body_15_0_350(n);return;
 case 45351:full_charge_body_15_0_351(n);return;
 case 45352:full_charge_body_15_0_352(n);return;
 case 45360:full_charge_body_15_0_360(n);return;
 case 45361:full_charge_body_15_0_361(n);return;
 case 46350:full_charge_body_15_1_350(n);return;
 case 46360:full_charge_body_15_1_360(n);return;
 default:throw std::invalid_argument("No actual original full-charge body binding");
 }}
