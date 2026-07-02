// ============================================
// Address:  0x006680f0
// Original: FUN_006680f0
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_006680f0(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  void *pvVar5;
  float10 fVar6;
  double dVar7;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  local_c = 0;
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    *param_1 = param_1[1];
  }
  else {
    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0') {
      FUN_006536c0();
      FUN_00654170();
    }
  }
  cVar1 = FUN_00653620(param_1,param_2);
  if (cVar1 == '\0') {
    FUN_00654170();
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00653a70();
    param_1[2] = uVar2;
    local_8 = 0;
    iVar3 = FUN_006778e0(param_1,param_1 + 4,0,0,PTR_FUN_006b77c8,PTR_FUN_006b77cc,PTR_FUN_006b77d0)
    ;
    if (iVar3 < 0) {
      FUN_006536c0();
      FUN_00654170();
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_00679700(param_1 + 4);
      param_1[0xb8] = uVar2;
      if (param_1[0x4c3] != 0) {
        _free((void *)param_1[0x4c3]);
        param_1[0x4c3] = 0;
      }
      dVar7 = (double)(*(int *)(param_1[0xb8] + 4) * *(int *)(param_1[0xb8] + 8));
      fVar6 = (float10)FUN_00678520(param_1 + 4,0xffffffff,dVar7);
      FUN_0066d020((double)(fVar6 * (float10)dVar7 + fVar6 * (float10)dVar7));
      uVar4 = FUN_0066b668();
      pvVar5 = operator_new(uVar4);
      param_1[0x4c3] = pvVar5;
      while (local_c == 0) {
        iVar3 = FUN_00679740(param_1 + 4,param_1[0x4c3] + local_8,0x1000,0,2,1,local_10);
        if (iVar3 == 0) {
          local_c = 1;
        }
        else {
          if (iVar3 < 0) {
            FUN_006777e0();
            return 0;
          }
          local_8 = local_8 + iVar3;
        }
      }
      *(undefined2 *)(param_1 + 0x4be) = 1;
      *(undefined2 *)((int)param_1 + 0x12fa) = *(undefined2 *)(param_1[0xb8] + 4);
      param_1[0x4bf] = *(undefined4 *)(param_1[0xb8] + 8);
      *(undefined2 *)((int)param_1 + 0x1306) = 0x10;
      iVar3 = (uint)*(ushort *)((int)param_1 + 0x12fa) * (uint)*(ushort *)((int)param_1 + 0x1306);
      *(short *)(param_1 + 0x4c1) = (short)((int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3);
      param_1[0x4c0] = (uint)*(ushort *)(param_1 + 0x4c1) * param_1[0x4bf];
      *(undefined2 *)(param_1 + 0x4c2) = 0;
      FUN_00668820();
      FUN_006777e0();
      uVar2 = 1;
    }
  }
  return uVar2;
}

