// ============================================
// Address:  0x00473610
// Original: FUN_00473610
// Status:   unreviewed
// ============================================


void __fastcall FUN_00473610(int *param_1)

{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  int local_2c;
  int local_28;
  float local_24;
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
  iVar5 = param_1[0x2b7b];
  if (iVar5 < 0x14f) {
    if (iVar5 == 0x14e) {
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
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    }
    else if (iVar5 < 0x2d) {
      if (iVar5 == 0x2c) {
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
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
          goto switchD_004736a5_caseD_1;
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
          param_1[0x15] = 0x40e00000;
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
          cVar2 = FUN_004218c0();
          if (cVar2 != '\0') {
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
          if ((param_1[0x2b7d] < 2) && (param_1[0x20d] = param_1[0x20d] + -10, param_1[0x20d] < 0))
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
            param_1[0x15] = 0x41700000;
            param_1[0x3a] = 0;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x21d] = 0x40800000;
            param_1[0x15] = 0x41700000;
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
            if ((param_1[0x2b81] == 1) && (param_1[0x3a] < 0xf)) {
              param_1[0x3a] = param_1[0x3a] + 1;
              return;
            }
          }
          break;
        case 0x17:
          cVar2 = FUN_004218c0();
          if (cVar2 != '\0') {
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
            param_1[0x2bd2] = param_1[0x2bd2] + 1;
            param_1[0x19] = 0;
            param_1[0x18] = -0x3d4c0000;
            param_1[0x15] = 0x41a00000;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x18] = -0x3d4c0000;
          }
          if ((param_1[0x2b7d] < 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 13.0)) {
            param_1[0x15] = 0x41500000;
          }
          if (param_1[0x2b7d] == 2) {
            if ((char)param_1[0x21] == '\0') {
              param_1[0x16] = 0x3f000000;
              FUN_00421080(0x2b);
              return;
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.95);
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
          cVar2 = FUN_004218c0();
          if (cVar2 != '\0') {
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
            param_1[0x2bd2] = param_1[0x2bd2] + 1;
            param_1[0x19] = 0;
            param_1[0x18] = 0x42b40000;
            param_1[0x15] = 0x41a00000;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x18] = 0x42b40000;
          }
          if ((param_1[0x2b7d] < 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 13.0)) {
            param_1[0x15] = 0x41500000;
          }
          if ((param_1[0x2b7d] == 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.95), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
          if (param_1[0x2b81] % 10 == 0) {
            param_1[0x2b81] = param_1[0x2b81] + 1;
            param_1[0x2b82] = param_1[0x2b82] + 1;
          }
          break;
        case 0x1b:
        case 0x1c:
          cVar2 = FUN_004218c0();
          if (cVar2 != '\0') {
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
            param_1[0x2bd2] = param_1[0x2bd2] + 1;
            param_1[0x19] = 0;
            param_1[0x18] = 0x43340000;
            param_1[0x15] = 0x41680000;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x21d] = 0;
            param_1[0x15] = 0x41680000;
            param_1[0x18] = 0x43340000;
          }
          if ((param_1[0x2b7d] == 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 1.25), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
          break;
        case 0x1e:
          cVar2 = FUN_004218c0();
          if (cVar2 != '\0') {
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
          cVar2 = FUN_004218c0();
          if (cVar2 != '\0') {
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
        }
      }
    }
    else {
      switch(iVar5) {
      case 300:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          return;
        }
        if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x3b] = 0;
          param_1[0x3c] = 1;
          param_1[0x15] = 0x41780000;
          FUN_0042db10(0,0x43340000);
          fVar7 = (float10)FUN_0042d980();
          if ((float10)640000.0 <= fVar7) {
            param_1[0x3a] = 1;
          }
          else {
            param_1[0x3a] = 1;
            param_1[0x15] = 0x41cc0000;
          }
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        sVar3 = FUN_0042c7b0();
        if ((sVar3 != 0) && (param_1[0x3b] == 0)) {
          param_1[0x3b] = 1;
        }
        if (param_1[0x2b7d] < 2) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] < 4)) {
          FUN_0042db10(0,0x41200000);
        }
        if ((param_1[0x2b7d] == 1) &&
           (((fVar7 = (float10)FUN_0042d980(), fVar7 < (float10)90000.0 || (param_1[0x3a] == 0)) ||
            (10 < param_1[0x2b81])))) {
          FUN_00421100(2);
          return;
        }
        if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 4)) {
          FUN_0042c880(0x3c);
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
        if ((param_1[0x2b7d] == 2) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 1.5), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        if (((param_1[0x2b7d] == 2) && (1 < param_1[0x2b81])) && (param_1[0x2b81] < 10)) {
          FUN_00434b30();
        }
        else {
          FUN_00434bd0();
        }
        break;
      case 0x12d:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          return;
        }
        if ((param_1[0x3b] != 0) && (param_1[0x1a1] = 2, param_1[0x2b81] < 8)) {
          FUN_0042db10(0,0x41a00000);
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] == 8) {
          FUN_0042c880(0x3d);
          FUN_004223d0(2,10,0);
        }
        if (param_1[0x2b81] == 1) {
          param_1[0x15] = 0x41400000;
          param_1[0x21d] = 0;
        }
        if (param_1[0x2b81] == 0xf) {
          param_1[0x15] = 0;
          param_1[0x21d] = 0;
        }
        if ((param_1[0x2b81] < 8) || (0xe < param_1[0x2b81])) {
          FUN_00434bd0();
        }
        else {
          FUN_00434b30();
        }
        break;
      case 0x12e:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          return;
        }
        if ((param_1[0x3b] != 0) && (param_1[0x1a1] = 2, param_1[0x2b81] < 10)) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] == 10) {
          FUN_0042c880(0x3e);
          FUN_004223d0(3,10,0);
        }
        if (param_1[0x2b81] == 2) {
          param_1[0x15] = 0x41200000;
          param_1[0x21d] = 0;
        }
        if (param_1[0x2b81] == 0xf) {
          param_1[0x15] = 0;
          param_1[0x21d] = 0;
        }
        if ((param_1[0x2b81] < 0xc) || (0x11 < param_1[0x2b81])) {
          FUN_00434bd0();
        }
        else {
          FUN_00434b30();
        }
        break;
      default:
