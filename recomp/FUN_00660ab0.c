// ============================================
// Address:  0x00660ab0
// Original: FUN_00660ab0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00660ab0(undefined4 *param_1)

{
    LONG LVar1;

    LVar1 = ImmGetCompositionStringA((HIMC)*param_1, 0x200, (LPVOID)0x0, 0);
    if (LVar1 != 0)
    {
        FUN_00660b50();
    }
    LVar1 = ImmGetCompositionStringA((HIMC)*param_1, 8, param_1 + 0x202, 0xff);
    *(undefined1 *)((int)param_1 + LVar1 + 0x808) = 0;
    ImmGetCompositionStringA((HIMC)*param_1, 0x10, param_1 + 0x242, 0xff);
    ImmGetCompositionStringA((HIMC)*param_1, 0x80, (LPVOID)0x0, 0);
    *(undefined1 *)((int)param_1 + 0xa0e) = 1;
    return;
}
