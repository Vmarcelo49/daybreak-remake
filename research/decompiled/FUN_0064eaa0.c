// Function: FUN_0064eaa0
// Address:  0x0064eaa0
// Source:   batch_decompile (mass dump)
// Hash:     5bf2c8177b0a3724


undefined4 __thiscall FUN_0064eaa0(int param_1,undefined4 param_2,float param_3)

{
  int iVar1;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (1 < local_8) {
      return 1;
    }
    iVar1 = (**(code **)(**(int **)(param_1 + 0xc + local_8 * 4) + 0x54))
                      (*(undefined4 *)(param_1 + 0xc + local_8 * 4),param_2,(double)param_3);
    if (iVar1 < 0) break;
    local_8 = local_8 + 1;
  }
  return 0;
}

