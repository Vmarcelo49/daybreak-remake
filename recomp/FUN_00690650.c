// ============================================
// Address:  0x00690650
// Original: FUN_00690650
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00690650(undefined4 *param_1,
                                    undefined4 param_2,
                                    undefined4 param_3,
                                    undefined4 param_4,
                                    undefined4 param_5)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fa88;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068e160(param_2, param_3, param_4, param_5);
    local_8 = 0;
    FUN_0068d8d0();
    FUN_0068d8d0();
    *param_1      = &PTR_FUN_006ad608;
    param_1[3]    = &PTR_FUN_006ab258;
    param_1[4]    = &PTR_LAB_006ad95c;
    param_1[0x38] = &PTR_LAB_006ab234;
    param_1[0x39] = &PTR_LAB_006ad5f4;
    param_1[0x3b] = 0;
    param_1[0x48] = 0;
    param_1[0x49] = 0;
    FUN_00690780();
    ExceptionList = local_10;
    return param_1;
}
