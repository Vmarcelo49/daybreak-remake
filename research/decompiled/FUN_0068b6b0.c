// Function: FUN_0068b6b0
// Address:  0x0068b6b0
// Source:   batch_decompile (mass dump)
// Hash:     c76dd3af16237370


undefined4 * __thiscall
FUN_0068b6b0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            int *param_5,undefined4 param_6)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f64e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00689f70(param_2,param_3,param_4,param_5,param_6);
  local_8 = 0;
  FUN_0068d8d0();
  *param_1 = &PTR_FUN_006ad370;
  param_1[3] = &PTR_FUN_006ad328;
  param_1[4] = &PTR_LAB_006ad310;
  param_1[0x28] = &PTR_LAB_006ad300;
  FUN_0068db90();
  local_8 = CONCAT31(local_8._1_3_,1);
  param_1[0x2f] = 0;
  param_1[0x30] = 0;
  param_1[0x31] = 0;
  param_1[0x32] = 0;
  param_1[0x33] = 0;
  param_1[0x34] = 0;
  param_1[0x35] = 0;
  param_1[0x36] = 0;
  iVar1 = FUN_0068b890();
  if (iVar1 < 0) {
    *param_5 = iVar1;
  }
  ExceptionList = local_10;
  return param_1;
}

