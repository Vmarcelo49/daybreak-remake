// ============================================
// Address:  0x0041aa10
// Original: FUN_0041aa10
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_0041aa10(int param_1, undefined4 param_2)

{
    undefined4 uVar1;
    int local_13c;
    int local_138;
    undefined4 auStack_12c[4];
    undefined4 auStack_11c[4];
    undefined4 auStack_10c[4];
    undefined1 auStack_fc[16];
    undefined1 auStack_ec[16];
    undefined1 auStack_dc[16];
    undefined4 local_cc;
    undefined4 local_c8;
    undefined4 local_c4;
    undefined4 local_c0;
    undefined4 local_bc;
    undefined4 local_b8;
    int local_a8;
    undefined1 local_a4[8];
    undefined4 local_9c;
    undefined1 local_98[8];
    undefined4 local_90;
    undefined1 local_8c[8];
    undefined4 local_84;
    int local_78;
    char local_6c;
    undefined1 local_6b;
    undefined1 local_6a[86];
    undefined4 local_14;
    int local_10;
    int local_c;
    int local_8;

    local_14 = DAT_006b77f4;
    uVar1    = FUN_004165e0(param_2);
    switch (uVar1)
    {
    case 1:
        FUN_00416410();
        FUN_0041d7e0(param_2);
        if (local_78 == 0xc)
        {
            FUN_00416410();
            local_90 = 0xd;
            FUN_0041afb0(local_98, 0, 2);
        }
        else if (local_78 == 0xe)
        {
            FUN_00416410();
            local_84 = 0xf;
            FUN_0041afb0(local_8c, 0, 2);
            *(undefined4 *)(param_1 + 0x1000) = 1;
        }
        else
        {
            FUN_00416410();
            local_9c = 0xd;
            FUN_0041afb0(local_a4, 0, 2);
        }
        break;
    case 6:
        *(undefined4 *)(param_1 + 0x1000) = 2;
        break;
    case 10:
        FUN_00416670();
        FUN_00416500(param_2);
        FUN_00646110((int)local_6c, local_6a, local_6b);
        break;
    case 0xb:
        FUN_00416760();
        FUN_0041d7e0(param_2);
        (&DAT_006cfdd1)[local_a8] = 0;
        _memset(&DAT_006cfb58 + local_a8 * 9, 0, 9);
        FUN_00645dc0(local_a8, &DAT_006cfb58 + local_a8 * 9);
        break;
    case 0xc:
        FUN_004177a0();
        FUN_00417920(param_2);
        for (local_138 = 0; local_138 < 4; local_138 = local_138 + 1)
        {
            *(undefined4 *)(&DAT_006cfb08 + local_138 * 4) = 0xffffffff;
        }
        for (local_13c = 0; local_13c < 4; local_13c = local_13c + 1)
        {
            (&DAT_006cfb28)[local_13c]                     = auStack_11c[local_13c];
            *(undefined4 *)(&DAT_006cfb38 + local_13c * 4) = auStack_10c[local_13c];
            (&DAT_006cfaf8)[local_13c]                     = auStack_12c[local_13c];
            (&DAT_006cfb48)[local_13c]                     = auStack_fc[local_13c * 4];
            (&DAT_006cfb4c)[local_13c]                     = auStack_ec[local_13c * 4];
            (&DAT_006cfb54)[local_13c]                     = auStack_dc[local_13c * 4];
            if ((-1 < (int)(&DAT_006cfaf8)[local_13c]) && ((int)(&DAT_006cfaf8)[local_13c] < 4))
            {
                *(int *)(&DAT_006cfb08 + (&DAT_006cfaf8)[local_13c] * 4) = local_13c;
            }
        }
        DAT_006cfaf4                      = local_cc;
        DAT_006cf3c0                      = local_c8;
        DAT_006cf3b8                      = local_c4;
        DAT_006cf3bc                      = local_c0;
        DAT_006cf3b0                      = local_bc;
        DAT_006cf3b4                      = local_b8;
        *(undefined4 *)(param_1 + 0x1000) = 3;
        break;
    case 0x10:
        (**(code **)(*(int *)(param_1 + 0x104) + 4))(param_2);
        local_8 = -1;
        for (local_c = 0; local_c < 8; local_c = local_c + 1)
        {
            (&DAT_006cfdd1)[local_c] = *(undefined1 *)(param_1 + local_c + 0x10c);
            if ((&DAT_006cfdd1)[local_c] == '\0')
            {
                _memset(&DAT_006cfb58 + local_c * 9, 0, 9);
            }
            else
            {
                _memcpy(&DAT_006cfb58 + local_c * 9, (void *)(param_1 + 0x114 + local_c * 9), 9);
                local_8 = local_8 + 1;
            }
            FUN_00645dc0(local_c, &DAT_006cfb58 + local_c * 9);
            (&DAT_006cfde1)[local_c] = *(undefined1 *)(param_1 + local_c + 0x15c);
        }
        DAT_006cfdcc = local_8;
        for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1)
        {
            (&DAT_006cfb18)[local_10] = (int)*(char *)(param_1 + local_10 + 0x164);
        }
        FUN_0064bf60();
    }
    return;
}
