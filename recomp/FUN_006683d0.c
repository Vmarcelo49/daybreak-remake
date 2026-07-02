// ============================================
// Address:  0x006683d0
// Original: FUN_006683d0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_006683d0(undefined4 *param_1, undefined4 param_2)

{
    char cVar1;
    undefined4 uVar2;
    int iVar3;

    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0')
    {
        *param_1 = param_1[1];
    }
    else
    {
        cVar1 = FUN_0064d6e0();
        if (cVar1 == '\0')
        {
            FUN_006536c0(*param_1);
            FUN_00654170(0);
        }
    }
    cVar1 = FUN_00653620(param_1, param_2);
    if (cVar1 == '\0')
    {
        uVar2 = 0;
    }
    else
    {
        uVar2      = FUN_00653a70(*param_1);
        param_1[2] = uVar2;
        iVar3      = FUN_006778e0(param_1,
                                  param_1 + 4,
                                  0,
                                  0,
                                  PTR_FUN_006b77c8,
                                  PTR_FUN_006b77cc,
                                  PTR_FUN_006b77d0,
                                  PTR_FUN_006b77d4);
        if (iVar3 < 0)
        {
            FUN_006536c0(*param_1);
            FUN_00654170(0);
            uVar2 = 0;
        }
        else
        {
            uVar2                                  = FUN_00679700(param_1 + 4, 0xffffffff);
            param_1[0xb8]                          = uVar2;
            *(undefined2 *)(param_1 + 0x4be)       = 1;
            *(undefined2 *)((int)param_1 + 0x12fa) = *(undefined2 *)(param_1[0xb8] + 4);
            param_1[0x4bf]                         = *(undefined4 *)(param_1[0xb8] + 8);
            *(undefined2 *)((int)param_1 + 0x1306) = 0x10;
            iVar3                       = (uint) * (ushort *)((int)param_1 + 0x12fa) * (uint) *
                                          (ushort *)((int)param_1 + 0x1306);
            *(short *)(param_1 + 0x4c1) = (short)((int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3);
            param_1[0x4c0]              = (uint) * (ushort *)(param_1 + 0x4c1) * param_1[0x4bf];
            *(undefined2 *)(param_1 + 0x4c2) = 0;
            FUN_00668820(param_2);
            uVar2 = 1;
        }
    }
    return uVar2;
}
