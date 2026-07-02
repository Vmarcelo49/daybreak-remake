// ============================================
// Address:  0x00650f70
// Original: FUN_00650f70
// Status:   unreviewed
// ============================================

uint __fastcall FUN_00650f70(uint param_1)

{
    int iVar1;

    if (*(char *)(param_1 + 0x58) == '\0')
    {
        param_1 = param_1 & 0xffffff00;
    }
    else if (*(char *)(param_1 + 0x59) == '\0')
    {
        FUN_0065d670();
        iVar1 = (**(code **)(*DAT_006d16f8 + 0xa4))(DAT_006d16f8);
        if (iVar1 == 0)
        {
            param_1 = 1;
        }
        else
        {
            param_1 = FUN_0065d6a0();
            param_1 = param_1 & 0xffffff00;
        }
    }
    else
    {
        param_1 = 0;
    }
    return param_1;
}
