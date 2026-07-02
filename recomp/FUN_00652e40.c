// ============================================
// Address:  0x00652e40
// Original: FUN_00652e40
// Status:   unreviewed
// ============================================

void FUN_00652e40(int param_1, int param_2)

{
    undefined4 uVar1;
    int iVar2;
    int local_a4;
    int local_a0;
    undefined1 local_9c[64];
    undefined1 local_5c[64];
    uint local_1c;
    uint local_18;
    int *local_14;
    int local_10;
    uint local_c;
    undefined4 local_8;

    if (param_1 == 0)
    {
        local_a0 = 0;
    }
    else
    {
        local_a0 = param_1 + -4;
    }
    if ((*(uint *)(local_a0 + 0x48) & 1) != 0)
    {
        if (param_1 == 0)
        {
            local_a4 = 0;
        }
        else
        {
            local_a4 = param_1 + -4;
        }
        local_10 = local_a4;
        local_8  = 0x3e99999a;
        local_14 = *(int **)(&DAT_006d13c0 + DAT_006d13e8 * 4);
        if (*(int *)(local_a4 + 0x20) == 0)
        {
            if (param_2 == 0)
            {
                iVar2 = 0;
            }
            else
            {
                iVar2 = param_2 + -0x10;
            }
            FUN_00423850(local_5c, &DAT_006d1510);
            if (param_2 == 0)
            {
                param_2 = 0;
            }
            else
            {
                param_2 = param_2 + -0x10;
            }
            FUN_00423850(local_9c, &DAT_006d15d0);
            (**(code **)(*local_14 + 0x98))(local_14, "mTransform", local_5c, param_2, iVar2);
            (**(code **)(*local_14 + 0x98))(local_14, "mTransformLight", local_9c);
            (**(code **)(*local_14 + 0x78))(local_14, "Alpha", local_8);
            (**(code **)(*local_14 + 0xfc))(local_14, &local_18, 0);
            for (local_c = 0; local_c < local_18; local_c = local_c + 1)
            {
                (**(code **)(*local_14 + 0x100))(local_14, local_c);
                for (local_1c = 0; local_1c < *(uint *)(local_10 + 0x18); local_1c = local_1c + 1)
                {
                    uVar1 = FUN_00662890(local_1c);
                    (**(code **)(*local_14 + 0xd0))(local_14, &DAT_006aac60, uVar1);
                    (**(code **)(*local_14 + 0xd0))(local_14, &DAT_006aac68, DAT_006d13f4);
                    (**(code **)(*local_14 + 0x104))(local_14);
                    (**(code **)(**(int **)(local_10 + 0xc) + 0xc))(*(undefined4 *)(local_10 + 0xc),
                                                                    local_1c);
                }
                (**(code **)(*local_14 + 0x108))(local_14);
            }
            (**(code **)(*local_14 + 0x10c))(local_14);
        }
        else
        {
            (**(code **)(*local_14 + 0x98))(local_14, "mTransform", &DAT_006d1510);
            (**(code **)(*local_14 + 0x98))(local_14, "mTransformLight", &DAT_006d15d0);
            (**(code **)(*local_14 + 0x78))(local_14, "Alpha", local_8);
            (**(code **)(*local_14 + 0xfc))(local_14, &local_18, 0);
            for (local_c = 0; local_c < local_18; local_c = local_c + 1)
            {
                (**(code **)(*local_14 + 0x100))(local_14, local_c);
                for (local_1c = 0; local_1c < *(uint *)(local_10 + 0x38); local_1c = local_1c + 1)
                {
                    uVar1 =
                        FUN_00662890(*(undefined4 *)(*(int *)(local_10 + 0x34) + local_1c * 0x14));
                    (**(code **)(*local_14 + 0xd0))(local_14, &DAT_006aac2c, uVar1);
                    (**(code **)(*local_14 + 0xd0))(local_14, &DAT_006aac34, DAT_006d13f4);
                    (**(code **)(*local_14 + 0x104))(local_14);
                    (**(code **)(**(int **)(local_10 + 0xc) + 0xc))(
                        *(undefined4 *)(local_10 + 0xc),
                        *(undefined4 *)(*(int *)(local_10 + 0x34) + local_1c * 0x14));
                }
                (**(code **)(*local_14 + 0x108))(local_14);
            }
            (**(code **)(*local_14 + 0x10c))(local_14);
        }
    }
    return;
}
