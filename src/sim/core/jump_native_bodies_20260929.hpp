// Generated NEW jump State40..44 from retained original source.
#pragma once
inline void jump_body_0_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x16] = 0;
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x16] = 0;
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x16] = 0;
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_0_44(JumpBodyContext& n)
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
        cVar2 = n.FUN_004218c0();
        if (cVar2 != '\0')
        {
          n.FUN_00421080(0);
          return;
        }
        n.w[0x16] = 0;
        n.w[0x18] = 0;
        n.w[0x21d] = 0;
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_1_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_0_2_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_0_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_0_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_0_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_0_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_0_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_1_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_1_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_1_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_1_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_1_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_2_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_2_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_2_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_2_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_1_2_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_0_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_1_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_2_2_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40a00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_0_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
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

inline void jump_body_3_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40a00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
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

inline void jump_body_3_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
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

inline void jump_body_3_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
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

inline void jump_body_3_1_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
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

inline void jump_body_3_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40a00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_3_2_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -4), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40a00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.w[0x16] = 0x3f000000;
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_0_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -4), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40a00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.w[0x16] = 0x3f000000;
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_1_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_2_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_2_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41400000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x40400000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -6), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40a00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_2_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x40400000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_2_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x40400000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.w[0x16] = 0x3f000000;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_4_2_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_0_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_0_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41780000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_0_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_0_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_0_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41780000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_1_43(JumpBodyContext& n)
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
        if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
        {
          n.FUN_00421080(0x2c);
          n.w[0x10] = 0;
          return;
        }
        n.w[0x21d] = 0x3f800000;
        if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
        if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
        {
          n.w[0x16] = 0x3f000000;
        }
        n.FUN_00421780();
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_1_44(JumpBodyContext& n)
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
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_2_40(JumpBodyContext& n)
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
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41780000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_2_43(JumpBodyContext& n)
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
          ;
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_5_2_44(JumpBodyContext& n)
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
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_0_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_1_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_6_2_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_0_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_0_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_0_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_0_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_0_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_1_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_1_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_1_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_1_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_1_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_2_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_2_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_2_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_2_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_7_2_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41280000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_0_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41280000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_1_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_2_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_2_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -0xc), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_2_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_2_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_8_2_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_0_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_1_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_9_2_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41280000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_0_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41280000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_1_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41280000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_10_2_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_0_40(JumpBodyContext& n)
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
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_0_43(JumpBodyContext& n)
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
          ;
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_0_44(JumpBodyContext& n)
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
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_1_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_1_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41400000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_1_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_1_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_1_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_2_40(JumpBodyContext& n)
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
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_2_43(JumpBodyContext& n)
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
          ;
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_11_2_44(JumpBodyContext& n)
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
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_0_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_0_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_0_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_0_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_0_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_1_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_1_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41280000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_1_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_1_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_1_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41280000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_12_2_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_0_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_1_44(JumpBodyContext& n)
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
          n.w[0x16] = 0;
          n.w[0x10] = 0;
          n.w[0x18] = 0;
          n.w[0x21d] = 0;
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_2_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_2_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_2_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_2_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_13_2_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_0_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_0_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40a00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_0_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_0_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.w[0x16] = 0x3f000000;
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_0_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_1_40(JumpBodyContext& n)
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
          cVar1 = n.FUN_004218c0();
          if (cVar1 != '\0')
          {
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40a00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40a00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_1_43(JumpBodyContext& n)
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
          ;
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x40400000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.w[0x16] = 0x3f000000;
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_14_1_44(JumpBodyContext& n)
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
          if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
          {
            n.w[0x15] = 0;
          }
          if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_0_40(JumpBodyContext& n)
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
        ;
        {
          do
          {
            cVar1 = n.FUN_004218c0();
            if (cVar1 != '\0')
            {
              n.FUN_00421080(0x29);
              return;
            }
            n.w[0x18] = 0;
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
            n.w[0x16] = 0;
            n.w[0x15] = 0;
            n.w[0x21d] = 0x41900000;
            n.w[0x18] = 0;
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_0_41(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
            {
              n.w[0x10] = 0x41400000;
              n.write_scratch(0x3a, 0);
              if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
            {
              n.FUN_00421080(0x2a);
              return;
            }
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
            if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
            {
              n.w[0x20d] = 0;
            }
            if (n.w[0xa0] == 0)
            {
              n.write_scratch(0x3a, 0);
            }
            if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_0_42(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
              if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
              {
                n.w[0x15] = 0;
              }
            }
            else
            {
              n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
              if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
              {
                n.w[0x15] = 0x40c00000;
              }
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_0_43(JumpBodyContext& n)
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
        ;
        {
          do
          {
            if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
            {
              n.FUN_00421080(0x2c);
              n.w[0x10] = 0;
              return;
            }
            n.w[0x21d] = 0x3f800000;
            if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
            if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
            {
              n.w[0x16] = 0x3f000000;
            }
            n.FUN_00421780();
            break;
          }
          while (0);
        }
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_0_44(JumpBodyContext& n)
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
        ;
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
            if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
            {
              n.w[0x15] = 0;
            }
            if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_1_40(JumpBodyContext& n)
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
            n.FUN_00421080(0x29);
            return;
          }
          n.w[0x18] = 0;
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
          n.w[0x16] = 0;
          n.w[0x15] = 0;
          n.w[0x21d] = 0x41900000;
          n.w[0x18] = 0;
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_1_41(JumpBodyContext& n)
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
          if ((n.w[0x2b7d] == 0) && (n.w[0x2b81] == 0))
          {
            n.w[0x10] = 0x41400000;
            n.write_scratch(0x3a, 0);
            if ((n.w[0x9f] != 0) || (n.w[0x9e] != 0))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          if (((actor_word_real(n.w[0x10])) < actor_word_real(0x40c00000u)) && (n.w[0x2b7d] == 1))
          {
            n.FUN_00421080(0x2a);
            return;
          }
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
          if (((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u)) && ((n.w[0x20d] = actor_word_add(n.w[0x20d], -10), n.w[0x20d] < 0)))
          {
            n.w[0x20d] = 0;
          }
          if (n.w[0xa0] == 0)
          {
            n.write_scratch(0x3a, 0);
          }
          if (((n.w[0x3a] == 0) || (99 < n.w[0x3a])) || (n.w[0x20d] < 1))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_1_42(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          if ((n.w[0x9f] == 0) && (n.w[0x9e] == 0))
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3e4ccccdu)));
            if ((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))
            {
              n.w[0x15] = 0;
            }
          }
          else
          {
            n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3e4ccccdu)));
            if (actor_word_real(0x40c00000u) < (actor_word_real(n.w[0x15])))
            {
              n.w[0x15] = 0x40c00000;
            }
          }
          n.FUN_00421780();
          break;
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_1_43(JumpBodyContext& n)
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
          if ((((char) n.w[0x21]) != '\0') && (((actor_word_real(n.w[0x10])) < actor_word_real(0x00000000u)) != ((actor_word_real(n.w[0x10])) == actor_word_real(0x00000000u))))
          {
            n.FUN_00421080(0x2c);
            n.w[0x10] = 0;
            return;
          }
          n.w[0x21d] = 0x3f800000;
          if ((actor_word_real(n.w[0x16])) == actor_word_real(0x00000000u))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.w[0x10] = actor_real_word(float((actor_word_real(n.w[0x10])) - (actor_word_real(n.w[0x16]))));
          if ((n.w[0xa0] == 0) || (0x3b < ((uint) n.w[0xa0])))
          {
            n.w[0x16] = 0x3f000000;
          }
          n.FUN_00421780();
        }
        while (0);
      }
    }
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void jump_body_15_1_44(JumpBodyContext& n)
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
        if ((actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15]))) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) - actor_word_real(0x3f000000u))), (actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u))))
        {
          n.w[0x15] = 0;
        }
        if (((actor_word_real(n.w[0x15])) < actor_word_real(0x00000000u)) && ((n.w[0x15] = actor_real_word(float((actor_word_real(n.w[0x15])) + actor_word_real(0x3f000000u))), actor_word_real(0x00000000u) < (actor_word_real(n.w[0x15])))))
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
  }
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);
  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
