// Actual DAT370/371 candidates; NOT enabled, not native parity proof.
#pragma once
inline void special_strike_body_2_0_370(SpecialStrikeBodyContext& n)
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
        return;
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] < 0xe)
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        }
        if (0x17 < n.w[0x2b81])
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
        }
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] < 0xe)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] < 0x20)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
      }
      if (n.w[0x2b81] == 0)
      {
        n.write_scratch(0x3e, 0);
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.FUN_0042c880(0x3e);
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if ((n.w[0x2b81] == 0xd) && (n.w[0x3e] < 5))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (n.w[0x2b81] == 0xe)
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0x420c0000;
      }
      if (n.w[0x2b81] == 0x17)
      {
        n.w[0x15] = 0x41200000;
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if ((n.w[0x2b81] < 0x10) || (0x1d < n.w[0x2b81]))
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
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void special_strike_body_2_1_370(SpecialStrikeBodyContext& n)
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
        return;
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] < 0xe)
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        }
        if (0x17 < n.w[0x2b81])
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
        }
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] < 0xe)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] < 0x20)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
      }
      if (n.w[0x2b81] == 0)
      {
        n.write_scratch(0x3e, 0);
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.FUN_0042c880(0x3e);
        n.FUN_004223d0(0x20, 0x14, 0);
      }
      if ((n.w[0x2b81] == 10) && (n.w[0x3e] < 5))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (n.w[0x2b81] == 0xe)
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0x420c0000;
      }
      if (n.w[0x2b81] == 0x17)
      {
        n.w[0x15] = 0x41200000;
      }
      uVar4 = n.FUN_0042c7b0();
      if ((uVar4 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if ((n.w[0x2b81] < 0x10) || (0x1d < n.w[0x2b81]))
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
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void special_strike_body_2_2_370(SpecialStrikeBodyContext& n)
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
        return;
      }
      if (n.w[0x2b7d] == 0)
      {
        if (n.w[0x2b81] < 0xe)
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        }
        if (0x17 < n.w[0x2b81])
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
        }
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (n.w[0x2b81] < 0xe)
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] < 0x20)
        {
          n.FUN_0042db10(0, 0x40a00000);
        }
      }
      if (n.w[0x2b81] == 0)
      {
        n.write_scratch(0x3e, 0);
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.FUN_0042c880(0x3e);
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if ((n.w[0x2b81] == 0xd) && (n.w[0x3e] < 5))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (n.w[0x2b81] == 0xe)
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0x420c0000;
      }
      if (n.w[0x2b81] == 0x17)
      {
        n.w[0x15] = 0x41200000;
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if ((n.w[0x2b81] < 0x10) || (0x1d < n.w[0x2b81]))
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
  n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
  n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void special_strike_body_3_0_370(SpecialStrikeBodyContext& n)
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
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 1);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41f00000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x27, 1, 0x14, 1);
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b7d] < 2)
      {
        n.FUN_0042db10(0, 0x41c80000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        fVar7 = (float10) n.FUN_0042d980();
        if ((fVar7 < ((float10) actor_word_real(0x47afc800u))) || (2 < n.w[0x2b81]))
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        if ((n.w[0x2b81] < 10) && (n.w[0x3c] == 1))
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3c);
        }
        if ((10 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40a00000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] == 0x18) && (n.w[0x3e] < 0x1e))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
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

inline void special_strike_body_3_1_370(SpecialStrikeBodyContext& n)
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
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 1);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41f00000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x27, 1, 0x14, 1);
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b7d] < 2)
      {
        n.FUN_0042db10(0, 0x41c80000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        fVar7 = (float10) n.FUN_0042d980();
        if ((fVar7 < ((float10) actor_word_real(0x47afc800u))) || (2 < n.w[0x2b81]))
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        if ((n.w[0x2b81] < 10) && (n.w[0x3c] == 1))
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3c);
        }
        if ((10 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40a00000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] == 0x18) && (n.w[0x3e] < 0x1e))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
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

inline void special_strike_body_3_2_370(SpecialStrikeBodyContext& n)
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
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 1);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41f00000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_00422490(0x27, 1, 0x14, 1);
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
      n.w[0x1a1] = 2;
      if (n.w[0x2b7d] < 2)
      {
        n.FUN_0042db10(0, 0x41c80000);
      }
      if (n.w[0x2b7d] == 1)
      {
        n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        fVar7 = (float10) n.FUN_0042d980();
        if ((fVar7 < ((float10) actor_word_real(0x47afc800u))) || (2 < n.w[0x2b81]))
        {
          n.FUN_00421100(2);
          return;
        }
      }
      if (n.w[0x2b7d] == 2)
      {
        if ((n.w[0x2b81] < 10) && (n.w[0x3c] == 1))
        {
          n.FUN_0042db10(0, 0x41700000);
        }
        if (n.w[0x2b81] == 0xc)
        {
          n.FUN_0042c880(0x3c);
        }
        if ((10 < n.w[0x2b81]) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40a00000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] == 0x18) && (n.w[0x3e] < 0x1e))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
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

