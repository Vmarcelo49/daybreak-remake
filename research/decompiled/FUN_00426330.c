// Function: FUN_00426330
// Address:  0x00426330
// Source:   batch_decompile (mass dump)
// Hash:     ed6fb9ce2cb59378


void FUN_00426330(undefined4 param_1,int param_2,undefined4 param_3)

{
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e2f0;
  pvStack_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_10;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    FUN_00425480(param_1,param_3);
  }
  FUN_004263c2();
  return;
}