switchD_004736a5_caseD_1:
        FUN_00428510();
        return;
      case 0x136:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          FUN_0042db10(0,0x43340000);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x41a00000);
          param_1[0x15] = 0x41c80000;
        }
        if (param_1[0x2b7d] == 1) {
          FUN_0042db10(0,0x41a00000);
          param_1[0x21d] = 0;
          fVar7 = (float10)FUN_0042d980();
          if ((fVar7 < (float10)90000.0) || (6 < param_1[0x2b81])) {
            FUN_00421100(2);
            return;
          }
        }
        if (param_1[0x2b7d] == 2) {
          if (param_1[0x2b81] < 6) {
            FUN_0042db10(0,0x41700000);
          }
          if (param_1[0x2b81] == 5) {
            param_1[0x15] = 0;
          }
          if (param_1[0x2b81] == 4) {
            FUN_004223d0(2,10,0);
            FUN_0042c8b0(0x3e);
          }
          if (((0xc < param_1[0x2b81]) && (uVar4 = FUN_0042c7b0(), (uVar4 & 1) != 0)) &&
             (param_1[0xa0] != 0)) {
            FUN_00421080(0x28);
            return;
          }
        }
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        break;
      case 0x137:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          return;
        }
        if (param_1[0x2b7d] == 0) {
          param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
          if (param_1[0x2b81] < 0xe) {
            FUN_0042db10(0,0x41700000);
          }
          if (param_1[0x2b81] < 0x20) {
            FUN_0042db10(0,0x41200000);
          }
        }
        if (param_1[0x2b81] == 0) {
          FUN_0042c800(0);
          FUN_0042c840(1);
          FUN_00422900();
          FUN_00423000();
        }
        if (param_1[0x2b81] == 0x13) {
          FUN_0042c880(0x3e);
          FUN_004223d0(3,10,0);
        }
        if (param_1[0x2b81] == 0xe) {
          param_1[0x18] = 0;
          param_1[0x15] = 0x41f00000;
        }
        if (param_1[0x2b81] == 0x20) {
          param_1[0x15] = 0;
        }
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if ((param_1[0x2b81] < 0x10) || (0x1d < param_1[0x2b81])) {
          FUN_00434bd0();
        }
        else {
          FUN_00434b30();
        }
        break;
      case 0x140:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0x2b);
          param_1[0xb] = 0;
          return;
        }
        if ((float)param_1[0x16] == 0.0) {
          param_1[0x16] = 0x3f000000;
        }
        if ((param_1[0x2b7d] == 2) && (10 < param_1[0x2b81])) {
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        }
        if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) && (10 < param_1[0x2b81])) {
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
            local_24 = (float)param_1[0x10];
          }
          else {
            local_24 = 3.0;
          }
          if (-3.0 <= local_24) {
            if ((float)param_1[0x10] <= 3.0) {
              local_2c = param_1[0x10];
            }
            else {
              local_2c = 0x40400000;
            }
            local_28 = local_2c;
          }
          else {
            local_28 = -0x3fc00000;
          }
          param_1[0x10] = local_28;
          param_1[0x15] = 0x41380000;
          fVar7 = (float10)FUN_0042d980();
          if (fVar7 < (float10)810000.0) {
            param_1[0x3c] = 0xe1;
            FUN_0042db10(0,0x43340000);
          }
          fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar7 / (float10)3.1415927) * (float10)180.0 + (float10)20.0)
          ;
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
          if (55.0 < local_8) {
            local_8 = 55.0;
          }
          if (local_8 < -30.0) {
            local_8 = -30.0;
          }
          iVar5 = param_1[0x3c];
          fVar7 = (float10)FUN_0065d050(local_8);
          param_1[0x15] = (int)(float)(fVar7 * (float10)((float)iVar5 * 0.1));
          iVar5 = param_1[0x3c];
          fVar7 = (float10)FUN_0065d010(local_8);
          param_1[0x10] = (int)(float)(fVar7 * (float10)((float)iVar5 * 0.1));
          fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar7 / (float10)3.1415927) * (float10)180.0 + (float10)20.0)
          ;
          param_1[0xb6] = 0x428c0000;
          FUN_0042db10(0,0x40800000);
          param_1[0x3c] = param_1[0x3c] + -4;
          if (param_1[0x3c] < 0x8c) {
            param_1[0x3c] = 0x8c;
          }
        }
        if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0,0x40400000), 10 < param_1[0x2b81])) {
          fVar7 = (float10)FUN_0042d980();
          fVar8 = (float10)FUN_0042da30();
          fVar9 = (float10)FUN_0042da30();
          if ((fVar9 * (float10)(float)fVar8 + (float10)(float)fVar7 < (float10)40000.0) ||
             ((0x14 < param_1[0x2b81] || (param_1[0x3c] == 0)))) {
            FUN_00421100(2);
            return;
          }
        }
        if (param_1[0x2b7d] == 2) {
          if (param_1[0x2b81] == 0) {
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
        if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] < 8)) {
          FUN_00434b30();
        }
        else {
          FUN_00434bd0();
        }
        break;
      case 0x149:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
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
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0);
          return;
        }
        if ((char)param_1[0x21] == '\0') {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if (param_1[0x2b7d] == 0) {
          if (param_1[0x2b81] == 0) {
            param_1[0x18] = 0;
            FUN_0042c800(0);
            FUN_0042c840(1);
            param_1[0x3a] = 0;
            FUN_00422900();
            FUN_00423000();
          }
          if ((param_1[0x2b81] < 0xb) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
          if (param_1[0x2b81] == 0xb) {
            param_1[0x15] = 0x41f00000;
          }
        }
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b7d] == 1) {
          fVar7 = (float10)FUN_0042d980();
          if (fVar7 < (float10)40000.0) {
            param_1[0x3a] = 10;
          }
          if ((5 < param_1[0x2b81]) || (fVar7 = (float10)FUN_0042d980(), fVar7 < (float10)40000.0))
          {
            FUN_00421100(2);
            return;
          }
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0,0x40400000), param_1[0x2b81] == 0)) {
          FUN_0042c880(0x3e);
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
        if ((param_1[0x2b7d] == 2) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 3.0), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        break;
      case 0x14b:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
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
          param_1[0x15] = 0x41800000;
          fVar7 = (float10)FUN_0042d980();
          if ((float10)810000.0 <= fVar7) {
            param_1[0x3c] = 0;
          }
          else {
            param_1[0x3c] = 1;
            param_1[0x15] = 0x41b00000;
          }
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
        }
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x41a00000);
        }
        if (param_1[0x2b7d] == 1) {
          if (param_1[0x3c] == 1) {
            FUN_0042db10(0,0x41a00000);
          }
          if ((5 < param_1[0x2b81]) &&
             (((fVar7 = (float10)FUN_0042d980(), fVar7 < (float10)90000.0 || (10 < param_1[0x2b81]))
              || (param_1[0x3c] == 0)))) {
            FUN_00421100(2);
            return;
          }
        }
        if (param_1[0x2b7d] == 2) {
          param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
          if ((param_1[0x2b81] < 7) && (param_1[0x3c] == 1)) {
            FUN_0042db10(0,0x40000000);
          }
          if (param_1[0x2b81] == 6) {
            FUN_004223d0(3,10,0);
            FUN_0042c8b0(0x3f);
          }
          if (param_1[0x2b81] == 0x14) {
            param_1[0x15] = 0;
          }
          if ((param_1[0x2b81] < 3) || (0x13 < param_1[0x2b81])) {
            FUN_00434bd0();
          }
          else {
            FUN_00434b30();
          }
        }
        break;
      case 0x14c:
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
          FUN_00421080(0x2b);
          param_1[0xb] = 0;
          return;
        }
        if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b7d])) {
          FUN_00421080(0x14d);
          param_1[0xb] = 0;
          param_1[0x15] = 0;
          param_1[0x10] = 0;
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
          iVar5 = FUN_0066b65c((float)param_1[0x19] < 90.0);
          if (iVar5 != 0) {
            FUN_0042db10(0,0x3f800000);
          }
          if (param_1[0x2b81] == 0) {
            FUN_00422490(3,0,10,0);
            fVar7 = (float10)FUN_0042da80();
            local_10 = (float)fVar7;
            if (-5.0 < local_10) {
              local_10 = -5.0;
            }
            if (local_10 < -20.0) {
              local_10 = -20.0;
            }
            fVar7 = (float10)FUN_0065d050(local_10);
            param_1[0x15] = (int)(float)(fVar7 * (float10)25.0);
            fVar7 = (float10)FUN_0065d010(local_10);
            param_1[0x10] = (int)(float)(fVar7 * (float10)25.0);
            fVar7 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
            param_1[0xb] = (int)(float)((fVar7 / (float10)3.1415927) * (float10)180.0 +
                                       (float10)10.0);
            if (0.0 < (float)param_1[0xb]) {
              param_1[0xb] = 0;
            }
            param_1[0xb6] = 0x428c0000;
          }
          if (0x16 < param_1[0x2b81]) {
            FUN_0042c840(0);
          }
          if (0x28 < param_1[0x2b81]) {
            FUN_00421100(2);
            param_1[0x15] = 0x41200000;
            return;
          }
        }
        if ((param_1[0x2b7d] == 2) || ((param_1[0x2b7d] == 1 && (0x16 < param_1[0x2b81])))) {
          if (param_1[0x2b7d] == 2) {
            if ((0.0 < (float)param_1[0xb]) &&
               (param_1[0xb] = (int)((float)param_1[0xb] - 5.0), (float)param_1[0xb] < 0.0)) {
              param_1[0xb] = 0;
            }
            if (((float)param_1[0xb] < 0.0) &&
               (param_1[0xb] = (int)((float)param_1[0xb] + 5.0), 0.0 < (float)param_1[0xb])) {
              param_1[0xb] = 0;
            }
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
        cVar2 = FUN_004218c0();
        if (cVar2 != '\0') {
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
  }
  else {
    switch(iVar5) {
    case 0x154:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
        param_1[0x3b] = 0;
      }
      uVar4 = FUN_0042c7b0();
      if ((uVar4 & 2) != 0) {
        FUN_00421080(0x188);
        FUN_0042c800(0);
        return;
      }
      sVar3 = FUN_0042c7b0();
      if ((sVar3 != 0) && (param_1[0x3b] == 0)) {
        param_1[0x3b] = 1;
      }
      if (param_1[0x2b81] == 0xf) {
        FUN_0042c880(0x3d);
        FUN_004223d0(2,10,0);
      }
      if (param_1[0x2b81] < 7) {
        FUN_0042db10(0,0x41200000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 9) {
        param_1[0x15] = 0x41700000;
      }
      if (param_1[0x2b81] == 0xf) {
        param_1[0x15] = 0;
        param_1[0x21d] = 0;
      }
      break;
    case 0x155:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0);
        return;
      }
      if (((param_1[0x2b7d] == 0) || (param_1[0x2b7d] == 3)) && ((char)param_1[0x21] == '\0')) {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        FUN_00423000();
      }
      param_1[0x1a1] = 2;
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x18] = 0;
        FUN_0042c800(0);
        FUN_0042c840(1);
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] < 5)) {
        param_1[0x15] = 0x41c80000;
        if (param_1[0x3b] == 1) {
          FUN_0042db10(0,0x41a00000);
        }
      }
      else {
        param_1[0x15] = (int)((float)param_1[0x15] - 3.0);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      if (param_1[0x2b81] == 3) {
        FUN_004223d0(3,10,0);
      }
      if (param_1[0x2b7d] == 1) {
        FUN_00434b30();
      }
      else {
        FUN_00434bd0();
      }
      uVar4 = FUN_0042c7b0();
      if ((uVar4 & 2) != 0) {
        FUN_00421080(0x188);
        FUN_0042c800(0);
        return;
      }
      break;
    default:
      goto switchD_004736a5_caseD_1;
    case 0x15e:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
        FUN_004223d0(0x20,0x14,0);
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042dc20(0,0x41700000);
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x14) {
        FUN_0042c8b0(0x5b);
        FUN_004230e0();
        uVar6 = 0x42700000;
        fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,0x42700000);
        fVar13 = (float)param_1[7];
        fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
        fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                        fVar8 * (float10)50.0);
        fVar11 = (float)param_1[6] + 20.0;
        fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
        fVar1 = (float)param_1[5];
        fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
        FUN_00435450(10,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                               fVar8 * (float10)50.0),fVar11,fVar13,fVar15,uVar6);
        uVar6 = 0x42700000;
        fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,0x42700000);
        fVar13 = (float)param_1[7];
        fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
        fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                        fVar8 * (float10)50.0);
        fVar11 = (float)param_1[6] + 20.0;
        fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
        fVar1 = (float)param_1[5];
        fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
        FUN_00435450(6,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                              fVar8 * (float10)50.0),fVar11,fVar13,fVar15,uVar6);
        param_1[0x3e] = 0;
      }
      if ((param_1[0x2b81] == 0x1c) && (param_1[0x3e] < 0x19)) {
        param_1[0x3e] = param_1[0x3e] + 1;
        return;
      }
      break;
    case 0x168:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        FUN_00421080(0x1d5);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_004223d0(0x20,0x14,0);
        FUN_00422900();
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042dc20(0,0x41700000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = (int)((float)param_1[0x15] * 0.25);
        param_1[0x10] = (int)((float)param_1[0x10] * 0.25);
        param_1[0x16] = 0x3dcccccd;
      }
      if (param_1[0x2b81] == 0x14) {
        param_1[0x18] = 0;
        FUN_0042c8b0(0x5b);
        param_1[0x15] = -0x3f300000;
        param_1[0x10] = 0x40a00000;
        FUN_004230e0();
        uVar6 = 0x42700000;
        fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,0x42700000);
        fVar13 = (float)param_1[7];
        fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
        fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                        fVar8 * (float10)50.0);
        fVar11 = (float)param_1[6] + 20.0;
        fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
        fVar1 = (float)param_1[5];
        fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
        FUN_00435450(10,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                               fVar8 * (float10)50.0),fVar11,fVar13,fVar15,uVar6);
        uVar6 = 0x42700000;
        fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,0x42700000);
        fVar13 = (float)param_1[7];
        fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
        fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                        fVar8 * (float10)50.0);
        fVar11 = (float)param_1[6] + 20.0;
        fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
        fVar1 = (float)param_1[5];
        fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
        FUN_00435450(6,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                              fVar8 * (float10)50.0),fVar11,fVar13,fVar15,uVar6);
      }
      if (param_1[0x2b81] == 0x14) {
        param_1[0x16] = 0x3f000000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if ((param_1[0x2b81] == 0x1c) && (param_1[0x3e] < 0x19)) {
        param_1[0x3e] = param_1[0x3e] + 1;
        return;
      }
      break;
    case 0x172:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] < 0xe) {
          param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
        }
        if (0x17 < param_1[0x2b81]) {
          param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
        }
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
        if (param_1[0x2b81] < 0xe) {
          FUN_0042db10(0,0x41700000);
        }
        if (param_1[0x2b81] < 0x20) {
          FUN_0042db10(0,0x40a00000);
        }
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x3e] = 0;
        FUN_0042c800(0);
        FUN_0042c840(1);
        FUN_00422900();
        FUN_00423000();
      }
      if (param_1[0x2b81] == 0x13) {
        FUN_0042c880(0x3e);
        FUN_004223d0(0x20,0x14,0);
      }
      if ((param_1[0x2b81] == 10) && (param_1[0x3e] < 5)) {
        param_1[0x3e] = param_1[0x3e] + 1;
        return;
      }
      if (param_1[0x2b81] == 0xe) {
        param_1[0x18] = 0;
        param_1[0x15] = 0x420c0000;
      }
      if (param_1[0x2b81] == 0x17) {
        param_1[0x15] = 0x41200000;
      }
      uVar4 = FUN_0042c7b0();
      if ((uVar4 & 2) != 0) {
        FUN_00421080(0x188);
        FUN_0042c800(0);
        return;
      }
      if ((param_1[0x2b81] < 0x10) || (0x1d < param_1[0x2b81])) {
        FUN_00434bd0();
      }
      else {
        FUN_00434b30();
      }
      break;
    case 0x186:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      uVar4 = FUN_0042c7b0();
      if (((uVar4 & 2) != 0) && (0 < param_1[0x20d])) {
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
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if ((param_1[0x2b7d] < 2) && (uVar4 = FUN_0042c7b0(), (uVar4 & 2) != 0)) {
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
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      uVar4 = FUN_0042c7b0();
      if (((uVar4 & 2) != 0) && (0 < param_1[0x20d])) {
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
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if ((param_1[0x2b7d] < 2) && (uVar4 = FUN_0042c7b0(), (uVar4 & 2) != 0)) {
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
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] < 0xe) {
          FUN_0042db10(0,0x41a00000);
        }
        param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x59);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 1;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      break;
    case 0x191:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
        FUN_0042dc20(0,0x41200000);
      }
      if (param_1[0x2b7d] == 0) {
        FUN_0042dc20(0,0x41700000);
        param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      if (param_1[0x2b81] == 10) {
        FUN_0042c8b0(0x59);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 1;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      break;
    case 0x192:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if (param_1[0x2b81] < 0xe) {
        FUN_0042dc20(0,0x41a00000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x59);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x2d;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x2d;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 1;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      if ((float)param_1[0x16] == 0.0) {
        param_1[0x16] = 0x3f000000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      break;
    case 0x193:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
        FUN_0042dc20(0,0x41200000);
      }
      if ((0x1e < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x59);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 1;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      break;
    case 0x195:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if (param_1[0x2b81] < 0xe) {
        FUN_0042db10(0,0x41200000);
      }
      if ((0x14 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = -0x3d4c0000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x59);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 1;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      break;
    case 0x196:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if (param_1[0x2b81] < 0xe) {
        FUN_0042db10(0,0x41200000);
      }
      if ((0x14 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x42b40000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x59);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 1;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      break;
    case 0x197:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if ((0x1e < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b7d] == 0) {
        FUN_0042db10(0,0x41700000);
        param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x43340000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x2d) {
          param_1[0x3c] = -0x2d;
        }
        if (0x2d < param_1[0x3c]) {
          param_1[0x3c] = 0x2d;
        }
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 1;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      break;
    case 0x198:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if (param_1[0x2b81] < 0xe) {
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
        FUN_0042c8b0(0x56);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3c] = iVar5;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 0;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 3;
          uVar6 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar6,uVar12,uVar14,fVar13);
        }
      }
      break;
    case 0x199:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
    case 0x1c2:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if (param_1[0x2b81] < 0x14) {
        FUN_0042db10(0,0x41900000);
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x14) {
        FUN_0042c8b0(0x5a);
        FUN_004230e0();
        if (param_1[0x1c8] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1d,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3a] = iVar5;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_14 = (float)((fVar7 * (float10)40.0) / (float10)5000.0);
        if (40.0 < local_14) {
          local_14 = 40.0;
        }
        if (local_14 < 0.0) {
          local_14 = 0.0;
        }
        if (param_1[0x3a] < 0) {
          local_14 = local_14 * 0.95;
        }
        fVar15 = (float)param_1[0x3a] + local_14;
        fVar11 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar11,fVar15);
        fVar13 = (float)param_1[7];
        fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
        fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                        fVar8 * (float10)50.0);
        fVar10 = (float)param_1[6] + 40.0;
        fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar10,fVar13);
        fVar1 = (float)param_1[5];
        fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
        FUN_00435450(9,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                              fVar8 * (float10)50.0),fVar10,fVar13,fVar11,fVar15);
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          local_14 = (float)param_1[0x3a] + local_14;
          fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,local_14);
          fVar13 = (float)param_1[7];
          fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                          fVar8 * (float10)50.0);
          fVar11 = (float)param_1[6] + 40.0;
          fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
          fVar1 = (float)param_1[5];
          fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(2,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                                fVar8 * (float10)50.0),fVar11,fVar13,fVar15,local_14);
        }
        else {
          local_14 = (float)param_1[0x3a] + local_14;
          fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,local_14);
          fVar13 = (float)param_1[7];
          fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                          fVar8 * (float10)50.0);
          fVar11 = (float)param_1[6] + 40.0;
          fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
          fVar1 = (float)param_1[5];
          fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(3,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                                fVar8 * (float10)50.0),fVar11,fVar13,fVar15,local_14);
        }
      }
      break;
    case 0x1cc:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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
      if (param_1[0x2b81] < 0x14) {
        FUN_0042dc20(0,0x41900000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
      }
      if (param_1[0x2b81] == 0x14) {
        FUN_0042c8b0(0x5a);
        FUN_004230e0();
        if (param_1[0x1c8] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1d,10,0);
        }
        FUN_0042da80();
        iVar5 = FUN_0066b668();
        param_1[0x3a] = iVar5;
        if (param_1[0x3a] < -0x28) {
          param_1[0x3a] = -0x28;
        }
        if (0x28 < param_1[0x3a]) {
          param_1[0x3a] = 0x28;
        }
        fVar7 = (float10)FUN_0042d980();
        fVar7 = (float10)FUN_0042de80((float)fVar7);
        local_18 = (float)((fVar7 * (float10)40.0) / (float10)5000.0);
        if (40.0 < local_18) {
          local_18 = 40.0;
        }
        if (local_18 < 0.0) {
          local_18 = 0.0;
        }
        if (param_1[0x3a] < 0) {
          local_18 = local_18 * 0.95;
        }
        fVar15 = (float)param_1[0x3a] + local_18;
        fVar11 = (float)param_1[0x17] + (float)param_1[0x19];
        fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar11,fVar15);
        fVar13 = (float)param_1[7];
        fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
        fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                        fVar8 * (float10)50.0);
        fVar10 = (float)param_1[6] + 20.0;
        fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar10,fVar13);
        fVar1 = (float)param_1[5];
        fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
        FUN_00435450(9,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                              fVar8 * (float10)50.0),fVar10,fVar13,fVar11,fVar15);
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          local_18 = (float)param_1[0x3a] + local_18;
          fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,local_18);
          fVar13 = (float)param_1[7];
          fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                          fVar8 * (float10)50.0);
          fVar11 = (float)param_1[6] + 20.0;
          fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
          fVar1 = (float)param_1[5];
          fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(2,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                                fVar8 * (float10)50.0),fVar11,fVar13,fVar15,local_18);
        }
        else {
          local_18 = (float)param_1[0x3a] + local_18;
          fVar15 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar7 = (float10)FUN_0065d010(param_1[0x17],fVar15,local_18);
          fVar13 = (float)param_1[7];
          fVar8 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar13 = (float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar13) -
                          fVar8 * (float10)50.0);
          fVar11 = (float)param_1[6] + 20.0;
          fVar7 = (float10)FUN_0065d050(param_1[0x17],fVar11,fVar13);
          fVar1 = (float)param_1[5];
          fVar8 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(3,(float)((float10)(float)(fVar7 * (float10)0.0 + (float10)fVar1) -
                                fVar8 * (float10)50.0),fVar11,fVar13,fVar15,local_18);
        }
      }
      param_1[0x16] = 0x3f000000;
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      break;
    case 0x1d5:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
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

