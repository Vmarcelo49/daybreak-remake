// ============================================
// Address:  0x0065cfa0
// Original: FUN_0065cfa0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0065cfa0(undefined4 param_1)

{
    float10 fVar1;
    int local_8;

    for (local_8 = 0; local_8 < 0xe10; local_8 = local_8 + 1)
    {
        fVar1 = (float10)FUN_0066cd04((((double)local_8 / 10.0) * 3.1415926535) / 180.0);
        *(float *)(&DAT_006d3b90 + local_8 * 4) = (float)fVar1;
    }
    FUN_0065d0c0();
    return param_1;
}
