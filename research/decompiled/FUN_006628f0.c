// Function: FUN_006628f0
// Address:  0x006628f0
// Source:   batch_decompile (mass dump)
// Hash:     37ba70bed12d5d77


undefined4 * __fastcall FUN_006628f0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f25b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006631f0();
  local_8 = 0;
  *param_1 = 0;
  FUN_00663420();
  ExceptionList = local_10;
  return param_1;
}

