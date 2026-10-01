// Function: FUN_005e00d0
// Address:  0x005e00d0
// Source:   batch_decompile (mass dump)
// Hash:     74c06f61287264d4


void __fastcall FUN_005e00d0(int param_1)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  
  if (*(int *)(param_1 + 0x288) != 0) {
    FUN_0043f3e0();
  }
  *(undefined4 *)(param_1 + 0x7c8) = 0x5a;
  *(undefined4 *)(param_1 + 0x7cc) = 0x73;
  *(undefined4 *)(param_1 + 2000) = 100;
  FUN_00435560(1);
  if (0 < *(int *)(param_1 + 0x7f4)) {
    uVar3 = FUN_0066b668();
    *(undefined4 *)(param_1 + 0x7c8) = uVar3;
  }
  if (0 < *(int *)(param_1 + 0x7e0)) {
    uVar3 = FUN_0066b668();
    *(undefined4 *)(param_1 + 0x7c8) = uVar3;
  }
  if (0 < *(int *)(param_1 + 0x7e4)) {
    uVar3 = FUN_0066b668();
    *(undefined4 *)(param_1 + 0x7cc) = uVar3;
  }
  if (*(char *)(param_1 + 0x846) == '\0') {
    if (*(char *)(param_1 + 0x844) == '\0') {
      if (*(char *)(param_1 + 0x845) != '\0') {
        FUN_00435560(4);
      }
    }
    else {
      uVar3 = FUN_0066b668();
      *(undefined4 *)(param_1 + 0x7c8) = uVar3;
      uVar3 = FUN_0066b668();
      *(undefined4 *)(param_1 + 0x7cc) = uVar3;
      uVar3 = FUN_0066b668();
      *(undefined4 *)(param_1 + 2000) = uVar3;
    }
  }
  else {
    *(int *)(param_1 + 0x7a4) = *(int *)(param_1 + 0x7a4) + 3;
    uVar3 = FUN_0066b668();
    *(undefined4 *)(param_1 + 0x7c8) = uVar3;
    uVar3 = FUN_0066b668();
    *(undefined4 *)(param_1 + 0x7cc) = uVar3;
    uVar3 = FUN_0066b668();
    *(undefined4 *)(param_1 + 2000) = uVar3;
    FUN_00435560(2);
    if (*(int *)(param_1 + 0x834) < 1000) {
      *(int *)(param_1 + 0x834) = *(int *)(param_1 + 0x834) + 1;
    }
  }
  if (*(int *)(param_1 + 0x830) == 1) {
    if ((((*(char *)(param_1 + 0x84) != '\0') && (0 < *(int *)(param_1 + 0x834))) &&
        (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0xab0))) &&
       ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
      FUN_00421080(0x14);
      return;
    }
    if (((*(char *)(param_1 + 0x84) == '\0') && (0 < *(int *)(param_1 + 0x834))) &&
       ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0xab0) &&
        ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)))) {
      FUN_00421080(0x1e);
      return;
    }
  }
  if (((*(int *)(param_1 + 0x830) == 4) && (0 < *(int *)(param_1 + 0x834))) &&
     ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0xb04) &&
      ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)))) {
    if (*(char *)(param_1 + 0x84) == '\0') {
      FUN_00421080(0x1e);
    }
    else {
      FUN_00421080(0x17);
    }
  }
  else if ((((*(int *)(param_1 + 0x830) == 3) && (0 < *(int *)(param_1 + 0x834))) &&
           (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0xb20))) &&
          ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
    if (*(char *)(param_1 + 0x84) == '\0') {
      FUN_00421080(0x1e);
    }
    else {
      FUN_00421080(0x18);
    }
  }
  else if (((*(int *)(param_1 + 0x830) == 2) && (0 < *(int *)(param_1 + 0x834))) &&
          ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0xb74) &&
           ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)))) {
    if (*(char *)(param_1 + 0x84) == '\0') {
      FUN_00421080(0x1e);
    }
    else {
      FUN_00421080(0x1b);
    }
  }
  else {
    if (((*(int *)(param_1 + 0x288) != 0) && (*(int *)(param_1 + 0x284) != 0)) &&
       (((*(uint *)(param_1 + 0x288) < 3 &&
         (((*(uint *)(param_1 + 0x284) < 3 && (*(char *)(param_1 + 0x844) == '\0')) &&
          (*(char *)(param_1 + 0x845) == '\0')))) && (*(char *)(param_1 + 0x846) == '\0')))) {
      if (*(char *)(param_1 + 0x318) == '\0') {
        if (((((*(int *)(param_1 + 0xadec) < 0x76) ||
              ((0x81 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0xb4)))) ||
             ((199 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0xda)))) ||
            ((0xe5 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x118)))) &&
           ((*(int *)(param_1 + 0x324) <= *(int *)(param_1 + 0x838) &&
            (*(char *)(param_1 + 0x844) == '\0')))) {
          if ((*(int *)(param_1 + 0xadec) < 100) || (299 < *(int *)(param_1 + 0xadec))) {
            *(undefined4 *)(param_1 + 0xec) = 0;
          }
          else {
            *(undefined4 *)(param_1 + 0xec) = 1;
          }
          if (*(char *)(param_1 + 0x84) != '\0') {
            FUN_00421080(500);
            return;
          }
          FUN_00421080(0x1f5);
          return;
        }
      }
      else if ((*(char *)(param_1 + 0x318) == '\x01') &&
              ((((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))) &&
                (*(char *)(param_1 + 0x845) == '\0')) &&
               (*(int *)(param_1 + 0x32c) <= *(int *)(param_1 + 0x83c))))) {
        FUN_004220e0();
        *(undefined4 *)(param_1 + 0x290) = 0x14;
        *(undefined4 *)(param_1 + 0x288) = 0x14;
        *(undefined4 *)(param_1 + 0x284) = 0x14;
        piVar4 = (int *)FUN_00658a10(0);
        iVar1 = *piVar4;
        piVar4 = (int *)FUN_00658a10(0);
        if ((*(int *)(iVar1 + 0x330) - *(int *)(*piVar4 + 0x83c) < 0x78) &&
           (piVar4 = (int *)FUN_00658a10(0), *(char *)(*piVar4 + 0x845) != '\0')) {
          FUN_00422240(0x23,0x1e,0);
          return;
        }
        FUN_00422240(0x24,0x1e,0);
        return;
      }
    }
    if (((*(int *)(param_1 + 0x280) == 0) || (*(int *)(param_1 + 0x284) == 0)) ||
       ((*(char *)(param_1 + 0x84) == '\0' ||
        ((*(int *)(param_1 + 0x3328) < *(int *)(*(int *)(param_1 + 0xade0) + 4) ||
         ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) == 0)))))) {
      if ((0 < *(int *)(param_1 + 0x2b8)) &&
         ((*(int *)(param_1 + 0x730) == 1 && (*(int *)(param_1 + 0x720) == 0)))) {
        FUN_00422560(*(undefined4 *)(param_1 + 8),0x18,10,1);
      }
      if (((0 < *(int *)(param_1 + 0x2b8)) && (*(int *)(param_1 + 0x2b8) < 0x14)) &&
         (*(int *)(param_1 + 0x6dc) == 0)) {
        FUN_00422560(*(undefined4 *)(param_1 + 8),0x18,10,1);
        *(int *)(param_1 + 0xaf4c) = *(int *)(param_1 + 0xaf4c) + 1;
      }
      if (((0 < *(int *)(param_1 + 0x2b8)) && (*(int *)(param_1 + 0x730) == 2)) &&
         (0 < *(int *)(param_1 + 0x720))) {
        if (*(char *)(param_1 + 0x84) == '\0') {
          if ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2fe0)) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf50) = *(int *)(param_1 + 0xaf50) + 1;
            FUN_00421080(0x168);
            if ((*(char *)(param_1 + 0x845) == '\0') &&
               ((*(char *)(param_1 + 0x846) == '\0' && (*(char *)(param_1 + 0x844) == '\0')))) {
              return;
            }
            FUN_00421080(0x169);
            return;
          }
        }
        else if ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2ec8)) &&
                ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
          *(int *)(param_1 + 0xaf50) = *(int *)(param_1 + 0xaf50) + 1;
          FUN_00421080(0x15e);
          if ((*(char *)(param_1 + 0x845) == '\0') &&
             ((*(char *)(param_1 + 0x846) == '\0' && (*(char *)(param_1 + 0x844) == '\0')))) {
            return;
          }
          FUN_00421080(0x15f);
          return;
        }
      }
      if (((0 < *(int *)(param_1 + 0x2b8)) && (*(int *)(param_1 + 0x730) == 1)) &&
         (0 < *(int *)(param_1 + 0x720))) {
        if (*(char *)(param_1 + 0x84) == '\0') {
          if ((((((*(int *)(param_1 + 0x27c) != 0) || (*(int *)(param_1 + 0x278) != 0)) &&
                (*(int *)(param_1 + 0xadf4) == 1)) &&
               ((*(int *)(param_1 + 0xadec) == 0x1e || (*(int *)(param_1 + 0xadec) == 0x198)))) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x3aec))) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1cc);
            return;
          }
          if ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x3ad0)) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1cc);
            return;
          }
        }
        else {
          if (((*(int *)(param_1 + 0xadec) == 0x14) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x39b8))) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1c2);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x17) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x39d4))) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1c3);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x18) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x39d4))) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1c3);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x1b) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x39b8))) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1c2);
            return;
          }
          if (((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x39b8)) &&
              (*(int *)(param_1 + 0xadec) == 10)) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1c2);
            return;
          }
          if ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x39b8)) &&
             ((*(int *)(param_1 + 0xadec) < 100 || (299 < *(int *)(param_1 + 0xadec))))) {
            *(int *)(param_1 + 0xaf54) = *(int *)(param_1 + 0xaf54) + 1;
            FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < *(int *)(param_1 + 0x2b8)) && (*(int *)(param_1 + 0x2b8) < 0x14)) &&
         (0 < *(int *)(param_1 + 0x6dc))) {
        if (*(char *)(param_1 + 0x84) == '\0') {
          if ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x3478)) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x192);
            return;
          }
        }
        else {
          if (((*(int *)(param_1 + 0xadec) == 0x14) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x34b0))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x194);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x17) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x34cc))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x195);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x18) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x34e8))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x196);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x1b) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x34e8))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x197);
            return;
          }
          if (((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x3440)) &&
              (*(int *)(param_1 + 0xadec) == 10)) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            if ((100.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -100.0)) {
              FUN_00421080(400);
              return;
            }
            if ((*(float *)(param_1 + 100) < 40.0) && (-40.0 < *(float *)(param_1 + 100))) {
              FUN_004211f0(0x19a);
              return;
            }
            if (40.0 <= *(float *)(param_1 + 100)) {
              FUN_004211f0(0x19c);
              return;
            }
            if (*(float *)(param_1 + 100) < -40.0 != (*(float *)(param_1 + 100) == -40.0)) {
              FUN_004211f0(0x19b);
              return;
            }
          }
          if ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x3440)) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(400);
            return;
          }
        }
      }
      if (((*(char *)(param_1 + 0x845) == '\0') && (*(char *)(param_1 + 0x844) == '\0')) &&
         (*(char *)(param_1 + 0x846) == '\0')) {
        if ((*(int *)(param_1 + 0x284) == 3) ||
           ((0 < *(int *)(param_1 + 0x2b4) && (*(int *)(param_1 + 0x2b4) < 3)))) {
          if (*(char *)(param_1 + 0x84) == '\0') {
            if (((*(int *)(param_1 + 0x278) != 0) || (*(int *)(param_1 + 0x27c) != 0)) &&
               ((*(int *)(param_1 + 0xadec) == 0x1e &&
                (((*(int *)(param_1 + 0xadf4) < 2 &&
                  (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2b80))) &&
                 ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)))))) {
              FUN_00421080(0x140);
              return;
            }
            if (((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2b80)) ||
                (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                 ((299 < *(int *)(param_1 + 0xadec) &&
                  ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x140))))))
                )) && (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                       ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0))
                         && (sVar2 = FUN_0042c7b0(), sVar2 != 0)) &&
                        ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e)))
                        ))))) {
              FUN_00421080(0x140);
              return;
            }
          }
          else {
            if ((((*(int *)(param_1 + 0x278) != 0) && (*(int *)(param_1 + 0xadec) == 0x14)) &&
                (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2cb4))) &&
               ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
              FUN_00421080(0x14b);
              return;
            }
            if (((*(int *)(param_1 + 0xadec) == 0x14) &&
                (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2c98))) &&
               ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
              FUN_00421080(0x14a);
              return;
            }
            if ((((*(int *)(param_1 + 0x27c) < 0) &&
                 ((*(int *)(param_1 + 0xadec) == 0x17 || (*(int *)(param_1 + 0xadec) == 0x18)))) &&
                (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2c98))) &&
               ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
              FUN_00421080(0x14a);
              return;
            }
            if ((((*(int *)(param_1 + 0xadec) == 0x17) || (*(int *)(param_1 + 0xadec) == 0x18)) &&
                (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2cb4))) &&
               ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
              FUN_00421080(0x14b);
              return;
            }
            if (((*(int *)(param_1 + 0x27c) < 0) &&
                ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2a68) ||
                 (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                  ((299 < *(int *)(param_1 + 0xadec) &&
                   ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x136)))))
                  ))))) &&
               (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                  (sVar2 = FUN_0042c7b0(), sVar2 != 0)) &&
                 ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e)))))))) {
              FUN_00421080(0x136);
              return;
            }
            if (((*(int *)(param_1 + 0x278) != 0) &&
                ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2a84) ||
                 (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                  ((299 < *(int *)(param_1 + 0xadec) &&
                   ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x137)))))
                  ))))) &&
               (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                  (sVar2 = FUN_0042c7b0(), sVar2 != 0)) &&
                 ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e)))))))) {
              FUN_00421080(0x137);
              return;
            }
            if (((((*(int *)(param_1 + 0xadec) == 0x149) || (*(int *)(param_1 + 0xadec) == 0x14d))
                 || (*(int *)(param_1 + 0xadec) == 0x2c)) &&
                ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2db0) ||
                 ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                   (299 < *(int *)(param_1 + 0xadec))) &&
                  ((((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 300)) &&
                    ((*(int *)(param_1 + 0xadec) != 0x12d &&
                     ((*(int *)(param_1 + 0xadec) != 0x12e && (*(int *)(param_1 + 0xadec) != 0x14a))
                     )))) && (*(int *)(param_1 + 0xadec) != 0x154)))))))) &&
               (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                  (sVar2 = FUN_0042c7b0(), sVar2 != 0)) &&
                 ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e)))))))) {
              FUN_00421080(0x154);
              return;
            }
            if (((*(int *)(param_1 + 0xadec) == 300) &&
                (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x296c))) &&
               ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
              FUN_00421080(0x12d);
              return;
            }
            if (((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2950)) ||
                (((((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                     (299 < *(int *)(param_1 + 0xadec))) &&
                    ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 300))))
                   && (*(int *)(param_1 + 0xadec) != 0x12d)) &&
                  ((*(int *)(param_1 + 0xadec) != 0x12e && (*(int *)(param_1 + 0xadec) != 0x140))))
                 && ((*(int *)(param_1 + 0xadec) != 0x14a && (*(int *)(param_1 + 0xadec) != 0x155)))
                 ))) && (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                         ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0))
                           && (sVar2 = FUN_0042c7b0(), sVar2 != 0)) &&
                          ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e)
                           ))))))) {
              FUN_00421080(300);
              return;
            }
          }
        }
      }
      else if ((*(int *)(param_1 + 0x284) == 3) ||
              ((0 < *(int *)(param_1 + 0x2b4) && (*(int *)(param_1 + 0x2b4) < 3)))) {
        if (*(char *)(param_1 + 0x84) == '\0') {
          if ((((*(int *)(param_1 + 0x278) != 0) || (*(int *)(param_1 + 0x27c) != 0)) &&
              (*(int *)(param_1 + 0xadec) == 0x1e)) &&
             (((*(int *)(param_1 + 0xadf4) < 2 &&
               (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2b80))) &&
              ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)))) {
            FUN_00421080(0x140);
            return;
          }
          if (((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2b80)) ||
              (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
               ((299 < *(int *)(param_1 + 0xadec) &&
                ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x140))))))))
             && (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                 ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                   (sVar2 = FUN_0042c7b0(), sVar2 != 0)) &&
                  ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e))))))))
          {
            FUN_00421080(0x140);
            return;
          }
        }
        else {
          if (((*(int *)(param_1 + 0x278) != 0) && (*(int *)(param_1 + 0xadec) == 0x14)) &&
             ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2d40) &&
              ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)))) {
            FUN_00421080(0x150);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x14) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2d24))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x14f);
            return;
          }
          if ((((*(int *)(param_1 + 0x27c) < 0) &&
               ((*(int *)(param_1 + 0xadec) == 0x17 || (*(int *)(param_1 + 0xadec) == 0x18)))) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2d24))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x14f);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x17) || (*(int *)(param_1 + 0xadec) == 0x18)) &&
             ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2d40) &&
              ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)))) {
            FUN_00421080(0x150);
            return;
          }
          if (((*(int *)(param_1 + 0x27c) < 0) &&
              ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2aa0) ||
               ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                 (299 < *(int *)(param_1 + 0xadec))) &&
                ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x138))))))))
             && (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                 (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                  ((sVar2 = FUN_0042c7b0(), sVar2 != 0 &&
                   ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e))))))))
                )) {
            FUN_00421080(0x138);
            return;
          }
          if (((*(int *)(param_1 + 0x278) != 0) &&
              ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2abc) ||
               ((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                 (299 < *(int *)(param_1 + 0xadec))) &&
                ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x139))))))))
             && (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
                 (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                  ((sVar2 = FUN_0042c7b0(), sVar2 != 0 &&
                   ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e))))))))
                )) {
            FUN_00421080(0x139);
            return;
          }
          if (((((*(int *)(param_1 + 0xadec) == 0x149) || (*(int *)(param_1 + 0xadec) == 0x14d)) ||
               (*(int *)(param_1 + 0xadec) == 0x2c)) &&
              ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2dcc) ||
               (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                ((((299 < *(int *)(param_1 + 0xadec) &&
                   ((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x12e))))
                  && (*(int *)(param_1 + 0xadec) != 0x12f)) &&
                 (((*(int *)(param_1 + 0xadec) != 0x130 && (*(int *)(param_1 + 0xadec) != 0x14f)) &&
                  (*(int *)(param_1 + 0xadec) != 0x155)))))))))) &&
             (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
              (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
               ((sVar2 = FUN_0042c7b0(), sVar2 != 0 &&
                ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e))))))))))
          {
            FUN_00421080(0x155);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x12f) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x29c0))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x130);
            return;
          }
          if (((*(int *)(param_1 + 0xadec) == 0x12e) &&
              (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x29a4))) &&
             ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0)) {
            FUN_00421080(0x12f);
            return;
          }
          if (((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0x2988)) ||
              (((((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
                 ((299 < *(int *)(param_1 + 0xadec) &&
                  ((((*(int *)(param_1 + 0xadec) < 0x15e && (*(int *)(param_1 + 0xadec) != 0x12e))
                    && (*(int *)(param_1 + 0xadec) != 0x12f)) &&
                   ((*(int *)(param_1 + 0xadec) != 0x130 && (*(int *)(param_1 + 0xadec) != 0x140))))
                  )))) && (*(int *)(param_1 + 0xadec) != 0x14f)) &&
               (*(int *)(param_1 + 0xadec) != 0x154)))) &&
             (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 ||
              (((*(char *)(param_1 + 0x845) != '\0' && (*(int *)(param_1 + 0x848) != 0)) &&
               ((sVar2 = FUN_0042c7b0(), sVar2 != 0 &&
                ((299 < *(int *)(param_1 + 0xadec) && (*(int *)(param_1 + 0xadec) < 0x15e))))))))))
          {
            FUN_00421080(0x12e);
            return;
          }
        }
      }
      if (((((*(int *)(param_1 + 0x280) == 3) ||
            ((0 < *(int *)(param_1 + 0x2b0) && (*(int *)(param_1 + 0x2b0) < 3)))) &&
           (*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0xbc8))) &&
          (((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 &&
           (((*(int *)(param_1 + 0x27c) != 0 || (*(int *)(param_1 + 0x278) != 0)) &&
            (*(char *)(param_1 + 0x84) == '\0')))))) && (0 < *(int *)(param_1 + 0x834))) {
        FUN_00421080(0x1e);
      }
      else if ((((*(int *)(param_1 + 0x280) == 3) ||
                ((0 < *(int *)(param_1 + 0x2b0) && (*(int *)(param_1 + 0x2b0) < 3)))) &&
               ((*(int *)(*(int *)(param_1 + 0xade0) + 4) <= *(int *)(param_1 + 0xce0) ||
                (*(int *)(*(int *)(param_1 + 0xade0) + 4) == 99)))) &&
              ((((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x100) != 0 &&
                (*(char *)(param_1 + 0x84) != '\0')) && (0 < *(int *)(param_1 + 0x834))))) {
        FUN_00421080(0x28);
      }
    }
    else {
      FUN_00421080(0x186);
    }
  }
  return;
}

