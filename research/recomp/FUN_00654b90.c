// ============================================
// Address:  0x00654b90
// Original: FUN_00654b90
// Status:   unreviewed
// ============================================

undefined4 __thiscall
FUN_00654b90(int param_1, HWND param_2, int param_3, int param_4, char param_5)

{
    undefined4 uVar1;
    int iVar2;
    tagWINDOWINFO local_40;

    uVar1                           = Direct3DCreate9(0x20);
    *(undefined4 *)(param_1 + 0x1c) = uVar1;
    if (*(int *)(param_1 + 0x1c) == 0)
    {
        FUN_006553e0(&DAT_006aac74);
        uVar1 = 0;
    }
    else
    {
        iVar2 = (**(code **)(**(int **)(param_1 + 0x1c) + 0x20))(
            *(undefined4 *)(param_1 + 0x1c), 0, param_1 + 0x5c);
        if (iVar2 < 0)
        {
            FUN_006553e0(&DAT_006aac90);
            uVar1 = 0;
        }
        else
        {
            _memset((void *)(param_1 + 0x24), 0, 0x38);
            if ((param_3 < 1) || (param_4 < 1))
            {
                _memset(&local_40, 0, 0x3c);
                GetWindowInfo(param_2, &local_40);
                *(LONG *)(param_1 + 0x24) = local_40.rcClient.right - local_40.rcClient.left;
                *(LONG *)(param_1 + 0x28) = local_40.rcClient.bottom - local_40.rcClient.top;
            }
            else
            {
                *(int *)(param_1 + 0x24) = param_3;
                *(int *)(param_1 + 0x28) = param_4;
            }
            *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x68);
            *(undefined4 *)(param_1 + 0x30) = 1;
            *(undefined4 *)(param_1 + 0x34) = 0;
            *(undefined4 *)(param_1 + 0x3c) = 1;
            *(HWND *)(param_1 + 0x40)       = param_2;
            *(undefined4 *)(param_1 + 0x44) = 1;
            *(undefined4 *)(param_1 + 0x48) = 1;
            *(undefined4 *)(param_1 + 0x4c) = 0x50;
            *(undefined4 *)(param_1 + 0x50) = 2;
            *(undefined4 *)(param_1 + 0x54) = 0;
            if (param_5 == '\0')
            {
                *(undefined4 *)(param_1 + 0x58) = 0;
            }
            else
            {
                *(undefined4 *)(param_1 + 0x58) = 0x80000000;
            }
            iVar2 =
                (**(code **)(**(int **)(param_1 + 0x1c) + 0x40))(*(undefined4 *)(param_1 + 0x1c),
                                                                 0,
                                                                 1,
                                                                 param_2,
                                                                 0x44,
                                                                 param_1 + 0x24,
                                                                 param_1 + 0x20);
            if (((iVar2 < 0) && (iVar2 = (**(code **)(**(int **)(param_1 + 0x1c) + 0x40))(
                                     *(undefined4 *)(param_1 + 0x1c),
                                     0,
                                     1,
                                     param_2,
                                     0x24,
                                     param_1 + 0x24,
                                     param_1 + 0x20),
                                 iVar2 < 0)) &&
                (iVar2 = (**(code **)(**(int **)(param_1 + 0x1c) + 0x40))(
                     *(undefined4 *)(param_1 + 0x1c),
                     0,
                     2,
                     param_2,
                     0x24,
                     param_1 + 0x24,
                     param_1 + 0x20),
                 iVar2 < 0))
            {
                FUN_006553e0(&DAT_006aacb0);
                return 0;
            }
            FUN_00654f00();
            uVar1 = 1;
        }
    }
    return uVar1;
}
