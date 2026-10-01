// ============================================
// Address:  0x00698320
// Original: FUN_00698320
// Status:   unreviewed
// ============================================

void __fastcall FUN_00698320(CAccessibleProxy *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    puStack_c     = &LAB_0069fee8;
    local_10      = ExceptionList;
    local_8       = 0;
    ExceptionList = &local_10;
    FUN_0068dbb0();
    local_8 = 0xffffffff;
    ATL::CAccessibleProxy::~CAccessibleProxy(param_1);
    ExceptionList = local_10;
    return;
}
