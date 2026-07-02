// ============================================
// Address:  0x00421100
// Original: FUN_00421100
// Status:   unreviewed
// ============================================

void __thiscall FUN_00421100(int param_1, undefined4 param_2)

{
    undefined4 uVar1;
    undefined4 *puVar2;

    *(undefined4 *)(param_1 + 0xadf8) = param_2;
    *(undefined4 *)(param_1 + 0xadf4) = param_2;
    *(undefined4 *)(param_1 + 0xadfc) = 0;
    *(undefined4 *)(param_1 + 0xae08) = 0;
    *(undefined4 *)(param_1 + 0xae04) = 0;
    uVar1                             = *(undefined4 *)(param_1 + 0xadfc);
    FUN_004244e0(*(undefined4 *)(param_1 + 0xadf4));
    uVar1                           = FUN_00424370(uVar1);
    *(undefined4 *)(param_1 + 0x10) = uVar1;
    puVar2                          = (undefined4 *)FUN_004244e0(*(undefined4 *)(param_1 + 0xadf8));
    FUN_00421410(0, *puVar2);
    puVar2 = (undefined4 *)FUN_004244e0(*(undefined4 *)(param_1 + 0xadf4));
    FUN_00421410(1, *puVar2);
    return;
}
