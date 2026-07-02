// Function: FUN_00427600
// Address:  0x00427600
// Source:   batch_decompile (mass dump)
// Hash:     bb8a9b8fe8d63a3c


void FUN_00427600(int param_1,int param_2,int param_3)

{
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069e380;
  pvStack_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_10;
  for (; param_1 != param_2; param_1 = param_1 + 0xc) {
    FUN_004275e0(param_3,param_1);
    param_3 = param_3 + 0xc;
  }
  FUN_00427687();
  return;
}

