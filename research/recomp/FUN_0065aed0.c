// ============================================
// Address:  0x0065aed0
// Original: FUN_0065aed0
// Status:   unreviewed
// ============================================

int __fastcall FUN_0065aed0(int param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069effe;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0065a460();
    local_8 = 0;
    FUN_006679a0();
    local_8._0_1_ = 1;
    FUN_006675d0();
    local_8 = CONCAT31(local_8._1_3_, 2);
    FUN_00425ac0();
    std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x5c));
    ExceptionList = local_10;
    return param_1;
}
