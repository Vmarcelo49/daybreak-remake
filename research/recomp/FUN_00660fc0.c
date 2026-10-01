// ============================================
// Address:  0x00660fc0
// Original: FUN_00660fc0
// Status:   unreviewed
// ============================================

void __thiscall FUN_00660fc0(int param_1, int param_2)

{
    char cVar1;

    if (param_2 < 0)
    {
        if (*(int *)(param_1 + 0xa10) < 2)
        {
            *(undefined4 *)(param_1 + 0xa10) = 0;
        }
        else
        {
            cVar1 = FUN_00661620(*(undefined1 *)(param_1 + 6 + *(int *)(param_1 + 0xa10)));
            if (cVar1 == '\0')
            {
                *(int *)(param_1 + 0xa10) = *(int *)(param_1 + 0xa10) + -1;
            }
            else
            {
                *(int *)(param_1 + 0xa10) = *(int *)(param_1 + 0xa10) + -2;
            }
        }
    }
    else if ((0 < param_2) && (*(char *)(param_1 + 8 + *(int *)(param_1 + 0xa10)) != '\0'))
    {
        if (0x3fd < *(int *)(param_1 + 0xa10))
        {
            *(undefined4 *)(param_1 + 0xa10) = 0x3ff;
        }
        cVar1 = FUN_00661620(*(undefined1 *)(param_1 + 8 + *(int *)(param_1 + 0xa10)));
        if (cVar1 == '\0')
        {
            *(int *)(param_1 + 0xa10) = *(int *)(param_1 + 0xa10) + 1;
        }
        else
        {
            *(int *)(param_1 + 0xa10) = *(int *)(param_1 + 0xa10) + 2;
        }
        if (*(int *)(param_1 + 0xa08) < *(int *)(param_1 + 0xa10))
        {
            *(undefined4 *)(param_1 + 0xa10) = *(undefined4 *)(param_1 + 0xa08);
        }
    }
    return;
}
