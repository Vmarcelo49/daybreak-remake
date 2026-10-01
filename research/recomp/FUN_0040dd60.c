// ============================================
// Address:  0x0040dd60
// Original: FUN_0040dd60
// Status:   unreviewed
// ============================================

float10 FUN_0040dd60(float param_1, uint param_2)

{
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;

    if ((int)param_2 < 0)
    {
        local_8 = -param_2;
    }
    else
    {
        local_8 = param_2;
    }
    local_c = 1.0;
    while (true)
    {
        if ((local_8 & 1) != 0)
        {
            local_c = local_c * param_1;
        }
        local_8 = local_8 >> 1;
        if (local_8 == 0)
            break;
        param_1 = param_1 * param_1;
    }
    if ((int)param_2 < 0)
    {
        local_10 = 1.0 / local_c;
    }
    else
    {
        local_10 = local_c;
    }
    return (float10)local_10;
}
