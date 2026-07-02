// Function: FUN_0068a580
// Address:  0x0068a580
// Source:   batch_decompile (mass dump)
// Hash:     c2041b2d3cbfc52f


void FUN_0068a580(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int local_8;
  
  iVar1 = FUN_006871b0(param_2,&LAB_006ad003_1);
  if (iVar1 == 0) {
    FUN_00689280(param_1,param_2,param_3);
  }
  else {
    if (param_1 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = param_1 + 0x98;
    }
    FUN_0068e090(local_8,param_3);
  }
  return;
}

