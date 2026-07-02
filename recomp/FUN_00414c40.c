// ============================================
// Address:  0x00414c40
// Original: FUN_00414c40
// Status:   unreviewed
// ============================================

void __fastcall FUN_00414c40(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    int local_8;

    puStack_c     = &LAB_0069de38;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a1e60;
    param_1[1]    = &PTR_FUN_006a1e4c;
    local_8       = 2;
    FUN_0065fee0(0);
    FUN_00656200(param_1[0x195]);
    FUN_00656200(param_1[0x197]);
    FUN_00656200(param_1[0x198]);
    FUN_00656200(param_1[0x199]);
    local_8._0_1_ = 1;
    FUN_0065d640();
    local_8 = (uint)local_8._1_3_ << 8;
    if (param_1 == (undefined4 *)0x0)
    {
        param_1 = (undefined4 *)0x0;
    }
    else
    {
        param_1 = param_1 + 1;
    }
    FUN_00415e30(param_1);
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
