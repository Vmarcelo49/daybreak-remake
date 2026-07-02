// Function: FUN_00657390
// Address:  0x00657390
// Source:   batch_decompile (mass dump)
// Hash:     566487e6f3d30c6d


void __fastcall FUN_00657390(char *param_1)

{
  char *pcVar1;
  int *piVar2;
  int iVar3;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1[0x60] == '\0') {
    if (*param_1 < '\0') {
      if (*param_1 == -1) {
        if ((-1 < *(int *)(param_1 + 0xc)) && (-1 < *(int *)(param_1 + 0x10))) {
          if (((&DAT_006d1928)[*(int *)(param_1 + 0xc)] & 0x80) == 0) {
            if (((&DAT_006d1928)[*(int *)(param_1 + 0x10)] & 0x80) == 0) {
              param_1[0x38] = '\0';
              param_1[0x39] = '\0';
              param_1[0x3a] = '\0';
              param_1[0x3b] = '\0';
            }
            else {
              if (*(int *)(param_1 + 0x38) < 0) {
                param_1[0x38] = '\0';
                param_1[0x39] = '\0';
                param_1[0x3a] = '\0';
                param_1[0x3b] = '\0';
              }
              *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
            }
          }
          else {
            if (0 < *(int *)(param_1 + 0x38)) {
              param_1[0x38] = '\0';
              param_1[0x39] = '\0';
              param_1[0x3a] = '\0';
              param_1[0x3b] = '\0';
            }
            *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
          }
        }
        if ((-1 < *(int *)(param_1 + 4)) && (-1 < *(int *)(param_1 + 8))) {
          if (((&DAT_006d1928)[*(int *)(param_1 + 4)] & 0x80) == 0) {
            if (((&DAT_006d1928)[*(int *)(param_1 + 8)] & 0x80) == 0) {
              param_1[0x3c] = '\0';
              param_1[0x3d] = '\0';
              param_1[0x3e] = '\0';
              param_1[0x3f] = '\0';
            }
            else {
              if (*(int *)(param_1 + 0x3c) < 0) {
                param_1[0x3c] = '\0';
                param_1[0x3d] = '\0';
                param_1[0x3e] = '\0';
                param_1[0x3f] = '\0';
              }
              *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
            }
          }
          else {
            if (0 < *(int *)(param_1 + 0x3c)) {
              param_1[0x3c] = '\0';
              param_1[0x3d] = '\0';
              param_1[0x3e] = '\0';
              param_1[0x3f] = '\0';
            }
            *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -1;
          }
        }
        for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
          if (-1 < *(int *)(param_1 + local_10 * 4 + 0x14)) {
            if (((&DAT_006d1928)[*(int *)(param_1 + local_10 * 4 + 0x14)] & 0x80) == 0) {
              pcVar1 = param_1 + local_10 * 4 + 0x40;
              pcVar1[0] = '\0';
              pcVar1[1] = '\0';
              pcVar1[2] = '\0';
              pcVar1[3] = '\0';
            }
            else {
              *(int *)(param_1 + local_10 * 4 + 0x40) = *(int *)(param_1 + local_10 * 4 + 0x40) + 1;
            }
          }
        }
      }
      else {
        _memset(param_1 + 0x38,0,0x28);
      }
    }
    else {
      piVar2 = (int *)FUN_00404e20((int)*param_1);
      if (*piVar2 < -500) {
        if (0 < *(int *)(param_1 + 0x38)) {
          param_1[0x38] = '\0';
          param_1[0x39] = '\0';
          param_1[0x3a] = '\0';
          param_1[0x3b] = '\0';
        }
        *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
      }
      else {
        piVar2 = (int *)FUN_00404e20((int)*param_1);
        if (*piVar2 < 0x1f5) {
          param_1[0x38] = '\0';
          param_1[0x39] = '\0';
          param_1[0x3a] = '\0';
          param_1[0x3b] = '\0';
        }
        else {
          if (*(int *)(param_1 + 0x38) < 0) {
            param_1[0x38] = '\0';
            param_1[0x39] = '\0';
            param_1[0x3a] = '\0';
            param_1[0x3b] = '\0';
          }
          *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
        }
      }
      iVar3 = FUN_00404e20((int)*param_1);
      if (*(int *)(iVar3 + 4) < -500) {
        if (0 < *(int *)(param_1 + 0x3c)) {
          param_1[0x3c] = '\0';
          param_1[0x3d] = '\0';
          param_1[0x3e] = '\0';
          param_1[0x3f] = '\0';
        }
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -1;
      }
      else {
        iVar3 = FUN_00404e20((int)*param_1);
        if (*(int *)(iVar3 + 4) < 0x1f5) {
          param_1[0x3c] = '\0';
          param_1[0x3d] = '\0';
          param_1[0x3e] = '\0';
          param_1[0x3f] = '\0';
        }
        else {
          if (*(int *)(param_1 + 0x3c) < 0) {
            param_1[0x3c] = '\0';
            param_1[0x3d] = '\0';
            param_1[0x3e] = '\0';
            param_1[0x3f] = '\0';
          }
          *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
        }
      }
      for (local_c = 0; local_c < 8; local_c = local_c + 1) {
        if (-1 < *(int *)(param_1 + local_c * 4 + 0x14)) {
          iVar3 = FUN_00404e20((int)*param_1);
          if (*(char *)(iVar3 + 0x30 + *(int *)(param_1 + local_c * 4 + 0x14)) == '\0') {
            pcVar1 = param_1 + local_c * 4 + 0x40;
            pcVar1[0] = '\0';
            pcVar1[1] = '\0';
            pcVar1[2] = '\0';
            pcVar1[3] = '\0';
          }
          else {
            *(int *)(param_1 + local_c * 4 + 0x40) = *(int *)(param_1 + local_c * 4 + 0x40) + 1;
          }
        }
      }
    }
  }
  else {
    if ((*(uint *)(param_1 + 0x34) & 4) == 0) {
      if ((*(uint *)(param_1 + 0x34) & 8) == 0) {
        param_1[0x38] = '\0';
        param_1[0x39] = '\0';
        param_1[0x3a] = '\0';
        param_1[0x3b] = '\0';
      }
      else {
        if (*(int *)(param_1 + 0x38) < 0) {
          param_1[0x38] = '\0';
          param_1[0x39] = '\0';
          param_1[0x3a] = '\0';
          param_1[0x3b] = '\0';
        }
        *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
      }
    }
    else {
      if (0 < *(int *)(param_1 + 0x38)) {
        param_1[0x38] = '\0';
        param_1[0x39] = '\0';
        param_1[0x3a] = '\0';
        param_1[0x3b] = '\0';
      }
      *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
    }
    if ((*(uint *)(param_1 + 0x34) & 1) == 0) {
      if ((*(uint *)(param_1 + 0x34) & 2) == 0) {
        param_1[0x3c] = '\0';
        param_1[0x3d] = '\0';
        param_1[0x3e] = '\0';
        param_1[0x3f] = '\0';
      }
      else {
        if (*(int *)(param_1 + 0x3c) < 0) {
          param_1[0x3c] = '\0';
          param_1[0x3d] = '\0';
          param_1[0x3e] = '\0';
          param_1[0x3f] = '\0';
        }
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
      }
    }
    else {
      if (0 < *(int *)(param_1 + 0x3c)) {
        param_1[0x3c] = '\0';
        param_1[0x3d] = '\0';
        param_1[0x3e] = '\0';
        param_1[0x3f] = '\0';
      }
      *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -1;
    }
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
      if ((0x10 << ((byte)local_8 & 0x1f) & *(uint *)(param_1 + 0x34)) == 0) {
        pcVar1 = param_1 + local_8 * 4 + 0x40;
        pcVar1[0] = '\0';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
      }
      else {
        *(int *)(param_1 + local_8 * 4 + 0x40) = *(int *)(param_1 + local_8 * 4 + 0x40) + 1;
      }
    }
  }
  return;
}

