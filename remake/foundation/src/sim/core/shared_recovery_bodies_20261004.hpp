#pragma once
// Four 00428510 bodies and three dedicated Satoko State186 slot-6 bodies.
inline void shared_recovery_body_common124(SharedRecoveryContext& n)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  n.w[0x1f5] = -1;
  iVar2 = n.w[0x2b7b];
  ;
  ;
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
    if (n.w[0x2b7d] == 0)
    {
      n.write_scratch(0x3a, 0);
      n.w[0x18] = 0;
      n.w[0x21d] = 0x43340000;
      n.FUN_00421780();
    }
    if (n.w[0x2b7d] == 1)
    {
      n.w[0x21d] = 0x40400000;
      n.FUN_00421780();
      n.w[0x15] = 0x41200000;
      n.write_scratch(0x3a, actor_word_add(n.w[0x3a], 1));
      if ((0x96 < n.w[0x3a]) || ((0x1e < n.w[0x3a]) && (((n.w[0xa1] != 0) || (n.w[0xa2] != 0)) || (n.w[0xa0] != 0))))
      {
        n.FUN_00421100(2);
        return;
      }
    }
    if (n.w[0x2b7d] == 2)
    {
      n.w[0x15] = 0;
      n.w[0x21d] = 0x40c00000;
    }
    break;
  }
  while (0);
  switchD_00428568_caseD_2e:
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);

  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void shared_recovery_body_common128(SharedRecoveryContext& n)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  n.w[0x1f5] = -1;
  iVar2 = n.w[0x2b7b];
  ;
  ;
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
      n.w[0x10] = 0;
      n.FUN_00421080(0x2b);
      n.w[0x16] = 0x3f000000;
      return;
    }
    n.w[0x15] = 0;
    break;
  }
  while (0);
  switchD_00428568_caseD_2e:
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);

  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void shared_recovery_body_common187(SharedRecoveryContext& n)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  n.w[0x1f5] = -1;
  iVar2 = n.w[0x2b7b];
  ;
  ;
  do
  {
  }
  while (0);
  switchD_00428568_caseD_2e:
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);

  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void shared_recovery_body_common190(SharedRecoveryContext& n)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  n.w[0x1f5] = -1;
  iVar2 = n.w[0x2b7b];
  ;
  ;
  do
  {
  }
  while (0);
  switchD_00428568_caseD_2e:
  n.w[0x2b81] = actor_word_add(n.w[0x2b81], 1);

  n.w[0x2b82] = actor_word_add(n.w[0x2b82], 1);
  n.FUN_004212f0();
  if ((n.duration < n.w[0x2b81]) && (n.hold == 0))
  {
    n.FUN_00421100(n.w[0x2b7d] + 1);
  }
  return;
}

inline void shared_recovery_body_satoko186w0(SharedRecoveryContext& n)
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
        if (n.w[0x2b81] == 0)
        {
          uVar14 = 0;
          fVar12 = (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19]));
          fVar5 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, 0);
          fVar7 = (float10) actor_word_real(0x00000000u);
          fVar11 = actor_word_real(n.w[7]);
          fVar6 = (float10) n.FUN_0065d010((actor_word_real(n.w[0x17])) + actor_word_real(0x42b40000u));
          fVar11 = (float) ((fVar6 * ((float10) actor_word_real(0x00000000u))) + ((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar11)))));
          fVar8 = actor_word_real(0x42aa0000u) + (actor_word_real(n.w[6]));
          fVar5 = (float10) n.FUN_0065d050(n.w[0x17], fVar8, fVar11);
          fVar7 = (float10) actor_word_real(0x00000000u);
          fVar13 = actor_word_real(n.w[5]);
          fVar6 = (float10) n.FUN_0065d050((actor_word_real(n.w[0x17])) + actor_word_real(0x42b40000u));
          n.FUN_00435450(0xe, (float) ((fVar6 * ((float10) actor_word_real(0x00000000u))) + ((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar13))))), fVar8, fVar11, fVar12, uVar14);
          n.FUN_00422300(0x27, 0, 0x14, 0);
        }
        break;
      }
      while (0);
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

