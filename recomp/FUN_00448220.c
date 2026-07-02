// ============================================
// Address:  0x00448220
// Original: FUN_00448220
// Status:   unreviewed
// ============================================


void __fastcall FUN_00448220(int *param_1)

{
  float fVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  int local_58;
  int local_54;
  float local_50;
  int local_48;
  int local_44;
  float local_40;
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
  if (iVar4 < 0x155) {
    if (iVar4 == 0x154) {
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
      param_1[0x1a1] = 2;
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        FUN_00423000();
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        FUN_0042c800(0);
        FUN_0042c840(1);
      }
      uVar5 = FUN_0042c7b0();
      if ((uVar5 & 2) != 0) {
        FUN_00421080(0x188);
        FUN_0042c800(0);
        return;
      }
      if (param_1[0x2b81] == 0xc) {
        FUN_0042c880(0x43);
        FUN_004223d0(3,10,0);
      }
      if (param_1[0x2b81] < 8) {
        FUN_0042db10(0,0x40c00000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xf) {
        param_1[0x15] = 0;
        param_1[0x21d] = 0;
      }
      if ((param_1[0x2b81] < 10) || (0x10 < param_1[0x2b81])) {
        FUN_00434bd0();
      }
      else {
        FUN_00434b30();
      }
    }
    else if (iVar4 < 0x2d) {
      if (iVar4 == 0x2c) {
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
        switch(iVar4) {
        case 0:
          param_1[0x10] = 0;
          param_1[0x15] = 0;
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
          goto switchD_004482b2_caseD_1;
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
          param_1[0x15] = 0x40e66666;
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
          if ((param_1[0x2b7d] < 2) && (param_1[0x20d] = param_1[0x20d] + -0xc, param_1[0x20d] < 0))
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
            param_1[0x15] = 0x41840000;
            param_1[0x3a] = 0;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x21d] = 0x40800000;
            param_1[0x15] = 0x41840000;
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
            param_1[0x20d] = param_1[0x20d] + -0xc;
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
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 12.5)) {
            param_1[0x15] = 0x41480000;
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
          if (param_1[0x2b81] % 9 == 0) {
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
            param_1[0x20d] = param_1[0x20d] + -0xc;
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
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 12.5)) {
            param_1[0x15] = 0x41480000;
          }
          if ((param_1[0x2b7d] == 2) &&
             (param_1[0x15] = (int)((float)param_1[0x15] - 0.7), (float)param_1[0x15] < 0.0)) {
            param_1[0x15] = 0;
          }
          if (param_1[0x2b81] % 9 == 0) {
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
          if ((param_1[0x2b7d] < 2) && (param_1[0x20d] = param_1[0x20d] + -0xc, param_1[0x20d] < 0))
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
             (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
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
            param_1[0x15] = 0x41840000;
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
            param_1[0x15] = 0x41840000;
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
      switch(iVar4) {
      case 300:
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
        if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3b] = 0;
          param_1[0x15] = 0x41700000;
          fVar6 = (float10)FUN_0042d980();
          if ((float10)810000.0 <= fVar6) {
            param_1[0x3a] = 1;
          }
          else {
            param_1[0x3a] = 1;
            param_1[0x15] = 0x41c80000;
          }
          FUN_00422900();
          FUN_00423000();
        }
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        sVar3 = FUN_0042c7b0();
        if ((sVar3 != 0) && (param_1[0x3b] == 0)) {
          param_1[0x3b] = 1;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_0042db10(0,0x43340000);
        }
        else if (param_1[0x2b7d] < 2) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 1) &&
           (((fVar6 = (float10)FUN_0042d980(), fVar6 < (float10)90000.0 || (param_1[0x3a] == 0)) ||
            (10 < param_1[0x2b81])))) {
          FUN_00421100(2);
          return;
        }
        if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 0)) {
          FUN_0042c880(0x40);
          fVar6 = (float10)FUN_0042d980();
          if (((float10)90000.0 <= fVar6) ||
             ((fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6 ||
              (*(char *)((int)param_1 + 0xaec3) != '\x01')))) {
            fVar6 = (float10)FUN_0042d980();
            if (((float10)90000.0 <= fVar6) ||
               ((fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6 ||
                (*(char *)((int)param_1 + 0xaebe) != '\x01')))) {
              fVar6 = (float10)FUN_0042d980();
              if (((float10)90000.0 <= fVar6) ||
                 ((fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6 ||
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
        if (param_1[0x2b7d] == 2) {
          if ((param_1[0x2b81] < 4) && (param_1[0x3c] == 1)) {
            FUN_0042db10(0,0x40a00000);
          }
          param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
        }
        if (((param_1[0x2b7d] == 2) && (2 < param_1[0x2b81])) && (param_1[0x2b81] < 0xb)) {
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
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x3b] != 0) && (param_1[0x1a1] = 2, param_1[0x2b81] < 8)) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          param_1[0x15] = 0x41200000;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b81] == 3) {
          FUN_0042c880(0x43);
          FUN_004223d0(3,10,0);
        }
        if (param_1[0x2b81] == 8) {
          param_1[0x15] = 0;
          param_1[0x21d] = 0;
        }
        if ((param_1[0x2b81] < 10) || (0x10 < param_1[0x2b81])) {
          FUN_00434bd0();
        }
        else {
          FUN_00434b30();
        }
        break;
      default:
switchD_004482b2_caseD_1:
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
          param_1[0x16] = 0x3f000000;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x15] = 0x41f00000;
          param_1[0x3a] = 0;
          FUN_0042db10(0,0x43340000);
          FUN_00422900();
          FUN_00423000();
        }
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if (param_1[0x2b7d] == 0) {
          FUN_0042db10(0,0x41a00000);
        }
        if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0,0x41700000), -1 < param_1[0x2b81])) {
          FUN_00421100(2);
          return;
        }
        if (param_1[0x2b7d] == 2) {
          param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
          if (((float)param_1[0x15] < 0.0) || (param_1[0x2b81] == 5)) {
            param_1[0x15] = 0;
          }
          if (param_1[0x2b81] < 5) {
            FUN_0042db10(0,0x40a00000);
          }
          if (param_1[0x2b81] == 4) {
            FUN_0042c880(0x3e);
            FUN_004223d0(2,10,0);
          }
          if ((param_1[0x2b81] < 5) || (7 < param_1[0x2b81])) {
            FUN_00434bd0();
          }
          else {
            FUN_00434b30();
          }
          if (((0xc < param_1[0x2b81]) && (uVar5 = FUN_0042c7b0(), (uVar5 & 1) != 0)) &&
             (param_1[0xa0] != 0)) {
            FUN_00421080(0x28);
            return;
          }
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
          param_1[0x16] = 0x3f000000;
          return;
        }
        if (param_1[0x2b81] == 0) {
          FUN_00422900();
          FUN_00423000();
          param_1[0x15] = 0x41a00000;
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          FUN_0042db10(0,0x43340000);
        }
        if (param_1[0x2b81] == 0xc) {
          FUN_0042c880(0x43);
          FUN_004223d0(3,10,0);
        }
        if (param_1[0x2b81] < 10) {
          FUN_0042db10(0,0x41100000);
        }
        if ((0x11 < param_1[0x2b81]) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 2.0), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if ((param_1[0x2b81] < 0xc) || (0x12 < param_1[0x2b81])) {
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
        if ((param_1[0x2b7d] == 2) && (5 < param_1[0x2b81])) {
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        }
        if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) && (10 < param_1[0x2b81])) {
          FUN_00421080(0x149);
          param_1[0xb] = 0;
          param_1[0x15] = 0;
          param_1[0x10] = 0;
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
          param_1[0x15] = 0x41480000;
          fVar6 = (float10)FUN_0042d980();
          if (fVar6 < (float10)1e+06) {
            param_1[0x3c] = 0xe6;
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
          fVar1 = (float)(fVar6 + (float10)10.0);
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            fVar6 = (float10)FUN_0042da80();
            local_8 = (float)(fVar6 + (float10)10.0);
          }
          if ((fVar1 < local_8) && (local_8 = local_8 - 5.0, local_8 < fVar1)) {
            local_8 = fVar1;
          }
          if ((local_8 < fVar1) && (local_8 = local_8 + 5.0, fVar1 < local_8)) {
            local_8 = fVar1;
          }
          if (50.0 < local_8) {
            local_8 = 50.0;
          }
          if (local_8 < -30.0) {
            local_8 = -30.0;
          }
          iVar4 = param_1[0x3c];
          fVar6 = (float10)FUN_0065d050(local_8);
          param_1[0x15] = (int)(float)(fVar6 * (float10)((float)iVar4 * 0.1));
          iVar4 = param_1[0x3c];
          fVar6 = (float10)FUN_0065d010(local_8);
          param_1[0x10] = (int)(float)(fVar6 * (float10)((float)iVar4 * 0.1));
          fVar6 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
          param_1[0xb] = (int)(float)((fVar6 / (float10)3.1415927) * (float10)180.0 + (float10)20.0)
          ;
          param_1[0xb6] = 0x428c0000;
          param_1[0x3c] = param_1[0x3c] + -4;
          if (param_1[0x3c] < 0x7d) {
            param_1[0x3c] = 0x7d;
          }
          FUN_0042db10(0,0x40400000);
        }
        if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0,0x40000000), 10 < param_1[0x2b81])) {
          fVar6 = (float10)FUN_0042d980();
          fVar7 = (float10)FUN_0042da30();
          fVar8 = (float10)FUN_0042da30();
          if ((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar6 < (float10)40000.0) ||
             ((0x19 < param_1[0x2b81] || (param_1[0x3c] == 0)))) {
            FUN_00421100(2);
            return;
          }
        }
        if (param_1[0x2b7d] == 2) {
          if (param_1[0x2b81] == 0) {
            FUN_0042c880(0x3f);
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
          if (param_1[0x2b81] < 8) {
            FUN_00434b30();
          }
          else {
            FUN_00434bd0();
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
        if (((char)param_1[0x21] == '\0') && ((param_1[0x2b7d] == 0 || (param_1[0x2b7d] == 3)))) {
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if (((char)param_1[0x21] != '\0') &&
           (((param_1[0x2b7d] == 1 || (param_1[0x2b7d] == 2)) && ((float)param_1[0x10] < 0.0)))) {
          FUN_00421100(3);
          param_1[0x15] = 0;
          param_1[0x10] = 0;
          return;
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          FUN_00422900();
          FUN_00423000();
        }
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
        }
        if (param_1[0x2b7d] == 0) {
          param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
          if ((float)param_1[0x15] < 0.0) {
            param_1[0x15] = 0;
          }
          FUN_0042db10(0,0x40a00000);
        }
        if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) {
          param_1[0x15] = 0x41700000;
          param_1[0x10] = 0x41700000;
          param_1[0x16] = 0x3f400000;
          fVar6 = (float10)FUN_0042d980();
          if (((float10)40000.0 <= fVar6) ||
             ((fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6 ||
              (*(char *)((int)param_1 + 0xaec3) != '\x01')))) {
            fVar6 = (float10)FUN_0042d980();
            if (((float10)40000.0 <= fVar6) ||
               ((fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6 ||
                (*(char *)((int)param_1 + 0xaebe) != '\x01')))) {
              fVar6 = (float10)FUN_0042d980();
              if (((float10)40000.0 <= fVar6) ||
                 ((fVar6 = (float10)FUN_0042df90(param_1[0x19]), (float10)30.0 <= fVar6 ||
                  (*(char *)((int)param_1 + 0xaeb9) != '\x01')))) {
                FUN_004223d0(3,10,0);
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
        if ((param_1[0x2b7d] == 1) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        if ((param_1[0x2b7d] == 1) || (param_1[0x2b7d] == 2)) {
          param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        }
        if (((param_1[0x2b7d] == 0) && (10 < param_1[0x2b81])) ||
           ((param_1[0x2b7d] == 1 && (param_1[0x2b81] < 0x14)))) {
          FUN_00434b30();
        }
        else {
          FUN_00434bd0();
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
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x3a] = 0;
          param_1[0x3c] = 0;
          param_1[0x15] = 0x418c0000;
          fVar6 = (float10)FUN_0042d980();
          if (fVar6 < (float10)640000.0) {
            param_1[0x3c] = 1;
            param_1[0x15] = 0x41a00000;
          }
        }
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
          FUN_00421080(0x188);
          FUN_0042c800(0);
          return;
        }
        if ((param_1[0x2b7d] < 2) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x41a00000);
        }
        if (((param_1[0x2b7d] == 2) && (param_1[0x2b81] < 10)) && (param_1[0x3c] == 1)) {
          FUN_0042db10(0,0x41200000);
        }
        if (((param_1[0x2b7d] == 1) && (2 < param_1[0x2b81])) &&
           ((fVar6 = (float10)FUN_0042d980(), fVar6 < (float10)90000.0 || (param_1[0x3c] == 0)))) {
          FUN_00421100(2);
          return;
        }
        if ((1 < param_1[0x2b7d]) &&
           (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
          param_1[0x15] = 0;
        }
        if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 10)) {
          FUN_004223d0(2,10,0);
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
          iVar4 = FUN_0066b65c((float)param_1[0x19] < 90.0);
          if (iVar4 != 0) {
            FUN_0042db10(0,0x3f800000);
          }
          if (param_1[0x2b81] == 0) {
            FUN_00422490(3,0,10,0);
            fVar6 = (float10)FUN_0042da80();
            local_10 = (float)fVar6;
            if (-5.0 < local_10) {
              local_10 = -5.0;
            }
            if (local_10 < -20.0) {
              local_10 = -20.0;
            }
            fVar6 = (float10)FUN_0065d050(local_10);
            param_1[0x15] = (int)(float)(fVar6 * (float10)25.0);
            fVar6 = (float10)FUN_0065d010(local_10);
            param_1[0x10] = (int)(float)(fVar6 * (float10)25.0);
            fVar6 = (float10)FUN_00423580(param_1[0x10],param_1[0x15]);
            param_1[0xb] = (int)(float)((fVar6 / (float10)3.1415927) * (float10)180.0 +
                                       (float10)10.0);
            if (0.0 < (float)param_1[0xb]) {
              param_1[0xb] = 0;
            }
            param_1[0xb6] = 0x428c0000;
          }
          sVar3 = FUN_0042c7b0();
          if (sVar3 != 0) {
            param_1[0xb] = 0;
            param_1[0x10] = 0x41200000;
            param_1[0x15] = -0x3f200000;
            param_1[0x16] = 0x3eb33333;
            FUN_00421080(0x14e);
            FUN_0042c800(0);
            FUN_0042c840(1);
            return;
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
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      }
    }
  }
  else {
    switch(iVar4) {
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
        FUN_00423000();
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        FUN_0042c800(0);
        FUN_0042c840(1);
        param_1[0x15] = 0;
      }
      if (((param_1[0x2b81] == 0x19) || (param_1[0x2b81] == 0x2d)) || (param_1[0x2b81] == 0x41)) {
        FUN_0042c8b0(0x44);
      }
      if (param_1[0x2b81] < 8) {
        FUN_0042db10(0,0x41c80000);
      }
      if (param_1[0x2b81] == 0x14) {
        param_1[0x15] = 0x41080000;
        param_1[0x21d] = 0;
      }
      if (0x14 < param_1[0x2b81]) {
        param_1[0x1a1] = 0;
      }
      if (param_1[0x2b81] == 0x49) {
        param_1[0x15] = 0;
        param_1[0x21d] = 0;
      }
      if ((param_1[0x2b81] < 0x15) || (0x40 < param_1[0x2b81])) {
        FUN_00434bd0();
      }
      else {
        FUN_00434b30();
      }
      break;
    case 0x15f:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0);
        return;
      }
      if (((param_1[0x2b7d] == 0) || (param_1[0x2b7d] == 4)) && ((char)param_1[0x21] == '\0')) {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x18] = 0;
        FUN_0042c800(0);
        FUN_0042c840(1);
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] < 5)) {
        FUN_0042db10(0,0x41200000);
      }
      if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) {
        param_1[0x15] = 0x41200000;
        param_1[0x10] = 0x41a00000;
        param_1[0x16] = 0x3f000000;
        param_1[0x21d] = 0;
      }
      if ((((0 < param_1[0x2b7d]) &&
           (param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]), param_1[0x2b7d] < 4)
           ) && ((char)param_1[0x21] != '\0')) && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        FUN_00421100(4);
        return;
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 0.7);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b7d] == 1) {
        FUN_00434b30();
      }
      else {
        FUN_00434bd0();
      }
      break;
    default:
      goto switchD_004482b2_caseD_1;
    case 0x168:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0);
        return;
      }
      if (param_1[0x2b81] == 0) {
        uVar5 = FUN_0065d150();
        if (uVar5 % 100 < 0x32) {
          FUN_00422490(0x20,4,0x14,0);
        }
        else {
          FUN_00422490(0x20,3,0x14,0);
        }
        FUN_0042c800(0);
        FUN_00422900();
      }
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
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41900000);
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x10) {
        FUN_0042c8b0(0x40);
        FUN_00434fd0(8,0,0x428c0000,0);
        FUN_004230e0();
      }
      break;
    case 0x172:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0x2b);
        param_1[0x16] = 0x3f000000;
        return;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        FUN_00421080(0x1d5);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        uVar5 = FUN_0065d150();
        if (uVar5 % 100 < 0x32) {
          FUN_00422490(0x20,4,0xf,0);
        }
        else {
          FUN_00422490(0x20,3,0xf,0);
        }
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41900000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
        param_1[0x10] = 0;
      }
      if (param_1[0x2b81] == 0x10) {
        FUN_0042c8b0(0x40);
        FUN_00434fd0(8,0,0x428c0000,0);
        FUN_004230e0();
      }
      param_1[0x16] = 0x3f000000;
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
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
      uVar5 = FUN_0042c7b0();
      if (((uVar5 & 2) != 0) && (0 < param_1[0x20d])) {
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
      if ((param_1[0x2b7d] < 2) && (uVar5 = FUN_0042c7b0(), (uVar5 & 2) != 0)) {
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
      uVar5 = FUN_0042c7b0();
      if (((uVar5 & 2) != 0) && (0 < param_1[0x20d])) {
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
      if ((param_1[0x2b7d] < 2) && (uVar5 = FUN_0042c7b0(), (uVar5 & 2) != 0)) {
        FUN_00421080(0x18a);
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
        FUN_00423000();
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x41a00000);
      }
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        FUN_0042db10(0,0x41700000);
        param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      if (param_1[0x2b81] == 7) {
        param_1[0x15] = 0x42340000;
      }
      if (param_1[0x2b81] == 0xf) {
        FUN_0042c8b0(0x43);
        FUN_004223d0(0x1d,10,0);
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x12) {
        FUN_0042c8b0(0x4d);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00434fd0(6,0,0,0);
        }
        else {
          FUN_00434fd0(0,0,0,0);
          FUN_00434fd0(9,0,0,0);
        }
      }
      if ((param_1[0x2b81] < 8) || (0x12 < param_1[0x2b81])) {
        FUN_00434bd0();
      }
      else {
        FUN_00434b30();
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
        FUN_00423000();
        param_1[0x18] = 0;
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x41a00000);
      }
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] == 0) {
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        FUN_0042dc20(0,0x40a00000);
        param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
        if ((float)param_1[0x15] < 0.0) {
          param_1[0x15] = 0;
        }
      }
      if (param_1[0x2b81] == 7) {
        param_1[0x15] = 0x41f00000;
      }
      if (param_1[0x2b81] == 0xf) {
        FUN_0042c8b0(0x43);
        FUN_004223d0(0x1d,10,0);
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x12) {
        FUN_0042c8b0(0x4d);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00434fd0(6,0,0,0);
        }
        else {
          FUN_00434fd0(0,0,0,0);
        }
      }
      if ((param_1[0x2b81] < 8) || (0x12 < param_1[0x2b81])) {
        FUN_00434bd0();
      }
      else {
        FUN_00434b30();
      }
      break;
    case 0x192:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0);
        return;
      }
      if (((char)param_1[0x21] != '\0') && (param_1[0x2b7d] < 2)) {
        FUN_00421100(2);
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        FUN_00423000();
      }
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] == 0) {
          param_1[0x15] = 0;
          param_1[0x10] = 0;
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if (param_1[0x2b81] < 10) {
          FUN_0042db10(0,0x41a00000);
        }
      }
      if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) {
        param_1[0x10] = -0x3de00000;
        fVar6 = (float10)FUN_0042d980();
        fVar6 = (float10)FUN_0042de80((float)fVar6);
        fVar1 = (float)param_1[0x10];
        fVar7 = (float10)FUN_0042da30();
        param_1[0x15] =
             (int)(float)((float10)(float)((fVar6 + (float10)1.0) * (float10)fVar1) / fVar7);
        if ((float)param_1[0x15] <= 10.0) {
          local_40 = (float)param_1[0x15];
        }
        else {
          local_40 = 10.0;
        }
        if (0.0 <= local_40) {
          if ((float)param_1[0x15] <= 10.0) {
            local_48 = param_1[0x15];
          }
          else {
            local_48 = 0x41200000;
          }
          local_44 = local_48;
        }
        else {
          local_44 = 0;
        }
        param_1[0x15] = local_44;
      }
      if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 0)) {
        FUN_0042c8b0(0x43);
        FUN_004223d0(0x1d,10,0);
      }
      if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 5)) {
        FUN_0042c8b0(0x4d);
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00434fd0(6,0,0,0);
        }
        else {
          FUN_00434fd0(0,0,0,0);
          FUN_00434fd0(9,0,0,0);
        }
      }
      if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] < 6)) {
        FUN_00434b30();
      }
      else {
        FUN_00434bd0();
      }
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
        FUN_00423000();
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41100000);
      }
      if (0xd < param_1[0x2b81]) {
        FUN_00434a70(0,0xffffffff);
        FUN_00434a70(1,0xffffffff);
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
        FUN_0042c8b0(0x46);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_00434fd0(0,0,(float)param_1[0x3c],0);
        FUN_004230e0();
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
        FUN_00423000();
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41100000);
      }
      if (0xd < param_1[0x2b81]) {
        FUN_00434a70(0,0xffffffff);
        FUN_00434a70(1,0xffffffff);
      }
      if ((10 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = -0x3d4c0000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x46);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_00434fd0(0,0,(float)param_1[0x3c],0);
        FUN_004230e0();
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
        FUN_00423000();
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41100000);
      }
      if (0xd < param_1[0x2b81]) {
        FUN_00434a70(0,0xffffffff);
        FUN_00434a70(1,0xffffffff);
      }
      if ((10 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0x42b40000;
        param_1[0x15] = 0x41200000;
      }
      if (param_1[0x2b81] == 0xd) {
        FUN_0042c8b0(0x46);
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
        FUN_00434fd0(0,0,(float)param_1[0x3c],0);
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
      if (0xd < param_1[0x2b81]) {
        FUN_00434a70(0,0xffffffff);
        FUN_00434a70(1,0xffffffff);
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
        FUN_00434fd0(4,0x42480000,0x42340000,0);
        FUN_00434fd0(4,0xc2480000,0x42340000,0);
      }
      break;
    case 0x198:
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0);
        return;
      }
      if (((char)param_1[0x21] != '\0') && (param_1[0x2b7d] < 2)) {
        FUN_00421100(2);
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
      }
      if (param_1[0x2b7d] == 0) {
        if (param_1[0x2b81] == 0) {
          param_1[0x18] = 0;
          FUN_0042c800(0);
          FUN_0042c840(1);
        }
        if (param_1[0x2b81] < 10) {
          FUN_0042db10(0,0x41900000);
        }
      }
      if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) {
        param_1[0x10] = -0x3de00000;
        fVar6 = (float10)FUN_0042d980();
        fVar6 = (float10)FUN_0042de80((float)fVar6);
        fVar1 = (float)param_1[0x10];
        fVar7 = (float10)FUN_0042da30();
        param_1[0x15] =
             (int)(float)((float10)(float)((fVar6 + (float10)1.0) * (float10)fVar1) / fVar7);
        if ((float)param_1[0x15] <= 10.0) {
          local_50 = (float)param_1[0x15];
        }
        else {
          local_50 = 10.0;
        }
        if (0.0 <= local_50) {
          if ((float)param_1[0x15] <= 10.0) {
            local_58 = param_1[0x15];
          }
          else {
            local_58 = 0x41200000;
          }
          local_54 = local_58;
        }
        else {
          local_54 = 0;
        }
        param_1[0x15] = local_54;
      }
      if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 0)) {
        FUN_0042c8b0(0x3e);
      }
      if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 5)) {
        FUN_0042c8b0(0x4d);
        FUN_0042da80();
        iVar4 = FUN_0066b668();
        param_1[0x3c] = iVar4;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
      }
      if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] < 6)) {
        FUN_00434b30();
      }
      else {
        FUN_00434bd0();
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
      FUN_00434a70(0,2);
      FUN_00434a70(1,0xffffffff);
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
        param_1[0x3a] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41900000);
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if ((0xb < param_1[0x2b81]) && (param_1[0x2b81] < 0x1b)) {
        param_1[0x3a] = param_1[0x3a] + 4;
        uVar5 = FUN_0065d150();
        param_1[0x3b] = param_1[0x3a] + -5 + uVar5 % 10;
        FUN_004230e0();
        if (param_1[0x2b81] == 0xf) {
          FUN_0042c8b0(0x3f);
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,(float)param_1[0x3b] - 30.0,0,0);
        }
        else {
          FUN_00435000(0,3,(float)param_1[0x3b] - 30.0,0,0);
        }
      }
      break;
    case 0x1cc:
      FUN_00434a70(0,2);
      FUN_00434a70(1,0xffffffff);
      cVar2 = FUN_004218c0();
      if (cVar2 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b81])) {
        param_1[0x10] = 0;
        FUN_00421080(0x1d5);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41900000);
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
        param_1[0x18] = 0;
      }
      if ((0xe < param_1[0x2b81]) && (param_1[0x2b81] < 0x1e)) {
        param_1[0x3a] = param_1[0x3a] + 4;
        uVar5 = FUN_0065d150();
        param_1[0x3b] = param_1[0x3a] + -5 + uVar5 % 10;
        if (param_1[0x2b81] == 0xf) {
          FUN_0042c8b0(0x3f);
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          FUN_00435000(0,1,(float)param_1[0x3b] - 30.0,0,0);
        }
        else {
          FUN_00435000(0,3,(float)param_1[0x3b] - 30.0,0,0);
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

