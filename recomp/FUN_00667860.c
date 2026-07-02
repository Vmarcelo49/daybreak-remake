// ============================================
// Address:  0x00667860
// Original: FUN_00667860
// Status:   unreviewed
// ============================================

int __thiscall FUN_00667860(int param_1, int param_2)

{
    uint local_14;
    int local_10;
    uint local_c;
    void *local_8;

    local_8 = (void *)0x0;
    local_c = 0;
    (**(code **)(**(int **)(param_1 + 4) + 0x24))(*(undefined4 *)(param_1 + 4), &local_14);
    if ((local_14 & 1) != 0)
    {
        (**(code **)(**(int **)(param_1 + 4) + 0x48))(*(undefined4 *)(param_1 + 4));
    }
    (**(code **)(**(int **)(param_1 + 4) + 0x34))(*(undefined4 *)(param_1 + 4), 0);
    local_10 = (**(code **)(**(int **)(param_1 + 4) + 0x2c))(
        *(undefined4 *)(param_1 + 4), 0, 0, &local_8, &local_c, 0, 0, 2);
    if (-1 < local_10)
    {
        if (*(uint *)(param_2 + 0x18) < local_c)
        {
            _memset((void *)((int)local_8 + *(int *)(param_2 + 0x18)),
                    0,
                    local_c - *(int *)(param_2 + 0x18));
            _memcpy(local_8, *(void **)(param_2 + 0x14), *(size_t *)(param_2 + 0x18));
        }
        else
        {
            _memcpy(local_8, *(void **)(param_2 + 0x14), local_c);
        }
        (**(code **)(**(int **)(param_1 + 4) + 0x4c))(
            *(undefined4 *)(param_1 + 4), local_8, local_c, 0, 0);
    }
    return param_1;
}
