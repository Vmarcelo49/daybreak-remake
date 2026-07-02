// ============================================
// Address:  0x0065d670
// Original: FUN_0065d670
// Suggested: EnterGameCriticalSection (confidence: high)
// Status:   suggested — name kept as comment until reviewed
// ============================================


void __fastcall FUN_0065d670(int param_1)

{
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 4));
  return;
}

