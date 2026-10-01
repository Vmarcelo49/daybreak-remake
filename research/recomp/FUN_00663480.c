// ============================================
// Address:  0x00663480
// Original: FUN_00663480
// Status:   unreviewed
// ============================================

undefined4 *FUN_00663480(undefined4 *param_1, undefined4 param_2)

{
    char cVar1;
    undefined4 uVar2;
    undefined4 *local_1c;
    undefined1 local_14[4];
    undefined1 local_10[8];
    undefined4 local_8;

    FUN_006635e0(&local_8, param_2);
    uVar2 = FUN_00654620(local_10);
    cVar1 = const_iterator__operator__(uVar2);
    if (cVar1 == '\0')
    {
        uVar2 = FUN_0068de10();
        uVar2 = FUN_00663570(uVar2);
        cVar1 = FUN_00663c00(param_2, uVar2);
        if (cVar1 == '\0')
        {
            local_1c = &local_8;
            goto LAB_006634f1;
        }
    }
    local_1c = (undefined4 *)FUN_00654620(local_14);
LAB_006634f1:
    *param_1 = *local_1c;
    return param_1;
}
