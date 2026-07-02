// ============================================
// Address:  0x0068cd10
// Original: FUN_0068cd10
// Status:   unreviewed
// ============================================

void __fastcall FUN_0068cd10(int param_1)

{
    if (*(int *)(param_1 + 0x34) != 0)
    {
        ReleaseSemaphore(*(HANDLE *)(param_1 + 0x30), *(LONG *)(param_1 + 0x34), (LPLONG)0x0);
        *(undefined4 *)(param_1 + 0x34) = 0;
    }
    return;
}
