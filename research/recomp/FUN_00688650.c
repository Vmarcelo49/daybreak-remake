// ============================================
// Address:  0x00688650
// Original: FUN_00688650
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00688650(undefined4 *param_1, undefined4 param_2, int param_3)

{
    undefined4 uVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f4fe;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d8d0();
    *param_1   = &PTR_FUN_006ad264;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = param_2;
    param_1[5] = 1;
    FUN_0068dd80(0);
    local_8 = 0;
    (**(code **)(*(int *)(param_1[3] + 0xc) + 4))(param_1[3] + 0xc);
    if (param_3 == 0)
    {
        uVar1      = (**(code **)(*(int *)param_1[3] + 0x14))();
        param_1[4] = uVar1;
        uVar1      = (**(code **)(*(int *)param_1[3] + 0x18))();
        param_1[2] = uVar1;
    }
    else
    {
        param_1[1] = *(undefined4 *)(param_3 + 4);
        param_1[2] = *(undefined4 *)(param_3 + 8);
        param_1[4] = *(undefined4 *)(param_3 + 0x10);
        FUN_0068dda0(param_3 + 0x18);
    }
    ExceptionList = local_10;
    return param_1;
}
