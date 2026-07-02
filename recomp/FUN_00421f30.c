// ============================================
// Address:  0x00421f30
// Original: FUN_00421f30
// Status:   unreviewed
// ============================================

void __thiscall FUN_00421f30(int param_1, int param_2)

{
    int iVar1;
    undefined4 *puVar2;

    if ((-1 < param_2) && (iVar1 = FUN_0064f010(), param_2 < iVar1))
    {
        *(int *)(param_1 + 0x304)        = param_2;
        *(undefined4 *)(param_1 + 0x30c) = 0xf;
        puVar2                           = (undefined4 *)FUN_00658a10(param_2);
        *(undefined4 *)(param_1 + 0x38)  = *puVar2;
        puVar2                           = (undefined4 *)FUN_00658a10(param_2);
        *(undefined4 *)(param_1 + 0x308) = *puVar2;
        *(undefined4 *)(param_1 + 0x848) = 0;
        FUN_0064ae10(*(undefined4 *)(param_1 + 8), 0xd);
        return;
    }
    *(undefined4 *)(param_1 + 0x304) = 0xffffffff;
    return;
}
