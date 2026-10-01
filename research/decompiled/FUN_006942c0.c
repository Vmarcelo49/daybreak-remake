// Function: FUN_006942c0
// Address:  0x006942c0
// Source:   batch_decompile (mass dump)
// Hash:     39e3430b77127aeb


uint FUN_006942c0(int *param_1,undefined4 param_2,int param_3,undefined4 param_4,int *param_5)

{
  uint uVar1;
  DWORD DVar2;
  int *local_18;
  FARPROC local_14;
  HMODULE local_10;
  FARPROC local_c;
  uint local_8;
  
  if (param_5 == (int *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_5 = 0;
    if (param_3 == 0) {
      if (param_5 == (int *)0x0) {
        uVar1 = 0x80004003;
      }
      else {
        if (*param_1 == 0) {
          local_10 = (HMODULE)FUN_0068deb0();
          if (local_10 == (HMODULE)0x0) {
            DVar2 = GetLastError();
            return DVar2 | 0x80070000;
          }
          local_14 = GetProcAddress(local_10,"LoadRegTypeLib");
          if (local_14 == (FARPROC)0x0) {
            DVar2 = GetLastError();
            return DVar2 | 0x80070000;
          }
          local_8 = (*local_14)(&LAB_006ad141_3,1,0,param_4,&local_18);
          if ((int)local_8 < 0) {
            local_c = GetProcAddress(local_10,"LoadTypeLib");
            if (local_c == (FARPROC)0x0) {
              DVar2 = GetLastError();
              return DVar2 | 0x80070000;
            }
            local_8 = (*local_c)(L"control.tlb",&local_18);
            if ((int)local_8 < 0) {
              return local_8;
            }
          }
          local_8 = (**(code **)(*local_18 + 0x18))(local_18,param_2,param_1);
          (**(code **)(*local_18 + 8))(local_18);
          if ((int)local_8 < 0) {
            return local_8;
          }
        }
        *param_5 = *param_1;
        (**(code **)(*(int *)*param_1 + 4))(*param_1);
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0x8002802b;
    }
  }
  return uVar1;
}

