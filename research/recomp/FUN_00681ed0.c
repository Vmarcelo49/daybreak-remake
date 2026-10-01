// ============================================
// Address:  0x00681ed0
// Original: FUN_00681ed0
// Status:   unreviewed
// ============================================

int FUN_00681ed0(int param_1)

{
    int iVar1;
    uint uVar2;

    iVar1 = 0;
    if (param_1 != 0)
    {
        for (uVar2 = param_1 - 1; uVar2 != 0; uVar2 = uVar2 >> 1)
        {
            iVar1 = iVar1 + 1;
        }
    }
    return iVar1;
}