inline void special_strike_body_4_0_370(SpecialStrikeBodyContext& n)
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
        n.w[0x15] = 0;
        n.FUN_0042db10(0, 0x43340000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      uVar3 = n.FUN_0042c7b0();
      if ((((uVar3 & 0x80) != 0) && ((-1) < n.w[0xc1])) && ((cVar1 = n.FUN_00422950(0xba, 0, 0), cVar1 != '\0')))
      {
        n.w[0x1eb] = 0x1e;
        n.FUN_00421080(0x173);
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

inline void special_strike_body_4_0_371(SpecialStrikeBodyContext& n)
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
    do
    {
      n.FUN_00434a70(0, 0xffffffff);
      n.FUN_00434a70(1, 0xffffffff);
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (n.w[0x2b81] == 0)
      {
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
      }
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      if (n.w[0x2b81] < 0x14)
      {
        n.w[0x1a1] = 5;
      }
      else
      {
        n.w[0x1a1] = -1;
      }
      n.w[0x1eb] = 3;
      if (n.w[0x2b81] < 0x14)
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if ((n.w[0x2b81] == 0x13) && (n.w[0x3e] < 0x3c))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.write_scratch(0x3c, 0);
        fVar6 = (float10) n.FUN_0065d010(n.source_float(0x3c));
        fVar11 = (float) (fVar6 * ((float10) actor_word_real(0x457a0000u)));
        fVar6 = (float10) n.FUN_0065d050(n.source_float(0x3c), fVar11);
        n.FUN_00422bd0(0x87, 0xc6, 0, 1, 0, (float) (fVar6 * ((float10) actor_word_real(0xc57a0000u))), fVar11);
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

inline void special_strike_body_4_1_370(SpecialStrikeBodyContext& n)
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
        n.w[0x15] = 0;
        n.FUN_0042db10(0, 0x43340000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      uVar3 = n.FUN_0042c7b0();
      if ((((uVar3 & 0x80) != 0) && ((-1) < n.w[0xc1])) && ((cVar1 = n.FUN_00422950(0xba, 0, 0), cVar1 != '\0')))
      {
        n.w[0x1eb] = 0x1e;
        n.FUN_00421080(0x173);
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

inline void special_strike_body_4_1_371(SpecialStrikeBodyContext& n)
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
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
      }
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      if (n.w[0x2b81] < 0x1e)
      {
        n.w[0x1a1] = 5;
      }
      n.FUN_00434a70(0, 0xffffffff);
      n.FUN_00434a70(1, 0xffffffff);
      n.w[0x1eb] = 3;
      if (n.w[0x2b81] < 0x14)
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if ((n.w[0x2b81] == 0x13) && (n.w[0x3e] < 0x3c))
      {
        n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        return;
      }
      if (n.w[0x2b81] == 0x13)
      {
        n.write_scratch(0x3c, 0);
        fVar6 = (float10) n.FUN_0065d010(n.source_float(0x3c));
        fVar12 = (float) (fVar6 * ((float10) actor_word_real(0x457a0000u)));
        fVar6 = (float10) n.FUN_0065d050(n.source_float(0x3c), fVar12);
        n.FUN_00422bd0(0x87, 0xc6, 0, 1, 0, (float) (fVar6 * ((float10) actor_word_real(0xc57a0000u))), fVar12);
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

inline void special_strike_body_6_0_370(SpecialStrikeBodyContext& n)
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
      if (n.w[0x2b81] == 0)
      {
        n.write_scratch(0x3a, 0);
        n.w[0x1e9] = 1;
        n.w[0x2bd8] = 1;
        n.FUN_0042c880(0x31);
        n.FUN_00422490(0x14, 1, 0x1e, 0);
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (0x3c < n.w[0x3a])
      {
        n.FUN_00421080(0);
        return;
      }
      if (n.w[0x3a] == 0)
      {
        n.particle(0x168, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
      }
      n.w[0x1a1] = 4;
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      n.w[0x1f0] = 100;
      n.w[0x1f1] = 0x3c;
      n.w[0x1eb] = 0x3c;
      n.w[0x16] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      n.w[0x15] = 0;
      if (n.w[0x2b81] == 0x2c)
      {
        n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], -1));
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

inline void special_strike_body_6_2_370(SpecialStrikeBodyContext& n)
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
      if (n.w[0x2b81] == 0)
      {
        n.write_scratch(0x3a, 0);
        n.w[0x1e9] = 1;
        n.w[0x2bd8] = 1;
        n.FUN_0042c880(0x31);
        n.FUN_00422490(0x14, 1, 0x1e, 0);
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      cVar1 = n.FUN_004218c0();
      if (cVar1 != '\0')
      {
        n.FUN_00421080(0);
        return;
      }
      if (0x3c < n.w[0x3a])
      {
        n.FUN_00421080(0);
        return;
      }
      if (n.w[0x3a] == 0)
      {
        n.particle(0x168, n.w[5], n.w[6], n.w[7], n.w[0x17], 0);
      }
      n.w[0x1a1] = 4;
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      n.w[0x1f0] = 100;
      n.w[0x1f1] = 0x3c;
      n.w[0x1eb] = 0x3c;
      n.w[0x16] = 0;
      n.w[0x18] = 0;
      n.w[0x21d] = 0;
      n.w[0x15] = 0;
      if (n.w[0x2b81] == 0x2c)
      {
        n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], -1));
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

inline void special_strike_body_7_0_370(SpecialStrikeBodyContext& n)
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b7d] == 0)
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c8b0(0x9a);
        n.FUN_004230e0();
        n.FUN_00435000(0, 10, 0, 0, 0);
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

inline void special_strike_body_7_1_370(SpecialStrikeBodyContext& n)
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b7d] == 0)
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c8b0(0x9a);
        n.FUN_004230e0();
        n.FUN_00435000(0, 0xe, 0, 0, 0);
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

