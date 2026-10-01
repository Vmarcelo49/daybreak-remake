// Function: FUN_0042cd50
// Address:  0x0042cd50
// Source:   batch_decompile (mass dump)
// Hash:     55d7a6d1997ce895


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0042cd50(int param_1,int param_2,float param_3)

{
  byte bVar1;
  undefined4 *puVar2;
  float10 fVar3;
  int local_f4;
  undefined1 local_dc [12];
  ushort local_d0;
  int local_cc;
  ushort local_c8;
  ushort local_c4;
  int local_c0;
  undefined1 local_bc [12];
  uint local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  int local_a0;
  allocator<char> local_9c [12];
  uint local_90;
  allocator<char> local_8c [12];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  int local_68;
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  int local_48;
  undefined4 local_44;
  int *local_40;
  int local_3c;
  undefined1 local_38 [12];
  undefined1 local_2c [4];
  int local_28;
  int local_24;
  undefined1 local_20 [12];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  uint local_8;
  
  FUN_00423750(*(undefined4 *)(param_1 + 0x14),*(float *)(param_1 + 0x18) + 50.0,
               *(undefined4 *)(param_1 + 0x1c));
  FUN_00423750(0,0xbf800000,0);
  local_24 = 0;
  local_28 = *(int *)(param_2 + 0x44);
  do {
    if (local_28 == 0) {
      if (*(int *)(param_2 + 0x48) != 0) {
        FUN_0042cd50(*(undefined4 *)(param_2 + 0x48),param_3);
      }
      if (*(int *)(param_2 + 0x4c) != 0) {
        FUN_0042cd50(*(undefined4 *)(param_2 + 0x4c),param_3);
      }
      return;
    }
    if (local_28 == 0) {
      local_f4 = 0;
    }
    else {
      local_f4 = local_28 + -4;
    }
    local_3c = local_f4;
    local_40 = (int *)0x0;
    local_44 = D3DXIntersect(*(undefined4 *)(local_28 + 8),local_20,local_38,&local_24,local_14,
                             local_10,local_c,local_2c,&local_40,&local_8);
    if (local_24 != 0) {
      local_64 = (**(code **)(*local_40 + 0xc))(local_40);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_54);
      std::allocator<char>::allocator<char>(local_8c);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_80);
      std::allocator<char>::allocator<char>(local_9c);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_ac);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_60);
      std::allocator<char>::allocator<char>((allocator<char> *)&local_74);
      local_90 = (**(code **)(**(int **)(local_28 + 8) + 0x18))(*(undefined4 *)(local_28 + 8));
      local_68 = D3DXGetFVFVertexSize(local_90);
      local_24 = 0;
      (**(code **)(**(int **)(local_28 + 8) + 0x3c))(*(undefined4 *)(local_28 + 8),0x10,&local_a0);
      (**(code **)(**(int **)(local_28 + 8) + 0x44))(*(undefined4 *)(local_28 + 8),0x10,&local_48);
      for (local_b0 = 0; local_b0 < local_8; local_b0 = local_b0 + 1) {
        local_cc = *(int *)(local_64 + local_b0 * 0x10);
        local_c8 = *(ushort *)(local_48 + local_cc * 6);
        local_d0 = *(ushort *)(local_48 + 2 + local_cc * 6);
        local_c4 = *(ushort *)(local_48 + 4 + local_cc * 6);
        local_c0 = local_a0;
        if ((local_90 & 0x40) == 0) {
LAB_0042d053:
          puVar2 = (undefined4 *)((uint)local_c8 * local_68 + local_a0);
          local_ac = *puVar2;
          local_a8 = puVar2[1];
          local_a4 = puVar2[2];
          puVar2 = (undefined4 *)((uint)local_d0 * local_68 + local_a0);
          local_60 = *puVar2;
          local_5c = puVar2[1];
          local_58 = puVar2[2];
          puVar2 = (undefined4 *)((uint)local_c4 * local_68 + local_a0);
          local_74 = *puVar2;
          local_70 = puVar2[1];
          local_6c = puVar2[2];
          FUN_0042dfd0(local_bc,&local_ac);
          FUN_0042dfd0(local_dc,&local_ac);
          FUN_0042e020(&local_54,local_dc,local_bc);
          D3DXVec3Normalize(&local_54,&local_54);
          if ((0.1 <= local_50 * local_50) || (param_3 < 0.0 == (param_3 == 0.0))) {
            if ((*(float *)(local_64 + 0xc + local_b0 * 0x10) - 1.0) - 50.0 <
                *(float *)(param_1 + 0x7c)) {
              *(float *)(param_1 + 0x7c) =
                   (*(float *)(local_64 + 0xc + local_b0 * 0x10) - 1.0) - 50.0;
            }
          }
          else if (_DAT_006c789c <
                   -(((*(float *)(local_64 + 0xc + local_b0 * 0x10) - 1.0) - 50.0) + param_3)) {
            puVar2 = (undefined4 *)FUN_00423750(local_54,0,local_4c);
            local_80 = *puVar2;
            local_7c = puVar2[1];
            local_78 = puVar2[2];
            D3DXVec3Normalize(&DAT_006c78ac,&local_80);
            _DAT_006c789c =
                 -(((*(float *)(local_64 + 0xc + local_b0 * 0x10) - 1.0) - 50.0) + param_3);
            fVar3 = (float10)FUN_0042df90(local_50);
            _DAT_006c7894 = (float)fVar3;
          }
        }
        else {
          bVar1 = *(byte *)(local_a0 + 0x18 + (uint)local_c8 * local_68);
          if ((((*(byte *)(local_a0 + 0x1a + (uint)local_c8 * local_68) < 0x80) &&
               (DAT_006c7898 = 1, 0.0 < (*(float *)(local_64 + 0xc + local_b0 * 0x10) - 1.0) - 50.0)
               ) && (((*(float *)(local_64 + 0xc + local_b0 * 0x10) - 1.0) - 50.0) + param_3 < 0.0))
             && ((bVar1 < 0x80 && (param_3 < -5.0)))) {
            DAT_006c78a8 = 1;
          }
          if (0x7f < bVar1) goto LAB_0042d053;
        }
      }
      (**(code **)(**(int **)(local_28 + 8) + 0x40))(*(undefined4 *)(local_28 + 8));
      (**(code **)(**(int **)(local_28 + 8) + 0x48))(*(undefined4 *)(local_28 + 8));
    }
    if (local_40 != (int *)0x0) {
      (**(code **)(*local_40 + 8))(local_40);
    }
    local_28 = *(int *)(local_28 + 0x20);
  } while( true );
}

