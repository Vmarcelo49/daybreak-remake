// ============================================
// Address:  0x00531ce0
// Original: FUN_00531ce0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00531ce0(int *param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
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
  iVar4 = param_1[0x2b7b];
  if (iVar4 < 0x169) {
    if (iVar4 == 0x168) {
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) &&
         (0x1e < param_1[0x2b81])) {
        FUN_00421080(0x1d5);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        param_1[0x3d] = 0;
        param_1[0x3e] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] * 0.25);
        param_1[0x10] = 0;
        FUN_004223d0(0x20,0x14,0);
      }
      if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x1e)) {
        FUN_00434a70(1,0xffffffff);
        FUN_00434a70(0,2);
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042dc20(0,0x41500000);
      }
      if (param_1[0x2b81] < 0x1e) {
        FUN_0042db10(0,0x40000000);
      }
      if (param_1[0x2b81] == 0x1e) {
        param_1[0x3d] = param_1[0x3d] + 1;
        param_1[0x18] = 0;
        param_1[0x15] = -0x3ee00000;
        param_1[0x10] = 0x40a00000;
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x81);
        FUN_004230e0();
        FUN_00434fd0(8,0,(float)param_1[0x3a],0);
      }
      param_1[0x16] = 0x3f000000;
      param_1[0x10] = (int)((float)param_1[0x10] - 0.15);
      if (param_1[0x2b81] == 0x1d) {
        if (param_1[0x3e] < 0) {
          param_1[0x3e] = param_1[0x3e] + 1;
          return;
        }
        param_1[0x3e] = 0;
      }
    }
    else if (iVar4 < 0x12e) {
      if (iVar4 == 0x12d) {
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
            FUN_0042db10(0,0x41a00000);
          }
          if ((0x10 < param_1[0x2b81]) && (param_1[0x2b81] < 0x1c)) {
            FUN_0042db10(0,0x41700000);
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
      else if (iVar4 < 0x1f) {
        if (iVar4 == 0x1e) {
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            param_1[0x16] = 0x3f000000;
            FUN_00421080(0x2b);
            return;
          }
          if (param_1[0x2b7d] < 3) {
            param_1[0x20d] = param_1[0x20d] + -7;
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
          switch(iVar4) {
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
            goto switchD_00531d8c_caseD_1;
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
            param_1[0x15] = 0x40d80000;
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
            if (param_1[0x2b81] % 10 == 0) {
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
            if (param_1[0x2b81] % 10 == 0) {
              param_1[0x2b81] = param_1[0x2b81] + 1;
              param_1[0x2b82] = param_1[0x2b82] + 1;
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
        if (300 < iVar4) {
switchD_00531d8c_caseD_1:
          FUN_00428510();
          return;
        }
        if (iVar4 == 300) {
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
            param_1[0x15] = 0x41680000;
            fVar7 = (float10)FUN_0042d980();
            if (fVar7 < (float10)640000.0) {
              param_1[0x3c] = 1;
              param_1[0x15] = 0x41b40000;
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
            FUN_0042db10(0,0x41700000);
          }
          if (param_1[0x2b7d] == 1) {
            if (param_1[0x3c] == 1) {
              FUN_0042db10(0,0x41900000);
            }
            fVar7 = (float10)FUN_0042d980();
            if ((fVar7 < (float10)90000.0) || (param_1[0x3c] == 0)) {
              FUN_00421100(2);
              return;
            }
          }
          if (param_1[0x2b7d] == 2) {
            if (param_1[0x2b81] < 0xc) {
              FUN_0042db10(0,0x41200000);
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
          switch(iVar4) {
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
            goto switchD_00531d8c_caseD_1;
          }
        }
      }
    }
    else {
      switch(iVar4) {
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
          param_1[0x15] = 0x41b40000;
          FUN_0042db10(0,0x43340000);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x41700000);
        }
        if (param_1[0x2b7d] == 1) {
          FUN_0042db10(0,0x41700000);
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
           ((param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0 ||
            (param_1[0x2b81] == 0xf)))) {
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
        if (param_1[0x2b81] == 9) {
          param_1[0x2b81] = 0xd;
          param_1[0x2b82] = 0xd;
          param_1[0x15] = 0x420c0000;
          FUN_0042c880(0x3c);
          FUN_004223d0(2,10,0);
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
        goto switchD_00531d8c_caseD_1;
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
          param_1[0x15] = 0x41400000;
          if ((param_1[0x2b81] == 0) && (fVar7 = (float10)FUN_0042d980(), fVar7 < (float10)1e+06)) {
            param_1[0x3c] = 0xdc;
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
          fVar13 = (float)(fVar7 + (float10)10.0);
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            fVar7 = (float10)FUN_0042da80();
            local_8 = (float)(fVar7 + (float10)10.0);
          }
          if ((fVar13 < local_8) && (local_8 = local_8 - 5.0, local_8 < fVar13)) {
            local_8 = fVar13;
          }
          if ((local_8 < fVar13) && (local_8 = local_8 + 5.0, fVar13 < local_8)) {
            local_8 = fVar13;
          }
          if (30.0 < local_8) {
            local_8 = 30.0;
          }
          if (local_8 < -25.0) {
            local_8 = -25.0;
          }
          iVar4 = param_1[0x3c];
          fVar7 = (float10)FUN_0065d050(local_8);
          param_1[0x15] = (int)(float)(fVar7 * (float10)((float)iVar4 * 0.1));
          iVar4 = param_1[0x3c];
          fVar7 = (float10)FUN_0065d010(local_8);
          param_1[0x10] = (int)(float)(fVar7 * (float10)((float)iVar4 * 0.1));
          fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar7 / (float10)3.1415927) * (float10)180.0 + (float10)5.0);
          param_1[0xb6] = 0x428c0000;
          FUN_0042db10(0,0x40a00000);
          param_1[0x3c] = param_1[0x3c] + -4;
          if (param_1[0x3c] < 0x96) {
            param_1[0x3c] = 0x96;
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
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] < 7)) {
          FUN_0042db10(0,0x41700000);
          param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x40a00000);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 6)) {
          param_1[0x15] = 0x41dc0000;
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
          if (fVar7 < (float10)640000.0 != (fVar7 == (float10)640000.0)) {
            param_1[0x19] = param_1[0x18];
            param_1[0x3c] = 1;
            param_1[0x15] = 0x41b40000;
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
          FUN_0042db10(0,0x41a00000);
          fVar7 = (float10)FUN_0042d980();
          if ((fVar7 < (float10)160000.0) || (param_1[0x3c] == 0)) {
            FUN_00421100(1);
            return;
          }
        }
        if (param_1[0x2b7d] == 1) {
          if (param_1[0x2b81] < 0xf) {
            FUN_0042db10(0,0x41200000);
          }
          if (param_1[0x2b81] == 0) {
            FUN_0042db10(0,0x43340000);
            param_1[0x15] = 0x41480000;
            param_1[0x18] = 0;
            FUN_0042c800(0);
            FUN_0042c840(1);
            param_1[0x2b81] = 5;
            param_1[0x2b82] = 5;
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
          param_1[0x3a] = 0;
          param_1[0x15] = 0;
          param_1[0x18] = 0;
          param_1[0x10] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x2b81] = 6;
          param_1[0x2b82] = 6;
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x40a00000);
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
            param_1[0x15] = (int)(float)(fVar7 * (float10)25.0);
            fVar7 = (float10)FUN_0065d010(local_10);
            param_1[0x10] = (int)(float)(fVar7 * (float10)25.0);
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
          if (0x1e < param_1[0x3a]) {
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
        if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x1e)) {
          FUN_00434a70(1,0xffffffff);
          FUN_00434a70(0,2);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
        }
        if (param_1[0x2b81] < 0xf) {
          FUN_0042db10(0,0x41800000);
        }
        if (param_1[0x2b81] < 0x1e) {
          FUN_0042db10(0,0x40800000);
        }
        if ((0x11 < param_1[0x2b81]) &&
           (param_1[0x15] = (int)((float)param_1[0x15] + 0.35), 0.0 < (float)param_1[0x15])) {
          param_1[0x15] = 0;
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          param_1[0x15] = 0;
          param_1[0x3d] = 0;
          param_1[0x3e] = 0;
          FUN_004223d0(0x20,0x14,0);
        }
        if (param_1[0x2b81] == 0x1e) {
          param_1[0x18] = 0;
          param_1[0x15] = -0x3e900000;
          FUN_0042da80();
          iVar4 = FUN_0066b668();
          param_1[0x3a] = iVar4;
          if (param_1[0x3a] < -0x28) {
            param_1[0x3a] = -0x28;
          }
          if (0x28 < param_1[0x3a]) {
            param_1[0x3a] = 0x28;
          }
          FUN_0042c8b0(0x81);
          FUN_004230e0();
          FUN_00434fd0(8,0,(float)param_1[0x3a],0);
          param_1[0x3d] = param_1[0x3d] + 1;
        }
        if (param_1[0x2b81] == 0x1d) {
          if (param_1[0x3e] < 0) {
            param_1[0x3e] = param_1[0x3e] + 1;
            return;
          }
          param_1[0x3e] = 0;
        }
      }
    }
  }
  else {
    switch(iVar4) {
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
      goto switchD_00531d8c_caseD_1;
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
        FUN_00435000(0,10,0,0,0);
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
        FUN_0042db10(0,0x41200000);
      }
      if (param_1[0x2b7d] == 0) {
        FUN_0042db10(0,0x41700000);
        param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      if (((param_1[0x2b81] == 0xc) || (param_1[0x2b81] == 0xf)) || (param_1[0x2b81] == 0x12)) {
        if (param_1[0x2b81] == 0xc) {
          if (param_1[0x1b7] < 4) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
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
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x41a00000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x43340000;
        param_1[0x15] = 0x40a00000;
      }
      if (param_1[0x2b81] == 0xf) {
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x80);
        FUN_00435000(0,0,0,(float)param_1[0x3a],0);
        FUN_00435000(1,0,0,(float)param_1[0x3a],0);
      }
      if ((((0x1d < param_1[0x2b81]) && (1 < param_1[0x1b7])) && (0 < param_1[0xae])) &&
         (param_1[0xae] < 10)) {
        if (0 < param_1[0x9e]) {
          FUN_00421080(0x19b);
          return;
        }
        if (param_1[0x9e] < 0) {
          FUN_00421080(0x19c);
          return;
        }
        if (param_1[0x9f] < 0) {
          FUN_00421080(0x19a);
          return;
        }
        if (0 < param_1[0x9f]) {
          FUN_00421080(0x191);
          return;
        }
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
      if (((param_1[0x2b81] == 0xc) || (param_1[0x2b81] == 0xf)) || (param_1[0x2b81] == 0x12)) {
        if (param_1[0x2b81] == 0xc) {
          if (param_1[0x1b7] < 4) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
      }
      if ((float)param_1[0x16] == 0.0) {
        param_1[0x16] = 0x3f000000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
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
      if ((((param_1[0x2b81] + param_1[0x3b] == 0xf) || (param_1[0x2b81] + param_1[0x3b] == 0x14))
          || (param_1[0x2b81] + param_1[0x3b] == 0x19)) || (param_1[0x2b81] + param_1[0x3b] == 0x1e)
         ) {
        if (param_1[0x2b81] == 0xf) {
          if (param_1[0x1b7] < 5) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1c,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
      }
      if ((param_1[0x2b81] == 0x12) && (param_1[0x3b] = param_1[0x3b] + 1, param_1[0x3b] < 0x14)) {
        param_1[0x2b81] = param_1[0x2b81] + -1;
        param_1[0x2b82] = param_1[0x2b82] + -1;
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
      if ((((param_1[0x2b81] + param_1[0x3b] == 0xf) || (param_1[0x2b81] + param_1[0x3b] == 0x14))
          || (param_1[0x2b81] + param_1[0x3b] == 0x19)) || (param_1[0x2b81] + param_1[0x3b] == 0x1e)
         ) {
        if (param_1[0x2b81] == 0xf) {
          if (param_1[0x1b7] < 5) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1c,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
      }
      if ((param_1[0x2b81] == 0x12) && (param_1[0x3b] = param_1[0x3b] + 1, param_1[0x3b] < 0x14)) {
        param_1[0x2b81] = param_1[0x2b81] + -1;
        param_1[0x2b82] = param_1[0x2b82] + -1;
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
      if ((((param_1[0x2b81] + param_1[0x3b] == 0xf) || (param_1[0x2b81] + param_1[0x3b] == 0x14))
          || (param_1[0x2b81] + param_1[0x3b] == 0x19)) || (param_1[0x2b81] + param_1[0x3b] == 0x1e)
         ) {
        if (param_1[0x2b81] == 0xf) {
          if (param_1[0x1b7] < 5) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1c,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
      }
      if ((param_1[0x2b81] == 0x12) && (param_1[0x3b] = param_1[0x3b] + 1, param_1[0x3b] < 0x14)) {
        param_1[0x2b81] = param_1[0x2b81] + -1;
        param_1[0x2b82] = param_1[0x2b82] + -1;
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
      if ((((param_1[0x2b81] + param_1[0x3b] == 0xf) || (param_1[0x2b81] + param_1[0x3b] == 0x14))
          || (param_1[0x2b81] + param_1[0x3b] == 0x19)) || (param_1[0x2b81] + param_1[0x3b] == 0x1e)
         ) {
        if (param_1[0x2b81] == 0xf) {
          if (param_1[0x1b7] < 5) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1c,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar11 = 0;
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,uVar11,fVar13);
        }
      }
      if ((param_1[0x2b81] == 0x12) && (param_1[0x3b] = param_1[0x3b] + 1, param_1[0x3b] < 0x14)) {
        param_1[0x2b81] = param_1[0x2b81] + -1;
        param_1[0x2b82] = param_1[0x2b82] + -1;
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
        param_1[0x15] = 0x40d80000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0x14 < param_1[0x2b81]) {
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
      if (((param_1[0x2b81] == 0xd) || (param_1[0x2b81] == 0x11)) || (param_1[0x2b81] == 0x15)) {
        if (param_1[0x2b81] == 0xd) {
          if (param_1[0x1b7] < 4) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        iVar4 = FUN_0066b668();
        param_1[0x3b] = iVar4;
        if (param_1[0x3b] < 0x29) {
          local_38 = param_1[0x3b];
        }
        else {
          local_38 = 0x28;
        }
        if (local_38 < -0x28) {
          local_3c = -0x28;
        }
        else {
          if (param_1[0x3b] < 0x29) {
            local_40 = param_1[0x3b];
          }
          else {
            local_40 = 0x28;
          }
          local_3c = local_40;
        }
        param_1[0x3b] = local_3c;
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          fVar12 = (float)param_1[0x3b];
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,fVar12,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          fVar12 = (float)param_1[0x3b];
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,fVar12,fVar13);
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
        param_1[0x15] = 0x40d80000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0x14 < param_1[0x2b81]) {
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
      if (((param_1[0x2b81] == 0xd) || (param_1[0x2b81] == 0x11)) || (param_1[0x2b81] == 0x15)) {
        if (param_1[0x2b81] == 0xd) {
          if (param_1[0x1b7] < 4) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        iVar4 = FUN_0066b668();
        param_1[0x3b] = iVar4;
        if (param_1[0x3b] < 0x65) {
          local_44 = param_1[0x3b];
        }
        else {
          local_44 = 100;
        }
        if (local_44 < 0x14) {
          local_48 = 0x14;
        }
        else {
          if (param_1[0x3b] < 0x65) {
            local_4c = param_1[0x3b];
          }
          else {
            local_4c = 100;
          }
          local_48 = local_4c;
        }
        param_1[0x3b] = local_48;
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          fVar12 = (float)param_1[0x3b];
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,fVar12,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          fVar12 = (float)param_1[0x3b];
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,fVar12,fVar13);
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
        param_1[0x15] = 0x40d80000;
      }
      if (param_1[0x3e] == 1) {
        param_1[0x15] = 0;
      }
      if (0x14 < param_1[0x2b81]) {
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
      if (((param_1[0x2b81] == 0xd) || (param_1[0x2b81] == 0x11)) || (param_1[0x2b81] == 0x15)) {
        if (param_1[0x2b81] == 0xd) {
          if (param_1[0x1b7] < 4) {
            FUN_004223d0(0x1e,10,0);
          }
          else {
            FUN_004223d0(0x1b,10,0);
          }
        }
        FUN_0042c8b0(0x80);
        iVar4 = FUN_0066b668();
        param_1[0x3b] = iVar4;
        if (param_1[0x3b] < -0x13) {
          local_50 = param_1[0x3b];
        }
        else {
          local_50 = -0x14;
        }
        if (local_50 < -100) {
          local_54 = -100;
        }
        else {
          if (param_1[0x3b] < -0x13) {
            local_58 = param_1[0x3b];
          }
          else {
            local_58 = -0x14;
          }
          local_54 = local_58;
        }
        param_1[0x3b] = local_54;
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          fVar12 = (float)param_1[0x3b];
          uVar10 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,fVar12,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          fVar12 = (float)param_1[0x3b];
          uVar10 = 6;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar10,fVar12,fVar13);
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
        FUN_0042db10(0,0x41a00000);
      }
      if ((0x14 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] + 0.35), 0.0 < (float)param_1[0x15])) {
        param_1[0x15] = 0;
      }
      if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x12)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x12) {
        if (param_1[0x1c8] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1d,10,0);
        }
        param_1[0x18] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] - 15.0);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x81);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,0,(float)param_1[0x3a],0);
        }
        else {
          FUN_00435000(0,7,0,(float)param_1[0x3a],0);
        }
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
      if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x11)) {
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
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x81);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,0,(float)param_1[0x3a],0);
        }
        else {
          FUN_00435000(0,7,0,(float)param_1[0x3a],0);
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
      if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x11)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x42b40000;
        param_1[0x15] = 0x41200000;
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
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x81);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,0,(float)param_1[0x3a],0);
        }
        else {
          FUN_00435000(0,7,0,(float)param_1[0x3a],0);
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
      if ((9 < param_1[0x2b81]) && (param_1[0x2b81] < 0x14)) {
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
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x81);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,0,(float)param_1[0x3a],0);
        }
        else {
          FUN_00435000(0,7,0,(float)param_1[0x3a],0);
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
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x81);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,0,(float)param_1[0x3a],0);
        }
        else {
          FUN_00435000(0,7,0,(float)param_1[0x3a],0);
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
      }
      if ((-1 < param_1[0x2b81]) && (param_1[0x2b81] < 0x11)) {
        FUN_00434a70(1,2);
        FUN_00434a70(0,0xffffffff);
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042dc20(0,0x41700000);
      }
      if (param_1[0x2b81] == 0x11) {
        FUN_004223d0(0x1d,10,0);
        param_1[0x18] = 0;
        param_1[0x15] = -0x3ee00000;
        param_1[0x10] = 0x40a00000;
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3a] = iVar4;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        FUN_0042c8b0(0x81);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,0,(float)param_1[0x3a],0);
        }
        else {
          FUN_00435000(0,7,0,(float)param_1[0x3a],0);
        }
      }
      param_1[0x16] = 0x3f000000;
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
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

