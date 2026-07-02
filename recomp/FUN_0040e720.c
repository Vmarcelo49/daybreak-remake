// ============================================
// Address:  0x0040e720
// Original: FUN_0040e720
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_0040e720(undefined4 *param_1)

{
    undefined4 *puVar1;
    HANDLE pvVar2;
    undefined4 local_28;
    undefined1 local_20[4];
    void *local_1c;
    undefined4 local_18;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069dc71;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00403a50();
    local_8  = 0;
    *param_1 = &PTR_FUN_006a1b70;
    FUN_0065d610();
    local_8._0_1_ = 1;
    FUN_0040fa90();
    local_8._0_1_ = 2;
    FUN_00425ac0();
    FUN_00425ac0();
    FUN_00425ac0();
    FUN_00425ac0();
    _vector_constructor_iterator_(param_1 + 0x15, 4, 6, FUN_00425ac0);
    FUN_00403a70();
    FUN_00403a70();
    FUN_00403a70();
    FUN_00403a70();
    _vector_constructor_iterator_(param_1 + 0xbb, 0xa0, 6, FUN_00403a70);
    _eh_vector_constructor_iterator_(param_1 + 0x1b1, 0x14, 6, FUN_004248f0, FUN_0040fc10);
    local_8._0_1_ = 3;
    local_1c      = operator_new(0x148);
    local_8._0_1_ = 4;
    if (local_1c == (void *)0x0)
    {
        local_28 = 0;
    }
    else
    {
        local_28 = FUN_0065d6f0(DAT_006d1850);
    }
    local_18      = local_28;
    local_8       = CONCAT31(local_8._1_3_, 3);
    param_1[0x10] = local_28;
    FUN_0065d7e0(&DAT_006a1ae4, 0x18, 0xff, 0xff, 0xff);
    CPane::SetBorders((CPane *)param_1[0x10], 0x2f8, 5, 0, 10);
    FUN_00654170(0);
    puVar1        = (undefined4 *)FUN_006560c0(local_20, "data/talk/window.bmp");
    param_1[0x14] = *puVar1;
    FUN_00655af0(param_1[0x14], 0, 0, 0x30c, 0x96);
    FUN_00655af0(param_1[0x14], 0, 0xa0, 0x40, 0x20);
    param_1[0x1d7] = 0;
    for (local_14 = 0; local_14 < 6; local_14 = local_14 + 1)
    {
        param_1[local_14 + 0x1d0] = local_14;
    }
    *(undefined1 *)((int)param_1 + 0x76b) = 0;
    *(undefined1 *)((int)param_1 + 0x769) = 0xff;
    *(undefined1 *)(param_1 + 0x1db)      = 0;
    *(undefined1 *)((int)param_1 + 0x76a) = 0;
    *(undefined1 *)(param_1 + 0x1d6)      = 0;
    param_1[0x21e]                        = 0x1e;
    pvVar2         = CreateEventA((LPSECURITY_ATTRIBUTES)0x0, 0, 0, (LPCSTR)0x0);
    param_1[0x1cf] = pvVar2;
    FUN_0040f970();
    ExceptionList = local_10;
    return param_1;
}
