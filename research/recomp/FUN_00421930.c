// ============================================
// Address:  0x00421930
// Original: FUN_00421930
// Status:   unreviewed
// ============================================

int __fastcall FUN_00421930(int param_1)

{
    return *(int *)(*(int *)(param_1 + 0x23c) + 0x43c4 + **(int **)(param_1 + 0xc) * 4) -
           *(int *)(*(int *)(param_1 + 0xc) + 4);
}
