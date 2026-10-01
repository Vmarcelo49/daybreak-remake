// Function: FUN_0068c4b0
// Address:  0x0068c4b0
// Source:   batch_decompile (mass dump)
// Hash:     8215d12bd6f0201e


int __thiscall FUN_0068c4b0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = FUN_00689fc0(param_2);
  if (-1 < local_8) {
    iVar1 = FUN_0068daa0();
    if ((iVar1 == 0) && (*(int *)(param_1 + 0x98) != 0)) {
      local_8 = (**(code **)(**(int **)(param_1 + 0x98) + 0x14))(*(undefined4 *)(param_1 + 0x98));
    }
  }
  return local_8;
}

