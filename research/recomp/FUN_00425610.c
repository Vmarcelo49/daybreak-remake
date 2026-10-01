// ============================================
// Address:  0x00425610
// Original: FUN_00425610
// Status:   unreviewed
// ============================================

void FUN_00425610(void)

{
    undefined4 uVar1;
    undefined4 local_1c;
    int local_18;
    undefined1 *local_14;
    void *pvStack_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e2c0;
    pvStack_10    = ExceptionList;
    local_14      = &stack0xffffffcc;
    ExceptionList = &pvStack_10;
    local_1c      = FUN_00426460(1);
    local_18      = 0;
    local_8       = 0;
    uVar1         = FUN_00663590(local_1c);
    FUN_00426480(uVar1, &local_1c);
    local_18 = local_18 + 1;
    uVar1    = FUN_00653df0(local_1c);
    FUN_00426480(uVar1, &local_1c);
    FUN_004256d4();
    return;
}
