// ============================================
// Address:  0x00401a60
// Original: FUN_00401a60
// Status:   unreviewed
// ============================================

void FUN_00401a60(char *param_1, undefined4 param_2, int param_3)

{
    int iVar1;
    undefined4 *local_14;
    undefined4 *local_10;
    undefined4 *local_8;

    for (local_8 = *(undefined4 **)(param_3 + 0x44); local_8 != (undefined4 *)0x0;
         local_8 = (undefined4 *)local_8[8])
    {
        iVar1 = _strcmp(param_1, (char *)*local_8);
        if (iVar1 == 0)
        {
            if (local_8 == (undefined4 *)0x0)
            {
                local_10 = (undefined4 *)0x0;
            }
            else
            {
                local_10 = local_8 + -1;
            }
            local_10[0x12] = param_2;
        }
        else
        {
            if (local_8 == (undefined4 *)0x0)
            {
                local_14 = (undefined4 *)0x0;
            }
            else
            {
                local_14 = local_8 + -1;
            }
            local_14[0x12] = 0;
        }
    }
    if (*(int *)(param_3 + 0x48) != 0)
    {
        FUN_00401a60(param_1, param_2, *(undefined4 *)(param_3 + 0x48));
    }
    if (*(int *)(param_3 + 0x4c) != 0)
    {
        FUN_00401a60(param_1, param_2, *(undefined4 *)(param_3 + 0x4c));
    }
    return;
}
