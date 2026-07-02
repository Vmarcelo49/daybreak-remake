// ============================================
// Address:  0x00669000
// Original: FUN_00669000
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00669000(int param_1,int *param_2)

{
  uint *puVar1;
  uint *puVar2;
  undefined4 uVar3;
  int iVar4;
  int local_40;
  int local_34;
  uint *local_30;
  uint *local_2c;
  uint *local_24;
  int local_20;
  uint *local_1c;
  int local_18;
  uint local_14;
  uint *local_10;
  uint *local_c;
  uint local_8;
  
  local_c = (uint *)0x0;
  if (param_2 == (int *)0x0) {
    uVar3 = 0x80004003;
  }
  else if (*(int *)(param_1 + 0x160) == 0) {
    uVar3 = 0x8000ffff;
  }
  else {
    (**(code **)(*param_2 + 0xc))(param_2,&local_10);
    local_10 = (uint *)((*(int *)(param_1 + 0x174) + -1) * *(int *)(param_1 + 0x178) + (int)local_10
                       );
    if (*(int *)(param_1 + 0x16c) == 0) {
      iVar4 = (**(code **)(**(int **)(param_1 + 0x160) + 0x4c))
                        (*(undefined4 *)(param_1 + 0x160),0,&local_20,0,0);
      if (iVar4 < 0) {
        return 0x80004005;
      }
    }
    else {
      iVar4 = (**(code **)(**(int **)(param_1 + 0x160) + 0x4c))
                        (*(undefined4 *)(param_1 + 0x160),0,&local_20,0,0x2000);
      if (iVar4 < 0) {
        return 0x80004005;
      }
    }
    local_2c = local_1c;
    local_18 = local_20;
    if (*(int *)(param_1 + 0x164) == 0x16) {
      iVar4 = *(int *)(param_1 + 0x170);
      for (local_14 = 0; local_14 < *(uint *)(param_1 + 0x174); local_14 = local_14 + 1) {
        local_24 = local_10;
        local_30 = local_2c;
        for (local_8 = 0; local_8 < (uint)((int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2);
            local_8 = local_8 + 1) {
          *local_30 = *local_24 | 0xff000000;
          local_30[1] = local_24[1] << 8 | 0xff000000 | *local_24 >> 0x18;
          local_30[2] = local_24[2] << 0x10 | 0xff000000 | local_24[1] >> 0x10;
          local_30[3] = local_24[2] >> 8 | 0xff000000;
          local_30 = local_30 + 4;
          local_24 = local_24 + 3;
        }
        local_c = local_24;
        for (local_8 = 0; local_8 < *(uint *)(param_1 + 0x170) % 4; local_8 = local_8 + 1) {
          *local_30 = (uint)*(byte *)((int)local_c + 2) << 0x10 | 0xff000000 |
                      (uint)*(byte *)((int)local_c + 1) << 8 | (uint)(byte)*local_c;
          local_30 = local_30 + 1;
          local_c = (uint *)((int)local_c + 3);
        }
        local_10 = (uint *)((int)local_10 - *(int *)(param_1 + 0x178));
        local_2c = (uint *)((int)local_2c + local_20);
      }
    }
    else if (*(int *)(param_1 + 0x164) == 0x19) {
      for (local_34 = 0; puVar2 = local_10, puVar1 = local_2c, local_34 < *(int *)(param_1 + 0x174);
          local_34 = local_34 + 1) {
        for (local_40 = 0; local_40 < *(int *)(param_1 + 0x170); local_40 = local_40 + 1) {
          *(ushort *)local_2c =
               (*(byte *)((int)local_10 + 2) & 0xf8) * 0x80 + -0x8000 +
               (*(byte *)((int)local_10 + 1) & 0xf8) * 4 + (short)((int)(uint)(byte)*local_10 >> 3);
          local_2c = (uint *)((int)local_2c + 2);
          local_10 = (uint *)((int)local_10 + 3);
        }
        local_10 = (uint *)((int)puVar2 - *(int *)(param_1 + 0x178));
        local_2c = (uint *)((int)puVar1 + local_20);
      }
    }
    iVar4 = (**(code **)(**(int **)(param_1 + 0x160) + 0x50))(*(undefined4 *)(param_1 + 0x160),0);
    if (iVar4 < 0) {
      uVar3 = 0x80004005;
    }
    else {
      uVar3 = 0;
    }
  }
  return uVar3;
}

