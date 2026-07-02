// ============================================
// Address:  0x00667a30
// Original: FUN_00667a30
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_00667a30(int param_1, undefined4 param_2, undefined4 param_3)

{
    int iVar1;
    undefined4 uVar2;
    int *local_30;
    undefined4 local_2c;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 local_1c;
    undefined4 local_8;

    local_8 = DAT_006b77f4;
    _memset(&local_2c, 0, 0x24);
    local_2c = 0x24;
    local_28 = 0x58080;
    local_24 = param_3;
    local_1c = param_2;
    local_30 = (int *)0x0;
    iVar1    = (**(code **)(*DAT_006d8424 + 0xc))(DAT_006d8424, &local_2c, &local_30, 0);
    if (iVar1 < 0)
    {
        FUN_00661cf0(&DAT_006ab1bc);
        uVar2 = 0;
    }
    else
    {
        iVar1 = (**(code **)*local_30)(local_30, &DAT_006ab874, param_1 + 4);
        (**(code **)(*local_30 + 8))(local_30);
        if (iVar1 < 0)
        {
            FUN_00661cf0(&DAT_006ab1dc);
            uVar2 = 0;
        }
        else
        {
            uVar2 = 1;
        }
    }
    return uVar2;
}
