// ============================================
// Address:  0x0064fbc0
// Original: FUN_0064fbc0
// Status:   unreviewed
// ============================================


void FUN_0064fbc0(int param_1,int param_2,undefined4 param_3)

{
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069ec40;
  pvStack_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_10;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    FUN_00432ee0(param_1,param_3);
    param_1 = param_1 + 4;
  }
  FUN_0064fc45();
  return;
}

