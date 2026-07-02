// ============================================
// Address:  0x00417b80
// Original: FUN_00417b80
// Status:   unreviewed
// ============================================

void __fastcall FUN_00417b80(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    uint local_8;

    puStack_c      = &LAB_0069df11;
    local_10       = ExceptionList;
    ExceptionList  = &local_10;
    *param_1       = &PTR_FUN_006a1f88;
    param_1[0xf66] = &PTR_FUN_006a1f74;
    local_8        = 1;
    FUN_00645df0();
    FUN_0065fee0(0);
    local_8 = local_8 & 0xffffff00;
    if (param_1 == (undefined4 *)0x0)
    {
        param_1 = (undefined4 *)0x0;
    }
    else
    {
        param_1 = param_1 + 0xf66;
    }
    FUN_00415e30(param_1);
    local_8 = 0xffffffff;
    FUN_00408f40();
    ExceptionList = local_10;
    return;
}