inline void special_strike_body_7_2_370(SpecialStrikeBodyContext& n)
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
      if (((char) n.w[0x21]) == '\0')
      {
        n.FUN_00421080(0x2b);
        n.w[0x16] = 0x3f000000;
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if (n.w[0x2b81] < 0xf)
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if (n.w[0x2b7d] == 0)
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c8b0(0x9a);
        n.FUN_004230e0();
        n.FUN_00435000(0, 0x17, 0, 0, 0);
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

inline void special_strike_body_8_0_370(SpecialStrikeBodyContext& n)
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
      if (((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2)) && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_0042c8b0(0x85);
        n.FUN_00421100(2);
        n.FUN_004230e0();
        n.FUN_00435450(8, n.w[5], n.w[6], n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
        n.FUN_0042c8b0(0x28);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        return;
      }
      if (n.w[0x2b7d] < 2)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 0x1e))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
      }
      if ((n.w[0x2b7d] == 0) && ((n.FUN_0042db10(0, 0x3f800000), n.w[0x2b81] == 5)))
      {
        if ((actor_word_real(0x00000000u) <= (n.source_float(0x10))) || ((iVar5 = n.shooting_ftol(n.source_float(0x0b)), (iVar5 % 0x168) != 0)))
        {
          n.w[0xb6] = 0x428c0000;
          n.w[0xb] = actor_real_word(float((n.source_float(0xb)) - actor_word_real(0x41a00000u)));
          return;
        }
        n.w[0xb] = 0;
      }
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.FUN_0042c8b0(0x84);
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0x40a00000;
        n.write_scratch(0x3e, 0);
        n.w[0x10] = 0x42480000;
        n.w[0x18] = 0;
        n.w[0x16] = 0x3f4ccccd;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
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

inline void special_strike_body_8_1_370(SpecialStrikeBodyContext& n)
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
      if (((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2)) && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_0042c8b0(0x85);
        n.FUN_00421100(2);
        n.FUN_004230e0();
        n.FUN_00435450(6, n.w[5], n.w[6], n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
        n.FUN_0042c8b0(0x28);
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        return;
      }
      if (n.w[0x2b7d] < 2)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 0x1e))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
      }
      if ((n.w[0x2b7d] == 0) && ((n.FUN_0042db10(0, 0x3f800000), n.w[0x2b81] == 5)))
      {
        if ((actor_word_real(0x00000000u) <= (n.source_float(0x10))) || ((iVar4 = n.shooting_ftol(n.source_float(0x0b)), (iVar4 % 0x168) != 0)))
        {
          n.w[0xb6] = 0x428c0000;
          n.w[0xb] = actor_real_word(float((n.source_float(0xb)) - actor_word_real(0x41a00000u)));
          return;
        }
        n.w[0xb] = 0;
      }
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.FUN_0042c8b0(0x84);
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0x40a00000;
        n.write_scratch(0x3e, 0);
        n.w[0x10] = 0x42480000;
        n.w[0x18] = 0;
        n.w[0x16] = 0x3f4ccccd;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
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

