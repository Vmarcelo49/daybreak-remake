// ============================================
// Address:  0x00645b90
// Original: FUN_00645b90
// Status:   unreviewed
// ============================================

void __fastcall FUN_00645b90(int param_1)

{
    int local_8;

    FUN_00645df0();
    FUN_0065d670();
    FUN_00656200(*(undefined4 *)(param_1 + 0x100));
    FUN_00654170(0);
    FUN_00656200(*(undefined4 *)(param_1 + 0x134));
    FUN_00654170(0);
    FUN_00656200(*(undefined4 *)(param_1 + 0x138));
    FUN_00654170(0);
    FUN_00656200(*(undefined4 *)(param_1 + 0x104));
    FUN_00654170(0);
    FUN_00656200(*(undefined4 *)(param_1 + 0x108));
    FUN_00654170(0);
    FUN_00656200(*(undefined4 *)(param_1 + 0x10c));
    FUN_00654170(0);
    FUN_00656200(*(undefined4 *)(param_1 + 0x110));
    FUN_00654170(0);
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        FUN_00656200(*(undefined4 *)(param_1 + 0x114 + local_8 * 4));
        FUN_00654170(0);
    }
    FUN_00656200(*(undefined4 *)(param_1 + 0x13c));
    FUN_00654170(0);
    if (*(int *)(param_1 + 0x140) != 0)
    {
        if (*(int *)(param_1 + 0x140) != 0)
        {
            FUN_0040fb10(1);
        }
        *(undefined4 *)(param_1 + 0x140) = 0;
    }
    if (*(int *)(param_1 + 0x144) != 0)
    {
        if (*(int *)(param_1 + 0x144) != 0)
        {
            FUN_0040fb10(1);
        }
        *(undefined4 *)(param_1 + 0x144) = 0;
    }
    FUN_0065d6a0();
    FUN_00646ec0(0);
    return;
}
