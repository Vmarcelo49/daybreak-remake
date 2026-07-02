// ============================================
// Address:  0x0065d6a0
// Original: FUN_0065d6a0
// Suggested: LeaveGameCriticalSection (confidence: high)
// Status:   suggested — name kept as comment until reviewed
// ============================================

void __fastcall FUN_0065d6a0(int param_1)

{
    LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 4));
    return;
}
