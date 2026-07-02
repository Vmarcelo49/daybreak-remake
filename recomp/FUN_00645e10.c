// ============================================
// Address:  0x00645e10
// Original: FUN_00645e10
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00645e10(int param_1)

{
    char cVar1;
    void *_Src;
    undefined4 uVar2;
    undefined4 *puVar3;
    int iVar4;
    size_t _Size;
    undefined1 local_7c[4];
    undefined1 local_78[4];
    undefined1 local_74[8];
    undefined1 local_6c;
    undefined1 local_6b;
    char local_6a[90];
    undefined4 local_10;
    int local_c;
    int local_8;

    local_10 = DAT_006b77f4;
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        if (*(int *)(param_1 + 0xdd4 + local_8 * 4) != 0)
        {
            *(int *)(param_1 + 0xdd4 + local_8 * 4) = *(int *)(param_1 + 0xdd4 + local_8 * 4) + -1;
        }
    }
    FUN_00646f40();
    cVar1 = FUN_00660a10();
    if (cVar1 == '\0')
    {
        iVar4 = FUN_0068de10();
        if (iVar4 != 0)
        {
            FUN_0065d670();
            FUN_00656200(*(undefined4 *)(param_1 + 0x138));
            FUN_00654170(0);
            FUN_0065d6a0();
        }
        iVar4 = FUN_0068de10();
        if (iVar4 != 0)
        {
            FUN_0065d670();
            FUN_00656200(*(undefined4 *)(param_1 + 0x134));
            FUN_00654170(0);
            FUN_0065d6a0();
        }
        uVar2 = 0;
    }
    else
    {
        cVar1 = FUN_00661320();
        if (cVar1 == '\0')
        {
            local_c = FUN_00660f60();
            if (local_c != 0)
            {
                FUN_0065d670();
                FUN_00656200(*(undefined4 *)(param_1 + 0x134));
                puVar3 =
                    (undefined4 *)FUN_00656190(local_78, local_c, *(undefined4 *)(param_1 + 0x140));
                *(undefined4 *)(param_1 + 0x134) = *puVar3;
                FUN_00655690(*(undefined4 *)(param_1 + 0x134), 0, 0, 8, 0x10);
                FUN_0065d6a0();
            }
            local_c = FUN_00660f90();
            if (local_c != 0)
            {
                FUN_0065d670();
                FUN_00656200(*(undefined4 *)(param_1 + 0x138));
                puVar3 =
                    (undefined4 *)FUN_00656190(local_7c, local_c, *(undefined4 *)(param_1 + 0x140));
                *(undefined4 *)(param_1 + 0x138) = *puVar3;
                FUN_00655690(*(undefined4 *)(param_1 + 0x138), 0, 0, 8, 0x10);
                FUN_0065d6a0();
            }
            uVar2 = 1;
        }
        else
        {
            FUN_00416670();
            local_6c = *(undefined1 *)(param_1 + 0xdf5);
            local_6b = 0;
            _Size    = 0x50;
            _Src     = (void *)FUN_00646f20();
            _memcpy(local_6a, _Src, _Size);
            if (local_6a[0] == '\0')
            {
                FUN_006609f0(0);
                uVar2 = 1;
            }
            else
            {
                if (*(char *)(param_1 + 0xdf4) == '\x02')
                {
                    FUN_0041afb0(local_74, 0, 8);
                }
                else if (*(char *)(param_1 + 0xdf4) == '\x01')
                {
                    FUN_00415d30(0, local_74, 0, 8);
                    FUN_00646110((int)*(char *)(param_1 + 0xdf5),
                                 local_6a,
                                 *(undefined1 *)(param_1 + 0xe60));
                }
                uVar2 = 1;
            }
        }
    }
    return uVar2;
}
