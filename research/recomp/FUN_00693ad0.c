// ============================================
// Address:  0x00693ad0
// Original: FUN_00693ad0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00693ad0(undefined4 param_1)

{
    undefined4 uVar1;
    int iVar2;
    int local_8;

    local_8 = FUN_006936a0(param_1);
    while (true)
    {
        if (local_8 == 0)
        {
            return 1;
        }
        uVar1 = FUN_00693720(local_8);
        iVar2 = FUN_00693990(uVar1);
        if (iVar2 == 0)
            break;
        local_8 = FUN_00694240(local_8);
    }
    return 0;
}
