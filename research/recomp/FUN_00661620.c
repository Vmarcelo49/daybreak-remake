// ============================================
// Address:  0x00661620
// Original: FUN_00661620
// Status:   unreviewed
// ============================================

undefined4 FUN_00661620(byte param_1)

{
    undefined4 uVar1;

    if (param_1 < 0x81)
    {
        uVar1 = 0;
    }
    else if (param_1 < 0xa0)
    {
        uVar1 = 1;
    }
    else if (param_1 < 0xe0)
    {
        uVar1 = 0;
    }
    else if (param_1 < 0xff)
    {
        uVar1 = 1;
    }
    else
    {
        uVar1 = 0;
    }
    return uVar1;
}
