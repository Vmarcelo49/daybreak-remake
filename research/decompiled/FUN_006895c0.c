// Function: FUN_006895c0
// Address:  0x006895c0
// Source:   batch_decompile (mass dump)
// Hash:     298df36b5c299735


int __thiscall FUN_006895c0(undefined4 param_1,undefined4 param_2,int param_3,int *param_4)

{
  int iVar1;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  iVar1 = (**(code **)(*param_4 + 0x14))(param_4,param_1);
  if (-1 < iVar1) {
    local_c = 0;
    local_10 = 0;
    local_8 = 0;
    do {
      iVar1 = (**(code **)(*param_4 + 0xc))(param_4,1,&local_c,&local_10);
      if (iVar1 != 0) {
        if (local_8 != 0) {
          return local_8;
        }
        return -0x7ffbfdf9;
      }
      if ((param_3 == 0) || (iVar1 = FUN_00686dc0(param_3), iVar1 != 0)) {
        local_14 = FUN_00689470(param_2,local_c);
        if (((local_14 < 0) &&
            (((-1 < local_8 && (local_14 != -0x7fffbffb)) && (local_14 != -0x7ff8ffa9)))) &&
           (local_14 != -0x7ffbfdd6)) {
          local_8 = local_14;
        }
      }
      else {
        local_14 = -0x7ffbfdf9;
      }
      FUN_00686ea0(local_c);
    } while (local_14 != 0);
    iVar1 = 0;
  }
  return iVar1;
}

