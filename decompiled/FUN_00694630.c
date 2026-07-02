// Function: FUN_00694630
// Address:  0x00694630
// Source:   batch_decompile (mass dump)
// Hash:     96b4b9b8d03c3ae6


undefined4 __thiscall FUN_00694630(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fc10;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d8b0();
  FUN_0068dee0(param_2,param_3);
  local_8 = 0;
  FUN_00425ac0();
  ExceptionList = local_10;
  return param_1;
}

