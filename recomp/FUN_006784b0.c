// ============================================
// Address:  0x006784b0
// Original: FUN_006784b0
// Status:   unreviewed
// ============================================


longlong FUN_006784b0(int param_1,int param_2)

{
  longlong lVar1;
  int iVar2;
  longlong lVar3;
  
  if ((1 < *(int *)(param_1 + 0x58)) && (*(int *)(param_1 + 4) != 0)) {
    if (param_2 < *(int *)(param_1 + 0x34)) {
      if (param_2 < 0) {
        lVar3 = 0;
        iVar2 = 0;
        lVar1 = 0;
        if (0 < *(int *)(param_1 + 0x34)) {
          do {
            lVar3 = FUN_006784b0(param_1,iVar2);
            lVar3 = lVar3 + lVar1;
            iVar2 = iVar2 + 1;
            lVar1 = lVar3;
          } while (iVar2 < *(int *)(param_1 + 0x34));
        }
        return lVar3;
      }
      return CONCAT44(*(undefined4 *)(*(int *)(param_1 + 0x44) + 0xc + param_2 * 0x10),
                      *(undefined4 *)(*(int *)(param_1 + 0x44) + 8 + param_2 * 0x10));
    }
  }
  return -0x83;
}

