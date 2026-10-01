// ============================================
// Address:  0x00686000
// Original: FUN_00686000
// Status:   unreviewed
// ============================================

void FUN_00686000(int param_1, int param_2, int param_3, int param_4, int param_5)

{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    uint uVar5;
    float *pfVar6;
    uint uVar7;
    float *pfVar8;
    int iVar9;

    iVar4 = param_2;
    iVar2 = param_1;
    uVar7 = param_4 - param_3;
    iVar9 = param_2 - param_1;
    iVar3 = (int)uVar7 / iVar9;
    if ((int)uVar7 < 0)
    {
        param_1 = iVar3 + -1;
    }
    else
    {
        param_1 = iVar3 + 1;
    }
    uVar5   = iVar3 * iVar9 >> 0x1f;
    param_2 = 0;
    pfVar6  = (float *)(&DAT_006c6860 + param_3 * 4);
    iVar1   = iVar2 + 1;
    *(float *)(param_5 + iVar2 * 4) =
        *(float *)(&DAT_006c6860 + param_3 * 4) * *(float *)(param_5 + iVar2 * 4);
    if (iVar1 < iVar4)
    {
        iVar4  = iVar4 - iVar1;
        pfVar8 = (float *)(param_5 + iVar1 * 4);
        do
        {
            param_2 = param_2 + (((uVar7 ^ (int)uVar7 >> 0x1f) - ((int)uVar7 >> 0x1f)) -
                                 ((iVar3 * iVar9 ^ uVar5) - uVar5));
            iVar2   = iVar3;
            if (iVar9 <= param_2)
            {
                param_2 = param_2 - iVar9;
                iVar2   = param_1;
            }
            pfVar6  = pfVar6 + iVar2;
            iVar4   = iVar4 + -1;
            *pfVar8 = *pfVar6 * *pfVar8;
            pfVar8  = pfVar8 + 1;
        } while (iVar4 != 0);
    }
    return;
}
