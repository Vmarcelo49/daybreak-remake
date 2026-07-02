// ============================================
// Address:  0x0068a7b0
// Original: FUN_0068a7b0
// Status:   unreviewed
// ============================================

int FUN_0068a7b0(int param_1, int *param_2)

{
    int iVar1;
    undefined4 uVar2;
    int *local_8;

    if (param_2 == (int *)0x0)
    {
        iVar1 = -0x7fffbffd;
    }
    else
    {
        iVar1 = (**(code **)(*(int *)(param_1 + -0x98) + 0x38))();
        if (iVar1 == 0)
        {
            iVar1 = (**(code **)*param_2)(param_2, &LAB_006ad031_3, &local_8);
            if (iVar1 < 0)
            {
                *(undefined4 *)(param_1 + 0x10) = 0x30;
                *(undefined4 *)(param_1 + 0x14) = 0;
                *(undefined4 *)(param_1 + 0x30) = 0;
                *(undefined4 *)(param_1 + 0x18) = 0;
                iVar1                           = (**(code **)(*param_2 + 0x3c))(param_2);
                if (iVar1 == 0)
                {
                    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 4;
                }
                iVar1 = (**(code **)(*param_2 + 0x24))(param_2);
                if (iVar1 == 0)
                {
                    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 2;
                }
                iVar1 = (**(code **)(*param_2 + 0x1c))(param_2);
                if (iVar1 == 0)
                {
                    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 1;
                }
                iVar1 = (**(code **)(*param_2 + 0x14))(param_2, param_1 + 0x20, param_1 + 0x28);
                if (-1 < iVar1)
                {
                    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 0x110;
                }
                iVar1 = (**(code **)(*param_2 + 0x34))(param_2, param_1 + 0x34);
                if (iVar1 == 0)
                {
                    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) | 8;
                }
                (**(code **)(*param_2 + 0xc))(param_2, param_1 + 0x38);
                uVar2                           = (**(code **)(*param_2 + 0x2c))(param_2);
                *(undefined4 *)(param_1 + 0x1c) = uVar2;
                uVar2                           = (**(code **)(*param_2 + 0x10))(param_2);
                *(undefined4 *)(param_1 + 0x3c) = uVar2;
            }
            else
            {
                iVar1 = (**(code **)(*local_8 + 0x4c))(local_8, 0x30, param_1 + 0x10);
                (**(code **)(*local_8 + 8))(local_8);
                if (iVar1 < 0)
                {
                    return iVar1;
                }
            }
            if ((*(uint *)(param_1 + 0x18) & 8) == 0)
            {
                iVar1 = 0;
            }
            else
            {
                iVar1 = (**(code **)(*(int *)(param_1 + -0x98) + 0x20))(
                    *(undefined4 *)(param_1 + 0x34));
                if (iVar1 == 0)
                {
                    iVar1 = 0;
                }
                else
                {
                    *(undefined1 *)(param_1 + -0x74) = 1;
                    (**(code **)(*(int *)(param_1 + -0x8c) + 0x38))(param_1 + -0x8c);
                    FUN_006883f0(3, 0x8004022a, 0);
                    iVar1 = -0x7ffbfe00;
                }
            }
        }
    }
    return iVar1;
}
