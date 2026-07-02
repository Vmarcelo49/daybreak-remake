// ============================================
// Address:  0x0067cbc0
// Original: FUN_0067cbc0
// Status:   unreviewed
// ============================================

void FUN_0067cbc0(int *param_1, int param_2, int param_3)

{
    float *pfVar1;
    float fVar2;
    int iVar3;
    float *pfVar4;
    int iVar5;
    int iVar6;

    iVar6 = 0;
    iVar5 = param_1[9];
    FUN_0067cd00(param_2, iVar5, param_1[10]);
    iVar5 = (*(int *)param_1[5] - (iVar5 >> 1)) - param_1[7];
    if (1 < *param_1)
    {
        do
        {
            fVar2  = *(float *)(param_2 + iVar5 * 4);
            pfVar4 = (float *)(param_2 + iVar5 * 4);
            iVar3  = iVar5;
            if (*(float *)(param_1[1] + 0x20) < fVar2)
            {
                fVar2 = *(float *)(param_1[1] + 0x20);
            }
            while (
                iVar3 = iVar3 + 1,
                iVar3 <=
                    (*(int *)(param_1[5] + 4 + iVar6 * 4) + *(int *)(param_1[5] + iVar6 * 4) >> 1) -
                        param_1[7])
            {
                pfVar1 = pfVar4 + 1;
                pfVar4 = pfVar4 + 1;
                iVar5  = iVar5 + 1;
                if (((-9999.0 < *pfVar1) && (*pfVar4 < fVar2)) || (fVar2 == -9999.0))
                {
                    fVar2 = *pfVar4;
                }
            }
            iVar3 = param_1[7];
            if (iVar6 < *param_1)
            {
                do
                {
                    if (iVar3 + iVar5 < *(int *)(param_1[5] + iVar6 * 4))
                        break;
                    if (*(float *)(param_3 + iVar6 * 4) < fVar2)
                    {
                        *(float *)(param_3 + iVar6 * 4) = fVar2;
                    }
                    iVar6 = iVar6 + 1;
                } while (iVar6 < *param_1);
            }
        } while (iVar6 + 1 < *param_1);
    }
    fVar2 = *(float *)(param_2 + -4 + param_1[10] * 4);
    if (iVar6 < *param_1)
    {
        pfVar4 = (float *)(param_3 + iVar6 * 4);
        do
        {
            if (*pfVar4 < fVar2)
            {
                *pfVar4 = fVar2;
            }
            iVar6  = iVar6 + 1;
            pfVar4 = pfVar4 + 1;
        } while (iVar6 < *param_1);
    }
    return;
}
