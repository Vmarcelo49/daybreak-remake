// Function: FUN_0068b890
// Address:  0x0068b890
// Source:   batch_decompile (mass dump)
// Hash:     be90c1622829368e


undefined4 __fastcall FUN_0068b890(int param_1)

{
  HANDLE pvVar1;
  undefined4 uVar2;
  
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,1,(LPCSTR)0x0);
  *(HANDLE *)(param_1 + 0xbc) = pvVar1;
  if (*(int *)(param_1 + 0xbc) == 0) {
    uVar2 = FUN_00693210();
  }
  else {
    FUN_0068dc30(1);
    uVar2 = 0;
  }
  return uVar2;
}

