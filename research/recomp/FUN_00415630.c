// ============================================
// Address:  0x00415630
// Original: FUN_00415630
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00415630(int param_1, int param_2, undefined4 param_3)

{
    undefined4 uVar1;
    int local_8c;
    char local_80;
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
        if (local_8c == 0xd)
        {
            *(undefined4 *)(param_1 + 0x140 + param_2 * 4) = 1;
        }
        else if (local_8c == 0xf)
        {
            *(undefined4 *)(param_1 + 0x120 + param_2 * 4) = 1;
        }
        break;
    case 10:
        FUN_00416670();
        FUN_00416500(param_3);
        if (DAT_006cfdc8 != '\0')
        {
            FUN_00415d30(0, local_7c, 0, 8);
            FUN_00646110((int)local_74, local_72, local_73);
        }
        break;
    case 0xf:
        FUN_00416600();
        FUN_00416560(param_3);
        _memcpy(&DAT_006cfb58 + param_2 * 9, local_14, 9);
        _memcpy((void *)(param_1 + 0x194 + param_2 * 9), local_14, 9);
        FUN_00645dc0(param_2, &DAT_006cfb58 + param_2 * 9);
        *(undefined1 *)(param_1 + param_2 + 0x18c) = 1;
        FUN_00415d30(0, param_1 + 0x184, 0, 0x88);
        break;
    case 0x11:
        FUN_00416700();
        FUN_004165b0(param_3);
        if (local_80 == '\x01')
        {
            FUN_00415ae0(param_2);
        }
        else if (local_80 == '\x02')
        {
            FUN_00415be0(param_2);
        }
    }
    return;
}
