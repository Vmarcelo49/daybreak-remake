// Function: FUN_00695580
// Address:  0x00695580
// Source:   batch_decompile (mass dump)
// Hash:     362f1556697943ab


int __thiscall FUN_00695580(int param_1,int *param_2)

{
  int iVar1;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_20;
  undefined4 local_1c;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fc5e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x1c);
  local_8 = 0;
  iVar1 = (**(code **)(*param_2 + 0x14))(param_2,&local_20,&local_30);
  local_14 = iVar1;
  if (iVar1 < 0) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
  }
  else {
    *(undefined4 *)(param_1 + 0x38) = local_20;
    *(undefined4 *)(param_1 + 0x3c) = local_1c;
    *(undefined4 *)(param_1 + 0x40) = local_30;
    *(undefined4 *)(param_1 + 0x44) = local_2c;
    *(undefined4 *)(param_1 + 0x48) = 0;
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    iVar1 = 0;
  }
  ExceptionList = local_10;
  return iVar1;
}

