// ============================================
// Address:  0x0067c2b0
// Original: FUN_0067c2b0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Type propagation algorithm not settling */

void FUN_0067c2b0(int *param_1, int param_2, float *param_3)

{
    float *pfVar1;
    float fVar2;
    int iVar3;
    int iVar4;
    float *pfVar5;
    float *pfVar6;
    int iVar7;
    int iVar8;
    int aiStack_30[6];
    undefined4 uStack_18;

    pfVar5                = param_3;
    iVar3                 = *param_1;
    uStack_18             = 0x67c2cd;
    iVar4                 = iVar3 * -4;
    iVar8                 = param_1[6];
    aiStack_30[6 - iVar3] = 0xffffffff;
    aiStack_30[5 - iVar3] = 0x430c0000;
    aiStack_30[4 - iVar3] = (int)param_3;
    aiStack_30[3 - iVar3] = param_2;
    aiStack_30[2 - iVar3] = iVar8;
    aiStack_30[1 - iVar3] = iVar3;
    aiStack_30[-iVar3]    = 0x67c2eb;
    FUN_0067c3a0();
    if (0 < iVar3)
    {
        iVar7   = param_2 - (int)param_3;
        iVar8   = iVar4 - (int)param_3;
        pfVar6  = param_3;
        param_3 = (float *)iVar3;
        do
        {
            pfVar1 = (float *)(iVar7 + (int)pfVar6);
            fVar2  = *pfVar6;
            pfVar6 = pfVar6 + 1;
            *(float *)((int)aiStack_30 + iVar8 + 0x18 + (int)pfVar6) = *pfVar1 - fVar2;
            param_3                                                  = (float *)((int)param_3 + -1);
        } while (param_3 != (float *)0x0);
    }
    iVar8                 = param_1[6];
    aiStack_30[6 - iVar3] = *(undefined4 *)(param_1[1] + 0x80);
    aiStack_30[5 - iVar3] = 0;
    aiStack_30[4 - iVar3] = (int)pfVar5;
    aiStack_30[3 - iVar3] = (int)(&stack0xffffffec + iVar4);
    aiStack_30[2 - iVar3] = iVar8;
    aiStack_30[1 - iVar3] = iVar3;
    aiStack_30[-iVar3]    = 0x67c336;
    FUN_0067c3a0();
    if (0 < iVar3)
    {
        pfVar6 = (float *)(&stack0xffffffec + iVar4);
        iVar8  = iVar3;
        do
        {
            iVar8 = iVar8 + -1;
            *pfVar6 =
                *(float *)((param_2 - (int)(&stack0xffffffec + iVar4)) + (int)pfVar6) - *pfVar6;
            pfVar6 = pfVar6 + 1;
        } while (iVar8 != 0);
        if (0 < iVar3)
        {
            iVar8  = iVar3;
            pfVar6 = pfVar5;
            do
            {
                aiStack_30[6 - iVar3] = 0x67c367;
                iVar7                 = __ftol();
                if (iVar7 < 0x28)
                {
                    if (iVar7 < 0)
                    {
                        iVar7 = 0;
                    }
                }
                else
                {
                    iVar7 = 0x27;
                }
                iVar8   = iVar8 + -1;
                *pfVar6 = *(float *)(param_1[1] + 0x150 + iVar7 * 4) +
                          *(float *)((int)pfVar6 + (int)(&stack0xffffffec + (iVar4 - (int)pfVar5)));
                pfVar6  = pfVar6 + 1;
            } while (iVar8 != 0);
        }
    }
    return;
}
