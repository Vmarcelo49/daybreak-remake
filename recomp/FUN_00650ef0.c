// ============================================
// Address:  0x00650ef0
// Original: FUN_00650ef0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00650ef0(undefined4 param_1)

{
    char cVar1;

    DAT_006d171c = (uint)(DAT_006d171c == 0);
    cVar1        = FUN_00650de0(param_1);
    if (cVar1 == '\0')
    {
        DAT_006d171c = (uint)(DAT_006d171c == 0);
    }
    else
    {
        ShowCursor(DAT_006d171c);
    }
    return;
}
