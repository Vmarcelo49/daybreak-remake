// Function: FUN_0069cd70
// Address:  0x0069cd70
// Source:   batch_decompile (mass dump)
// Hash:     9db024f1e71c2fd3


undefined4 FUN_0069cd70(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((void *)*param_1 != (void *)0x0) {
      _free((void *)*param_1);
    }
    FUN_0069cd50(param_1);
  }
  return 0;
}

