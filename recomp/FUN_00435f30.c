// ============================================
// Address:  0x00435f30
// Original: FUN_00435f30
// Status:   unreviewed
// ============================================

void FUN_00435f30(undefined4 param_1, undefined4 param_2, undefined4 param_3)

{
    undefined4 uVar1;
    int iVar2;
    void *pvStack_10;
    undefined1 *puStack_c;
    int local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e5a1;
    pvStack_10    = ExceptionList;
    ExceptionList = &pvStack_10;
    uVar1         = FUN_00667580(1);
    local_8       = 0;
    iVar2         = FUN_00410cf0(0xc, uVar1);
    local_8._0_1_ = 1;
    if (iVar2 != 0)
    {
        FUN_00654220(param_1, param_2, param_3);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00435fcd();
    return;
}
