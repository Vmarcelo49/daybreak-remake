// NEW whole dash State20/23/24/27/28/30 from retained original source.
#pragma once
inline void dash_body_0_0_20(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.write_scratch(0x3a, 0);
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41880000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41880000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_0_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_0_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_0_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_0_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_0_0_30(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41840000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_0_1_20(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41840000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_0_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_0_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_0_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_0_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_0_1_30(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41840000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_0_2_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.write_scratch(0x3a, 0);
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41f00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41f00000;
            n.FUN_00421780();
            if (5 < n.w[0x2b81])
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x40200000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_0_2_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_0_2_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_0_2_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_0_2_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_0_2_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41380000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41380000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.w[0x16] = 0;
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_1_0_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar5)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41600000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_1_0_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41900000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
            {
              n.w[0x15] = 0x41400000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_1_0_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41900000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
            {
              n.w[0x15] = 0x41400000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_1_0_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41700000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41700000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_1_0_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41700000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41700000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_1_0_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -7);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41680000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41680000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_1_1_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar5)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41700000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_1_1_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41980000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
            {
              n.w[0x15] = 0x41400000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_1_1_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41980000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
            {
              n.w[0x15] = 0x41400000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_1_1_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_1_1_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_1_1_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -7);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41680000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41680000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_1_2_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar5)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41600000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_1_2_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41900000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
            {
              n.w[0x15] = 0x41400000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_1_2_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41900000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
            {
              n.w[0x15] = 0x41400000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_1_2_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41500000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41500000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_1_2_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41500000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41500000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_1_2_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41500000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_2_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar7)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41700000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41700000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_2_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_2_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_2_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_2_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_2_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41780000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41780000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_2_1_20(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar7)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41700000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41700000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_2_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_2_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_2_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_2_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_2_1_30(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41780000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41780000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_2_2_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar7)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41700000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41700000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_2_2_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_2_2_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 10) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_2_2_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_2_2_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_2_2_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41780000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41780000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_3_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar7)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41880000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40b00000;
            n.w[0x15] = 0x41880000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f266666u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 5) && (n.w[0x3a] < 10))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_3_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41b00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41800000u))))
          {
            n.w[0x15] = 0x41800000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_3_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41b00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41800000u))))
          {
            n.w[0x15] = 0x41800000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_3_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_3_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_3_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41580000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41580000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_3_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar7)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41880000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40b00000;
            n.w[0x15] = 0x41880000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f266666u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 5) && (n.w[0x3a] < 10))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
      }
    }
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
      n.FUN_00435450(6, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void dash_body_3_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41b00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41800000u))))
          {
            n.w[0x15] = 0x41800000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
      }
    }
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
      n.FUN_00435450(6, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void dash_body_3_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41b00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41800000u))))
          {
            n.w[0x15] = 0x41800000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
      }
    }
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
      n.FUN_00435450(6, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void dash_body_3_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
      }
    }
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
      n.FUN_00435450(6, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void dash_body_3_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
      }
    }
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
      n.FUN_00435450(6, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void dash_body_3_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41580000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41580000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
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
      n.FUN_00435450(6, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
    else
    {
      n.FUN_00435450(7, n.w[5], (actor_word_real(n.w[6])) + actor_word_real(0x42480000u), n.w[7], (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19])), 0);
    }
  }
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void dash_body_3_2_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xd), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar7)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41600000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40400000;
            n.w[0x15] = 0x41600000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f266666u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 5) && (n.w[0x3a] < 10))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_3_2_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41980000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_3_2_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41980000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_3_2_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_3_2_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_3_2_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xd);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41500000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_4_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x30) == 0x18))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x30) == 0x2f))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41200000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41200000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 3) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_4_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
          {
            n.w[0x15] = 0x41200000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_4_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
          {
            n.w[0x15] = 0x41200000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_4_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41480000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_4_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41480000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_4_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -5);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41300000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41300000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_4_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x30) == 0x18))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x30) == 0x2f))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41200000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41200000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 3) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_4_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
          {
            n.w[0x15] = 0x41200000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_4_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
          {
            n.w[0x15] = 0x41200000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_4_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41480000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_4_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41480000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_4_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -5);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41300000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41300000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_4_2_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -9), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x30) == 0x18))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x30) == 0x2f))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar6)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41840000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41840000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 3) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_4_2_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41ac0000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
            {
              n.w[0x15] = 0x41500000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_4_2_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41ac0000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
            {
              n.w[0x15] = 0x41500000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_4_2_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41680000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41680000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_4_2_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41680000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41680000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_4_2_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41840000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40400000;
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_5_0_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar7)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41a00000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40a00000;
              n.w[0x15] = 0x41a00000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 10))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_5_0_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41a00000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
            {
              n.w[0x15] = 0x41500000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f666666u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            uVar3 = n.w[0x2b81] & 0x80000007;
            if (((int) uVar3) < 0)
            {
              uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
            }
            if (uVar3 == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_5_0_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41a00000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
            {
              n.w[0x15] = 0x41500000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f666666u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            uVar3 = n.w[0x2b81] & 0x80000007;
            if (((int) uVar3) < 0)
            {
              uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
            }
            if (uVar3 == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_5_0_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41780000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_5_0_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41780000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_5_0_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41840000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_5_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41a00000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40a00000;
            n.w[0x15] = 0x41a00000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 10))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_5_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f666666u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_5_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f666666u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_5_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_5_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41780000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_5_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41840000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_5_2_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar7)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41a00000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40a00000;
              n.w[0x15] = 0x41a00000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 10))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_5_2_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41a00000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
            {
              n.w[0x15] = 0x41500000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f666666u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            uVar3 = n.w[0x2b81] & 0x80000007;
            if (((int) uVar3) < 0)
            {
              uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
            }
            if (uVar3 == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_5_2_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41a00000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
            {
              n.w[0x15] = 0x41500000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f666666u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            uVar3 = n.w[0x2b81] & 0x80000007;
            if (((int) uVar3) < 0)
            {
              uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
            }
            if (uVar3 == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_5_2_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41780000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_5_2_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41780000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_5_2_30(DashBodyContext& n)
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
      {
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
            if (n.w[0x2b7d] < 3)
            {
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
              if (n.w[0x2b7d] < 2)
              {
                if (n.w[0xa0] == 0)
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                  if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                  {
                    n.w[0x10] = 0;
                  }
                }
                else
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                  if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                  {
                    n.w[0x10] = 0x41000000;
                  }
                  n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
                }
              }
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x15] = 0x41840000;
              n.w[0x10] = 0;
              n.w[0x21d] = 0x42700000;
              n.w[0x18] = 0;
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
            {
              n.FUN_0042c880(2);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40000000;
              n.w[0x15] = 0x41840000;
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x16] = 0x3f000000;
              n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
              if (((char) n.w[0x21]) != '\0')
              {
                n.FUN_00421080(0x2c);
                n.w[0x10] = 0;
                return;
              }
            }
            n.FUN_00421780();
          }
          while (0);
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

inline void dash_body_6_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41820000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41820000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 4) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_6_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000003;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffffc) + 1;
          }
          if ((uVar3 == 0) && (n.w[0x2b7d] == 2))
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_6_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41980000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41780000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41780000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_6_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xd), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41800000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41800000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 4) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_6_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar5 = n.w[0x2b81] & 0x80000003;
          if (((int) uVar5) < 0)
          {
            uVar5 = ((uVar5 - 1) | 0xfffffffc) + 1;
          }
          if ((uVar5 == 0) && (n.w[0x2b7d] == 2))
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_6_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41980000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41700000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41700000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_6_2_20(DashBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a]))) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) - actor_word_real(0x41200000u))), (actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xd), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41820000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41820000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 4) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_6_2_23(DashBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a]))) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) - actor_word_real(0x41200000u))), (actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000003;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffffc) + 1;
          }
          if ((uVar3 == 0) && (n.w[0x2b7d] == 2))
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_6_2_24(DashBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a]))) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) - actor_word_real(0x41200000u))), (actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41980000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_2_27(DashBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a]))) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) - actor_word_real(0x41200000u))), (actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_2_28(DashBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a]))) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) - actor_word_real(0x41200000u))), (actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_6_2_30(DashBodyContext& n)
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
  if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a]))) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) - actor_word_real(0x41200000u))), (actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u))))
  {
    n.w[0x1a] = 0;
  }
  if (((actor_word_real(n.w[0x1a])) < actor_word_real(0x00000000u)) && ((n.w[0x1a] = actor_real_word(float((actor_word_real(n.w[0x1a])) + actor_word_real(0x41200000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x1a])))))
  {
    n.w[0x1a] = 0;
  }
  iVar5 = n.w[0x2b7b];
  {
    {
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41780000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41780000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_7_0_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar7)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41580000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41580000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_7_0_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41900000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
            {
              n.w[0x15] = 0x41380000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            if ((n.w[0x2b81] % 10) == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_7_0_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41900000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
            {
              n.w[0x15] = 0x41380000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] % 10) == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_7_0_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_7_0_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_7_0_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -7);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41640000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41640000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_7_1_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar7 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar7)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41580000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41580000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_7_1_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41900000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
            {
              n.w[0x15] = 0x41380000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_7_1_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41900000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
            {
              n.w[0x15] = 0x41380000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_7_1_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_7_1_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_7_1_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41640000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41640000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_7_2_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar6)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41580000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41580000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_7_2_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41900000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
            {
              n.w[0x15] = 0x41380000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            if ((n.w[0x2b81] % 10) == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_7_2_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41900000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
            {
              n.w[0x15] = 0x41380000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] % 10) == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_7_2_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_7_2_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41600000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41600000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_7_2_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -7);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41640000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41640000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_8_0_20(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0xd))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0x1f))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41380000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41380000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 5) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_8_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41300000u))))
          {
            n.w[0x15] = 0x41300000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3eb33333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_8_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41300000u))))
          {
            n.w[0x15] = 0x41300000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3eb33333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_8_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_8_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_8_0_30(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x414c0000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x414c0000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_8_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0xd))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0x1f))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41380000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41380000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 5) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_8_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41300000u))))
          {
            n.w[0x15] = 0x41300000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3eb33333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_8_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41300000u))))
          {
            n.w[0x15] = 0x41300000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3eb33333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_8_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_8_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_8_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x414c0000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x414c0000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_8_2_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xb), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0xd))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0x1f))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar5)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41380000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41380000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 5) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_8_2_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41700000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41300000u))))
            {
              n.w[0x15] = 0x41300000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3eb33333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_8_2_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41700000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41300000u))))
            {
              n.w[0x15] = 0x41300000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3eb33333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_8_2_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41580000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41580000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_8_2_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41580000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41580000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_8_2_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x414c0000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x414c0000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_9_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41780000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41780000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 4) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_9_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41580000u))))
          {
            n.w[0x15] = 0x41580000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_9_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
          {
            n.w[0x15] = 0x41380000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_9_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41700000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_9_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41700000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_9_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41700000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41700000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_9_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.write_scratch(0x3a, 0);
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41780000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41780000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 4) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_9_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41580000u))))
          {
            n.w[0x15] = 0x41580000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_9_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
          {
            n.w[0x15] = 0x41380000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_9_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41700000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_9_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41700000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_9_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41700000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41700000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_9_2_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.write_scratch(0x3a, 0);
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41780000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41780000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 4) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_9_2_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41580000u))))
          {
            n.w[0x15] = 0x41580000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_9_2_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41380000u))))
          {
            n.w[0x15] = 0x41380000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_9_2_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41700000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_9_2_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41700000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41700000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_9_2_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41700000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41700000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_10_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -9), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0xc))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0x1e))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41500000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 2) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_10_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x418c0000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_10_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x418c0000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41600000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41600000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_10_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -9), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0xc))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0x1e))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41500000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 2) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_10_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x418c0000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_10_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x418c0000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41600000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41600000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_10_2_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -9), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0xc))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x24) == 0x1e))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41500000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 2) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_10_2_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x418c0000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_10_2_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x418c0000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41400000u))))
          {
            n.w[0x15] = 0x41400000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_2_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_2_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -8), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41580000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41580000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_10_2_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41600000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41600000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_11_0_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar6)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.FUN_0042c880(2);
              n.w[0x15] = 0x41b40000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x3e800000;
              n.w[0x15] = 0x41b40000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 6) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_11_0_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41a80000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_11_0_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41a80000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_11_0_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x416c0000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x416c0000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_11_0_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x416c0000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x416c0000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_11_0_30(DashBodyContext& n)
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
      {
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
            if (n.w[0x2b7d] < 3)
            {
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x2b7d] < 2)
              {
                if (n.w[0xa0] == 0)
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                  if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                  {
                    n.w[0x10] = 0;
                  }
                }
                else
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                  if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                  {
                    n.w[0x10] = 0x41000000;
                  }
                  n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
                }
              }
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x15] = 0x41740000;
              n.w[0x10] = 0;
              n.w[0x21d] = 0x42700000;
              n.w[0x18] = 0;
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
            {
              n.FUN_0042c880(2);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40000000;
              n.w[0x15] = 0x41740000;
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x16] = 0x3f000000;
              n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
              if (((char) n.w[0x21]) != '\0')
              {
                n.FUN_00421080(0x2c);
                n.w[0x10] = 0;
                return;
              }
            }
            n.FUN_00421780();
          }
          while (0);
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

