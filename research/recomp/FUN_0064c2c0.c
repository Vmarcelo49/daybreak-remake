// ============================================
// Address:  0x0064c2c0
// Original: FUN_0064c2c0
// Status:   unreviewed
// ============================================

int __fastcall FUN_0064c2c0(int param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069eb82;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0065d610();
    local_8 = 0;
    FUN_004248f0();
    local_8._0_1_ = 1;
    FUN_004248f0();
    local_8._0_1_ = 2;
    FUN_004248f0();
    local_8 = CONCAT31(local_8._1_3_, 3);
    FUN_0064c690();
    FUN_0064c6b0();
    _vector_constructor_iterator_((void *)(param_1 + 0x2d4), 0x20, 4, FUN_0063f620);
    _vector_constructor_iterator_((void *)(param_1 + 0x354), 0x1c, 4, FUN_0063f4a0);
    _vector_constructor_iterator_((void *)(param_1 + 0x3c4), 0xc, 4, FUN_0063f530);
    _vector_constructor_iterator_((void *)(param_1 + 0x3f4), 0x10, 4, FUN_0063f430);
    _vector_constructor_iterator_((void *)(param_1 + 0x434), 0xc, 0x24, FUN_0063f590);
    _vector_constructor_iterator_((void *)(param_1 + 0x5e4), 0x18, 4, FUN_0063f240);
    _vector_constructor_iterator_((void *)(param_1 + 0x644), 0x10, 4, FUN_0063f3c0);
    _vector_constructor_iterator_((void *)(param_1 + 0x684), 0x10, 4, FUN_0063f2e0);
    _vector_constructor_iterator_((void *)(param_1 + 0x6c4), 0x10, 4, FUN_0063f350);
    _vector_constructor_iterator_((void *)(param_1 + 0x704), 0xc, 4, FUN_0063f720);
    _vector_constructor_iterator_((void *)(param_1 + 0x734), 0xc, 4, FUN_0063f7a0);
    _vector_constructor_iterator_((void *)(param_1 + 0x764), 0xc, 4, FUN_0063f820);
    _vector_constructor_iterator_((void *)(param_1 + 0x794), 0xc, 4, FUN_0063f880);
    FUN_0063f8e0();
    FUN_0063f950();
    FUN_00417750();
    _vector_constructor_iterator_((void *)(param_1 + 0x7f8), 0xa0, 7, FUN_00403a70);
    FUN_00403a70();
    _vector_constructor_iterator_((void *)(param_1 + 0xcf8), 0xa0, 4, FUN_00403a70);
    _vector_constructor_iterator_((void *)(param_1 + 0xf7c), 0xa0, 3, FUN_00403a70);
    _vector_constructor_iterator_((void *)(param_1 + 0x115c), 0xa0, 2, FUN_00403a70);
    FUN_00403a70();
    FUN_00403a70();
    _vector_constructor_iterator_((void *)(param_1 + 0x140c), 0xb74, 4, FUN_0064c6d0);
    FUN_00403a70();
    FUN_00403a70();
    FUN_00403a70();
    _vector_constructor_iterator_((void *)(param_1 + 0x4434), 4, 10, FUN_00425ac0);
    _vector_constructor_iterator_((void *)(param_1 + 0x445c), 4, 10, FUN_00425ac0);
    _vector_constructor_iterator_((void *)(param_1 + 0x4484), 4, 4, FUN_00425ac0);
    FUN_00425ac0();
    _eh_vector_constructor_iterator_(
        (void *)(param_1 + 0x44b8), 0x160, 4, FUN_00632c30, FUN_00632cc0);
    ExceptionList = local_10;
    return param_1;
}
