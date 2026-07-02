// ============================================
// Address:  0x0067a330
// Original: FUN_0067a330
// Status:   unreviewed
// ============================================


void FUN_0067a330(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *_Memory;
  void *pvVar3;
  
  _Memory = *(undefined4 **)(param_1 + 0x54);
  while (_Memory != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)_Memory[1];
    _free((void *)*_Memory);
    *_Memory = 0;
    _Memory[1] = 0;
    _free(_Memory);
    _Memory = puVar1;
  }
  if (*(int *)(param_1 + 0x50) != 0) {
    pvVar3 = _realloc(*(void **)(param_1 + 0x44),*(int *)(param_1 + 0x4c) + *(int *)(param_1 + 0x50)
                     );
    *(void **)(param_1 + 0x44) = pvVar3;
    iVar2 = *(int *)(param_1 + 0x50);
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + iVar2;
  }
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  return;
}

