// ============================================
// Address:  0x00634f60
// Original: FUN_00634f60
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00634f60(int param_1)

{
    undefined4 uVar1;
    char cVar2;
    undefined4 uVar3;
    int local_54;
    int local_50;
    int local_4c;
    int local_48;
    int local_44;
    int local_40;
    int local_3c;
    int local_38;
    int local_34;
    int local_30;
    int local_2c;
    int local_28;
    int local_1c;
    int local_18;
    int local_10;
    int local_c;
    char local_5;

    FUN_006585f0();
    FUN_006584e0();
    FUN_00634ca0();
    for (local_c = 0; local_c < 4; local_c = local_c + 1)
    {
        FUN_0041efe0();
        if ((DAT_006cfdb0 == '\0') && (*(int *)(param_1 + 0x4a3c) == 2))
        {
            if (*(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0x29c) == 1)
            {
                FUN_0064aed0(0x11);
                *(char *)(param_1 + 0x4430) = '\x01' - (*(char *)(param_1 + 0x4430) != '\0');
            }
            if (*(char *)(param_1 + 0x4430) != '\0')
            {
                for (local_10 = 0; local_10 < 7; local_10 = local_10 + 1)
                {
                    if (*(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0x280 + local_10 * 4) ==
                        1)
                    {
                        *(char *)(param_1 + 0x4431) =
                            '\x01' - (*(char *)(param_1 + 0x4431) != '\0');
                    }
                }
            }
        }
    }
    cVar2 = FUN_006586d0(1);
    if ((cVar2 != '\0') && (DAT_006cfce9 == '\0'))
    {
        *(undefined1 *)(param_1 + 0x4a40) = 1;
    }
    if (*(char *)(param_1 + 0x4430) == '\0')
    {
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
        if (*(int *)(param_1 + 0x4a3c) != 2)
        {
            switch (*(undefined4 *)(param_1 + 0x4a3c))
            {
            case 1:
                for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1)
                {
                    if (*(char *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x860) == '\0')
                    {
                        uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x28c);
                        uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x298);
                        _memset(
                            (void *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x278), 0, 0x28);
                        *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x28c) = uVar3;
                        *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x298) = uVar1;
                    }
                    else
                    {
                        _memset(
                            (void *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x278), 0, 0x28);
                    }
                    _memset((void *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x2b0), 0, 0x10);
                    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x830) = 0;
                }
                break;
            case 3:
                for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1)
                {
                    if (local_28 != *(int *)(param_1 + 0x4428))
                    {
                        _memset(
                            (void *)(*(int *)(param_1 + 0x129c + local_28 * 4) + 0x278), 0, 0x28);
                        _memset(
                            (void *)(*(int *)(param_1 + 0x129c + local_28 * 4) + 0x2b0), 0, 0x10);
                        *(undefined4 *)(*(int *)(param_1 + 0x129c + local_28 * 4) + 0x830) = 0;
                    }
                }
                break;
            case 4:
            case 5:
                for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1)
                {
                    _memset((void *)(*(int *)(param_1 + 0x129c + local_18 * 4) + 0x278), 0, 0x28);
                    _memset((void *)(*(int *)(param_1 + 0x129c + local_18 * 4) + 0x2b0), 0, 0x10);
                    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_18 * 4) + 0x830) = 0;
                }
            }
        }
        local_5 = -1;
        for (local_2c = 0; local_2c < 4; local_2c = local_2c + 1)
        {
            if (*(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x828) != 0)
            {
                local_5 = (char)local_2c;
            }
        }
        if (local_5 < '\0')
        {
            for (local_38 = 0; local_38 < 4; local_38 = local_38 + 1)
            {
                (**(code **)(**(int **)(param_1 + 0x129c + local_38 * 4) + 0x1c))();
            }
            for (local_3c = 0; local_3c < 4; local_3c = local_3c + 1)
            {
                (**(code **)(**(int **)(param_1 + 0x129c + local_3c * 4) + 0x18))();
            }
            for (local_40 = 0; local_40 < 4; local_40 = local_40 + 1)
            {
                FUN_00420850();
            }
            for (local_44 = 0; local_44 < 4; local_44 = local_44 + 1)
            {
                FUN_0042e110();
                (**(code **)(**(int **)(param_1 + 0x129c + local_44 * 4) + 0x24))();
            }
            FUN_00635d40();
            for (local_48 = 0; local_48 < 4; local_48 = local_48 + 1)
            {
                FUN_0041f580();
            }
            for (local_4c = 0; local_4c < 4; local_4c = local_4c + 1)
            {
                FUN_004201a0();
            }
            FUN_006430f0();
            for (local_50 = 0; local_50 < 4; local_50 = local_50 + 1)
            {
                Concurrency::details::CollectionTypes::Count::Increment(
                    (Count *)(param_1 + 0x140c + local_50 * 0xb74));
            }
            FUN_006358c0((int)local_5);
            FUN_00637680();
            FUN_00435a20();
            FUN_00401b30();
        }
        else
        {
            (**(code **)(**(int **)(param_1 + 0x129c + local_5 * 4) + 0x1c))();
            (**(code **)(**(int **)(param_1 + 0x129c + local_5 * 4) + 0x18))();
            FUN_0042e110();
            (**(code **)(**(int **)(param_1 + 0x129c + local_5 * 4) + 0x24))();
            FUN_00635d40();
            FUN_0041f580();
            for (local_30 = 0; local_30 < 4; local_30 = local_30 + 1)
            {
                FUN_004201a0();
            }
            FUN_006430f0();
            for (local_34 = 0; local_34 < 4; local_34 = local_34 + 1)
            {
                Concurrency::details::CollectionTypes::Count::Increment(
                    (Count *)(param_1 + 0x140c + local_34 * 0xb74));
            }
            FUN_006358c0((int)local_5);
            FUN_00637680();
            FUN_00435a20();
        }
        if (DAT_006cfce9 == '\0')
        {
            cVar2 = FUN_006586d0(0x3c);
            if (cVar2 != '\0')
            {
                *(undefined1 *)(*(int *)(param_1 + 0x129c) + 0x860) = 0;
                *(undefined1 *)(*(int *)(param_1 + 0x12a0) + 0x860) = 0;
                *(undefined1 *)(*(int *)(param_1 + 0x12a4) + 0x860) = 0;
                *(undefined1 *)(*(int *)(param_1 + 0x12a8) + 0x860) = 0;
            }
            cVar2 = FUN_006586d0(0x3d);
            if (cVar2 != '\0')
            {
                if (3 < DAT_006cfaf8)
                {
                    *(undefined1 *)(*(int *)(param_1 + 0x129c) + 0x860) = 1;
                }
                if (3 < DAT_006cfafc)
                {
                    *(undefined1 *)(*(int *)(param_1 + 0x12a0) + 0x860) = 1;
                }
                if (3 < DAT_006cfb00)
                {
                    *(undefined1 *)(*(int *)(param_1 + 0x12a4) + 0x860) = 1;
                }
                if (3 < DAT_006cfb04)
                {
                    *(undefined1 *)(*(int *)(param_1 + 0x12a8) + 0x860) = 1;
                }
            }
            cVar2 = FUN_006586d0(0x3b);
            if (cVar2 != '\0')
            {
                *(undefined4 *)(param_1 + 0x12b0)                   = 0;
                *(undefined4 *)(param_1 + 0x12bc)                   = 0;
                *(undefined4 *)(*(int *)(param_1 + 0x129c) + 0x7a8) = 10000;
                *(undefined4 *)(*(int *)(param_1 + 0x129c) + 0x7a4) = 10000;
                *(undefined4 *)(*(int *)(param_1 + 0x12a0) + 0x7a8) = 10000;
                *(undefined4 *)(*(int *)(param_1 + 0x12a0) + 0x7a4) = 10000;
                *(undefined4 *)(*(int *)(param_1 + 0x12a4) + 0x7a8) = 10000;
                *(undefined4 *)(*(int *)(param_1 + 0x12a4) + 0x7a4) = 10000;
                *(undefined4 *)(*(int *)(param_1 + 0x12a8) + 0x7a8) = 10000;
                *(undefined4 *)(*(int *)(param_1 + 0x12a8) + 0x7a4) = 10000;
            }
            cVar2 = FUN_006586d0(0x3e);
            if (cVar2 != '\0')
            {
                for (local_54 = 0; local_54 < 4; local_54 = local_54 + 1)
                {
                    if (*(char *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x318) == '\x01')
                    {
                        *(undefined4 *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x83c) =
                            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x32c);
                    }
                    else if (*(char *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x318) == '\x02')
                    {
                        *(undefined4 *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x840) =
                            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x324);
                    }
                    else
                    {
                        *(undefined4 *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x838) =
                            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_54 * 4) + 0x324);
                    }
                }
            }
        }
        uVar3 = *(undefined4 *)(param_1 + 0x4a3c);
    }
    else
    {
        uVar3 = *(undefined4 *)(param_1 + 0x4a3c);
    }
    return uVar3;
}
