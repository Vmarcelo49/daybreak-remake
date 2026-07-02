// ============================================
// Address:  0x00697b00
// Original: FUN_00697b00
// Status:   unreviewed
// ============================================

/* WARNING: Removing unreachable block (ram,0x00697c4a) */
/* WARNING: Removing unreachable block (ram,0x00697cdb) */

undefined4 __thiscall
FUN_00697b00(int param_1, undefined4 param_2, undefined4 param_3, int *param_4)

{
    int iVar1;
    undefined4 *puVar2;
    longlong lVar3;
    longlong lVar4;
    undefined4 uVar5;
    undefined1 local_58[12];
    undefined4 local_4c;
    undefined1 local_48[12];
    undefined4 local_3c;
    undefined1 local_38[12];
    undefined4 local_2c;
    undefined4 local_28;
    int local_18;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fe71;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 8);
    local_8 = 0;
    FUN_0068d8f0(param_2, param_3);
    local_18 = 0;
    iVar1    = FUN_00699fc0();
    if (0 < iVar1)
    {
        local_28 = FUN_0068de10();
        local_18 = FUN_006981f0(local_28);
    }
    local_14 = 0;
    iVar1    = FUN_00699fc0();
    if (0 < iVar1)
    {
        local_2c = FUN_0068de10();
        local_14 = FUN_006981f0(local_2c);
    }
    if (local_14 != 0)
    {
        uVar5  = 0;
        puVar2 = (undefined4 *)FUN_006981a0(local_38);
        iVar1  = FUN_00698090(*puVar2, puVar2[1], uVar5);
        if (iVar1 != 0)
        {
            (**(code **)(*(int *)(local_14 + 0xc) + 4))(local_14 + 0xc);
            *param_4 = local_14;
            local_3c = 0;
            local_8  = 0xffffffff;
            FUN_0068d9a0();
            ExceptionList = local_10;
            return local_3c;
        }
    }
    if (local_18 != 0)
    {
        FUN_006981a0(local_48);
        lVar3 = FUN_00697fc0();
        lVar4 = FUN_00697fc0();
        if (lVar3 <= lVar4)
        {
            (**(code **)(*(int *)(local_14 + 0xc) + 4))(local_14 + 0xc);
            *param_4 = local_18;
            local_4c = 0;
            local_8  = 0xffffffff;
            FUN_0068d9a0();
            ExceptionList = local_10;
            return local_4c;
        }
    }
    if ((*(int *)(param_1 + 100) != 0) && (local_14 != 0))
    {
        FUN_00697ee0(param_1 + 0x68);
        FUN_006981a0(local_58);
        lVar3 = FUN_00697fc0();
        lVar4 = FUN_00697fc0();
        if (lVar3 <= lVar4)
        {
            *param_4 = local_14;
            local_8  = 0xffffffff;
            FUN_0068d9a0();
            ExceptionList = local_10;
            return 0;
        }
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return 0x80040216;
}
