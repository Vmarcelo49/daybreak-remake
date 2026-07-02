// ============================================
// Address:  0x006932d0
// Original: FUN_006932d0
// Status:   unreviewed
// ============================================

undefined4 FUN_006932d0(void)

{
    BOOL BVar1;
    undefined4 uVar2;
    _OSVERSIONINFOA local_9c;

    local_9c.dwOSVersionInfoSize = 0x94;
    BVar1                        = GetVersionExA(&local_9c);
    if ((BVar1 == 0) || ((local_9c.dwMajorVersion < 6 &&
                          ((local_9c.dwMajorVersion != 5 || (local_9c.dwMinorVersion == 0))))))
    {
        uVar2 = 0;
    }
    else
    {
        uVar2 = 1;
    }
    return uVar2;
}
