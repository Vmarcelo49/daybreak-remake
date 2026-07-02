// ============================================
// Address:  0x0064f080
// Original: FUN_0064f080
// Status:   unreviewed
// ============================================

undefined4 FUN_0064f080(undefined4 param_1, undefined4 param_2, undefined4 param_3)

{
    int iVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 extraout_var;
    undefined1 local_10[4];
    undefined1 local_c[4];
    undefined4 local_8;

    iVar1 = FUN_0064f010();
    uVar3 = extraout_var;
    if (iVar1 == 0)
    {
        local_8 = 0;
    }
    else
    {
        uVar2   = FUN_00654620(local_c);
        local_8 = FUN_0064fa40(uVar2);
    }
    FUN_0064f3a0(param_2, 1, param_3, local_8, uVar3);
    uVar3 = param_1;
    uVar2 = local_8;
    FUN_00654620(local_10);
    iterator__operator_(uVar3, uVar2);
    return param_1;
}
