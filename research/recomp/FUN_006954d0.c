// ============================================
// Address:  0x006954d0
// Original: FUN_006954d0
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_006954d0(undefined4 *param_1,
                                    undefined4 param_2,
                                    undefined4 param_3,
                                    undefined4 param_4,
                                    undefined4 param_5)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fc4c;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00694a30(param_2, param_3, param_4, param_5);
    local_8    = 0;
    *param_1   = &PTR_FUN_006ad7f0;
    param_1[1] = &PTR_LAB_006ad7a8;
    param_1[2] = &PTR_FUN_006ad794;
    FUN_0068db90();
    param_1[0xe]  = 0;
    param_1[0xf]  = 0;
    param_1[0x10] = 0;
    param_1[0x11] = 0;
    param_1[0x12] = 1;
    ExceptionList = local_10;
    return param_1;
}