inline void dash_body_11_1_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar6)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41b40000;
              n.write_scratch(0x3a, 0);
              n.FUN_0042c880(2);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x3e800000;
              n.w[0x15] = 0x41b40000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 6) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_11_1_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41a80000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_11_1_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41a80000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_11_1_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x416c0000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x416c0000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_11_1_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x416c0000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x416c0000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_11_1_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41740000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41740000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_11_2_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar6)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.FUN_0042c880(2);
              n.w[0x15] = 0x41b40000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x3e800000;
              n.w[0x15] = 0x41b40000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 6) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_11_2_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41a80000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_11_2_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41a80000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f733333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_11_2_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x416c0000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x416c0000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_11_2_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x416c0000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x416c0000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fa00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_11_2_30(DashBodyContext& n)
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
      {
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
            if (n.w[0x2b7d] < 3)
            {
              n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              if (n.w[0x2b7d] < 2)
              {
                if (n.w[0xa0] == 0)
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                  if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                  {
                    n.w[0x10] = 0;
                  }
                }
                else
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                  if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                  {
                    n.w[0x10] = 0x41000000;
                  }
                  n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
                }
              }
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x15] = 0x41740000;
              n.w[0x10] = 0;
              n.w[0x21d] = 0x42700000;
              n.w[0x18] = 0;
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
            {
              n.FUN_0042c880(2);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40000000;
              n.w[0x15] = 0x41740000;
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x16] = 0x3f000000;
              n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
              if (((char) n.w[0x21]) != '\0')
              {
                n.FUN_00421080(0x2c);
                n.w[0x10] = 0;
                return;
              }
            }
            n.FUN_00421780();
          }
          while (0);
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

