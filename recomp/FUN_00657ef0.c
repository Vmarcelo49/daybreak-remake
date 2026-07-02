// ============================================
// Address:  0x00657ef0
// Original: FUN_00657ef0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00657ef0(undefined4 *param_1)

{
  BOOL BVar1;
  DWORD DVar2;
  undefined4 uVar3;
  tagMSG local_20;
  
  while( true ) {
    while (BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,0), BVar1 == 0) {
      DVar2 = timeGetTime();
      if (DVar2 - param_1[4] < 1000) {
        param_1[3] = param_1[3] + 1;
      }
      else {
        param_1[2] = param_1[3];
        param_1[5] = param_1[6];
        DVar2 = timeGetTime();
        param_1[4] = DVar2;
        param_1[3] = 0;
        param_1[6] = 0;
      }
      if (param_1[0xf] != 0) {
        if ((param_1[0x18] == 0) || (param_1[0x19] != 0)) {
          uVar3 = (**(code **)(*(int *)param_1[0xf] + 0xc))();
          param_1[0x1b] = uVar3;
        }
        FUN_00657c80(param_1[0x1b]);
        if (*(char *)(param_1 + 0x17) != '\0') {
          if (param_1[0xf] != 0) {
            (**(code **)(*(int *)param_1[0xf] + 4))();
          }
          param_1[6] = param_1[6] + 1;
        }
      }
      FUN_00650d70();
      if (*(char *)(param_1 + 0x1c) != '\0') {
        FUN_0065d670();
        FUN_00650ef0();
        FUN_0065d6a0();
        *(undefined1 *)(param_1 + 0x1c) = 0;
      }
      if (param_1[0xf] == 0) {
        FUN_0065d670();
        DestroyWindow((HWND)*param_1);
        FUN_0065d6a0();
      }
      FUN_00667180(param_1[0xc]);
    }
    BVar1 = GetMessageA(&local_20,(HWND)0x0,0,0);
    if (BVar1 == 0) break;
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  return;
}

