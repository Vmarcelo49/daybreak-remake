// Function: FUN_00433d90
// Address:  0x00433d90
// Source:   batch_decompile (mass dump)
// Hash:     420b8009a20eaa9e


void __fastcall FUN_00433d90(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e55e;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 4) != 0) {
    ExceptionList = &local_10;
    if (*(int *)(param_1 + 4) != 0) {
      ExceptionList = &local_10;
      FUN_004355d0(3);
    }
    *(undefined4 *)(param_1 + 4) = 0;
  }
  if (*(int *)(param_1 + 8) != 0) {
    _free(*(void **)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  if (*(int *)(param_1 + 4) != 0) {
    if (*(int *)(param_1 + 4) != 0) {
      FUN_004355d0(3);
    }
    *(undefined4 *)(param_1 + 4) = 0;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    _free(*(void **)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  local_8 = 0xffffffff;
  FUN_005f7f90();
  ExceptionList = local_10;
  return;
}