inline void special_strike_body_8_2_370(SpecialStrikeBodyContext& n)
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
      if (((((char) n.w[0x21]) != '\0') && (n.w[0x2b7d] < 2)) && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))
      {
        n.FUN_0042c8b0(0x85);
        n.FUN_00421100(2);
        n.FUN_004230e0();
        n.FUN_00435450(0x1b, n.w[5], n.w[6], n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
        n.FUN_0042c8b0(0x28);
        n.w[0x16] = 0;
        n.w[0x10] = 0;
        return;
      }
      if (n.w[0x2b7d] < 2)
      {
        n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16))));
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if (((char) n.w[0x21]) == '\0')
        {
          n.FUN_00421080(0x2b);
          n.w[0x16] = 0x3f000000;
          return;
        }
        if ((n.w[0x2b81] == 0x1c) && (n.w[0x3e] < 0x1e))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
      }
      if ((n.w[0x2b7d] == 0) && ((n.FUN_0042db10(0, 0x3f800000), n.w[0x2b81] == 5)))
      {
        if ((actor_word_real(0x00000000u) <= (n.source_float(0x10))) || ((iVar4 = n.shooting_ftol(n.source_float(0x0b)), (iVar4 % 0x168) != 0)))
        {
          n.w[0xb6] = 0x428c0000;
          n.w[0xb] = actor_real_word(float((n.source_float(0xb)) - actor_word_real(0x41a00000u)));
          return;
        }
        n.w[0xb] = 0;
      }
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.FUN_0042c8b0(0x84);
        n.FUN_00422490(0x27, 0, 0x14, 0);
        n.FUN_00422900();
        n.FUN_00423000();
        n.w[0x15] = 0x40a00000;
        n.write_scratch(0x3e, 0);
        n.w[0x10] = 0x42480000;
        n.w[0x18] = 0;
        n.w[0x16] = 0x3f4ccccd;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
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

