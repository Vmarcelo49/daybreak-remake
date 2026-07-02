// Function: FUN_00653620
// Address:  0x00653620
// Source:   batch_decompile (mass dump)
// Hash:     ea856e14e9231230


undefined4 __thiscall FUN_00653620(undefined4 param_1,undefined4 *param_2,LPCSTR param_3)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  HANDLE pvVar4;
  
  cVar1 = FUN_0064d6e0(param_1);
  if (cVar1 == '\0') {
    FUN_006543d0(*param_2);
    cVar1 = FUN_00662f70(param_3);
    if (cVar1 == '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    piVar3 = (int *)FUN_00654430(param_2);
    pvVar4 = CreateFileA(param_3,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    *piVar3 = (int)pvVar4;
    if (*piVar3 == -1) {
      FUN_0065a7f0(*param_2);
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

