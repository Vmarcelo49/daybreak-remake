// Function: FUN_00664de0
// Address:  0x00664de0
// Source:   batch_decompile (mass dump)
// Hash:     77a0080f286f0564


undefined4 * __thiscall
FUN_00664de0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5,undefined1 param_6)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  puVar2 = param_1 + 3;
  for (iVar1 = 0x43; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_5;
    param_5 = param_5 + 1;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)(param_1 + 0x46) = param_6;
  *(undefined1 *)((int)param_1 + 0x119) = 0;
  return param_1;
}

