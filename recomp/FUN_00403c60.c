// ============================================
// Address:  0x00403c60
// Original: FUN_00403c60
// Status:   unreviewed
// ============================================


undefined4 * __fastcall FUN_00403c60(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069da88;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a146c;
  FUN_00425ac0();
  FUN_00403a70();
  param_1[1] = 0;
  puVar1 = (undefined4 *)FUN_006560c0(local_14,"data/object/gameover.bmp");
  param_1[2] = *puVar1;
  FUN_00655af0(param_1[2],0,0,800,600);
  ExceptionList = local_10;
  return param_1;
}

