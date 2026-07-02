// ============================================
// Address:  0x00659b70
// Original: FUN_00659b70
// Status:   unreviewed
// ============================================

void __fastcall FUN_00659b70(int param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    int local_8;

    puStack_c     = &LAB_0069ef3c;
    local_10      = ExceptionList;
    local_8       = 2;
    ExceptionList = &local_10;
    _eh_vector_destructor_iterator_(
        (void *)(param_1 + 0x1e0), 0x10, 0x20, std::ctype<char>::~ctype<char>);
    local_8._0_1_ = 1;
    _eh_vector_destructor_iterator_((void *)(param_1 + 0x60), 0xc, 0x20, FUN_006679d0);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_0065a580();
    local_8 = 0xffffffff;
    FUN_0065a4c0();
    ExceptionList = local_10;
    return;
}
