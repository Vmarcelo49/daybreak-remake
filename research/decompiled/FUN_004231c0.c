// Function: FUN_004231c0
// Address:  0x004231c0
// Source:   batch_decompile (mass dump)
// Hash:     1ac9cec0b3790560


undefined4 * __fastcall FUN_004231c0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e26b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004248f0();
  local_8 = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  *param_1 = 0;
  param_1[7] = 1;
  param_1[8] = 0;
  FUN_00424210();
  ExceptionList = local_10;
  return param_1;
}

