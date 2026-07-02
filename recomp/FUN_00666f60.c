// ============================================
// Address:  0x00666f60
// Original: FUN_00666f60
// Status:   unreviewed
// ============================================

undefined4 FUN_00666f60(void)

{
    char cVar1;
    undefined4 *puVar2;
    undefined1 local_18[4];
    undefined1 local_14[4];
    undefined1 local_10[4];
    undefined4 local_c;
    undefined4 local_8;

    FUN_004248b0();
    FUN_004248b0();
    while (DAT_006d8468 != '\0')
    {
        WaitForSingleObject(DAT_006d844c, DAT_006d8458);
        FUN_0065d670();
        puVar2  = (undefined4 *)FUN_00653d10(local_10);
        local_8 = *puVar2;
        puVar2  = (undefined4 *)FUN_00654620(local_14);
        local_c = *puVar2;
        while (true)
        {
            cVar1 = const_iterator__operator__(&local_c);
            if (cVar1 == '\0')
                break;
            puVar2 = (undefined4 *)FUN_00653d70();
            SetEvent((HANDLE)*puVar2);
            FUN_0042fc40(local_18, 0);
        }
        FUN_0065d6a0();
    }
    return 0;
}
