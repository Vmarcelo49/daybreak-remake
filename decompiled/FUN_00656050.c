// Function: FUN_00656050
// Address:  0x00656050
// Source:   batch_decompile (mass dump)
// Hash:     98cc106c57d4255d


undefined4 __fastcall FUN_00656050(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ed88;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00656440();
  local_8 = 0;
  FUN_00425ac0();
  ExceptionList = local_10;
  return param_1;
}

