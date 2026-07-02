// ============================================
// Address:  0x006941d0
// Original: FUN_006941d0
// Status:   unreviewed
// ============================================


int __fastcall FUN_006941d0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 != 0) {
    uVar2 = FUN_0068dc80();
    *(undefined4 *)(param_1 + 8) = uVar2;
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  }
  return iVar1;
}

