// ============================================
// Address:  0x0041a260
// Original: FUN_0041a260
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_0041a260(int param_1)

{
    char cVar1;
    undefined4 uVar2;
    void *pvVar3;
    undefined4 local_50;
    undefined1 local_34[8];
    undefined1 local_2c[12];
    undefined4 local_20;
    undefined1 local_1c[8];
    undefined1 local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069dfbf;
    local_10      = ExceptionList;
    local_20      = DAT_006b77f4;
    ExceptionList = &local_10;
    if (DAT_006cfdd1 == '\0')
    {
        ExceptionList = &local_10;
        FUN_00416600();
        _memcpy(local_2c, &DAT_006cfdb8, 9);
        FUN_0041afb0(local_34, 0, 8);
    }
    DAT_006cfdd1 = 1;
    cVar1        = FUN_0041af70();
    if ((cVar1 == '\0') && (cVar1 = FUN_0064c230(), cVar1 == '\0'))
    {
        if (*(int *)(param_1 + 0x1004) == 1)
        {
            DAT_006cfdb4 = DAT_006d7648;
            uVar2        = 0xf;
        }
        else if (*(int *)(param_1 + 0x1004) == 2)
        {
            uVar2 = 0xb;
        }
        else if (*(int *)(param_1 + 0x1004) == 3)
        {
            DAT_006cfba0 = 1;
            DAT_006cfba4 = 0;
            if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0)
            {
                if (*(int *)(DAT_006cfa24 + DAT_006cfdb4 * 4) != 0)
                {
                    FUN_0040dce0(1);
                }
                *(undefined4 *)(DAT_006cfa24 + DAT_006cfdb4 * 4) = 0;
            }
            pvVar3  = operator_new(0x180);
            local_8 = 0;
            if (pvVar3 == (void *)0x0)
            {
                local_50 = 0;
            }
            else
            {
                local_50 = FUN_0040dab0();
            }
            local_8                                          = 0xffffffff;
            *(undefined4 *)(DAT_006cfa24 + DAT_006cfdb4 * 4) = local_50;
            FUN_00657330(&DAT_006cfe20);
            uVar2 = 0x11;
        }
        else
        {
            cVar1 = FUN_00645e10();
            if (cVar1 == '\0')
            {
                FUN_006584e0();
                FUN_006585f0();
                cVar1 = FUN_006586d0(0x1c);
                if ((cVar1 != '\0') &&
                    ((cVar1 = FUN_006586d0(0xb8),
                      cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))))
                {
                    FUN_0064ad70();
                }
                FUN_00657390();
                cVar1 = FUN_0064c090();
                if (cVar1 == '\0')
                {
                    FUN_00416700();
                    if (DAT_006cae9c == 1)
                    {
                        FUN_0064aed0(0);
                        local_14 = 1;
                        FUN_0041afb0(local_1c, 0, 8);
                    }
                    else if (DAT_006caea0 == 1)
                    {
                        FUN_0064aed0(1);
                        local_14 = 2;
                        FUN_0041afb0(local_1c, 0, 8);
                    }
                    if ((DAT_006cae98 == 1) || ((DAT_006cae98 % 6 == 1 && (0x3c < DAT_006cae98))))
                    {
                        FUN_006463c0();
                    }
                    if ((DAT_006cae98 == -1) ||
                        ((-DAT_006cae98 % 6 == 1 && (DAT_006cae98 < -0x3c))))
                    {
                        FUN_00646460();
                    }
                    uVar2 = 0xd;
                }
                else
                {
                    uVar2 = 0xd;
                }
            }
            else
            {
                uVar2 = 0xd;
            }
        }
    }
    else
    {
        FUN_0065f8b0();
        uVar2 = 0xb;
    }
    ExceptionList = local_10;
    return uVar2;
}
