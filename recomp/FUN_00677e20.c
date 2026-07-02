// ============================================
// Address:  0x00677e20
// Original: FUN_00677e20
// Status:   unreviewed
// ============================================

longlong FUN_00677e20(int param_1, undefined4 param_2)

{
    uint uVar1;
    int iVar2;
    longlong lVar3;
    int iVar4;
    uint uVar5;
    int extraout_EDX;
    bool bVar6;
    longlong lVar7;
    uint local_10;
    int local_c;

    uVar1    = *(uint *)(param_1 + 8);
    iVar2    = *(int *)(param_1 + 0xc);
    lVar3    = -1;
    local_c  = iVar2;
    local_10 = uVar1;
    do
    {
        bVar6    = 0x2133 < local_10;
        local_10 = local_10 - 0x2134;
        local_c  = local_c + -1 + (uint)bVar6;
        if ((local_c < 1) && (local_c < 0))
        {
            local_10 = 0;
            local_c  = 0;
        }
        FUN_00677f40(param_1, local_10, local_c);
        iVar4 = *(int *)(param_1 + 0xc);
        uVar5 = *(uint *)(param_1 + 8);
        if (iVar4 <= iVar2)
        {
            lVar7 = lVar3;
            if (iVar4 < iVar2)
                goto LAB_00677e8a;
            while (lVar3 = lVar7, uVar5 < uVar1)
            {
            LAB_00677e8a:
                do
                {
                    lVar7 = FUN_00677ba0(
                        param_1, param_2, uVar1 - uVar5, (iVar2 - iVar4) - (uint)(uVar1 < uVar5));
                    if (lVar7 == -0x80)
                    {
                        return -0x80;
                    }
                    if (lVar7 < 0)
                        goto LAB_00677ecc;
                    uVar5 = *(uint *)(param_1 + 8);
                    iVar4 = *(int *)(param_1 + 0xc);
                    lVar3 = lVar7;
                } while (iVar4 < iVar2);
                if (iVar2 < iVar4)
                    break;
            }
        }
    LAB_00677ecc:
        if (lVar3 != -1)
        {
            FUN_00677f40(param_1, lVar3);
            FUN_00677ba0(param_1, param_2, 0x2134, 0);
            if ((extraout_EDX < 1) && (extraout_EDX < 0))
            {
                return -0x81;
            }
            return lVar3;
        }
    } while (true);
}
