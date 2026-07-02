// ============================================
// Address:  0x006331e0
// Original: FUN_006331e0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006331e0(int param_1)

{
    *(undefined4 *)(param_1 + 0x7c) = 0xffffffff;
    *(undefined1 *)(param_1 + 0x94) = 0;
    if (*(char *)(param_1 + 0x95) != '\0')
    {
        *(undefined1 *)(param_1 + 0x95) = 0;
    }
    return;
}
