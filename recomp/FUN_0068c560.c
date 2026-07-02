// ============================================
// Address:  0x0068c560
// Original: FUN_0068c560
// Status:   unreviewed
// ============================================

int __thiscall FUN_0068c560(int param_1,
                            undefined4 param_2,
                            undefined4 param_3,
                            undefined4 *param_4,
                            int param_5,
                            undefined4 param_6)

{
    HANDLE pvVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f6fb;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068dee0(param_2, param_3);
    local_8 = 0;
    FUN_0068db70();
    FUN_0068db90();
    local_8 = CONCAT31(local_8._1_3_, 1);
    FUN_0068dc50();
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined4 *)(param_1 + 0x4c) = 0;
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0;
    *(undefined4 *)(param_1 + 0x5c) = param_6;
    if (param_5 != 0)
    {
        pvVar1 = CreateSemaphoreA((LPSECURITY_ATTRIBUTES)0x0, 0, 0x7fffffff, (LPCSTR)0x0);
        *(HANDLE *)(param_1 + 0x30) = pvVar1;
        if (*(int *)(param_1 + 0x30) == 0)
        {
            *param_4 = 0x8007000e;
        }
    }
    ExceptionList = local_10;
    return param_1;
}
