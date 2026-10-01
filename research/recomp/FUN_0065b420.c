// ============================================
// Address:  0x0065b420
// Original: FUN_0065b420
// Status:   unreviewed
// ============================================

void __thiscall FUN_0065b420(int param_1, undefined4 param_2, char param_3, int param_4)

{
    char cVar1;
    uint uVar2;
    int *piVar3;
    undefined4 *puVar4;

    if (param_3 == '\0')
    {
        FUN_0065b330(param_2, param_4);
    }
    else
    {
        cVar1 = FUN_0064d6e0();
        if (cVar1 == '\0')
        {
            if (param_4 - *(char *)(param_1 + 0x58) < *(int *)(param_1 + 0x54))
            {
                if (*(char *)(param_1 + 0x50) == '\0')
                {
                    uVar2  = FUN_00667f50();
                    piVar3 = (int *)FUN_0065a850(*(undefined4 *)(param_1 + 0x4c));
                    if (uVar2 < *(uint *)(*piVar3 + 0x18))
                    {
                        return;
                    }
                }
                else
                {
                    uVar2  = FUN_00667f50();
                    piVar3 = (int *)FUN_0065a850(*(undefined4 *)(param_1 + 0x4c));
                    if (uVar2 < *(uint *)(*piVar3 + 0x18))
                    {
                        return;
                    }
                }
            }
            FUN_00667f20();
            puVar4 = (undefined4 *)FUN_0065a850(param_2);
            FUN_00667860(*puVar4);
            FUN_00667ed0(0);
            *(int *)(param_1 + 0x54)        = param_4;
            *(undefined4 *)(param_1 + 0x4c) = param_2;
            *(undefined1 *)(param_1 + 0x50) = 1;
        }
    }
    return;
}