void dispatch_jump_body(JumpBodyContext& n,unsigned ch,unsigned we,unsigned state)
#else
inline void dispatch_jump_body(JumpBodyContext& n,unsigned ch,unsigned we,unsigned state)
#endif
{
 switch((ch*3u+we)*1000u+state){
 case 40: jump_body_0_0_40(n);return;
 case 41: jump_body_0_0_41(n);return;
 case 42: jump_body_0_0_42(n);return;
 case 43: jump_body_0_0_43(n);return;
 case 44: jump_body_0_0_44(n);return;
 case 1040: jump_body_0_1_40(n);return;
 case 1041: jump_body_0_1_41(n);return;
 case 1042: jump_body_0_1_42(n);return;
 case 1043: jump_body_0_1_43(n);return;
 case 1044: jump_body_0_1_44(n);return;
 case 2040: jump_body_0_2_40(n);return;
 case 2041: jump_body_0_2_41(n);return;
 case 2042: jump_body_0_2_42(n);return;
 case 2043: jump_body_0_2_43(n);return;
 case 2044: jump_body_0_2_44(n);return;
 case 3040: jump_body_1_0_40(n);return;
 case 3041: jump_body_1_0_41(n);return;
 case 3042: jump_body_1_0_42(n);return;
 case 3043: jump_body_1_0_43(n);return;
 case 3044: jump_body_1_0_44(n);return;
 case 4040: jump_body_1_1_40(n);return;
 case 4041: jump_body_1_1_41(n);return;
 case 4042: jump_body_1_1_42(n);return;
 case 4043: jump_body_1_1_43(n);return;
 case 4044: jump_body_1_1_44(n);return;
 case 5040: jump_body_1_2_40(n);return;
 case 5041: jump_body_1_2_41(n);return;
 case 5042: jump_body_1_2_42(n);return;
 case 5043: jump_body_1_2_43(n);return;
 case 5044: jump_body_1_2_44(n);return;
 case 6040: jump_body_2_0_40(n);return;
 case 6041: jump_body_2_0_41(n);return;
 case 6042: jump_body_2_0_42(n);return;
 case 6043: jump_body_2_0_43(n);return;
 case 6044: jump_body_2_0_44(n);return;
 case 7040: jump_body_2_1_40(n);return;
 case 7041: jump_body_2_1_41(n);return;
 case 7042: jump_body_2_1_42(n);return;
 case 7043: jump_body_2_1_43(n);return;
 case 7044: jump_body_2_1_44(n);return;
 case 8040: jump_body_2_2_40(n);return;
 case 8041: jump_body_2_2_41(n);return;
 case 8042: jump_body_2_2_42(n);return;
 case 8043: jump_body_2_2_43(n);return;
 case 8044: jump_body_2_2_44(n);return;
 case 9040: jump_body_3_0_40(n);return;
 case 9041: jump_body_3_0_41(n);return;
 case 9042: jump_body_3_0_42(n);return;
 case 9043: jump_body_3_0_43(n);return;
 case 9044: jump_body_3_0_44(n);return;
 case 10040: jump_body_3_1_40(n);return;
 case 10041: jump_body_3_1_41(n);return;
 case 10042: jump_body_3_1_42(n);return;
 case 10043: jump_body_3_1_43(n);return;
 case 10044: jump_body_3_1_44(n);return;
 case 11040: jump_body_3_2_40(n);return;
 case 11041: jump_body_3_2_41(n);return;
 case 11042: jump_body_3_2_42(n);return;
 case 11043: jump_body_3_2_43(n);return;
 case 11044: jump_body_3_2_44(n);return;
 case 12040: jump_body_4_0_40(n);return;
 case 12041: jump_body_4_0_41(n);return;
 case 12042: jump_body_4_0_42(n);return;
 case 12043: jump_body_4_0_43(n);return;
 case 12044: jump_body_4_0_44(n);return;
 case 13040: jump_body_4_1_40(n);return;
 case 13041: jump_body_4_1_41(n);return;
 case 13042: jump_body_4_1_42(n);return;
 case 13043: jump_body_4_1_43(n);return;
 case 13044: jump_body_4_1_44(n);return;
 case 14040: jump_body_4_2_40(n);return;
 case 14041: jump_body_4_2_41(n);return;
 case 14042: jump_body_4_2_42(n);return;
 case 14043: jump_body_4_2_43(n);return;
 case 14044: jump_body_4_2_44(n);return;
 case 15040: jump_body_5_0_40(n);return;
 case 15041: jump_body_5_0_41(n);return;
 case 15042: jump_body_5_0_42(n);return;
 case 15043: jump_body_5_0_43(n);return;
 case 15044: jump_body_5_0_44(n);return;
 case 16040: jump_body_5_1_40(n);return;
 case 16041: jump_body_5_1_41(n);return;
 case 16042: jump_body_5_1_42(n);return;
 case 16043: jump_body_5_1_43(n);return;
 case 16044: jump_body_5_1_44(n);return;
 case 17040: jump_body_5_2_40(n);return;
 case 17041: jump_body_5_2_41(n);return;
 case 17042: jump_body_5_2_42(n);return;
 case 17043: jump_body_5_2_43(n);return;
 case 17044: jump_body_5_2_44(n);return;
 case 18040: jump_body_6_0_40(n);return;
 case 18041: jump_body_6_0_41(n);return;
 case 18042: jump_body_6_0_42(n);return;
 case 18043: jump_body_6_0_43(n);return;
 case 18044: jump_body_6_0_44(n);return;
 case 19040: jump_body_6_1_40(n);return;
 case 19041: jump_body_6_1_41(n);return;
 case 19042: jump_body_6_1_42(n);return;
 case 19043: jump_body_6_1_43(n);return;
 case 19044: jump_body_6_1_44(n);return;
 case 20040: jump_body_6_2_40(n);return;
 case 20041: jump_body_6_2_41(n);return;
 case 20042: jump_body_6_2_42(n);return;
 case 20043: jump_body_6_2_43(n);return;
 case 20044: jump_body_6_2_44(n);return;
 case 21040: jump_body_7_0_40(n);return;
 case 21041: jump_body_7_0_41(n);return;
 case 21042: jump_body_7_0_42(n);return;
 case 21043: jump_body_7_0_43(n);return;
 case 21044: jump_body_7_0_44(n);return;
 case 22040: jump_body_7_1_40(n);return;
 case 22041: jump_body_7_1_41(n);return;
 case 22042: jump_body_7_1_42(n);return;
 case 22043: jump_body_7_1_43(n);return;
 case 22044: jump_body_7_1_44(n);return;
 case 23040: jump_body_7_2_40(n);return;
 case 23041: jump_body_7_2_41(n);return;
 case 23042: jump_body_7_2_42(n);return;
 case 23043: jump_body_7_2_43(n);return;
 case 23044: jump_body_7_2_44(n);return;
 case 24040: jump_body_8_0_40(n);return;
 case 24041: jump_body_8_0_41(n);return;
 case 24042: jump_body_8_0_42(n);return;
 case 24043: jump_body_8_0_43(n);return;
 case 24044: jump_body_8_0_44(n);return;
 case 25040: jump_body_8_1_40(n);return;
 case 25041: jump_body_8_1_41(n);return;
 case 25042: jump_body_8_1_42(n);return;
 case 25043: jump_body_8_1_43(n);return;
 case 25044: jump_body_8_1_44(n);return;
 case 26040: jump_body_8_2_40(n);return;
 case 26041: jump_body_8_2_41(n);return;
 case 26042: jump_body_8_2_42(n);return;
 case 26043: jump_body_8_2_43(n);return;
 case 26044: jump_body_8_2_44(n);return;
 case 27040: jump_body_9_0_40(n);return;
 case 27041: jump_body_9_0_41(n);return;
 case 27042: jump_body_9_0_42(n);return;
 case 27043: jump_body_9_0_43(n);return;
 case 27044: jump_body_9_0_44(n);return;
 case 28040: jump_body_9_1_40(n);return;
 case 28041: jump_body_9_1_41(n);return;
 case 28042: jump_body_9_1_42(n);return;
 case 28043: jump_body_9_1_43(n);return;
 case 28044: jump_body_9_1_44(n);return;
 case 29040: jump_body_9_2_40(n);return;
 case 29041: jump_body_9_2_41(n);return;
 case 29042: jump_body_9_2_42(n);return;
 case 29043: jump_body_9_2_43(n);return;
 case 29044: jump_body_9_2_44(n);return;
 case 30040: jump_body_10_0_40(n);return;
 case 30041: jump_body_10_0_41(n);return;
 case 30042: jump_body_10_0_42(n);return;
 case 30043: jump_body_10_0_43(n);return;
 case 30044: jump_body_10_0_44(n);return;
 case 31040: jump_body_10_1_40(n);return;
 case 31041: jump_body_10_1_41(n);return;
 case 31042: jump_body_10_1_42(n);return;
 case 31043: jump_body_10_1_43(n);return;
 case 31044: jump_body_10_1_44(n);return;
 case 32040: jump_body_10_2_40(n);return;
 case 32041: jump_body_10_2_41(n);return;
 case 32042: jump_body_10_2_42(n);return;
 case 32043: jump_body_10_2_43(n);return;
 case 32044: jump_body_10_2_44(n);return;
 case 33040: jump_body_11_0_40(n);return;
 case 33041: jump_body_11_0_41(n);return;
 case 33042: jump_body_11_0_42(n);return;
 case 33043: jump_body_11_0_43(n);return;
 case 33044: jump_body_11_0_44(n);return;
 case 34040: jump_body_11_1_40(n);return;
 case 34041: jump_body_11_1_41(n);return;
 case 34042: jump_body_11_1_42(n);return;
 case 34043: jump_body_11_1_43(n);return;
 case 34044: jump_body_11_1_44(n);return;
 case 35040: jump_body_11_2_40(n);return;
 case 35041: jump_body_11_2_41(n);return;
 case 35042: jump_body_11_2_42(n);return;
 case 35043: jump_body_11_2_43(n);return;
 case 35044: jump_body_11_2_44(n);return;
 case 36040: jump_body_12_0_40(n);return;
 case 36041: jump_body_12_0_41(n);return;
 case 36042: jump_body_12_0_42(n);return;
 case 36043: jump_body_12_0_43(n);return;
 case 36044: jump_body_12_0_44(n);return;
 case 37040: jump_body_12_1_40(n);return;
 case 37041: jump_body_12_1_41(n);return;
 case 37042: jump_body_12_1_42(n);return;
 case 37043: jump_body_12_1_43(n);return;
 case 37044: jump_body_12_1_44(n);return;
 case 38040: jump_body_12_2_40(n);return;
 case 38041: jump_body_12_2_41(n);return;
 case 38042: jump_body_12_2_42(n);return;
 case 38043: jump_body_12_2_43(n);return;
 case 38044: jump_body_12_2_44(n);return;
 case 39040: jump_body_13_0_40(n);return;
 case 39041: jump_body_13_0_41(n);return;
 case 39042: jump_body_13_0_42(n);return;
 case 39043: jump_body_13_0_43(n);return;
 case 39044: jump_body_13_0_44(n);return;
 case 40040: jump_body_13_1_40(n);return;
 case 40041: jump_body_13_1_41(n);return;
 case 40042: jump_body_13_1_42(n);return;
 case 40043: jump_body_13_1_43(n);return;
 case 40044: jump_body_13_1_44(n);return;
 case 41040: jump_body_13_2_40(n);return;
 case 41041: jump_body_13_2_41(n);return;
 case 41042: jump_body_13_2_42(n);return;
 case 41043: jump_body_13_2_43(n);return;
 case 41044: jump_body_13_2_44(n);return;
 case 42040: jump_body_14_0_40(n);return;
 case 42041: jump_body_14_0_41(n);return;
 case 42042: jump_body_14_0_42(n);return;
 case 42043: jump_body_14_0_43(n);return;
 case 42044: jump_body_14_0_44(n);return;
 case 43040: jump_body_14_1_40(n);return;
 case 43041: jump_body_14_1_41(n);return;
 case 43042: jump_body_14_1_42(n);return;
 case 43043: jump_body_14_1_43(n);return;
 case 43044: jump_body_14_1_44(n);return;
 case 45040: jump_body_15_0_40(n);return;
 case 45041: jump_body_15_0_41(n);return;
 case 45042: jump_body_15_0_42(n);return;
 case 45043: jump_body_15_0_43(n);return;
 case 45044: jump_body_15_0_44(n);return;
 case 46040: jump_body_15_1_40(n);return;
 case 46041: jump_body_15_1_41(n);return;
 case 46042: jump_body_15_1_42(n);return;
 case 46043: jump_body_15_1_43(n);return;
 case 46044: jump_body_15_1_44(n);return;
 default:throw std::invalid_argument("No original jump body binding");
 }}
