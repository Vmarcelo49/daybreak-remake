// ============================================
// Address:  0x00692380
// Original: FUN_00692380
// Status:   unreviewed
// ============================================

void __thiscall FUN_00692380(int param_1, undefined4 *param_2)

{
    undefined4 *_Memory;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fb6d;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    while (true)
    {
        FUN_0068d950(param_1 + 0x24);
        local_8 = 0;
        _Memory = (undefined4 *)FUN_00693460();
        if (_Memory != (undefined4 *)0x0)
            break;
        *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
        local_8                  = 0xffffffff;
        FUN_0068d9a0();
        WaitForSingleObject(*(HANDLE *)(param_1 + 0x3c), 0xffffffff);
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    *param_2   = *_Memory;
    param_2[1] = _Memory[1];
    param_2[2] = _Memory[2];
    param_2[3] = _Memory[3];
    _free(_Memory);
    ExceptionList = local_10;
    return;
}
