// Function: FUN_0041da70
// Address:  0x0041da70
// Source:   batch_decompile (mass dump)
// Hash:     3cd6565bc1fe17a2


void __fastcall FUN_0041da70(undefined4 *param_1)

{
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069e1f6;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a240c;
  local_8 = 10;
  if (param_1[0x47] != 0) {
    if (param_1[0x47] != 0) {
      FUN_00402010(1);
    }
    param_1[0x47] = 0;
  }
  if (param_1[0x2bad] != 0) {
    if (param_1[0x2bad] != 0) {
      FUN_00423370(1);
    }
    param_1[0x2bad] = 0;
  }
  for (local_14 = 0; local_14 < 1000; local_14 = local_14 + 1) {
    FUN_004244c0();
  }
  for (local_18 = 0; local_18 < 0x100; local_18 = local_18 + 1) {
    FUN_00424210();
  }
  local_8._0_1_ = 9;
  FUN_00431da0();
  local_8._0_1_ = 8;
  _eh_vector_destructor_iterator_(param_1 + 0x1d78,0x38,0x100,FUN_00423270);
  local_8._0_1_ = 7;
  _eh_vector_destructor_iterator_(param_1 + 0x220,0x1c,1000,FUN_004232c0);
  local_8._0_1_ = 6;
  FUN_004247e0();
  local_8._0_1_ = 5;
  FUN_00433d90();
  local_8._0_1_ = 4;
  FUN_0065a5e0();
  local_8._0_1_ = 3;
  FUN_0065a5e0();
  local_8._0_1_ = 2;
  FUN_00424670();
  local_8._0_1_ = 1;
  FUN_00657320();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0065d640();
  local_8 = 0xffffffff;
  FUN_0040dc70();
  ExceptionList = local_10;
  return;
}

