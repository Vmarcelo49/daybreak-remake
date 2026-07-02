// Function: FUN_00427430
// Address:  0x00427430
// Source:   batch_decompile (mass dump)
// Hash:     e981af2719c4c38d


void FUN_00427430(int param_1,int param_2,undefined4 param_3)

{
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e370;
  pvStack_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_10;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    FUN_004275e0(param_1,param_3);
    param_1 = param_1 + 0xc;
  }
  FUN_004274b5();
  return;
}

