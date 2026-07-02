// ============================================
// Address:  0x00697d70
// Original: FUN_00697d70
// Status:   unreviewed
// ============================================


void __fastcall FUN_00697d70(int param_1)

{
  CAccessibleProxy *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069fea7;
  local_10 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_10;
  FUN_00694270();
  local_8 = 0xffffffff;
  if (param_1 == 0) {
    local_18 = (CAccessibleProxy *)0x0;
  }
  else {
    local_18 = (CAccessibleProxy *)(param_1 + 4);
  }
  ATL::CAccessibleProxy::~CAccessibleProxy(local_18);
  ExceptionList = local_10;
  return;
}

