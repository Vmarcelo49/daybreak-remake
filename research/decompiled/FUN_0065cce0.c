// Function: FUN_0065cce0
// Address:  0x0065cce0
// Source:   batch_decompile (mass dump)
// Hash:     26e876808428de5a


undefined8 __thiscall FUN_0065cce0(int param_1,undefined8 *param_2)

{
  DWORD DVar1;
  int iVar2;
  undefined8 uVar3;
  
  DVar1 = timeGetTime();
  iVar2 = DVar1 - *(int *)(param_1 + 0x2c);
  uVar3 = __allmul(iVar2,iVar2 >> 0x1f,*(int *)(param_1 + 0x28),*(int *)(param_1 + 0x28) >> 0x1f);
  iVar2 = (int)((ulonglong)uVar3 >> 0x20);
  if ((*(int *)(param_1 + 0x3c) <= iVar2) &&
     ((*(int *)(param_1 + 0x3c) < iVar2 || (*(uint *)(param_1 + 0x38) < (uint)uVar3)))) {
    uVar3 = *(undefined8 *)(param_1 + 0x38);
  }
  *param_2 = uVar3;
  return *(undefined8 *)(param_1 + 0x38);
}

