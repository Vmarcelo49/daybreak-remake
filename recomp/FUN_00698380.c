// ============================================
// Address:  0x00698380
// Original: FUN_00698380
// Status:   unreviewed
// ============================================


CAccessibleProxy * __thiscall FUN_00698380(CAccessibleProxy *param_1,uint param_2)

{
  ATL::CAccessibleProxy::~CAccessibleProxy(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

