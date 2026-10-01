// ============================================
// Address:  0x005f8510
// Original: FUN_005f8510
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall
FUN_005f8510(int param_1, int param_2, undefined4 param_3, undefined4 param_4, char param_5)

{
    char cVar1;
    undefined4 uVar2;
    wchar_t *pwVar3;
    undefined1 local_4dc[20];
    undefined4 local_4c8;
    uint local_4c4;
    undefined4 *local_4c0;
    uint local_4bc;
    uint local_4b8;
    wchar_t *local_4b4;
    undefined1 local_4b0[132];
    uint local_42c;
    wchar_t *local_428;
    uint local_424;
    undefined1 local_420[24];
    uint local_408;
    undefined1 *local_404;
    uint local_400;
    undefined1 local_3fc[28];
    int local_3e0;
    uint local_3dc;
    undefined1 local_3d8[60];
    undefined1 local_39c[32];
    int local_37c;
    undefined1 local_378[268];
    undefined1 local_26c[4];
    uint local_268;
    undefined1 local_264[60];
    CHAR local_228[264];
    undefined1 local_120[264];
    undefined4 local_18;
    uint local_14;
    void *local_10;
    undefined1 *puStack_c;
    uint local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e6dc;
    local_10      = ExceptionList;
    local_18      = DAT_006b77f4;
    ExceptionList = &local_10;
    FUN_00655600(param_3, local_378, local_228);
    cVar1 = FUN_00653540(param_3);
    if (cVar1 == '\0')
    {
        uVar2 = 0;
    }
    else
    {
        FUN_00653760(local_26c, 4);
        FUN_00653760(local_120, 0x104);
        wsprintfA(local_228, "%s%s", local_378, local_120);
        cVar1 = FUN_0064d940(local_228);
        if (cVar1 == '\0')
        {
            uVar2 = 0;
        }
        else
        {
            FUN_00653540(param_3);
            FUN_00653960(0x108, 0);
            FUN_00653760(&local_14, 4);
            for (local_3dc = 0; local_3dc < local_14; local_3dc = local_3dc + 1)
            {
                FUN_00423350();
                local_8 = 0;
                FUN_00653760(&local_3e0, 4);
                if (local_3e0 == param_5)
                {
                    local_404 = (undefined1 *)(param_2 * 0x1c + *(int *)(param_1 + 0x34));
                }
                else
                {
                    local_404 = local_3fc;
                }
                FUN_00653760(local_404, 4);
                FUN_00653760(local_404 + 4, 4);
                FUN_00653760(&local_400, 4);
                FUN_004244c0();
                for (local_408 = 0; local_408 < local_400; local_408 = local_408 + 1)
                {
                    FUN_00423560();
                    local_8 = CONCAT31(local_8._1_3_, 1);
                    FUN_00424550(local_420);
                    local_428 = std::basic_string<wchar_t,
                                                  std::char_traits<wchar_t>,
                                                  std::allocator<wchar_t> _>::
                        back((basic_string<wchar_t,
                                           std::char_traits<wchar_t>,
                                           std::allocator<wchar_t> _> *)(local_404 + 8));
                    FUN_00653760(local_428, 4);
                    local_424 = FUN_0063bf40();
                    FUN_00653760(&local_424, 4);
                    for (local_42c = 0; local_42c < local_424; local_42c = local_42c + 1)
                    {
                        FUN_00423480();
                        FUN_004243e0(local_4b0);
                        local_4b4 = std::basic_string<wchar_t,
                                                      std::char_traits<wchar_t>,
                                                      std::allocator<wchar_t> _>::
                            back((basic_string<wchar_t,
                                               std::char_traits<wchar_t>,
                                               std::allocator<wchar_t> _> *)(local_428 + 2));
                        FUN_00653760(local_39c, 0x1e);
                        uVar2                    = FUN_0064e6c0(local_39c);
                        *(undefined4 *)local_4b4 = uVar2;
                        FUN_00653760(local_4b4 + 2, 4);
                        FUN_00653760(&local_37c, 4);
                        *(float *)(local_4b4 + 6) = (float)local_37c;
                        FUN_00653760(&local_37c, 4);
                        *(float *)(local_4b4 + 8) = (float)local_37c;
                        FUN_00653760(&local_37c, 4);
                        *(float *)(local_4b4 + 10) = (float)local_37c;
                        FUN_00653760(local_4b4 + 0x12, 4);
                        FUN_00653760(local_4b4 + 0x18, 0x50);
                        FUN_00653760(local_4b4 + 0x14, 4);
                        FUN_00653760(local_4b4 + 0x16, 4);
                        FUN_00653760(local_4b4 + 4, 4);
                        FUN_00653760(&local_37c, 4);
                        *(float *)(local_4b4 + 0xc) = (float)local_37c;
                        FUN_00653760(&local_37c, 4);
                        *(float *)(local_4b4 + 0xe) = (float)local_37c;
                        FUN_00653760(&local_37c, 4);
                        *(float *)(local_4b4 + 0x10) = (float)local_37c;
                    }
                    local_8 = local_8 & 0xffffff00;
                    FUN_004234c0();
                }
                local_8 = 0xffffffff;
                FUN_004232c0();
            }
            FUN_00653760(&local_268, 4);
            for (local_4b8 = 0; local_4b8 < local_268; local_4b8 = local_4b8 + 1)
            {
                local_4c0 = (undefined4 *)(param_2 * 0x38 + *(int *)(param_1 + 0x38));
                FUN_0064e8b0(local_4b8);
                uVar2      = FUN_0066b668();
                *local_4c0 = uVar2;
                FUN_00653760(local_4c0 + 7, 4);
                FUN_00653760(local_4c0 + 8, 4);
                local_4bc = FUN_0063bf40();
                FUN_00653760(&local_4bc, 4);
                for (local_4c4 = 0; local_4c4 < local_4bc; local_4c4 = local_4c4 + 1)
                {
                    FUN_00423460();
                    FUN_00424270(local_4dc);
                    pwVar3 = std::basic_string<wchar_t,
                                               std::char_traits<wchar_t>,
                                               std::allocator<wchar_t> _>::
                        back((basic_string<wchar_t,
                                           std::char_traits<wchar_t>,
                                           std::allocator<wchar_t> _> *)(local_4c0 + 9));
                    FUN_00653760(pwVar3, 4);
                    FUN_00653760(pwVar3 + 2, 4);
                    FUN_00653760(pwVar3 + 4, 4);
                    FUN_00653760(local_3d8, 0x3c);
                    uVar2                       = FUN_0064e7c0(local_3d8);
                    *(undefined4 *)(pwVar3 + 6) = uVar2;
                    FUN_00653760(local_264, 0x3c);
                    local_4c8 = FUN_00653960(0, 1);
                    FUN_0064ecd0(local_264, pwVar3 + 8);
                    FUN_00653540(param_3);
                    local_4c8 = FUN_00653960(local_4c8, 0);
                }
            }
            uVar2 = 1;
        }
    }
    ExceptionList = local_10;
    return uVar2;
}
