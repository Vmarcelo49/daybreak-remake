// ============================================
// Address:  0x004177c0
// Original: FUN_004177c0
// Status:   unreviewed
// ============================================

undefined1 *__thiscall FUN_004177c0(int param_1, undefined1 *param_2)

{
    int local_c;
    undefined1 *local_8;

    *param_2 = 0xc;
    local_8  = param_2 + 1;
    for (local_c = 0; local_c < 4; local_c = local_c + 1)
    {
        *local_8   = *(undefined1 *)(param_1 + 8 + local_c * 4);
        local_8[1] = *(undefined1 *)(param_1 + 0x18 + local_c * 4);
        local_8[2] = *(undefined1 *)(param_1 + 0x28 + local_c * 4);
        local_8[3] = *(undefined1 *)(param_1 + 0x38 + local_c * 4);
        local_8[4] = *(undefined1 *)(param_1 + 0x48 + local_c * 4);
        local_8[5] = *(undefined1 *)(param_1 + 0x58 + local_c * 4);
        local_8    = local_8 + 6;
    }
    *local_8                     = *(undefined1 *)(param_1 + 0x68);
    *(undefined2 *)(local_8 + 1) = *(undefined2 *)(param_1 + 0x6c);
    *(undefined2 *)(local_8 + 3) = *(undefined2 *)(param_1 + 0x70);
    *(undefined2 *)(local_8 + 5) = *(undefined2 *)(param_1 + 0x74);
    *(undefined2 *)(local_8 + 7) = *(undefined2 *)(param_1 + 0x78);
    *(undefined2 *)(local_8 + 9) = *(undefined2 *)(param_1 + 0x7c);
    return local_8 + (0xb - (int)param_2);
}
