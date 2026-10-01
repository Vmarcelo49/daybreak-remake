// Function: FUN_00403eb0
// Address:  0x00403eb0
// Source:   batch_decompile (mass dump)
// Hash:     bf494367cd657291


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 * __fastcall FUN_00403eb0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_128 [4];
  int local_124;
  CHAR local_120 [268];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dabb;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a1494;
  _vector_constructor_iterator_(param_1 + 1,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x51,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0xa1,0xa0,5,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x169,4,5,FUN_00425ac0);
  for (local_124 = 0; local_124 < 5; local_124 = local_124 + 1) {
    wsprintfA(local_120,"data/keyconfig/%04d.bmp",local_124);
    puVar1 = (undefined4 *)FUN_006560c0(local_128,local_120);
    param_1[local_124 + 0x169] = *puVar1;
  }
  FUN_00655af0(param_1[0x169],0,0,800,600);
  FUN_00655af0(param_1[0x16d],0,0x1a0,0x1a0,0x20);
  FUN_00655690(param_1[0x16a],0,0,0x20,0x20);
  FUN_00655690(param_1[0x16b],0,0,0x20,0x20);
  FUN_00655690(param_1[0x16c],0,0,0x20,0x20);
  FUN_00655690(param_1[0x16d],0,0,0x200,0x20);
  FUN_00655690(param_1[0x16d],0xa0,0x1c0,0x40,0x20);
  FUN_00655af0(param_1[0x16d],0x60,0x1e0,0x20,0x20);
  FUN_00655af0(param_1[0x16d],0,0x1c0,0x60,0x20);
  param_1[0x170] = 0;
  param_1[0x16e] = 4;
  param_1[0x16f] = 0;
  ExceptionList = local_10;
  return param_1;
}

