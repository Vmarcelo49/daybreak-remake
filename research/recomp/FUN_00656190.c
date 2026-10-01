// ============================================
// Address:  0x00656190
// Original: FUN_00656190
// Status:   unreviewed
// ============================================

undefined4 *__thiscall
FUN_00656190(undefined4 param_1, undefined4 *param_2, undefined4 param_3, undefined4 param_4)

{
    undefined4 *puVar1;
    int iVar2;
    undefined4 local_8;

    FUN_00425ac0(param_1);
    puVar1  = (undefined4 *)FUN_00656680(&local_8);
    *puVar1 = 0;
    iVar2   = FUN_00657170(param_3, param_4, puVar1);
    if (iVar2 < 0)
    {
        FUN_0065a7f0(local_8);
        FUN_00654170(0);
    }
    else
    {
        *param_2 = local_8;
    }
    return param_2;
}
