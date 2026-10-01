// ============================================
// Address:  0x006358c0
// Original: FUN_006358c0
// Status:   unreviewed
// ============================================

void __thiscall FUN_006358c0(int param_1, int param_2)

{
    int iVar1;
    int *piVar2;
    float10 fVar3;
    undefined4 uVar4;
    allocator<char> local_30[12];
    allocator<char> local_24[12];
    int local_18;
    int local_14;
    int local_10;
    int local_c;
    char local_5;

    FUN_0065d670();
    if (param_2 < 0)
    {
        for (local_c = 0; local_c < 4; local_c = local_c + 1)
        {
            FUN_004202b0();
            FUN_004348c0();
        }
    }
    else
    {
        FUN_004202b0();
    }
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1)
    {
        FUN_00420880();
    }
    FUN_006394c0();
    FUN_00435b20();
    local_5 = '\0';
    if ((**(int **)(param_1 + 19000) != 0) && (*(char *)(**(int **)(param_1 + 19000) + 1) != '\0'))
    {
        local_5 = '\x01';
    }
    for (local_14 = 0; iVar1 = DAT_006cfba4, local_14 < 4; local_14 = local_14 + 1)
    {
        local_18 = *(int *)(param_1 + 0x129c + local_14 * 4);
        if (*(char *)(local_18 + 0xaecc) != '\0')
        {
            local_18 = *(int *)(local_18 + 0xaed0);
        }
        if (local_5 == '\0')
        {
            if (*(char *)(local_18 + 0x2dc) == '\0')
            {
                if (*(int *)(local_18 + 0x304) < 0)
                {
                    uVar4  = 0;
                    piVar2 = (int *)FUN_00658a10(*(undefined4 *)(local_18 + 0x300));
                    FUN_00632e70(*piVar2 + 0x14, uVar4);
                }
                else
                {
                    uVar4  = 0;
                    piVar2 = (int *)FUN_00658a10(0);
                    FUN_00632e70(*piVar2 + 0x14, uVar4);
                }
                FUN_00632ed0(local_18 + 0x14, 0);
                if (*(int *)(local_18 + 0x684) < 0)
                {
                    FUN_006331e0();
                }
                else
                {
                    FUN_00633140(*(undefined4 *)(local_18 + 0x684),
                                 *(float *)(local_18 + 0x5c) + *(float *)(local_18 + 100));
                }
            }
            else
            {
                std::allocator<char>::allocator<char>(local_24);
                std::allocator<char>::allocator<char>(local_30);
                FUN_00422f90(local_24, local_30);
                FUN_0063b820();
                FUN_006330e0(local_30);
                FUN_00633110(local_24);
            }
        }
        else
        {
            FUN_00632e70(local_18 + 0x14, 0);
            FUN_00632ed0(**(int **)(param_1 + 19000) + 0x7c, 0);
        }
        FUN_00633220();
    }
    if (local_5 == '\0')
    {
        (**(code **)(*DAT_006d8428 + 0x38))(
            DAT_006d8428,
            *(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x14),
            *(float *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x18) + 150.0,
            *(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x1c),
            1);
        fVar3 = (float10)FUN_0065d010(
            *(undefined4 *)(*(int *)(param_1 + 0x129c + iVar1 * 4) + 0x5c), 0, 0x3f800000, 0, 1);
        fVar3 = (float10)FUN_0065d050(
            *(undefined4 *)(*(int *)(param_1 + 0x129c + iVar1 * 4) + 0x5c), 0, (float)fVar3);
        (**(code **)(*DAT_006d8428 + 0x34))(DAT_006d8428, (float)fVar3);
    }
    else
    {
        (**(code **)(*DAT_006d8428 + 0x38))(DAT_006d8428,
                                            *(undefined4 *)(**(int **)(param_1 + 19000) + 0x7c),
                                            *(float *)(**(int **)(param_1 + 19000) + 0x80) + 150.0,
                                            *(undefined4 *)(**(int **)(param_1 + 19000) + 0x84),
                                            1);
        fVar3 = (float10)FUN_0065d010(
            *(undefined4 *)(**(int **)(param_1 + 19000) + 0xc4), 0, 0x3f800000, 0, 1);
        fVar3 = (float10)FUN_0065d050(
            *(undefined4 *)(**(int **)(param_1 + 19000) + 0xc4), 0, (float)fVar3);
        (**(code **)(*DAT_006d8428 + 0x34))(DAT_006d8428, (float)fVar3);
    }
    (**(code **)(*DAT_006d8428 + 0x44))(DAT_006d8428);
    FUN_0065d6a0();
    return;
}
