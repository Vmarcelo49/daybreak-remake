// ============================================
// Address:  0x0041a1c0
// Original: FUN_0041a1c0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0041a1c0(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069dfaa;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a2074;
    param_1[1]    = &PTR_FUN_006a2068;
    local_8       = 0;
    FUN_00656200(param_1[0x175]);
    FUN_00656200(param_1[0x177]);
    FUN_00656200(param_1[0x178]);
    FUN_0065f780(0);
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
