// Function: FUN_00403d70
// Address:  0x00403d70
// Source:   batch_decompile (mass dump)
// Hash:     c8a85eeed9cf0ea0


undefined4 __fastcall FUN_00403d70(int param_1)

{
  int local_8;
  
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
  FUN_006584e0();
  FUN_006585f0();
  local_8 = 0;
  while( true ) {
    if (3 < local_8) {
      return 0x14;
    }
    FUN_00657390();
    if (((&DAT_006cae9c)[local_8 * 0x19] != 0) || ((&DAT_006caea0)[local_8 * 0x19] != 0)) break;
    local_8 = local_8 + 1;
  }
  FUN_0065b870("data/bgm/title.ogg");
  return 1;
}