inline void dash_body_12_0_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar5)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41480000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41480000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 2) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_12_0_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_12_0_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_12_0_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41500000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41500000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_12_0_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41500000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41500000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_12_0_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41500000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_12_1_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar5)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41480000;
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41480000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 2) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_12_1_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_12_1_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41780000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_12_1_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41500000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41500000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_12_1_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41500000;
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41500000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_12_1_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41500000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_12_2_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41480000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41480000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 2) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_12_2_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_12_2_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41780000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_12_2_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41500000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41500000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_12_2_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41500000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41500000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_12_2_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41500000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41500000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_13_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xf), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41b40000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40c00000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 10))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_13_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41f00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fc00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_13_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41f00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fc00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_13_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41940000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_13_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41940000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_13_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41580000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41580000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_13_1_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xf), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41b40000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40c00000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 10))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_13_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41f00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fc00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_13_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41f00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fc00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_13_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41940000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_13_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41940000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_13_1_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41580000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41580000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_13_2_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xf), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar5)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41b40000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40c00000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 10))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_13_2_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41f00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fc00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_13_2_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41f00000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3fc00000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41500000u))))
          {
            n.w[0x15] = 0x41500000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          uVar3 = n.w[0x2b81] & 0x80000007;
          if (((int) uVar3) < 0)
          {
            uVar3 = ((uVar3 - 1) | 0xfffffff8) + 1;
          }
          if (uVar3 == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_13_2_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41940000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_13_2_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xe), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41940000;
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41940000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_13_2_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -9);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41580000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41580000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_14_0_20(DashBodyContext& n)
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -9), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar8 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar8)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41680000;
            n.write_scratch(0x3a, 0);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40a00000;
            n.w[0x15] = 0x41680000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 3) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_14_0_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41840000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
          {
            n.w[0x15] = 0x41200000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_14_0_24(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41840000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
          {
            n.w[0x15] = 0x41200000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_14_0_27(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x418c0000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x418c0000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_14_0_28(DashBodyContext& n)
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
      {
        do
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x418c0000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x418c0000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_14_0_30(DashBodyContext& n)
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
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -7);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41780000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41780000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

inline void dash_body_14_1_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              if ((((n.byte(0x845)) == '\0') && (((char) n.w[0x211]) == '\0')) && ((n.byte(0x846)) == '\0'))
              {
                n.w[0x20d] = actor_word_add(n.w[0x20d], -10);
              }
              else
              {
                n.w[0x20d] = actor_word_add(n.w[0x20d], -7);
              }
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar6)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41580000;
              if ((((n.byte(0x845)) != '\0') || (((char) n.w[0x211]) != '\0')) || ((n.byte(0x846)) != '\0'))
              {
                n.w[0x15] = 0x41780000;
              }
              n.write_scratch(0x3a, 0);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x41000000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3ecccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 3) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_14_1_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41780000;
              if (((n.byte(0x845)) != '\0') || ((((char) n.w[0x211]) != '\0') || ((n.byte(0x846)) != '\0')))
              {
                n.w[0x15] = 0x418c0000;
              }
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
            {
              n.w[0x15] = 0x41200000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_14_1_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -6);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41780000;
              if (((n.byte(0x845)) != '\0') || ((((char) n.w[0x211]) != '\0') || ((n.byte(0x846)) != '\0')))
              {
                n.w[0x15] = 0x418c0000;
              }
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41200000u))))
            {
              n.w[0x15] = 0x41200000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_14_1_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41780000;
              if (((n.byte(0x845)) != '\0') || ((((char) n.w[0x211]) != '\0') || ((n.byte(0x846)) != '\0')))
              {
                n.w[0x15] = 0x418c0000;
              }
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_14_1_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41780000;
              if (((n.byte(0x845)) != '\0') || ((((char) n.w[0x211]) != '\0') || ((n.byte(0x846)) != '\0')))
              {
                n.w[0x15] = 0x418c0000;
              }
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            break;
          }
          while (0);
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

