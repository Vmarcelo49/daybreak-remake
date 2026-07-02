// ============================================
// Address:  0x006997e0
// Original: FUN_006997e0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_006997e0(int param_1, undefined8 *param_2, undefined4 param_3)

{
    undefined4 uVar1;
    undefined8 uVar2;

    if (param_2 == (undefined8 *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        uVar2    = (**(code **)(**(int **)(param_1 + 0x18) + 0xc))(param_3);
        *param_2 = uVar2;
        uVar1    = 0;
    }
    return uVar1;
}
