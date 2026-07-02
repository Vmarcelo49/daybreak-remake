// Function: FUN_00684930
// Address:  0x00684930
// Source:   batch_decompile (mass dump)
// Hash:     097a18b5eea4cf38


undefined4 *
FUN_00684930(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  undefined1 *puVar11;
  uint *local_d48;
  int local_d44;
  int *local_d40;
  undefined4 *local_d3c;
  int local_d38;
  int local_d34;
  int local_d30;
  int local_d2c;
  int local_d28;
  undefined4 *local_d24;
  int local_d20;
  int local_d1c;
  int local_d18;
  int local_d14;
  undefined4 *local_d10;
  int aiStack_d0c [63];
  int local_c10;
  undefined4 *local_c0c;
  int aiStack_c08 [63];
  int local_b0c [65];
  int local_a08 [65];
  int local_904 [65];
  undefined1 local_800 [2048];
  
  iVar1 = param_2[0x141];
  iVar2 = param_2[0x144];
  uVar6 = param_2[0x142];
  local_d48 = (uint *)0x0;
  if (0 < iVar1) {
    piVar10 = &local_c10;
    for (iVar9 = iVar1; iVar9 != 0; iVar9 = iVar9 + -1) {
      *piVar10 = -200;
      piVar10 = piVar10 + 1;
    }
  }
  if (0 < iVar1) {
    piVar10 = &local_d14;
    for (iVar9 = iVar1; iVar9 != 0; iVar9 = iVar9 + -1) {
      *piVar10 = -200;
      piVar10 = piVar10 + 1;
    }
    if (0 < iVar1) {
      piVar10 = local_a08;
      for (iVar9 = iVar1; iVar9 != 0; iVar9 = iVar9 + -1) {
        *piVar10 = 0;
        piVar10 = piVar10 + 1;
      }
    }
    if (0 < iVar1) {
      piVar10 = local_904;
      for (iVar9 = iVar1; iVar9 != 0; iVar9 = iVar9 + -1) {
        *piVar10 = 1;
        piVar10 = piVar10 + 1;
      }
      if (0 < iVar1) {
        piVar10 = local_b0c;
        for (iVar9 = iVar1; iVar9 != 0; iVar9 = iVar9 + -1) {
          *piVar10 = -1;
          piVar10 = piVar10 + 1;
        }
      }
    }
  }
  local_d38 = iVar1;
  local_d30 = iVar2;
  if (iVar1 == 0) {
    local_d48 = (uint *)FUN_00684e40(param_4,param_3,0,uVar6,local_800,uVar6,iVar2);
  }
  else {
    local_d44 = iVar1 + -1;
    if (local_d44 < 1) {
      return (undefined4 *)0x0;
    }
    puVar11 = local_800;
    puVar5 = param_2;
    do {
      iVar1 = FUN_00684e40(param_4,param_3,*puVar5,puVar5[1],puVar11,uVar6,iVar2);
      local_d48 = (uint *)((int)local_d48 + iVar1);
      puVar11 = puVar11 + 0x20;
      puVar5 = puVar5 + 1;
      local_d44 = local_d44 + -1;
      iVar1 = local_d38;
    } while (local_d44 != 0);
  }
  puVar5 = (undefined4 *)0x0;
  if (local_d48 != (uint *)0x0) {
    local_d20 = -200;
    local_d24 = (undefined4 *)0xffffff38;
    FUN_00685060(local_800,iVar1 + -1,&local_d20,&local_d24);
    local_c10 = local_d20;
    local_d14 = local_d20;
    local_d10 = local_d24;
    local_c0c = local_d24;
    local_d44 = 2;
    if (2 < iVar1) {
      local_d48 = (uint *)0x0;
      local_d40 = param_2 + 0x84;
      do {
        local_d18 = *local_d40;
        iVar1 = local_a08[local_d18];
        iVar9 = local_904[local_d18];
        if (local_b0c[iVar1] != iVar9) {
          local_b0c[iVar1] = iVar9;
          iVar4 = param_2[iVar1 + 0x82];
          local_d34 = *(int *)(iVar2 + 0x344 + iVar1 * 4);
          local_d1c = param_2[iVar9 + 0x82];
          local_d3c = *(undefined4 **)(iVar2 + 0x344 + iVar9 * 4);
          iVar2 = FUN_006854a0(&local_c10,&local_d14,iVar1);
          iVar3 = FUN_006854a0(&local_c10,&local_d14,iVar9);
          if ((iVar2 == -1) || (iVar3 == -1)) {
                    /* WARNING: Subroutine does not return */
            _exit(1);
          }
          iVar2 = FUN_00685270(local_d34,local_d3c,iVar2,iVar3,param_4,param_3,local_d30);
          iVar3 = local_d18;
          if (iVar2 == 0) {
            *(undefined4 *)((int)aiStack_c08 + (int)local_d48) = 0xffffff38;
            *(undefined4 *)((int)aiStack_d0c + (int)local_d48) = 0xffffff38;
            iVar2 = local_d30;
          }
          else {
            local_d28 = -200;
            local_d2c = -200;
            local_d34 = -200;
            local_d3c = (undefined4 *)0xffffff38;
            FUN_00685060(local_800 + iVar4 * 0x20,local_d18 - iVar4,&local_d28,&local_d2c);
            FUN_00685060(local_800 + iVar3 * 0x20,local_d1c - iVar3,&local_d34,&local_d3c);
            (&local_d14)[iVar1] = local_d28;
            if (iVar1 == 0) {
              local_c10 = local_d28;
            }
            *(int *)((int)aiStack_c08 + (int)local_d48) = local_d2c;
            *(int *)((int)aiStack_d0c + (int)local_d48) = local_d34;
            (&local_c10)[iVar9] = (int)local_d3c;
            if (iVar9 == 1) {
              local_d10 = local_d3c;
            }
            iVar2 = local_d30;
            if ((-1 < local_d2c) || (-1 < local_d34)) {
              iVar4 = iVar3 + -1;
              if (-1 < iVar4) {
                piVar10 = local_904 + iVar4;
                do {
                  if (*piVar10 != iVar9) break;
                  iVar4 = iVar4 + -1;
                  *piVar10 = local_d44;
                  piVar10 = piVar10 + -1;
                } while (-1 < iVar4);
              }
              iVar3 = iVar3 + 1;
              if (iVar3 < local_d38) {
                piVar10 = local_a08 + iVar3;
                do {
                  if (*piVar10 != iVar1) break;
                  iVar3 = iVar3 + 1;
                  *piVar10 = local_d44;
                  piVar10 = piVar10 + 1;
                } while (iVar3 < local_d38);
              }
            }
          }
        }
        local_d40 = local_d40 + 1;
        local_d48 = (uint *)((int)local_d48 + 4);
        local_d44 = local_d44 + 1;
        iVar1 = local_d38;
      } while (local_d44 < local_d38);
    }
    puVar5 = (undefined4 *)FUN_0067a2c0(param_1,iVar1 * 4);
    local_d3c = puVar5;
    uVar6 = FUN_006854a0(&local_c10,&local_d14,0);
    *puVar5 = uVar6;
    uVar6 = FUN_006854a0(&local_c10,&local_d14,1);
    puVar5[1] = uVar6;
    local_d44 = 2;
    if (2 < iVar1) {
      local_d48 = puVar5 + 2;
      local_d40 = (int *)(iVar2 + 0x34c);
      piVar10 = param_2 + 0xc3;
      do {
        uVar7 = FUN_00684df0(*(undefined4 *)(iVar2 + 0x344 + piVar10[0x3f] * 4),
                             *(undefined4 *)(iVar2 + 0x344 + *piVar10 * 4),puVar5[piVar10[0x3f]],
                             puVar5[*piVar10],*local_d40);
        uVar8 = FUN_006854a0(&local_c10,&local_d14,local_d44);
        if (((int)uVar8 < 0) || (uVar7 == uVar8)) {
          *local_d48 = uVar7 | 0x8000;
        }
        else {
          *local_d48 = uVar8;
        }
        local_d44 = local_d44 + 1;
        piVar10 = piVar10 + 1;
        local_d40 = local_d40 + 1;
        local_d48 = local_d48 + 1;
        puVar5 = local_d3c;
      } while (local_d44 < local_d38);
    }
  }
  return puVar5;
}

