// ============================================
// Address:  0x006670b0
// Original: FUN_006670b0
// Status:   unreviewed
// ============================================

BOOL __thiscall FUN_006670b0(undefined4 param_1, int param_2)

{
    char cVar1;
    undefined4 *puVar2;
    int *piVar3;
    undefined1 local_20[4];
    undefined1 local_1c[4];
    undefined1 local_18[4];
    undefined1 local_14[4];
    BOOL local_10;
    undefined4 local_c;
    undefined4 local_8;

    local_10 = 0;
    FUN_004248b0(param_1);
    FUN_004248b0();
    FUN_0065d670();
    puVar2  = (undefined4 *)FUN_00653d10(local_14);
    local_8 = *puVar2;
    puVar2  = (undefined4 *)FUN_00654620(local_18);
    local_c = *puVar2;
    do
    {
        cVar1 = const_iterator__operator__(&local_c);
        if (cVar1 == '\0')
        {
        LAB_0066716c:
            FUN_0065d6a0();
            return local_10;
        }
        piVar3 = (int *)FUN_00653d70();
        if (*piVar3 == param_2)
        {
            puVar2 = (undefined4 *)FUN_00653d70();
            SetEvent((HANDLE)*puVar2);
            puVar2   = (undefined4 *)FUN_00653d70();
            local_10 = CloseHandle((HANDLE)*puVar2);
            FUN_00425500(local_1c, local_8);
            goto LAB_0066716c;
        }
        FUN_0042fc40(local_20, 0);
    } while (true);
}
