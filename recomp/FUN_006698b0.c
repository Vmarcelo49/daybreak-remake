// ============================================
// Address:  0x006698b0
// Original: FUN_006698b0
// Status:   unreviewed
// ============================================

undefined4 FUN_006698b0(undefined4 param_1, int *param_2, void *param_3, uint *param_4)

{
    char cVar1;
    undefined4 uVar2;
    void *pvVar3;
    undefined1 local_1c[4];
    int local_18;
    int local_14;
    int local_10;
    undefined4 local_c;
    int local_8;

    cVar1 = FUN_00653540(param_1);
    if (cVar1 == '\0')
    {
        uVar2 = 0;
    }
    else
    {
        _memset(param_3, 0, 0x12);
        FUN_00653760(&local_8, 4);
        if (local_8 == 0x46464952)
        {
            FUN_00653760(local_1c, 4);
            FUN_00653760(&local_18, 4);
            if (local_18 == 0x45564157)
            {
                FUN_00653760(&local_14, 4);
                if (local_14 == 0x20746d66)
                {
                    FUN_00653760(&local_c, 4);
                    FUN_00653760(param_3, local_c);
                    FUN_00653760(&local_10, 4);
                    if (local_10 == 0x61746164)
                    {
                        FUN_00653760(param_4, 4);
                        if (*param_4 == 0)
                        {
                            uVar2 = 0;
                        }
                        else
                        {
                            if (*param_2 != 0)
                            {
                                _free((void *)*param_2);
                            }
                            pvVar3   = operator_new(*param_4);
                            *param_2 = (int)pvVar3;
                            FUN_00653760(*param_2, *param_4);
                            uVar2 = 1;
                        }
                    }
                    else
                    {
                        uVar2 = 0;
                    }
                }
                else
                {
                    uVar2 = 0;
                }
            }
            else
            {
                uVar2 = 0;
            }
        }
        else
        {
            uVar2 = 0;
        }
    }
    return uVar2;
}
