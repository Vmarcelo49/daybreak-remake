// ============================================
// Address:  0x00647d60
// Original: FUN_00647d60
// Status:   unreviewed
// ============================================

void __fastcall FUN_00647d60(int param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    int local_8;

    puStack_c     = &LAB_0069e88e;
    local_10      = ExceptionList;
    local_8       = 3;
    ExceptionList = &local_10;
    FUN_00645820();
    local_8._0_1_ = 2;
    FUN_0065af50();
    local_8._0_1_ = 1;
    FUN_0042ea20();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_0064c600();
    local_8 = 0xffffffff;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x63c), 100, 4, FUN_00657320);
    ExceptionList = local_10;
    return;
}
