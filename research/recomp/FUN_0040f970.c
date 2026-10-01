// ============================================
// Address:  0x0040f970
// Original: FUN_0040f970
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_0040f970(int param_1)

{
    int local_118;
    CHAR local_114[268];
    undefined4 local_8;

    local_8 = DAT_006b77f4;
    for (local_118 = 0; local_118 < 6; local_118 = local_118 + 1)
    {
        FUN_0040fc10();
        *(int *)(param_1 + 0x740 + local_118 * 4) = local_118;
    }
    if (DAT_006cfbc4 < '\0')
    {
        wsprintfA(local_114, "data/scenario/prologue.txt");
    }
    else
    {
        wsprintfA(local_114,
                  "data/scenario/D%02d-%01d.txt",
                  (int)(char)(&DAT_006cfbc7)[DAT_006cfbc4],
                  (int)DAT_006cfbc5);
    }
    FUN_0065e500(local_114, 0);
    FUN_0040f4c0();
    return;
}
