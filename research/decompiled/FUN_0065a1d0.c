// Function: FUN_0065a1d0
// Address:  0x0065a1d0
// Source:   batch_decompile (mass dump)
// Hash:     30e2ee02fd7103ff


void __thiscall FUN_0065a1d0(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    iVar2 = (*(int *)(param_1 + 1000) * param_3) / 10000 + -10000;
    FUN_0065a850(param_2);
    FUN_0065a390(iVar2);
  }
  return;
}