inline void special_strike_body_9_0_370(SpecialStrikeBodyContext& n)
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
      if (((n.w[0x2b7d] < 2) || (n.w[0x2b7d] == 5)) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 6))
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0x42340000;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xc))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0x14))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((n.w[0x2b81] < 5) && (n.w[0x2b7d] == 1))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] == 3) && (n.w[0x2b7d] == 1))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0x42200000;
        n.w[0x16] = 0x3f800000;
        n.w[0x21d] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(7);
      }
      if (actor_word_real(0x00000000u) < (n.source_float(0x10)))
      {
        n.w[0x1eb] = 3;
      }
      if ((((n.w[0x2b7d] == 2) || (n.w[0x2b7d] == 3)) || (n.w[0x2b7d] == 4)) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), (((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))))
      {
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(5);
        return;
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0xc] = actor_real_word(float((n.source_float(0xc)) - actor_word_real(0x41f00000u)));
        sVar2 = n.FUN_0042c7b0();
        if (sVar2 != 0)
        {
          if (2 < n.w[0x3e])
          {
            n.write_scratch(0x3e, 0);
            n.FUN_0042c800(0);
          }
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        }
        if ((n.source_float(0x10)) < actor_word_real(0x00000000u))
        {
          n.w[0xc] = 0;
          n.FUN_00421100(3);
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

inline void special_strike_body_9_1_370(SpecialStrikeBodyContext& n)
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
      if (((n.w[0x2b7d] < 2) || (n.w[0x2b7d] == 5)) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 6))
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0x42340000;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xc))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0x14))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((n.w[0x2b81] < 5) && (n.w[0x2b7d] == 1))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] == 3) && (n.w[0x2b7d] == 1))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0x42200000;
        n.w[0x16] = 0x3f800000;
        n.w[0x21d] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(7);
      }
      if (actor_word_real(0x00000000u) < (n.source_float(0x10)))
      {
        n.w[0x1eb] = 3;
      }
      if ((((n.w[0x2b7d] == 2) || (n.w[0x2b7d] == 3)) || (n.w[0x2b7d] == 4)) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), (((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))))
      {
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(5);
        return;
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0xc] = actor_real_word(float((n.source_float(0xc)) - actor_word_real(0x41f00000u)));
        sVar2 = n.FUN_0042c7b0();
        if (sVar2 != 0)
        {
          if (2 < n.w[0x3e])
          {
            n.write_scratch(0x3e, 0);
            n.FUN_0042c800(0);
          }
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        }
        if ((n.source_float(0x10)) < actor_word_real(0x00000000u))
        {
          n.w[0xc] = 0;
          n.FUN_00421100(3);
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

inline void special_strike_body_9_2_370(SpecialStrikeBodyContext& n)
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
      if (((n.w[0x2b7d] < 2) || (n.w[0x2b7d] == 5)) && (((char) n.w[0x21]) == '\0'))
      {
        n.FUN_00421080(0x2b);
        return;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x18] = 0;
        n.w[0x15] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 6))
      {
        n.w[0x18] = 0;
        n.w[0x15] = 0x42340000;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xc))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0x14))
      {
        n.FUN_00421100(1);
        return;
      }
      if ((n.w[0x2b81] < 5) && (n.w[0x2b7d] == 1))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b81] == 3) && (n.w[0x2b7d] == 1))
      {
        n.FUN_004223d0(3, 10, 0);
        n.w[0x15] = 0;
        n.w[0x10] = 0x42200000;
        n.w[0x16] = 0x3f800000;
        n.w[0x21d] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(7);
      }
      if (actor_word_real(0x00000000u) < (n.source_float(0x10)))
      {
        n.w[0x1eb] = 3;
      }
      if ((((n.w[0x2b7d] == 2) || (n.w[0x2b7d] == 3)) || (n.w[0x2b7d] == 4)) && ((n.w[0x10] = actor_real_word(float((n.source_float(0x10)) - (n.source_float(0x16)))), (((char) n.w[0x21]) != '\0') && ((n.source_float(0x10)) < actor_word_real(0x00000000u)))))
      {
        n.w[0x10] = 0;
        n.w[0x16] = 0;
        n.w[0x15] = 0;
        n.FUN_00421100(5);
        return;
      }
      if (n.w[0x2b7d] == 2)
      {
        n.w[0xc] = actor_real_word(float((n.source_float(0xc)) - actor_word_real(0x41f00000u)));
        sVar2 = n.FUN_0042c7b0();
        if (sVar2 != 0)
        {
          if (2 < n.w[0x3e])
          {
            n.write_scratch(0x3e, 0);
            n.FUN_0042c800(0);
          }
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
        }
        if ((n.source_float(0x10)) < actor_word_real(0x00000000u))
        {
          n.w[0xc] = 0;
          n.FUN_00421100(3);
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

inline void special_strike_body_10_0_370(SpecialStrikeBodyContext& n)
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
        n.FUN_004223d0(0x27, 0x14, 1);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c8b0(0xa1);
        n.FUN_00435450(0xd, n.w[5], n.w[6], n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
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

inline void special_strike_body_10_1_370(SpecialStrikeBodyContext& n)
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
        n.FUN_004223d0(0x27, 0x14, 1);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c8b0(0xa1);
        n.FUN_00435450(0xc, n.w[5], n.w[6], n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
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

inline void special_strike_body_10_2_370(SpecialStrikeBodyContext& n)
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
        n.FUN_004223d0(0x27, 0x14, 1);
      }
      n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f000000u)));
      if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c8b0(0xa1);
        n.FUN_00435450(9, n.w[5], n.w[6], n.w[7], (n.source_float(0x17)) + (n.source_float(0x19)), 0);
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

inline void special_strike_body_12_0_370(SpecialStrikeBodyContext& n)
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
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] < 0x11)
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if (n.w[0x2b81] == 10)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x11)
      {
        n.FUN_0042c800(0);
        n.write_scratch(0x3d, 0x14);
        n.write_scratch(0x3a, 0);
        while (n.w[0x3a] < 0xf)
        {
          n.FUN_004230e0();
          uVar9 = 0;
          uVar3 = n.FUN_0065d150(0);
          fVar8 = (((float) (((short) (((ulonglong) uVar3) % 0x96)) + (-0x4b))) * actor_word_real(0x3dcccccdu)) + (n.source_float(0x3d));
          uVar3 = n.FUN_0065d150(fVar8);
          n.FUN_00435000(0, 0, ((float) (((short) (((ulonglong) uVar3) % 0x96)) + (-0x4b))) * actor_word_real(0x3dcccccdu), fVar8, uVar9);
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
        }

        n.FUN_004223d0(0x1d, 0x14, 0);
        n.FUN_0042c880(0x97);
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

inline void special_strike_body_12_1_370(SpecialStrikeBodyContext& n)
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
        n.write_scratch(0x3c, 0);
        n.write_scratch(0x3e, 0);
      }
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] < 0x11)
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if (n.w[0x2b81] == 10)
      {
        n.w[0x15] = 0;
      }
      if (((9 < n.w[0x2b81]) && (n.w[0x2b81] < 0x13)) && ((n.write_scratch(0x3c, actor_word_add(n.w[0x3c], 1)), (n.w[0x3c] % 3) == 0)))
      {
        n.FUN_0042c800(0);
        n.write_scratch(0x3d, 0x14);
        n.FUN_0042c8b0(0x9b);
        n.FUN_004230e0();
        n.FUN_00435000(0, 2, 0, 0, 0);
        uVar9 = 0;
        uVar3 = n.FUN_0065d150(0);
        fVar8 = (((float) (((short) (((ulonglong) uVar3) % 10)) + (-5))) * actor_word_real(0x3dcccccdu)) + (n.source_float(0x3d));
        uVar3 = n.FUN_0065d150(fVar8);
        n.FUN_00435000(0, 0xe, ((float) (((short) (((ulonglong) uVar3) % 10)) + (-5))) * actor_word_real(0x3dcccccdu), fVar8, uVar9);
        if (n.w[0x2b81] == 10)
        {
          n.FUN_004223d0(0x1d, 0x14, 0);
        }
      }
      if ((n.w[0x2b81] == 0x12) && (n.w[0x3e] < 10))
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

