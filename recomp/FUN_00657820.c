// ============================================
// Address:  0x00657820
// Original: FUN_00657820
// Suggested: IsKeyDown (confidence: high)
// Status:   suggested — name kept as comment until reviewed
// ============================================

bool FUN_00657820(byte param_1)

{
    return ((&DAT_006d1928)[param_1] & 0x80) != 0;
}
