// Function: FUN_0042db10
// Address:  0x0042db10
// Source:   batch_decompile (mass dump)
// Hash:     187f13397b7d6f9a


void __thiscall FUN_0042db10(int param_1,float param_2,float param_3)

{
  float10 fVar1;
  float local_8;
  
  local_8 = *(float *)(param_1 + 100) - param_2;
  if (local_8 < -180.0) {
    local_8 = local_8 + 360.0;
  }
  if (180.0 < local_8) {
    local_8 = local_8 - 360.0;
  }
  fVar1 = (float10)FUN_0042df90(local_8);
  if ((float10)param_3 <= fVar1) {
    if (0.0 <= local_8) {
      if ((0.0 < local_8) &&
         (*(float *)(param_1 + 100) = *(float *)(param_1 + 100) - param_3,
         *(float *)(param_1 + 100) < -180.0)) {
        *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 360.0;
      }
    }
    else {
      *(float *)(param_1 + 100) = param_3 + *(float *)(param_1 + 100);
      if (180.0 < *(float *)(param_1 + 100)) {
        *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 360.0;
      }
    }
  }
  else {
    *(float *)(param_1 + 100) = param_2;
  }
  return;
}

