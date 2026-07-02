// ============================================
// Address:  0x00653960
// Original: FUN_00653960
// Status:   unreviewed
// ============================================

void __thiscall FUN_00653960(undefined4 *param_1, LONG param_2, DWORD param_3)

{
    if (param_1[0x1f] == 0)
    {
        SetFilePointer((HANDLE)*param_1, param_2, (PLONG)0x0, param_3);
    }
    else
    {
        FUN_006630f0(param_2, param_3);
    }
    return;
}
