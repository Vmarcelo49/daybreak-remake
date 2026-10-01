// ============================================
// Address:  0x00416800
// Original: FUN_00416800
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_00416800(undefined4 *param_1)

{
    undefined4 *local_1c;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069de63;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00403ae0();
    local_8 = 0;
    FUN_00415dc0();
    local_8    = CONCAT31(local_8._1_3_, 1);
    *param_1   = &PTR_FUN_006a1f08;
    param_1[1] = &PTR_FUN_006a1ef4;
    for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1)
    {
        if ((int)(&DAT_006cfaf8)[local_14] < 4)
        {
            if (0 < (int)(&DAT_006cfb18)[(&DAT_006cfaf8)[local_14]])
            {
                FUN_0040da90();
            }
        }
        else
        {
            FUN_0040da90();
        }
        FUN_00657850();
        *(undefined2 *)(&DAT_006cb758 + local_14 * 0xc) = 0xffff;
    }
    param_1[0x5b] = 1;
    FUN_00415da0();
    if ((DAT_006cfdc8 == '\0') || (DAT_006cfe1e == '\0'))
    {
        FUN_00415d70(0, 0);
    }
    else
    {
        FUN_00415d70(1, 0);
    }
    if (param_1 == (undefined4 *)0x0)
    {
        local_1c = (undefined4 *)0x0;
    }
    else
    {
        local_1c = param_1 + 1;
    }
    FUN_0065fee0(local_1c);
    ExceptionList = local_10;
    return param_1;
}
