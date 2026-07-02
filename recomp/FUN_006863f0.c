// ============================================
// Address:  0x006863f0
// Original: FUN_006863f0
// Status:   unreviewed
// ============================================


void FUN_006863f0(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  int local_18;
  
  iVar2 = *(int *)(param_1 + 0x1c);
  if (*(int *)(param_3[2] + iVar2 * 4) == 0) {
    iVar6 = *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x40) + 4) + 0x1c) + iVar2 * 4) / 2;
    fVar7 = (float10)*(int *)(param_2 + 4) * (float10)0.5;
    iVar1 = *param_3;
    fVar9 = (float10)fpatan(fVar7 * fVar7 * (float10)1.85e-08,(float10)1);
    fVar10 = (float10)fpatan(fVar7 * (float10)0.00074,(float10)1);
    pvVar3 = _malloc(iVar6 * 4 + 4);
    *(void **)(param_3[2] + iVar2 * 4) = pvVar3;
    iVar5 = 0;
    local_18 = 0;
    if (0 < iVar6) {
      do {
        fVar8 = (((float10)*(int *)(param_2 + 4) * (float10)0.5) / (float10)iVar6) *
                (float10)local_18;
        fVar11 = (float10)fpatan(fVar8 * fVar8 * (float10)1.85e-08,(float10)1);
        fVar12 = (float10)fpatan(fVar8 * (float10)0.00074,(float10)1);
        FUN_0069a090((double)((float10)(float)((float10)iVar1 /
                                              (fVar7 * (float10)0.0001 +
                                              fVar10 * (float10)13.100000381469727 +
                                              fVar9 * (float10)2.240000009536743)) *
                             (fVar8 * (float10)0.0001 +
                             fVar12 * (float10)13.100000381469727 +
                             fVar11 * (float10)2.240000009536743)));
        iVar4 = __ftol();
        if (*param_3 <= iVar4) {
          iVar4 = *param_3 + -1;
        }
        iVar5 = local_18 + 1;
        *(int *)(*(int *)(param_3[2] + iVar2 * 4) + -4 + iVar5 * 4) = iVar4;
        local_18 = iVar5;
      } while (iVar5 < iVar6);
    }
    *(undefined4 *)(*(int *)(param_3[2] + iVar2 * 4) + iVar5 * 4) = 0xffffffff;
    param_3[iVar2 + 3] = iVar6;
  }
  return;
}