inline void dash_body_14_1_30(DashBodyContext& n)
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
      {
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
            if (n.w[0x2b7d] < 2)
            {
              if ((((n.byte(0x845)) == '\0') && (((char) n.w[0x211]) == '\0')) && ((n.byte(0x846)) == '\0'))
              {
                n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
              }
              else
              {
                n.w[0x20d] = actor_word_add(n.w[0x20d], -7);
              }
              if (n.w[0x2b7d] < 2)
              {
                if (n.w[0xa0] == 0)
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                  if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                  {
                    n.w[0x10] = 0;
                  }
                }
                else
                {
                  n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                  if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                  {
                    n.w[0x10] = 0x41000000;
                  }
                  n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
                }
              }
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x15] = 0x41680000;
              if (((n.byte(0x845)) != '\0') || ((((char) n.w[0x211]) != '\0') || ((n.byte(0x846)) != '\0')))
              {
                n.w[0x15] = 0x41800000;
              }
              n.w[0x10] = 0;
              n.w[0x21d] = 0x42700000;
              n.w[0x18] = 0;
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
            {
              n.FUN_0042c880(2);
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40000000;
              if ((((n.byte(0x845)) != '\0') || (((char) n.w[0x211]) != '\0')) || ((n.byte(0x846)) != '\0'))
              {
                n.w[0x21d] = 0x41200000;
              }
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x16] = 0x3f000000;
              n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
              if (((char) n.w[0x21]) != '\0')
              {
                n.FUN_00421080(0x2c);
                n.w[0x10] = 0;
                return;
              }
            }
            n.FUN_00421780();
          }
          while (0);
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

inline void dash_body_15_0_20(DashBodyContext& n)
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
      {
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
              n.FUN_00421080(0x1e);
              return;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
            {
              n.FUN_0042c8b0(5);
            }
            if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
            {
              n.FUN_0042c8b0(6);
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.write_scratch(0x3a, 0);
              n.w[0x18] = 0;
              n.w[0x19] = 0;
              fVar5 = (float10) n.FUN_0042df90(n.w[0x19]);
              if (((float10) actor_word_real(0x41400000u)) <= fVar5)
              {
                if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
                {
                  if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                  {
                    n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                  }
                }
                else
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = 0;
              }
              n.w[0x15] = 0x41880000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0x40800000;
              n.w[0x15] = 0x41880000;
              n.FUN_00421780();
              if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
              {
                n.FUN_00421100(2);
                return;
              }
            }
            if (n.w[0x2b7d] == 2)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
              if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
              {
                n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
                return;
              }
            }
            break;
          }
          while (0);
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

