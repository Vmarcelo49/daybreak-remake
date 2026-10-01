// Function: FUN_00693ad0
// Address:  0x00693ad0
// Source:   batch_decompile (mass dump)
// Hash:     1b00d64c7b513d51


undefined4 __fastcall FUN_00693ad0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_8;
  
  local_8 = FUN_006936a0(param_1);
  while( true ) {
    if (local_8 == 0) {
      return 1;
    }
    uVar1 = FUN_00693720(local_8);
    iVar2 = FUN_00693990(uVar1);
    if (iVar2 == 0) break;
    local_8 = FUN_00694240(local_8);
  }
  return 0;
}

