// ============================================
// Address:  0x00688fe0
// Original: FUN_00688fe0
// Status:   unreviewed
// ============================================


uint FUN_00688fe0(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined1 local_58 [72];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f561;
  local_10 = ExceptionList;
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    ExceptionList = &local_10;
    iVar2 = FUN_0068db10();
    if (iVar2 == 1) {
      uVar1 = 0x80040203;
    }
    else {
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + param_2;
      FUN_00686800();
      local_8 = 0;
      iVar2 = (**(code **)(**(int **)(param_1 + 8) + 0x34))(*(int *)(param_1 + 4) + -1,local_58);
      uVar1 = (uint)(iVar2 != 0);
      local_8 = 0xffffffff;
      FUN_006867e0();
    }
  }
  ExceptionList = local_10;
  return uVar1;
}

