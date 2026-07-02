// ============================================
// Address:  0x0064fd40
// Original: FUN_0064fd40
// Status:   unreviewed
// ============================================

void FUN_0064fd40(int param_1, int param_2, int param_3)

{
    void *pvStack_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069ec50;
    pvStack_10    = ExceptionList;
    local_8       = 0;
    ExceptionList = &pvStack_10;
    for (; param_1 != param_2; param_1 = param_1 + 4)
    {
        FUN_00432ee0(param_3, param_1);
        param_3 = param_3 + 4;
    }
    FUN_0064fdc7();
    return;
}
