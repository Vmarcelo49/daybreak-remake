// ============================================
// Address:  0x0068d590
// Original: FUN_0068d590
// Status:   unreviewed
// ============================================

void __fastcall FUN_0068d590(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069f808;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    *param_1      = &PTR_FUN_006ad404;
    param_1[3]    = &PTR_FUN_006ad3d8;
    local_8       = 0;
    FUN_0068ce70(param_1 + 3);
    FUN_0068d500();
    local_8 = 0xffffffff;
    FUN_0068c680();
    ExceptionList = local_10;
    return;
}
