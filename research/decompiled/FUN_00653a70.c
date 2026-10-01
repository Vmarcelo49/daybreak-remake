// Function: FUN_00653a70
// Address:  0x00653a70
// Source:   batch_decompile (mass dump)
// Hash:     886d8780628948d7


void __thiscall FUN_00653a70(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  LPDWORD lpFileSizeHigh;
  
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    iVar2 = FUN_006543d0(param_2);
    if (iVar2 == 0) {
      lpFileSizeHigh = (LPDWORD)0x0;
      puVar3 = (undefined4 *)FUN_006543d0(param_2);
      GetFileSize((HANDLE)*puVar3,lpFileSizeHigh);
    }
    else {
      FUN_00699fc0();
    }
  }
  else {
    GetFileSize((HANDLE)*param_1,(LPDWORD)0x0);
  }
  return;
}

