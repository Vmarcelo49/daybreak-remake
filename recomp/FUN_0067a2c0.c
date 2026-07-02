// ============================================
// Address:  0x0067a2c0
// Original: FUN_0067a2c0
// Status:   unreviewed
// ============================================


int FUN_0067a2c0(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  void *pvVar3;
  uint _Size;
  
  _Size = param_2 + 7U & 0xfffffff8;
  if (*(int *)(param_1 + 0x4c) < (int)(*(int *)(param_1 + 0x48) + _Size)) {
    if (*(int *)(param_1 + 0x44) != 0) {
      puVar2 = _malloc(8);
      *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x48);
      puVar2[1] = *(undefined4 *)(param_1 + 0x54);
      *puVar2 = *(undefined4 *)(param_1 + 0x44);
      *(undefined4 **)(param_1 + 0x54) = puVar2;
    }
    *(uint *)(param_1 + 0x4c) = _Size;
    pvVar3 = _malloc(_Size);
    *(void **)(param_1 + 0x44) = pvVar3;
    *(undefined4 *)(param_1 + 0x48) = 0;
  }
  iVar1 = *(int *)(param_1 + 0x48);
  *(uint *)(param_1 + 0x48) = iVar1 + _Size;
  return *(int *)(param_1 + 0x44) + iVar1;
}

