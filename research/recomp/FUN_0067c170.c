// ============================================
// Address:  0x0067c170
// Original: FUN_0067c170
// Status:   unreviewed
// ============================================

void FUN_0067c170(float *param_1, float param_2)

{
    int iVar1;

    iVar1 = 0x38;
    do
    {
        iVar1    = iVar1 + -1;
        *param_1 = param_2 + *param_1;
        param_1  = param_1 + 1;
    } while (iVar1 != 0);
    return;
}
