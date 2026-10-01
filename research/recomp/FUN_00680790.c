// ============================================
// Address:  0x00680790
// Original: FUN_00680790
// Status:   unreviewed
// ============================================

void FUN_00680790(int *param_1, int param_2)

{
    void *pvVar1;

    *param_1   = param_2;
    pvVar1     = _calloc(param_2 * 3, 4);
    param_1[1] = (int)pvVar1;
    pvVar1     = _calloc(0x20, 4);
    param_1[2] = (int)pvVar1;
    FUN_006807d0(param_2, param_1[1], pvVar1);
    return;
}
