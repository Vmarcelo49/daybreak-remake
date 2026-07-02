// ============================================
// Address:  0x00661ad0
// Original: FUN_00661ad0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_00661ad0(undefined4 *param_1, undefined4 param_2, uint param_3)

{
    HRESULT HVar1;
    undefined4 uVar2;
    int iVar3;
    undefined4 local_2c;
    undefined4 local_28;
    undefined4 local_8;

    local_8  = DAT_006b77f4;
    *param_1 = param_2;
    HVar1    = CoCreateInstance(
        (IID *)&DAT_006ab894, (LPUNKNOWN)0x0, 3, (IID *)&DAT_006ab884, (LPVOID *)(param_1 + 2));
    if (HVar1 < 0)
    {
        FUN_00661cf0(&DAT_006ab04c);
        uVar2 = 0;
    }
    else
    {
        iVar3 = (**(code **)(*(int *)param_1[2] + 0x28))(param_1[2], 0);
        if (iVar3 < 0)
        {
            FUN_00661cf0(&DAT_006ab070);
            uVar2 = 0;
        }
        else
        {
            iVar3 = (**(code **)(*(int *)param_1[2] + 0x18))(param_1[2], param_2, 2);
            if ((iVar3 < 0) &&
                (iVar3 = (**(code **)(*(int *)param_1[2] + 0x18))(param_1[2], param_2, 1),
                 iVar3 < 0))
            {
                FUN_00661cf0(&DAT_006ab098);
                return 0;
            }
            _memset(&local_2c, 0, 0x24);
            local_2c = 0x24;
            if ((param_3 & 1) == 0)
            {
                local_28 = 0x40001;
            }
            else
            {
                local_28 = 0x40011;
            }
            iVar3 = (**(code **)(*(int *)param_1[2] + 0xc))(param_1[2], &local_2c, param_1 + 1, 0);
            if (iVar3 < 0)
            {
                FUN_00661cf0(&DAT_006ab0b0);
                uVar2 = 0;
            }
            else
            {
                if ((param_3 & 1) != 0)
                {
                    (*(code *)**(undefined4 **)param_1[1])(param_1[1], &DAT_006ab864, param_1 + 3);
                    (**(code **)(*(int *)param_1[1] + 8))(param_1[1]);
                }
                uVar2 = 1;
            }
        }
    }
    return uVar2;
}
