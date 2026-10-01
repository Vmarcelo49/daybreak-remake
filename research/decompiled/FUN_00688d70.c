// Function: FUN_00688d70
// Address:  0x00688d70
// Source:   batch_decompile (mass dump)
// Hash:     a6e094947ebdfe2e


undefined4 FUN_00688d70(int param_1,int *param_2)

{
  int iVar1;
  void *pvVar2;
  int local_20;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f53d;
  local_10 = ExceptionList;
  if (param_2 == (int *)0x0) {
    local_14 = 0x80004003;
  }
  else {
    local_14 = 0;
    ExceptionList = &local_10;
    iVar1 = FUN_0068db10();
    if (iVar1 == 1) {
      *param_2 = 0;
      local_14 = 0x80040203;
    }
    else {
      pvVar2 = operator_new(0x14);
      local_8 = 0;
      if (pvVar2 == (void *)0x0) {
        local_20 = 0;
      }
      else {
        local_20 = FUN_00688be0(*(undefined4 *)(param_1 + 8),param_1);
      }
      *param_2 = local_20;
      if (*param_2 == 0) {
        local_14 = 0x8007000e;
      }
    }
  }
  ExceptionList = local_10;
  return local_14;
}

