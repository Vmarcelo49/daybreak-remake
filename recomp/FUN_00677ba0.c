// ============================================
// Address:  0x00677ba0
// Original: FUN_00677ba0
// Status:   unreviewed
// ============================================

undefined8 FUN_00677ba0(int param_1, undefined4 param_2, uint param_3, int param_4)

{
    uint uVar1;
    undefined8 uVar2;
    uint uVar3;
    int iVar4;
    bool bVar5;

    if ((-1 < param_4) && ((0 < param_4 || (param_3 != 0))))
    {
        bVar5   = CARRY4(param_3, *(uint *)(param_1 + 8));
        param_3 = param_3 + *(uint *)(param_1 + 8);
        param_4 = param_4 + *(int *)(param_1 + 0xc) + (uint)bVar5;
    }
    while (true)
    {
        while (true)
        {
            if (((-1 < param_4) && ((0 < param_4 || (param_3 != 0)))) &&
                ((param_4 < *(int *)(param_1 + 0xc) ||
                  ((param_4 <= *(int *)(param_1 + 0xc) && (param_3 <= *(uint *)(param_1 + 8)))))))
            {
                return 0xffffffffffffffff;
            }
            uVar3 = FUN_0069ce40(param_1 + 0x18, param_2);
            if (-1 < (int)uVar3)
                break;
            uVar1                  = *(uint *)(param_1 + 8);
            *(uint *)(param_1 + 8) = uVar1 - uVar3;
            *(uint *)(param_1 + 0xc) =
                (*(int *)(param_1 + 0xc) - ((int)uVar3 >> 0x1f)) - (uint)(uVar1 < uVar3);
        }
        if (uVar3 != 0)
        {
            uVar1                  = *(uint *)(param_1 + 8);
            uVar2                  = *(undefined8 *)(param_1 + 8);
            *(uint *)(param_1 + 8) = uVar3 + uVar1;
            *(uint *)(param_1 + 0xc) =
                ((int)uVar3 >> 0x1f) + *(int *)(param_1 + 0xc) + (uint)CARRY4(uVar3, uVar1);
            return uVar2;
        }
        if (param_3 == 0 && param_4 == 0)
            break;
        iVar4 = FUN_00677c60(param_1);
        if (iVar4 == 0)
        {
            return 0xfffffffffffffffe;
        }
        if (iVar4 < 0)
        {
            return 0xffffffffffffff80;
        }
    }
    return 0xffffffffffffffff;
}