inline void dash_body_15_0_23(DashBodyContext& n)
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
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = -0x3d4c0000;
              n.w[0x15] = 0x41a00000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = -0x3d4c0000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if (n.w[0x2b7d] == 2)
            {
              if (((char) n.w[0x21]) == '\0')
              {
                n.w[0x16] = 0x3f000000;
                n.FUN_00421080(0x2b);
                return;
              }
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            if ((n.w[0x2b81] % 9) == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_15_0_24(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if (n.w[0x2b7d] < 2)
            {
              n.FUN_0042db10(0, 0x41a00000);
              n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
              if (n.w[0x20d] < 0)
              {
                n.w[0x20d] = 0;
              }
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x42b40000;
              n.w[0x15] = 0x41a00000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x18] = 0x42b40000;
            }
            if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
            {
              n.w[0x15] = 0x41480000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] % 9) == 0)
            {
              n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
              n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
            }
            break;
          }
          while (0);
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

inline void dash_body_15_0_27(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41680000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41680000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_15_0_28(DashBodyContext& n)
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
      {
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
            if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
              n.w[0x19] = 0;
              n.w[0x18] = 0x43340000;
              n.w[0x15] = 0x41680000;
            }
            if (n.w[0x2b7d] == 1)
            {
              n.w[0x21d] = 0;
              n.w[0x15] = 0x41680000;
              n.w[0x18] = 0x43340000;
            }
            if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
          }
          while (0);
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

inline void dash_body_15_0_30(DashBodyContext& n)
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
      {
        {
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41840000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
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

inline void dash_body_15_1_20(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
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
            n.FUN_00421080(0x1e);
            return;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 6))
          {
            n.FUN_0042c8b0(5);
          }
          if ((n.w[0x2b7d] == 1) && ((n.w[0x2b81] % 0x16) == 0x11))
          {
            n.FUN_0042c8b0(6);
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.write_scratch(0x3a, 0);
            n.w[0x18] = 0;
            n.w[0x19] = 0;
            fVar6 = (float10) n.FUN_0042df90(n.w[0x19]);
            if (((float10) actor_word_real(0x41400000u)) <= fVar6)
            {
              if (actor_word_real(0x00000000u) <= (actor_word_real(n.w[0x19])))
              {
                if (actor_word_real(0x00000000u) < (actor_word_real(n.w[0x19])))
                {
                  n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) - actor_word_real(0x41200000u)));
                }
              }
              else
              {
                n.w[0x19] = actor_real_word(float((actor_word_real(n.w[0x19])) + actor_word_real(0x41200000u)));
              }
            }
            else
            {
              n.w[0x19] = 0;
            }
            n.w[0x15] = 0x41880000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40800000;
            n.w[0x15] = 0x41880000;
            n.FUN_00421780();
            if (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f400000u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
            if ((n.w[0x2b81] == 1) && (n.w[0x3a] < 0xf))
            {
              n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
              return;
            }
          }
          break;
        }
        while (0);
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

inline void dash_body_15_1_23(DashBodyContext& n)
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
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = -0x3d4c0000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = -0x3d4c0000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if (n.w[0x2b7d] == 2)
          {
            if (((char) n.w[0x21]) == '\0')
            {
              n.w[0x16] = 0x3f000000;
              n.FUN_00421080(0x2b);
              return;
            }
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_15_1_24(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if (n.w[0x2b7d] < 2)
          {
            n.FUN_0042db10(0, 0x41a00000);
            n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc);
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x42b40000;
            n.w[0x15] = 0x41a00000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x18] = 0x42b40000;
          }
          if ((n.w[0x2b7d] < 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x41480000u))))
          {
            n.w[0x15] = 0x41480000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f333333u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if ((n.w[0x2b81] % 9) == 0)
          {
            n.write_clock(0x2b81, actor_word_add(n.w[0x2b81], 1));
            n.write_clock(0x2b82, actor_word_add(n.w[0x2b82], 1));
          }
          break;
        }
        while (0);
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

