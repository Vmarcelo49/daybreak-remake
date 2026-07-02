// ============================================
// Address:  0x006540f0
// Original: FUN_006540f0
// Status:   unreviewed
// ============================================

void __thiscall FUN_006540f0(int param_1, uint param_2)

{
    int iVar1;
    undefined1 local_54[28];
    undefined1 local_38[40];
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069ed38;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    iVar1         = FUN_00436070();
    if ((uint)(iVar1 - *(int *)(param_1 + 8)) < param_2)
    {
        basic_string<>("list<T> too long");
        local_8 = 0;
        FID_conflict_length_error(local_54);
        /* WARNING: Subroutine does not return */
        __CxxThrowException_8(local_38, &DAT_006b1da0);
    }
    *(uint *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2;
    ExceptionList          = local_10;
    return;
}
