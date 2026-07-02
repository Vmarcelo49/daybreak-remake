// Function: FUN_004220e0
// Address:  0x004220e0
// Source:   batch_decompile (mass dump)
// Hash:     e06c3b4a9e9cbf1f


void __fastcall FUN_004220e0(int param_1)

{
  undefined1 local_10 [8];
  undefined4 local_8;
  
  if (DAT_006cfdb0 == '\x01') {
    FUN_00423b80();
    local_8 = *(undefined4 *)(param_1 + 8);
    FUN_00415d30(0,local_10,0,8);
  }
  FUN_0064af20(*(undefined4 *)(param_1 + 8),7);
  *(undefined4 *)(param_1 + 0x83c) = *(undefined4 *)(param_1 + 0x330);
  *(undefined1 *)(param_1 + 0x845) = 1;
  return;
}

