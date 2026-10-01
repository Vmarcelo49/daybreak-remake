// ============================================
// Address:  0x00401b30
// Original: FUN_00401b30
// Status:   unreviewed
// ============================================

void __fastcall FUN_00401b30(int param_1)

{
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
    if (*(int *)(param_1 + 0x1c) != 0)
    {
        FUN_00402040(0, (float)*(uint *)(param_1 + 0x30) / 500.0);
    }
    return;
}
