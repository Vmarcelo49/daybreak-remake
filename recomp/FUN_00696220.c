// ============================================
// Address:  0x00696220
// Original: FUN_00696220
// Status:   unreviewed
// ============================================

void FUN_00696220(int *param_1, undefined8 param_2)

{
    FUN_0068d980();
    *(undefined8 *)(param_1 + 0xc) = param_2;
    FUN_0068d9c0();
    (**(code **)(*param_1 + 0x50))();
    return;
}
