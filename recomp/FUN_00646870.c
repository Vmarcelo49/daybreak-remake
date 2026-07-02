// ============================================
// Address:  0x00646870
// Original: FUN_00646870
// Status:   unreviewed
// ============================================


void __thiscall FUN_00646870(int param_1,float param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float10 fVar7;
  undefined4 uVar8;
  float fVar9;
  float fVar10;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  iVar3 = FUN_0068de10();
  if (iVar3 != 0) {
    iVar3 = *(int *)(param_1 + 0x1278);
    local_8 = iVar3 + -8;
    if (local_8 < 0) {
      local_8 = 0;
    }
    local_14 = 0;
    for (local_10 = local_8; local_10 < iVar3; local_10 = local_10 + 1) {
      iVar4 = FUN_00647370(local_10);
      fVar2 = 800.0 - (float)(600 - iVar4) * 3.0;
      fVar7 = (float10)FUN_006473a0(local_10);
      fVar1 = (float)(fVar7 + (float10)5.0 + (float10)param_2);
      iVar4 = FUN_006473d0(local_10);
      fVar10 = ((float)iVar4 * 8.0 + 96.0 + 16.0) / 224.0;
      iVar4 = FUN_00647340(local_10);
      if (iVar4 == 1) {
        iVar4 = FUN_00647370(local_10);
        if (400 < iVar4) {
          FUN_0040da60(fVar10,0x3f800000);
          FUN_00655d60(0x43870000,0xc1400000);
          uVar6 = 0x41400000;
          uVar8 = 0x438e0000;
          uVar5 = FUN_00647310(local_10);
          FUN_00646db0(uVar5,uVar8,uVar6);
          FUN_00655830(0x43c20000,0x41400000,0,local_14 << 1);
        }
      }
      else {
        FUN_0040da60(fVar10,0x3f800000);
        FUN_00655d60(fVar2,fVar1);
        fVar10 = fVar1 + 24.0;
        fVar9 = fVar2 + 14.0;
        uVar6 = FUN_00647310(local_10);
        FUN_00646db0(uVar6,fVar9,fVar10);
        FUN_00655830(fVar2 + 14.0 + 96.0 + 8.0,(fVar1 + 48.0) - 24.0,0,local_14 << 1);
      }
      local_14 = local_14 + 1;
    }
  }
  return;
}

