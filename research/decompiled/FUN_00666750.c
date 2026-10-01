// Function: FUN_00666750
// Address:  0x00666750
// Source:   batch_decompile (mass dump)
// Hash:     5afcaaa1792a2664


void __thiscall FUN_00666750(int param_1,int param_2,undefined1 param_3,uint param_4)

{
  byte *pbVar1;
  ushort *puVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint local_9c;
  uint local_98;
  uint local_8c;
  uint local_88;
  uint local_74;
  uint local_70;
  uint local_64;
  uint local_60;
  uint local_5c;
  int local_58;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  int local_38;
  uint local_2c;
  ushort local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  int local_18;
  uint local_c;
  undefined2 local_8;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    switch(param_3) {
    case 8:
      iVar6 = *(int *)(param_1 + 0x18);
      for (local_70 = 0; local_70 < *(uint *)(param_1 + 8); local_70 = local_70 + 1) {
        for (local_74 = 0; local_74 < *(uint *)(param_1 + 4); local_74 = local_74 + 1) {
          *(undefined2 *)(param_2 + (local_70 * param_4 + local_74) * 2) =
               *(undefined2 *)
                (*(int *)(param_1 + 0x14) +
                (uint)*(byte *)(iVar6 + local_70 * *(int *)(param_1 + 0xc) + local_74) * 2);
        }
      }
      break;
    case 0x10:
      uVar4 = *(uint *)(param_1 + 4);
      uVar5 = *(uint *)(param_1 + 0xc);
      iVar6 = *(int *)(param_1 + 0x18);
      for (local_88 = 0; local_88 < *(uint *)(param_1 + 8); local_88 = local_88 + 1) {
        for (local_8c = 0; local_8c < uVar4 >> 1; local_8c = local_8c + 1) {
          *(undefined4 *)(param_2 + (local_88 * (param_4 >> 1) + local_8c) * 4) =
               *(undefined4 *)(iVar6 + (local_88 * (uVar5 >> 1) + local_8c) * 4);
        }
      }
      break;
    case 0x18:
    case 0x20:
      iVar6 = *(int *)(param_1 + 0x18);
      for (local_98 = 0; local_98 < *(uint *)(param_1 + 8); local_98 = local_98 + 1) {
        for (local_9c = 0; local_9c < *(uint *)(param_1 + 4); local_9c = local_9c + 1) {
          *(undefined4 *)(param_2 + (local_98 * param_4 + local_9c) * 4) =
               *(undefined4 *)(iVar6 + (local_98 * *(int *)(param_1 + 0xc) + local_9c) * 4);
        }
      }
    }
  }
  else {
    switch(param_3) {
    case 8:
      pbVar1 = *(byte **)(param_1 + 0x18);
      local_1c = 0;
      local_18 = 0;
      local_c = (uint)*pbVar1;
      local_8 = *(undefined2 *)(*(int *)(param_1 + 0x14) + (uint)pbVar1[1] * 2);
      for (local_20 = 0; local_20 < *(uint *)(param_1 + 8); local_20 = local_20 + 1) {
        for (local_24 = 0; iVar6 = local_18, local_24 < *(uint *)(param_1 + 4);
            local_24 = local_24 + 1) {
          *(undefined2 *)(param_2 + (local_20 * param_4 + local_24) * 2) = local_8;
          local_1c = local_1c + 1;
          if (local_c <= local_1c) {
            iVar6 = local_18 + 2;
            local_1c = (uint)(local_c < local_1c);
            if ((local_24 == *(int *)(param_1 + 4) - 1U) && (local_20 == *(int *)(param_1 + 8) - 1U)
               ) break;
            local_c = (uint)pbVar1[iVar6];
            local_8 = *(undefined2 *)(*(int *)(param_1 + 0x14) + (uint)pbVar1[local_18 + 3] * 2);
            local_18 = iVar6;
          }
        }
        local_18 = iVar6;
      }
      break;
    case 0x10:
      puVar2 = *(ushort **)(param_1 + 0x18);
      local_3c = 0;
      local_38 = 0;
      local_2c = (uint)*puVar2;
      local_28 = puVar2[1];
      for (local_40 = 0; local_40 < *(uint *)(param_1 + 8); local_40 = local_40 + 1) {
        for (local_44 = 0; iVar6 = local_38, local_44 < *(uint *)(param_1 + 4);
            local_44 = local_44 + 1) {
          *(ushort *)(param_2 + (local_40 * param_4 + local_44) * 2) = local_28;
          local_3c = local_3c + 1;
          if (local_2c <= local_3c) {
            iVar6 = local_38 + 2;
            local_3c = 0;
            if ((local_44 == *(int *)(param_1 + 4) - 1U) && (local_40 == *(int *)(param_1 + 8) - 1U)
               ) break;
            local_2c = (uint)puVar2[iVar6];
            local_28 = puVar2[local_38 + 3];
            local_38 = iVar6;
          }
        }
        local_38 = iVar6;
      }
      break;
    case 0x18:
    case 0x20:
      puVar3 = *(uint **)(param_1 + 0x18);
      local_5c = 0;
      local_58 = 0;
      local_4c = *puVar3;
      local_48 = puVar3[1];
      for (local_60 = 0; local_60 < *(uint *)(param_1 + 8); local_60 = local_60 + 1) {
        for (local_64 = 0; iVar6 = local_58, local_64 < *(uint *)(param_1 + 4);
            local_64 = local_64 + 1) {
          *(uint *)(param_2 + (local_60 * param_4 + local_64) * 4) = local_48;
          local_5c = local_5c + 1;
          if (local_4c <= local_5c) {
            iVar6 = local_58 + 2;
            local_5c = 0;
            if ((local_64 == *(int *)(param_1 + 4) - 1U) && (local_60 == *(int *)(param_1 + 8) - 1U)
               ) break;
            local_4c = puVar3[iVar6];
            local_48 = puVar3[local_58 + 3];
            local_58 = iVar6;
          }
        }
        local_58 = iVar6;
      }
    }
  }
  return;
}

