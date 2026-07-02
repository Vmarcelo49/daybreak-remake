// ============================================
// Address:  0x00664a40
// Original: FUN_00664a40
// Status:   unreviewed
// ============================================

void FUN_00664a40(void)

{
    undefined4 uVar1;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 local_20;
    undefined4 local_1c;
    int local_18;
    undefined1 *local_14;
    void *pvStack_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f2e0;
    pvStack_10    = ExceptionList;
    local_14      = &stack0xffffffbc;
    ExceptionList = &pvStack_10;
    local_1c      = FUN_00664c20(1);
    local_18      = 0;
    local_8       = 0;
    local_20      = 0;
    uVar1         = FUN_00663590(local_1c);
    FUN_00426480(uVar1, &local_20);
    local_18 = local_18 + 1;
    local_24 = 0;
    uVar1    = FUN_00653df0(local_1c);
    FUN_00426480(uVar1, &local_24);
    local_18 = local_18 + 1;
    local_28 = 0;
    uVar1    = FUN_00654020(local_1c);
    FUN_00426480(uVar1, &local_28);
    FUN_00664b68();
    return;
}
