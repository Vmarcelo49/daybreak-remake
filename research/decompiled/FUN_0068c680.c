// Function: FUN_0068c680
// Address:  0x0068c680
// Source:   batch_decompile (mass dump)
// Hash:     34f034239dbc3894


void __fastcall FUN_0068c680(CAccessibleProxy *param_1)

{
  CAccessibleProxy *pCVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069f734;
  local_10 = ExceptionList;
  local_8 = 1;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x30) != 0) {
    ExceptionList = &local_10;
    CloseHandle(*(HANDLE *)(param_1 + 0x30));
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    (**(code **)(**(int **)(param_1 + 0x58) + 8))(*(undefined4 *)(param_1 + 0x58));
  }
  local_8 = local_8 & 0xffffff00;
  if (param_1 == (CAccessibleProxy *)0x0) {
    pCVar1 = (CAccessibleProxy *)0x0;
  }
  else {
    pCVar1 = param_1 + 0x10;
  }
  FUN_0068dbb0(pCVar1);
  local_8 = 0xffffffff;
  ATL::CAccessibleProxy::~CAccessibleProxy(param_1);
  ExceptionList = local_10;
  return;
}

