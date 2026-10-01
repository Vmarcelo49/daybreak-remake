// ============================================
// Address:  0x0063edc0
// Original: FUN_0063edc0
// Status:   unreviewed
// ============================================

void __thiscall FUN_0063edc0(int param_1, int param_2)

{
    *(undefined1 *)(param_1 + 8) = *(undefined1 *)(param_2 + 1);
    *(float *)(param_1 + 0xc)    = (float)(int)*(short *)(param_2 + 2) / 100.0;
    *(float *)(param_1 + 0x10)   = (float)(int)*(short *)(param_2 + 4) / 100.0;
    *(float *)(param_1 + 0x14)   = (float)(int)*(short *)(param_2 + 6) / 100.0;
    *(float *)(param_1 + 0x18)   = (float)(int)*(short *)(param_2 + 8);
    *(float *)(param_1 + 0x1c)   = (float)(int)*(short *)(param_2 + 10) / 100.0;
    return;
}
