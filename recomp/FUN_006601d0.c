// ============================================
// Address:  0x006601d0
// Original: FUN_006601d0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __thiscall FUN_006601d0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  HANDLE pvVar2;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  wchar_t *local_24;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = DAT_006b77f4;
  _memset(param_1 + 10,0xff,0x20);
  local_8 = param_3;
  (**(code **)(*(int *)param_1[1] + 0x48))(param_1[1],L"port",&local_8,4,2);
  _memset(&local_54,0,0x48);
  local_54 = 0x48;
  local_50 = 1;
  local_3c = *param_2;
  local_38 = param_2[1];
  local_34 = param_2[2];
  local_30 = param_2[3];
  local_24 = L"Session";
  iVar1 = (**(code **)(*(int *)*param_1 + 0x34))(*param_1,&local_54,param_1 + 1,1,0,0,0,0);
  if (-1 < iVar1) {
    *(undefined1 *)(param_1 + 0x1a) = 1;
    pvVar2 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    param_1[0x1b] = pvVar2;
    pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_00660870,(LPVOID)0x0,0,param_1 + 0x1d);
    param_1[0x1c] = pvVar2;
    SetThreadPriority((HANDLE)param_1[0x1c],0xf);
    _memset(param_1 + 0x1e,0,0x20);
  }
  else {
    FUN_006601b0(&DAT_006ab034);
  }
  return -1 < iVar1;
}

