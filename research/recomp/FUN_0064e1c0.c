// ============================================
// Address:  0x0064e1c0
// Original: FUN_0064e1c0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_0064e1c0(int param_1, int param_2)

{
    uint uVar1;
    void *pvVar2;
    undefined4 uVar3;
    int local_2c;
    int local_24;
    uint local_10;

    if (param_2 == 0)
    {
        local_24 = 0;
    }
    else
    {
        local_24 = param_2 + -4;
    }
    if (*(int *)(local_24 + 0x20) != 0)
    {
        uVar1 = (**(code **)(**(int **)(local_24 + 0x20) + 0x24))(*(undefined4 *)(local_24 + 0x20));
        if (*(int *)(local_24 + 0x40) != 0)
        {
            _free(*(void **)(local_24 + 0x40));
            *(undefined4 *)(local_24 + 0x40) = 0;
        }
        pvVar2                      = operator_new(uVar1 << 2);
        *(void **)(local_24 + 0x40) = pvVar2;
        if (*(int *)(local_24 + 0x40) == 0)
        {
            return 0;
        }
        for (local_10 = 0; local_10 < uVar1; local_10 = local_10 + 1)
        {
            uVar3 = (**(code **)(**(int **)(local_24 + 0x20) + 0x3c))(
                *(undefined4 *)(local_24 + 0x20), local_10);
            local_2c = D3DXFrameFind(*(undefined4 *)(param_1 + 8), uVar3);
            if (local_2c == 0)
            {
                local_2c = 0;
            }
            else
            {
                local_2c = local_2c + -0x10;
            }
            if (local_2c == 0)
            {
                return 0;
            }
            *(int *)(*(int *)(local_24 + 0x40) + local_10 * 4) = local_2c + 0x60;
        }
    }
    return 1;
}
