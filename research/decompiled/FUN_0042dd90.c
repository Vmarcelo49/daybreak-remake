// Function: FUN_0042dd90
// Address:  0x0042dd90
// Source:   batch_decompile (mass dump)
// Hash:     a8f10395111d9dc7


void __fastcall FUN_0042dd90(int param_1)

{
  float fVar1;
  float10 fVar2;
  undefined4 local_8;
  
  fVar2 = (float10)FUN_00423580(*(float *)(*(int *)(param_1 + 0x38) + 0x1c) -
                                *(float *)(param_1 + 0x1c),
                                *(float *)(*(int *)(param_1 + 0x38) + 0x14) -
                                *(float *)(param_1 + 0x14));
  fVar1 = (float)((fVar2 / (float10)3.1415927) * (float10)180.0);
  local_8 = *(float *)(param_1 + 0x5c) - fVar1;
  if (local_8 < -180.0) {
    local_8 = local_8 + 360.0;
  }
  if (180.0 < local_8) {
    local_8 = local_8 - 360.0;
  }
  *(float *)(param_1 + 100) = local_8 + *(float *)(param_1 + 100);
  *(float *)(param_1 + 0x5c) = fVar1;
  if (*(float *)(param_1 + 100) < -180.0) {
    *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 360.0;
  }
  if (180.0 < *(float *)(param_1 + 100)) {
    *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 360.0;
  }
  return;
}

