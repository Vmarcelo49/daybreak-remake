// Function: FUN_005f7f90
// Address:  0x005f7f90
// Source:   batch_decompile (mass dump)
// Hash:     fcca0bf581ee120c


void __fastcall FUN_005f7f90(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e688;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a47fc;
  local_8 = 0;
  if (param_1[0x10] != 0) {
    _free((void *)param_1[0x10]);
    param_1[0x10] = 0;
  }
  if (param_1[0xd] != 0) {
    if (param_1[0xd] != 0) {
      FID_conflict__vector_deleting_destructor_(3);
    }
    param_1[0xd] = 0;
  }
  if (param_1[0xe] != 0) {
    if (param_1[0xe] != 0) {
      FID_conflict__vector_deleting_destructor_(3);
    }
    param_1[0xe] = 0;
  }
  if (param_1[0xf] != 0) {
    if (param_1[0xf] != 0) {
      FUN_005f8e50(3);
    }
    param_1[0xf] = 0;
  }
  local_8 = 0xffffffff;
  FUN_0042f6a0();
  ExceptionList = local_10;
  return;
}

