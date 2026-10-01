// Function: FUN_00679ad0
// Address:  0x00679ad0
// Source:   batch_decompile (mass dump)
// Hash:     744ad28516205760


void FUN_00679ad0(int *param_1)

{
  void *_Memory;
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    iVar1 = 0;
    if (0 < param_1[2]) {
      do {
        _Memory = *(void **)(*param_1 + iVar1 * 4);
        if (_Memory != (void *)0x0) {
          _free(_Memory);
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < param_1[2]);
    }
    if ((void *)*param_1 != (void *)0x0) {
      _free((void *)*param_1);
    }
    if ((void *)param_1[1] != (void *)0x0) {
      _free((void *)param_1[1]);
    }
    if ((void *)param_1[3] != (void *)0x0) {
      _free((void *)param_1[3]);
    }
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return;
}

