// Function: FUN_0068f8c0
// Address:  0x0068f8c0
// Source:   batch_decompile (mass dump)
// Hash:     2d482c3300027dc9


undefined4 __fastcall FUN_0068f8c0(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f9a2;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x94);
  local_8 = 0;
  if (*(int *)(param_1 + 0x6c) != 0) {
    (**(code **)(**(int **)(param_1 + 0x6c) + 8))(*(undefined4 *)(param_1 + 0x6c));
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

