// ============================================
// Address:  0x00696ac0
// Original: FUN_00696ac0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00696ac0(int *param_1)

{
    short sVar1;
    uint local_8;

    for (local_8 = 0; local_8 < (uint)param_1[2]; local_8 = local_8 + 1)
    {
        sVar1 = *(short *)(*param_1 + local_8 * 0x10);
        if (sVar1 == 8)
        {
            if (*(int *)(*param_1 + 8 + local_8 * 0x10) != 0)
            {
                _free((void *)(*(int *)(*param_1 + 8 + local_8 * 0x10) + -2));
            }
        }
        else if (sVar1 == 9)
        {
            (**(code **)(**(int **)(*param_1 + 8 + local_8 * 0x10) + 8))(
                *(undefined4 *)(*param_1 + 8 + local_8 * 0x10));
        }
        else if (sVar1 == 0xd)
        {
            (**(code **)(**(int **)(*param_1 + 8 + local_8 * 0x10) + 8))(
                *(undefined4 *)(*param_1 + 8 + local_8 * 0x10));
        }
    }
    _free((void *)*param_1);
    return;
}
