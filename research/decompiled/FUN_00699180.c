// Function: FUN_00699180
// Address:  0x00699180
// Source:   batch_decompile (mass dump)
// Hash:     3bf542721db1e4d3


undefined4 __fastcall FUN_00699180(int param_1)

{
  undefined4 uVar1;
  int local_8;
  
  (**(code **)(**(int **)(param_1 + 4) + 0x14))();
  uVar1 = (**(code **)(**(int **)(param_1 + 4) + 4))
                    (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  *(undefined4 *)(param_1 + 0x24) = uVar1;
  if (*(int *)(param_1 + 0x24) == 0) {
    uVar1 = (**(code **)(**(int **)(param_1 + 4) + 8))
                      (*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x14),
                       *(undefined4 *)(param_1 + 0x10),&local_8);
    *(undefined4 *)(param_1 + 0x24) = uVar1;
    if ((*(int *)(param_1 + 0x24) == 0x40000) && (*(int *)(param_1 + 0x1c) != 0)) {
      (**(code **)(**(int **)(param_1 + 0x1c) + 0x40))(*(int **)(param_1 + 0x1c),1);
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    if (-1 < *(int *)(param_1 + 0x24)) {
      if (local_8 == *(int *)(param_1 + 0x14)) {
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      else {
        *(int *)(param_1 + 0x14) = local_8;
        *(undefined4 *)(param_1 + 0x24) = 1;
      }
    }
  }
  (**(code **)(**(int **)(param_1 + 4) + 0x18))();
  return *(undefined4 *)(param_1 + 0x24);
}

