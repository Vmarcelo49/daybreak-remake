// ============================================
// Address:  0x00653cd0
// Original: FUN_00653cd0
// Status:   unreviewed
// ============================================

int FUN_00653cd0(void)

{
    undefined4 uVar1;
    undefined4 uStack_10;
    int local_c;

    std::allocator<char>::allocator<char>((allocator<char> *)&uStack_10);
    FUN_00425760();
    uStack_10                    = 0x653cf1;
    uVar1                        = FUN_00653e80();
    *(undefined4 *)(local_c + 4) = uVar1;
    *(undefined4 *)(local_c + 8) = 0;
    return local_c;
}
