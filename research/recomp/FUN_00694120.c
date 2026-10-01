// ============================================
// Address:  0x00694120
// Original: FUN_00694120
// Status:   unreviewed
// ============================================

void __fastcall FUN_00694120(int param_1)

{
    void *pvVar1;
    undefined4 local_8;

    local_8 = *(void **)(param_1 + 8);
    while (local_8 != (void *)0x0)
    {
        pvVar1 = (void *)FUN_0068dc80();
        _free(local_8);
        local_8 = pvVar1;
    }
    return;
}
