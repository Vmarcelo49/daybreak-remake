// ============================================
// Address:  0x006934d0
// Original: FUN_006934d0
// Status:   unreviewed
// ============================================

undefined4 FUN_006934d0(char *param_1, int param_2, char *param_3, va_list param_4)

{
    uint _Count;
    uint uVar1;
    undefined4 local_8;

    local_8 = 0;
    if (param_2 == 0)
    {
        local_8 = 0x80070057;
    }
    else
    {
        _Count = param_2 - 1;
        uVar1  = __vsnprintf(param_1, _Count, param_3, param_4);
        if (((int)uVar1 < 0) || (_Count < uVar1))
        {
            param_1[_Count] = '\0';
            local_8         = 0x8007007a;
        }
        else if (uVar1 == _Count)
        {
            param_1[_Count] = '\0';
        }
    }
    return local_8;
}
