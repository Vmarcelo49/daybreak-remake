// ============================================
// Address:  0x00663420
// Original: FUN_00663420
// Status:   unreviewed
// ============================================

void __fastcall FUN_00663420(int param_1)

{
    undefined4 *puVar1;

    puVar1 = (undefined4 *)FUN_00663b30();
    FUN_00663610(*puVar1);
    puVar1                       = (undefined4 *)FUN_00663b30();
    *puVar1                      = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(param_1 + 8) = 0;
    puVar1                       = (undefined4 *)FUN_00663af0();
    *puVar1                      = *(undefined4 *)(param_1 + 4);
    puVar1                       = (undefined4 *)FUN_00663b10();
    *puVar1                      = *(undefined4 *)(param_1 + 4);
    return;
}
