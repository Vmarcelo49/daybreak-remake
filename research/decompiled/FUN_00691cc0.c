// Function: FUN_00691cc0
// Address:  0x00691cc0
// Source:   batch_decompile (mass dump)
// Hash:     c5a7da4a2e8d148d


undefined4 FUN_00691cc0(short *param_1,int param_2,short *param_3)

{
  undefined4 local_8;
  
  local_8 = 0;
  if (param_2 == 0) {
    local_8 = 0x80070057;
  }
  else {
    for (; (param_2 != 0 && (*param_3 != 0)); param_3 = param_3 + 1) {
      *param_1 = *param_3;
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    }
    if (param_2 == 0) {
      param_1 = param_1 + -1;
      local_8 = 0x8007007a;
    }
    *param_1 = 0;
  }
  return local_8;
}

