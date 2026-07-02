// Function: FUN_00647220
// Address:  0x00647220
// Source:   batch_decompile (mass dump)
// Hash:     63e4436face8216a


void __fastcall FUN_00647220(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  *(int *)(param_1 + 0x414) = *(int *)(param_1 + 0x414) + -1;
  if (*(int *)(param_1 + 0x414) < 8) {
    *(undefined4 *)(param_1 + 0x414) = 8;
    iVar1 = FUN_0063bf40();
    if (iVar1 < *(int *)(param_1 + 0x414)) {
      uVar2 = FUN_0063bf40();
      *(undefined4 *)(param_1 + 0x414) = uVar2;
    }
  }
  return;
}

