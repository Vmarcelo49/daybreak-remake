// Function: FUN_005f6db0
// Address:  0x005f6db0
// Source:   batch_decompile (mass dump)
// Hash:     4bdde2f1650e5db7


void __thiscall
FUN_005f6db0(int param_1,undefined4 param_2,float param_3,float param_4,float param_5)

{
  float10 fVar1;
  float fVar2;
  float fVar3;
  undefined1 local_18 [12];
  float local_c;
  float local_8;
  
  fVar1 = (float10)FUN_0042df50(param_1 + 0x3c);
  if ((float10)0.0 == fVar1) {
    fVar1 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x6c));
    local_c = (float)fVar1;
    fVar1 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x6c));
    local_8 = (float)fVar1;
    fVar1 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    fVar3 = (float)(fVar1 * (float10)local_8);
    fVar2 = local_c;
    fVar1 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100),local_c,
                                  fVar3);
    FUN_00423750((float)(fVar1 * (float10)local_8),fVar2,fVar3);
    (**(code **)(**(int **)(param_1 + 0x11c) + 0xc))
              (param_2,param_3 + *(float *)(param_1 + 0x14),param_4 + *(float *)(param_1 + 0x18),
               param_5 + *(float *)(param_1 + 0x1c),local_18,*(undefined4 *)(param_1 + 0x38));
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x11c) + 0xc))
              (param_2,param_3 + *(float *)(param_1 + 0x14),param_4 + *(float *)(param_1 + 0x18),
               param_5 + *(float *)(param_1 + 0x1c),param_1 + 0x3c,*(undefined4 *)(param_1 + 0x38));
  }
  return;
}

