// ============================================
// Address:  0x0063bcf0
// Original: FUN_0063bcf0
// Status:   unreviewed
// ============================================

void __thiscall FUN_0063bcf0(int param_1, int param_2)

{
    *(undefined1 *)(param_1 + 8)   = *(undefined1 *)(param_2 + 1);
    *(undefined2 *)(param_1 + 10)  = *(undefined2 *)(param_2 + 2);
    *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_2 + 4);
    *(float *)(param_1 + 0x10)     = (float)(int)*(short *)(param_2 + 6);
    *(float *)(param_1 + 0x14)     = (float)(int)*(short *)(param_2 + 8);
    *(float *)(param_1 + 0x18)     = (float)(int)*(short *)(param_2 + 10);
    *(float *)(param_1 + 0x1c)     = (float)(int)*(short *)(param_2 + 0xc) / 100.0;
    *(float *)(param_1 + 0x20)     = (float)(int)*(short *)(param_2 + 0xe) / 100.0;
    *(float *)(param_1 + 0x24)     = (float)(int)*(short *)(param_2 + 0x10) / 100.0;
    return;
}
