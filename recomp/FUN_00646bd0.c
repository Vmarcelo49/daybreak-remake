// ============================================
// Address:  0x00646bd0
// Original: FUN_00646bd0
// Status:   unreviewed
// ============================================

/* WARNING: Removing unreachable block (ram,0x00646cad) */

void __thiscall
FUN_00646bd0(int param_1, int param_2, float param_3, undefined4 param_4, char param_5)

{
    uint uVar1;
    undefined4 local_8;

    if (param_5 == '\0')
    {
        FUN_004082f0(0xffffffff);
        FUN_004082f0(0xffffffff);
    }
    else
    {
        FUN_004082f0(*(undefined4 *)(param_1 + 0xe40 + param_2 * 4));
        FUN_004082f0(*(undefined4 *)(param_1 + 0xe40 + param_2 * 4));
    }
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
    {
        uVar1 = (uint) * (byte *)(param_1 + 0xdf6 + param_2 * 9 + local_8);
        FUN_00655830((float)local_8 * 24.0 + param_3, param_4, uVar1 & 0x8000000f, (int)uVar1 >> 4);
    }
    return;
}
