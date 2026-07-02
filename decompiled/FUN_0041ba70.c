// Function: FUN_0041ba70
// Address:  0x0041ba70
// Source:   batch_decompile (mass dump)
// Hash:     ac07f037b174258c


void __fastcall FUN_0041ba70(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e02a;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a2188;
  param_1[0xf66] = &PTR_FUN_006a217c;
  local_8 = 0;
  FUN_00645df0();
  FUN_0065f780(0);
  local_8 = 0xffffffff;
  FUN_00408f40();
  ExceptionList = local_10;
  return;
}

