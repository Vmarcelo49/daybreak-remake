// Function: FUN_0065b620
// Address:  0x0065b620
// Source:   batch_decompile (mass dump)
// Hash:     2af6bf1775244fc3


void __fastcall FUN_0065b620(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069f076;
  local_10 = ExceptionList;
  local_8 = 1;
  ExceptionList = &local_10;
  FUN_0065d640(param_1);
  local_8 = local_8 & 0xffffff00;
  FUN_00668050();
  local_8 = 0xffffffff;
  FUN_006679d0();
  ExceptionList = local_10;
  return;
}

