// ============================================
// Address:  0x00527880
// Original: FUN_00527880
// Status:   unreviewed
// ============================================


void __fastcall FUN_00527880(int *param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  int local_160;
  int local_15c;
  int local_158;
  int local_154;
  int local_150;
  float local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int local_138;
  float local_134;
  int local_110;
  int local_10c;
  float local_108;
  int local_24;
  int local_20;
  float local_1c;
  float local_10;
  float local_8;
  
  if (param_1[0x28] != 0) {
    return;
  }
  FUN_00434a70(0,0);
  FUN_00434a70(1,1);
  FUN_00434bd0();
  if ((0.0 < (float)param_1[0x1a]) &&
     (param_1[0x1a] = (int)((float)param_1[0x1a] - 10.0), (float)param_1[0x1a] < 0.0)) {
    param_1[0x1a] = 0;
  }
  if (((float)param_1[0x1a] < 0.0) &&
     (param_1[0x1a] = (int)((float)param_1[0x1a] + 10.0), 0.0 < (float)param_1[0x1a])) {
    param_1[0x1a] = 0;
  }
  iVar5 = param_1[0x2b7b];
  if (iVar5 < 0x156) {
    if (iVar5 == 0x155) {
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        FUN_00423000();
      }
      param_1[0x1a1] = 2;
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        FUN_0042c800(0);
        FUN_0042c840(1);
      }
      uVar3 = FUN_0042c7b0();
      if ((uVar3 & 2) != 0) {
        FUN_00421080(0x188);
        FUN_0042c800(0);
        return;
      }
      if (param_1[0x2b81] == 9) {
        FUN_0042c880(0x3d);
        FUN_004223d0(3,10,0);
      }
      if ((param_1[0x2b81] < 10) && (param_1[0x3b] == 1)) {
        FUN_0042db10(0,0x40000000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = 0x41700000;
      }
      if (param_1[0x2b81] == 0xf) {
        param_1[0x15] = 0;
        param_1[0x21d] = 0;
      }
    }
    else if (iVar5 < 0x12d) {
      if (iVar5 == 300) {
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x3b] = 0;
          param_1[0x3c] = 1;
          param_1[0x15] = 0x41840000;
          FUN_0042db10(0,0x43340000);
          fVar6 = (float10)FUN_0042d980();
          if (fVar6 < (float10)640000.0) {
            param_1[0x3c] = 1;
            param_1[0x15] = 0x41b40000;
          }
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) && (param_1[0x3b] == 0)) {
          param_1[0x3b] = 1;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x41700000);
        }
        if ((param_1[0x2b7d] == 1) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x41700000);
        }
        if (((param_1[0x2b7d] == 1) && (2 < param_1[0x2b81])) &&
           ((fVar6 = (float10)FUN_0042d980(), fVar6 < (float10)90000.0 || (param_1[0x3c] == 0)))) {
          FUN_00421100(2);
          return;
        }
        if (param_1[0x2b7d] == 2) {
          if ((param_1[0x2b81] < 8) && (param_1[0x3c] == 1)) {
            FUN_0042db10(0,0x41100000);
          }
          if (param_1[0x2b81] == 8) {
            FUN_0042c880(0x3c);
            fVar6 = (float10)FUN_0042d980();
            if ((((float10)90000.0 <= fVar6) ||
                (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
               (*(char *)((int)param_1 + 0xaec3) != '\x01')) {
              fVar6 = (float10)FUN_0042d980();
              if ((((float10)90000.0 <= fVar6) ||
                  (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
                 (*(char *)((int)param_1 + 0xaebe) != '\x01')) {
                fVar6 = (float10)FUN_0042d980();
                if ((((float10)90000.0 <= fVar6) ||
                    (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
                   (*(char *)((int)param_1 + 0xaeb9) != '\x01')) {
                  FUN_004223d0(1,10,0);
                }
                else {
                  FUN_004223d0(5,0xc,0);
                }
              }
              else {
                FUN_004223d0(0xf,0xc,0);
              }
            }
            else {
              FUN_004223d0(0,0xc,0);
            }
          }
          if ((0 < param_1[0x2b81]) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 1.5), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
        }
      }
      else {
        switch(iVar5) {
        case 0:
          param_1[0x15] = 0;
          param_1[0x10] = 0;
          if (param_1[0x1fd] < 1) {
            param_1[0x20d] = param_1[0x20d] + 0x28;
          }
          else {
            param_1[0x20d] = param_1[0x20d] + 5;
          }
          param_1[0x21d] = 0;
          if (1000 < param_1[0x20d]) {
            param_1[0x20d] = 1000;
          }
          param_1[0x3a] = 10;
          if ((char)param_1[0x21] == '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if ((param_1[0x9e] != 0) || (param_1[0x9f] != 0)) {
            FUN_00421080(10);
            return;
          }
          break;
        default:
          goto switchD_0052799f_caseD_1;
        case 10:
          param_1[0x10] = 0;
          if ((char)param_1[0x21] == '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x9f] == 0)) {
            FUN_00421080(0);
            return;
          }
          if (param_1[0x9f] < 0) {
            if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1)) {
              param_1[0x3a] = 1;
              param_1[0x21d] = 0x41a00000;
            }
            if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0)) {
              param_1[0x3a] = 0;
              param_1[0x21d] = 0x41a00000;
            }
            if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2)) {
              param_1[0x3a] = 2;
              param_1[0x21d] = 0x41a00000;
            }
          }
          if (param_1[0x9f] == 0) {
            if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3)) {
              param_1[0x3a] = 3;
              param_1[0x21d] = 0x41a00000;
            }
            if ((param_1[0x9e] == 0) && (param_1[0x3a] != 10)) {
              param_1[0x3a] = 10;
              param_1[0x21d] = 0x41a00000;
            }
            if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4)) {
              param_1[0x3a] = 4;
              param_1[0x21d] = 0x41a00000;
            }
          }
          if (0 < param_1[0x9f]) {
            if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5)) {
              param_1[0x3a] = 5;
              param_1[0x21d] = 0x41a00000;
            }
            if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6)) {
              param_1[0x3a] = 6;
              param_1[0x21d] = 0x41a00000;
            }
            if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7)) {
              param_1[0x3a] = 7;
              param_1[0x21d] = 0x41a00000;
            }
          }
          param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
          if ((float)param_1[0x21d] < 1.0) {
            param_1[0x21d] = 0x3f800000;
          }
          param_1[0x15] = 0x40c80000;
          if (param_1[0x1fd] < 1) {
            param_1[0x20d] = param_1[0x20d] + 0x28;
          }
          else {
            param_1[0x20d] = param_1[0x20d] + 5;
          }
          if (1000 < param_1[0x20d]) {
            param_1[0x20d] = 1000;
          }
          param_1[0x18] = 0;
          FUN_00421780();
          break;
        case 0x14:
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            if ((char)param_1[0x21] == '\0') {
              param_1[0x16] = 0x3f000000;
              FUN_00421080(0x2b);
              return;
            }
            FUN_00421080(0);
            return;
          }
          if ((char)param_1[0x21] == '\0') {
            FUN_00421080(0x1e);
            return;
          }
          if ((param_1[0x2b7d] < 2) && (param_1[0x20d] = param_1[0x20d] + -0xd, param_1[0x20d] < 0))
          {
            param_1[0x20d] = 0;
          }
          if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x16 == 6)) {
            FUN_0042c8b0(5);
          }
          if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x16 == 0x11)) {
            FUN_0042c8b0(6);
          }
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            param_1[0x18] = 0;
            param_1[0x19] = 0;
            fVar6 = (float10)FUN_0042df90(param_1[0x19]);
            if ((float10)12.0 <= fVar6) {
              if (0.0 <= (float)param_1[0x19]) {
                if (0.0 < (float)param_1[0x19]) {
                  param_1[0x19] = (int)((float)param_1[0x19] - 10.0);
                }
              }
              else {
                param_1[0x19] = (int)((float)param_1[0x19] + 10.0);
              }
            }
            else {
              param_1[0x19] = 0;
            }
            param_1[0x15] = 0x41820000;
            param_1[0x3a] = 0;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x21d] = 0x40800000;
            param_1[0x15] = 0x41820000;
            FUN_00421780();
            if (((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) || (param_1[0x20d] < 1)) {
              FUN_00421100(2);
              return;
            }
          }
          if (param_1[0x2b7d] == 2) {
            param_1[0x21d] = 0;
            param_1[0x15] = (int)((float)param_1[0x15] - 0.75);
            if ((float)param_1[0x15] < 0.0) {
              param_1[0x15] = 0;
            }
            if ((param_1[0x2b81] == 4) && (param_1[0x3a] < 0xf)) {
              param_1[0x3a] = param_1[0x3a] + 1;
              return;
            }
          }
          break;
        case 0x17:
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            FUN_00421080(0);
            return;
          }
          if ((char)param_1[0x21] == '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if (param_1[0x2b7d] < 2) {
            FUN_0042db10(0,0x41a00000);
            param_1[0x20d] = param_1[0x20d] + -10;
            if (param_1[0x20d] < 0) {
              param_1[0x20d] = 0;
            }
          }
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            param_1[0x19] = 0;
            param_1[0x18] = -0x3d4c0000;
            param_1[0x15] = 0x41940000;
            param_1[0x2bd2] = param_1[0x2bd2] + 1;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x18] = -0x3d4c0000;
          }
          if ((param_1[0x2b7d] < 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 12.0)) {
            param_1[0x15] = 0x41400000;
          }
          if (param_1[0x2b7d] == 2) {
            if ((char)param_1[0x21] == '\0') {
              param_1[0x16] = 0x3f000000;
              FUN_00421080(0x2b);
              return;
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.7);
            if ((float)param_1[0x15] < 0.0) {
              param_1[0x15] = 0;
            }
          }
          uVar3 = param_1[0x2b81] & 0x80000003;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
          }
          if ((uVar3 == 0) && (param_1[0x2b7d] == 2)) {
            param_1[0x2b81] = param_1[0x2b81] + 1;
            param_1[0x2b82] = param_1[0x2b82] + 1;
          }
          break;
        case 0x18:
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            if (10.0 < (float)param_1[0x1f]) {
              param_1[0x16] = 0x3f000000;
              FUN_00421080(0x2b);
              return;
            }
            FUN_00421080(0);
            return;
          }
          if ((char)param_1[0x21] == '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if (param_1[0x2b7d] < 2) {
            FUN_0042db10(0,0x41a00000);
            param_1[0x20d] = param_1[0x20d] + -10;
            if (param_1[0x20d] < 0) {
              param_1[0x20d] = 0;
            }
          }
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            param_1[0x19] = 0;
            param_1[0x18] = 0x42b40000;
            param_1[0x15] = 0x41980000;
            param_1[0x2bd2] = param_1[0x2bd2] + 1;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x18] = 0x42b40000;
          }
          if ((param_1[0x2b7d] < 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 12.0)) {
            param_1[0x15] = 0x41400000;
          }
          if ((param_1[0x2b7d] == 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.7), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
          break;
        case 0x1b:
        case 0x1c:
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            if (10.0 < (float)param_1[0x1f]) {
              param_1[0x16] = 0x3f000000;
              FUN_00421080(0x2b);
              return;
            }
            FUN_00421080(0);
            return;
          }
          if ((char)param_1[0x21] == '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if ((param_1[0x2b7d] < 2) && (param_1[0x20d] = param_1[0x20d] + -10, param_1[0x20d] < 0))
          {
            param_1[0x20d] = 0;
          }
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            param_1[0x19] = 0;
            param_1[0x18] = 0x43340000;
            param_1[0x15] = 0x41580000;
            param_1[0x2bd2] = param_1[0x2bd2] + 1;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x21d] = 0;
            param_1[0x15] = 0x41580000;
            param_1[0x18] = 0x43340000;
          }
          if ((param_1[0x2b7d] == 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
          break;
        case 0x1e:
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if (param_1[0x2b7d] < 3) {
            param_1[0x20d] = param_1[0x20d] + -0xb;
            if (param_1[0x2b7d] < 2) {
              if (param_1[0xa0] == 0) {
                param_1[0x10] = (int)((float)param_1[0x10] - 0.5);
                if ((float)param_1[0x10] < 0.0) {
                  param_1[0x10] = 0;
                }
              }
              else {
                param_1[0x10] = (int)((float)param_1[0x10] + 0.5);
                if (8.0 < (float)param_1[0x10]) {
                  param_1[0x10] = 0x41000000;
                }
                param_1[0x20d] = param_1[0x20d] + -3;
              }
            }
            if (param_1[0x20d] < 0) {
              param_1[0x20d] = 0;
            }
          }
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            param_1[0x15] = 0x41780000;
            param_1[0x10] = 0;
            param_1[0x21d] = 0x42700000;
            param_1[0x18] = 0;
            param_1[0x3a] = 0;
          }
          if (((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) && (param_1[0x3a] == 0)) {
            FUN_0042c880(2);
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x21d] = 0x40000000;
            param_1[0x15] = 0x41780000;
            param_1[0x3a] = param_1[0x3a] + 1;
            if ((5 < param_1[0x3a]) &&
               (((param_1[0x9f] == 0 && (param_1[0x9e] == 0)) || (param_1[0x20d] < 1)))) {
              FUN_00421100(2);
              return;
            }
          }
          if (param_1[0x2b7d] == 2) {
            param_1[0x16] = 0x3f000000;
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            if ((char)param_1[0x21] != '\0') {
              FUN_00421080(0x2c);
              param_1[0x10] = 0;
              return;
            }
          }
          FUN_00421780();
          break;
        case 0x28:
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            FUN_00421080(0x29);
            return;
          }
          param_1[0x18] = 0;
          if (param_1[0x1fd] < 1) {
            param_1[0x20d] = param_1[0x20d] + 0x28;
          }
          else {
            param_1[0x20d] = param_1[0x20d] + 5;
          }
          if (1000 < param_1[0x20d]) {
            param_1[0x20d] = 1000;
          }
          param_1[0x16] = 0;
          param_1[0x15] = 0;
          param_1[0x21d] = 0x41900000;
          param_1[0x18] = 0;
          FUN_00421780();
          break;
        case 0x29:
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            param_1[0x10] = 0x41400000;
            param_1[0x3a] = 0;
            if ((param_1[0x9f] != 0) || (param_1[0x9e] != 0)) {
              param_1[0x15] = 0x40c00000;
            }
          }
          if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
            FUN_00421080(0x2a);
            return;
          }
          if (((char)param_1[0x21] != '\0') &&
             ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0))) {
            FUN_00421080(0x2c);
            param_1[0x10] = 0;
            return;
          }
          param_1[0x21d] = 0x3f800000;
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
          param_1[0x3a] = param_1[0x3a] + 1;
          if (((float)param_1[0x16] == 0.0) &&
             (param_1[0x20d] = param_1[0x20d] + -10, param_1[0x20d] < 0)) {
            param_1[0x20d] = 0;
          }
          if (param_1[0xa0] == 0) {
            param_1[0x3a] = 0;
          }
          if (((param_1[0x3a] == 0) || (99 < param_1[0x3a])) || (param_1[0x20d] < 1)) {
            param_1[0x16] = 0x3f000000;
          }
          if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) {
            param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
            if ((float)param_1[0x15] < 0.0) {
              param_1[0x15] = 0;
            }
          }
          else {
            param_1[0x15] = (int)((float)param_1[0x15] + 0.2);
            if (6.0 < (float)param_1[0x15]) {
              param_1[0x15] = 0x40c00000;
            }
          }
          FUN_00421780();
          break;
        case 0x2a:
          if (((char)param_1[0x21] != '\0') &&
             ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0))) {
            FUN_00421080(0x2c);
            param_1[0x10] = 0;
            return;
          }
          param_1[0x21d] = 0x3f800000;
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
          if ((param_1[0xa0] == 0) || (0x3b < (uint)param_1[0xa0])) {
            param_1[0x16] = 0x3f000000;
          }
          if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) {
            param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
            if ((float)param_1[0x15] < 0.0) {
              param_1[0x15] = 0;
            }
          }
          else {
            param_1[0x15] = (int)((float)param_1[0x15] + 0.2);
            if (6.0 < (float)param_1[0x15]) {
              param_1[0x15] = 0x40c00000;
            }
          }
          FUN_00421780();
          break;
        case 0x2b:
          if (((char)param_1[0x21] != '\0') &&
             ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0))) {
            FUN_00421080(0x2c);
            param_1[0x10] = 0;
            return;
          }
          param_1[0x21d] = 0x3f800000;
          if ((float)param_1[0x16] == 0.0) {
            param_1[0x16] = 0x3f000000;
          }
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
          if ((param_1[0xa0] == 0) || (0x3b < (uint)param_1[0xa0])) {
            param_1[0x16] = 0x3f000000;
          }
          FUN_00421780();
          break;
        case 0x2c:
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            FUN_00421080(0);
            return;
          }
          param_1[0x16] = 0;
          param_1[0x10] = 0;
          param_1[0x18] = 0;
          param_1[0x21d] = 0;
          if ((0.0 < (float)param_1[0x15]) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
          if (((float)param_1[0x15] < 0.0) &&
             (param_1[0x15] = (int)((float)param_1[0x15] + 0.5), 0.0 < (float)param_1[0x15])) {
            param_1[0x15] = 0;
          }
          param_1[0x15] = 0;
          if (param_1[0x1fd] < 1) {
            param_1[0x20d] = param_1[0x20d] + 0x28;
          }
          else {
            param_1[0x20d] = param_1[0x20d] + 5;
          }
          if (1000 < param_1[0x20d]) {
            param_1[0x20d] = 1000;
          }
        }
      }
    }
    else {
      switch(iVar5) {
      case 0x12d:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x3b] != 0) && (param_1[0x1a1] = 2, param_1[0x2b81] < 0xf)) {
          FUN_0042db10(0,0x41700000);
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x15] = 0;
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if (param_1[0x2b81] == 0xe) {
          param_1[0x15] = 0x41700000;
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if ((0xe < param_1[0x2b81]) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 0.75), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] == 0xf) {
          FUN_0042c880(0x3d);
          FUN_004223d0(3,10,0);
        }
        break;
      default:
