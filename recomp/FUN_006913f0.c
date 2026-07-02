// ============================================
// Address:  0x006913f0
// Original: FUN_006913f0
// Status:   unreviewed
// ============================================


bool __thiscall FUN_006913f0(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0068f290(param_2);
  if (iVar1 == 0) {
    *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 1;
  }
  return iVar1 != 0;
}

