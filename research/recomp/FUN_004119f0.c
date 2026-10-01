// ============================================
// Address:  0x004119f0
// Original: FUN_004119f0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004119f0(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069dd7d;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006a1c68;
    local_8       = 0;
    FUN_00656200(param_1[0x169]);
    FUN_00656200(param_1[0x16a]);
    FUN_00656200(param_1[0x16b]);
    FUN_00656200(param_1[0x16c]);
    FUN_00656200(param_1[0x16d]);
    FUN_00656200(param_1[0x16e]);
    FUN_00656200(param_1[0x16f]);
    FUN_00656200(param_1[0x170]);
    local_8 = 0xffffffff;
    FUN_004039d0();
    ExceptionList = local_10;
    return;
}
