// Function: FUN_0040dab0
// Address:  0x0040dab0
// Source:   batch_decompile (mass dump)
// Hash:     1ab0ed52f44ddde2


undefined1 * __fastcall FUN_0040dab0(undefined1 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dbeb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006572d0();
  local_8 = 0;
  CWnd::CWnd((CWnd *)(param_1 + 0x68));
  *param_1 = 0;
  param_1[1] = 0;
  ExceptionList = local_10;
  return param_1;
}

