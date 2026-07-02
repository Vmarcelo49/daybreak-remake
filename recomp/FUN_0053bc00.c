// ============================================
// Address:  0x0053bc00
// Original: FUN_0053bc00
// Status:   unreviewed
// ============================================


void __fastcall FUN_0053bc00(int *param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_54;
  int local_50;
  float local_4c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_8;
  
  if (param_1[0x28] != 0) {
    return;
  }
  FUN_00434a70(0,0);
  FUN_00434a70(1,1);
  FUN_00434bd0();
  param_1[0x2bdb] = 0;
  iVar6 = param_1[0x2b7b];
  if (iVar6 < 0x169) {
    if (iVar6 == 0x168) {
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = 0;
        param_1[0x10] = 0;
        param_1[0x3a] = 0;
        param_1[0x3b] = 0;
        param_1[0x3c] = 0;
        FUN_00422900();
        param_1[0x2bdb] = 1;
        FUN_004223d0(0x21,0x14,0);
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x41900000);
      }
      if (param_1[0x2b81] == 0x11) {
        FUN_0042c8b0(0x9a);
        FUN_004230e0();
        uVar13 = 0x41f00000;
        uVar11 = 0;
        uVar10 = 0xf;
        uVar4 = FUN_0064e6c0("Bip01_R_Hand");
        FUN_00435220(uVar4,uVar10,uVar11,uVar13);
      }
      if (0x23 < param_1[0x2b81]) {
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        param_1[0x16] = 0x3f000000;
        if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
          FUN_00421080(0x169);
          return;
        }
      }
    }
    else if (iVar6 < 0x12e) {
      if (iVar6 == 0x12d) {
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
        if (param_1[0x3b] != 0) {
          param_1[0x1a1] = 2;
          if (param_1[0x2b81] < 8) {
            FUN_0042db10(0,0x41200000);
          }
          if ((0x10 < param_1[0x2b81]) && (param_1[0x2b81] < 0x1c)) {
            FUN_0042db10(0,0x41200000);
          }
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          param_1[0x15] = 0x41700000;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if (param_1[0x2b81] == 0x13) {
          param_1[0x15] = 0x41200000;
        }
        if (param_1[0x2b81] == 0x1c) {
          FUN_00423000();
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if (param_1[0x2b81] == 0x1c) {
          FUN_0042c880(0x3e);
        }
        if (param_1[0x2b81] == 0x21) {
          param_1[0x15] = 0;
        }
        if (param_1[0x2b81] == 0x25) {
          param_1[0x15] = 0;
          param_1[0x21d] = 0;
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] < 0x13) {
          param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
          if (param_1[0x2b81] == 4) {
            FUN_0042c880(0x3d);
            FUN_004223d0(2,10,0);
          }
        }
      }
      else if (iVar6 < 0x1f) {
        if (iVar6 == 0x1e) {
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if (param_1[0x2b7d] < 3) {
            param_1[0x20d] = param_1[0x20d] + -9;
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
            param_1[0x15] = 0x41640000;
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
            param_1[0x15] = 0x41640000;
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
        }
        else {
          switch(iVar6) {
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
            goto switchD_0053bcbc_caseD_1;
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
            param_1[0x15] = 0x40b00000;
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
            if ((param_1[0x2b7d] < 2) && (param_1[0x20d] = param_1[0x20d] + -8, param_1[0x20d] < 0))
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
              fVar7 = (float10)FUN_0042df90(param_1[0x19]);
              if ((float10)12.0 <= fVar7) {
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
              param_1[0x15] = 0x41580000;
              param_1[0x3a] = 0;
            }
            if (param_1[0x2b7d] == 1) {
              param_1[0x21d] = 0x40800000;
              param_1[0x15] = 0x41580000;
              FUN_00421780();
              if (((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) || (param_1[0x20d] < 1)) {
                FUN_00421100(2);
                return;
              }
            }
            if (param_1[0x2b7d] == 2) {
              param_1[0x21d] = 0;
              param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
              if ((float)param_1[0x15] < 0.0) {
                param_1[0x15] = 0;
              }
              if ((param_1[0x2b81] == 1) && (param_1[0x3a] < 0xf)) {
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
              param_1[0x20d] = param_1[0x20d] + -8;
              if (param_1[0x20d] < 0) {
                param_1[0x20d] = 0;
              }
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
              param_1[0x19] = 0;
              param_1[0x18] = -0x3d4c0000;
              param_1[0x15] = 0x41900000;
              param_1[0x2bd2] = param_1[0x2bd2] + 1;
            }
            if (param_1[0x2b7d] == 1) {
              param_1[0x18] = -0x3d4c0000;
            }
            if ((param_1[0x2b7d] < 2) &&
               (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 11.5)) {
              param_1[0x15] = 0x41380000;
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
              param_1[0x20d] = param_1[0x20d] + -8;
              if (param_1[0x20d] < 0) {
                param_1[0x20d] = 0;
              }
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
              param_1[0x19] = 0;
              param_1[0x18] = 0x42b40000;
              param_1[0x15] = 0x41900000;
              param_1[0x2bd2] = param_1[0x2bd2] + 1;
            }
            if (param_1[0x2b7d] == 1) {
              param_1[0x18] = 0x42b40000;
            }
            if ((param_1[0x2b7d] < 2) &&
               (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 11.5)) {
              param_1[0x15] = 0x41380000;
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
            if ((param_1[0x2b7d] < 2) && (param_1[0x20d] = param_1[0x20d] + -8, param_1[0x20d] < 0))
            {
              param_1[0x20d] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
              param_1[0x19] = 0;
              param_1[0x18] = 0x43340000;
              param_1[0x15] = 0x41600000;
              param_1[0x2bd2] = param_1[0x2bd2] + 1;
            }
            if (param_1[0x2b7d] == 1) {
              param_1[0x21d] = 0;
              param_1[0x15] = 0x41600000;
              param_1[0x18] = 0x43340000;
            }
            if ((param_1[0x2b7d] == 2) &&
               (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
              param_1[0x15] = 0;
            }
          }
        }
      }
      else {
        if (300 < iVar6) {
switchD_0053bcbc_caseD_1:
          FUN_00428510();
          return;
        }
        if (iVar6 == 300) {
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
            param_1[0x18] = 0;
            FUN_0042c800(0);
            FUN_0042c840(1);
            param_1[0x3a] = 0;
            param_1[0x3b] = 0;
            param_1[0x3c] = 1;
            param_1[0x15] = 0x41700000;
            fVar7 = (float10)FUN_0042d980();
            if (fVar7 < (float10)360000.0) {
              param_1[0x3c] = 1;
            }
            FUN_0042db10(0,0x43340000);
          }
          sVar2 = FUN_0042c7b0();
          if ((sVar2 != 0) && (param_1[0x3b] == 0)) {
            param_1[0x3b] = 1;
          }
          uVar3 = FUN_0042c7b0();
          if ((uVar3 & 2) != 0) {
            FUN_00421080(0x188);
            FUN_0042c800(0);
            return;
          }
          if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1)) {
            FUN_0042db10(0,0x40e00000);
          }
          if (param_1[0x2b7d] == 1) {
            if (param_1[0x3c] == 1) {
              FUN_0042db10(0,0x40e00000);
            }
            fVar7 = (float10)FUN_0042d980();
            if ((fVar7 < (float10)90000.0) || (param_1[0x3c] == 0)) {
              FUN_00421100(2);
              return;
            }
          }
          if (param_1[0x2b7d] == 2) {
            if (param_1[0x2b81] < 0xc) {
              FUN_0042db10(0,0x40a00000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.75);
            if ((float)param_1[0x15] < 0.0) {
              param_1[0x15] = 0;
            }
          }
          if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 0xc)) {
            FUN_0042c880(0x3d);
            fVar7 = (float10)FUN_0042d980();
            if (((float10)90000.0 <= fVar7) ||
               ((fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7 ||
                (*(char *)((int)param_1 + 0xaec3) != '\x01')))) {
              fVar7 = (float10)FUN_0042d980();
              if (((float10)90000.0 <= fVar7) ||
                 ((fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7 ||
                  (*(char *)((int)param_1 + 0xaebe) != '\x01')))) {
                fVar7 = (float10)FUN_0042d980();
                if (((float10)90000.0 <= fVar7) ||
                   ((fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7 ||
                    (*(char *)((int)param_1 + 0xaeb9) != '\x01')))) {
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
        }
        else {
          switch(iVar6) {
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
              param_1[0x10] = 0x41280000;
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
            break;
          default:
            goto switchD_0053bcbc_caseD_1;
          }
        }
      }
    }
    else {
      switch(iVar6) {
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
          FUN_00422900();
          FUN_00423000();
        }
        if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x15] = 0x418c0000;
          FUN_0042db10(0,0x43340000);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x40a00000);
        }
        if (param_1[0x2b7d] == 1) {
          FUN_0042db10(0,0x40a00000);
          fVar7 = (float10)FUN_0042d980();
          if (fVar7 < (float10)40000.0) {
            FUN_00421100(2);
            return;
          }
        }
        if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 7)) {
          FUN_0042c880(0x3c);
          FUN_004223d0(2,10,0);
        }
        if ((param_1[0x2b7d] == 2) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        break;
      case 0x137:
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x15] = 0;
          FUN_0042db10(0,0x43340000);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] < 0x14) {
          FUN_0042db10(0,0x41200000);
        }
        if (param_1[0x2b81] < 10) {
          FUN_0042db10(0,0x40c00000);
        }
        if (param_1[0x2b81] == 0xc) {
          param_1[0x15] = 0x420c0000;
          FUN_0042c880(0x3c);
          FUN_004223d0(2,10,0);
        }
        if (param_1[0x2b81] == 0x16) {
          param_1[0x15] = 0x41200000;
        }
        if ((0x16 < param_1[0x2b81]) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        break;
      default:
        goto switchD_0053bcbc_caseD_1;
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
        if ((param_1[0x2b7d] == 2) && (0xf < param_1[0x2b81])) {
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        }
        if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) && (0x14 < param_1[0x2b81])) {
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
            local_4c = (float)param_1[0x10];
          }
          else {
            local_4c = 3.0;
          }
          if (-3.0 <= local_4c) {
            if ((float)param_1[0x10] <= 3.0) {
              local_54 = param_1[0x10];
            }
            else {
              local_54 = 0x40400000;
            }
            local_50 = local_54;
          }
          else {
            local_50 = -0x3fc00000;
          }
          param_1[0x10] = local_50;
          param_1[0x15] = 0x41400000;
          if ((param_1[0x2b81] == 0) && (fVar7 = (float10)FUN_0042d980(), fVar7 < (float10)490000.0)
             ) {
            param_1[0x3c] = 0xa5;
            FUN_0042db10(0,0x43340000);
          }
          fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar7 / (float10)3.1415927) * (float10)180.0 + (float10)5.0);
          param_1[0xb6] = 0x428c0000;
        }
        param_1[0x3b] = param_1[0x3b] + 1;
        if ((param_1[0x2b7d] < 2) && (0 < param_1[0x3c])) {
          fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          local_8 = (float)((fVar7 / (float10)3.1415927) * (float10)180.0);
          fVar7 = (float10)FUN_0042da80();
          fVar14 = (float)(fVar7 + (float10)10.0);
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            fVar7 = (float10)FUN_0042da80();
            local_8 = (float)(fVar7 + (float10)10.0);
          }
          if ((fVar14 < local_8) && (local_8 = local_8 - 5.0, local_8 < fVar14)) {
            local_8 = fVar14;
          }
          if ((local_8 < fVar14) && (local_8 = local_8 + 5.0, fVar14 < local_8)) {
            local_8 = fVar14;
          }
          if (30.0 < local_8) {
            local_8 = 30.0;
          }
          if (local_8 < -25.0) {
            local_8 = -25.0;
          }
          iVar6 = param_1[0x3c];
          fVar7 = (float10)FUN_0065d050(local_8);
          param_1[0x15] = (int)(float)(fVar7 * (float10)((float)iVar6 * 0.1));
          iVar6 = param_1[0x3c];
          fVar7 = (float10)FUN_0065d010(local_8);
          param_1[0x10] = (int)(float)(fVar7 * (float10)((float)iVar6 * 0.1));
          fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar7 / (float10)3.1415927) * (float10)180.0 + (float10)5.0);
          param_1[0xb6] = 0x428c0000;
          FUN_0042db10(0,0x40a00000);
          param_1[0x3c] = param_1[0x3c] + -3;
          if (param_1[0x3c] < 0x78) {
            param_1[0x3c] = 0x78;
          }
        }
        if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0,0x40000000), 7 < param_1[0x2b81])) {
          fVar7 = (float10)FUN_0042d980();
          fVar8 = (float10)FUN_0042da30();
          fVar9 = (float10)FUN_0042da30();
          if ((fVar9 * (float10)(float)fVar8 + (float10)(float)fVar7 < (float10)50000.0) ||
             ((0x19 < param_1[0x2b81] || (param_1[0x3c] == 0)))) {
            FUN_00421100(2);
            return;
          }
        }
        if (param_1[0x2b7d] == 2) {
          if (param_1[0x2b81] == 10) {
            FUN_0042c880(0x3e);
            fVar7 = (float10)FUN_0042d980();
            if ((((float10)40000.0 <= fVar7) ||
                (fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7)) ||
               (*(char *)((int)param_1 + 0xaec3) != '\x01')) {
              fVar7 = (float10)FUN_0042d980();
              if ((((float10)40000.0 <= fVar7) ||
                  (fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7)) ||
                 (*(char *)((int)param_1 + 0xaebe) != '\x01')) {
                fVar7 = (float10)FUN_0042d980();
                if ((((float10)40000.0 <= fVar7) ||
                    (fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7)) ||
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
        if (((char)param_1[0x21] == '\0') &&
           ((param_1[0x2b7d] == 2 || ((param_1[0x2b7d] == 0 && (param_1[0x2b81] < 7)))))) {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x15] = 0x41b40000;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] < 7)) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 7)) {
          param_1[0x10] = 0x40000000;
          param_1[0x16] = 0x3f000000;
          fVar7 = (float10)FUN_0042d980();
          if (((float10)40000.0 <= fVar7) ||
             ((fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7 ||
              (*(char *)((int)param_1 + 0xaec3) != '\x01')))) {
            fVar7 = (float10)FUN_0042d980();
            if (((float10)40000.0 <= fVar7) ||
               ((fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7 ||
                (*(char *)((int)param_1 + 0xaebe) != '\x01')))) {
              fVar7 = (float10)FUN_0042d980();
              if (((float10)40000.0 <= fVar7) ||
                 ((fVar7 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar7 ||
                  (*(char *)((int)param_1 + 0xaeb9) != '\x01')))) {
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
        if (param_1[0x2b7d] == 1) {
          param_1[0x10] = (int)((float)param_1[0x10] - 0.2);
          sVar2 = FUN_0042c7b0();
          if (sVar2 != 0) {
            FUN_00421080(0x14e);
            return;
          }
          if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
            param_1[0x15] = 0;
            param_1[0x10] = 0;
            param_1[0x16] = 0;
            FUN_00421100(2);
            return;
          }
          if (0x1e < param_1[0x2b81]) {
            FUN_00421080(0x153);
            return;
          }
        }
        break;
      case 0x14b:
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
          FUN_00422900();
          FUN_00423000();
          param_1[0x3c] = 0;
          param_1[0x15] = 0x41840000;
          fVar7 = (float10)FUN_0042d980();
          if (fVar7 < (float10)490000.0 != (fVar7 == (float10)490000.0)) {
            param_1[0x19] = param_1[0x18];
            param_1[0x3c] = 1;
            param_1[0x15] = 0x41a40000;
          }
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
        }
        if (param_1[0x2b7d] == 0) {
          if (param_1[0x3c] != 1) {
            FUN_00421100(1);
            return;
          }
          FUN_0042db10(0,0x41700000);
          fVar7 = (float10)FUN_0042d980();
          if ((fVar7 < (float10)160000.0) || (param_1[0x3c] == 0)) {
            FUN_00421100(1);
            return;
          }
        }
        if (param_1[0x2b7d] == 1) {
          if (param_1[0x2b81] < 0xf) {
            FUN_0042db10(0,0x40e00000);
          }
          if (param_1[0x2b81] == 0) {
            FUN_0042db10(0,0x43340000);
            param_1[0x15] = 0x41480000;
            param_1[0x18] = 0;
            FUN_0042c800(0);
            FUN_0042c840(1);
          }
          if (param_1[0x2b81] == 0xd) {
            param_1[0x15] = 0x41840000;
          }
          if (param_1[0x2b81] == 0x12) {
            FUN_004223d0(3,10,0);
          }
        }
        if (param_1[0x2b7d] == 2) {
          FUN_0042db10(0,0x41200000);
          if (param_1[0x2b81] == 0) {
            FUN_0042c880(0x3e);
          }
          if (param_1[0x2b81] == 0x14) {
            param_1[0x10] = 0;
            FUN_00421100(3);
            return;
          }
        }
        if ((param_1[0x2b7d] == 3) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        break;
      case 0x14c:
        if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b7d])) {
          FUN_00421080(0x14d);
          param_1[0x15] = 0;
          param_1[0x16] = 0;
          param_1[0x10] = 0;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if ((param_1[0x2b7d] == 0) && (FUN_0042db10(0,0x40a00000), param_1[0x2b81] == 0)) {
          param_1[0x3a] = 0;
          param_1[0x15] = 0;
          param_1[0x18] = 0;
          param_1[0x10] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if (param_1[0x2b7d] == 1) {
          param_1[0x3a] = param_1[0x3a] + 1;
          if ((param_1[0x2b81] == 0) && (param_1[0x2b81] == 0)) {
            FUN_00422490(3,0,10,0);
            fVar7 = (float10)FUN_0042da80();
            local_10 = (float)fVar7;
            if (-5.0 < local_10) {
              local_10 = -5.0;
            }
            if (local_10 < -35.0) {
              local_10 = -35.0;
            }
            fVar7 = (float10)FUN_0065d050(local_10);
            param_1[0x15] = (int)(float)(fVar7 * (float10)20.0);
            fVar7 = (float10)FUN_0065d010(local_10);
            param_1[0x10] = (int)(float)(fVar7 * (float10)20.0);
            fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
            param_1[0xb] = (int)(float)((fVar7 / (float10)3.1415927) * (float10)180.0 + (float10)5.0
                                       );
            if (0.0 < (float)param_1[0xb]) {
              param_1[0xb] = 0;
            }
            param_1[0xb6] = 0x428c0000;
          }
          sVar2 = FUN_0042c7b0();
          if (sVar2 != 0) {
            FUN_00421080(0x14e);
            return;
          }
          if (0x2d < param_1[0x3a]) {
            FUN_00421080(0x153);
            param_1[0x15] = 0x41200000;
            return;
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
      case 0x14e:
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x15] = 0;
          param_1[0x10] = 0;
          param_1[0x19] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          FUN_00423000();
        }
        param_1[0x1a1] = 2;
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0xb)) {
          FUN_004223d0(0,10,0);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0xc)) {
          param_1[0x15] = -0x3f400000;
          param_1[0x10] = 0x41200000;
        }
        if ((param_1[0x2b7d] == 1) || ((param_1[0x2b7d] == 0 && (0xc < param_1[0x2b81])))) {
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        }
        if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
          FUN_00421080(0x14d);
          param_1[0x10] = 0;
          return;
        }
        if ((param_1[0x2b7d] == 1) && (10 < param_1[0x2b81])) {
          FUN_00421080(0x2b);
          return;
        }
        break;
      case 0x153:
        if (((char)param_1[0x21] != '\0') &&
           ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0))) {
          FUN_00421080(0x14d);
          param_1[0x10] = 0;
          return;
        }
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
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
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          param_1[0x15] = 0x41700000;
          FUN_0042c840(1);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] == 8) {
          FUN_0042c880(0x3d);
          FUN_004223d0(2,10,0);
        }
        if (param_1[0x2b81] < 8) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 0) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        break;
      case 0x155:
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
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          param_1[0x15] = 0x41700000;
          FUN_0042c840(1);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] == 8) {
          FUN_0042c880(0x3d);
          FUN_004223d0(3,10,0);
        }
        if (param_1[0x2b81] < 8) {
          FUN_0042db10(0,0x41c80000);
        }
        if ((param_1[0x2b7d] == 0) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        break;
      case 0x15e:
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
          param_1[0x2bdb] = 1;
          FUN_004223d0(0x21,0x14,0);
        }
        if (param_1[0x2b81] < 0x12) {
          FUN_0042db10(0,0x41200000);
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x41700000);
          param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
        }
        if (param_1[0x2b81] == 0x11) {
          FUN_0042c8b0(0x9a);
          FUN_004230e0();
          uVar13 = 0x41f00000;
          uVar11 = 0;
          uVar10 = 0xf;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,uVar13);
        }
      }
    }
  }
  else {
    switch(iVar6) {
    case 0x169:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      FUN_00434a70(0,0);
      FUN_00434a70(1,1);
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
      break;
    default:
      goto switchD_0053bcbc_caseD_1;
    case 0x172:
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
        FUN_004223d0(0x21,0x14,0);
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x41200000);
      }
      if (param_1[0x2b7d] == 0) {
        param_1[0x15] = 0;
      }
      if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0xf)) {
        FUN_0042c8b0(0x9a);
        FUN_004230e0();
        FUN_00435000(0,0xe,0,0,0);
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
      }
      if (param_1[0x2b81] < 0x12) {
        FUN_0042dc20(0,0x41700000);
      }
      if ((param_1[0x2b7d] == 0) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.75), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x13) {
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
      }
      if (param_1[0x2b81] < 10) {
        param_1[0x2b81] = param_1[0x2b81] + 1;
        param_1[0x2b82] = param_1[0x2b82] + 1;
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
      }
      if (param_1[0x2b81] < 0x12) {
        FUN_0042dc20(0,0x41700000);
      }
      if ((param_1[0x2b7d] == 0) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x13) {
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
      }
      if (param_1[0x2b81] < 10) {
        param_1[0x2b81] = param_1[0x2b81] + 1;
        param_1[0x2b82] = param_1[0x2b82] + 1;
      }
      break;
    case 0x192:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b81])) {
        FUN_00421080(0x193);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
      }
      if (param_1[0x2b81] < 0x12) {
        FUN_0042dc20(0,0x41a00000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
      }
      if (param_1[0x2b81] == 0x13) {
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
      }
      if ((float)param_1[0x16] == 0.0) {
        param_1[0x16] = 0x3f000000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (param_1[0x2b81] < 10) {
        param_1[0x2b81] = param_1[0x2b81] + 1;
        param_1[0x2b82] = param_1[0x2b82] + 1;
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
        param_1[0x3b] = 0;
      }
      if ((0x1a < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xc) {
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 10.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 15.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 10.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 15.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
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
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41200000);
      }
      else if (param_1[0x2b81] < 0x1a) {
        FUN_0042db10(0,0x40c00000);
      }
      if ((0x1a < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = -0x3d4c0000;
        param_1[0x15] = 0x41200000;
        param_1[0x3b] = 0;
      }
      if (param_1[0x2b81] == 0xf) {
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 7.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 9.0;
          uVar11 = 0xc0a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 7.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 9.0;
          uVar11 = 0xc0a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
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
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41200000);
      }
      else if (param_1[0x2b81] < 0x1a) {
        FUN_0042db10(0,0x40c00000);
      }
      if ((0x1a < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x42b40000;
        param_1[0x15] = 0x41200000;
        param_1[0x3b] = 0;
      }
      if (param_1[0x2b81] == 0xf) {
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 7.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 9.0;
          uVar11 = 0x40a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 7.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 9.0;
          uVar11 = 0x40a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
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
        param_1[0x3b] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41100000);
      }
      if ((0x1a < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x43340000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xf) {
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0xc0a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
          fVar14 = (float)param_1[0x3c] + 5.0;
          uVar11 = 0x40a00000;
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,uVar11,fVar14);
        }
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
        FUN_0042db10(0,0x41a00000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
      }
      if ((float)param_1[0x16] == 0.0) {
        param_1[0x16] = 0x3f000000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (param_1[0x2b81] == 0xd) {
        FUN_004230e0();
        FUN_00435000(0,0,0,(float)param_1[0x3a],0);
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
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x3e] = 0;
        param_1[0x21d] = 0;
      }
      if ((param_1[0x3e] == 0) && (0x14 < param_1[0x2b81])) {
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
      if (((0x14 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
         ((param_1[0x9f] != 0 || (param_1[0x9e] != 0)))) {
        param_1[0x3e] = 0;
        param_1[0x2b7c] = 10;
        param_1[0x2b7e] = 0;
        param_1[0x2b82] = 0;
        puVar5 = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
        FUN_00421410(0,*puVar5);
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
        param_1[0x15] = 0x40a00000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0xe < param_1[0x2b81]) {
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
      if (param_1[0x2b81] == 0xf) {
        if (param_1[0x1b7] < 2) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        iVar6 = FUN_0066b668();
        param_1[0x3b] = iVar6;
        if (param_1[0x3b] < 0x29) {
          local_68 = param_1[0x3b];
        }
        else {
          local_68 = 0x28;
        }
        if (local_68 < -0x28) {
          local_6c = -0x28;
        }
        else {
          if (param_1[0x3b] < 0x29) {
            local_70 = param_1[0x3b];
          }
          else {
            local_70 = 0x28;
          }
          local_6c = local_70;
        }
        param_1[0x3b] = local_6c;
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          fVar12 = (float)param_1[0x3b];
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,fVar12,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          fVar12 = (float)param_1[0x3b];
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,fVar12,fVar14);
        }
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
        param_1[0x21d] = 0;
      }
      if ((param_1[0x3e] == 0) && (0x14 < param_1[0x2b81])) {
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
      if (((0x14 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
         ((param_1[0x9f] != 0 || (param_1[0x9e] != 0)))) {
        param_1[0x3e] = 0;
        param_1[0x2b7c] = 10;
        param_1[0x2b7e] = 0;
        param_1[0x2b82] = 0;
        puVar5 = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
        FUN_00421410(0,*puVar5);
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
        param_1[0x15] = 0x40a00000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0xe < param_1[0x2b81]) {
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
      if (param_1[0x2b81] == 0xf) {
        if (param_1[0x1b7] < 2) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        iVar6 = FUN_0066b668();
        param_1[0x3b] = iVar6;
        if (param_1[0x3b] < 0x65) {
          local_74 = param_1[0x3b];
        }
        else {
          local_74 = 100;
        }
        if (local_74 < 0x14) {
          local_78 = 0x14;
        }
        else {
          if (param_1[0x3b] < 0x65) {
            local_7c = param_1[0x3b];
          }
          else {
            local_7c = 100;
          }
          local_78 = local_7c;
        }
        param_1[0x3b] = local_78;
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          fVar12 = (float)param_1[0x3b];
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,fVar12,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          fVar12 = (float)param_1[0x3b];
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,fVar12,fVar14);
        }
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
        param_1[0x21d] = 0;
      }
      if ((param_1[0x3e] == 0) && (0x14 < param_1[0x2b81])) {
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
      if (((0x14 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
         ((param_1[0x9f] != 0 || (param_1[0x9e] != 0)))) {
        param_1[0x3e] = 0;
        param_1[0x2b7c] = 10;
        param_1[0x2b7e] = 0;
        param_1[0x2b82] = 0;
        puVar5 = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
        FUN_00421410(0,*puVar5);
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
        param_1[0x15] = 0x40a00000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0xe < param_1[0x2b81]) {
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
      if (param_1[0x2b81] == 0xf) {
        if (param_1[0x1b7] < 2) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042c8b0(0x9e);
        iVar6 = FUN_0066b668();
        param_1[0x3b] = iVar6;
        if (param_1[0x3b] < -0x13) {
          local_80 = param_1[0x3b];
        }
        else {
          local_80 = -0x14;
        }
        if (local_80 < -100) {
          local_84 = -100;
        }
        else {
          if (param_1[0x3b] < -0x13) {
            local_88 = param_1[0x3b];
          }
          else {
            local_88 = -0x14;
          }
          local_84 = local_88;
        }
        param_1[0x3b] = local_84;
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3c] = iVar6;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar14 = (float)param_1[0x3c] + 5.0;
          fVar12 = (float)param_1[0x3b];
          uVar10 = 0;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,fVar12,fVar14);
        }
        else {
          fVar14 = (float)param_1[0x3c] + 5.0;
          fVar12 = (float)param_1[0x3b];
          uVar10 = 1;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar10,fVar12,fVar14);
        }
      }
      break;
    case 0x1c2:
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
      }
      if (param_1[0x2b81] < 0x11) {
        FUN_0042dc20(0,0x41a00000);
      }
      if (0 < param_1[0x2b81]) {
        if ((0.0 < (float)param_1[0x15]) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        if (((float)param_1[0x15] < 0.0) &&
           (param_1[0x15] = (int)((float)param_1[0x15] + 1.0), 0.0 < (float)param_1[0x15])) {
          param_1[0x15] = 0;
        }
      }
      if ((-1 < param_1[0x2b81]) && (param_1[0x2b81] < 0x12)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] == 0x12) {
        if (param_1[0x3e] == 0) {
          if (param_1[0x1c8] == 1) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1d,10,0);
          }
        }
        param_1[0x18] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] - 15.0);
        FUN_0042da80();
        iVar6 = FUN_0066b668();
        param_1[0x3a] = iVar6;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_14 = (float)((fVar7 * (float10)30.0) / (float10)600.0);
        if (85.0 < local_14) {
          local_14 = 85.0;
        }
        if (local_14 < 45.0) {
          local_14 = 45.0;
        }
        local_18 = (float)param_1[0x3a] + local_14;
        if (85.0 < local_18) {
          local_18 = 85.0;
        }
        if (local_18 < 85.0) {
          local_18 = 85.0;
        }
        FUN_0042c8b0(0x82);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,2,0,local_18,0);
        }
        else {
          FUN_00435000(0,3,0,local_18,0);
        }
      }
      if ((param_1[0x2b81] == 0x29) && (param_1[0x3e] < 5)) {
        param_1[0x3e] = param_1[0x3e] + 1;
        return;
      }
      break;
    case 0x1c3:
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
      }
      if (param_1[0x2b81] < 0x11) {
        FUN_0042db10(0,0x41200000);
      }
      else if (param_1[0x2b81] < 0x1a) {
        FUN_0042db10(0,0x40800000);
      }
      if ((0x28 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if ((-1 < param_1[0x2b81]) && (param_1[0x2b81] < 0x11)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = -0x3d4c0000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0x11) {
        if (param_1[0x1c8] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1d,10,0);
        }
        param_1[0x18] = -0x3cf90000;
        param_1[0x15] = 0x41700000;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_1c = (float)((fVar7 * (float10)30.0) / (float10)600.0);
        if (85.0 < local_1c) {
          local_1c = 85.0;
        }
        if (local_1c < 20.0) {
          local_1c = 20.0;
        }
        local_20 = (float)param_1[0x3a] + local_1c;
        if (85.0 < local_20) {
          local_20 = 85.0;
        }
        if (local_20 < 85.0) {
          local_20 = 85.0;
        }
        FUN_0042c8b0(0x82);
        param_1[0x3e] = param_1[0x3e] + 1;
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,2,0,local_20,0);
        }
        else {
          FUN_00435000(0,3,0,local_20,0);
        }
      }
      break;
    case 0x1c4:
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
      }
      if ((0x28 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x42b40000;
        param_1[0x15] = 0x41200000;
      }
      if ((-1 < param_1[0x2b81]) && (param_1[0x2b81] < 0x11)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0x11) {
        if (param_1[0x1c8] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1d,10,0);
        }
        param_1[0x18] = 0x43070000;
        param_1[0x15] = 0x41700000;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_24 = (float)((fVar7 * (float10)30.0) / (float10)600.0);
        if (85.0 < local_24) {
          local_24 = 85.0;
        }
        if (local_24 < 20.0) {
          local_24 = 20.0;
        }
        local_28 = (float)param_1[0x3a] + local_24;
        if (85.0 < local_28) {
          local_28 = 85.0;
        }
        if (local_28 < 85.0) {
          local_28 = 85.0;
        }
        FUN_0042c8b0(0x82);
        param_1[0x3e] = param_1[0x3e] + 1;
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,2,0,local_28,0);
        }
        else {
          FUN_00435000(0,3,0,local_28,0);
        }
      }
      break;
    case 0x1c5:
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
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x41100000);
      }
      if ((0x25 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if ((-1 < param_1[0x2b81]) && (param_1[0x2b81] < 0x14)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x43340000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0x14) {
        if (param_1[0x1c8] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1d,10,0);
        }
        param_1[0x15] = 0x41700000;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_2c = (float)((fVar7 * (float10)30.0) / (float10)600.0);
        if (85.0 < local_2c) {
          local_2c = 85.0;
        }
        if (local_2c < 20.0) {
          local_2c = 20.0;
        }
        local_30 = (float)param_1[0x3a] + local_2c;
        if (85.0 < local_30) {
          local_30 = 85.0;
        }
        if (local_30 < 85.0) {
          local_30 = 85.0;
        }
        FUN_0042c8b0(0x82);
        param_1[0x3e] = param_1[0x3e] + 1;
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,2,0,local_30,0);
        }
        else {
          FUN_00435000(0,3,0,local_30,0);
        }
      }
      break;
    case 0x1c6:
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
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41100000);
      }
      if ((0x25 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] + 0.5), 0.0 < (float)param_1[0x15])) {
        param_1[0x15] = 0;
      }
      if ((-1 < param_1[0x2b81]) && (param_1[0x2b81] < 0x11)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x11) {
        if (param_1[0x1c8] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1d,10,0);
        }
        param_1[0x15] = -0x3ee00000;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_34 = (float)((fVar7 * (float10)30.0) / (float10)600.0);
        if (85.0 < local_34) {
          local_34 = 85.0;
        }
        if (local_34 < 20.0) {
          local_34 = 20.0;
        }
        local_38 = (float)param_1[0x3a] + local_34;
        if (85.0 < local_38) {
          local_38 = 85.0;
        }
        if (local_38 < 85.0) {
          local_38 = 85.0;
        }
        FUN_0042c8b0(0x82);
        param_1[0x3e] = param_1[0x3e] + 1;
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,2,0,local_38,0);
        }
        else {
          FUN_00435000(0,3,0,local_38,0);
        }
      }
      break;
    case 0x1cc:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        FUN_00421080(0x1d5);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        param_1[0x16] = 0;
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042dc20(0,0x41700000);
      }
      if ((-1 < param_1[0x2b81]) && (param_1[0x2b81] < 0x11)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0x11) {
        FUN_004223d0(0x1d,10,0);
        param_1[0x18] = 0;
        param_1[0x15] = -0x3f600000;
        param_1[0x10] = 0x40a00000;
        param_1[0x16] = 0x3f000000;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_3c = (float)((fVar7 * (float10)30.0) / (float10)600.0);
        if (85.0 < local_3c) {
          local_3c = 85.0;
        }
        if (local_3c < 20.0) {
          local_3c = 20.0;
        }
        local_40 = (float)param_1[0x3a] + local_3c;
        if (85.0 < local_40) {
          local_40 = 85.0;
        }
        if (local_40 < 85.0) {
          local_40 = 85.0;
        }
        FUN_0042c8b0(0x82);
        param_1[0x3e] = param_1[0x3e] + 1;
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,2,0,local_40,0);
        }
        else {
          FUN_00435000(0,3,0,local_40,0);
        }
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if ((param_1[0x2b81] == 0x29) && (param_1[0x3e] < 0x14)) {
        param_1[0x3e] = param_1[0x3e] + 1;
        return;
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

