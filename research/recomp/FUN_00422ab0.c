// ============================================
// Address:  0x00422ab0
// Original: FUN_00422ab0
// Status:   unreviewed
// ============================================

uint __thiscall FUN_00422ab0(uint param_1, short param_2, short param_3, char param_4, int param_5)

{
    int iVar1;
    undefined4 local_8;

    if (*(int *)(param_1 + 0xaed0) != 0)
    {
        if (param_5 != 0)
        {
            FUN_00423530(param_5);
        }
        *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b0) =
            *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b0) + 1;
        *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b4) =
            *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b4) + 1;
        if (param_4 == '\0')
        {
            local_8 = 100;
        }
        else
        {
            iVar1 = *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b0);
            if (iVar1 == 1)
            {
                local_8 = 100;
            }
            else if (iVar1 == 2)
            {
                local_8 = 0x46;
            }
            else if (iVar1 == 3)
            {
                local_8 = 0x32;
            }
            else
            {
                local_8 = 0x21;
            }
        }
        FUN_00639160(*(undefined4 *)(param_1 + 0xaed0), param_1, (param_3 * local_8) / 100, 0, 1);
        param_1 = FUN_00421080((int)param_2);
    }
    return param_1 & 0xffffff00;
}
