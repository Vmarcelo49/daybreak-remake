// ============================================
// Address:  0x00664f80
// Original: FUN_00664f80
// Status:   unreviewed
// ============================================

char *__thiscall FUN_00664f80(char *param_1, char param_2)

{
    if ((((param_2 == '\b') || (param_2 == '\x10')) || (param_2 == '\x18')) || (param_2 == ' '))
    {
        *param_1 = param_2;
    }
    else
    {
        *param_1 = '\0';
    }
    param_1[0x18] = '\0';
    param_1[0x19] = '\0';
    param_1[0x1a] = '\0';
    param_1[0x1b] = '\0';
    param_1[0x14] = '\0';
    param_1[0x15] = '\0';
    param_1[0x16] = '\0';
    param_1[0x17] = '\0';
    param_1[0x10] = '\0';
    param_1[0x11] = '\0';
    param_1[0x12] = '\0';
    param_1[0x13] = '\0';
    return param_1;
}
