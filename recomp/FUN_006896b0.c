// ============================================
// Address:  0x006896b0
// Original: FUN_006896b0
// Status:   unreviewed
// ============================================

int __thiscall FUN_006896b0(int param_1, int *param_2, int param_3)

{
    int iVar1;
    int local_14;
    uint local_10;
    int *local_c;
    int local_8;

    local_c = (int *)0x0;
    if ((param_3 == 0) || (iVar1 = FUN_00686d80(), iVar1 != 0))
    {
        local_8 = -0x7ffbfdf9;
        for (local_10 = 0; (int)local_10 < 2; local_10 = local_10 + 1)
        {
            if (local_10 == *(byte *)(param_1 + 0x26))
            {
                local_14 = (**(code **)(*param_2 + 0x30))(param_2, &local_c);
            }
            else
            {
                local_14 = (**(code **)(*(int *)(param_1 + 0xc) + 0x30))(param_1 + 0xc, &local_c);
            }
            if (-1 < local_14)
            {
                iVar1 = FUN_006895c0(param_2, param_3, local_c);
                (**(code **)(*local_c + 8))(local_c);
                if (-1 < iVar1)
                {
                    return 0;
                }
                if (((iVar1 != -0x7fffbffb) && (iVar1 != -0x7ff8ffa9)) && (iVar1 != -0x7ffbfdd6))
                {
                    local_8 = iVar1;
                }
            }
        }
    }
    else
    {
        local_8 = FUN_00689470(param_2, param_3);
    }
    return local_8;
}
