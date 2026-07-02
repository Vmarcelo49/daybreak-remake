// ============================================
// Address:  0x006586d0
// Original: FUN_006586d0
// Status:   unreviewed
// ============================================


bool __thiscall FUN_006586d0(int param_1,byte param_2)

{
  return (*(byte *)(param_1 + 0x20 + (uint)param_2) & 0x80) != 0;
}

