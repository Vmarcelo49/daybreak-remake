// ============================================
// Address:  0x0041b4d0
// Original: FUN_0041b4d0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0041b4d0(int param_1, undefined4 param_2, undefined4 param_3)

{
    char cVar1;
    int iVar2;
    CHAR local_1b4[276];
    int local_a0;
    undefined1 local_9c[8];
    undefined4 local_94;
    int local_88;
    int local_84;
    int local_80;
    undefined1 auStack_74[8];
    undefined1 auStack_6c[72];
    undefined1 auStack_24[8];
    char acStack_1c[16];
    undefined4 local_c;
    int local_8;

    local_c = DAT_006b77f4;
    iVar2   = FUN_004165e0(param_2);
    if (iVar2 == 1)
    {
        FUN_00416410();
        FUN_0041d7e0(param_2);
        if (local_88 == 0xe)
        {
            DAT_006cfa2c = 1;
        }
        else if (local_88 == 0x12)
        {
            FUN_00416410();
            local_94 = 0x13;
            FUN_0041afb0(local_9c, 0, 8);
        }
    }
    else if (iVar2 == 0xb)
    {
        FUN_00416760();
        FUN_0041d7e0(param_2);
        (&DAT_006cfdd1)[local_a0] = 0;
        _memset(&DAT_006cfb58 + local_a0 * 9, 0, 9);
        FUN_00645dc0(local_a0, &DAT_006cfb58 + local_a0 * 9);
        if (-1 < (char)(&DAT_006cfde1)[local_a0])
        {
            cVar1 = (&DAT_006cfb08)[(char)(&DAT_006cfde1)[local_a0] * 4];
            if (-1 < cVar1)
            {
                *(undefined4 *)(&DAT_006cfb08 + (char)(&DAT_006cfde1)[local_a0] * 4) = 0xffffffff;
                (&DAT_006cfaf8)[cVar1]                                               = 4;
            }
            (&DAT_006cfb18)[(char)(&DAT_006cfde1)[local_a0]] = 0xffffffff;
            (&DAT_006cfde1)[local_a0]                        = 0xff;
        }
    }
    else if (iVar2 == 0x10)
    {
        FUN_00415ea0();
        FUN_00416030(param_2);
        local_8 = -1;
        for (local_80 = 0; local_80 < 8; local_80 = local_80 + 1)
        {
            (&DAT_006cfdd1)[local_80] = auStack_74[local_80];
            if ((&DAT_006cfdd1)[local_80] == '\0')
            {
                _memset(&DAT_006cfb58 + local_80 * 9, 0, 9);
            }
            else
            {
                _memcpy(&DAT_006cfb58 + local_80 * 9, auStack_6c + local_80 * 9, 9);
                local_8 = local_8 + 1;
            }
            FUN_00645dc0(local_80, &DAT_006cfb58 + local_80 * 9);
            (&DAT_006cfde1)[local_80] = auStack_24[local_80];
        }
        DAT_006cfdcc = local_8;
        for (local_84 = 0; local_84 < 4; local_84 = local_84 + 1)
        {
            (&DAT_006cfb18)[local_84] = (int)acStack_1c[local_84];
        }
        FUN_0064bf60();
    }
    else if (*(int *)(param_1 + 0x124) == 0)
    {
        FUN_0063c2a0(param_2, param_3);
    }
    else
    {
        iVar2 = FUN_004165e0(param_2);
        if (iVar2 == 0x16)
        {
            if (*(int *)(param_1 + 0x124) == 1)
            {
                *(undefined4 *)(param_1 + 0x124) = 2;
            }
        }
        else
        {
            if (iVar2 != 0x17)
            {
                if (iVar2 != 0x18)
                {
                    return;
                }
                wsprintfA(local_1b4, "data/bgm/%02d.ogg", DAT_006cfaf4);
                FUN_0065b870(local_1b4);
                _DAT_006cfa28 = 2;
            }
            *(undefined4 *)(param_1 + 0x124) = 0;
        }
    }
    return;
}
