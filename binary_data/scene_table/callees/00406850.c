// Called by LoadNextScene
// Address: 0x00406850


void __thiscall FUN_00406850(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined1 local_14 [4];
  int local_10;
  int *local_c;
  char local_5;
  
  FUN_00657390();
  local_c = &DAT_006cae94 + param_2 * 0x19;
  if ((*(int *)(param_1 + 0x2e28 + param_2 * 4) < 0) &&
     (((*local_c != 0 || ((&DAT_006cae98)[param_2 * 0x19] != 0)) ||
      ((&DAT_006cae9c)[param_2 * 0x19] != 0)))) {
    *(int *)(param_1 + 0x2e28 + param_2 * 4) = param_2;
  }
  local_5 = *(char *)(param_1 + 0x2e28 + param_2 * 4);
  local_10 = *(int *)(param_1 + 0x2e98 + param_2 * 4);
  switch(*(undefined4 *)(param_1 + 0x2e98 + param_2 * 4)) {
  case 0:
    if ((((&DAT_006caea0)[param_2 * 0x19] == 1) && (*(int *)(param_1 + 0x2e98) == 0)) &&
       (*(int *)(param_1 + 0x2e9c) == 0)) {
      FUN_0064aed0(1);
      *(undefined4 *)(param_1 + 0x2e18) = 0;
      return;
    }
    iVar1 = FUN_00403aa0((&DAT_006cae98)[param_2 * 0x19]);
    if (iVar1 == 1) {
      if (local_c[1] < 1) {
        if (*(int *)(param_1 + 0x2e28 + param_2 * 4) == 0) {
          *(undefined4 *)(param_1 + 0x2e28 + param_2 * 4) = 2;
        }
        else if (*(int *)(param_1 + 0x2e28 + param_2 * 4) < 2) {
          *(int *)(param_1 + 0x2e28 + param_2 * 4) = *(int *)(param_1 + 0x2e28 + param_2 * 4) + -1;
        }
        else {
          *(undefined4 *)(param_1 + 0x2e28 + param_2 * 4) = 1;
        }
      }
      else if (*(int *)(param_1 + 0x2e28 + param_2 * 4) < 2) {
        *(int *)(param_1 + 0x2e28 + param_2 * 4) = *(int *)(param_1 + 0x2e28 + param_2 * 4) + 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x2e28 + param_2 * 4) = 0;
      }
      FUN_0064aed0(2);
    }
    else {
      iVar1 = FUN_00403aa0(*local_c);
      if (iVar1 == 1) {
        if (*(int *)(param_1 + 0x2e28 + param_2 * 4) == 2) {
          *(undefined4 *)(param_1 + 0x2e28 + param_2 * 4) = 3;
        }
        else if (*(int *)(param_1 + 0x2e28 + param_2 * 4) == 3) {
          *(undefined4 *)(param_1 + 0x2e28 + param_2 * 4) = 2;
        }
        FUN_0064aed0(2);
      }
    }
    if (*(int *)(param_1 + 0x2e28 + param_2 * 4) < 2) {
      if (((local_c[3] == 1) && (*(int *)(param_1 + 0x2e90 + local_5 * 4) < 0)) &&
         ((*(int *)(param_1 + 0x2e40 + local_5 * 4) == param_2 ||
          (*(int *)(param_1 + 0x2e40 + local_5 * 4) == 4)))) {
        if (*(int *)(param_1 + 0x2e40 + local_5 * 4) == param_2) {
          *(undefined4 *)(param_1 + 0x2ea0 + param_2 * 4) = 0xffffffff;
        }
        *(undefined4 *)(param_1 + 0x2e40 + local_5 * 4) = 0xffffffff;
        (&DAT_006cfb4c)[local_5] = 0;
        *(undefined1 *)(param_1 + 0x2ea8 + (int)local_5) = 0;
      }
      else if (((local_c[2] == 1) && (*(int *)(param_1 + 0x2e90 + local_5 * 4) < 0)) &&
              (*(int *)(param_1 + 0x2e40 + local_5 * 4) < 0)) {
        if ((local_c[5] == 0) ||
           ('\x05' < (char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + param_2])) {
          (&DAT_006cfb4c)[local_5] = 0;
        }
        else {
          (&DAT_006cfb4c)[local_5] = 1;
        }
        FUN_0064aed0(0);
        *(undefined1 *)(param_1 + 0x2ea8 + (int)local_5) = 0;
        *(int *)(param_1 + 0x2e90 + local_5 * 4) = param_2;
        *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 3;
        *(undefined4 *)(param_1 + 0x2e30 + local_5 * 4) = 0;
      }
    }
    else if (local_c[2] == 1) {
      if (((*(int *)(param_1 + 0x2e28 + param_2 * 4) == 3) && (*(int *)(param_1 + 0x2e98) == 0)) &&
         (*(int *)(param_1 + 0x2e9c) == 0)) {
        FUN_0064aed0(1);
        *(undefined4 *)(param_1 + 0x2e18) = 0;
        return;
      }
      if (((*(int *)(param_1 + 0x2e28 + param_2 * 4) == 2) && (*(int *)(param_1 + 0x2e98) == 0)) &&
         (*(int *)(param_1 + 0x2e9c) == 0)) {
        FUN_0064aed0(0);
        *(undefined4 *)(param_1 + 0x2e18) = 2;
        return;
      }
    }
    break;
  case 1:
    iVar1 = FUN_00403aa0((&DAT_006cae98)[param_2 * 0x19]);
    if ((iVar1 == 1) && (*(int *)(param_1 + 0x2ea0 + param_2 * 4) < 0)) {
      FUN_0064aed0(2);
      uVar4 = *(int *)(param_1 + 0x2e30 + local_5 * 4) + 2 + local_c[1] & 0x80000001;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
      }
      *(uint *)(param_1 + 0x2e30 + local_5 * 4) = uVar4;
    }
    if (local_c[2] == 1) {
      FUN_0064aed0(0);
      if (*(int *)(param_1 + 0x2e30 + local_5 * 4) == 0) {
        *(int *)(param_1 + 0x2ea0 + param_2 * 4) = (int)local_5;
        *(int *)(param_1 + 0x2e40 + local_5 * 4) = param_2;
      }
      else {
        *(undefined4 *)(param_1 + 0x2e40 + local_5 * 4) = 4;
      }
      *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 8;
      *(undefined4 *)(param_1 + 0x2eac + local_5 * 4) = 0x40800000;
      *(undefined1 *)(param_1 + 0x2ea8 + (int)local_5) = 1;
      FUN_0065b1d0(*(undefined4 *)(param_1 + 0x1a4));
      uVar2 = FUN_00649770((int)(char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + (int)local_5]
                          );
      wsprintfA((LPSTR)(param_1 + 4),"data/voice/entry/%s.wav",uVar2);
      puVar3 = (undefined4 *)FUN_0065b0d0(local_14,param_1 + 4);
      *(undefined4 *)(param_1 + 0x1a4) = *puVar3;
      FUN_0065b330(*(undefined4 *)(param_1 + 0x1a4),0);
    }
    else if (local_c[3] == 1) {
      FUN_0064aed0(1);
      if (*(int *)(param_1 + 0x2ea0 + param_2 * 4) == (int)local_5) {
        *(undefined4 *)(param_1 + 0x2ea0 + param_2 * 4) = 0xffffffff;
      }
      *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 4;
      *(undefined4 *)(param_1 + 0x2e30 + local_5 * 4) =
           *(undefined4 *)(param_1 + 0x2e70 + local_5 * 4);
      *(undefined4 *)(param_1 + 0x2e40 + local_5 * 4) = 0xffffffff;
    }
    break;
  case 3:
    iVar1 = FUN_00403aa0((&DAT_006cae98)[param_2 * 0x19]);
    if (iVar1 == 1) {
      FUN_0064aed0(2);
      *(int *)(param_1 + 0x2e30 + local_5 * 4) =
           (*(int *)(param_1 + 0x2e30 + local_5 * 4) + 3 + local_c[1]) % 3;
    }
    *(undefined4 *)(param_1 + 0x2e60 + local_5 * 4) =
         *(undefined4 *)(param_1 + 0x2e30 + local_5 * 4);
    if (local_c[2] == 1) {
      FUN_0064aed0(0);
      *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 4;
      *(undefined4 *)(param_1 + 0x2e30 + local_5 * 4) = 0;
    }
    else if (local_c[3] == 1) {
      FUN_0064aed0(1);
      if (*(int *)(param_1 + 0x2ea0 + param_2 * 4) == (int)local_5) {
        *(undefined4 *)(param_1 + 0x2ea0 + param_2 * 4) = 0xffffffff;
      }
      *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 0;
      *(undefined4 *)(param_1 + 0x2e40 + local_5 * 4) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x2e60 + local_5 * 4) = 0xffffffff;
      *(undefined4 *)(param_1 + 0x2e90 + local_5 * 4) = 0xffffffff;
      (&DAT_006cfb4c)[local_5] = 0;
    }
    break;
  case 4:
    iVar1 = FUN_00403aa0((&DAT_006cae98)[param_2 * 0x19]);
    if (iVar1 == 1) {
      FUN_0064aed0(2);
      *(int *)(param_1 + 0x2e30 + local_5 * 4) =
           (*(int *)(param_1 + 0x2e30 + local_5 * 4) + 3 + local_c[1]) % 3;
    }
    *(undefined4 *)(param_1 + 0x2e70 + local_5 * 4) =
         *(undefined4 *)(param_1 + 0x2e30 + local_5 * 4);
    if (local_c[2] == 1) {
      FUN_0064aed0(0);
      *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 1;
      if (*(int *)(param_1 + 0x2ea0 + param_2 * 4) == (int)local_5) {
        *(undefined4 *)(param_1 + 0x2ea0 + param_2 * 4) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x2e30 + local_5 * 4) = 0;
      }
      else {
        *(uint *)(param_1 + 0x2e30 + local_5 * 4) =
             (uint)(-1 < *(int *)(param_1 + 0x2ea0 + param_2 * 4));
      }
    }
    else if (local_c[3] == 1) {
      FUN_0064aed0(1);
      *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 3;
      *(undefined4 *)(param_1 + 0x2e30 + local_5 * 4) =
           *(undefined4 *)(param_1 + 0x2e60 + local_5 * 4);
    }
    break;
  case 8:
    if (*(float *)(param_1 + 0x2eac + local_5 * 4) <= 1.0) {
      FUN_0064aed0(3);
      *(undefined4 *)(param_1 + 0x2e98 + param_2 * 4) = 0;
      *(undefined4 *)(param_1 + 0x2e90 + local_5 * 4) = 0xffffffff;
    }
    else {
      *(float *)(param_1 + 0x2eac + local_5 * 4) = *(float *)(param_1 + 0x2eac + local_5 * 4) - 0.2;
    }
  }
  if (((*(int *)(param_1 + 0x2e98 + param_2 * 4) == 4) ||
      (*(int *)(param_1 + 0x2e98 + param_2 * 4) == 3)) ||
     (*(int *)(param_1 + 0x2e98 + param_2 * 4) == 1)) {
    if (*local_c == 1) {
      *(int *)(param_1 + 0x2e80 + local_5 * 4) =
           (*(int *)(param_1 + 0x2e80 + local_5 * 4) + 1) %
           (int)(char)(&DAT_006b71c0)
                      [(char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + (int)local_5]];
    }
    else if (*local_c == -1) {
      *(int *)(param_1 + 0x2e80 + local_5 * 4) =
           (*(int *)(param_1 + 0x2e80 + local_5 * 4) + -1 +
           (int)(char)(&DAT_006b71c0)
                      [(char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + (int)local_5]]) %
           (int)(char)(&DAT_006b71c0)
                      [(char)(&DAT_006b710c)[*(int *)(param_1 + 0x2e20) * 2 + (int)local_5]];
    }
  }
  if (*(int *)(param_1 + 0x2e98 + param_2 * 4) != local_10) {
    *(undefined4 *)(param_1 + 0x2eb4 + param_2 * 4) = 0x43960000;
  }
  if (0.0 < *(float *)(param_1 + 0x2eb4 + param_2 * 4)) {
    *(float *)(param_1 + 0x2eb4 + param_2 * 4) = *(float *)(param_1 + 0x2eb4 + param_2 * 4) - 20.0;
  }
  return;
}

