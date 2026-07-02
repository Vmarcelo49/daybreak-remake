// ============================================
// Address:  0x006471d0
// Original: FUN_006471d0
// Status:   unreviewed
// ============================================


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

