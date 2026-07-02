// ============================================
// Address:  0x00679b90
// Original: FUN_00679b90
// Status:   unreviewed
// ============================================


void FUN_00679b90(undefined4 *param_1)

{
  void *_Memory;
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  
  _Memory = (void *)param_1[7];
  if (_Memory != (void *)0x0) {
    iVar1 = 0;
    if (0 < *(int *)((int)_Memory + 8)) {
      puVar2 = (undefined4 *)((int)_Memory + 0x20);
      do {
        if ((void *)*puVar2 != (void *)0x0) {
          _free((void *)*puVar2);
        }
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar1 < *(int *)((int)_Memory + 8));
    }
    iVar1 = 0;
    if (0 < *(int *)((int)_Memory + 0xc)) {
      puVar2 = (undefined4 *)((int)_Memory + 0x220);
      do {
        (**(code **)((&PTR_PTR_006be814)[puVar2[-0x40]] + 8))(*puVar2);
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar1 < *(int *)((int)_Memory + 0xc));
    }
    iVar1 = 0;
    if (0 < *(int *)((int)_Memory + 0x10)) {
      puVar2 = (undefined4 *)((int)_Memory + 0x420);
      do {
        (**(code **)((&PTR_DAT_006be800)[puVar2[-0x40]] + 0xc))(*puVar2);
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar1 < *(int *)((int)_Memory + 0x10));
    }
    iVar1 = 0;
    if (0 < *(int *)((int)_Memory + 0x14)) {
      puVar2 = (undefined4 *)((int)_Memory + 0x620);
      do {
        (**(code **)((&PTR_DAT_006be808)[puVar2[-0x40]] + 0xc))(*puVar2);
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar1 < *(int *)((int)_Memory + 0x14));
    }
    iVar1 = 0;
    if (0 < *(int *)((int)_Memory + 0x18)) {
      iVar4 = 0;
      piVar3 = (int *)((int)_Memory + 0x720);
      do {
        if (*piVar3 != 0) {
          FUN_0067e0c0(*piVar3);
        }
        if (*(int *)((int)_Memory + 0xb20) != 0) {
          FUN_0067e0e0(iVar4 + *(int *)((int)_Memory + 0xb20));
        }
        iVar1 = iVar1 + 1;
        piVar3 = piVar3 + 1;
        iVar4 = iVar4 + 0x2c;
      } while (iVar1 < *(int *)((int)_Memory + 0x18));
    }
    if (*(void **)((int)_Memory + 0xb20) != (void *)0x0) {
      _free(*(void **)((int)_Memory + 0xb20));
    }
    iVar1 = 0;
    if (0 < *(int *)((int)_Memory + 0x1c)) {
      puVar2 = (undefined4 *)((int)_Memory + 0xb24);
      do {
        FUN_0067b420(*puVar2);
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar1 < *(int *)((int)_Memory + 0x1c));
    }
    _free(_Memory);
  }
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}