switchD_0052799f_caseD_1:
        FUN_00428510();
        return;
      case 0x136:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x15] = 0x41a00000;
          param_1[0x3a] = 0;
          FUN_0042db10(0,0x43340000);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if ((param_1[0x2b7d] == 1) && (fVar6 = (float10)FUN_0042d980(), fVar6 < (float10)40000.0)) {
          FUN_00421100(2);
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x40a00000);
        }
        if (param_1[0x2b7d] == 1) {
          FUN_0042db10(0,0x40a00000);
        }
        if (param_1[0x2b7d] == 2) {
          if (param_1[0x2b81] < 8) {
            FUN_0042db10(0,0x40a00000);
          }
          if (param_1[0x2b81] == 8) {
            FUN_0042c880(0x3e);
            FUN_004223d0(2,10,0);
          }
          param_1[0x15] = (int)((float)param_1[0x15] - 2.0);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
          if (((0xf < param_1[0x2b81]) && (uVar3 = FUN_0042c7b0(), (uVar3 & 1) != 0)) &&
             (param_1[0xa0] != 0)) {
            FUN_00421080(0x28);
            return;
          }
        }
        break;
      case 0x137:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x19] = param_1[0x18];
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x15] = 0x41680000;
          FUN_0042db10(0,0x43340000);
        }
        param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
        if (param_1[0x2b81] == 0xe) {
          param_1[0x15] = 0x41bc0000;
        }
        if (param_1[0x2b81] == 0x10) {
          FUN_0042c880(0x3e);
          FUN_004223d0(3,10,0);
        }
        if (param_1[0x2b81] == 0x25) {
          param_1[0x15] = 0;
        }
        if (param_1[0x2b81] < 0x10) {
          FUN_0042db10(0,0x41880000);
        }
        break;
      case 0x140:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0x2b);
          param_1[0xb] = 0;
          return;
        }
        if ((float)param_1[0x16] == 0.0) {
          param_1[0x16] = 0x3f000000;
        }
        if ((param_1[0x2b7d] == 2) && (0xc < param_1[0x2b81])) {
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        }
        if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) && (0xf < param_1[0x2b81])) {
          FUN_00421080(0x149);
          param_1[0x15] = 0;
          param_1[0x10] = 0;
          param_1[0xb] = 0;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x3b] = 0;
          param_1[0x3c] = 0;
          FUN_00422900();
          FUN_00423000();
          if ((float)param_1[0x10] <= 3.0) {
            local_1c = (float)param_1[0x10];
          }
          else {
            local_1c = 3.0;
          }
          if (-3.0 <= local_1c) {
            if ((float)param_1[0x10] <= 3.0) {
              local_24 = param_1[0x10];
            }
            else {
              local_24 = 0x40400000;
            }
            local_20 = local_24;
          }
          else {
            local_20 = -0x3fc00000;
          }
          param_1[0x10] = local_20;
          param_1[0x15] = 0x41500000;
          fVar6 = (float10)FUN_0042d980();
          if (fVar6 < (float10)810000.0) {
            param_1[0x3c] = 0xd2;
            FUN_0042db10(0,0x43340000);
          }
          fVar6 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar6 / (float10)3.1415927) * (float10)180.0 + (float10)20.0)
          ;
          param_1[0xb6] = 0x428c0000;
        }
        param_1[0x3b] = param_1[0x3b] + 1;
        if ((param_1[0x2b7d] < 2) && (0 < param_1[0x3c])) {
          fVar6 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          local_8 = (float)((fVar6 / (float10)3.1415927) * (float10)180.0);
          fVar6 = (float10)FUN_0042da80();
          fVar11 = (float)(fVar6 + (float10)10.0);
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            fVar6 = (float10)FUN_0042da80();
            local_8 = (float)(fVar6 + (float10)10.0);
          }
          if ((fVar11 < local_8) && (local_8 = local_8 - 5.0, local_8 < fVar11)) {
            local_8 = fVar11;
          }
          if ((local_8 < fVar11) && (local_8 = local_8 + 5.0, fVar11 < local_8)) {
            local_8 = fVar11;
          }
          if (50.0 < local_8) {
            local_8 = 50.0;
          }
          if (local_8 < -30.0) {
            local_8 = -30.0;
          }
          iVar5 = param_1[0x3c];
          fVar6 = (float10)FUN_0065d050(local_8);
          param_1[0x15] = (int)(float)(fVar6 * (float10)((float)iVar5 * 0.1));
          iVar5 = param_1[0x3c];
          fVar6 = (float10)FUN_0065d010(local_8);
          param_1[0x10] = (int)(float)(fVar6 * (float10)((float)iVar5 * 0.1));
          fVar6 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar6 / (float10)3.1415927) * (float10)180.0 + (float10)20.0)
          ;
          param_1[0xb6] = 0x428c0000;
          FUN_0042db10(0,0x40e00000);
          param_1[0x3c] = param_1[0x3c] + -4;
          if (param_1[0x3c] < 0x82) {
            param_1[0x3c] = 0x82;
          }
        }
        if (param_1[0x2b7d] == 1) {
          param_1[0x3a] = param_1[0x3a] + 1;
          FUN_0042db10(0,0x40000000);
          if (6 < param_1[0x2b81]) {
            fVar6 = (float10)FUN_0042d980();
            fVar7 = (float10)FUN_0042da30();
            fVar8 = (float10)FUN_0042da30();
            if (((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar6 < (float10)60000.0) ||
                (0x19 < param_1[0x2b81])) || (param_1[0x3c] == 0)) {
              FUN_00421100(2);
              return;
            }
          }
        }
        if (param_1[0x2b7d] == 2) {
          if (param_1[0x2b81] < 7) {
            FUN_0042db10(0,0x40400000);
          }
          if (param_1[0x2b81] == 10) {
            FUN_0042c880(0x3e);
            fVar6 = (float10)FUN_0042d980();
            if ((((float10)40000.0 <= fVar6) ||
                (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
               (*(char *)((int)param_1 + 0xaec3) != '\x01')) {
              fVar6 = (float10)FUN_0042d980();
              if ((((float10)40000.0 <= fVar6) ||
                  (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
                 (*(char *)((int)param_1 + 0xaebe) != '\x01')) {
                fVar6 = (float10)FUN_0042d980();
                if ((((float10)40000.0 <= fVar6) ||
                    (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
                   (*(char *)((int)param_1 + 0xaeb9) != '\x01')) {
                  FUN_004223d0(1,10,0);
                }
                else {
                  FUN_004223d0(5,0xc,0);
                }
              }
              else {
                FUN_004223d0(0xf,0xc,0);
              }
            }
            else {
              FUN_004223d0(0,0xc,0);
            }
          }
          if (0x19 < param_1[0x2b81]) {
            if ((0.0 < (float)param_1[0xb]) &&
               (param_1[0xb] = (int)((float)param_1[0xb] - 5.0), (float)param_1[0xb] < 0.0)) {
              param_1[0xb] = 0;
            }
            if (((float)param_1[0xb] < 0.0) &&
               (param_1[0xb] = (int)((float)param_1[0xb] + 5.0), 0.0 < (float)param_1[0xb])) {
              param_1[0xb] = 0;
            }
          }
        }
        break;
      case 0x149:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        param_1[0x16] = 0;
        param_1[0x10] = 0;
        param_1[0x18] = 0;
        param_1[0x21d] = 0;
        param_1[0x15] = 0;
        if (param_1[0x1fd] < 1) {
          param_1[0x20d] = param_1[0x20d] + 0x28;
        }
        else {
          param_1[0x20d] = param_1[0x20d] + 5;
        }
        if (1000 < param_1[0x20d]) {
          param_1[0x20d] = 1000;
        }
        break;
      case 0x14a:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
          param_1[0x19] = param_1[0x18];
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x3c] = 0;
          fVar6 = (float10)FUN_0042d980();
          if (fVar6 < (float10)810000.0) {
            param_1[0x3c] = 1;
          }
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if ((param_1[0x2b81] < 10) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b81] < 10) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        if (param_1[0x2b81] == 10) {
          param_1[0x15] = 0x41c80000;
          FUN_0042c880(0x3e);
          fVar6 = (float10)FUN_0042d980();
          if ((((float10)90000.0 <= fVar6) ||
              (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
             (*(char *)((int)param_1 + 0xaec3) != '\x01')) {
            fVar6 = (float10)FUN_0042d980();
            if ((((float10)90000.0 <= fVar6) ||
                (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
               (*(char *)((int)param_1 + 0xaebe) != '\x01')) {
              fVar6 = (float10)FUN_0042d980();
              if ((((float10)90000.0 <= fVar6) ||
                  (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
                 (*(char *)((int)param_1 + 0xaeb9) != '\x01')) {
                FUN_004223d0(2,10,0);
              }
              else {
                FUN_004223d0(5,0xc,0);
              }
            }
            else {
              FUN_004223d0(0xf,0xc,0);
            }
          }
          else {
            FUN_004223d0(0,0xc,0);
          }
        }
        if ((0xf < param_1[0x2b81]) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 3.0), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        break;
      case 0x14b:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if (((char)param_1[0x21] == '\0') && ((param_1[0x2b7d] == 0 || (param_1[0x2b7d] == 3)))) {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x15] = 0;
          param_1[0x3a] = 0;
          param_1[0x3c] = 0;
          fVar6 = (float10)FUN_0042d980();
          if ((float10)360000.0 <= fVar6) {
            param_1[0x19] = param_1[0x18];
          }
          else {
            param_1[0x3c] = 1;
          }
          param_1[0x18] = 0;
        }
        if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) {
          fVar6 = (float10)FUN_0042d980();
          fVar6 = (float10)FUN_0042de80((float)fVar6);
          param_1[0x15] = (int)(float)(fVar6 / (float10)33.0);
          if (15.0 < (float)param_1[0x15]) {
            param_1[0x15] = 0x41700000;
          }
          if ((float)param_1[0x15] < 12.0) {
            param_1[0x15] = 0x41400000;
          }
          param_1[0x10] = 0x41c80000;
          param_1[0x16] = 0x3fc00000;
        }
        if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0x14)) {
          FUN_0042c880(0x3f);
          if ((*(char *)((int)param_1 + 0xaebe) != '\x01') ||
             (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) {
            fVar6 = (float10)FUN_0042d980();
            if ((((float10)30000.0 <= fVar6) ||
                (fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6)) ||
               (*(char *)((int)param_1 + 0xaeb9) != '\x01')) {
              FUN_004223d0(1,10,0);
            }
            else {
              FUN_004223d0(5,0xc,0);
            }
          }
          else {
            FUN_004223d0(0xf,0xc,0);
          }
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 1) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x40a00000);
        }
        if ((param_1[0x2b7d] == 2) && (0xf < param_1[0x2b81])) {
          FUN_00421100(3);
          return;
        }
        if ((((0 < param_1[0x2b7d]) && (param_1[0x2b7d] < 4)) &&
            (param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]),
            (float)param_1[0x10] < 0.0)) && ((char)param_1[0x21] != '\0')) {
          param_1[0x10] = 0;
          param_1[0x15] = 0;
          param_1[0x16] = 0;
          FUN_00421100(4);
          return;
        }
        break;
      case 0x14c:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0x2b);
          return;
        }
        if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b7d])) {
          FUN_00421080(0x14d);
          param_1[0x2b81] = 0x18;
          param_1[0x2b82] = 0x18;
          param_1[0x10] = 0;
          param_1[0x16] = 0;
          return;
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x40a00000);
        }
        if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
          FUN_00422900();
          FUN_00423000();
          param_1[0x15] = 0;
          param_1[0x18] = 0;
          param_1[0x10] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if (param_1[0x2b7d] == 1) {
          FUN_0042db10(0,0x3f800000);
          if (param_1[0x2b81] == 0) {
            FUN_004223d0(3,10,0);
            fVar6 = (float10)FUN_0042da80();
            local_10 = (float)fVar6;
            if (-20.0 < local_10) {
              local_10 = -20.0;
            }
            if (local_10 < -35.0) {
              local_10 = -35.0;
            }
            fVar6 = (float10)FUN_0065d050(local_10);
            param_1[0x15] = (int)(float)(fVar6 * (float10)20.0);
            fVar6 = (float10)FUN_0065d010(local_10);
            param_1[0x10] = (int)(float)(fVar6 * (float10)20.0);
            fVar6 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
            param_1[0xb] = (int)(float)((fVar6 / (float10)3.1415927) * (float10)180.0 + (float10)0.0
                                       );
            if (0.0 < (float)param_1[0xb]) {
              param_1[0xb] = 0;
            }
            param_1[0xb6] = 0x428c0000;
          }
          if (0x2d < param_1[0x2b81]) {
            FUN_00421100(2);
            return;
          }
        }
        if (1 < param_1[0x2b7d]) {
          if ((0.0 < (float)param_1[0xb]) &&
             (param_1[0xb] = (int)((float)param_1[0xb] - 5.0), (float)param_1[0xb] < 0.0)) {
            param_1[0xb] = 0;
          }
          if (((float)param_1[0xb] < 0.0) &&
             (param_1[0xb] = (int)((float)param_1[0xb] + 5.0), 0.0 < (float)param_1[0xb])) {
            param_1[0xb] = 0;
          }
          if ((float)param_1[0x16] == 0.0) {
            param_1[0x16] = 0x3f000000;
          }
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
        }
        break;
      case 0x14d:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        param_1[0x16] = 0;
        param_1[0x10] = 0;
        param_1[0x18] = 0;
        param_1[0x21d] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
        if (param_1[0x1fd] < 1) {
          param_1[0x20d] = param_1[0x20d] + 0x28;
        }
        else {
          param_1[0x20d] = param_1[0x20d] + 5;
        }
        if (1000 < param_1[0x20d]) {
          param_1[0x20d] = 1000;
        }
        break;
      case 0x14e:
        if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 0)) {
          FUN_00421100(1);
          return;
        }
        if (((char)param_1[0x21] != '\0') &&
           ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0))) {
          FUN_00421080(0x14d);
          param_1[0x10] = 0;
          return;
        }
        if ((float)param_1[0x16] == 0.0) {
          param_1[0x16] = 0x3f000000;
        }
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        break;
      case 0x153:
        if (((char)param_1[0x21] != '\0') &&
           ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0))) {
          FUN_00421080(0x2c);
          param_1[0x10] = 0;
          return;
        }
        param_1[0x16] = 0x3f000000;
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        if (0x14 < param_1[0x2b81]) {
          FUN_00421080(0x2b);
          return;
        }
        break;
      case 0x154:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
          param_1[0x3b] = 0;
        }
        param_1[0x1a1] = 2;
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) && (param_1[0x3b] == 0)) {
          param_1[0x3b] = 1;
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] == 0xd) {
          FUN_0042c880(0x3d);
          FUN_004223d0(2,10,0);
        }
        if (param_1[0x2b81] < 10) {
          FUN_0042db10(0,0x41700000);
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x15] = 0x41700000;
        }
        if (param_1[0x2b81] == 0xf) {
          param_1[0x15] = 0;
          param_1[0x21d] = 0;
        }
      }
    }
  }
  else {
    switch(iVar5) {
    case 0x15e:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        if (param_1[0x2b7d] != 1) {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        param_1[0x10] = (int)((float)param_1[0x10] - 0.5);
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x18] = 0;
        param_1[0x15] = 0;
        param_1[0x10] = 0;
        FUN_0042c840(99);
        FUN_0042c800(0);
        FUN_00422900();
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] < 0x1d) {
          FUN_0042db10(0,0x41900000);
        }
        if (param_1[0x2b81] == 0x1e) {
          param_1[0x15] = 0x41a00000;
          FUN_0042c8b0(0xe7);
          FUN_00422300(0x13,1,0x14,0);
        }
      }
      if (param_1[0x2b7d] == 1) {
        if (param_1[0x2b81] % 0x14 == 0) {
          FUN_0042c8b0(0xe8);
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) && (param_1[0x3e] = param_1[0x3e] + 1, 0x1e < param_1[0x3e])) {
          param_1[0x3e] = 0;
          FUN_0042c800(0);
        }
        if ((char)param_1[0x21] != '\0') {
          if (param_1[0x2b81] % 3 == 0) {
            FUN_00435450(9,param_1[5],param_1[6],param_1[7],0,0);
          }
          param_1[0x10] = 0;
          if (300 < param_1[0x2b81]) {
            FUN_00421100(2);
            return;
          }
        }
        param_1[0x21d] = 0x40000000;
        FUN_00421780();
      }
      if ((param_1[0x2b7d] == 2) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      break;
    default:
      goto switchD_0052799f_caseD_1;
    case 0x168:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        if (param_1[0x2b7d] == 1) {
          param_1[0x10] = (int)((float)param_1[0x10] - 0.5);
        }
        else if (param_1[0x2b7d] == 2) {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x15] = 0;
        param_1[0x10] = 0;
        param_1[0x18] = 0;
        FUN_0042c840(99);
        FUN_0042c800(0);
        FUN_00422900();
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] < 0x1d) {
          FUN_0042db10(0,0x41900000);
        }
        if (param_1[0x2b81] == 0x1e) {
          param_1[0x15] = 0x41a00000;
          FUN_0042c8b0(0xe7);
          FUN_00422300(0x13,1,0x14,0);
        }
      }
      if (param_1[0x2b7d] == 1) {
        if (param_1[0x2b81] % 0x14 == 0) {
          FUN_0042c8b0(0xe8);
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) && (param_1[0x3e] = param_1[0x3e] + 1, 0x1e < param_1[0x3e])) {
          param_1[0x3e] = 0;
          FUN_0042c800(0);
        }
        if ((char)param_1[0x21] != '\0') {
          if (param_1[0x2b81] % 3 == 0) {
            FUN_00435450(9,param_1[5],param_1[6],param_1[7],0,0);
          }
          param_1[0x10] = 0;
          if (300 < param_1[0x2b81]) {
            FUN_00421100(2);
            return;
          }
        }
        param_1[0x21d] = 0x40000000;
        FUN_00421780();
      }
      if ((param_1[0x2b7d] == 2) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      break;
    case 0x172:
      if (param_1[0x2b81] == 0) {
        param_1[0x3a] = 0;
        param_1[0x1e9] = 1;
        param_1[0x2bd8] = 1;
        FUN_0042c880(0x31);
        FUN_00422490(0x14,1,0x1e,0);
        FUN_0042c800(0);
        FUN_0042c840(1);
      }
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if (0x3c < param_1[0x3a]) {
        FUN_00421080(0);
        return;
      }
      if (param_1[0x3a] == 0) {
        (**(code **)(*param_1 + 0xc))(0x168,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      }
      param_1[0x1a1] = 4;
      param_1[0x3a] = param_1[0x3a] + 1;
      param_1[0x1f0] = 100;
      param_1[0x1f1] = 0x3c;
      param_1[0x1eb] = 0x3c;
      param_1[0x16] = 0;
      param_1[0x18] = 0;
      param_1[0x21d] = 0;
      param_1[0x15] = 0;
      if (param_1[0x2b81] == 0x2c) {
        param_1[0x2b81] = param_1[0x2b81] + -1;
      }
      break;
    case 0x186:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        if ((char)param_1[0x21] == '\0') {
          param_1[0x16] = 0x3f000000;
          FUN_00421080(0x2b);
          return;
        }
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        param_1[0x16] = 0x3f000000;
        FUN_00421080(0x2b);
        return;
      }
      if ((param_1[0x2b7d] == 1) && (param_1[0x20d] = param_1[0x20d] + -10, param_1[0x20d] < 0)) {
        param_1[0x20d] = 0;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_0042c8b0(4);
        param_1[0x18] = 0;
        param_1[0x15] = 0;
        FUN_0042c800(0);
      }
      if (param_1[0x2b7d] == 0) {
        FUN_0042db10(0,0x41a00000);
      }
      if ((param_1[0x2b7d] == 1) &&
         (((param_1[0x20d] == 0 || (param_1[0xa0] == 0)) || (param_1[0xa1] == 0)))) {
        FUN_00421100(2);
        return;
      }
      uVar3 = FUN_0042c7b0();
      if (((uVar3 & 2) != 0) && (0 < param_1[0x20d])) {
        (**(code **)(*param_1 + 0xc))
                  (0x46,param_1[5],(float)param_1[6] + 100.0,param_1[7],
                   (float)param_1[0x17] + (float)param_1[0x19],0);
        FUN_00421080(0x187);
        FUN_0042c8b0(0x33);
        FUN_0042c800(0);
        return;
      }
      if (param_1[0x2b7d] == 2) {
        param_1[0x21d] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      break;
    case 0x187:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_004223d0(0xc,0x14,0);
        if ((char)param_1[0x21] == '\0') {
          param_1[0x16] = 0x3f000000;
          FUN_00421080(0x2b);
          return;
        }
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        param_1[0x16] = 0x3f000000;
        FUN_00421080(0x67);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x18] = 0;
        param_1[0x15] = -0x3e900000;
        param_1[0x3a] = 0;
      }
      if ((param_1[0x2b7d] < 2) && (uVar3 = FUN_0042c7b0(), (uVar3 & 2) != 0)) {
        FUN_00421080(0x187);
        (**(code **)(*param_1 + 0xc))
                  (0x46,param_1[5],(float)param_1[6] + 100.0,param_1[7],
                   (float)param_1[0x17] + (float)param_1[0x19],0);
        FUN_0042c880(0x33);
        FUN_0042c800(0);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x3a] = param_1[0x3a] + 1, 0x14 < param_1[0x3a])) {
        FUN_00421100(1);
        return;
      }
      if (param_1[0x2b7d] == 2) {
        param_1[0x1eb] = 0x2d;
      }
      if (param_1[0x2b7d] < 3) {
        param_1[0x21d] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] + 1.0);
        if (0.0 < (float)param_1[0x15]) {
          param_1[0x15] = 0;
        }
      }
      break;
    case 0x188:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        if ((char)param_1[0x21] == '\0') {
          param_1[0x16] = 0x3f000000;
          FUN_00421080(0x2b);
          return;
        }
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        param_1[0x16] = 0x3f000000;
        FUN_00421080(0x2b);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x18] = 0;
        param_1[0x15] = -0x3e900000;
        param_1[0x3a] = 0;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x3a] = param_1[0x3a] + 1, 0x14 < param_1[0x3a])) {
        FUN_00421100(1);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_004223d0(0xd,10,0);
      }
      if (param_1[0x2b7d] < 2) {
        param_1[0x21d] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] + 1.0);
        if (0.0 < (float)param_1[0x15]) {
          param_1[0x15] = 0;
        }
      }
      break;
    case 0x189:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        if ((char)param_1[0x21] == '\0') {
          param_1[0x16] = 0x3f000000;
          FUN_00421080(0x2b);
          return;
        }
        FUN_00421080(0);
        return;
      }
      if ((param_1[0x2b7d] == 1) && (param_1[0x20d] = param_1[0x20d] + -10, param_1[0x20d] < 0)) {
        param_1[0x20d] = 0;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_0042c8b0(4);
        param_1[0x18] = 0;
        param_1[0x15] = 0;
        param_1[0x10] = 0;
        param_1[0x16] = 0x3dcccccd;
        FUN_0042c800(0);
      }
      if (param_1[0x2b7d] == 0) {
        FUN_0042db10(0,0x41a00000);
      }
      if ((param_1[0x2b7d] == 1) &&
         (((param_1[0x20d] == 0 || (param_1[0xa0] == 0)) || (param_1[0xa1] == 0)))) {
        FUN_00421100(2);
        return;
      }
      uVar3 = FUN_0042c7b0();
      if (((uVar3 & 2) != 0) && (0 < param_1[0x20d])) {
        (**(code **)(*param_1 + 0xc))
                  (0x46,param_1[5],(float)param_1[6] + 100.0,param_1[7],
                   (float)param_1[0x17] + (float)param_1[0x19],0);
        FUN_00421080(0x18a);
        FUN_0042c8b0(0x33);
        FUN_0042c800(0);
        return;
      }
      if (param_1[0x2b7d] == 2) {
        param_1[0x16] = 0x3f000000;
        param_1[0x21d] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      break;
    case 0x18a:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_004223d0(0xc,0x14,0);
        if ((char)param_1[0x21] == '\0') {
          param_1[0x16] = 0x3f000000;
          FUN_00421080(0x2b);
          return;
        }
        FUN_00421080(0);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x18] = 0;
        param_1[0x15] = -0x3e900000;
        param_1[0x10] = 0x41200000;
        param_1[0x3a] = 0;
        param_1[0x16] = 0x3f000000;
      }
      if ((param_1[0x2b7d] < 2) && (uVar3 = FUN_0042c7b0(), (uVar3 & 2) != 0)) {
        FUN_00421080(0x18a);
        (**(code **)(*param_1 + 0xc))
                  (0x46,param_1[5],(float)param_1[6] + 100.0,param_1[7],
                   (float)param_1[0x17] + (float)param_1[0x19],0);
        FUN_0042c880(0x33);
        FUN_0042c800(0);
        return;
      }
      if ((param_1[0x2b7d] == 1) && (param_1[0x3a] = param_1[0x3a] + 1, 0x14 < param_1[0x3a])) {
        FUN_00421100(2);
        return;
      }
      if (param_1[0x2b7d] == 2) {
        param_1[0x1eb] = 0x2d;
      }
      if (param_1[0x2b7d] < 3) {
        param_1[0x21d] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] + 1.0);
        if (-10.0 < (float)param_1[0x15]) {
          param_1[0x15] = -0x3ee00000;
        }
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      break;
    case 400:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3a] = 0;
        param_1[0x3c] = 2;
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41900000);
      }
      if (param_1[0x2b81] < 0x23) {
        FUN_0042dc20(0,0x40000000);
      }
      if ((0 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 2.0), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if ((((0 < param_1[0x2b81]) && (param_1[0x2b81] < 0xb)) && (0 < param_1[0xae])) &&
         (param_1[0xae] < 0x14)) {
        if (param_1[0x3c] == 4) {
          param_1[0x3c] = 6;
        }
        if (param_1[0x3c] == 2) {
          param_1[0x3c] = 4;
        }
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x23)) {
        if (param_1[0x3e] == 0) {
          if (param_1[0x1b7] < 3) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        if ((param_1[0x3a] % 3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3d] = iVar5;
          if (param_1[0x3d] < -0x2d) {
            param_1[0x3d] = -0x2d;
          }
          if (0x2d < param_1[0x3d]) {
            param_1[0x3d] = 0x2d;
          }
          param_1[0x3e] = param_1[0x3e] + 1;
          FUN_00435000(0,7,0,0,0);
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 0xc) - 6.0) * 0.25 + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,5,((float)(uVar3 % 6) - 3.0) * 0.5,fVar11,uVar13);
          }
          else {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 6) - 3.0) * 0.25 + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,6,((float)(uVar3 % 0xc) - 6.0) * 0.25,fVar11,uVar13);
          }
        }
        if (param_1[0x1b7] < 1) {
          param_1[0x2b81] = 0x23;
          param_1[0x2b82] = 0x23;
        }
        param_1[0x3a] = param_1[0x3a] + 1;
      }
      break;
    case 0x191:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3a] = 5;
        param_1[0x3c] = 2;
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41900000);
      }
      if (param_1[0x2b81] == 10) {
        FUN_0042dc20(0,0x41200000);
      }
      if ((0 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if ((((0 < param_1[0x2b81]) && (param_1[0x2b81] < 0xb)) && (0 < param_1[0xae])) &&
         (param_1[0xae] < 0x14)) {
        if (param_1[0x3c] == 4) {
          param_1[0x3c] = 5;
        }
        if (param_1[0x3c] == 2) {
          param_1[0x3c] = 4;
        }
      }
      if (param_1[0x2b81] == 10) {
        if (param_1[0x3e] == 0) {
          if (param_1[0x1b7] < 3) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        if ((6 < param_1[0x3a]) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3d] = iVar5;
          if (param_1[0x3d] < -0x2d) {
            param_1[0x3d] = -0x2d;
          }
          if (0x2d < param_1[0x3d]) {
            param_1[0x3d] = 0x2d;
          }
          param_1[0x3e] = param_1[0x3e] + 1;
          FUN_00435000(0,2,0,0,0);
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            FUN_00435000(0,0,0,(float)param_1[0x3d],0);
          }
          else {
            FUN_00435000(0,1,0,(float)param_1[0x3d],0);
          }
          if (param_1[0x3e] < param_1[0x3c]) {
            param_1[0x3a] = 0;
          }
        }
        if ((0 < param_1[0x1b7]) && (param_1[0x3e] < param_1[0x3c])) {
          param_1[0x3a] = param_1[0x3a] + 1;
          return;
        }
        param_1[0x2b81] = 0x28;
        param_1[0x2b82] = 0x28;
      }
      break;
    case 0x192:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if ((char)param_1[0x21] != '\0') {
        FUN_00421080(0x193);
        param_1[0x10] = 0;
        return;
      }
      if (param_1[0x2b81] == 0) {
        FUN_00422900();
        param_1[0x3c] = 2;
        param_1[0x3b] = 0;
        param_1[0x3e] = 0;
        param_1[0x3a] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41700000);
      }
      if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x19)) {
        FUN_0042dc20(0,0x40a00000);
      }
      if ((float)param_1[0x16] == 0.0) {
        param_1[0x16] = 0x3f000000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if ((((0 < param_1[0x2b81]) && (param_1[0x2b81] < 0x10)) && (0 < param_1[0xae])) &&
         (param_1[0xae] < 0x14)) {
        if (param_1[0x3c] == 4) {
          param_1[0x3c] = 6;
        }
        if (param_1[0x3c] == 2) {
          param_1[0x3c] = 4;
        }
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x23)) {
        if (param_1[0x3e] == 0) {
          if (param_1[0x1b7] < 3) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        if ((param_1[0x3a] % 3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3d] = iVar5;
          if (param_1[0x3d] < -0x2d) {
            param_1[0x3d] = -0x2d;
          }
          if (0x2d < param_1[0x3d]) {
            param_1[0x3d] = 0x2d;
          }
          param_1[0x3e] = param_1[0x3e] + 1;
          FUN_00435000(0,7,0,0,0);
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 6) - 3.0) * 0.25 + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,5,((float)(uVar3 % 6) - 3.0) * 0.5,fVar11,uVar13);
          }
          else {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 6) - 3.0) * 0.25 + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,6,((float)(uVar3 % 6) - 3.0) * 0.5,fVar11,uVar13);
          }
        }
        if (param_1[0x1b7] < 1) {
          param_1[0x2b81] = 0x23;
          param_1[0x2b82] = 0x23;
        }
        param_1[0x3a] = param_1[0x3a] + 1;
      }
      break;
    case 0x193:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      param_1[0x16] = 0;
      param_1[0x10] = 0;
      param_1[0x18] = 0;
      param_1[0x21d] = 0;
      param_1[0x15] = 0;
      if (param_1[0x1fd] < 1) {
        param_1[0x20d] = param_1[0x20d] + 0x28;
      }
      else {
        param_1[0x20d] = param_1[0x20d] + 5;
      }
      if (1000 < param_1[0x20d]) {
        param_1[0x20d] = 1000;
      }
      break;
    case 0x194:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3a] = 0;
      }
      if ((0x19 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        param_1[0x15] = 0x41700000;
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x1b)) {
        if (param_1[0x3a] == 0) {
          if (param_1[0x1b7] < 6) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        uVar3 = param_1[0x3a] & 0x80000001;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
        }
        if ((uVar3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3d] = iVar5;
          if (param_1[0x3d] < -0x1e) {
            param_1[0x3d] = -0x1e;
          }
          if (0x1e < param_1[0x3d]) {
            param_1[0x3d] = 0x1e;
          }
          param_1[0x3e] = param_1[0x3e] + 1;
          FUN_00435000(0,7,0,0,0);
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,5,(float)(uVar3 % 6) - 3.0,fVar11,uVar13);
          }
          else {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,6,(float)(uVar3 % 6) - 3.0,fVar11,uVar13);
          }
        }
        param_1[0x3a] = param_1[0x3a] + 1;
      }
      break;
    case 0x195:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3a] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41700000);
      }
      if (param_1[0x2b81] < 0x19) {
        FUN_0042db10(0,0x40a00000);
      }
      if ((0x19 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = -0x3d4c0000;
        param_1[0x15] = 0x41480000;
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x1b)) {
        if (param_1[0x3a] == 0) {
          if (param_1[0x1b7] < 6) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        uVar3 = param_1[0x3a] & 0x80000001;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
        }
        if ((uVar3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3d] = iVar5;
          if (param_1[0x3d] < -0x1e) {
            param_1[0x3d] = -0x1e;
          }
          if (0x1e < param_1[0x3d]) {
            param_1[0x3d] = 0x1e;
          }
          if (((float)param_1[0x19] < 10.0) && (-10.0 < (float)param_1[0x19])) {
            param_1[0x3b] = 0;
          }
          if (10.0 < (float)param_1[0x19]) {
            iVar5 = FUN_0066b668();
            param_1[0x3b] = iVar5;
          }
          if ((float)param_1[0x19] < -10.0) {
            iVar5 = FUN_0066b668();
            param_1[0x3b] = iVar5;
          }
          param_1[0x3e] = param_1[0x3e] + 1;
          FUN_00435000(0,7,0,0,0);
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            uVar13 = 1;
            uVar3 = FUN_0065d150(1);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            iVar5 = param_1[0x3b];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,5,((float)(uVar3 % 6) + (float)iVar5) - 3.0,fVar11,uVar13);
          }
          else {
            uVar13 = 1;
            uVar3 = FUN_0065d150(1);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            iVar5 = param_1[0x3b];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,6,((float)(uVar3 % 6) + (float)iVar5) - 3.0,fVar11,uVar13);
          }
        }
        param_1[0x3a] = param_1[0x3a] + 1;
      }
      break;
    case 0x196:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3a] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41700000);
      }
      if (param_1[0x2b81] < 0x19) {
        FUN_0042db10(0,0x40a00000);
      }
      if ((0x19 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x42b40000;
        param_1[0x15] = 0x41480000;
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x1b)) {
        if (param_1[0x3a] == 0) {
          if (param_1[0x1b7] < 6) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        uVar3 = param_1[0x3a] & 0x80000001;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
        }
        if ((uVar3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3d] = iVar5;
          if (param_1[0x3d] < -0x1e) {
            param_1[0x3d] = -0x1e;
          }
          if (0x1e < param_1[0x3d]) {
            param_1[0x3d] = 0x1e;
          }
          if (((float)param_1[0x19] < 10.0) && (-10.0 < (float)param_1[0x19])) {
            param_1[0x3b] = 0;
          }
          if (10.0 < (float)param_1[0x19]) {
            iVar5 = FUN_0066b668();
            param_1[0x3b] = iVar5;
          }
          if ((float)param_1[0x19] < -10.0) {
            iVar5 = FUN_0066b668();
            param_1[0x3b] = iVar5;
          }
          param_1[0x3e] = param_1[0x3e] + 1;
          FUN_00435000(0,7,0,0,0);
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            uVar13 = 1;
            uVar3 = FUN_0065d150(1);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            iVar5 = param_1[0x3b];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,5,((float)(uVar3 % 6) + (float)iVar5) - 3.0,fVar11,uVar13);
          }
          else {
            uVar13 = 1;
            uVar3 = FUN_0065d150(1);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            iVar5 = param_1[0x3b];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,6,((float)(uVar3 % 6) + (float)iVar5) - 3.0,fVar11,uVar13);
          }
        }
        param_1[0x3a] = param_1[0x3a] + 1;
      }
      break;
    case 0x197:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3a] = 0;
      }
      if ((0x14 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] + 0.5), 0.0 < (float)param_1[0x15])) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x41200000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        param_1[0x15] = -0x3e740000;
      }
      if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x15)) {
        if (param_1[0x3a] == 0) {
          if (param_1[0x1b7] < 6) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        uVar3 = param_1[0x3a] & 0x80000001;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
        }
        if ((uVar3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3d] = iVar5;
          if (param_1[0x3d] < -0x2d) {
            param_1[0x3d] = -0x2d;
          }
          if (0x2d < param_1[0x3d]) {
            param_1[0x3d] = 0x2d;
          }
          param_1[0x3e] = param_1[0x3e] + 1;
          FUN_00435000(0,7,0,0,0);
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,5,(float)(uVar3 % 6) - 3.0,fVar11,uVar13);
          }
          else {
            uVar13 = 0;
            uVar3 = FUN_0065d150(0);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3d];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,6,(float)(uVar3 % 6) - 3.0,fVar11,uVar13);
          }
        }
        param_1[0x3a] = param_1[0x3a] + 1;
      }
      break;
    case 0x198:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b81])) {
        FUN_00421080(0x199);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41a00000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
      }
      if ((float)param_1[0x16] == 0.0) {
        param_1[0x16] = 0x3f000000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x46);
        FUN_004230e0();
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_00434fd0(0,0,(float)param_1[0x3c],0);
      }
      break;
    case 0x199:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      param_1[0x16] = 0;
      param_1[0x10] = 0;
      param_1[0x18] = 0;
      param_1[0x21d] = 0;
      param_1[0x15] = 0;
      if (param_1[0x1fd] < 1) {
        param_1[0x20d] = param_1[0x20d] + 0x28;
      }
      else {
        param_1[0x20d] = param_1[0x20d] + 5;
      }
      if (1000 < param_1[0x20d]) {
        param_1[0x20d] = 1000;
      }
      break;
    case 0x19a:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) {
          FUN_00421080(0);
          return;
        }
        FUN_004211f0(10);
        if (param_1[0x3e] != 1) {
          return;
        }
        FUN_00421080(10);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x3e] = 0;
        param_1[0x3d] = 0;
        param_1[0x21d] = 0;
      }
      if (param_1[0x2b81] < 0x23) {
        param_1[0x1a] = param_1[0x19];
        if ((float)param_1[0x1a] <= 85.0) {
          local_108 = (float)param_1[0x1a];
        }
        else {
          local_108 = 85.0;
        }
        if (-85.0 <= local_108) {
          if ((float)param_1[0x1a] <= 85.0) {
            local_110 = param_1[0x1a];
          }
          else {
            local_110 = 0x42aa0000;
          }
          local_10c = local_110;
        }
        else {
          local_10c = -0x3d560000;
        }
        param_1[0x1a] = local_10c;
      }
      if ((param_1[0x3e] == 0) && (0 < param_1[0x2b81])) {
        if (param_1[0x9f] < 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1)) {
            param_1[0x3a] = 1;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0)) {
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2)) {
            param_1[0x3a] = 2;
            param_1[0x21d] = 0x41200000;
          }
        }
        if (param_1[0x9f] == 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3)) {
            param_1[0x3a] = 3;
            param_1[0x21d] = 0x41200000;
          }
          if (param_1[0x9e] == 0) {
            param_1[0x3e] = 1;
            param_1[0x2b7c] = 0;
            param_1[0x2b7e] = 0;
            param_1[0x2b82] = 0;
            FUN_00421410(0,0);
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4)) {
            param_1[0x3a] = 4;
            param_1[0x21d] = 0x41200000;
          }
        }
        if (0 < param_1[0x9f]) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5)) {
            param_1[0x3a] = 5;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6)) {
            param_1[0x3a] = 6;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7)) {
            param_1[0x3a] = 7;
            param_1[0x21d] = 0x41200000;
          }
        }
      }
      if (((0 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
         ((param_1[0x9f] != 0 || (param_1[0x9e] != 0)))) {
        param_1[0x3e] = 0;
        param_1[0x2b7c] = 10;
        param_1[0x2b7e] = 0;
        param_1[0x2b82] = 0;
        puVar4 = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
        FUN_00421410(0,*puVar4);
        if (param_1[0x9f] < 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1)) {
            param_1[0x3a] = 1;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0)) {
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2)) {
            param_1[0x3a] = 2;
            param_1[0x21d] = 0x41200000;
          }
        }
        if (param_1[0x9f] == 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3)) {
            param_1[0x3a] = 3;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4)) {
            param_1[0x3a] = 4;
            param_1[0x21d] = 0x41200000;
          }
        }
        if (0 < param_1[0x9f]) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5)) {
            param_1[0x3a] = 5;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6)) {
            param_1[0x3a] = 6;
            param_1[0x21d] = 0x41200000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7)) {
            param_1[0x3a] = 7;
            param_1[0x21d] = 0x41200000;
          }
        }
      }
      if (param_1[0x3e] == 0) {
        param_1[0x15] = 0x40c80000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0 < param_1[0x2b81]) {
        param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
        if ((float)param_1[0x21d] < 1.0) {
          param_1[0x21d] = 0x3f800000;
        }
        FUN_00421780();
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x18] = 0;
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x24)) {
        if (param_1[0x2b81] == 0xf) {
          if (param_1[0x1b7] == 1) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        if ((param_1[0x3d] % 3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          if (((float)param_1[0x19] < 120.0) && (-120.0 < (float)param_1[0x19])) {
            param_1[0x3b] = 0;
          }
          if (120.0 < (float)param_1[0x19]) {
            iVar5 = FUN_0066b668();
            param_1[0x3b] = iVar5;
          }
          if ((float)param_1[0x19] < -120.0) {
            iVar5 = FUN_0066b668();
            param_1[0x3b] = iVar5;
          }
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3c] = iVar5;
          if (param_1[0x3c] < -0x28) {
            param_1[0x3c] = -0x28;
          }
          if (0x28 < param_1[0x3c]) {
            param_1[0x3c] = 0x28;
          }
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            uVar13 = 1;
            uVar3 = FUN_0065d150(1);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3c];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,5,((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3b],fVar11,uVar13);
          }
          else {
            uVar13 = 1;
            uVar3 = FUN_0065d150(1);
            fVar11 = ((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3c];
            uVar3 = FUN_0065d150(fVar11);
            FUN_00435000(0,6,((float)(uVar3 % 6) - 3.0) + (float)param_1[0x3b],fVar11,uVar13);
          }
          FUN_00435000(0,7,0,0,0);
        }
        param_1[0x3d] = param_1[0x3d] + 1;
      }
      break;
    case 0x19b:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) {
          FUN_00421080(0);
          return;
        }
        FUN_004211f0(10);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x3e] = 0;
        param_1[0x3d] = 0;
        param_1[0x21d] = 0;
      }
      if (param_1[0x2b81] < 0x23) {
        param_1[0x1a] = param_1[0x19];
        if ((float)param_1[0x1a] <= 60.0) {
          local_134 = (float)param_1[0x1a];
        }
        else {
          local_134 = 60.0;
        }
        if (-60.0 <= local_134) {
          if ((float)param_1[0x1a] <= 60.0) {
            local_13c = param_1[0x1a];
          }
          else {
            local_13c = 0x42700000;
          }
          local_138 = local_13c;
        }
        else {
          local_138 = -0x3d900000;
        }
        param_1[0x1a] = local_138;
      }
      if ((param_1[0x3e] == 0) && (0x23 < param_1[0x2b81])) {
        if (param_1[0x9f] < 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1)) {
            param_1[0x3a] = 1;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0)) {
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2)) {
            param_1[0x3a] = 2;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (param_1[0x9f] == 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3)) {
            param_1[0x3a] = 3;
            param_1[0x21d] = 0x41a00000;
          }
          if (param_1[0x9e] == 0) {
            param_1[0x3e] = 1;
            param_1[0x2b7c] = 0;
            param_1[0x2b7e] = 0;
            param_1[0x2b82] = 0;
            FUN_00421410(0,0);
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4)) {
            param_1[0x3a] = 4;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (0 < param_1[0x9f]) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5)) {
            param_1[0x3a] = 5;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6)) {
            param_1[0x3a] = 6;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7)) {
            param_1[0x3a] = 7;
            param_1[0x21d] = 0x41a00000;
          }
        }
      }
      if (((0x23 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
         ((param_1[0x9f] != 0 || (param_1[0x9e] != 0)))) {
        param_1[0x3e] = 0;
        param_1[0x2b7c] = 10;
        param_1[0x2b7e] = 0;
        param_1[0x2b82] = 0;
        puVar4 = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
        FUN_00421410(0,*puVar4);
        if (param_1[0x9f] < 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1)) {
            param_1[0x3a] = 1;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0)) {
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2)) {
            param_1[0x3a] = 2;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (param_1[0x9f] == 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3)) {
            param_1[0x3a] = 3;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4)) {
            param_1[0x3a] = 4;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (0 < param_1[0x9f]) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5)) {
            param_1[0x3a] = 5;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6)) {
            param_1[0x3a] = 6;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7)) {
            param_1[0x3a] = 7;
            param_1[0x21d] = 0x41a00000;
          }
        }
      }
      if (param_1[0x3e] == 0) {
        param_1[0x15] = 0x40c80000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0xc < param_1[0x2b81]) {
        param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
        if ((float)param_1[0x21d] < 1.0) {
          param_1[0x21d] = 0x3f800000;
        }
        FUN_00421780();
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x18] = 0;
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x24)) {
        if (param_1[0x2b81] == 0xf) {
          if (param_1[0x1b7] == 1) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        if ((param_1[0x3d] % 3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          iVar5 = FUN_0066b668();
          param_1[0x3b] = iVar5;
          if (param_1[0x3b] < 0x65) {
            local_140 = param_1[0x3b];
          }
          else {
            local_140 = 100;
          }
          if (local_140 < 0x14) {
            local_144 = 0x14;
          }
          else {
            if (param_1[0x3b] < 0x65) {
              local_148 = param_1[0x3b];
            }
            else {
              local_148 = 100;
            }
            local_144 = local_148;
          }
          param_1[0x3b] = local_144;
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3c] = iVar5;
          if (param_1[0x3c] < -0x28) {
            param_1[0x3c] = -0x28;
          }
          if (0x28 < param_1[0x3c]) {
            param_1[0x3c] = 0x28;
          }
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            FUN_00435000(0,5,(float)param_1[0x3b],(float)param_1[0x3c],0);
          }
          else {
            FUN_00435000(0,6,(float)param_1[0x3b],(float)param_1[0x3c],0);
          }
          FUN_00435000(0,7,0,0,0);
        }
        param_1[0x3d] = param_1[0x3d] + 1;
      }
      break;
    case 0x19c:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) {
          FUN_00421080(0);
          return;
        }
        FUN_004211f0(10);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x3e] = 0;
        param_1[0x3d] = 0;
        param_1[0x21d] = 0;
      }
      if (param_1[0x2b81] < 0x23) {
        param_1[0x1a] = param_1[0x19];
        if ((float)param_1[0x1a] <= 60.0) {
          local_14c = (float)param_1[0x1a];
        }
        else {
          local_14c = 60.0;
        }
        if (-60.0 <= local_14c) {
          if ((float)param_1[0x1a] <= 60.0) {
            local_154 = param_1[0x1a];
          }
          else {
            local_154 = 0x42700000;
          }
          local_150 = local_154;
        }
        else {
          local_150 = -0x3d900000;
        }
        param_1[0x1a] = local_150;
      }
      if ((param_1[0x3e] == 0) && (0x23 < param_1[0x2b81])) {
        if (param_1[0x9f] < 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1)) {
            param_1[0x3a] = 1;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0)) {
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2)) {
            param_1[0x3a] = 2;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (param_1[0x9f] == 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3)) {
            param_1[0x3a] = 3;
            param_1[0x21d] = 0x41a00000;
          }
          if (param_1[0x9e] == 0) {
            param_1[0x3e] = 1;
            param_1[0x2b7c] = 0;
            param_1[0x2b7e] = 0;
            param_1[0x2b82] = 0;
            FUN_00421410(0,0);
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4)) {
            param_1[0x3a] = 4;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (0 < param_1[0x9f]) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5)) {
            param_1[0x3a] = 5;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6)) {
            param_1[0x3a] = 6;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7)) {
            param_1[0x3a] = 7;
            param_1[0x21d] = 0x41a00000;
          }
        }
      }
      if (((0x23 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
         ((param_1[0x9f] != 0 || (param_1[0x9e] != 0)))) {
        param_1[0x3e] = 0;
        param_1[0x2b7c] = 10;
        param_1[0x2b7e] = 0;
        param_1[0x2b82] = 0;
        puVar4 = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
        FUN_00421410(0,*puVar4);
        if (param_1[0x9f] < 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1)) {
            param_1[0x3a] = 1;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0)) {
            param_1[0x3a] = 0;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2)) {
            param_1[0x3a] = 2;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (param_1[0x9f] == 0) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3)) {
            param_1[0x3a] = 3;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4)) {
            param_1[0x3a] = 4;
            param_1[0x21d] = 0x41a00000;
          }
        }
        if (0 < param_1[0x9f]) {
          if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5)) {
            param_1[0x3a] = 5;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6)) {
            param_1[0x3a] = 6;
            param_1[0x21d] = 0x41a00000;
          }
          if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7)) {
            param_1[0x3a] = 7;
            param_1[0x21d] = 0x41a00000;
          }
        }
      }
      if (param_1[0x3e] == 0) {
        param_1[0x15] = 0x40c80000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0xc < param_1[0x2b81]) {
        param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
        if ((float)param_1[0x21d] < 1.0) {
          param_1[0x21d] = 0x3f800000;
        }
        FUN_00421780();
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x18] = 0;
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x24)) {
        if (param_1[0x2b81] == 0xf) {
          if (param_1[0x1b7] == 1) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        if ((param_1[0x3d] % 3 == 0) && (0 < param_1[0x1b7])) {
          FUN_0042c8b0(0xe6);
          iVar5 = FUN_0066b668();
          param_1[0x3b] = iVar5;
          if (param_1[0x3b] < -0x13) {
            local_158 = param_1[0x3b];
          }
          else {
            local_158 = -0x14;
          }
          if (local_158 < -100) {
            local_15c = -100;
          }
          else {
            if (param_1[0x3b] < -0x13) {
              local_160 = param_1[0x3b];
            }
            else {
              local_160 = -0x14;
            }
            local_15c = local_160;
          }
          param_1[0x3b] = local_15c;
          FUN_0042da80();
          iVar5 = FUN_0066b668();
          param_1[0x3c] = iVar5;
          if (param_1[0x3c] < -0x28) {
            param_1[0x3c] = -0x28;
          }
          if (0x28 < param_1[0x3c]) {
            param_1[0x3c] = 0x28;
          }
          FUN_004230e0();
          if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
            FUN_00435000(0,5,(float)param_1[0x3b],(float)param_1[0x3c],0);
          }
          else {
            FUN_00435000(0,6,(float)param_1[0x3b],(float)param_1[0x3c],0);
          }
          FUN_00435000(0,7,0,0,0);
        }
        param_1[0x3d] = param_1[0x3d] + 1;
      }
      break;
    case 0x1c2:
      FUN_00434a70(0,2);
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3e] = 0;
        FUN_00422240(0x20,0x14,0);
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] < 5) {
        FUN_0042dc20(0,0x420c0000);
      }
      if (param_1[0x2b81] < 0x1e) {
        FUN_0042dc20(0,0x3e99999a);
      }
      if (param_1[0x2b81] == 0x1e) {
        FUN_0042c8b0(0x7c);
        FUN_0042c8b0(0x7e);
        FUN_004230e0();
        uVar13 = 0;
        fVar12 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar12,0);
        fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
        fVar9 = (float)param_1[6] + 75.0;
        fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
        FUN_00435450(4,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                     fVar12,uVar13);
        FUN_0042dac0(2);
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar12 = (float)param_1[0x3c];
          fVar9 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar12);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar10 = (float)param_1[6] + 75.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar10,fVar11);
          FUN_00435450(0,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar10,fVar11,
                       fVar9,fVar12);
        }
        else {
          fVar12 = (float)param_1[0x3c];
          fVar9 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar12);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar10 = (float)param_1[6] + 75.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar10,fVar11);
          FUN_00435450(2,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar10,fVar11,
                       fVar9,fVar12);
        }
      }
      if ((param_1[0x2b81] == 0x1c) && (param_1[0x3e] < 0xf)) {
        param_1[0x3e] = param_1[0x3e] + 1;
        return;
      }
      break;
    case 0x1cc:
      FUN_00434a70(0,2);
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b81])) {
        FUN_00421080(0x1d5);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x16] = 0x3f000000;
        param_1[0x10] = (int)((float)param_1[0x10] * 0.25);
        param_1[0x15] = (int)((float)param_1[0x15] * 0.25);
        FUN_00422240(0x20,0x14,0);
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] < 5) {
        FUN_0042dc20(0,0x420c0000);
      }
      if (param_1[0x2b81] < 0x1e) {
        FUN_0042dc20(0,0x3e99999a);
      }
      if (param_1[0x2b81] == 0x1e) {
        FUN_0042c8b0(0x7c);
        FUN_0042c8b0(0x7e);
        FUN_004230e0();
        fVar12 = (float)param_1[0x3c];
        fVar9 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar12);
        fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
        fVar10 = (float)param_1[6] + 75.0;
        fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar10,fVar11);
        FUN_00435450(4,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar10,fVar11,
                     fVar9,fVar12);
        FUN_0042dac0(2);
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar12 = (float)param_1[0x3c];
          fVar9 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar12);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar10 = (float)param_1[6] + 75.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar10,fVar11);
          FUN_00435450(0,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar10,fVar11,
                       fVar9,fVar12);
        }
        else {
          fVar12 = (float)param_1[0x3c];
          fVar9 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar12);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar10 = (float)param_1[6] + 75.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar10,fVar11);
          FUN_00435450(2,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar10,fVar11,
                       fVar9,fVar12);
        }
      }
      if ((param_1[0x2b81] == 0x1c) && (param_1[0x3e] < 0xf)) {
        param_1[0x3e] = param_1[0x3e] + 1;
        return;
      }
      if (0x1e < param_1[0x2b81]) {
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      }
      break;
    case 0x1d5:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      param_1[0x16] = 0;
      param_1[0x10] = 0;
      param_1[0x18] = 0;
      param_1[0x21d] = 0;
      param_1[0x15] = 0;
      if (param_1[0x1fd] < 1) {
        param_1[0x20d] = param_1[0x20d] + 0x28;
      }
      else {
        param_1[0x20d] = param_1[0x20d] + 5;
      }
      if (1000 < param_1[0x20d]) {
        param_1[0x20d] = 1000;
      }
    }
  }
  param_1[0x2b81] = param_1[0x2b81] + 1;
  param_1[0x2b82] = param_1[0x2b82] + 1;
  FUN_004212f0();
  if ((*(int *)param_1[0x2b79] < param_1[0x2b81]) && (*(int *)(param_1[0x2b79] + 0x20) == 0)) {
    FUN_00421100(param_1[0x2b7d] + 1);
  }
  return;
}

