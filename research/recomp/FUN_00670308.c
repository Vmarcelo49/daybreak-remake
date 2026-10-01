// ============================================
// Address:  0x00670308
// Original: FUN_00670308
// Status:   unreviewed
// ============================================

uint FUN_00670308(undefined4 param_1, uint param_2)

{
    if ((param_2 & 0x7ff00000) != 0x7ff00000)
    {
        return param_2 & 0x7ff00000;
    }
    return param_2;
}
