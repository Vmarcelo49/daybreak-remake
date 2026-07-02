// ============================================
// Address:  0x0040e020
// Original: FUN_0040e020
// Status:   unreviewed
// ============================================

void __fastcall FUN_0040e020(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069dc1a;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a1ad4;
    local_8       = 0;
    FUN_00656200(param_1[1]);
    FUN_00656200(param_1[2]);
    FUN_00656200(param_1[3]);
    FUN_0065bea0();
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
