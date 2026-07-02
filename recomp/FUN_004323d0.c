// ============================================
// Address:  0x004323d0
// Original: FUN_004323d0
// Status:   unreviewed
// ============================================

void __thiscall
FUN_004323d0(undefined4 param_1, uint param_2, uint param_3, undefined4 param_4, undefined1 param_5)

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
            uVar1 = (uint)DAT_006cfd00;
            FUN_00424230(param_2);
            puVar2 = (undefined4 *)FUN_004327d0(param_3);
            FUN_0065b420(*puVar2, uVar1, param_4);
        }
    }
    return;
}
