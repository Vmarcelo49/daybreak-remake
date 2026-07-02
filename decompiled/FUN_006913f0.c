// Function: FUN_006913f0
// Address:  0x006913f0
// Source:   batch_decompile (mass dump)
// Hash:     416a7fd235976b9f


bool __thiscall FUN_006913f0(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0068f290(param_2);
  if (iVar1 == 0) {
    *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 1;
  }
  return iVar1 != 0;
}

