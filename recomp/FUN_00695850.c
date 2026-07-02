// ============================================
// Address:  0x00695850
// Original: FUN_00695850
// Status:   unreviewed
// ============================================

int __thiscall FUN_00695850(
    int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fc85;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d8d0();
    FUN_0068dee0(param_2, param_3);
    local_8 = 0;
    FUN_0068d890();
    FUN_00697e90(0);
    FUN_0068d890();
    *(undefined4 *)(param_1 + 0x34) = param_5;
    FUN_0068d8f0(0xffffffff, 0x3fffffff);
    FUN_00697ec0(param_1 + 0x20);
    *(undefined8 *)(param_1 + 0x28) = 0x3ff0000000000000;
    *(undefined4 *)(param_1 + 0x30) = 0x37;
    ExceptionList                   = local_10;
    return param_1;
}
