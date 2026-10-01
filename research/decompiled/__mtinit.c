// Function: __mtinit
// Address:  0x0066dde4
// Reason:   keyword:Init


/* Library Function - Single Match
    __mtinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __mtinit(void)

{
  int iVar1;
  HMODULE hModule;
  DWORD *pDVar2;
  DWORD DVar3;
  
  iVar1 = __mtinitlocks();
  if (iVar1 == 0) {
    __mtterm();
    return 0;
  }
  hModule = GetModuleHandleA("kernel32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_006d8498 = GetProcAddress(hModule,"FlsAlloc");
    DAT_006d849c = GetProcAddress(hModule,"FlsGetValue");
    DAT_006d84a0 = GetProcAddress(hModule,"FlsSetValue");
    DAT_006d84a4 = GetProcAddress(hModule,"FlsFree");
    if (DAT_006d849c == (FARPROC)0x0) {
      DAT_006d849c = TlsGetValue_exref;
      DAT_006d84a0 = TlsSetValue_exref;
      DAT_006d8498 = FUN_0066dc06;
      DAT_006d84a4 = TlsFree_exref;
    }
  }
  DAT_006b7894 = (*DAT_006d8498)(&LAB_0066dc9d);
  if (((DAT_006b7894 != -1) && (pDVar2 = _calloc(1,0x8c), pDVar2 != (DWORD *)0x0)) &&
     (iVar1 = (*DAT_006d84a0)(DAT_006b7894,pDVar2), iVar1 != 0)) {
    pDVar2[0x15] = (DWORD)&DAT_006b81a0;
    pDVar2[5] = 1;
    DVar3 = GetCurrentThreadId();
    pDVar2[1] = 0xffffffff;
    *pDVar2 = DVar3;
    return 1;
  }
  __mtterm();
  return 0;
}

