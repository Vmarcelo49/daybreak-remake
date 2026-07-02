// Function: ___crtInitCritSecAndSpinCount
// Address:  0x006746da
// Reason:   keyword:Init


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___crtInitCritSecAndSpinCount
   
   Library: Visual Studio 2003 Release */

void ___crtInitCritSecAndSpinCount(undefined4 param_1,undefined4 param_2)

{
  HMODULE hModule;
  
  if (DAT_006d87dc == (code *)0x0) {
    if (DAT_006d8618 != 1) {
      hModule = GetModuleHandleA("kernel32.dll");
      if (hModule != (HMODULE)0x0) {
        DAT_006d87dc = GetProcAddress(hModule,"InitializeCriticalSectionAndSpinCount");
        if (DAT_006d87dc != (FARPROC)0x0) goto LAB_00674726;
      }
    }
    DAT_006d87dc = ___crtInitCritSecNoSpinCount_8;
  }
LAB_00674726:
  (*DAT_006d87dc)(param_1,param_2);
  return;
}

