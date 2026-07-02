// ============================================
// Address:  0x0042d3b0
// Original: FUN_0042d3b0
// Status:   unreviewed
// ============================================


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0042d3b0(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 *puVar4;
  float fVar5;
  int local_14c;
  undefined1 local_144 [12];
  undefined1 local_138 [12];
  undefined1 local_12c [12];
  undefined1 local_120 [12];
  undefined1 local_114 [48];
  float local_e4;
  undefined1 local_e0 [12];
  ushort local_d4;
  int local_d0;
  ushort local_cc;
  ushort local_c8;
  int local_c4;
  undefined1 local_c0 [12];
  uint local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  allocator<char> local_a0 [12];
  allocator<char> local_94 [12];
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  int local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  float local_5c;
  float local_58;
  int local_54;
  int *local_50;
  int local_4c;
  allocator<char> local_48 [12];
  float local_3c;
  int local_38;
  float local_34;
  int local_30;
  float local_2c;
  undefined1 local_28 [12];
  undefined1 local_1c [4];
  float local_18;
  int local_14;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  uint local_8;
  
  FUN_00423750(*(undefined4 *)(param_1 + 0x14),*(float *)(param_1 + 0x18) + 0.01,
               *(undefined4 *)(param_1 + 0x1c));
  std::allocator<char>::allocator<char>(local_48);
  D3DXVec3Normalize(local_48,param_3);
  local_30 = 0;
  fVar3 = (float10)FUN_0042df50(param_3);
  local_2c = (float)fVar3;
  for (local_38 = *(int *)(param_2 + 0x44); local_38 != 0; local_38 = *(int *)(local_38 + 0x20)) {
    if (local_38 == 0) {
      local_14c = 0;
    }
    else {
      local_14c = local_38 + -4;
    }
    local_4c = local_14c;
    local_50 = (int *)0x0;
    D3DXIntersect(*(undefined4 *)(local_38 + 8),local_28,local_48,&local_30,local_1c,local_10,
                  local_c,&local_3c,&local_50,&local_8);
    if (local_30 != 0) {
      local_14 = (**(code **)(*local_50 + 0xc))(local_50);
      local_3c = 10000.0;
      std::allocator<char>::allocator<char>((allocator<char> *)&local_60);
      std::allocator<char>::allocator<char>(local_94);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_88);
      std::allocator<char>::allocator<char>(local_a0);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_b0);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_6c);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_7c);
      uVar1 = (**(code **)(**(int **)(local_38 + 8) + 0x18))(*(undefined4 *)(local_38 + 8));
      local_70 = D3DXGetFVFVertexSize(uVar1);
      local_30 = 0;
      (**(code **)(**(int **)(local_38 + 8) + 0x3c))(*(undefined4 *)(local_38 + 8),0x10,&local_a4);
      (**(code **)(**(int **)(local_38 + 8) + 0x44))(*(undefined4 *)(local_38 + 8),0x10,&local_54);
      for (local_b4 = 0; local_b4 < local_8; local_b4 = local_b4 + 1) {
        local_d0 = *(int *)(local_14 + local_b4 * 0x10);
        local_cc = *(ushort *)(local_54 + local_d0 * 6);
        local_d4 = *(ushort *)(local_54 + 2 + local_d0 * 6);
        local_c8 = *(ushort *)(local_54 + 4 + local_d0 * 6);
        local_c4 = local_a4;
        puVar2 = (undefined4 *)((uint)local_cc * local_70 + local_a4);
        local_b0 = *puVar2;
        local_ac = puVar2[1];
        local_a8 = puVar2[2];
        puVar2 = (undefined4 *)((uint)local_d4 * local_70 + local_a4);
        local_6c = *puVar2;
        local_68 = puVar2[1];
        local_64 = puVar2[2];
        puVar2 = (undefined4 *)((uint)local_c8 * local_70 + local_a4);
        local_7c = *puVar2;
        local_78 = puVar2[1];
        local_74 = puVar2[2];
        FUN_0042dfd0(local_c0,&local_b0);
        FUN_0042dfd0(local_e0,&local_b0);
        FUN_0042e020(&local_60,local_e0,local_c0);
        D3DXVec3Normalize(&local_60,&local_60);
        if (local_5c * local_5c < 0.5) {
          puVar2 = (undefined4 *)FUN_00423750(local_60,0,local_58);
          local_88 = *puVar2;
          local_84 = puVar2[1];
          local_80 = puVar2[2];
          D3DXVec3Normalize(&local_88,&local_88);
          fVar3 = (float10)FUN_0042e0e0(local_48,&local_88);
          local_e4 = (float)fVar3;
          local_34 = -1.0 / local_e4;
          if (local_34 + *(float *)(local_14 + 0xc + local_b4 * 0x10) < local_3c) {
            local_3c = local_34 + *(float *)(local_14 + 0xc + local_b4 * 0x10);
            local_18 = 1.0 - local_e4 * *(float *)(local_14 + 0xc + local_b4 * 0x10);
            uVar1 = FUN_00423750(local_60,0,local_58);
            D3DXVec3Normalize(local_a0,uVar1);
            uVar1 = FUN_00423750(-local_58,0,local_60);
            D3DXVec3Normalize(local_94,uVar1);
            local_30 = 1;
          }
        }
      }
      (**(code **)(**(int **)(local_38 + 8) + 0x40))(*(undefined4 *)(local_38 + 8));
      (**(code **)(**(int **)(local_38 + 8) + 0x48))(*(undefined4 *)(local_38 + 8));
      if (((local_30 != 0) && (local_3c < DAT_006c78a4)) &&
         (DAT_006c78a4 = local_3c, local_3c <= local_2c)) {
        *(undefined1 *)(param_1 + 0x85) = 1;
        if (DAT_006c78a4 < 0.0 == (DAT_006c78a4 == 0.0)) {
          puVar2 = (undefined4 *)FUN_004241d0(local_12c,DAT_006c78a4);
          _DAT_006c78ac = *puVar2;
          _DAT_006c78b0 = puVar2[1];
          _DAT_006c78b4 = puVar2[2];
        }
        else {
          DAT_006c78a4 = 0.0;
          puVar4 = local_120;
          fVar5 = local_18;
          FUN_0042e0a0(local_114);
          puVar2 = (undefined4 *)FUN_004241d0(puVar4,fVar5);
          _DAT_006c78ac = *puVar2;
          _DAT_006c78b0 = puVar2[1];
          _DAT_006c78b4 = puVar2[2];
        }
        fVar5 = local_2c - DAT_006c78a4;
        puVar4 = local_144;
        fVar3 = (float10)FUN_0042e0e0(local_48,local_94,puVar4,fVar5);
        FUN_004241d0(local_138,(float)fVar3);
        puVar2 = (undefined4 *)FUN_004241d0(puVar4,fVar5);
        DAT_006c78b8 = *puVar2;
        DAT_006c78bc = puVar2[1];
        DAT_006c78c0 = puVar2[2];
      }
    }
    if (local_50 != (int *)0x0) {
      (**(code **)(*local_50 + 8))(local_50);
    }
  }
  if (*(int *)(param_2 + 0x48) != 0) {
    FUN_0042d3b0(*(undefined4 *)(param_2 + 0x48),param_3);
  }
  if (*(int *)(param_2 + 0x4c) != 0) {
    FUN_0042d3b0(*(undefined4 *)(param_2 + 0x4c),param_3);
  }
  return;
}

