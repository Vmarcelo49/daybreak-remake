// ============================================
// Address:  0x00654f00
// Original: FUN_00654f00
// Status:   unreviewed
// ============================================

void __fastcall FUN_00654f00(int param_1)

{
    undefined1 local_140[76];
    undefined1 local_f4[12];
    undefined1 local_e8[12];
    undefined1 local_dc[12];
    undefined1 local_d0[72];
    undefined4 local_88;
    undefined4 local_84;
    undefined4 local_80;
    undefined4 local_7c;
    undefined4 local_78;
    undefined4 local_74;
    undefined4 local_70;
    undefined4 local_6c;
    undefined4 local_68;
    undefined4 local_64;
    undefined4 local_60;
    undefined4 local_5c;
    undefined4 local_58;
    undefined4 local_54;
    undefined4 local_50;
    undefined4 local_4c;
    undefined1 local_48[12];
    undefined4 local_3c;
    undefined1 local_20[12];
    int local_14;

    local_14 = param_1;
    (**(code **)(**(int **)(param_1 + 0x20) + 0xe4))(*(undefined4 *)(param_1 + 0x20), 0x89, 0);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x1a, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 7, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x16, 3);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(
        *(undefined4 *)(local_14 + 0x20), 0x8b, 0xffffffff);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x8f, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 9, 2);
    (**(code **)(**(int **)(local_14 + 0x20) + 0x114))(*(undefined4 *)(local_14 + 0x20), 0, 5, 2);
    (**(code **)(**(int **)(local_14 + 0x20) + 0x114))(*(undefined4 *)(local_14 + 0x20), 0, 6, 2);
    (**(code **)(**(int **)(local_14 + 0x20) + 0x114))(*(undefined4 *)(local_14 + 0x20), 0, 7, 2);
    FUN_00423750(0x3f800000, 0xbf800000, 0x3f800000);
    _memset(&local_88, 0, 0x68);
    local_88 = 3;
    local_78 = 0x3f800000;
    local_84 = 0x3f800000;
    local_80 = 0x3f800000;
    local_7c = 0x3f800000;
    local_58 = 0x3f800000;
    local_64 = 0x3f800000;
    local_60 = 0x3f800000;
    local_5c = 0x3f800000;
    local_68 = 0x3f800000;
    local_74 = 0x3f800000;
    local_70 = 0x3f800000;
    local_6c = 0x3f800000;
    D3DXVec3Normalize(local_48, local_20);
    local_54 = 0;
    local_50 = 0x43fa0000;
    local_4c = 0;
    local_3c = 0x44fa0000;
    (**(code **)(**(int **)(local_14 + 0x20) + 0xcc))(
        *(undefined4 *)(local_14 + 0x20), 0, &local_88);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xd4))(*(undefined4 *)(local_14 + 0x20), 0, 1);
    FUN_0068d8d0();
    FUN_00423750(0, 0, 0x40400000);
    FUN_00423750(0, 0x3f333333, 0);
    FUN_00423750(0, 0x3f800000, 0);
    D3DXMatrixLookAtLH(local_d0, local_dc, local_e8, local_f4);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xb0))(
        *(undefined4 *)(local_14 + 0x20), 2, local_d0);
    FUN_0068d8d0();
    D3DXMatrixPerspectiveFovLH(local_140, 0x3f490fdb, 0x3faaaaab, 0x43fa0000, 0x467a0000);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xb0))(
        *(undefined4 *)(local_14 + 0x20), 3, local_140);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x1c, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(
        *(undefined4 *)(local_14 + 0x20), 0x22, 0x415e74);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x23, 3);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(
        *(undefined4 *)(local_14 + 0x20), 0x24, 0x43fa0000);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(
        *(undefined4 *)(local_14 + 0x20), 0x25, 0x476a6000);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x30, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x1b, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0xf, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x18, 1);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x19, 7);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x13, 5);
    (**(code **)(**(int **)(local_14 + 0x20) + 0xe4))(*(undefined4 *)(local_14 + 0x20), 0x14, 6);
    (**(code **)(**(int **)(local_14 + 0x20) + 0x10c))(*(undefined4 *)(local_14 + 0x20), 0, 4, 4);
    (**(code **)(**(int **)(local_14 + 0x20) + 0x10c))(*(undefined4 *)(local_14 + 0x20), 0, 5, 2);
    (**(code **)(**(int **)(local_14 + 0x20) + 0x10c))(*(undefined4 *)(local_14 + 0x20), 0, 6, 1);
    return;
}
