// ============================================
// Address:  0x0064e710
// Original: FUN_0064e710
// Status:   unreviewed
// ============================================

int __thiscall FUN_0064e710(int param_1, undefined4 param_2)

{
    undefined4 local_14;

    local_14 = D3DXFrameFind(*(undefined4 *)(param_1 + 8), param_2);
    if (local_14 == 0)
    {
        local_14 = 0;
    }
    else
    {
        local_14 = local_14 + -0x10;
    }
    if (local_14 == 0)
    {
        local_14 = 0;
    }
    else
    {
        local_14 = local_14 + 0x14;
    }
    return local_14;
}
