// Function: FUN_00422060
// Address:  0x00422060
// Source:   batch_decompile (mass dump)
// Hash:     dacba63cdc05dc54


void __fastcall FUN_00422060(int param_1)

{
  undefined4 uVar1;
  undefined1 local_10 [8];
  undefined4 local_8;
  
  if (DAT_006cfdb0 == '\x01') {
    FUN_00423b80();
    local_8 = *(undefined4 *)(param_1 + 8);
    FUN_00415d30(0,local_10,0,8);
  }
  *(undefined1 *)(param_1 + 0xaec8) = 1;
  uVar1 = FUN_0066b668();
  *(undefined4 *)(param_1 + 0x838) = uVar1;
  *(undefined1 *)(param_1 + 0x844) = 1;
  *(undefined1 *)(param_1 + 0x334) = 0xfc;
  return;
}

