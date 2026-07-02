// Function: FUN_00665e70
// Address:  0x00665e70
// Source:   batch_decompile (mass dump)
// Hash:     99f680c6d45338e6


undefined4 __thiscall FUN_00665e70(byte *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  void *pvVar3;
  
  cVar1 = FUN_00653540(param_2);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    FUN_00653760(param_1,1);
    FUN_00653760(param_1 + 4,4);
    FUN_00653760(param_1 + 8,4);
    FUN_00653760(param_1 + 0xc,4);
    FUN_00653760(param_1 + 0x10,4);
    if (*(int *)(param_1 + 0x10) == 0) {
      if (*param_1 < 0x18) {
        if (*(int *)(param_1 + 0x18) != 0) {
          _free(*(void **)(param_1 + 0x18));
          param_1[0x18] = 0;
          param_1[0x19] = 0;
          param_1[0x1a] = 0;
          param_1[0x1b] = 0;
        }
        pvVar3 = operator_new(*(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * (uint)*param_1 >> 3)
        ;
        *(void **)(param_1 + 0x18) = pvVar3;
        FUN_00653760(*(undefined4 *)(param_1 + 0x18),
                     *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * (uint)*param_1 >> 3);
      }
      else {
        if (*(int *)(param_1 + 0x18) != 0) {
          _free(*(void **)(param_1 + 0x18));
          param_1[0x18] = 0;
          param_1[0x19] = 0;
          param_1[0x1a] = 0;
          param_1[0x1b] = 0;
        }
        pvVar3 = operator_new(*(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * 4);
        *(void **)(param_1 + 0x18) = pvVar3;
        FUN_00653760(*(undefined4 *)(param_1 + 0x18),
                     *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * 4);
      }
    }
    else {
      if (*(int *)(param_1 + 0x18) != 0) {
        _free(*(void **)(param_1 + 0x18));
        param_1[0x18] = 0;
        param_1[0x19] = 0;
        param_1[0x1a] = 0;
        param_1[0x1b] = 0;
      }
      pvVar3 = operator_new(*(uint *)(param_1 + 0x10));
      *(void **)(param_1 + 0x18) = pvVar3;
      FUN_00653760(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x10));
    }
    uVar2 = 1;
  }
  return uVar2;
}