inline void dash_body_15_1_27(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_15_1_28(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            if (actor_word_real(0x41200000u) < (actor_word_real(n.w[0x1f])))
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
          if ((n.w[0x2b7d] < 2) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x2bd2] = actor_word_add(n.w[0x2bd2], 1);
            n.w[0x19] = 0;
            n.w[0x18] = 0x43340000;
            n.w[0x15] = 0x41680000;
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0;
            n.w[0x15] = 0x41680000;
            n.w[0x18] = 0x43340000;
          }
          if ((n.w[0x2b7d] == 2) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f800000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          break;
        }
        while (0);
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

inline void dash_body_15_1_30(DashBodyContext& n)
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
      {
        do
        {
          cVar2 = n.FUN_004218c0();
          if (cVar2 != '\0')
          {
            n.w[0x16] = 0x3f000000;
            n.FUN_00421080(0x2b);
            return;
          }
          if (n.w[0x2b7d] < 3)
          {
            n.w[0x20d] = actor_word_add(n.w[0x20d], -8);
            if (n.w[0x2b7d] < 2)
            {
              if (n.w[0xa0] == 0)
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - actor_word_real(0x3f000000u)));
                if ((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u))
                {
                  n.w[0x10] = 0;
                }
              }
              else
              {
                n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) + actor_word_real(0x3f000000u)));
                if (actor_word_real(0x41000000u) < (actor_word_real(n.w[0x10])))
                {
                  n.w[0x10] = 0x41000000;
                }
                n.w[0x20d] = actor_word_add(n.w[0x20d], -3);
              }
            }
            if (n.w[0x20d] < 0)
            {
              n.w[0x20d] = 0;
            }
          }
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x15] = 0x41840000;
            n.w[0x10] = 0;
            n.w[0x21d] = 0x42700000;
            n.w[0x18] = 0;
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x2b7d] == 1) && (n.w[0x2b81] == 0)) && (n.w[0x3a] == 0))
          {
            n.FUN_0042c880(2);
          }
          if (n.w[0x2b7d] == 1)
          {
            n.w[0x21d] = 0x40000000;
            n.w[0x15] = 0x41840000;
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if ((5 < n.w[0x3a]) && (((n.w[0x9f] == 0) && (n.w[0x9e] == 0)) || (n.w[0x20d] < 1)))
            {
              n.FUN_00421100(2);
              return;
            }
          }
          if (n.w[0x2b7d] == 2)
          {
            n.w[0x16] = 0x3f000000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if (((char) n.w[0x21]) != '\0')
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
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

#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
void dispatch_dash_body(DashBodyContext& n,unsigned ch,unsigned we,unsigned state)
#else
inline void dispatch_dash_body(DashBodyContext& n,unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 20: dash_body_0_0_20(n);return;
 case 23: dash_body_0_0_23(n);return;
 case 24: dash_body_0_0_24(n);return;
 case 27: dash_body_0_0_27(n);return;
 case 28: dash_body_0_0_28(n);return;
 case 30: dash_body_0_0_30(n);return;
 case 1020: dash_body_0_1_20(n);return;
 case 1023: dash_body_0_1_23(n);return;
 case 1024: dash_body_0_1_24(n);return;
 case 1027: dash_body_0_1_27(n);return;
 case 1028: dash_body_0_1_28(n);return;
 case 1030: dash_body_0_1_30(n);return;
 case 2020: dash_body_0_2_20(n);return;
 case 2023: dash_body_0_2_23(n);return;
 case 2024: dash_body_0_2_24(n);return;
 case 2027: dash_body_0_2_27(n);return;
 case 2028: dash_body_0_2_28(n);return;
 case 2030: dash_body_0_2_30(n);return;
 case 3020: dash_body_1_0_20(n);return;
 case 3023: dash_body_1_0_23(n);return;
 case 3024: dash_body_1_0_24(n);return;
 case 3027: dash_body_1_0_27(n);return;
 case 3028: dash_body_1_0_28(n);return;
 case 3030: dash_body_1_0_30(n);return;
 case 4020: dash_body_1_1_20(n);return;
 case 4023: dash_body_1_1_23(n);return;
 case 4024: dash_body_1_1_24(n);return;
 case 4027: dash_body_1_1_27(n);return;
 case 4028: dash_body_1_1_28(n);return;
 case 4030: dash_body_1_1_30(n);return;
 case 5020: dash_body_1_2_20(n);return;
 case 5023: dash_body_1_2_23(n);return;
 case 5024: dash_body_1_2_24(n);return;
 case 5027: dash_body_1_2_27(n);return;
 case 5028: dash_body_1_2_28(n);return;
 case 5030: dash_body_1_2_30(n);return;
 case 6020: dash_body_2_0_20(n);return;
 case 6023: dash_body_2_0_23(n);return;
 case 6024: dash_body_2_0_24(n);return;
 case 6027: dash_body_2_0_27(n);return;
 case 6028: dash_body_2_0_28(n);return;
 case 6030: dash_body_2_0_30(n);return;
 case 7020: dash_body_2_1_20(n);return;
 case 7023: dash_body_2_1_23(n);return;
 case 7024: dash_body_2_1_24(n);return;
 case 7027: dash_body_2_1_27(n);return;
 case 7028: dash_body_2_1_28(n);return;
 case 7030: dash_body_2_1_30(n);return;
 case 8020: dash_body_2_2_20(n);return;
 case 8023: dash_body_2_2_23(n);return;
 case 8024: dash_body_2_2_24(n);return;
 case 8027: dash_body_2_2_27(n);return;
 case 8028: dash_body_2_2_28(n);return;
 case 8030: dash_body_2_2_30(n);return;
 case 9020: dash_body_3_0_20(n);return;
 case 9023: dash_body_3_0_23(n);return;
 case 9024: dash_body_3_0_24(n);return;
 case 9027: dash_body_3_0_27(n);return;
 case 9028: dash_body_3_0_28(n);return;
 case 9030: dash_body_3_0_30(n);return;
 case 10020: dash_body_3_1_20(n);return;
 case 10023: dash_body_3_1_23(n);return;
 case 10024: dash_body_3_1_24(n);return;
 case 10027: dash_body_3_1_27(n);return;
 case 10028: dash_body_3_1_28(n);return;
 case 10030: dash_body_3_1_30(n);return;
 case 11020: dash_body_3_2_20(n);return;
 case 11023: dash_body_3_2_23(n);return;
 case 11024: dash_body_3_2_24(n);return;
 case 11027: dash_body_3_2_27(n);return;
 case 11028: dash_body_3_2_28(n);return;
 case 11030: dash_body_3_2_30(n);return;
 case 12020: dash_body_4_0_20(n);return;
 case 12023: dash_body_4_0_23(n);return;
 case 12024: dash_body_4_0_24(n);return;
 case 12027: dash_body_4_0_27(n);return;
 case 12028: dash_body_4_0_28(n);return;
 case 12030: dash_body_4_0_30(n);return;
 case 13020: dash_body_4_1_20(n);return;
 case 13023: dash_body_4_1_23(n);return;
 case 13024: dash_body_4_1_24(n);return;
 case 13027: dash_body_4_1_27(n);return;
 case 13028: dash_body_4_1_28(n);return;
 case 13030: dash_body_4_1_30(n);return;
 case 14020: dash_body_4_2_20(n);return;
 case 14023: dash_body_4_2_23(n);return;
 case 14024: dash_body_4_2_24(n);return;
 case 14027: dash_body_4_2_27(n);return;
 case 14028: dash_body_4_2_28(n);return;
 case 14030: dash_body_4_2_30(n);return;
 case 15020: dash_body_5_0_20(n);return;
 case 15023: dash_body_5_0_23(n);return;
 case 15024: dash_body_5_0_24(n);return;
 case 15027: dash_body_5_0_27(n);return;
 case 15028: dash_body_5_0_28(n);return;
 case 15030: dash_body_5_0_30(n);return;
 case 16020: dash_body_5_1_20(n);return;
 case 16023: dash_body_5_1_23(n);return;
 case 16024: dash_body_5_1_24(n);return;
 case 16027: dash_body_5_1_27(n);return;
 case 16028: dash_body_5_1_28(n);return;
 case 16030: dash_body_5_1_30(n);return;
 case 17020: dash_body_5_2_20(n);return;
 case 17023: dash_body_5_2_23(n);return;
 case 17024: dash_body_5_2_24(n);return;
 case 17027: dash_body_5_2_27(n);return;
 case 17028: dash_body_5_2_28(n);return;
 case 17030: dash_body_5_2_30(n);return;
 case 18020: dash_body_6_0_20(n);return;
 case 18023: dash_body_6_0_23(n);return;
 case 18024: dash_body_6_0_24(n);return;
 case 18027: dash_body_6_0_27(n);return;
 case 18028: dash_body_6_0_28(n);return;
 case 18030: dash_body_6_0_30(n);return;
 case 19020: dash_body_6_1_20(n);return;
 case 19023: dash_body_6_1_23(n);return;
 case 19024: dash_body_6_1_24(n);return;
 case 19027: dash_body_6_1_27(n);return;
 case 19028: dash_body_6_1_28(n);return;
 case 19030: dash_body_6_1_30(n);return;
 case 20020: dash_body_6_2_20(n);return;
 case 20023: dash_body_6_2_23(n);return;
 case 20024: dash_body_6_2_24(n);return;
 case 20027: dash_body_6_2_27(n);return;
 case 20028: dash_body_6_2_28(n);return;
 case 20030: dash_body_6_2_30(n);return;
 case 21020: dash_body_7_0_20(n);return;
 case 21023: dash_body_7_0_23(n);return;
 case 21024: dash_body_7_0_24(n);return;
 case 21027: dash_body_7_0_27(n);return;
 case 21028: dash_body_7_0_28(n);return;
 case 21030: dash_body_7_0_30(n);return;
 case 22020: dash_body_7_1_20(n);return;
 case 22023: dash_body_7_1_23(n);return;
 case 22024: dash_body_7_1_24(n);return;
 case 22027: dash_body_7_1_27(n);return;
 case 22028: dash_body_7_1_28(n);return;
 case 22030: dash_body_7_1_30(n);return;
 case 23020: dash_body_7_2_20(n);return;
 case 23023: dash_body_7_2_23(n);return;
 case 23024: dash_body_7_2_24(n);return;
 case 23027: dash_body_7_2_27(n);return;
 case 23028: dash_body_7_2_28(n);return;
 case 23030: dash_body_7_2_30(n);return;
 case 24020: dash_body_8_0_20(n);return;
 case 24023: dash_body_8_0_23(n);return;
 case 24024: dash_body_8_0_24(n);return;
 case 24027: dash_body_8_0_27(n);return;
 case 24028: dash_body_8_0_28(n);return;
 case 24030: dash_body_8_0_30(n);return;
 case 25020: dash_body_8_1_20(n);return;
 case 25023: dash_body_8_1_23(n);return;
 case 25024: dash_body_8_1_24(n);return;
 case 25027: dash_body_8_1_27(n);return;
 case 25028: dash_body_8_1_28(n);return;
 case 25030: dash_body_8_1_30(n);return;
 case 26020: dash_body_8_2_20(n);return;
 case 26023: dash_body_8_2_23(n);return;
 case 26024: dash_body_8_2_24(n);return;
 case 26027: dash_body_8_2_27(n);return;
 case 26028: dash_body_8_2_28(n);return;
 case 26030: dash_body_8_2_30(n);return;
 case 27020: dash_body_9_0_20(n);return;
 case 27023: dash_body_9_0_23(n);return;
 case 27024: dash_body_9_0_24(n);return;
 case 27027: dash_body_9_0_27(n);return;
 case 27028: dash_body_9_0_28(n);return;
 case 27030: dash_body_9_0_30(n);return;
 case 28020: dash_body_9_1_20(n);return;
 case 28023: dash_body_9_1_23(n);return;
 case 28024: dash_body_9_1_24(n);return;
 case 28027: dash_body_9_1_27(n);return;
 case 28028: dash_body_9_1_28(n);return;
 case 28030: dash_body_9_1_30(n);return;
 case 29020: dash_body_9_2_20(n);return;
 case 29023: dash_body_9_2_23(n);return;
 case 29024: dash_body_9_2_24(n);return;
 case 29027: dash_body_9_2_27(n);return;
 case 29028: dash_body_9_2_28(n);return;
 case 29030: dash_body_9_2_30(n);return;
 case 30020: dash_body_10_0_20(n);return;
 case 30023: dash_body_10_0_23(n);return;
 case 30024: dash_body_10_0_24(n);return;
 case 30027: dash_body_10_0_27(n);return;
 case 30028: dash_body_10_0_28(n);return;
 case 30030: dash_body_10_0_30(n);return;
 case 31020: dash_body_10_1_20(n);return;
 case 31023: dash_body_10_1_23(n);return;
 case 31024: dash_body_10_1_24(n);return;
 case 31027: dash_body_10_1_27(n);return;
 case 31028: dash_body_10_1_28(n);return;
 case 31030: dash_body_10_1_30(n);return;
 case 32020: dash_body_10_2_20(n);return;
 case 32023: dash_body_10_2_23(n);return;
 case 32024: dash_body_10_2_24(n);return;
 case 32027: dash_body_10_2_27(n);return;
 case 32028: dash_body_10_2_28(n);return;
 case 32030: dash_body_10_2_30(n);return;
 case 33020: dash_body_11_0_20(n);return;
 case 33023: dash_body_11_0_23(n);return;
 case 33024: dash_body_11_0_24(n);return;
 case 33027: dash_body_11_0_27(n);return;
 case 33028: dash_body_11_0_28(n);return;
 case 33030: dash_body_11_0_30(n);return;
 case 34020: dash_body_11_1_20(n);return;
 case 34023: dash_body_11_1_23(n);return;
 case 34024: dash_body_11_1_24(n);return;
 case 34027: dash_body_11_1_27(n);return;
 case 34028: dash_body_11_1_28(n);return;
 case 34030: dash_body_11_1_30(n);return;
 case 35020: dash_body_11_2_20(n);return;
 case 35023: dash_body_11_2_23(n);return;
 case 35024: dash_body_11_2_24(n);return;
 case 35027: dash_body_11_2_27(n);return;
 case 35028: dash_body_11_2_28(n);return;
 case 35030: dash_body_11_2_30(n);return;
 case 36020: dash_body_12_0_20(n);return;
 case 36023: dash_body_12_0_23(n);return;
 case 36024: dash_body_12_0_24(n);return;
 case 36027: dash_body_12_0_27(n);return;
 case 36028: dash_body_12_0_28(n);return;
 case 36030: dash_body_12_0_30(n);return;
 case 37020: dash_body_12_1_20(n);return;
 case 37023: dash_body_12_1_23(n);return;
 case 37024: dash_body_12_1_24(n);return;
 case 37027: dash_body_12_1_27(n);return;
 case 37028: dash_body_12_1_28(n);return;
 case 37030: dash_body_12_1_30(n);return;
 case 38020: dash_body_12_2_20(n);return;
 case 38023: dash_body_12_2_23(n);return;
 case 38024: dash_body_12_2_24(n);return;
 case 38027: dash_body_12_2_27(n);return;
 case 38028: dash_body_12_2_28(n);return;
 case 38030: dash_body_12_2_30(n);return;
 case 39020: dash_body_13_0_20(n);return;
 case 39023: dash_body_13_0_23(n);return;
 case 39024: dash_body_13_0_24(n);return;
 case 39027: dash_body_13_0_27(n);return;
 case 39028: dash_body_13_0_28(n);return;
 case 39030: dash_body_13_0_30(n);return;
 case 40020: dash_body_13_1_20(n);return;
 case 40023: dash_body_13_1_23(n);return;
 case 40024: dash_body_13_1_24(n);return;
 case 40027: dash_body_13_1_27(n);return;
 case 40028: dash_body_13_1_28(n);return;
 case 40030: dash_body_13_1_30(n);return;
 case 41020: dash_body_13_2_20(n);return;
 case 41023: dash_body_13_2_23(n);return;
 case 41024: dash_body_13_2_24(n);return;
 case 41027: dash_body_13_2_27(n);return;
 case 41028: dash_body_13_2_28(n);return;
 case 41030: dash_body_13_2_30(n);return;
 case 42020: dash_body_14_0_20(n);return;
 case 42023: dash_body_14_0_23(n);return;
 case 42024: dash_body_14_0_24(n);return;
 case 42027: dash_body_14_0_27(n);return;
 case 42028: dash_body_14_0_28(n);return;
 case 42030: dash_body_14_0_30(n);return;
 case 43020: dash_body_14_1_20(n);return;
 case 43023: dash_body_14_1_23(n);return;
 case 43024: dash_body_14_1_24(n);return;
 case 43027: dash_body_14_1_27(n);return;
 case 43028: dash_body_14_1_28(n);return;
 case 43030: dash_body_14_1_30(n);return;
 case 45020: dash_body_15_0_20(n);return;
 case 45023: dash_body_15_0_23(n);return;
 case 45024: dash_body_15_0_24(n);return;
 case 45027: dash_body_15_0_27(n);return;
 case 45028: dash_body_15_0_28(n);return;
 case 45030: dash_body_15_0_30(n);return;
 case 46020: dash_body_15_1_20(n);return;
 case 46023: dash_body_15_1_23(n);return;
 case 46024: dash_body_15_1_24(n);return;
 case 46027: dash_body_15_1_27(n);return;
 case 46028: dash_body_15_1_28(n);return;
 case 46030: dash_body_15_1_30(n);return;
 default:throw std::invalid_argument("No original dash body binding");
 }}
