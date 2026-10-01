// ============================================
// Address:  0x00646db0
// Original: FUN_00646db0
// Status:   unreviewed
// ============================================

/* WARNING: Removing unreachable block (ram,0x00646e12) */

void FUN_00646db0(int param_1, float param_2, undefined4 param_3)

{
    undefined4 local_8;

    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        FUN_00655830((float)local_8 * 12.0 + param_2,
                     param_3,
                     *(byte *)(param_1 + local_8) & 0x8000000f,
                     (int)(uint) * (byte *)(param_1 + local_8) >> 4);
    }
    return;
}
