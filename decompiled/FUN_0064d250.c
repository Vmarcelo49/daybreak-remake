// Function: FUN_0064d250
// Address:  0x0064d250
// Source:   batch_decompile (mass dump)
// Hash:     c323594faf94afdb


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WinMain-equivalent: registers window class "HigurashiDaybreak", creates main window, sets
   windowed size based on GetSystemMetrics. Entry point of game UI. */

undefined4 FUN_0064d250(HINSTANCE param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  ATOM AVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  void *pvVar7;
  undefined4 local_194;
  undefined1 local_18c [4];
  undefined1 local_188 [4];
  undefined1 local_184 [4];
  undefined1 local_180 [4];
  undefined1 local_17c [4];
  HWND local_178;
  CHAR local_174 [268];
  undefined4 local_68;
  char *local_64;
  HWND local_60;
  HINSTANCE local_5c;
  undefined4 local_58;
  uint local_48;
  int local_40;
  undefined4 local_3c;
  int local_38;
  WNDCLASSEXA local_34;
  
  local_68 = DAT_006b77f4;
  GetModuleFileNameA((HMODULE)0x0,local_174,0x104);
  local_64 = _strrchr(local_174,0x5c);
  local_64[1] = '\0';
  SetCurrentDirectoryA(local_174);
  iVar3 = GetSystemMetrics(0x2d);
  iVar4 = GetSystemMetrics(5);
  local_40 = GetSystemMetrics(7);
  local_40 = iVar3 + 800 + iVar4 + local_40;
  iVar3 = GetSystemMetrics(0x2e);
  iVar4 = GetSystemMetrics(6);
  iVar5 = GetSystemMetrics(8);
  local_38 = GetSystemMetrics(4);
  local_38 = iVar3 + 600 + iVar4 + iVar5 + local_38;
  local_34.cbSize = 0x30;
  local_34.hInstance = param_1;
  local_34.lpszClassName = "HigurashiDaybreak";
  local_34.lpfnWndProc = FUN_0064d5e0;
  local_34.style = 0;
  local_34.hIcon = LoadIconA(param_1,"ICON");
  local_34.hIconSm = LoadIconA(param_1,"ICON");
  local_34.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_34.lpszMenuName = (LPCSTR)0x0;
  local_34.cbClsExtra = 0;
  local_34.cbWndExtra = 0;
  local_34.hbrBackground = GetStockObject(4);
  AVar2 = RegisterClassExA(&local_34);
  if ((AVar2 != 0) &&
     (local_178 = CreateWindowExA(0x40000,"HigurashiDaybreak","Higurashi Daybreak Kai",0xc80000,
                                  -0x80000000,-0x80000000,local_40,local_38,(HWND)0x0,(HMENU)0x0,
                                  param_1,(LPVOID)0x0), local_178 != (HWND)0x0)) {
    ShowWindow(local_178,param_4);
    UpdateWindow(local_178);
    do {
    } while (DAT_006d11a0 == '\0');
    FUN_0064d760();
    puVar6 = (undefined4 *)FUN_006532f0(local_17c,"daybreak00.dat");
    DAT_006ca824 = *puVar6;
    puVar6 = (undefined4 *)FUN_006532f0(local_180,"daybreak04.dat");
    DAT_006ca828 = *puVar6;
    FUN_006532f0(&local_3c,"daybreak07.dat");
    puVar6 = (undefined4 *)FUN_006532f0(local_184,"daybreak05.dat");
    _DAT_006ca82c = *puVar6;
    puVar6 = (undefined4 *)FUN_006532f0(local_188,"daybreak02.dat");
    DAT_006ca830 = *puVar6;
    puVar6 = (undefined4 *)FUN_006532f0(local_18c,"daybreak06.dat");
    DAT_006ca834 = *puVar6;
    cVar1 = FUN_0064d6e0();
    if ((cVar1 == '\0') && (cVar1 = FUN_0064d6e0(), cVar1 == '\0')) {
      iVar3 = FUN_0068de10();
      if (iVar3 != 0) {
        FUN_00653480(local_3c);
      }
      FUN_00653480(DAT_006ca828);
      FUN_00653480(DAT_006ca824);
      FUN_0064d700();
      local_60 = local_178;
      local_5c = param_1;
      pvVar7 = operator_new(4);
      if (pvVar7 == (void *)0x0) {
        local_194 = 0;
      }
      else {
        local_194 = FUN_0064d780();
      }
      local_58 = local_194;
      local_48 = local_48 | 1;
      cVar1 = FUN_00657910(&local_60);
      if (cVar1 == '\0') {
        MessageBoxA(local_178,&DAT_006a5600,"Error",0);
      }
      else {
        FUN_006609a0();
        FUN_00657ef0();
        FUN_00657b00();
      }
      FUN_006609d0();
    }
  }
  return 0;
}

