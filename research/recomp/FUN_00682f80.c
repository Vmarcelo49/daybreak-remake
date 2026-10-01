// ============================================
// Address:  0x00682f80
// Original: FUN_00682f80
// Status:   unreviewed
// ============================================

int FUN_00682f80(uint param_1)

{
    int iVar1;

    iVar1 = 0;
    for (; param_1 != 0; param_1 = param_1 >> 1)
    {
        iVar1 = iVar1 + (param_1 & 1);
    }
    return iVar1;
}
