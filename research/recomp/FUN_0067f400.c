// ============================================
// Address:  0x0067f400
// Original: FUN_0067f400
// Status:   unreviewed
// ============================================

void FUN_0067f400(int param_1, undefined4 *param_2, undefined4 *param_3, int param_4, int param_5)

{
    int iVar1;
    int iVar2;
    int iVar3;
    undefined4 *puVar4;
    undefined4 *puVar5;
    int local_c;
    int *local_8;
    int local_4;

    iVar3   = param_5;
    local_4 = *(int *)(param_5 + 4);
    param_5 = 1;
    local_c = param_1;
    if (0 < local_4)
    {
        local_8 = (int *)(iVar3 + 4 + local_4 * 4);
        iVar3   = param_1;
        do
        {
            iVar2   = iVar3 / *local_8;
            iVar3   = param_1 / iVar3;
            local_c = local_c - (*local_8 + -1) * iVar3;
            param_5 = 1 - param_5;
            if (*local_8 == 4)
            {
                puVar4 = param_2;
                puVar5 = param_3;
                if (param_5 != 0)
                {
                    puVar4 = param_3;
                    puVar5 = param_2;
                }
                FUN_0067f770(iVar3,
                             iVar2,
                             puVar4,
                             puVar5,
                             param_4 + -4 + local_c * 4,
                             param_4 + -4 + (iVar3 + local_c) * 4,
                             param_4 + -4 + (iVar3 + local_c + iVar3) * 4);
            }
            else if (*local_8 == 2)
            {
                iVar1 = param_4 + -4 + local_c * 4;
                if (param_5 == 0)
                {
                    FUN_0067f5b0(iVar3, iVar2, param_2, param_3, iVar1);
                }
                else
                {
                    FUN_0067f5b0(iVar3, iVar2, param_3, param_2, iVar1);
                }
            }
            else
            {
                if (iVar3 == 1)
                {
                    param_5 = 1 - param_5;
                }
                iVar1 = param_4 + -4 + local_c * 4;
                if (param_5 == 0)
                {
                    FUN_0067fbe0(iVar3,
                                 *local_8,
                                 iVar2,
                                 iVar3 * iVar2,
                                 param_2,
                                 param_2,
                                 param_2,
                                 param_3,
                                 param_3,
                                 iVar1);
                    param_5 = 1;
                }
                else
                {
                    FUN_0067fbe0(iVar3,
                                 *local_8,
                                 iVar2,
                                 iVar3 * iVar2,
                                 param_3,
                                 param_3,
                                 param_3,
                                 param_2,
                                 param_2,
                                 iVar1);
                    param_5 = 0;
                }
            }
            local_8 = local_8 + -1;
            local_4 = local_4 + -1;
            iVar3   = iVar2;
        } while (local_4 != 0);
        if ((param_5 != 1) && (0 < param_1))
        {
            iVar3 = (int)param_3 - (int)param_2;
            do
            {
                *param_2 = *(undefined4 *)((int)param_2 + iVar3);
                param_2  = param_2 + 1;
                param_1  = param_1 + -1;
            } while (param_1 != 0);
        }
    }
    return;
}
