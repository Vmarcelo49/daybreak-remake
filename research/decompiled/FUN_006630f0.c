// Function: FUN_006630f0
// Address:  0x006630f0
// Source:   batch_decompile (mass dump)
// Hash:     001d07652714af71


int __thiscall FUN_006630f0(undefined4 *param_1,int param_2,int param_3)

{
  DWORD DVar1;
  int iVar2;
  
  if (param_3 == 0) {
    DVar1 = SetFilePointer((HANDLE)*param_1,param_1[1] + param_2,(PLONG)0x0,0);
    iVar2 = DVar1 - param_1[1];
  }
  else if (param_3 == 1) {
    DVar1 = SetFilePointer((HANDLE)*param_1,param_2,(PLONG)0x0,1);
    iVar2 = DVar1 - param_1[1];
  }
  else if (param_3 == 2) {
    DVar1 = SetFilePointer((HANDLE)*param_1,(param_1[1] + param_1[2]) - param_2,(PLONG)0x0,0);
    iVar2 = DVar1 - param_1[1];
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

