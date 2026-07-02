// ============================================
// Address:  0x00697100
// Original: FUN_00697100
// Status:   unreviewed
// ============================================


void __fastcall FUN_00697100(int param_1)

{
  int iVar1;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069fdd6;
  local_10 = ExceptionList;
  local_8 = 3;
  ExceptionList = &local_10;
  local_14 = FUN_0068de10();
  while (local_14 != 0) {
    iVar1 = FUN_006981d0(&local_14);
    (**(code **)(*(int *)(iVar1 + 0xc) + 8))(iVar1 + 0xc);
  }
  FUN_00693630();
  local_14 = FUN_0068de10();
  while (local_14 != 0) {
    iVar1 = FUN_006981d0(&local_14);
    (**(code **)(*(int *)(iVar1 + 0xc) + 8))(iVar1 + 0xc);
  }
  FUN_00693630();
  if (*(int *)(param_1 + 0x60) != 0) {
    if (*(int *)(param_1 + 0x54) != 0) {
      (**(code **)(**(int **)(param_1 + 0x60) + 0x18))
                (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x54));
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    (**(code **)(**(int **)(param_1 + 0x60) + 8))(*(undefined4 *)(param_1 + 0x60));
  }
  local_8._0_1_ = 2;
  FUN_00691d70();
  local_8._0_1_ = 1;
  FUN_00693440();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00693440();
  local_8 = 0xffffffff;
  FUN_0068dbb0();
  ExceptionList = local_10;
  return;
}

