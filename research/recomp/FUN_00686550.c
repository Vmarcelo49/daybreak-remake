// ============================================
// Address:  0x00686550
// Original: FUN_00686550
// Status:   unreviewed
// ============================================

void FUN_00686550(int param_1,
                  int param_2,
                  int param_3,
                  int param_4,
                  float *param_5,
                  uint param_6,
                  float param_7,
                  float param_8)

{
    float fVar1;
    float fVar2;
    float fVar3;
    int iVar4;
    float *pfVar5;
    float *pfVar6;
    int iVar7;
    int iVar8;
    uint uVar9;
    float10 fVar10;
    float10 fVar11;
    double dVar12;
    int local_4;

    pfVar6 = param_5;
    uVar9  = param_6;
    if (0 < (int)param_6)
    {
        do
        {
            fVar10  = (float10)FUN_006866d0(*pfVar6);
            *pfVar6 = (float)fVar10;
            uVar9   = uVar9 - 1;
            pfVar6  = pfVar6 + 1;
        } while (uVar9 != 0);
    }
    iVar8 = 0;
    if (0 < param_3)
    {
        do
        {
            iVar4  = *(int *)(param_2 + iVar8 * 4);
            fVar10 = (float10)FUN_006866d0((float)iVar4 * (3.1415927 / (float)param_4));
            fVar1  = (float)fVar10;
            fVar2  = 0.70710677;
            fVar3  = 0.70710677;
            pfVar6 = param_5;
            iVar7  = (int)param_6 >> 1;
            do
            {
                pfVar5 = pfVar6 + 2;
                iVar7  = iVar7 + -1;
                fVar2  = (*pfVar6 - fVar1) * fVar2;
                fVar3  = (pfVar6[1] - fVar1) * fVar3;
                pfVar6 = pfVar5;
            } while (iVar7 != 0);
            if ((param_6 & 1) == 0)
            {
                fVar2 = (fVar1 + 1.0) * fVar2 * fVar2;
            }
            else
            {
                fVar2 = (*pfVar5 - fVar1) * fVar2;
                fVar2 = fVar2 * fVar2;
                fVar1 = fVar1 * fVar1;
            }
            dVar12 = _frexp((double)(fVar2 + (1.0 - fVar1) * fVar3 * fVar3), &local_4);
            fVar10 = (float10)FUN_00686770(local_4 + param_6);
            fVar11 = (float10)FUN_00686720((float)dVar12);
            fVar10 = (float10)FUN_00686780(
                (float)(fVar11 * (float10)(float)fVar10 * (float10)param_7 - (float10)param_8));
            pfVar6 = (float *)(param_1 + iVar8 * 4);
            do
            {
                pfVar5  = pfVar6 + 1;
                iVar8   = iVar8 + 1;
                *pfVar6 = (float)(fVar10 * (float10)*pfVar6);
                pfVar6  = pfVar5;
            } while (*(int *)((param_2 - param_1) + (int)pfVar5) == iVar4);
        } while (iVar8 < param_3);
    }
    return;
}
