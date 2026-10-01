// ============================================
// Address:  0x0065d6a0
// Original: FUN_0065d6a0
// Name:     LeaveGameCriticalSection (status: reviewed)
// ============================================

void __fastcall LeaveGameCriticalSection(int param_1)

{
    LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 4));
    return;
}
