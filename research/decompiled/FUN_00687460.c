// Function: FUN_00687460
// Address:  0x00687460
// Source:   batch_decompile (mass dump)
// Hash:     c74da909ad796295


void FUN_00687460(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int local_c;
  int local_8;
  
  iVar1 = FUN_006871b0(param_2,&LAB_006ad061_3);
  if (iVar1 == 0) {
    iVar1 = FUN_006871b0(param_2,&DAT_006ad9b8);
    if (iVar1 == 0) {
      FUN_0068df80(param_1,param_2,param_3);
    }
    else {
      if (param_1 == 0) {
        local_c = 0;
      }
      else {
        local_c = param_1 + 0xc;
      }
      FUN_0068e090(local_c,param_3);
    }
  }
  else {
    if (param_1 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = param_1 + 0xc;
    }
    FUN_0068e090(local_8,param_3);
  }
  return;
}

