// Function: FUN_0042dc20
// Address:  0x0042dc20
// Source:   batch_decompile (mass dump)
// Hash:     d532d8d01405574f


void __thiscall FUN_0042dc20(int param_1,float param_2,float param_3)

{
  float10 fVar1;
  undefined4 local_8;
  
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
      if (0.0 < local_8) {
        *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - param_3;
        *(float *)(param_1 + 0x60) = param_3 + *(float *)(param_1 + 0x60);
        if (*(float *)(param_1 + 100) < -180.0) {
          *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 360.0;
        }
        if (180.0 < *(float *)(param_1 + 0x60)) {
          *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) - 360.0;
        }
      }
    }
    else {
      *(float *)(param_1 + 100) = param_3 + *(float *)(param_1 + 100);
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) - param_3;
      if (180.0 < *(float *)(param_1 + 100)) {
        *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 360.0;
      }
      if (*(float *)(param_1 + 0x60) < -180.0) {
        *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + 360.0;
      }
    }
  }
  else {
    *(float *)(param_1 + 100) = param_2;
  }
  return;
}

