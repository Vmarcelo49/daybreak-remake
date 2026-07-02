// ============================================
// Address:  0x00688b90
// Original: FUN_00688b90
// Status:   unreviewed
// ============================================

undefined4 FUN_00688b90(int param_1)

{
    undefined4 uVar1;

    uVar1                           = (**(code **)(**(int **)(param_1 + 0xc) + 0x14))();
    *(undefined4 *)(param_1 + 0x10) = uVar1;
    uVar1                           = (**(code **)(**(int **)(param_1 + 0xc) + 0x18))();
    *(undefined4 *)(param_1 + 8)    = uVar1;
    *(undefined4 *)(param_1 + 4)    = 0;
    return 0;
}
