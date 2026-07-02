// ============================================
// Address:  0x0065d670
// Original: FUN_0065d670
// Name:     EnterGameCriticalSection (status: reviewed)
// ============================================

void __fastcall EnterGameCriticalSection(int param_1)

{
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 4));
    return;
}
