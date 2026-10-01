// Function: FUN_00423420
// Address:  0x00423420
// Source:   batch_decompile (mass dump)
// Hash:     4d84d89f1a71fa49


void __thiscall FUN_00423420(int param_1,undefined4 *param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(*(int *)(param_1 + 0x12c4) + 0x44 + param_3 * 0xc);
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  param_2[2] = puVar1[2];
  return;
}

