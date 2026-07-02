// Function: FUN_006599e0
// Address:  0x006599e0
// Source:   batch_decompile (mass dump)
// Hash:     af192b1c7549b4c2


void FUN_006599e0(int param_1,int param_2,int param_3)

{
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069eed0;
  pvStack_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_10;
  for (; param_1 != param_2; param_1 = param_1 + 0x50) {
    FUN_00659990(param_3,param_1);
    param_3 = param_3 + 0x50;
  }
  FUN_00659a67();
  return;
}

