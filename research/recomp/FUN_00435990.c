// ============================================
// Address:  0x00435990
// Original: FUN_00435990
// Status:   unreviewed
// ============================================

void __thiscall FUN_00435990(int *param_1,
                             undefined4 param_2,
                             undefined4 param_3,
                             undefined4 param_4,
                             undefined4 param_5,
                             undefined4 param_6,
                             undefined4 param_7)

{
    undefined4 uVar1;
    undefined4 *puVar2;
    undefined4 local_8;

    FUN_0065d670();
    uVar1   = FUN_00423750(param_3, param_4, param_5);
    local_8 = (**(code **)(*param_1 + 8))(param_2, uVar1, param_6, param_7);
    FUN_00435e60(&local_8);
    puVar2 = (undefined4 *)FUN_00667280();
    (**(code **)(*(int *)*puVar2 + 0x10))();
    FUN_0065d6a0();
    return;
}
