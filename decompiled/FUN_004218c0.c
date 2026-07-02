// Function: FUN_004218c0
// Address:  0x004218c0
// Source:   batch_decompile (mass dump)
// Hash:     10d0af24ebde2586


undefined4 __fastcall FUN_004218c0(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined1 local_c;
  
  piVar2 = *(int **)(param_1 + 0xade8);
  if (*piVar2 <= *(int *)(param_1 + 0xae04) + 1) {
    iVar1 = FUN_0063bf40();
    piVar2 = (int *)(iVar1 + -1);
    if ((int)piVar2 <= *(int *)(param_1 + 0xadf4)) {
      local_c = 1;
      goto LAB_0042191b;
    }
  }
  local_c = 0;
LAB_0042191b:
  return CONCAT31((int3)((uint)piVar2 >> 8),local_c);
}

