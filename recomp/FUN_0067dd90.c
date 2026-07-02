// ============================================
// Address:  0x0067dd90
// Original: FUN_0067dd90
// Status:   unreviewed
// ============================================


void FUN_0067dd90(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  
  fVar5 = (float10)FUN_0069a730();
  FUN_0069a090((double)fVar5);
  iVar1 = __ftol();
  do {
    while( true ) {
      iVar2 = 1;
      iVar3 = 1;
      if (0 < *param_1) {
        iVar4 = *param_1;
        do {
          iVar2 = iVar2 * iVar1;
          iVar3 = iVar3 * (iVar1 + 1);
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      iVar4 = param_1[1];
      if (iVar2 <= iVar4) break;
LAB_0067ddeb:
      iVar1 = iVar1 + -1;
    }
    if (iVar4 < iVar3) {
      return;
    }
    if (iVar4 < iVar2) goto LAB_0067ddeb;
    iVar1 = iVar1 + 1;
  } while( true );
}

