// Function: FUN_00406140
// Address:  0x00406140
// Source:   batch_decompile (mass dump)
// Hash:     74bac650ddf79456


void __fastcall FUN_00406140(undefined4 *param_1)

{
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069db8a;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = &PTR_FUN_006a16b4;
  local_8 = 0;
  FUN_0065b1d0(param_1[0x69]);
  for (local_14 = 0; local_14 < 0xe; local_14 = local_14 + 1) {
    FUN_00656200(param_1[local_14 + 0x47]);
  }
  for (local_18 = 0; local_18 < 7; local_18 = local_18 + 1) {
    FUN_00656200(param_1[local_18 + 0x5d]);
  }
  FUN_00656200(param_1[0x55]);
  FUN_00656200(param_1[0x56]);
  FUN_00656200(param_1[0x57]);
  FUN_00656200(param_1[0x58]);
  FUN_00656200(param_1[0x5b]);
  FUN_00656200(param_1[0x5c]);
  FUN_00656200(param_1[0x67]);
  FUN_00656200(param_1[0x68]);
  FUN_00656200(param_1[0x43]);
  FUN_00656200(param_1[0x44]);
  FUN_00656200(param_1[0x45]);
  FUN_00656200(param_1[0x46]);
  FUN_00656200(param_1[0x42]);
  local_8 = 0xffffffff;
  FUN_004039d0();
  ExceptionList = local_10;
  return;
}

