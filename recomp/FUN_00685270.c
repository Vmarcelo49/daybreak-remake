// ============================================
// Address:  0x00685270
// Original: FUN_00685270
// Status:   unreviewed
// ============================================

undefined4 FUN_00685270(
    int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)

{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    uint uVar5;
    uint uVar6;
    int iVar7;
    int iVar8;
    float *pfVar9;
    int iVar10;
    int local_18;

    iVar8  = param_1;
    uVar5  = param_4 - param_3;
    iVar10 = param_2 - param_1;
    iVar1  = (int)uVar5 / iVar10;
    if ((int)uVar5 < 0)
    {
        iVar2 = iVar1 + -1;
    }
    else
    {
        iVar2 = iVar1 + 1;
    }
    param_4  = param_3;
    local_18 = 0;
    pfVar9   = (float *)(param_5 + param_1 * 4);
    iVar3    = FUN_00685030(pfVar9);
    uVar6    = iVar1 * iVar10 >> 0x1f;
    iVar4    = param_1 * 4;
    iVar7    = (param_3 - iVar3) * (param_3 - iVar3);
    param_1  = 1;
    if (*pfVar9 <= *(float *)(param_6 + iVar4) + *(float *)(param_7 + 0x458))
    {
        if ((float)param_3 + *(float *)(param_7 + 0x448) < (float)iVar3)
        {
            return 1;
        }
        if ((float)iVar3 < (float)param_3 - *(float *)(param_7 + 0x44c))
        {
            return 1;
        }
    }
    iVar8 = iVar8 + 1;
    if (iVar8 < param_2)
    {
        pfVar9 = (float *)(param_5 + iVar8 * 4);
        do
        {
            local_18 = local_18 + (((uVar5 ^ (int)uVar5 >> 0x1f) - ((int)uVar5 >> 0x1f)) -
                                   ((iVar1 * iVar10 ^ uVar6) - uVar6));
            iVar4    = iVar1;
            if (iVar10 <= local_18)
            {
                local_18 = local_18 - iVar10;
                iVar4    = iVar2;
            }
            param_4 = param_4 + iVar4;
            iVar4   = FUN_00685030(pfVar9);
            iVar7   = iVar7 + (param_4 - iVar4) * (param_4 - iVar4);
            param_1 = param_1 + 1;
            if ((*pfVar9 <=
                 *(float *)((param_6 - param_5) + (int)pfVar9) + *(float *)(param_7 + 0x458)) &&
                (iVar4 != 0))
            {
                if ((float)param_4 + *(float *)(param_7 + 0x448) < (float)iVar4)
                {
                    return 1;
                }
                if ((float)iVar4 < (float)param_4 - *(float *)(param_7 + 0x44c))
                {
                    return 1;
                }
            }
            iVar8  = iVar8 + 1;
            pfVar9 = pfVar9 + 1;
        } while (iVar8 < param_2);
    }
    if ((((*(float *)(param_7 + 0x448) * *(float *)(param_7 + 0x448)) / (float)param_1 <=
          *(float *)(param_7 + 0x450)) &&
         ((*(float *)(param_7 + 0x44c) * *(float *)(param_7 + 0x44c)) / (float)param_1 <=
          *(float *)(param_7 + 0x450))) &&
        (*(float *)(param_7 + 0x450) < (float)(iVar7 / param_1)))
    {
        return 1;
    }
    return 0;
}
