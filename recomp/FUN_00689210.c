// ============================================
// Address:  0x00689210
// Original: FUN_00689210
// Status:   unreviewed
// ============================================

void __fastcall FUN_00689210(CAccessibleProxy *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    uint local_8;

    puStack_c     = &LAB_0069f59b;
    local_10      = ExceptionList;
    local_8       = 1;
    ExceptionList = &local_10;
    _free(*(void **)(param_1 + 0x14));
    local_8 = local_8 & 0xffffff00;
    FUN_006867e0();
    local_8 = 0xffffffff;
    ATL::CAccessibleProxy::~CAccessibleProxy(param_1);
    ExceptionList = local_10;
    return;
}
