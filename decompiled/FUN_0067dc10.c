// Function: FUN_0067dc10
// Address:  0x0067dc10
// Source:   batch_decompile (mass dump)
// Hash:     87d90894d7cfdd77


uint * FUN_0067dc10(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  uint *_Memory;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  int local_90;
  int *local_88;
  uint local_84 [33];
  
  iVar4 = param_3;
  if (param_3 == 0) {
    iVar4 = param_2;
  }
  _Memory = _malloc(iVar4 << 2);
  puVar6 = local_84;
  for (iVar4 = 0x21; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  local_90 = 0;
  if (0 < param_2) {
    local_88 = param_1;
    puVar6 = _Memory;
    do {
      iVar4 = *local_88;
      if (iVar4 < 1) {
        if (param_3 == 0) {
          puVar6 = puVar6 + 1;
        }
      }
      else {
        uVar3 = local_84[iVar4];
        puVar2 = local_84 + iVar4;
        if ((iVar4 < 0x20) && (uVar3 >> ((byte)iVar4 & 0x1f) != 0)) {
          _free(_Memory);
          return (uint *)0x0;
        }
        *puVar6 = uVar3;
        puVar6 = puVar6 + 1;
        iVar5 = iVar4;
        do {
          if ((*puVar2 & 1) != 0) {
            if (iVar5 == 1) {
              local_84[1] = local_84[1] + 1;
            }
            else {
              local_84[iVar5] = local_84[iVar5 + -1] << 1;
            }
            break;
          }
          iVar5 = iVar5 + -1;
          *puVar2 = *puVar2 + 1;
          puVar2 = puVar2 + -1;
        } while (0 < iVar5);
        iVar4 = iVar4 + 1;
        if (iVar4 < 0x21) {
          puVar2 = local_84 + iVar4;
          do {
            uVar1 = *puVar2;
            if (uVar1 >> 1 != uVar3) break;
            *puVar2 = puVar2[-1] << 1;
            iVar4 = iVar4 + 1;
            puVar2 = puVar2 + 1;
            uVar3 = uVar1;
          } while (iVar4 < 0x21);
        }
      }
      local_90 = local_90 + 1;
      local_88 = local_88 + 1;
    } while (local_90 < param_2);
    if (0 < param_2) {
      local_90 = param_2;
      puVar6 = _Memory;
      do {
        iVar4 = *param_1;
        uVar3 = 0;
        iVar5 = 0;
        if (0 < iVar4) {
          do {
            uVar3 = uVar3 * 2 | *puVar6 >> ((byte)iVar5 & 0x1f) & 1;
            iVar5 = iVar5 + 1;
          } while (iVar5 < iVar4);
        }
        if ((param_3 == 0) || (iVar4 != 0)) {
          *puVar6 = uVar3;
          puVar6 = puVar6 + 1;
        }
        param_1 = param_1 + 1;
        local_90 = local_90 + -1;
      } while (local_90 != 0);
    }
  }
  return _Memory;
}

