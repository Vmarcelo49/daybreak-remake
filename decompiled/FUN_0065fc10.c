// Function: FUN_0065fc10
// Address:  0x0065fc10
// Source:   batch_decompile (mass dump)
// Hash:     dcfeef7bd6950385


void __fastcall FUN_0065fc10(int *param_1)

{
  int local_8;
  
  if (*param_1 != 0) {
    local_8 = (**(code **)(*(int *)*param_1 + 0x18))(*param_1,0,0x8000);
    do {
      if (local_8 == 0) {
        return;
      }
      local_8 = (**(code **)(*(int *)*param_1 + 0x18))(*param_1,0,0x8000);
      if (local_8 == -0x7fea7ef0) {
        return;
      }
    } while (local_8 != 0x15800e);
  }
  return;
}

