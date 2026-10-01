// ============================================
// Address:  0x00695ea0
// Original: FUN_00695ea0
// Status:   unreviewed
// ============================================

void FUN_00695ea0(int *param_1, undefined8 param_2)

{
    undefined4 extraout_var;

    FUN_0068d950(param_1[0xd]);
    *(undefined8 *)(param_1 + 10) = param_2;
    FUN_0068d9a0(extraout_var);
    (**(code **)(*param_1 + 0x58))();
    return;
}
