// ============================================
// Address:  0x0069cc20
// Original: FUN_0069cc20
// Status:   unreviewed
// ============================================


void FUN_0069cc20(int *param_1)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    uVar1 = 0;
    *(undefined1 *)(*param_1 + 0x16) = 0;
    *(undefined1 *)(*param_1 + 0x17) = 0;
    *(undefined1 *)(*param_1 + 0x18) = 0;
    *(undefined1 *)(*param_1 + 0x19) = 0;
    iVar2 = 0;
    if (0 < param_1[1]) {
      do {
        uVar1 = uVar1 << 8 ^
                *(uint *)(&DAT_006c73d0 + ((uint)*(byte *)(iVar2 + *param_1) ^ uVar1 >> 0x18) * 4);
        iVar2 = iVar2 + 1;
      } while (iVar2 < param_1[1]);
    }
    iVar2 = 0;
    if (0 < param_1[3]) {
      do {
        uVar1 = uVar1 << 8 ^
                *(uint *)(&DAT_006c73d0 + ((uint)*(byte *)(iVar2 + param_1[2]) ^ uVar1 >> 0x18) * 4)
        ;
        iVar2 = iVar2 + 1;
      } while (iVar2 < param_1[3]);
    }
    *(char *)(*param_1 + 0x16) = (char)uVar1;
    *(char *)(*param_1 + 0x17) = (char)(uVar1 >> 8);
    *(char *)(*param_1 + 0x18) = (char)(uVar1 >> 0x10);
    *(char *)(*param_1 + 0x19) = (char)(uVar1 >> 0x18);
  }
  return;
}

