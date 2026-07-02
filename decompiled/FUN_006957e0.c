// Function: FUN_006957e0
// Address:  0x006957e0
// Source:   batch_decompile (mass dump)
// Hash:     ea81f4e04f473630


int __fastcall FUN_006957e0(int *param_1)

{
  int local_14;
  int local_10;
  int local_8;
  
  if (param_1[0x12] == 1) {
    local_8 = -0x7fffbffb;
  }
  else {
    local_8 = (**(code **)(*param_1 + 0x2c))(param_1,&local_14);
    if (-1 < local_8) {
      FUN_0068d950(param_1 + 7);
      param_1[0x10] = local_14;
      param_1[0x11] = local_10;
      param_1[0xe] = local_14;
      param_1[0xf] = local_10;
      FUN_0068d9a0();
    }
  }
  return local_8;
}

