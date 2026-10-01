// ============================================
// Address:  0x00639160
// Original: FUN_00639160
// Status:   unreviewed
// ============================================

short __thiscall
FUN_00639160(int param_1, int param_2, int param_3, short param_4, short param_5, char param_6)

{
    undefined1 local_24[8];
    undefined1 local_1c;
    undefined1 local_1b;
    int local_18;
    int local_14;
    int local_10;
    undefined1 local_9;
    int local_8;

    local_9 = 0 < *(int *)(param_2 + 0x7a4);
    local_14 =
        ((((((int)param_4 * *(int *)(param_3 + 0x7c8)) / 100) * *(int *)(param_2 + 0x7cc)) / 100) *
         100) /
        *(int *)(param_1 + 0x43cc);
    *(int *)(param_2 + 0x7a4) = *(int *)(param_2 + 0x7a4) - local_14;
    local_8                   = 0;
    if (*(int *)(param_2 + 0x7a4) < 0)
    {
        local_8 = -*(int *)(param_2 + 0x7a4);
    }
    if (param_2 == *(int *)(param_3 + 0x308))
    {
        *(int *)(param_2 + 0xaef4) = (local_14 - local_8) + *(int *)(param_2 + 0xaef4);
        *(int *)(param_2 + 0xaf28) = *(int *)(param_2 + 0xaf28) + 1;
        *(int *)(param_3 + 0xaeec) = (local_14 - local_8) + *(int *)(param_3 + 0xaeec);
        *(int *)(param_3 + 0xaf1c) = *(int *)(param_3 + 0xaf1c) + 1;
    }
    else
    {
        *(int *)(param_2 + 0xaef8) = (local_14 - local_8) + *(int *)(param_2 + 0xaef8);
        *(int *)(param_2 + 0xaf2c) = *(int *)(param_2 + 0xaf2c) + 1;
        *(int *)(param_3 + 0xaef0) = (local_14 - local_8) + *(int *)(param_3 + 0xaef0);
        *(int *)(param_3 + 0xaf20) = *(int *)(param_3 + 0xaf20) + 1;
    }
    if (*(int *)(param_2 + 0x7a4) < 1)
    {
        if (param_6 == '\0')
        {
            local_10 = 0;
            if (((*(int *)(param_2 + 0xadec) != 0xc6) && (*(int *)(param_2 + 0xadec) != 199)) &&
                ((param_5 == 0xc6 || (param_5 == 199))))
            {
                local_10 = 1;
            }
            if ((((*(char *)(param_2 + 0x318) == '\x02') && (*(char *)(param_2 + 0x846) == '\0')) &&
                 (*(int *)(param_2 + 0x7a4) < 1)) &&
                (((bool)local_9 && (*(int *)(param_2 + 0x324) <= *(int *)(param_2 + 0x840)))))
            {
                *(undefined4 *)(param_2 + 0x7a4) = 1;
                param_5                          = 0x1f7;
            }
            else
            {
                if ((bool)local_9)
                {
                    local_18 = -*(int *)(param_2 + 0x7a4) / 1000;
                    FUN_00639650(**(undefined4 **)(param_2 + 0xc), local_18 + 0x14 + local_10);
                    FUN_0064aed0(9);
                    FUN_00421960();
                    if (*(int *)(param_1 + 0x4a3c) == 2)
                    {
                        *(undefined1 *)(param_3 + 0xaec9) = 1;
                        *(undefined1 *)(param_3 + 0xaeb8) = 1;
                        *(undefined4 *)(param_1 + 0x4428) = *(undefined4 *)(param_3 + 8);
                        *(int *)(param_3 + 0xaf34)        = *(int *)(param_3 + 0xaf34) + 1;
                        *(int *)(param_2 + 0xaf3c)        = *(int *)(param_2 + 0xaf3c) + 1;
                        if (DAT_006cfdb0 == '\x01')
                        {
                            FUN_0063be00();
                            local_1c = *(undefined1 *)(param_3 + 8);
                            local_1b = *(undefined1 *)(param_2 + 8);
                            FUN_00415d30(0, local_24, 0, 8);
                        }
                    }
                    *(undefined4 *)(param_2 + 0x7b8) = 0;
                }
                if (*(int *)(param_1 + 0x4a3c) == 2)
                {
                    *(undefined4 *)(param_2 + 0x7a4) = 0;
                }
                else
                {
                    *(undefined4 *)(param_2 + 0x7a4) = 1;
                }
            }
        }
        else
        {
            if ((bool)local_9)
            {
                *(undefined4 *)(param_2 + 0x7a4) = 1;
            }
            param_5 = -1;
        }
    }
    else
    {
        param_5 = -1;
    }
    return param_5;
}
