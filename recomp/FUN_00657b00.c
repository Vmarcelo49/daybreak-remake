// ============================================
// Address:  0x00657b00
// Original: FUN_00657b00
// Status:   unreviewed
// ============================================


void __fastcall FUN_00657b00(int param_1)

{
  DWORD local_8;
  
  FUN_0065d670();
  if (*(int *)(param_1 + 0x3c) != 0) {
    if (*(undefined4 **)(param_1 + 0x3c) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x3c))(1);
    }
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  FUN_0065d6a0();
  (**(code **)(**(int **)(param_1 + 0x38) + 4))();
  if (*(int *)(param_1 + 0x38) != 0) {
    _free(*(void **)(param_1 + 0x38));
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  *(undefined1 *)(param_1 + 0x1c) = 0;
  if (*(int *)(param_1 + 0x20) != 0) {
    SetThreadPriority(*(HANDLE *)(param_1 + 0x20),0xf);
    local_8 = 0x103;
    while (local_8 == 0x103) {
      GetExitCodeThread(*(HANDLE *)(param_1 + 0x20),&local_8);
    }
    CloseHandle(*(HANDLE *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    local_8 = 0x103;
    while (local_8 == 0x103) {
      GetExitCodeThread(*(HANDLE *)(param_1 + 0x20),&local_8);
    }
    CloseHandle(*(HANDLE *)(param_1 + 0x24));
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    CloseHandle(*(HANDLE *)(param_1 + 0x34));
  }
  FUN_006582d0();
  FUN_00661c60();
  FUN_00650280();
  FUN_00655380();
  CoUninitialize();
  return;
}

