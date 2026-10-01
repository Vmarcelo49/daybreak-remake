// Function: FUN_006538b0
// Address:  0x006538b0
// Source:   batch_decompile (mass dump)
// Hash:     44efb0ccce9ff92f


undefined4 __thiscall FUN_006538b0(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *lpBuffer;
  DWORD nNumberOfBytesToRead;
  LPDWORD lpNumberOfBytesRead;
  LPOVERLAPPED lpOverlapped;
  undefined4 local_8;
  
  local_8 = 0;
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    iVar2 = FUN_006543d0(param_2);
    if (iVar2 == 0) {
      lpOverlapped = (LPOVERLAPPED)0x0;
      lpNumberOfBytesRead = param_1 + 1;
      nNumberOfBytesToRead = 4;
      lpBuffer = &local_8;
      puVar4 = (undefined4 *)FUN_006543d0(param_2);
      ReadFile((HANDLE)*puVar4,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped);
    }
    else {
      FUN_00663030(&local_8,4);
      uVar3 = FUN_00653b30();
      param_1[1] = uVar3;
    }
  }
  else {
    ReadFile((HANDLE)*param_1,&local_8,4,param_1 + 1,(LPOVERLAPPED)0x0);
  }
  return local_8;
}

