// Function: FUN_0065f7c0
// Address:  0x0065f7c0
// Source:   batch_decompile (mass dump)
// Hash:     0e3ea15844dbd05d


undefined4 __fastcall FUN_0065f7c0(LPVOID *param_1)

{
  HRESULT HVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_1c [2];
  wchar_t *local_14;
  
  HVar1 = CoCreateInstance((IID *)&DAT_006ab824,(LPUNKNOWN)0x0,1,(IID *)&DAT_006ab804,param_1);
  if (HVar1 < 0) {
    FUN_0065f9c0(&DAT_006aaf14);
    uVar2 = 0;
  }
  else {
    iVar3 = (**(code **)(*(int *)*param_1 + 0xc))(*param_1,0,FUN_0065fc80,0);
    if (iVar3 < 0) {
      FUN_0065f9c0(&DAT_006aaf34);
      uVar2 = 0;
    }
    else {
      CoCreateInstance((IID *)&DAT_006ab844,(LPUNKNOWN)0x0,1,(IID *)&DAT_006ab834,param_1 + 1);
      (**(code **)(*(int *)param_1[1] + 0x34))(param_1[1],&DAT_006ab7e4);
      _memset(local_1c,0,0x18);
      local_1c[0] = 0x18;
      local_14 = L"Client";
      (**(code **)(*(int *)*param_1 + 0x2c))(*param_1,local_1c,0,0,0);
      uVar2 = 1;
    }
  }
  return uVar2;
}

