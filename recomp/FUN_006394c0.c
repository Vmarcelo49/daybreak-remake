// ============================================
// Address:  0x006394c0
// Original: FUN_006394c0
// Status:   unreviewed
// ============================================


void __fastcall FUN_006394c0(int param_1)

{
  undefined4 uVar1;
  float10 fVar2;
  undefined1 *puVar3;
  float fVar4;
  undefined1 local_50 [12];
  undefined1 local_44 [12];
  undefined1 local_38 [12];
  float local_2c;
  float local_28;
  undefined4 local_24 [3];
  float local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
    local_8 = *(int *)(param_1 + 0x129c + local_10 * 4);
    local_14 = local_10;
    while (local_14 = local_14 + 1, local_14 < 4) {
      if (((local_10 != local_14) && (*(char *)(local_8 + 0xaecc) == '\0')) &&
         (local_c = *(int *)(param_1 + 0x129c + local_14 * 4), *(char *)(local_c + 0xaecc) == '\0'))
      {
        FUN_00423750(*(float *)(local_8 + 0x14) - *(float *)(local_c + 0x14),0,
                     *(float *)(local_8 + 0x1c) - *(float *)(local_c + 0x1c));
        fVar2 = (float10)FUN_0042df50(local_24);
        local_2c = (float)fVar2;
        fVar2 = (float10)FUN_0042df90(*(float *)(local_8 + 0x18) - *(float *)(local_c + 0x18));
        local_18 = (float)fVar2;
        if (local_2c == 0.0) {
          local_24[0] = 0x3f800000;
          local_2c = 1.0;
        }
        FUN_0063be70(local_2c);
        if ((local_2c < 60.0) && (local_18 < 60.0)) {
          local_28 = (60.0 - local_2c) / 2.0;
          uVar1 = FUN_004241d0(local_38,local_28);
          FUN_0042cb50(uVar1);
          puVar3 = local_50;
          fVar4 = local_28;
          FUN_0042e0a0(local_44);
          uVar1 = FUN_004241d0(puVar3,fVar4);
          FUN_0042cb50(uVar1);
        }
      }
    }
  }
  return;
}