inline void shared_recovery_body_satoko186w1(SharedRecoveryContext& n)
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
        if (n.w[0x2b81] == 0)
        {
          uVar13 = 0;
          fVar9 = (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19]));
          fVar5 = (float10) n.FUN_0065d010(n.w[0x17], fVar9, 0);
          fVar7 = (float10) actor_word_real(0x00000000u);
          fVar11 = actor_word_real(n.w[7]);
          fVar6 = (float10) n.FUN_0065d010((actor_word_real(n.w[0x17])) + actor_word_real(0x42b40000u));
          fVar11 = (float) ((fVar6 * ((float10) actor_word_real(0x00000000u))) + ((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar11)))));
          fVar8 = actor_word_real(0x42aa0000u) + (actor_word_real(n.w[6]));
          fVar5 = (float10) n.FUN_0065d050(n.w[0x17], fVar8, fVar11);
          fVar7 = (float10) actor_word_real(0x00000000u);
          fVar12 = actor_word_real(n.w[5]);
          fVar6 = (float10) n.FUN_0065d050((actor_word_real(n.w[0x17])) + actor_word_real(0x42b40000u));
          n.FUN_00435450(0x16, (float) ((fVar6 * ((float10) actor_word_real(0x00000000u))) + ((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar12))))), fVar8, fVar11, fVar9, uVar13);
          n.FUN_00422300(0x27, 0, 0x14, 0);
        }
        break;
      }
      while (0);
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

inline void shared_recovery_body_satoko186w2(SharedRecoveryContext& n)
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
        if (n.w[0x2b81] == 0)
        {
          uVar14 = 0;
          fVar12 = (actor_word_real(n.w[0x17])) + (actor_word_real(n.w[0x19]));
          fVar5 = (float10) n.FUN_0065d010(n.w[0x17], fVar12, 0);
          fVar7 = (float10) actor_word_real(0x00000000u);
          fVar11 = actor_word_real(n.w[7]);
          fVar6 = (float10) n.FUN_0065d010((actor_word_real(n.w[0x17])) + actor_word_real(0x42b40000u));
          fVar11 = (float) ((fVar6 * ((float10) actor_word_real(0x00000000u))) + ((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar11)))));
          fVar8 = actor_word_real(0x42aa0000u) + (actor_word_real(n.w[6]));
          fVar5 = (float10) n.FUN_0065d050(n.w[0x17], fVar8, fVar11);
          fVar7 = (float10) actor_word_real(0x00000000u);
          fVar13 = actor_word_real(n.w[5]);
          fVar6 = (float10) n.FUN_0065d050((actor_word_real(n.w[0x17])) + actor_word_real(0x42b40000u));
          n.FUN_00435450(0xc, (float) ((fVar6 * ((float10) actor_word_real(0x00000000u))) + ((float10) ((float) ((fVar5 * fVar7) + ((float10) fVar13))))), fVar8, fVar11, fVar12, uVar14);
          n.FUN_00422300(0x27, 0, 0x14, 0);
        }
        break;
      }
      while (0);
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

inline void dispatch_shared_recovery_body(SharedRecoveryContext& n,unsigned character,unsigned weapon,unsigned state){
 switch(state){
 case 124:shared_recovery_body_common124(n);return;
 case 128:shared_recovery_body_common128(n);return;
 case 187:shared_recovery_body_common187(n);return;
 case 190:shared_recovery_body_common190(n);return;
 case 186:if(character==3){switch(weapon){
 case 0:shared_recovery_body_satoko186w0(n);return;
 case 1:shared_recovery_body_satoko186w1(n);return;
 case 2:shared_recovery_body_satoko186w2(n);return;
 }}break;
 }throw std::invalid_argument("No NEW shared recovery body");
 }
