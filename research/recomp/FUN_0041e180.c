// ============================================
// Address:  0x0041e180
// Original: FUN_0041e180
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_0041e180(
    int param_1, char *param_2, char param_3, char param_4, char param_5, undefined1 param_6)

{
    void *pvVar1;
    undefined4 uVar2;
    wchar_t *pwVar3;
    int iVar4;
    undefined4 uVar5;
    undefined4 local_51c;
    undefined4 local_518;
    undefined1 local_4ec[20];
    undefined4 local_4d8;
    uint local_4d4;
    undefined4 *local_4d0;
    uint local_4cc;
    uint local_4c8;
    wchar_t *local_4c4;
    undefined1 local_4c0[132];
    uint local_43c;
    wchar_t *local_438;
    uint local_434;
    undefined1 local_430[24];
    uint local_418;
    int local_414;
    uint local_410;
    int local_40c;
    uint local_408;
    undefined1 local_404[60];
    undefined1 local_3c8[68];
    int local_384;
    CHAR local_380[264];
    undefined1 local_278[4];
    uint local_274;
    CHAR local_270[268];
    undefined1 local_164[60];
    undefined1 local_128[268];
    undefined4 local_1c;
    undefined1 local_18[4];
    uint local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e227;
    local_10      = ExceptionList;
    local_1c      = DAT_006b77f4;
    ExceptionList = &local_10;
    wsprintfA(local_270, "data/%s/%02d.dat", param_2, (int)param_3);
    FUN_00653540(local_270);
    FUN_00653760(local_278, 4);
    FUN_00653760(local_128, 0x104);
    if (*(int *)(param_1 + 0x11c) != 0)
    {
        if (*(int *)(param_1 + 0x11c) != 0)
        {
            FUN_00402010(1);
        }
        *(undefined4 *)(param_1 + 0x11c) = 0;
    }
    switch (param_5)
    {
    case '\0':
        wsprintfA(local_380, "data/%s/%s", param_2, local_128);
        break;
    case '\x01':
        wsprintfA(local_380, "data/%s_B/%s", param_2, local_128);
        break;
    case '\x02':
        wsprintfA(local_380, "data/%s_C/%s", param_2, local_128);
        break;
    case '\x03':
        wsprintfA(local_380, "data/%s_D/%s", param_2, local_128);
        break;
    case '\x04':
        wsprintfA(local_380, "data/%s_E/%s", param_2, local_128);
        break;
    case '\x05':
        wsprintfA(local_380, "data/%s_F/%s", param_2, local_128);
    }
    pvVar1  = operator_new(0x9c);
    local_8 = 0;
    if (pvVar1 == (void *)0x0)
    {
        local_518 = 0;
    }
    else
    {
        local_518 = FUN_0064d7a0();
    }
    local_8                          = 0xffffffff;
    *(undefined4 *)(param_1 + 0x11c) = local_518;
    FUN_0064d940(local_380);
    FUN_00653540(local_270);
    FUN_00653960(0x108, 0);
    FUN_00653760(param_1 + 0x324, 4);
    FUN_00653760(param_1 + 0x328, 4);
    FUN_00653760(local_18, 4);
    FUN_00653760(&param_3, 4);
    FUN_00653760(param_1 + 0x32c, 4);
    FUN_00653760(param_1 + 0x330, 4);
    FUN_00653760(&local_14, 4);
    for (local_408 = 0; local_408 < local_14; local_408 = local_408 + 1)
    {
        FUN_00653760(&local_40c, 4);
        local_414 = param_1 + 0x880 + local_40c * 0x1c;
        FUN_00653760(local_414, 4);
        FUN_00653760(local_414 + 4, 4);
        FUN_00653760(&local_410, 4);
        FUN_004244c0();
        for (local_418 = 0; local_418 < local_410; local_418 = local_418 + 1)
        {
            FUN_00423560();
            local_8 = 1;
            FUN_00424550(local_430);
            local_438 = std::
                basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> _>::back(
                    (basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> _>
                         *)(local_414 + 8));
            FUN_00653760(local_438, 4);
            FUN_00653760(&local_434, 4);
            for (local_43c = 0; local_43c < local_434; local_43c = local_43c + 1)
            {
                FUN_00423480();
                FUN_004243e0(local_4c0);
                local_4c4 = std::basic_string<wchar_t,
                                              std::char_traits<wchar_t>,
                                              std::allocator<wchar_t> _>::
                    back(
                        (basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> _>
                             *)(local_438 + 2));
                FUN_00653760(local_3c8, 0x1e);
                uVar2                    = FUN_0064e6c0(local_3c8);
                *(undefined4 *)local_4c4 = uVar2;
                FUN_00653760(local_4c4 + 2, 4);
                FUN_00653760(&local_384, 4);
                *(float *)(local_4c4 + 6) = (float)local_384;
                FUN_00653760(&local_384, 4);
                *(float *)(local_4c4 + 8) = (float)local_384;
                FUN_00653760(&local_384, 4);
                *(float *)(local_4c4 + 10) = (float)local_384;
                FUN_00653760(local_4c4 + 0x12, 4);
                FUN_00653760(local_4c4 + 0x18, 0x50);
                FUN_00653760(local_4c4 + 0x14, 4);
                FUN_00653760(local_4c4 + 0x16, 4);
                FUN_00653760(local_4c4 + 4, 4);
                FUN_00653760(&local_384, 4);
                *(float *)(local_4c4 + 0xc) = (float)local_384;
                FUN_00653760(&local_384, 4);
                *(float *)(local_4c4 + 0xe) = (float)local_384;
                FUN_00653760(&local_384, 4);
                *(float *)(local_4c4 + 0x10) = (float)local_384;
            }
            local_8 = 0xffffffff;
            FUN_004234c0();
        }
    }
    FUN_00653760(&local_274, 4);
    for (local_4c8 = 0; local_4c8 < local_274; local_4c8 = local_4c8 + 1)
    {
        local_4d0 = (undefined4 *)(param_1 + 0x75e0 + local_4c8 * 0x38);
        FUN_0064e8b0(local_4c8);
        uVar2      = FUN_0066b668();
        *local_4d0 = uVar2;
        FUN_00653760(local_4d0 + 7, 4);
        FUN_00653760(local_4d0 + 8, 4);
        FUN_00653760(&local_4cc, 4);
        FUN_00424210();
        for (local_4d4 = 0; local_4d4 < local_4cc; local_4d4 = local_4d4 + 1)
        {
            FUN_00423460();
            FUN_00424270(local_4ec);
            pwVar3 = std::
                basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> _>::back(
                    (basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> _>
                         *)(local_4d0 + 9));
            FUN_00653760(pwVar3, 4);
            FUN_00653760(pwVar3 + 2, 4);
            FUN_00653760(pwVar3 + 4, 4);
            FUN_00653760(local_404, 0x3c);
            uVar2                       = FUN_0064e7c0(local_404);
            *(undefined4 *)(pwVar3 + 6) = uVar2;
            FUN_00653760(local_164, 0x3c);
            local_4d8 = FUN_00653960(0, 1);
            FUN_0064ecd0(local_164, pwVar3 + 8);
            FUN_00653540(local_270);
            local_4d8 = FUN_00653960(local_4d8, 0);
        }
    }
    uVar2                            = FUN_0064e7c0(&DAT_006a225c);
    *(undefined4 *)(param_1 + 0x31c) = uVar2;
    FUN_0064ecd0(&DAT_006a2268, param_1 + 800);
    *(char *)(param_1 + 0x688) = param_4;
    if (param_4 != '\0')
    {
        uVar2                            = FUN_0064e7c0(&DAT_006a2278);
        *(undefined4 *)(param_1 + 0x68c) = uVar2;
        FUN_0064ecd0(&DAT_006a2280, param_1 + 0x694);
        uVar2                            = FUN_0064e7c0(&DAT_006a2288);
        *(undefined4 *)(param_1 + 0x690) = uVar2;
        FUN_0064ecd0(&DAT_006a2298, param_1 + 0x698);
    }
    iVar4 = __stricmp(param_2, "rena");
    if ((((iVar4 == 0) && (param_3 == '!')) ||
         ((iVar4 = __stricmp(param_2, "rika"), iVar4 == 0 && (param_3 == '%')))) ||
        ((iVar4 = __stricmp(param_2, "chie"), iVar4 == 0 && (param_5 == '\x01'))))
    {
        wsprintfA(local_380, "data/voice/%sB", param_2);
        FUN_00431e70(local_380, param_6);
        FUN_00423510(DAT_006cfcf0 * DAT_006cfcfc);
    }
    else
    {
        wsprintfA(local_380, "data/voice/%s", param_2);
        FUN_00431e70(local_380, param_6);
        FUN_00423510(DAT_006cfcf0 * DAT_006cfcfc);
    }
    iVar4 = _strcmp(param_2, "hanyu");
    if ((iVar4 == 0) && (param_3 == ' '))
    {
        pvVar1  = operator_new(0x98);
        local_8 = 2;
        if (pvVar1 == (void *)0x0)
        {
            local_51c = 0;
        }
        else
        {
            local_51c = FUN_00431d30();
        }
        local_8                           = 0xffffffff;
        *(undefined4 *)(param_1 + 0xaeb4) = local_51c;
        wsprintfA(local_380, "data/voice/%sB", param_2);
        FUN_00431e70(local_380, 0);
        FUN_00423510(DAT_006cfcf0 * DAT_006cfcfc);
    }
    uVar2 = FUN_0064e6c0("Bip01_Prop2");
    uVar5 = FUN_0064e6c0("Bip01_Prop1");
    FUN_00433eb0(param_1, (int)param_3, uVar5, uVar2);
    uVar2                            = FUN_0064e6c0("Bip01_Spine");
    *(undefined4 *)(param_1 + 0x378) = uVar2;
    uVar2                            = FUN_0064e710("Bip01_Spine");
    *(undefined4 *)(param_1 + 0x37c) = uVar2;
    FUN_0064e760("Bip01_Spine", param_1 + 0x338);
    FUN_00423530("Bip01_Prop1");
    iVar4 = __stricmp(param_2, "natumi");
    if (iVar4 == 0)
    {
        FUN_00423530("Bip01_Prop2");
    }
    uVar2                            = FUN_0064e6c0("Bip01_Head");
    *(undefined4 *)(param_1 + 0x380) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip01_Spine");
    *(undefined4 *)(param_1 + 900)   = uVar2;
    uVar2                            = FUN_0064e6c0("Bip00");
    *(undefined4 *)(param_1 + 0x64c) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip01_Head");
    *(undefined4 *)(param_1 + 0x650) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip01_Spine");
    *(undefined4 *)(param_1 + 0x654) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip01_L_Forearm");
    *(undefined4 *)(param_1 + 0x658) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip01_R_Forearm");
    *(undefined4 *)(param_1 + 0x65c) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip00_L_Calf");
    *(undefined4 *)(param_1 + 0x660) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip00_R_Calf");
    *(undefined4 *)(param_1 + 0x664) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip01_L_Hand");
    *(undefined4 *)(param_1 + 0x668) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip01_R_Hand");
    *(undefined4 *)(param_1 + 0x66c) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip00_L_Foot");
    *(undefined4 *)(param_1 + 0x670) = uVar2;
    uVar2                            = FUN_0064e6c0("Bip00_R_Foot");
    *(undefined4 *)(param_1 + 0x674) = uVar2;
    _memset((void *)(param_1 + 0x678), 0, 0xb);
    ExceptionList = local_10;
    return;
}
