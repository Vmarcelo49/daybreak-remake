// ============================================
// Address:  0x004322b0
// Original: FUN_004322b0
// Status:   unreviewed
// ============================================

void __thiscall
FUN_004322b0(undefined4 param_1, uint param_2, uint param_3, undefined4 param_4, undefined1 param_5)

{
    uint uVar1;
    undefined4 *puVar2;

    uVar1 = FUN_0063bf40(param_1);
    if (param_2 < uVar1)
    {
        FUN_00424230(param_2);
        uVar1 = FUN_0063bf40(param_1);
        if (param_3 < uVar1)
        {
            FUN_00432500(param_5);
            FUN_00424230(param_2);
            puVar2 = (undefined4 *)FUN_004327d0(param_3);
            FUN_0065b330(*puVar2, param_4);
        }
    }
    return;
}
