// ============================================
// Address:  0x006873f0
// Original: FUN_006873f0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006873f0(CAccessibleProxy *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069f3ea;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    if (*(int *)(param_1 + 0x14) != 0)
    {
        ExceptionList = &local_10;
        (**(code **)(**(int **)(param_1 + 0x14) + 8))(*(undefined4 *)(param_1 + 0x14));
        *(undefined4 *)(param_1 + 0x14) = 0;
    }
    local_8 = 0xffffffff;
    ATL::CAccessibleProxy::~CAccessibleProxy(param_1);
    ExceptionList = local_10;
    return;
}
