// Function: FUN_0067b0c0
// Address:  0x0067b0c0
// Source:   batch_decompile (mass dump)
// Hash:     341a088b63945c01


int FUN_0067b0c0(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 4);
  if ((-1 < *(int *)(param_1 + 0x18)) && (*(int *)(param_1 + 0x18) < *(int *)(param_1 + 0x14))) {
    if (param_2 != (undefined4 *)0x0) {
      iVar3 = 0;
      if (0 < *(int *)(iVar2 + 4)) {
        do {
          iVar1 = iVar3 * 4;
          iVar3 = iVar3 + 1;
          *(int *)(*(int *)(param_1 + 0xc) + -4 + iVar3 * 4) =
               *(int *)(*(int *)(param_1 + 8) + iVar1) + *(int *)(param_1 + 0x18) * 4;
        } while (iVar3 < *(int *)(iVar2 + 4));
      }
      *param_2 = *(undefined4 *)(param_1 + 0xc);
    }
    return *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x18);
  }
  return 0;
}

