// Function: FUN_00436ab0
// Address:  0x00436ab0
// Source:   batch_decompile (mass dump)
// Hash:     1bb215af70e67155


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00436ab0(int param_1)

{
  float fVar1;
  float local_2c;
  float local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_14 = (float)((DAT_006d1628 >> 1) + _DAT_006d1620);
  local_10 = (float)((DAT_006d162c >> 1) + _DAT_006d1624);
  local_8 = (float)DAT_006d1628 / 2.0;
  local_c = (float)DAT_006d162c / 2.0;
  local_18 = *(int *)(param_1 + 0x34);
  FUN_00656300(*(undefined4 *)(param_1 + 0x18));
  (**(code **)(*DAT_006d16f8 + 0x170))(DAT_006d16f8,0);
  (**(code **)(*DAT_006d16f8 + 0x164))(DAT_006d16f8,0x144);
  if (1 < *(int *)(param_1 + 0xc)) {
    for (local_20 = 0; local_20 <= *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8);
        local_20 = local_20 + 1) {
      D3DXVec4Transform(local_20 * 0x38 + local_18,local_20 * 0x10 + *(int *)(param_1 + 0x30),
                        &DAT_006d1510);
    }
    if (*(char *)(param_1 + 0x14) == '\0') {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,0);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,2);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,3);
    }
    local_1c = 0;
    for (local_24 = 0; local_24 < *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * 2;
        local_24 = local_24 + 2) {
      FUN_004370d0(*(float *)(local_18 + 4 + (local_24 + 2) * 0x1c) /
                   *(float *)(local_18 + 0xc + (local_24 + 2) * 0x1c) -
                   *(float *)(local_18 + 4 + local_24 * 0x1c) /
                   *(float *)(local_18 + 0xc + local_24 * 0x1c),
                   *(float *)(local_18 + local_24 * 0x1c) /
                   *(float *)(local_18 + 0xc + local_24 * 0x1c) +
                   -(*(float *)(local_18 + (local_24 + 2) * 0x1c) /
                    *(float *)(local_18 + 0xc + (local_24 + 2) * 0x1c)));
      D3DXVec2Normalize(&local_2c,&local_2c);
      FUN_00437100(*(float *)(param_1 + 0x10) / *(float *)(local_18 + 0xc + local_24 * 0x1c));
      FUN_004307e0(*(undefined4 *)(local_18 + 0xc + local_24 * 0x1c));
      fVar1 = *(float *)(local_18 + 8 + local_24 * 0x1c);
      if (fVar1 < 0.0 == (fVar1 == 0.0)) {
        *(float *)(local_18 + (local_24 + 1) * 0x1c) =
             (*(float *)(local_18 + local_24 * 0x1c) - local_2c) * local_8 + local_14;
        *(float *)(local_18 + 4 + (local_24 + 1) * 0x1c) =
             -(*(float *)(local_18 + 4 + local_24 * 0x1c) - local_28) * local_c + local_10;
        *(undefined4 *)(local_18 + 8 + (local_24 + 1) * 0x1c) =
             *(undefined4 *)(local_18 + 8 + local_24 * 0x1c);
        *(undefined4 *)(local_18 + 0xc + (local_24 + 1) * 0x1c) =
             *(undefined4 *)(local_18 + 0xc + local_24 * 0x1c);
        *(float *)(local_18 + local_24 * 0x1c) =
             (local_2c + *(float *)(local_18 + local_24 * 0x1c)) * local_8 + local_14;
        *(float *)(local_18 + 4 + local_24 * 0x1c) =
             -(local_28 + *(float *)(local_18 + 4 + local_24 * 0x1c)) * local_c + local_10;
      }
      else {
        if (2 < local_24 - local_1c) {
          (**(code **)(*DAT_006d16f8 + 0x14c))
                    (DAT_006d16f8,5,(local_24 - local_1c) + -2,local_1c * 0x1c + local_18,0x1c);
        }
        local_1c = local_24 + 2;
      }
    }
    if (2 < local_24 - local_1c) {
      (**(code **)(*DAT_006d16f8 + 0x14c))
                (DAT_006d16f8,5,(local_24 - local_1c) + -2,local_1c * 0x1c + local_18,0x1c);
    }
    if (*(char *)(param_1 + 0x14) == '\0') {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
    }
  }
  return;
}

