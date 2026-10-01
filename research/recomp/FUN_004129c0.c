// ============================================
// Address:  0x004129c0
// Original: FUN_004129c0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004129c0(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069ddbb;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a1dc4;
    local_8       = 0;
    FUN_00656200(param_1[0x413]);
    FUN_00656200(param_1[0x414]);
    FUN_00656200(param_1[0x415]);
    FUN_00656200(param_1[0x416]);
    FUN_00656200(param_1[0x417]);
    FUN_00656200(param_1[0x418]);
    FUN_00656200(param_1[0x419]);
    FUN_00656200(param_1[0x41a]);
    FUN_00656200(param_1[0x41b]);
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
