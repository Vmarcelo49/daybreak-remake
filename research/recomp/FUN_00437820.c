// ============================================
// Address:  0x00437820
// Original: FUN_00437820
// Status:   unreviewed
// ============================================

void __thiscall
FUN_00437820(int param_1, undefined4 param_2, undefined4 param_3, uint param_4, undefined4 *param_5)

{
    undefined4 uVar1;
    undefined4 *puVar2;
    undefined4 *puVar3;
    undefined1 auStack_11c[8];
    undefined1 auStack_114[8];
    undefined1 auStack_10c[8];
    undefined1 auStack_104[8];
    undefined1 auStack_fc[8];
    undefined1 auStack_f4[8];
    undefined1 auStack_ec[8];
    undefined1 auStack_e4[8];
    undefined1 auStack_dc[8];
    undefined1 auStack_d4[8];
    undefined1 auStack_cc[8];
    undefined1 auStack_c4[8];
    undefined1 local_bc[8];
    undefined1 local_b4[8];
    undefined1 local_ac[8];
    undefined1 local_a4[8];
    undefined1 local_9c[8];
    undefined1 local_94[8];
    undefined1 local_8c[8];
    undefined1 local_84[8];
    undefined1 local_7c[8];
    undefined1 local_74[8];
    undefined1 local_6c[8];
    undefined1 local_64[8];
    undefined1 local_5c[8];
    undefined1 local_54[8];
    undefined4 uStack_4c;
    undefined4 uStack_48;
    undefined4 uStack_44;
    undefined4 uStack_40;
    undefined4 local_3c;
    undefined4 local_38;
    undefined4 local_34;
    undefined4 local_30;
    uint local_2c;
    uint local_28;
    uint local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    undefined1 *local_14;
    void *pvStack_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e610;
    pvStack_10    = ExceptionList;
    local_14      = &stack0xfffffe68;
    ExceptionList = &pvStack_10;
    FUN_0040fbd0();
    uVar1    = FUN_00425ae0(local_54);
    local_2c = FUN_00433aa0(uVar1);
    local_28 = *(int *)(param_1 + 0x10) - local_2c;
    local_18 = *(undefined4 *)(param_1 + 0x10);
    if (local_2c < local_28)
    {
        local_8 = 0;
        if (local_2c < param_4)
        {
            for (local_24 = param_4 - local_2c; local_24 != 0; local_24 = local_24 + -1)
            {
                FUN_00437130(param_5);
            }
            for (local_24 = local_2c; local_24 != 0; local_24 = local_24 - 1)
            {
                FUN_00425ae0(local_5c);
                uVar1 = FUN_00438050(param_4 - 1);
                FUN_00437130(uVar1);
            }
            FUN_00425ae0(local_64);
            puVar2   = (undefined4 *)FUN_004372b0(local_6c, param_4);
            local_20 = *puVar2;
            local_1c = puVar2[1];
            puVar2   = (undefined4 *)FUN_004372b0(local_74, local_2c);
            FUN_004381e0(local_20, local_1c, *puVar2, puVar2[1], param_5);
        }
        else
        {
            for (local_24 = param_4; local_24 != 0; local_24 = local_24 - 1)
            {
                FUN_00425ae0(local_7c);
                uVar1 = FUN_00438050(param_4 - 1);
                FUN_00437130(uVar1);
            }
            FUN_00425ae0(local_84);
            puVar2   = (undefined4 *)FUN_004372b0(local_8c, param_4);
            local_20 = *puVar2;
            local_1c = puVar2[1];
            local_3c = *param_5;
            local_38 = param_5[1];
            local_34 = param_5[2];
            local_30 = param_5[3];
            puVar2   = (undefined4 *)FUN_004372b0(local_94, local_2c);
            puVar3   = (undefined4 *)FUN_004372b0(local_9c, param_4);
            FUN_00438190(local_a4, *puVar3, puVar3[1], *puVar2, puVar2[1], local_20, local_1c);
            puVar2 = (undefined4 *)FUN_004372b0(local_ac, local_2c);
            FUN_00425ae0(local_b4);
            puVar3 = (undefined4 *)FUN_004372b0(local_bc, local_2c);
            FUN_004381e0(*puVar3, puVar3[1], *puVar2, puVar2[1], &local_3c);
        }
        FUN_00437b56();
        return;
    }
    local_8 = 2;
    if (local_28 < param_4)
    {
        for (local_24 = param_4 - local_28; local_24 != 0; local_24 = local_24 + -1)
        {
            FUN_00437f40(param_5);
        }
        for (local_24 = 0; local_24 < local_28; local_24 = local_24 + 1)
        {
            FUN_00425ae0(auStack_c4);
            uVar1 = FUN_00438050(local_2c + local_24);
            FUN_00437f40(uVar1);
        }
        FUN_00425ae0(auStack_cc);
        puVar2   = (undefined4 *)FUN_004372b0(auStack_d4, local_2c);
        local_20 = *puVar2;
        local_1c = puVar2[1];
        puVar2   = (undefined4 *)FUN_004372b0(auStack_dc, local_28);
        FUN_004381e0(local_20, local_1c, *puVar2, puVar2[1], param_5);
    }
    else
    {
        for (local_24 = 0; local_24 < param_4; local_24 = local_24 + 1)
        {
            FUN_00425ae0(auStack_e4);
            uVar1 = FUN_00438050(((local_2c + local_28) - param_4) + local_24);
            FUN_00437f40(uVar1);
        }
        FUN_00425ae0(auStack_ec);
        puVar2    = (undefined4 *)FUN_004372b0(auStack_f4, local_2c);
        local_20  = *puVar2;
        local_1c  = puVar2[1];
        uStack_4c = *param_5;
        uStack_48 = param_5[1];
        uStack_44 = param_5[2];
        uStack_40 = param_5[3];
        puVar2    = (undefined4 *)FUN_004372b0(auStack_fc, local_28);
        FUN_004372b0(auStack_104, local_28);
        puVar3 = (undefined4 *)FUN_004250e0(auStack_10c, param_4);
        FUN_00438140(auStack_114, local_20, local_1c, *puVar3, puVar3[1], *puVar2, puVar2[1]);
        puVar2 = (undefined4 *)FUN_004372b0(auStack_11c, param_4);
        FUN_004381e0(local_20, local_1c, *puVar2, puVar2[1], &uStack_4c);
    }
    FUN_00437e24();
    return;
}
