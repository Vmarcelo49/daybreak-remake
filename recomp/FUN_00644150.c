// ============================================
// Address:  0x00644150
// Original: FUN_00644150
// Status:   unreviewed
// ============================================


void __thiscall FUN_00644150(int *param_1,float param_2,float param_3,float param_4)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  float local_34;
  uint local_14;
  int local_c;
  
  FUN_00408250(param_4);
  FUN_00655d60(param_4 * 505.0 + param_2,param_4 * 565.0 + param_3);
  FUN_00408250(param_4);
  FUN_00645250(param_4 * 505.0 + param_2,param_4 * 565.0 + param_3);
  FUN_00408250(param_4);
  FUN_00645250(param_4 * 505.0 + param_2,param_4 * 565.0 + param_3);
  FUN_00408250(param_4);
  FUN_00655d60(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3);
  FUN_00408250(param_4);
  cVar1 = *(char *)(param_1[0x2dc] + 0x318);
  if (cVar1 == '\0') {
    if (*(char *)(param_1[0x2dc] + 0x844) == '\0') {
      if (*(int *)(param_1[0x2dc] + 0x838) < *(int *)(param_1[0x2dc] + 0x324)) {
        FUN_00645690(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,param_4);
      }
      else {
        FUN_00408250(param_4);
        FUN_00655830(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,0,
                     (*param_1 % 0x1e) / 0xf + 1);
        FUN_00408250(param_4);
        FUN_00655d60(param_4 * 64.0 + param_2,param_4 * 534.0 + param_3);
      }
    }
    else {
      FUN_00645690(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,param_4);
    }
    FUN_00655830(param_4 * 183.0 + param_2,param_4 * 548.0 + param_3,0,0);
  }
  else if (cVar1 == '\x01') {
    if (*(char *)(param_1[0x2dc] + 0x845) == '\0') {
      if (*(int *)(param_1[0x2dc] + 0x83c) < *(int *)(param_1[0x2dc] + 0x32c)) {
        FUN_00645690(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,param_4);
      }
      else {
        FUN_00408250(param_4);
        FUN_00655830(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,1,
                     (*param_1 % 0x1e) / 0xf + 1);
        FUN_00408250(param_4);
        FUN_00655d60(param_4 * 64.0 + param_2,param_4 * 534.0 + param_3);
      }
    }
    else {
      FUN_00645690(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,param_4);
    }
    FUN_00655830(param_4 * 183.0 + param_2,param_4 * 548.0 + param_3,0,1);
  }
  else if (cVar1 == '\x02') {
    if (*(char *)(param_1[0x2dc] + 0x846) == '\0') {
      if (*(int *)(param_1[0x2dc] + 0x840) < *(int *)(param_1[0x2dc] + 0x324)) {
        FUN_00645690(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,param_4);
      }
      else {
        FUN_00408250(param_4);
        FUN_00655830(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,0,
                     (*param_1 % 0x1e) / 0xf + 1);
        FUN_00408250(param_4);
        FUN_00655d60(param_4 * 64.0 + param_2,param_4 * 534.0 + param_3);
      }
    }
    else {
      FUN_00645690(param_4 * 55.0 + param_2,param_4 * 488.0 + param_3,param_4);
    }
    FUN_00655830(param_4 * 183.0 + param_2,param_4 * 548.0 + param_3,0,2);
  }
  if (*(int *)(param_1[0x2dc] + 0x834) < 1000) {
    FUN_00408250(param_4);
    FUN_00655d60(param_4 * 400.0 + param_2,param_4 * 517.0 + param_3);
    FUN_00645690(param_4 * 400.0 + param_2,param_4 * 517.0 + param_3,param_4);
  }
  if ((-1 < *(char *)(param_1[0x2dc] + 0x310)) && (*(char *)(param_1[0x2dc] + 0x860) == '\0')) {
    if (*(float *)(param_1[0x2dc] + 0x314) <= 0.0) {
      FUN_00408250(param_4);
    }
    else {
      FUN_00408250((*(float *)(param_1[0x2dc] + 0x314) + 1.0) * param_4);
    }
    uVar3 = (int)*(char *)(param_1[0x2dc] + 0x310) & 0x80000003;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
    }
    FUN_00655830(param_4 * 216.0 + param_2,param_4 * 520.0 + param_3,uVar3,
                 (int)((int)*(char *)(param_1[0x2dc] + 0x310) +
                      ((int)*(char *)(param_1[0x2dc] + 0x310) >> 0x1f & 3U)) >> 2);
  }
  FUN_00408250(param_4);
  FUN_00655d60(param_4 * 623.0 + param_2,param_4 * 471.0 + param_3);
  FUN_00408250(param_4);
  FUN_00655d60(param_4 * 597.0 + param_2,param_4 * 517.0 + param_3);
  FUN_00431b20(*(undefined4 *)(param_1[0x2dc] + 0x6dc),param_4 * 702.0 + param_2,
               param_4 * 443.0 + param_3,param_4,0);
  FUN_00431b20(*(undefined4 *)(param_1[0x2dc] + 0x720),param_4 * 676.0 + param_2,
               param_4 * 489.0 + param_3,param_4,0);
  if (*(int *)(param_1[0x2dc] + 0x6dc) == 0) {
    FUN_00408250(param_4);
    FUN_00645250(param_4 * 623.0 + param_2,param_4 * 471.0 + param_3);
  }
  else {
    FUN_00408250(param_4);
    FUN_00645250(param_4 * 623.0 + param_2,param_4 * 471.0 + param_3);
  }
  if (*(int *)(param_1[0x2dc] + 0x720) == 0) {
    FUN_00408250(param_4);
    FUN_00645250(param_4 * 597.0 + param_2,param_4 * 517.0 + param_3);
  }
  else {
    FUN_00408250(param_4);
    FUN_00645250(param_4 * 597.0 + param_2,param_4 * 517.0 + param_3);
    FUN_00408250(param_4);
    FUN_00645250(param_4 * 597.0 + param_2,param_4 * 525.0 + param_3);
    FUN_00408250(param_4);
    FUN_00645250(param_4 * 597.0 + param_2,param_4 * 525.0 + param_3);
  }
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    fVar4 = (float10)FUN_0065d010((float)*param_1);
    FUN_004120f0((float)(fVar4 * (float10)5.0));
    fVar6 = *(float *)(&DAT_006c78f0 + local_c * 4);
    fVar4 = (float10)FUN_0065d010((float)(&DAT_006c78e0)[local_c] * 3.0);
    FUN_00408250((float)(((fVar4 * (float10)20.0 + (float10)(fVar6 * 1.5 + 20.0)) * (float10)param_4
                         ) / (float10)100.0));
  }
  FUN_00655d60(param_4 * 85.0 + param_2,param_4 * 140.0 + param_3);
  FUN_00408250(param_4);
  FUN_00655d60(param_4 * 70.0 + param_2,param_4 * 110.0 + param_3);
  uVar8 = 0;
  fVar6 = param_4 * 80.0 + param_3;
  fVar5 = param_4 * 110.0 + param_2;
  fVar7 = param_4;
  uVar2 = FUN_0066b668(fVar5,fVar6,param_4,0);
  FUN_00431b20(uVar2,fVar5,fVar6,fVar7,uVar8);
  FUN_00431ce0(param_4 * 110.0 + param_2,param_4 * 78.0 + param_3,param_4,5,1);
  FUN_00431b20(DAT_006cf3b0,param_4 * 138.0 + param_2,param_4 * 110.0 + param_3,param_4 * 0.5,0);
  FUN_00431ce0(param_4 * 138.0 + param_2,param_4 * 110.0 + param_3,param_4 * 0.5,5,1);
  if (DAT_006c78e0 != 0) {
    FUN_00431b50(DAT_006c78e8,param_4 * 110.0 + param_2,
                 ((float)DAT_006c78e0 / 2.0 + 30.0) * param_4 + param_3,param_4,0,1);
    FUN_00431ce0(param_4 * 110.0 + param_2,((float)DAT_006c78e0 / 2.0 + 30.0) * param_4 + param_3,
                 param_4,0xd,0);
  }
  FUN_00655d60(param_4 * 715.0 + param_2,param_4 * 140.0 + param_3);
  FUN_00655d60(param_4 * 700.0 + param_2,param_4 * 110.0 + param_3);
  uVar8 = 0;
  fVar6 = param_4 * 80.0 + param_3;
  fVar5 = param_4 * 740.0 + param_2;
  fVar7 = param_4;
  uVar2 = FUN_0066b668(fVar5,fVar6,param_4,0);
  FUN_00431b20(uVar2,fVar5,fVar6,fVar7,uVar8);
  FUN_00431ce0(param_4 * 740.0 + param_2,param_4 * 78.0 + param_3,param_4,5,1);
  FUN_00431b20(DAT_006cf3b4,param_4 * 768.0 + param_2,param_4 * 110.0 + param_3,param_4 * 0.5,0);
  FUN_00431ce0(param_4 * 768.0 + param_2,param_4 * 110.0 + param_3,param_4 * 0.5,5,1);
  if (DAT_006c78e4 != 0) {
    FUN_00431b50(DAT_006c78ec,param_4 * 740.0 + param_2,
                 ((float)DAT_006c78e4 / 2.0 + 30.0) * param_4 + param_3,param_4,0,1);
    FUN_00431ce0(param_4 * 740.0 + param_2,((float)DAT_006c78e4 / 2.0 + 30.0) * param_4 + param_3,
                 param_4,0xd,0);
  }
  if (DAT_006cf3c0 != 0) {
    if (DAT_006cf3c4 + 0x3b < 6000) {
      if (DAT_006cf3c4 + 0x3b < 600) {
        if ((float)((DAT_006cf3c4 + 0x3b) % 0x3c) * 0.05 <= 1.0) {
          local_34 = 1.0;
        }
        else {
          local_34 = (float)((DAT_006cf3c4 + 0x3b) % 0x3c) * 0.05;
        }
        FUN_00431b20((DAT_006cf3c4 + 0x3b) / 0x3c,
                     ((local_34 - 1.0) * 16.0 + 416.0) * param_4 + param_2,
                     (10.0 - (local_34 - 1.0) * 10.0) * param_4 + param_3,param_4 * local_34,0);
      }
      else {
        FUN_00431b20((DAT_006cf3c4 + 0x3b) / 0x3c,param_4 * 428.0 + param_2,param_4 * 10.0 + param_3
                     ,param_4,0);
      }
    }
    else {
      FUN_00431b20((DAT_006cf3c4 + 0x3b) / 0x3c,param_4 * 442.0 + param_2,param_4 * 10.0 + param_3,
                   param_4,0);
    }
  }
  if (DAT_006cfdb0 != '\0') {
    for (local_14 = 0; (int)local_14 < 4; local_14 = local_14 + 1) {
      if (((int)(&DAT_006cfaf8)[local_14] < 4) &&
         ((&DAT_006cfdd1)[(&DAT_006cfb18)[(&DAT_006cfaf8)[local_14]]] != '\0')) {
        uVar3 = local_14 & 0x80000001;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
        }
        FUN_00646cf0((&DAT_006cfb18)[(&DAT_006cfaf8)[local_14]],(float)((int)local_14 / 2) * 692.0,
                     (float)(int)uVar3 * 20.0 + 12.0);
      }
    }
    if (DAT_006cfdb0 == '\x02') {
      FUN_0064c1e0();
    }
  }
  return;
}

