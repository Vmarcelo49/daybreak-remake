// Function: FUN_005949e0
// Address:  0x005949e0
// Source:   batch_decompile (mass dump)
// Hash:     b932ed8e58b74cfa


uint __fastcall FUN_005949e0(uint param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  float10 fVar4;
  float10 fVar5;
  int local_14;
  uint local_10;
  float local_c;
  uint local_8;
  
  FUN_0042cc90();
  *(undefined4 *)(param_1 + 0x830) = 0;
  local_c = 1.0;
  local_8 = 100;
  local_10 = 100;
  *(undefined4 *)(param_1 + 0x28c) = 0;
  for (local_14 = 0; local_14 < 3; local_14 = local_14 + 1) {
    *(undefined4 *)(param_1 + 0x2b0 + local_14 * 4) = 0;
    *(undefined4 *)(param_1 + 0x280 + local_14 * 4) = 0;
  }
  switch(*(undefined1 *)(param_1 + 0x310)) {
  case 0:
    FUN_00421c80();
    break;
  case 1:
    FUN_00421c80();
    local_c = 0.25;
    local_8 = 0x32;
    local_10 = 200;
    break;
  case 2:
    FUN_00421c80();
    local_c = 3.0;
    local_8 = 200;
    local_10 = 0x32;
    break;
  case 3:
    piVar1 = (int *)FUN_00658a10(0);
    if (*(int *)(param_1 + 0x300) != *(int *)(*piVar1 + 0x300)) {
      *(undefined4 *)(param_1 + 0x28c) = 1;
    }
    break;
  case 4:
    piVar1 = (int *)FUN_00658a10(0);
    if (*(int *)(param_1 + 0x300) == *(int *)(*piVar1 + 0x300)) {
      *(undefined4 *)(param_1 + 0x28c) = 1;
    }
    break;
  case 5:
    FUN_00421c80();
    local_c = 4.0;
    local_8 = 5;
    local_10 = 5;
  }
  uVar2 = param_1;
  if (((*(char *)(param_1 + 0x845) == '\0') &&
      (*(int *)(param_1 + 0x32c) <= *(int *)(param_1 + 0x83c))) &&
     ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
    *(undefined4 *)(param_1 + 0x288) = 1;
    *(undefined4 *)(param_1 + 0x284) = 1;
  }
  else if (((*(char *)(param_1 + 0x844) == '\0') &&
           (*(int *)(param_1 + 0x324) <= *(int *)(param_1 + 0x838))) &&
          (*(int *)(param_1 + 0xadec) < 300)) {
    *(undefined4 *)(param_1 + 0x288) = 1;
    *(undefined4 *)(param_1 + 0x284) = 1;
  }
  else {
    if (((*(char *)(param_1 + 0x84) != '\0') && (*(int *)(param_1 + 0x86c) == 0)) &&
       ((0x28a < *(int *)(param_1 + 0x834) &&
        ((fVar4 = (float10)FUN_0042d980(), (float10)40000.0 < fVar4 &&
         (uVar2 = FUN_0065d150(), uVar2 % 100 == 1)))))) {
      uVar2 = FUN_0065d150();
      *(uint *)(param_1 + 0x86c) = uVar2 % 0x78 + 10;
    }
    if ((((*(char *)(param_1 + 0x84) != '\0') &&
         (*(float *)(param_1 + 0x80) < 300.0 != (*(float *)(param_1 + 0x80) == 300.0))) &&
        (0x28a < *(int *)(param_1 + 0x834))) &&
       ((fVar4 = (float10)FUN_0042d980(), (float10)250000.0 < fVar4 &&
        (uVar2 = FUN_0065d150(), uVar2 % 100 < 10)))) {
      uVar2 = FUN_0065d150();
      *(uint *)(param_1 + 0x86c) = uVar2 % 0x78 + 0x3c;
    }
    if ((*(int *)(param_1 + 0x870) == 0) && (uVar2 = FUN_0065d150(), uVar2 % 500 == 0)) {
      uVar2 = FUN_0065d150();
      *(uint *)(param_1 + 0x870) = uVar2 % 0xb4 + 0xb4;
    }
    if ((*(int *)(param_1 + 0x870) == 0) &&
       ((uVar2 = FUN_0065d150(), uVar2 % 100 == 0 ||
        ((uVar2 = FUN_0065d150(), uVar2 % 0x55 == 0 && (*(char *)(param_1 + 0x310) == '\x02')))))) {
      uVar2 = FUN_0065d150();
      *(uint *)(param_1 + 0x870) = uVar2 % 0xb4;
    }
    if (0 < *(int *)(param_1 + 0x870)) {
      *(int *)(param_1 + 0x870) = *(int *)(param_1 + 0x870) + -1;
      *(undefined4 *)(param_1 + 0x288) = 4;
    }
    if (*(int *)(param_1 + 0x864) < 1) {
      if (*(int *)(param_1 + 0x864) < 0) {
        *(int *)(param_1 + 0x864) = *(int *)(param_1 + 0x864) + 1;
        *(undefined4 *)(param_1 + 0x278) = 0xffffffff;
        uVar2 = FUN_0065d150();
        if ((uVar2 % 100 < ((uint)(*(char *)(param_1 + 0x310) == '\x05') * 3 + 1) * 10) &&
           (*(int *)(param_1 + 0x86c) < 1)) {
          *(undefined4 *)(param_1 + 0x830) = 3;
        }
        uVar2 = FUN_0065d150();
        if (((uVar2 % 100 < ((uint)(*(char *)(param_1 + 0x310) == '\x05') * 3 + 1) * 10) &&
            (500 < *(int *)(param_1 + 0x834))) && (*(int *)(param_1 + 0x86c) < 1)) {
          *(undefined4 *)(param_1 + 0x830) = 3;
        }
      }
      else {
        uVar2 = FUN_0065d150();
        if (uVar2 % 100 == 0) {
          uVar2 = FUN_0065d150();
          *(uint *)(param_1 + 0x864) = uVar2 % 400 - 200;
        }
      }
    }
    else {
      *(int *)(param_1 + 0x864) = *(int *)(param_1 + 0x864) + -1;
      *(undefined4 *)(param_1 + 0x278) = 1;
      uVar2 = FUN_0065d150();
      if ((uVar2 % 100 < ((uint)(*(char *)(param_1 + 0x310) == '\x05') * 3 + 1) * 10) &&
         (*(int *)(param_1 + 0x86c) < 1)) {
        *(undefined4 *)(param_1 + 0x830) = 4;
      }
      uVar2 = FUN_0065d150();
      if (((uVar2 % 100 < ((uint)(*(char *)(param_1 + 0x310) == '\x05') * 3 + 1) * 10) &&
          (500 < *(int *)(param_1 + 0x834))) && (*(int *)(param_1 + 0x86c) < 1)) {
        *(undefined4 *)(param_1 + 0x830) = 4;
      }
    }
    if (*(int *)(param_1 + 0x868) < 1) {
      if (*(int *)(param_1 + 0x868) < 0) {
        *(int *)(param_1 + 0x868) = *(int *)(param_1 + 0x868) + 1;
        *(undefined4 *)(param_1 + 0x27c) = 1;
        uVar2 = FUN_0065d150();
        if ((((int)(uVar2 % 0xfa) < (int)((uint)(*(char *)(param_1 + 0x310) != '\x05') * -2 + 3)) &&
            (*(int *)(param_1 + 0x86c) < 1)) && (*(int *)(param_1 + 0x830) == 0)) {
          *(undefined4 *)(param_1 + 0x830) = 2;
        }
      }
      else {
        fVar4 = (float10)FUN_0042d980();
        if ((float10)1e+06 * (float10)local_c * (float10)local_c <= fVar4) {
          uVar2 = FUN_0065d150();
          *(uint *)(param_1 + 0x868) = uVar2 % 300 - 0x3c;
        }
        else {
          uVar2 = FUN_0065d150();
          *(uint *)(param_1 + 0x868) = uVar2 % 300 - 0xf0;
        }
      }
    }
    else {
      *(int *)(param_1 + 0x868) = *(int *)(param_1 + 0x868) + -1;
      *(undefined4 *)(param_1 + 0x27c) = 0xffffffff;
      uVar2 = FUN_0065d150();
      if (((uVar2 % 500 < (uint)(*(char *)(param_1 + 0x310) == '\x05') * 9 + 1) &&
          (*(int *)(param_1 + 0x86c) < 1)) && (*(int *)(param_1 + 0x830) == 0)) {
        *(undefined4 *)(param_1 + 0x830) = 1;
      }
      uVar2 = FUN_0065d150();
      if ((((int)(uVar2 % 500) < (int)(((uint)(*(char *)(param_1 + 0x310) != '\x05') * -2 + 3) * 10)
           ) && (500 < *(int *)(param_1 + 0x834))) &&
         ((fVar4 = (float10)FUN_0042d980(),
          (float10)1e+06 * (float10)local_c * (float10)local_c < fVar4 &&
          ((*(int *)(param_1 + 0x86c) < 1 && (*(int *)(param_1 + 0x830) == 0)))))) {
        *(undefined4 *)(param_1 + 0x830) = 1;
      }
    }
    if (0 < *(int *)(param_1 + 0x86c)) {
      *(undefined4 *)(param_1 + 0x280) = 3;
      if (*(char *)(param_1 + 0x84) == '\0') {
        *(undefined4 *)(param_1 + 0x280) = 4;
      }
      *(int *)(param_1 + 0x86c) = *(int *)(param_1 + 0x86c) + -1;
    }
    if (((*(char *)(param_1 + 0x84) != '\0') && (*(int *)(param_1 + 0xadec) != 0x28)) &&
       (*(int *)(param_1 + 0xadec) != 0x29)) {
      *(undefined4 *)(param_1 + 0x86c) = 0;
    }
    fVar4 = (float10)FUN_0042d980();
    if ((fVar4 < (float10)160000.0) && (uVar2 = FUN_0065d150(), uVar2 % 100 < local_10)) {
      uVar2 = FUN_0065d150();
      if (((uVar2 % 100 == 0) ||
          ((uVar2 = FUN_0065d150(), uVar2 % 0x4b == 0 && (*(char *)(param_1 + 0x310) == '\x01'))))
         && (fVar4 = (float10)FUN_0042d980(), fVar4 < (float10)90000.0)) {
        *(undefined4 *)(param_1 + 0x278) = 0;
        *(undefined4 *)(param_1 + 0x27c) = 0;
        *(undefined4 *)(param_1 + 0x2b4) = 1;
        return param_1;
      }
      uVar2 = FUN_0065d150();
      if ((uVar2 % 100 == 0) ||
         ((uVar2 = FUN_0065d150(), uVar2 % 0x4b == 0 && (*(char *)(param_1 + 0x310) == '\x01')))) {
        *(undefined4 *)(param_1 + 0x278) = 0;
        *(undefined4 *)(param_1 + 0x27c) = 0xffffffff;
        *(undefined4 *)(param_1 + 0x2b4) = 1;
        return param_1;
      }
      uVar2 = FUN_0065d150();
      if (((uVar2 % 100 == 0) ||
          ((uVar2 = FUN_0065d150(), uVar2 % 0x4b == 0 && (*(char *)(param_1 + 0x310) == '\x01'))))
         && (fVar4 = (float10)FUN_0042d980(), fVar4 < (float10)62500.0)) {
        *(undefined4 *)(param_1 + 0x27c) = 0;
        *(undefined4 *)(param_1 + 0x278) = 1;
        *(undefined4 *)(param_1 + 0x2b4) = 1;
        return param_1;
      }
    }
    uVar3 = FUN_0065d150();
    uVar2 = uVar3 / 100;
    if (uVar3 % 100 < local_8) {
      uVar2 = FUN_0065d150();
      if (((uVar2 % 0xaf == 0) ||
          ((uVar2 = FUN_0065d150(), uVar2 % 0x96 == 0 && (*(char *)(param_1 + 0x310) == '\x02'))))
         && (fVar4 = (float10)FUN_0042d980(),
            fVar4 < (float10)*(float *)(param_1 + 0x80) * (float10)*(float *)(param_1 + 0x80))) {
        *(undefined4 *)(param_1 + 0x2b8) = 1;
        *(undefined4 *)(param_1 + 0x870) = 0;
      }
      uVar2 = FUN_0065d150();
      if (uVar2 % 0x96 != 0) {
        uVar2 = FUN_0065d150();
        if (uVar2 % 0x7d != 0) {
          return uVar2 / 0x7d;
        }
        if ((int)*(char *)(param_1 + 0x310) != 2) {
          return (int)*(char *)(param_1 + 0x310);
        }
      }
      fVar5 = (float10)FUN_0042d980();
      fVar4 = (float10)1e+06;
      uVar2 = (uint)(ushort)((ushort)(fVar5 < fVar4) << 8 | (ushort)(NAN(fVar5) || NAN(fVar4)) << 10
                            | (ushort)(fVar5 == fVar4) << 0xe);
      if (fVar5 < fVar4) {
        fVar4 = (float10)FUN_0042d980();
        fVar5 = (float10)*(float *)(param_1 + 0x80) * (float10)*(float *)(param_1 + 0x80);
        uVar2 = (uint)(ushort)((ushort)(fVar5 < fVar4) << 8 |
                               (ushort)(NAN(fVar5) || NAN(fVar4)) << 10 |
                              (ushort)(fVar5 == fVar4) << 0xe);
        if (fVar5 >= fVar4 && (fVar5 == fVar4) == 0) {
          *(undefined4 *)(param_1 + 0x2b8) = 1;
          *(undefined4 *)(param_1 + 0x870) = 0;
          uVar2 = param_1;
        }
      }
    }
  }
  return uVar2;
}

