// Function: FUN_006471d0
// Address:  0x006471d0
// Source:   batch_decompile (mass dump)
// Hash:     e59c51b293d17be0


void __fastcall FUN_006471d0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  *(int *)(param_1 + 0x414) = *(int *)(param_1 + 0x414) + 1;
  iVar1 = FUN_0063bf40();
  if (iVar1 < *(int *)(param_1 + 0x414)) {
    uVar2 = FUN_0063bf40();
    *(undefined4 *)(param_1 + 0x414) = uVar2;
  }
  return;
}

