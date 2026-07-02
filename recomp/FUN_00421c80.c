// ============================================
// Address:  0x00421c80
// Original: FUN_00421c80
// Status:   unreviewed
// ============================================


void __fastcall FUN_00421c80(int param_1)

{
  int *piVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  undefined4 uVar6;
  uint local_1c;
  
  uVar6 = 2;
  piVar1 = (int *)FUN_00658a10(0);
  fVar2 = (float10)FUN_0040da40(*(float *)(param_1 + 0x14) - *(float *)(*piVar1 + 0x14),uVar6);
  uVar6 = 2;
  piVar1 = (int *)FUN_00658a10(0);
  fVar3 = (float10)FUN_0040da40(*(float *)(param_1 + 0x1c) - *(float *)(*piVar1 + 0x1c),uVar6);
  uVar6 = 2;
  piVar1 = (int *)FUN_00658a10(1);
  fVar4 = (float10)FUN_0040da40(*(float *)(param_1 + 0x14) - *(float *)(*piVar1 + 0x14),uVar6);
  uVar6 = 2;
  piVar1 = (int *)FUN_00658a10(1);
  fVar5 = (float10)FUN_0040da40(*(float *)(param_1 + 0x1c) - *(float *)(*piVar1 + 0x1c),uVar6);
  if (*(int *)(param_1 + 0x30c) == 0) {
    piVar1 = (int *)FUN_00658a10(0);
    if ((*(int *)(*piVar1 + 0x7ac) == 0) ||
       (piVar1 = (int *)FUN_00658a10(1), *(int *)(*piVar1 + 0x7ac) != 0)) {
      piVar1 = (int *)FUN_00658a10(1);
      if ((*(int *)(*piVar1 + 0x7ac) == 0) ||
         (piVar1 = (int *)FUN_00658a10(0), *(int *)(*piVar1 + 0x7ac) != 0)) {
        local_1c = (uint)((float)(fVar5 + (float10)(float)fVar4) <
                         (float)(fVar3 + (float10)(float)fVar2));
        if (*(uint *)(param_1 + 0x300) != local_1c) {
          *(undefined4 *)(param_1 + 0x28c) = 1;
        }
      }
      else if (*(int *)(param_1 + 0x300) != 0) {
        *(undefined4 *)(param_1 + 0x28c) = 1;
      }
    }
    else if (*(int *)(param_1 + 0x300) != 1) {
      *(undefined4 *)(param_1 + 0x28c) = 1;
    }
  }
  return;
}

