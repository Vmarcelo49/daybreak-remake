// ============================================
// Address:  0x00687ae0
// Original: FUN_00687ae0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00687ae0(CAccessibleProxy *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069f456;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    _free(*(void **)(param_1 + 0x3c));
    if (*(int *)(param_1 + 0x18) != 0)
    {
        (**(code **)(**(int **)(param_1 + 0x18) + 8))(*(undefined4 *)(param_1 + 0x18));
        *(undefined4 *)(param_1 + 0x18) = 0;
    }
    local_8 = 0xffffffff;
    ATL::CAccessibleProxy::~CAccessibleProxy(param_1);
    ExceptionList = local_10;
    return;
}
