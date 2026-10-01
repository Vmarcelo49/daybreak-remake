// Function: FUN_00688760
// Address:  0x00688760
// Source:   batch_decompile (mass dump)
// Hash:     e5558ecfd5139e4f


void __fastcall FUN_00688760(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069f513;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006ad264;
  local_8 = 0;
  (**(code **)(*(int *)(param_1[3] + 0xc) + 8))(param_1[3] + 0xc);
  local_8 = 0xffffffff;
  FUN_00693440();
  ExceptionList = local_10;
  return;
}

