// ============================================
// Address:  0x00667050
// Original: FUN_00667050
// Status:   unreviewed
// ============================================

undefined4 FUN_00667050(void)

{
    HANDLE pvVar1;
    undefined4 *puVar2;
    undefined4 local_8;

    local_8 = 0;
    FUN_0065d670();
    FUN_006672b0(&local_8);
    pvVar1  = CreateEventA((LPSECURITY_ATTRIBUTES)0x0, 0, 0, (LPCSTR)0x0);
    puVar2  = (undefined4 *)FUN_00667280();
    *puVar2 = pvVar1;
    FUN_0065d6a0();
    puVar2 = (undefined4 *)FUN_00667280();
    return *puVar2;
}
