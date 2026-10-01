// Function: FUN_0042eba0
// Address:  0x0042eba0
// Source:   batch_decompile (mass dump)
// Hash:     45dff8c41d232032


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_0042eba0(int param_1,undefined4 param_2)

{
  void *pvVar1;
  undefined4 *local_160;
  undefined4 *local_15c;
  int local_124;
  CHAR local_120 [268];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e3ce;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x30) != 0) {
    ExceptionList = &local_10;
    if (*(int *)(param_1 + 0x30) != 0) {
      ExceptionList = &local_10;
      FID_conflict__vector_deleting_destructor_(3);
    }
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    if (*(int *)(param_1 + 0x34) != 0) {
      FID_conflict__vector_deleting_destructor_(3);
    }
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    _free(*(void **)(param_1 + 0x38));
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  local_15c = operator_new(0x6d64);
  local_8 = 0;
  if (local_15c == (undefined4 *)0x0) {
    local_15c = (undefined4 *)0x0;
  }
  else {
    *local_15c = 1000;
    _eh_vector_constructor_iterator_(local_15c + 1,0x1c,1000,FUN_00423350,FUN_004232c0);
    local_15c = local_15c + 1;
  }
  local_8 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x30) = local_15c;
  local_160 = operator_new(0x15e4);
  local_8 = 1;
  if (local_160 == (undefined4 *)0x0) {
    local_160 = (undefined4 *)0x0;
  }
  else {
    *local_160 = 100;
    _eh_vector_constructor_iterator_(local_160 + 1,0x38,100,FUN_004231c0,FUN_00423270);
    local_160 = local_160 + 1;
  }
  local_8 = 0xffffffff;
  *(undefined4 **)(param_1 + 0x34) = local_160;
  pvVar1 = operator_new(400);
  *(void **)(param_1 + 0x38) = pvVar1;
  _memset(*(void **)(param_1 + 0x38),0,400);
  *(undefined4 *)(param_1 + 0x3c) = param_2;
  for (local_124 = 0; local_124 < 100; local_124 = local_124 + 1) {
    wsprintfA(local_120,"data/effect/%03d.dat",local_124);
    *(undefined4 *)(*(int *)(param_1 + 0x38) + local_124 * 4) = 0;
    FUN_0042eec0(local_124,local_120,*(int *)(param_1 + 0x38) + local_124 * 4);
  }
  ExceptionList = local_10;
  return 1;
}