inline void special_strike_body_12_2_370(SpecialStrikeBodyContext& n)
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
      if (n.w[0x2b81] == 0)
      {
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3a, 0);
        n.FUN_0042db10(0, 0x43340000);
        n.w[0x15] = 0x41700000;
      }
      if (n.w[0x2b81] < 0x11)
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if (n.w[0x2b81] == 10)
      {
        n.w[0x15] = 0;
      }
      if (n.w[0x2b81] == 0x11)
      {
        n.FUN_0042c800(0);
        n.write_scratch(0x3d, 0x14);
        n.FUN_004230e0();
        n.FUN_00435000(0, 0xc, 0, n.source_float(0x3d), 0);
        n.FUN_004223d0(0x1d, 0x14, 0);
        n.FUN_0042c8b0(0xcd);
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

inline void special_strike_body_13_0_370(SpecialStrikeBodyContext& n)
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
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3f000000u)));
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
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41f00000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_0042c8b0(0x95);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 1))
      {
        uVar12 = 0;
        fVar11 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
        n.FUN_00435450(9, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar11, uVar12);
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
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x40e00000);
      }
      if (((n.w[0x2b7d] == 1) && ((n.FUN_0042db10(0, 0x40e00000), 0 < n.w[0x2b81]))) && (0 < n.w[0x2b81]))
      {
        n.FUN_00421100(2);
        return;
      }
      if (((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1)), 10 < n.w[0x2b81]))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40c00000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c880(0x40);
        n.FUN_004223d0(3, 0x14, 0);
      }
      if (((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 0x1a)) && (n.w[0x3e] < 10))
      {
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

inline void special_strike_body_13_1_370(SpecialStrikeBodyContext& n)
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
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3f000000u)));
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
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41f00000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_0042c8b0(0x95);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 1))
      {
        uVar11 = 0;
        fVar10 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar10, 0);
        fVar9 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar9);
        n.FUN_00435450(3, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar9, fVar10, uVar11);
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
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x40e00000);
      }
      if (((n.w[0x2b7d] == 1) && ((n.FUN_0042db10(0, 0x40e00000), 0 < n.w[0x2b81]))) && (0 < n.w[0x2b81]))
      {
        n.FUN_00421100(2);
        return;
      }
      if (((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1)), 10 < n.w[0x2b81]))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40c00000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c880(0x40);
        n.FUN_004223d0(3, 0x14, 0);
      }
      if (((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 0x1a)) && (n.w[0x3e] < 10))
      {
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

inline void special_strike_body_13_2_370(SpecialStrikeBodyContext& n)
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
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3f000000u)));
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
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41f00000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_0042c8b0(0x95);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 1))
      {
        uVar12 = 0;
        fVar11 = (n.source_float(0x17)) + (n.source_float(0x19));
        fVar5 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar11, 0);
        fVar10 = (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(7))));
        fVar8 = actor_word_real(0x42a00000u) + (n.source_float(6));
        fVar5 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar8, fVar10);
        n.FUN_00435450(7, (float) ((fVar5 * ((float10) actor_word_real(0x42c80000u))) + ((float10) (n.source_float(5)))), fVar8, fVar10, fVar11, uVar12);
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
      if (n.w[0x2b7d] == 0)
      {
        n.FUN_0042db10(0, 0x40e00000);
      }
      if (((n.w[0x2b7d] == 1) && ((n.FUN_0042db10(0, 0x40e00000), 0 < n.w[0x2b81]))) && (0 < n.w[0x2b81]))
      {
        n.FUN_00421100(2);
        return;
      }
      if (((n.w[0x2b7d] == 2) && ((n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1)), 10 < n.w[0x2b81]))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40c00000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
      {
        n.w[0x15] = 0;
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 5))
      {
        n.FUN_0042c880(0x40);
        n.FUN_004223d0(3, 0x14, 0);
      }
      if (((n.w[0x2b7d] == 2) && (n.w[0x2b81] == 0x1a)) && (n.w[0x3e] < 10))
      {
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

inline void special_strike_body_14_0_370(SpecialStrikeBodyContext& n)
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
        n.w[0x15] = 0;
        n.w[0x18] = 0;
        n.FUN_0042c800(0);
        n.FUN_0042c840(1);
        n.write_scratch(0x3b, 0);
        n.write_scratch(0x3e, 0);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0xf))
      {
        n.FUN_0042c880(0x3d);
        n.FUN_004223d0(0x21, 0x14, 0);
      }
      if (n.w[0x2b7d] == 0)
      {
        if (((0xf < n.w[0x2b81]) && (n.w[0x2b81] == 0x16)) && (n.w[0x3e] < 7))
        {
          uVar3 = n.w[0x3e] & 0x80000001;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffffe) + 1;
          }
          if (uVar3 == 0)
          {
            uVar13 = 0;
            fVar12 = (n.source_float(0x17)) + (n.source_float(0x19));
            fVar8 = (float10) n.FUN_0065d010((n.source_float(0x17)) + (n.source_float(0x19)), fVar12, 0);
            fVar11 = (float) ((fVar8 * ((float10) actor_word_real(0x428c0000u))) + ((float10) (n.source_float(7))));
            fVar9 = actor_word_real(0x428c0000u) + (n.source_float(6));
            fVar8 = (float10) n.FUN_0065d050((n.source_float(0x17)) + (n.source_float(0x19)), fVar9, fVar11);
            n.FUN_00435450(8, (float) ((fVar8 * ((float10) actor_word_real(0x428c0000u))) + ((float10) (n.source_float(5)))), fVar9, fVar11, fVar12, uVar13);
          }
          n.write_clock(0x2b81, 0x15);
          n.write_clock(0x2b82, 0x15);
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
          return;
        }
        if (n.w[0x2b81] == 0x17)
        {
          n.FUN_00421100(1);
          return;
        }
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] < 0x10))
      {
        n.FUN_0042db10(0, 0x41200000);
      }
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0x10))
      {
        n.w[0x15] = 0x420c0000;
      }
      if ((((n.w[0x2b7d] == 1) && (0 < n.w[0x2b81])) && (actor_word_real(0x00000000u) < (n.source_float(0x15)))) && ((n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x40000000u))), (n.source_float(0x15)) < actor_word_real(0x00000000u))))
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

