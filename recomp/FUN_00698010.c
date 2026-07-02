// ============================================
// Address:  0x00698010
// Original: FUN_00698010
// Status:   unreviewed
// ============================================


void __fastcall FUN_00698010(CAccessibleProxy *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069fed3;
  local_10 = ExceptionList;
  local_8 = 1;
  ExceptionList = &local_10;
  FUN_00694270();
  local_8 = local_8 & 0xffffff00;
  FUN_00696ac0();
  local_8 = 0xffffffff;
  ATL::CAccessibleProxy::~CAccessibleProxy(param_1);
  ExceptionList = local_10;
  return;
}

