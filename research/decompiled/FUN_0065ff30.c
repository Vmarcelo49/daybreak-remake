// Function: FUN_0065ff30
// Address:  0x0065ff30
// Source:   batch_decompile (mass dump)
// Hash:     6cffe2c3d4f72ad9


undefined4 __fastcall FUN_0065ff30(LPVOID *param_1)

{
  HRESULT HVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_1c [2];
  wchar_t *local_14;
  
  HVar1 = CoCreateInstance((IID *)&DAT_006ab814,(LPUNKNOWN)0x0,1,(IID *)&DAT_006ab7f4,param_1);
  if (HVar1 < 0) {
    FUN_006601b0(&DAT_006aaf94);
    uVar2 = 0;
  }
  else {
    iVar3 = (**(code **)(*(int *)*param_1 + 0xc))(*param_1,0,FUN_00660620,0);
    if (iVar3 < 0) {
      FUN_006601b0(&DAT_006aafb4);
      uVar2 = 0;
    }
    else {
      HVar1 = CoCreateInstance((IID *)&DAT_006ab844,(LPUNKNOWN)0x0,1,(IID *)&DAT_006ab834,
                               param_1 + 1);
      if (HVar1 < 0) {
        FUN_006601b0(&DAT_006aafcc);
        uVar2 = 0;
      }
      else {
        iVar3 = (**(code **)(*(int *)param_1[1] + 0x34))(param_1[1],&DAT_006ab7e4);
        if (iVar3 < 0) {
          FUN_006601b0(&DAT_006aafe4);
          uVar2 = 0;
        }
        else {
          _memset(local_1c,0,0x18);
          local_1c[0] = 0x18;
          local_14 = L"Server";
          (**(code **)(*(int *)*param_1 + 0x20))(*param_1,local_1c,0,0,0);
          uVar2 = 1;
        }
      }
    }
  }
  return uVar2;
}

