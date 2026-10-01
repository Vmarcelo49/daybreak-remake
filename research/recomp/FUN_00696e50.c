// ============================================
// Address:  0x00696e50
// Original: FUN_00696e50
// Status:   unreviewed
// ============================================

undefined4 FUN_00696e50(int param_1, undefined4 *param_2)

{
    undefined4 uVar1;

    if (param_2 == (undefined4 *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else if (*(int *)(param_1 + 4) == 0)
    {
        *param_2 = *(undefined4 *)(param_1 + 0x40);
        uVar1    = 0;
    }
    else
    {
        uVar1 = 0x80004004;
    }
    return uVar1;
}
