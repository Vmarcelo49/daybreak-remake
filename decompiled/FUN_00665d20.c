// Function: FUN_00665d20
// Address:  0x00665d20
// Source:   batch_decompile (mass dump)
// Hash:     54a2dc584905f48c


void __thiscall FUN_00665d20(byte *param_1,undefined4 *param_2)

{
  void *pvVar1;
  
  *(undefined4 *)(param_1 + 4) = *param_2;
  *(undefined4 *)(param_1 + 8) = param_2[1];
  *(undefined4 *)(param_1 + 0xc) = param_2[2];
  *param_1 = *(byte *)(param_2 + 3);
  *(undefined4 *)(param_1 + 0x10) = param_2[4];
  if (*(int *)(param_1 + 0x10) == 0) {
    if (*param_1 < 0x18) {
      pvVar1 = operator_new(*(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * (uint)*param_1 >> 3);
      *(void **)(param_1 + 0x18) = pvVar1;
      _memcpy(*(void **)(param_1 + 0x18),(void *)param_2[5],
              *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * (uint)*param_1 >> 3);
    }
    else {
      pvVar1 = operator_new(*(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * 4);
      *(void **)(param_1 + 0x18) = pvVar1;
      _memcpy(*(void **)(param_1 + 0x18),(void *)param_2[5],
              *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * 4);
    }
  }
  else {
    pvVar1 = operator_new(*(uint *)(param_1 + 0x10));
    *(void **)(param_1 + 0x18) = pvVar1;
    _memcpy(*(void **)(param_1 + 0x18),(void *)param_2[5],*(size_t *)(param_1 + 0x10));
  }
  return;
}

