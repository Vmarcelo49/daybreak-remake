// ============================================
// Address:  0x00696bc0
// Original: FUN_00696bc0
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00696bc0(undefined4 *param_1,
                                    int *param_2,
                                    undefined4 param_3,
                                    int *param_4,
                                    undefined4 param_5,
                                    undefined8 param_6,
                                    undefined4 param_7,
                                    undefined4 param_8,
                                    short param_9,
                                    undefined4 param_10,
                                    undefined4 param_11,
                                    undefined4 param_12,
                                    undefined4 param_13,
                                    undefined4 param_14)

{
    undefined4 uVar1;
    int iVar2;
    undefined8 uVar3;
    int *local_28;
    int *local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fd6a;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068dee0(0, param_3);
    local_8 = 0;
    FUN_0068d8d0();
    *param_1                 = &PTR_FUN_006ad86c;
    param_1[3]               = &PTR_FUN_006ad850;
    param_1[4]               = param_2;
    param_1[5]               = param_5;
    param_1[8]               = param_7;
    param_1[9]               = param_8;
    *(short *)(param_1 + 10) = param_9;
    param_1[0xb]             = param_12;
    param_1[0xc]             = param_14;
    FUN_006967f0(param_10, param_11, param_4);
    local_8._0_1_ = 1;
    FUN_00425ac0();
    local_8       = CONCAT31(local_8._1_3_, 2);
    param_1[0x13] = 0x80004004;
    FUN_00697f90(param_6);
    uVar3                        = FUN_00697fc0();
    *(undefined8 *)(param_1 + 6) = uVar3;
    uVar1                        = FUN_004233c0();
    iVar2                        = (*(code *)**(undefined4 **)param_1[5])(param_1[5], uVar1);
    if (iVar2 < 0)
    {
        *param_4 = iVar2;
    }
    else
    {
        (**(code **)(*local_28 + 8))(local_28);
        iVar2 = FUN_006942c0(param_1 + 0x12, param_7, 0, 0, &local_14);
        if (iVar2 < 0)
        {
            *param_4 = iVar2;
        }
        else
        {
            (**(code **)(*local_14 + 8))(local_14);
            if (param_9 == 4)
            {
                param_1[0x10] = 1;
                param_1[0x11] = 0xfffffffd;
                param_1[0xe]  = param_1 + 0x11;
            }
            iVar2 = (**(code **)(*param_2 + 8))(param_1);
            if (iVar2 < 0)
            {
                *param_4 = iVar2;
            }
        }
    }
    ExceptionList = local_10;
    return param_1;
}
