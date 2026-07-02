// ============================================
// Address:  0x00693320
// Original: FUN_00693320
// Status:   unreviewed
// ============================================

bool __thiscall FUN_00693320(undefined4 *param_1, DWORD param_2)

{
    DWORD DVar1;

    DVar1 = WaitForSingleObject((HANDLE)*param_1, param_2);
    return DVar1 == 0;
}
