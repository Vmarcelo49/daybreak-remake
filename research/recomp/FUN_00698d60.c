// ============================================
// Address:  0x00698d60
// Original: FUN_00698d60
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00698d60(undefined4 *param_1,
                                    undefined4 param_2,
                                    undefined4 param_3,
                                    undefined4 param_4,
                                    undefined4 param_5)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069ff53;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00687a00(param_2, param_3, param_1 + 0x14, &DAT_006ad88c, 0);
    local_8    = 0;
    *param_1   = &PTR_FUN_006ad970;
    param_1[3] = &PTR_FUN_006aae18;
    param_1[4] = &PTR_LAB_006ad95c;
    FUN_0068db90();
    local_8._0_1_ = 1;
    FUN_00699290(param_4);
    local_8._0_1_ = 2;
    FUN_006983b0(param_5, param_1, param_1 + 0x1a, param_1 + 0x14);
    local_8 = CONCAT31(local_8._1_3_, 3);
    FUN_00686800();
    ExceptionList = local_10;
    return param_1;
}
