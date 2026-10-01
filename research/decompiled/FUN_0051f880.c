// Function: FUN_0051f880
// Address:  0x0051f880
// Source:   batch_decompile (mass dump)
// Hash:     781eb9d91e2ce793


void __fastcall FUN_0051f880(int *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  undefined4 uVar14;
  int local_28;
  int local_24;
  float local_20;
  float local_14;
  float local_10;
  float local_8;
  
  if (param_1[0x28] != 0) {
    return;
  }
  FUN_00434a70(0,0);
  FUN_00434a70(1,1);
  FUN_00434bd0();
  iVar3 = param_1[0x2b7b];
  if (iVar3 < 0x154) {
    if (iVar3 == 0x153) {
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
    }
    else if (iVar3 < 0x2d) {
      if (iVar3 == 0x2c) {
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
      else {
        switch(iVar3) {
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
          goto switchD_0051f912_caseD_1;
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
            param_1[0x15] = 0x41800000;
            param_1[0x3a] = 0;
          }
          if (param_1[0x2b7d] == 1) {
            param_1[0x21d] = 0x40800000;
            param_1[0x15] = 0x41800000;
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
          uVar5 = param_1[0x2b81] & 0x80000003;
          if ((int)uVar5 < 0) {
            uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
          }
          if ((uVar5 == 0) && (param_1[0x2b7d] == 2)) {
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
            param_1[0x15] = 0x41700000;
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
            param_1[0x15] = 0x41700000;
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
        }
      }
    }
    else {
      switch(iVar3) {
      case 300:
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
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
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
        break;
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
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
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
switchD_0051f912_caseD_1:
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
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
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
          if (((0xf < param_1[0x2b81]) && (uVar5 = FUN_0042c7b0(), (uVar5 & 1) != 0)) &&
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
            local_20 = (float)param_1[0x10];
          }
          else {
            local_20 = 3.0;
          }
          if (-3.0 <= local_20) {
            if ((float)param_1[0x10] <= 3.0) {
              local_28 = param_1[0x10];
            }
            else {
              local_28 = 0x40400000;
            }
            local_24 = local_28;
          }
          else {
            local_24 = -0x3fc00000;
          }
          param_1[0x10] = local_24;
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
          iVar3 = param_1[0x3c];
          fVar6 = (float10)FUN_0065d050(local_8);
          param_1[0x15] = (int)(float)(fVar6 * (float10)((float)iVar3 * 0.1));
          iVar3 = param_1[0x3c];
          fVar6 = (float10)FUN_0065d010(local_8);
          param_1[0x10] = (int)(float)(fVar6 * (float10)((float)iVar3 * 0.1));
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
        uVar5 = FUN_0042c7b0();
        if ((uVar5 & 2) != 0) {
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
      }
    }
  }
  else {
    switch(iVar3) {
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
      uVar5 = FUN_0042c7b0();
      if ((uVar5 & 2) != 0) {
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
      param_1[0x1a1] = 2;
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
      break;
    default:
      goto switchD_0051f912_caseD_1;
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
      if (param_1[0x2b81] < 0x31) {
        FUN_00434a70(0,2);
        FUN_00434a70(1,0xffffffff);
      }
      else {
        FUN_00434a70(0,0);
        FUN_00434a70(1,1);
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        FUN_00423000();
        FUN_0042c840(1);
        FUN_0042c800(0);
        FUN_00422490(0x27,0,0x14,0);
        param_1[0x3e] = 0;
        param_1[0x10] = 0;
        param_1[0x15] = 0;
      }
      if ((param_1[0x2b81] < 0x1a) || (0x2b < param_1[0x2b81])) {
        FUN_00434bd0();
      }
      else {
        FUN_00434b90(0);
      }
      if (param_1[0x2b81] < 0x19) {
        FUN_0042dc20(0,0x41200000);
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 0.75);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x19) {
        param_1[0x18] = 0;
        param_1[0x15] = 0x41b40000;
        FUN_0042c8b0(0x41);
      }
      if (param_1[0x2b81] == 0x31) {
        FUN_0042c8b0(0x7d);
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_004230e0();
        fVar11 = (float)param_1[0x3c];
        uVar14 = 0;
        uVar12 = 6;
        uVar4 = FUN_0064e6c0("Bip01_R_Hand");
        FUN_00435220(uVar4,uVar12,uVar14,fVar11);
      }
      break;
    case 0x168:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x2b);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422900();
        FUN_00423000();
        FUN_0042c840(1);
        FUN_0042c800(0);
        FUN_00422490(0x27,0,0x14,0);
        param_1[0x3e] = 0;
        param_1[0x10] = 0;
        param_1[0x15] = (int)((float)param_1[0x15] * 0.25);
      }
      if (param_1[0x2b81] < 0x31) {
        FUN_00434a70(0,2);
        FUN_00434a70(1,0xffffffff);
      }
      else {
        FUN_00434a70(0,0);
        FUN_00434a70(1,1);
      }
      if ((param_1[0x2b81] < 0x1a) || (0x2b < param_1[0x2b81])) {
        FUN_00434bd0();
      }
      else {
        FUN_00434b90(0);
      }
      if (param_1[0x2b81] < 0x19) {
        FUN_0042dc20(0,0x41200000);
      }
      if ((param_1[0x2b81] < 0x1a) || (0x30 < param_1[0x2b81])) {
        param_1[0xc] = 0;
      }
      else {
        param_1[0xc] = (int)((float)param_1[0xc] + 5.0);
      }
      if (param_1[0x2b81] < 0x31) {
        fVar6 = (float10)FUN_0042da80();
        local_14 = (float)fVar6;
        if (30.0 < local_14) {
          local_14 = 30.0;
        }
        if (local_14 < -30.0) {
          local_14 = -30.0;
        }
        param_1[0xb] = (int)local_14;
        param_1[0xb6] = 0x428c0000;
      }
      param_1[0x16] = 0x3f000000;
      if (param_1[0x2b81] == 0x31) {
        param_1[0x18] = 0;
        param_1[0x15] = -0x3ee00000;
        param_1[0x10] = 0x40a00000;
        FUN_0042c8b0(0x7d);
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        FUN_004230e0();
        fVar11 = (float)param_1[0x3c];
        uVar14 = 0;
        uVar12 = 6;
        uVar4 = FUN_0064e6c0("Bip01_R_Hand");
        FUN_00435220(uVar4,uVar12,uVar14,fVar11);
      }
      if (param_1[0x2b81] < 0x32) {
        param_1[0x10] = (int)((float)param_1[0x10] - 0.25);
      }
      else {
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
        if (0x3c < param_1[0x2b81]) {
          if ((0.0 < (float)param_1[0xb]) &&
             (param_1[0xb] = (int)((float)param_1[0xb] - 2.0), (float)param_1[0xb] < 0.0)) {
            param_1[0xb] = 0;
          }
          if (((float)param_1[0xb] < 0.0) &&
             (param_1[0xb] = (int)((float)param_1[0xb] + 2.0), 0.0 < (float)param_1[0xb])) {
            param_1[0xb] = 0;
          }
        }
        if ((char)param_1[0x21] != '\0') {
          param_1[0x10] = 0;
          param_1[0x15] = 0;
          FUN_00421080(0x1d5);
          return;
        }
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
      if ((param_1[0x2b7d] < 2) && (uVar5 = FUN_0042c7b0(), (uVar5 & 2) != 0)) {
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
      param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042db10(0,0x41200000);
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042db10(0,0x40a00000);
      }
      if (param_1[0x2b81] == 0xf) {
        FUN_0042c8b0(0x7c);
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 125.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(0,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
        }
        else {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 125.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(1,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
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
        FUN_0042dc20(0,0x41a00000);
      }
      if ((param_1[0x2b7d] == 0) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0xf) {
        FUN_0042c8b0(0x7c);
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        FUN_004230e0();
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 125.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(0,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
        }
        else {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 125.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(1,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
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
        param_1[0x16] = 0x3f000000;
      }
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41200000);
      }
      if (param_1[0x2b81] < 0xf) {
        FUN_0042dc20(0,0x40a00000);
      }
      if (param_1[0x2b81] == 0xf) {
        FUN_0042c8b0(0x7c);
        FUN_004230e0();
        if (param_1[0x1b7] == 1) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1c,10,0);
        }
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x28 < param_1[0x3c]) {
          param_1[0x3c] = 0x28;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 125.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(0,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
        }
        else {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)50.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 125.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(1,(float)(fVar6 * (float10)50.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
        }
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
      }
      if ((0x19 < param_1[0x2b81]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0) {
        param_1[0x18] = 0;
        param_1[0x15] = 0x41700000;
      }
      if (param_1[0x2b81] == 0x14) {
        FUN_0042c8b0(0x7c);
        FUN_004230e0();
        if (param_1[0x1b7] < 2) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 100.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(0,(float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
        }
        else {
          fVar10 = (float)param_1[0x3c];
          fVar13 = (float)param_1[0x17] + (float)param_1[0x19];
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],fVar13,fVar10);
          fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
          fVar9 = (float)param_1[6] + 100.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          FUN_00435450(1,(float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),fVar9,fVar11,
                       fVar13,fVar10);
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
        FUN_0042db10(0,0x41700000);
      }
      if (param_1[0x2b81] < 0x14) {
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
      if (param_1[0x2b81] == 0x14) {
        FUN_0042c8b0(0x7c);
        FUN_004230e0();
        if (param_1[0x1b7] < 2) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar4 = 0;
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],0,fVar13);
          fVar11 = (float)param_1[7];
          fVar7 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar11 = (float)((float10)(float)(fVar6 * (float10)200.0 + (float10)fVar11) -
                          fVar7 * (float10)100.0);
          fVar9 = (float)param_1[6] + 50.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          fVar10 = (float)param_1[5];
          fVar7 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(0,(float)((float10)(float)(fVar6 * (float10)200.0 + (float10)fVar10) -
                                fVar7 * (float10)100.0),fVar9,fVar11,uVar4,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar4 = 0;
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],0,fVar13);
          fVar11 = (float)param_1[7];
          fVar7 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar11 = (float)((float10)(float)(fVar6 * (float10)200.0 + (float10)fVar11) -
                          fVar7 * (float10)100.0);
          fVar9 = (float)param_1[6] + 50.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          fVar10 = (float)param_1[5];
          fVar7 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(1,(float)((float10)(float)(fVar6 * (float10)200.0 + (float10)fVar10) -
                                fVar7 * (float10)100.0),fVar9,fVar11,uVar4,fVar13);
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
        FUN_0042db10(0,0x41700000);
      }
      if (param_1[0x2b81] < 0x14) {
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
      if (param_1[0x2b81] == 0x14) {
        FUN_0042c8b0(0x7c);
        FUN_004230e0();
        if (param_1[0x1b7] < 2) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x1e) {
          param_1[0x3c] = -0x1e;
        }
        if (0x1e < param_1[0x3c]) {
          param_1[0x3c] = 0x1e;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar13 = (float)param_1[0x3c];
          uVar4 = 0;
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],0,fVar13);
          fVar11 = (float)param_1[7];
          fVar7 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar11 = (float)(fVar7 * (float10)100.0 +
                          (float10)(float)(fVar6 * (float10)200.0 + (float10)fVar11));
          fVar9 = (float)param_1[6] + 50.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          fVar10 = (float)param_1[5];
          fVar7 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(0,(float)(fVar7 * (float10)100.0 +
                                (float10)(float)(fVar6 * (float10)200.0 + (float10)fVar10)),fVar9,
                       fVar11,uVar4,fVar13);
        }
        else {
          fVar13 = (float)param_1[0x3c];
          uVar4 = 0;
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],0,fVar13);
          fVar11 = (float)param_1[7];
          fVar7 = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
          fVar11 = (float)(fVar7 * (float10)100.0 +
                          (float10)(float)(fVar6 * (float10)200.0 + (float10)fVar11));
          fVar9 = (float)param_1[6] + 50.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar9,fVar11);
          fVar10 = (float)param_1[5];
          fVar7 = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
          FUN_00435450(1,(float)(fVar7 * (float10)100.0 +
                                (float10)(float)(fVar6 * (float10)200.0 + (float10)fVar10)),fVar9,
                       fVar11,uVar4,fVar13);
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
      if (param_1[0x2b81] == 0xf) {
        FUN_0042c8b0(0x7c);
        FUN_004230e0();
        if (param_1[0x1b7] < 4) {
          FUN_004223d0(0x1e,10,0);
        }
        else {
          FUN_004223d0(0x1b,10,0);
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          uVar12 = 0;
          uVar4 = 0;
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],0,0);
          fVar11 = (float)(fVar6 * (float10)150.0 + (float10)(float)param_1[7]);
          fVar10 = (float)param_1[6] + 100.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar10,fVar11);
          FUN_00435450(0,(float)(fVar6 * (float10)150.0 + (float10)(float)param_1[5]),fVar10,fVar11,
                       uVar4,uVar12);
        }
        else {
          uVar12 = 0;
          uVar4 = 0;
          fVar6 = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19],0,0);
          fVar11 = (float)(fVar6 * (float10)150.0 + (float10)(float)param_1[7]);
          fVar10 = (float)param_1[6] + 100.0;
          fVar6 = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19],fVar10,fVar11);
          FUN_00435450(1,(float)(fVar6 * (float10)150.0 + (float10)(float)param_1[5]),fVar10,fVar11,
                       uVar4,uVar12);
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
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
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
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] < 0x1b) {
        FUN_00434a70(0,2);
        FUN_00434a70(1,0xffffffff);
      }
      else {
        FUN_00434a70(0,0);
        FUN_00434a70(1,1);
      }
      if (param_1[0x2b81] < 0x10) {
        FUN_0042dc20(0,0x41700000);
      }
      if (param_1[0x2b81] < 0x1b) {
        FUN_0042dc20(0,0x40a00000);
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b81] == 0x1b) {
        FUN_004230e0();
        FUN_004223d0(0x1d,10,0);
        FUN_0042c8b0(0x7d);
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x32 < param_1[0x3c]) {
          param_1[0x3c] = 0x32;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar11 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 2;
          uVar4 = FUN_0064e6c0("Bip01_L_Hand");
          FUN_00435220(uVar4,uVar12,uVar14,fVar11);
        }
        else {
          fVar11 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 3;
          uVar4 = FUN_0064e6c0("Bip01_L_Hand");
          FUN_00435220(uVar4,uVar12,uVar14,fVar11);
        }
      }
      if (param_1[0x2b81] == 9) {
        if (param_1[0x3e] < 0) {
          param_1[0x3e] = param_1[0x3e] + 1;
          return;
        }
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] == 0x1b) {
        param_1[0x2b81] = 0x31;
        param_1[0x2b82] = 0x31;
        return;
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
      if (param_1[0x2b81] == 0) {
        FUN_00422900();
        param_1[0x3e] = 0;
      }
      if (param_1[0x2b81] < 0x1b) {
        FUN_00434a70(0,2);
        FUN_00434a70(1,0xffffffff);
      }
      else {
        FUN_00434a70(0,0);
        FUN_00434a70(1,1);
      }
      param_1[0x16] = 0x3f000000;
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (param_1[0x2b81] < 10) {
        FUN_0042dc20(0,0x41700000);
      }
      if (param_1[0x2b81] < 0x1b) {
        FUN_0042dc20(0,0x40a00000);
      }
      if (param_1[0x2b81] == 0x1b) {
        FUN_004230e0();
        param_1[0x18] = 0;
        param_1[0x10] = 0x41200000;
        param_1[0x15] = -0x3f100000;
        FUN_004223d0(0x1d,10,0);
        FUN_0042c8b0(0x7d);
        FUN_0042da80();
        iVar3 = FUN_0066b668();
        param_1[0x3c] = iVar3;
        if (param_1[0x3c] < -0x28) {
          param_1[0x3c] = -0x28;
        }
        if (0x32 < param_1[0x3c]) {
          param_1[0x3c] = 0x32;
        }
        if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0)) {
          fVar11 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 2;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar12,uVar14,fVar11);
        }
        else {
          fVar11 = (float)param_1[0x3c];
          uVar14 = 0;
          uVar12 = 3;
          uVar4 = FUN_0064e6c0("Bip01_R_Hand");
          FUN_00435220(uVar4,uVar12,uVar14,fVar11);
        }
      }
      if (param_1[0x2b81] == 0x1b) {
        param_1[0x2b81] = 0x31;
        param_1[0x2b82] = 0x31;
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

