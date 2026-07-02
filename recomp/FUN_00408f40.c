// ============================================
// Address:  0x00408f40
// Original: FUN_00408f40
// Status:   unreviewed
// ============================================

void __fastcall FUN_00408f40(undefined4 *param_1)

{
    int local_20;
    int local_1c;
    int local_18;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069dbba;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a1974;
    local_8       = 0;
    for (local_14 = 0; local_14 < 3; local_14 = local_14 + 1)
    {
        FUN_00656200(param_1[local_14 + 8]);
    }
    for (local_18 = 0; local_18 < 7; local_18 = local_18 + 1)
    {
        FUN_00656200(param_1[local_18 + 1]);
    }
    for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1)
    {
        FUN_00656200(param_1[local_1c + 0xb]);
        FUN_00656200(param_1[local_1c + 0xf]);
    }
    for (local_20 = 0; local_20 < 0x10; local_20 = local_20 + 1)
    {
        FUN_00656200(param_1[local_20 + 0x33]);
        FUN_00656200(param_1[local_20 + 0x13]);
        FUN_00656200(param_1[local_20 + 0x23]);
    }
    FUN_0065b1d0(param_1[0xf0e]);
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
