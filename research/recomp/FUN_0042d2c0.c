// ============================================
// Address:  0x0042d2c0
// Original: FUN_0042d2c0
// Status:   unreviewed
// ============================================

void __thiscall FUN_0042d2c0(int param_1, int param_2, undefined4 param_3)

{
    allocator<char> local_28[12];
    float local_1c;
    int local_18;
    int local_14;
    undefined1 local_10[4];
    undefined1 local_c[4];
    undefined1 local_8[4];

    local_14 = 0;
    std::allocator<char>::allocator<char>(local_28);
    D3DXVec3Normalize(local_28, param_3);
    for (local_18 = *(int *)(param_2 + 0x44); local_18 != 0; local_18 = *(int *)(local_18 + 0x20))
    {
        D3DXIntersect(*(undefined4 *)(local_18 + 8),
                      param_1 + 0x14,
                      local_28,
                      &local_14,
                      local_10,
                      local_c,
                      local_8,
                      &local_1c,
                      0,
                      0);
        if ((local_14 != 0) && (local_1c < DAT_006c78a4))
        {
            DAT_006c78a4 = local_1c;
        }
    }
    if (*(int *)(param_2 + 0x48) != 0)
    {
        FUN_0042d2c0(*(undefined4 *)(param_2 + 0x48), param_3);
    }
    if (*(int *)(param_2 + 0x4c) != 0)
    {
        FUN_0042d2c0(*(undefined4 *)(param_2 + 0x4c), param_3);
    }
    return;
}
