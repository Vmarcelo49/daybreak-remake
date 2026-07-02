// ============================================
// Address:  0x00656300
// Original: FUN_00656300
// Status:   unreviewed
// ============================================

void __thiscall FUN_00656300(int param_1, undefined4 param_2)

{
    char cVar1;
    int iVar2;
    undefined4 *puVar3;

    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0')
    {
        iVar2 = FUN_00656420(*(undefined4 *)(param_1 + 0x30));
        if (iVar2 != 0)
        {
            puVar3 = (undefined4 *)FUN_00656740(param_2);
            (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8, 0, *puVar3);
        }
    }
    else
    {
        (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8, 0, 0);
    }
    *(undefined4 *)(param_1 + 0x30) = param_2;
    return;
}
