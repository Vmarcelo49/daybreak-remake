// Function: FUN_0064e980
// Address:  0x0064e980
// Source:   batch_decompile (mass dump)
// Hash:     220baa77ef757e2d


undefined4 __thiscall FUN_0064e980(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (1 < local_8) {
      return 1;
    }
    iVar1 = (**(code **)(**(int **)(param_1 + 0xc + local_8 * 4) + 0x58))
                      (*(undefined4 *)(param_1 + 0xc + local_8 * 4),param_2,param_3);
    if (iVar1 < 0) break;
    local_8 = local_8 + 1;
  }
  return 0;
}

