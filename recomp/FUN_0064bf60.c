// ============================================
// Address:  0x0064bf60
// Original: FUN_0064bf60
// Status:   unreviewed
// ============================================

void __fastcall FUN_0064bf60(int param_1)

{
    int local_8;

    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
    {
        if (-1 < *(int *)(param_1 + 0x52f8 + local_8 * 4))
        {
            switch (local_8)
            {
            case 0:
                FUN_0064cee0(*(undefined4 *)(param_1 + 0x52f8 + local_8 * 4), 0xffffc8c8);
                break;
            case 1:
                FUN_0064cee0(*(undefined4 *)(param_1 + 0x52f8 + local_8 * 4), 0xffc8c8ff);
                break;
            case 2:
                FUN_0064cee0(*(undefined4 *)(param_1 + 0x52f8 + local_8 * 4), 0xffc8ffc8);
                break;
            case 3:
                FUN_0064cee0(*(undefined4 *)(param_1 + 0x52f8 + local_8 * 4), 0xffffffc8);
            }
        }
    }
    return;
}
