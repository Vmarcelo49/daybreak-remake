// ============================================
// Address:  0x00646500
// Original: FUN_00646500
// Status:   unreviewed
// ============================================


void FUN_00646500(float param_1,float param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_34;
  tagRECT local_2c;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  cVar1 = FUN_00660a10();
  if (cVar1 != '\0') {
    local_10 = FUN_006472b0();
    local_c = FUN_006472f0();
    iVar2 = FUN_006472d0();
    if (local_10 + local_c < iVar2) {
      local_34 = FUN_006472d0();
    }
    else {
      local_34 = local_10 + local_c;
    }
    local_8 = local_34;
    FUN_00655d60(param_1,param_2);
    for (local_14 = 0; local_14 < local_8; local_14 = local_14 + 1) {
      if ((local_14 < local_10) || (local_10 + local_c <= local_14)) {
        iVar2 = FUN_0068de10();
        if (iVar2 != 0) {
          FUN_00655830((float)local_14 * 8.0 + param_1 + 96.0,param_2 + 24.0,local_14,0);
        }
      }
      else {
        local_1c = FUN_00647290();
        local_18 = 0;
        iVar3 = FUN_0066b668();
        iVar3 = iVar3 + 0x2a;
        iVar2 = FUN_0066b668();
        iVar2 = iVar2 + 0x68 + local_14 * 8;
        iVar4 = FUN_0066b668();
        iVar4 = iVar4 + 0x17;
        iVar5 = FUN_0066b668();
        SetRect(&local_2c,iVar5 + 0x60 + local_14 * 8,iVar4,iVar2,iVar3);
        switch(*(undefined1 *)(local_1c + (local_14 - local_10))) {
        case 0:
          local_18 = -1;
          iVar3 = FUN_0066b668();
          iVar3 = iVar3 + 0x2a;
          iVar2 = FUN_0066b668();
          iVar2 = iVar2 + 0x68 + local_14 * 8;
          iVar4 = FUN_0066b668();
          iVar4 = iVar4 + 0x28;
          iVar5 = FUN_0066b668();
          SetRect(&local_2c,iVar5 + 0x60 + local_14 * 8,iVar4,iVar2,iVar3);
          break;
        case 1:
          local_18 = -0x9f9f30;
          break;
        case 2:
          local_18 = -0x7f7f80;
          break;
        case 3:
          local_18 = -0x9f9f10;
          iVar3 = FUN_0066b668();
          iVar3 = iVar3 + 0x2a;
          iVar2 = FUN_0066b668();
          iVar2 = iVar2 + 0x68 + local_14 * 8;
          iVar4 = FUN_0066b668();
          iVar4 = iVar4 + 0x28;
          iVar5 = FUN_0066b668();
          SetRect(&local_2c,iVar5 + 0x60 + local_14 * 8,iVar4,iVar2,iVar3);
        }
        if (local_18 != 0) {
          FUN_00651820(&local_2c,local_18);
        }
        iVar2 = FUN_0068de10();
        if (iVar2 != 0) {
          FUN_00655830((float)local_14 * 8.0 + param_1 + 96.0,param_2 + 24.0,local_14 - local_10,0);
        }
      }
    }
    FUN_00655d60((float)local_10 * 8.0 + param_1 + 96.0,param_2 + 32.0);
  }
  return;
}

