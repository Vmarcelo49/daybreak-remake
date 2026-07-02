// ============================================
// Address:  0x00685b70
// Original: FUN_00685b70
// Status:   unreviewed
// ============================================

void FUN_00685b70(int param_1, int param_2, int param_3, int param_4, int param_5)

{
    int iVar1;
    int iVar2;
    int iVar3;
    uint uVar4;
    int *piVar5;
    uint uVar6;
    int iVar7;

    uVar4 = param_4 - param_3;
    iVar7 = param_2 - param_1;
    iVar2 = (int)uVar4 / iVar7;
    if ((int)uVar4 < 0)
    {
        param_4 = iVar2 + -1;
    }
    else
    {
        param_4 = iVar2 + 1;
    }
    uVar6                           = iVar2 * iVar7 >> 0x1f;
    *(int *)(param_5 + param_1 * 4) = param_3;
    param_1                         = param_1 + 1;
    if (param_1 < param_2)
    {
        piVar5  = (int *)(param_5 + param_1 * 4);
        param_2 = param_2 - param_1;
        iVar3   = 0;
        do
        {
            iVar3 = iVar3 + (((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)) -
                             ((iVar2 * iVar7 ^ uVar6) - uVar6));
            iVar1 = iVar2;
            if (iVar7 <= iVar3)
            {
                iVar3 = iVar3 - iVar7;
                iVar1 = param_4;
            }
            param_3 = param_3 + iVar1;
            *piVar5 = param_3;
            piVar5  = piVar5 + 1;
            param_2 = param_2 + -1;
        } while (param_2 != 0);
    }
    return;
}
