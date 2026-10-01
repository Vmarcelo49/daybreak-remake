// ============================================
// Address:  0x0065b570
// Original: FUN_0065b570
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_0065b570(undefined4 *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f056;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_006679a0();
    local_8 = 0;
    FUN_00425ac0();
    FUN_00667fe0();
    local_8 = CONCAT31(local_8._1_3_, 1);
    FUN_0065d610();
    param_1[1]                             = 0;
    *param_1                               = 0;
    *(undefined1 *)(param_1 + 0x4d3)       = 0;
    *(undefined1 *)((int)param_1 + 0x134d) = 0;
    param_1[0x4d7]                         = 10000;
    param_1[0x4d8]                         = 10000;
    ExceptionList                          = local_10;
    return param_1;
}
