// ============================================
// Address:  0x00687190
// Original: FUN_00687190
// Status:   unreviewed
// ============================================

bool FUN_00687190(void *param_1, void *param_2)

{
    int iVar1;

    iVar1 = _memcmp(param_1, param_2, 0x10);
    return iVar1 == 0;
}
