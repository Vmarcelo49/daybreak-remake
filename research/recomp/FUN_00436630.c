// ============================================
// Address:  0x00436630
// Original: FUN_00436630
// Status:   unreviewed
// ============================================

void __fastcall FUN_00436630(int param_1)

{
    int iVar1;

    if (*(int *)(param_1 + 300) == 0x24)
    {
        iVar1                           = *(int *)(param_1 + 0x38);
        *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(iVar1 + 0x14);
        *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(iVar1 + 0x18);
        *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(iVar1 + 0x1c);
    }
    *(int *)(param_1 + 0x130) = *(int *)(param_1 + 0x130) + 1;
    if (**(int **)(param_1 + 0x120) <= *(int *)(param_1 + 0x130))
    {
        FUN_00435e40();
    }
    return;
}
