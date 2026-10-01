// ============================================
// Address:  0x004183d0
// Original: FUN_004183d0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_004183d0(int param_1, int param_2, undefined4 param_3)

{
    undefined4 uVar1;
    undefined1 local_169;
    int local_158;
    undefined1 local_154[8];
    char local_14c;
    undefined1 local_14a[86];
    int local_f4;
    int local_f0;
    undefined1 local_ec[8];
    undefined1 auStack_e4[8];
    undefined1 auStack_dc[72];
    undefined1 auStack_94[8];
    undefined1 auStack_8c[4];
    undefined1 local_88;
    undefined1 local_87;
    undefined1 local_86;
    undefined1 local_85;
    undefined1 local_84;
    undefined1 local_83;
    undefined1 local_7c[8];
    char local_74;
    undefined1 local_73;
    undefined1 local_72[94];
    undefined1 local_14[12];
    undefined4 local_8;

    local_8 = DAT_006b77f4;
    uVar1   = FUN_004165e0(param_3);
    switch (uVar1)
    {
    case 1:
        FUN_00416410();
        FUN_0041d7e0(param_3);
        if (local_158 == 0xd)
        {
            *(undefined4 *)(param_1 + 0x120 + param_2 * 4) = 1;
        }
        else if (local_158 == 0xf)
        {
            *(undefined4 *)(param_1 + 0x140 + param_2 * 4) = 1;
        }
        break;
    case 2:
        if (((&DAT_006cfdd1)[param_2] != '\0') && (-1 < (char)(&DAT_006cfde1)[param_2]))
        {
            (**(code **)(*(int *)(param_1 + 0x2b4) + 4))(param_3);
            FUN_00417730(*(undefined2 *)(param_1 + 700));
        }
        break;
    case 10:
        FUN_00416670();
        FUN_00416500(param_3);
        if (DAT_006cfdc8 != '\0')
        {
            FUN_00415d30(0, local_154, 0, 8);
            if (((char)(&DAT_006cfde1)[param_2] < '\0') || (*(char *)(param_1 + -0x158) != '\0'))
            {
                local_169 = 0;
            }
            else
            {
                local_169 = 1;
            }
            FUN_00646110((int)local_14c,
                         local_14a,
                         CONCAT31((char)(&DAT_006cfde1)[param_2] >> 7, local_169));
        }
        break;
    case 0xf:
        FUN_00416600();
        FUN_00416560(param_3);
        FUN_00415ea0();
        local_84 = 0;
        local_83 = 0;
        local_88 = DAT_006cfdd0;
        local_87 = DAT_006cfdf9;
        local_86 = DAT_006cfe1c;
        local_85 = DAT_006cfe1e;
        _memcpy(&DAT_006cfb58 + param_2 * 9, local_14, 9);
        FUN_00645dc0(param_2, &DAT_006cfb58 + param_2 * 9);
        for (local_f0 = 0; local_f0 < 8; local_f0 = local_f0 + 1)
        {
            _memcpy(auStack_dc + local_f0 * 9, &DAT_006cfb58 + local_f0 * 9, 9);
            auStack_e4[local_f0] = (&DAT_006cfdd1)[local_f0];
            auStack_94[local_f0] = (&DAT_006cfde1)[local_f0];
        }
        for (local_f4 = 0; local_f4 < 4; local_f4 = local_f4 + 1)
        {
            auStack_8c[local_f4] = *(undefined1 *)(&DAT_006cfb18 + local_f4);
        }
        FUN_00415d30(0, local_ec, 0, 8);
        FUN_00416670();
        local_74 = (char)param_2;
        local_73 = 2;
        FUN_0066b860(local_72, &DAT_006a1f4c);
        FUN_00415d30(0, local_7c, 0, 8);
        FUN_00646110((int)local_74, local_72, local_73);
    }
    return;
}
