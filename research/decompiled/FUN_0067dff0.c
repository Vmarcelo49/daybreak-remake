// Function: FUN_0067dff0
// Address:  0x0067dff0
// Source:   batch_decompile (mass dump)
// Hash:     0a348079ed993145


void FUN_0067dff0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1[0xc] != 0) {
    if ((void *)param_1[8] != (void *)0x0) {
      _free((void *)param_1[8]);
    }
    if ((void *)param_1[2] != (void *)0x0) {
      _free((void *)param_1[2]);
    }
    if ((undefined4 *)param_1[9] != (undefined4 *)0x0) {
      _free(*(void **)param_1[9]);
      _free(*(void **)(param_1[9] + 4));
      _free(*(void **)(param_1[9] + 8));
      _free(*(void **)(param_1[9] + 0xc));
      puVar2 = (undefined4 *)param_1[9];
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      _free((void *)param_1[9]);
    }
    if ((undefined4 *)param_1[10] != (undefined4 *)0x0) {
      _free(*(void **)param_1[10]);
      _free(*(void **)(param_1[10] + 4));
      puVar2 = (undefined4 *)param_1[10];
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar2[2] = 0;
      puVar2[3] = 0;
      _free((void *)param_1[10]);
    }
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_1 = 0;
      param_1 = param_1 + 1;
    }
  }
  return;
}

