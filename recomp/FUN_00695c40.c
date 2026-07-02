// ============================================
// Address:  0x00695c40
// Original: FUN_00695c40
// Status:   unreviewed
// ============================================

undefined4
FUN_00695c40(int *param_1, undefined4 *param_2, uint param_3, uint *param_4, uint param_5)

{
    undefined8 uVar1;
    undefined1 local_28[12];
    uint local_1c;
    undefined4 local_18;
    uint local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069fcbb;
    local_10  = ExceptionList;
    local_14  = param_5 & 3;
    local_1c  = param_3 & 3;
    if (param_5 != 0)
    {
        if (param_4 == (uint *)0x0)
        {
            return 0x80004003;
        }
        if (local_14 != param_5)
        {
            return 0x80070057;
        }
    }
    if (param_3 != 0)
    {
        if (param_2 == (undefined4 *)0x0)
        {
            return 0x80004003;
        }
        if ((local_1c != 1) && (local_1c != 2))
        {
            return 0x80070057;
        }
    }
    ExceptionList = &local_10;
    FUN_0068d950(param_1[0xd]);
    local_8 = 0;
    if (local_1c == 1)
    {
        FUN_0068d8f0(*param_2, param_2[1]);
    }
    else if (local_1c == 2)
    {
        FUN_0068d8f0(*param_2, param_2[1]);
        FUN_00697ee0(local_28);
    }
    if (local_14 == 1)
    {
        FUN_0068d8f0(*param_4, param_4[1]);
    }
    else if (local_14 == 3)
    {
        uVar1 = FUN_00697fc0();
        FUN_0068d8f0((uint)uVar1 + *param_4,
                     (int)((ulonglong)uVar1 >> 0x20) + param_4[1] +
                         (uint)CARRY4((uint)uVar1, *param_4));
    }
    else if (local_14 == 2)
    {
        uVar1 = FUN_00697fc0();
        FUN_0068d8f0((uint)uVar1 + *param_4,
                     (int)((ulonglong)uVar1 >> 0x20) + param_4[1] +
                         (uint)CARRY4((uint)uVar1, *param_4));
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    local_18 = 0;
    if (local_14 != 0)
    {
        local_18 = (**(code **)(*param_1 + 0x54))();
    }
    if (local_1c != 0)
    {
        local_18 = (**(code **)(*param_1 + 0x50))();
    }
    ExceptionList = local_10;
    return local_18;
}
