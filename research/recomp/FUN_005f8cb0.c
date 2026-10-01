// ============================================
// Address:  0x005f8cb0
// Original: FUN_005f8cb0
// Status:   unreviewed
// ============================================

void __thiscall FUN_005f8cb0(int *param_1,
                             undefined4 param_2,
                             undefined4 param_3,
                             undefined4 param_4,
                             undefined4 param_5,
                             undefined4 param_6,
                             undefined4 param_7,
                             undefined4 param_8)

{
    undefined4 uVar1;
    undefined4 *puVar2;
    undefined4 local_c;
    undefined4 local_8;

    local_8      = DAT_006b7630;
    DAT_006b7630 = param_2;
    FUN_0065d670();
    uVar1   = FUN_00423750(param_4, param_5, param_6);
    local_c = (**(code **)(*param_1 + 8))(param_3, uVar1, param_7, param_8);
    FUN_00435e60(&local_c);
    puVar2 = (undefined4 *)FUN_00667280();
    (**(code **)(*(int *)*puVar2 + 0x10))();
    FUN_0065d6a0();
    DAT_006b7630 = local_8;
    return;
}
