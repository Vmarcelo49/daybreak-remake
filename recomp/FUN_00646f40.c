// ============================================
// Address:  0x00646f40
// Original: FUN_00646f40
// Status:   unreviewed
// ============================================


void FUN_00646f40(void)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined1 local_24 [8];
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  iVar2 = FUN_0063bf40();
  if (iVar2 != 0) {
    uVar4 = 1;
    puVar3 = local_c;
    FUN_00425150(local_1c);
    FUN_004250e0(puVar3,uVar4);
    FUN_00425ae0(local_14);
    while (iVar2 = FUN_00647610(), 0 < *(int *)(iVar2 + 0x8c)) {
      iVar2 = FUN_00647610();
      if (*(int *)(iVar2 + 0x8c) != 0) {
        iVar2 = FUN_00647610();
        *(int *)(iVar2 + 0x8c) = *(int *)(iVar2 + 0x8c) + -1;
      }
      cVar1 = FUN_00647670(local_14);
      if (cVar1 != '\0') {
        return;
      }
      FUN_00647630(local_24,0);
    }
  }
  return;
}

