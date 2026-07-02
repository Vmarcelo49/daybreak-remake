// ============================================
// Address:  0x00417a70
// Original: FUN_00417a70
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_00417a70(undefined4 *param_1)

{
    undefined4 *local_18;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069ded6;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00408330();
    local_8 = 0;
    FUN_00415dc0();
    local_8        = CONCAT31(local_8._1_3_, 1);
    *param_1       = &PTR_FUN_006a1f88;
    param_1[0xf66] = &PTR_FUN_006a1f74;
    FUN_00418c10();
    FUN_00418f70();
    _vector_constructor_iterator_(param_1 + 0xfff, 0x14, 4, FUN_00419170);
    FUN_00417750();
    FUN_00419240();
    param_1[0x101d] = 0;
    param_1[0x101c] = 0;
    FUN_00415da0();
    if (param_1 == (undefined4 *)0x0)
    {
        local_18 = (undefined4 *)0x0;
    }
    else
    {
        local_18 = param_1 + 0xf66;
    }
    FUN_0065fee0(local_18);
    ExceptionList = local_10;
    return param_1;
}
