// ============================================
// Address:  0x00653e80
// Original: FUN_00653e80
// Status:   unreviewed
// ============================================

void FUN_00653e80(void)

{
    undefined4 uVar1;
    undefined4 local_1c;
    int local_18;
    undefined1 *local_14;
    void *pvStack_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069ed00;
    pvStack_10    = ExceptionList;
    local_14      = &stack0xffffffcc;
    ExceptionList = &pvStack_10;
    local_1c      = FUN_00667580(1);
    local_18      = 0;
    local_8       = 0;
    uVar1         = FUN_00663590(local_1c);
    FUN_00426480(uVar1, &local_1c);
    local_18 = local_18 + 1;
    uVar1    = FUN_00653df0(local_1c);
    FUN_00426480(uVar1, &local_1c);
    FUN_00653f44();
    return;
}
