// ============================================
// Address:  0x0069d4c0
// Original: FUN_0069d4c0
// Status:   unreviewed
// ============================================


void FUN_0069d4c0(int *param_1,uint param_2,int param_3)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  
  if (param_1[4] <= *param_1 + 4) {
    pvVar1 = _realloc((void *)param_1[2],param_1[4] + 0x100);
    param_1[2] = (int)pvVar1;
    param_1[4] = param_1[4] + 0x100;
    param_1[3] = *param_1 + (int)pvVar1;
  }
  param_2 = param_2 & *(uint *)(&DAT_006c77d8 + param_3 * 4);
  uVar3 = param_3 + param_1[1];
  *(byte *)param_1[3] = *(byte *)param_1[3] | (char)param_2 << ((byte)param_1[1] & 0x1f);
  if ((((7 < (int)uVar3) &&
       (*(char *)(param_1[3] + 1) = (char)(param_2 >> (8U - (char)param_1[1] & 0x1f)),
       0xf < (int)uVar3)) &&
      (*(char *)(param_1[3] + 2) = (char)(param_2 >> (0x10U - (char)param_1[1] & 0x1f)),
      0x17 < (int)uVar3)) &&
     (*(char *)(param_1[3] + 3) = (char)(param_2 >> (0x18U - (char)param_1[1] & 0x1f)),
     0x1f < (int)uVar3)) {
    if (param_1[1] == 0) {
      *(undefined1 *)(param_1[3] + 4) = 0;
    }
    else {
      *(char *)(param_1[3] + 4) = (char)(param_2 >> (0x20U - (char)param_1[1] & 0x1f));
    }
  }
  iVar2 = (int)(uVar3 + ((int)uVar3 >> 0x1f & 7U)) >> 3;
  param_1[1] = uVar3 & 7;
  *param_1 = *param_1 + iVar2;
  param_1[3] = param_1[3] + iVar2;
  return;
}

