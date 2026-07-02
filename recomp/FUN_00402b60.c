// ============================================
// Address:  0x00402b60
// Original: FUN_00402b60
// Status:   unreviewed
// ============================================

void __fastcall FUN_00402b60(undefined4 *param_1)

{
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069da4d;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a13fc;
    local_8       = 0;
    for (local_14 = 0; local_14 < 3; local_14 = local_14 + 1)
    {
        FUN_00656200(param_1[local_14 + 0xf1]);
    }
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
