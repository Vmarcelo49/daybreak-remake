// ============================================
// Address:  0x00646cf0
// Original: FUN_00646cf0
// Status:   unreviewed
// ============================================

/* WARNING: Removing unreachable block (ram,0x00646d6b) */

void __thiscall FUN_00646cf0(int param_1, int param_2, float param_3, undefined4 param_4)

{
    uint uVar1;
    undefined4 local_8;

    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        uVar1 = (uint) * (byte *)(param_1 + 0xdf6 + param_2 * 9 + local_8);
        FUN_00655830((float)local_8 * 12.0 + param_3, param_4, uVar1 & 0x8000000f, (int)uVar1 >> 4);
    }
    return;
}
