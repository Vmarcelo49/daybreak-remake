// ============================================
// Address:  0x0064e360
// Original: FUN_0064e360
// Status:   unreviewed
// ============================================

void __thiscall FUN_0064e360(undefined4 param_1, int param_2, int param_3)

{
    int iVar1;

    if (param_2 == 0)
    {
        param_2 = 0;
    }
    else
    {
        param_2 = param_2 + -0x10;
    }
    iVar1 = param_2;
    if (*(int *)(param_2 + 0xa0) != 0)
    {
        FUN_00423780(*(undefined4 *)(param_2 + 0xa0));
    }
    if (param_3 == 0)
    {
        FUN_0064ee60(param_2 + 0x14);
    }
    else
    {
        D3DXMatrixMultiply(param_2 + 0x60, param_2 + 0x14, param_3, iVar1, param_1);
    }
    if (*(int *)(param_2 + 0x58) != 0)
    {
        FUN_0064e360(*(undefined4 *)(param_2 + 0x58), param_3);
    }
    if (*(int *)(param_2 + 0x5c) != 0)
    {
        FUN_0064e360(*(undefined4 *)(param_2 + 0x5c), param_2 + 0x60);
    }
    return;
}
