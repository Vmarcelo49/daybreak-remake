// ============================================
// Address:  0x0065ca70
// Original: FUN_0065ca70
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_0065ca70(undefined4 *param_1, undefined4 param_2, undefined4 param_3)

{
    undefined4 uVar1;
    DWORD DVar2;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f0e3;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0065cdf0();
    local_8  = 0;
    *param_1 = &PTR_FUN_006aadcc;
    FUN_0065d610();
    local_8     = CONCAT31(local_8._1_3_, 1);
    param_1[8]  = 0;
    param_1[9]  = 0;
    param_1[10] = param_3;
    FUN_00425ac0();
    param_1[0xc]  = param_2;
    uVar1         = FUN_00653a70(param_2);
    param_1[0xe]  = uVar1;
    param_1[0xf]  = 0;
    DVar2         = timeGetTime();
    param_1[0xb]  = DVar2;
    param_1[8]    = 0;
    param_1[9]    = 0;
    ExceptionList = local_10;
    return param_1;
}
