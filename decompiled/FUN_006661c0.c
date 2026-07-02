// Function: FUN_006661c0
// Address:  0x006661c0
// Source:   batch_decompile (mass dump)
// Hash:     74841965b4221337


void __fastcall FUN_006661c0(undefined1 *param_1)

{
  short *psVar1;
  void *pvVar2;
  void *pvVar3;
  uint _Size;
  uint local_58;
  uint local_54;
  int local_50;
  int local_4c;
  int local_48;
  uint local_3c;
  uint local_38;
  int local_34;
  short local_30;
  short local_2c;
  uint local_1c;
  uint local_18;
  int local_14;
  char local_e;
  byte local_d;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    switch(*param_1) {
    case 8:
      pvVar2 = operator_new(*(int *)(param_1 + 8) * *(int *)(param_1 + 4) * 2);
      local_14 = 0;
      local_d = 0;
      local_e = **(char **)(param_1 + 0x18);
      for (local_18 = 0; local_18 < *(uint *)(param_1 + 8); local_18 = local_18 + 1) {
        for (local_1c = 0; local_1c < *(uint *)(param_1 + 4); local_1c = local_1c + 1) {
          if ((local_e ==
               *(char *)(*(int *)(param_1 + 0x18) + local_18 * *(int *)(param_1 + 0xc) + local_1c))
             && (local_d < 0xff)) {
            local_d = local_d + 1;
          }
          else {
            *(byte *)((int)pvVar2 + local_14) = local_d;
            *(char *)((int)pvVar2 + local_14 + 1) = local_e;
            local_14 = local_14 + 2;
            local_e = *(char *)(local_18 * *(int *)(param_1 + 0xc) + local_1c +
                               *(int *)(param_1 + 0x18));
            local_d = 1;
          }
        }
      }
      *(byte *)((int)pvVar2 + local_14) = local_d;
      *(char *)((int)pvVar2 + local_14 + 1) = local_e;
      _Size = local_14 + 2;
      _free(*(void **)(param_1 + 0x18));
      pvVar3 = operator_new(_Size);
      *(void **)(param_1 + 0x18) = pvVar3;
      *(uint *)(param_1 + 0x10) = _Size;
      _memcpy(*(void **)(param_1 + 0x18),pvVar2,_Size);
      _free(pvVar2);
      break;
    case 0x10:
      psVar1 = *(short **)(param_1 + 0x18);
      pvVar2 = operator_new(*(int *)(param_1 + 8) * *(int *)(param_1 + 4) * 4);
      local_34 = 0;
      local_2c = 0;
      local_30 = *psVar1;
      for (local_38 = 0; local_38 < *(uint *)(param_1 + 8); local_38 = local_38 + 1) {
        for (local_3c = 0; local_3c < *(uint *)(param_1 + 4); local_3c = local_3c + 1) {
          if (local_30 == psVar1[local_38 * *(int *)(param_1 + 0xc) + local_3c]) {
            local_2c = local_2c + 1;
          }
          else {
            *(short *)((int)pvVar2 + local_34 * 2) = local_2c;
            *(short *)((int)pvVar2 + local_34 * 2 + 2) = local_30;
            local_34 = local_34 + 2;
            local_30 = psVar1[local_38 * *(int *)(param_1 + 0xc) + local_3c];
            local_2c = 1;
          }
        }
      }
      *(short *)((int)pvVar2 + local_34 * 2) = local_2c;
      *(short *)((int)pvVar2 + local_34 * 2 + 2) = local_30;
      local_34 = local_34 + 2;
      _free(*(void **)(param_1 + 0x18));
      pvVar3 = operator_new(local_34 * 2);
      *(void **)(param_1 + 0x18) = pvVar3;
      *(int *)(param_1 + 0x10) = local_34 * 2;
      _memcpy(*(void **)(param_1 + 0x18),pvVar2,local_34 * 2);
      _free(pvVar2);
      break;
    case 0x18:
    case 0x20:
      pvVar2 = operator_new(*(int *)(param_1 + 8) * *(int *)(param_1 + 4) * 8);
      local_50 = 0;
      local_48 = 0;
      local_4c = **(int **)(param_1 + 0x18);
      for (local_54 = 0; local_54 < *(uint *)(param_1 + 8); local_54 = local_54 + 1) {
        for (local_58 = 0; local_58 < *(uint *)(param_1 + 4); local_58 = local_58 + 1) {
          if (local_4c ==
              *(int *)(*(int *)(param_1 + 0x18) +
                      (local_54 * *(int *)(param_1 + 0xc) + local_58) * 4)) {
            local_48 = local_48 + 1;
          }
          else {
            *(int *)((int)pvVar2 + local_50 * 4) = local_48;
            *(int *)((int)pvVar2 + local_50 * 4 + 4) = local_4c;
            local_50 = local_50 + 2;
            local_4c = *(int *)(*(int *)(param_1 + 0x18) +
                               (local_54 * *(int *)(param_1 + 0xc) + local_58) * 4);
            local_48 = 1;
          }
        }
      }
      *(int *)((int)pvVar2 + local_50 * 4) = local_48;
      *(int *)((int)pvVar2 + local_50 * 4 + 4) = local_4c;
      local_50 = local_50 + 2;
      _free(*(void **)(param_1 + 0x18));
      pvVar3 = operator_new(local_50 * 4);
      *(void **)(param_1 + 0x18) = pvVar3;
      *(int *)(param_1 + 0x10) = local_50 * 4;
      _memcpy(*(void **)(param_1 + 0x18),pvVar2,local_50 * 4);
      _free(pvVar2);
    }
  }
  return;
}

