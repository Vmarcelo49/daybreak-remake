// ============================================
// Address:  0x005f6880
// Original: FUN_005f6880
// Status:   unreviewed
// ============================================


void __thiscall FUN_005f6880(int param_1,char param_2)

{
  float10 fVar1;
  float10 fVar2;
  
  if ((*(char *)(param_1 + 0x148) == '\0') || (param_2 != '\0')) {
    if ((*(char *)(param_1 + 0x148) == '\0') && (param_2 != '\0')) {
      fVar1 = (float10)FUN_0042df50(param_1 + 0x3c);
      *(float *)(param_1 + 0x54) = (float)fVar1;
      if (*(float *)(param_1 + 0x54) == 0.0) {
        fVar1 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 100));
        *(float *)(param_1 + 0x3c) = (float)fVar1;
        *(undefined4 *)(param_1 + 0x40) = 0;
        fVar1 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 100));
        *(float *)(param_1 + 0x44) = (float)fVar1;
        *(undefined4 *)(param_1 + 100) = 0;
        *(undefined4 *)(param_1 + 0x6c) = 0;
      }
      else {
        D3DXVec3Normalize(param_1 + 0x3c,param_1 + 0x3c);
        fVar1 = (float10)FUN_00423580(*(undefined4 *)(param_1 + 0x44),
                                      *(undefined4 *)(param_1 + 0x3c));
        *(float *)(param_1 + 100) =
             (float)((fVar1 / (float10)3.1415927) * (float10)180.0 -
                    (float10)*(float *)(param_1 + 0x5c));
        if (180.0 < *(float *)(param_1 + 100)) {
          *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 360.0;
        }
        if (*(float *)(param_1 + 100) < -180.0) {
          *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 360.0;
        }
        fVar1 = (float10)FUN_004365f0(*(undefined4 *)(param_1 + 0x40));
        *(float *)(param_1 + 0x6c) = (float)((fVar1 / (float10)3.1415927) * (float10)180.0);
      }
    }
  }
  else {
    fVar1 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x6c));
    *(float *)(param_1 + 0x40) = (float)(fVar1 * (float10)*(float *)(param_1 + 0x54));
    fVar1 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    fVar2 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x6c));
    *(float *)(param_1 + 0x3c) =
         (float)(fVar2 * (float10)(float)fVar1 * (float10)*(float *)(param_1 + 0x54));
    fVar1 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    fVar2 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x6c));
    *(float *)(param_1 + 0x44) =
         (float)(fVar2 * (float10)(float)fVar1 * (float10)*(float *)(param_1 + 0x54));
  }
  *(char *)(param_1 + 0x148) = param_2;
  return;
}

