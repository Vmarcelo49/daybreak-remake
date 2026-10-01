// ============================================
// Address:  0x0068a110
// Original: FUN_0068a110
// Status:   unreviewed
// ============================================

int __thiscall FUN_0068a110(int *param_1, int *param_2, int *param_3)

{
    undefined1 local_18[8];
    int local_10;
    int local_8;

    local_8  = 0;
    *param_3 = 0;
    _memset(local_18, 0, 0x10);
    (**(code **)(*param_2 + 0x14))(param_2, local_18);
    if (local_10 == 0)
    {
        local_10 = 1;
    }
    local_8 = (**(code **)(*param_2 + 0xc))(param_2, param_3);
    if (((local_8 < 0) ||
         (local_8 = (**(code **)(*param_1 + 0x3c))(*param_3, local_18), local_8 < 0)) ||
        (local_8 = (**(code **)(*param_2 + 0x10))(param_2, *param_3, 0), local_8 < 0))
    {
        if (*param_3 != 0)
        {
            (**(code **)(*(int *)*param_3 + 8))(*param_3);
            *param_3 = 0;
        }
        local_8 = (**(code **)(*param_1 + 0x48))(param_3);
        if (((local_8 < 0) ||
             (local_8 = (**(code **)(*param_1 + 0x3c))(*param_3, local_18), local_8 < 0)) ||
            (local_8 = (**(code **)(*param_2 + 0x10))(param_2, *param_3, 0), local_8 < 0))
        {
            if (*param_3 != 0)
            {
                (**(code **)(*(int *)*param_3 + 8))(*param_3);
                *param_3 = 0;
            }
        }
        else
        {
            local_8 = 0;
        }
    }
    else
    {
        local_8 = 0;
    }
    return local_8;
}
