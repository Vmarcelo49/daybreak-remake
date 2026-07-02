// ============================================
// Address:  0x00691c80
// Original: FUN_00691c80
// Status:   unreviewed
// ============================================

undefined4 FUN_00691c80(undefined4 param_1, uint param_2, undefined4 param_3)

{
    undefined4 local_8;

    if (param_2 < 0x80000000)
    {
        local_8 = FUN_00691cc0(param_1, param_2, param_3);
    }
    else
    {
        local_8 = 0x80070057;
    }
    return local_8;
}
