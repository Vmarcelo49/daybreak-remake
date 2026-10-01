// ============================================
// Address:  0x00418dd0
// Original: FUN_00418dd0
// Status:   unreviewed
// ============================================

void __thiscall FUN_00418dd0(int param_1, int param_2)

{
    int local_c;
    char *local_8;

    *(undefined1 *)(param_1 + 8) = *(undefined1 *)(param_2 + 1);
    local_8                      = (char *)(param_2 + 2);
    for (local_c = 0; local_c < 4; local_c = local_c + 1)
    {
        *(int *)(param_1 + 0xc + local_c * 4)  = (int)*local_8;
        *(int *)(param_1 + 0x1c + local_c * 4) = (int)local_8[1];
        *(int *)(param_1 + 0x2c + local_c * 4) = (int)local_8[2];
        *(int *)(param_1 + 0x3c + local_c * 4) = (int)local_8[3];
        *(int *)(param_1 + 0x4c + local_c * 4) = (int)local_8[4];
        *(int *)(param_1 + 0x5c + local_c * 4) = (int)local_8[5];
        *(char *)(param_1 + local_c + 0x6c)    = local_8[6];
        *(int *)(param_1 + 0x70 + local_c * 4) = (int)local_8[7];
        *(int *)(param_1 + 0x80 + local_c * 4) = (int)local_8[8];
        *(int *)(param_1 + 0x90 + local_c * 4) = (int)local_8[9];
        *(int *)(param_1 + 0xa0 + local_c * 4) = (int)local_8[10];
        *(int *)(param_1 + 0xb0 + local_c * 4) = (int)local_8[0xb];
        *(int *)(param_1 + 0xc0 + local_c * 4) = (int)local_8[0xc];
        local_8                                = local_8 + 0xd;
    }
    return;
}
