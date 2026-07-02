// Function: FUN_00680980
// Address:  0x00680980
// Source:   batch_decompile (mass dump)
// Hash:     33c863bcb497bcec


void FUN_00680980(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((void *)param_1[1] != (void *)0x0) {
      _free((void *)param_1[1]);
    }
    if ((void *)param_1[2] != (void *)0x0) {
      _free((void *)param_1[2]);
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}

