// ============================================
// Address:  0x006586d0
// Original: FUN_006586d0
// Suggested: IsKeyPressed (confidence: medium)
// Status:   suggested — name kept as comment until reviewed
// ============================================


bool __thiscall FUN_006586d0(int param_1,byte param_2)

{
  return (*(byte *)(param_1 + 0x20 + (uint)param_2) & 0x80) != 0;
}

