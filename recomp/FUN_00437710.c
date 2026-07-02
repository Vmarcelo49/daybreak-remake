// ============================================
// Address:  0x00437710
// Original: FUN_00437710
// Status:   unreviewed
// ============================================

undefined4 FUN_00437710(undefined4 param_1,
                        undefined4 param_2,
                        undefined4 param_3,
                        undefined4 param_4,
                        undefined4 param_5)

{
    undefined4 uVar1;
    uint uVar2;
    undefined4 *puVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined1 local_44[8];
    undefined1 local_3c[8];
    undefined1 local_34[8];
    undefined1 local_2c[8];
    undefined1 local_24[8];
    undefined1 local_1c[8];
    undefined1 local_14[8];
    uint local_c;
    int local_8;

    uVar1   = FUN_00425ae0(local_14);
    local_c = FUN_00433aa0(uVar1);
    local_8 = FUN_00433aa0(&param_2);
    puVar3  = &param_4;
    FUN_00425150(local_1c);
    uVar2 = FUN_00433aa0(puVar3);
    if (local_c < uVar2)
    {
        uVar1  = param_2;
        uVar4  = param_3;
        uVar5  = param_4;
        uVar6  = param_5;
        puVar3 = (undefined4 *)FUN_00425ae0(local_24);
        FUN_00438140(local_2c, *puVar3, puVar3[1], uVar1, uVar4, uVar5, uVar6);
        for (; local_8 != 0; local_8 = local_8 + -1)
        {
            FUN_00437ea0();
        }
    }
    else
    {
        uVar1  = param_2;
        uVar4  = param_3;
        puVar3 = (undefined4 *)FUN_00425150(local_34);
        FUN_00438190(local_3c, param_4, param_5, *puVar3, puVar3[1], uVar1, uVar4);
        for (; local_8 != 0; local_8 = local_8 + -1)
        {
            FUN_0041b8e0();
        }
    }
    uVar1 = param_1;
    uVar2 = local_c;
    FUN_00425ae0(local_44);
    FUN_004372b0(uVar1, uVar2);
    return param_1;
}
