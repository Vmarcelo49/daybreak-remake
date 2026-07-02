// ============================================
// Address:  0x0040e9c0
// Original: FUN_0040e9c0
// Status:   unreviewed
// ============================================


void __fastcall FUN_0040e9c0(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069dcb1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a1b70;
  local_8 = 3;
  if (param_1[0x10] != 0) {
    FUN_0040fb10(1);
  }
  CloseHandle((HANDLE)param_1[0x1cf]);
  FUN_0065b1d0(param_1[0x11]);
  FUN_00656200(param_1[0x12]);
  FUN_00656200(param_1[0x13]);
  FUN_00656200(param_1[0x14]);
  FUN_00656200(param_1[0x15]);
  FUN_00656200(param_1[0x16]);
  FUN_00656200(param_1[0x17]);
  FUN_00656200(param_1[0x18]);
  FUN_00656200(param_1[0x19]);
  FUN_00656200(param_1[0x1a]);
  local_8._0_1_ = 2;
  _eh_vector_destructor_iterator_(param_1 + 0x1b1,0x14,6,FUN_0040fc10);
  local_8._0_1_ = 1;
  ~<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0065d640();
  local_8 = 0xffffffff;
  FUN_004039d0();
  ExceptionList = local_10;
  return;
}

