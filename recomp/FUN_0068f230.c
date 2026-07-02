// ============================================
// Address:  0x0068f230
// Original: FUN_0068f230
// Status:   unreviewed
// ============================================

bool __fastcall FUN_0068f230(int param_1)

{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x68);
    if (*(int *)(param_1 + 0x68) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x18) + 0x18))(*(undefined4 *)(param_1 + 0x18),
                                                         *(undefined4 *)(param_1 + 0x68));
        FUN_0068f210();
    }
    FUN_006919c0();
    return iVar1 == 0;
}