inline void special_strike_body_15_0_370(SpecialStrikeBodyContext& n)
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
        n.FUN_00422490(0x20, 0, 0x14, 0);
        n.w[0x18] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41c80000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_0042c800(0);
      }
      uVar3 = n.FUN_0042c7b0();
      if ((uVar3 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b7d] < 2)
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 5))
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if (1 < n.w[0x2b7d])
      {
        if ((((n.w[0x2b81] == 2) || (n.w[0x2b81] == 8)) || (n.w[0x2b81] == 0xe)) || (n.w[0x2b81] == 0x14))
        {
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042c880(0x3e);
        }
        if (n.w[0x2b81] == 0x1e)
        {
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042c880(0x3e);
          n.w[0x15] = 0x420c0000;
        }
        if (n.w[0x2b81] == 0x28)
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        }
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] == 0x2e) && (n.w[0x3e] < 0xf))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
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

inline void special_strike_body_15_1_370(SpecialStrikeBodyContext& n)
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
      if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
      {
        n.FUN_00422900();
        n.FUN_00423000();
      }
      if ((n.w[0x2b81] == 0) && (n.w[0x2b7d] == 0))
      {
        n.FUN_00422490(0x20, 0, 0x14, 0);
        n.w[0x18] = 0;
        n.write_scratch(0x3a, 0);
        n.write_scratch(0x3e, 0);
        n.w[0x15] = 0x41c80000;
        n.FUN_0042db10(0, 0x43340000);
        n.FUN_0042c800(0);
      }
      uVar4 = n.FUN_0042c7b0();
      if ((uVar4 & 2) != 0)
      {
        n.FUN_00421080(0x188);
        n.FUN_0042c800(0);
        return;
      }
      if (n.w[0x2b7d] < 2)
      {
        n.FUN_0042db10(0, 0x41a00000);
      }
      if ((n.w[0x2b7d] == 2) && (n.w[0x2b81] < 5))
      {
        n.FUN_0042db10(0, 0x40a00000);
      }
      if (1 < n.w[0x2b7d])
      {
        if ((((n.w[0x2b81] == 2) || (n.w[0x2b81] == 8)) || (n.w[0x2b81] == 0xe)) || (n.w[0x2b81] == 0x14))
        {
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042c880(0x3e);
        }
        if (n.w[0x2b81] == 0x1e)
        {
          n.FUN_0042c800(0);
          n.FUN_0042c840(1);
          n.FUN_0042c880(0x3e);
          n.w[0x15] = 0x420c0000;
        }
        if (n.w[0x2b81] == 0x28)
        {
          n.w[0x15] = actor_real_word(float((n.source_float(0x15)) * actor_word_real(0x3e800000u)));
        }
        n.w[0x15] = actor_real_word(float((n.source_float(0x15)) - actor_word_real(0x3f800000u)));
        if ((n.source_float(0x15)) < actor_word_real(0x00000000u))
        {
          n.w[0x15] = 0;
        }
        if ((n.w[0x2b81] == 0x2e) && (n.w[0x3e] < 0xf))
        {
          n.write_scratch(0x3e, actor_word_add(n.w[0x3e], 1));
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

#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
bool special_strike_native_body_binding(unsigned ch,unsigned we,unsigned state)
#else
inline bool special_strike_native_body_binding(unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 6370:return true;
 case 7370:return true;
 case 8370:return true;
 case 9370:return true;
 case 10370:return true;
 case 11370:return true;
 case 12370:return true;
 case 12371:return true;
 case 13370:return true;
 case 13371:return true;
 case 18370:return true;
 case 20370:return true;
 case 21370:return true;
 case 22370:return true;
 case 23370:return true;
 case 24370:return true;
 case 25370:return true;
 case 26370:return true;
 case 27370:return true;
 case 28370:return true;
 case 29370:return true;
 case 30370:return true;
 case 31370:return true;
 case 32370:return true;
 case 36370:return true;
 case 37370:return true;
 case 38370:return true;
 case 39370:return true;
 case 40370:return true;
 case 41370:return true;
 case 42370:return true;
 case 45370:return true;
 case 46370:return true;
 default:return false;
 }}
#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
void dispatch_special_strike_body(SpecialStrikeBodyContext& n,unsigned ch,unsigned we,unsigned state)
#else
inline void dispatch_special_strike_body(SpecialStrikeBodyContext& n,unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 6370:special_strike_body_2_0_370(n);return;
 case 7370:special_strike_body_2_1_370(n);return;
 case 8370:special_strike_body_2_2_370(n);return;
 case 9370:special_strike_body_3_0_370(n);return;
 case 10370:special_strike_body_3_1_370(n);return;
 case 11370:special_strike_body_3_2_370(n);return;
 case 12370:special_strike_body_4_0_370(n);return;
 case 12371:special_strike_body_4_0_371(n);return;
 case 13370:special_strike_body_4_1_370(n);return;
 case 13371:special_strike_body_4_1_371(n);return;
 case 18370:special_strike_body_6_0_370(n);return;
 case 20370:special_strike_body_6_2_370(n);return;
 case 21370:special_strike_body_7_0_370(n);return;
 case 22370:special_strike_body_7_1_370(n);return;
 case 23370:special_strike_body_7_2_370(n);return;
 case 24370:special_strike_body_8_0_370(n);return;
 case 25370:special_strike_body_8_1_370(n);return;
 case 26370:special_strike_body_8_2_370(n);return;
 case 27370:special_strike_body_9_0_370(n);return;
 case 28370:special_strike_body_9_1_370(n);return;
 case 29370:special_strike_body_9_2_370(n);return;
 case 30370:special_strike_body_10_0_370(n);return;
 case 31370:special_strike_body_10_1_370(n);return;
 case 32370:special_strike_body_10_2_370(n);return;
 case 36370:special_strike_body_12_0_370(n);return;
 case 37370:special_strike_body_12_1_370(n);return;
 case 38370:special_strike_body_12_2_370(n);return;
 case 39370:special_strike_body_13_0_370(n);return;
 case 40370:special_strike_body_13_1_370(n);return;
 case 41370:special_strike_body_13_2_370(n);return;
 case 42370:special_strike_body_14_0_370(n);return;
 case 45370:special_strike_body_15_0_370(n);return;
 case 46370:special_strike_body_15_1_370(n);return;
 default:throw std::invalid_argument("No actual special-strike DAT binding");
 }}
