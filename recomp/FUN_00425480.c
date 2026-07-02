// ============================================
// Address:  0x00425480
// Original: FUN_00425480
// Status:   unreviewed
// ============================================

void __thiscall FUN_00425480(undefined4 param_1, undefined4 param_2, undefined4 param_3)

{
    undefined4 uVar1;
    undefined4 *puVar2;
    undefined4 uVar3;

    uVar1  = FUN_0068de10(param_1);
    puVar2 = (undefined4 *)FUN_00653df0(uVar1, param_3);
    uVar3  = FUN_00426270(uVar1, *puVar2);
    FUN_004263e0(1);
    puVar2  = (undefined4 *)FUN_00653df0(uVar1);
    *puVar2 = uVar3;
    puVar2  = (undefined4 *)FUN_00653df0(uVar3);
    puVar2  = (undefined4 *)FUN_00663590(*puVar2);
    *puVar2 = uVar3;
    return;
}
