// ============================================
// Address:  0x00690900
// Original: FUN_00690900
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00690900(int param_1)

{
    DWORD DVar1;

    DVar1                       = timeGetTime();
    *(DWORD *)(param_1 + 0x158) = DVar1 - *(int *)(param_1 + 0x158);
    return 0;
}
