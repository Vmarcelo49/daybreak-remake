// Function: FUN_00662810
// Address:  0x00662810
// Source:   batch_decompile (mass dump)
// Hash:     9f48ba867f861bd2


void __thiscall FUN_00662810(int param_1,LPCSTR param_2)

{
  int iVar1;
  void *pvVar2;
  
  if (param_2 != (LPCSTR)0x0) {
    iVar1 = lstrlenA(param_2);
    if (*(int *)(param_1 + 4) != 0) {
      _free(*(void **)(param_1 + 4));
      *(undefined4 *)(param_1 + 4) = 0;
    }
    pvVar2 = operator_new(iVar1 + 1U);
    *(void **)(param_1 + 4) = pvVar2;
    _memcpy(*(void **)(param_1 + 4),param_2,iVar1 + 1U);
  }
  return;
}

