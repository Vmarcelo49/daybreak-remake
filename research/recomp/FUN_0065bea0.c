// ============================================
// Address:  0x0065bea0
// Original: FUN_0065bea0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0065bea0(int param_1)

{
    char cVar1;
    int iVar2;

    if (*(int *)(param_1 + 0x1c) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x1c) + 8))(*(undefined4 *)(param_1 + 0x1c));
    }
    if (*(int *)(param_1 + 0x20) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x20) + 8))(*(undefined4 *)(param_1 + 0x20));
    }
    if (*(int *)(param_1 + 0x10) != 0)
    {
        (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0xc) + 8))(*(int *)(param_1 + 0x10) + 0xc);
    }
    if (*(int *)(param_1 + 0x14) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x14) + 8))(*(undefined4 *)(param_1 + 0x14));
    }
    if (*(int *)(param_1 + 0x18) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x18) + 8))(*(undefined4 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0xc) != 0)
    {
        if (*(undefined4 **)(param_1 + 0xc) != (undefined4 *)0x0)
        {
            (**(code **)**(undefined4 **)(param_1 + 0xc))(1);
        }
        *(undefined4 *)(param_1 + 0xc) = 0;
    }
    *(undefined4 *)(param_1 + 0x10) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(undefined4 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0;
    cVar1                           = FUN_0064d6e0();
    if (cVar1 == '\0')
    {
        FUN_006536c0(*(undefined4 *)(param_1 + 4));
        FUN_00654170(0);
    }
    iVar2 = FUN_0068de10();
    if (iVar2 != 0)
    {
        FUN_00656200(*(undefined4 *)(param_1 + 8));
        FUN_00654170(0);
    }
    return;
}
