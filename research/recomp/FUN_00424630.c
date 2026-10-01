// ============================================
// Address:  0x00424630
// Original: FUN_00424630
// Status:   unreviewed
// ============================================

int FUN_00424630(void)

{
    undefined4 uVar1;
    undefined4 uStack_10;
    int local_c;

    std::allocator<char>::allocator<char>((allocator<char> *)&uStack_10);
    FUN_00425760();
    uStack_10                    = 0x424651;
    uVar1                        = FUN_00425610();
    *(undefined4 *)(local_c + 4) = uVar1;
    *(undefined4 *)(local_c + 8) = 0;
    return local_c;
}
