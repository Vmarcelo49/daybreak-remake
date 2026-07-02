// ============================================
// Address:  0x00428510
// Original: FUN_00428510
// Status:   unreviewed
// ============================================


void __fastcall FUN_00428510(int *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  param_1[0x1f5] = -1;
  iVar2 = param_1[0x2b7b];
  if (0xc0 < iVar2) {
    if (0xdd < iVar2) {
      if (iVar2 < 0x1f5) {
        if (iVar2 == 500) {
          if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
            (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
            (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
            param_1[0x3a] = 0;
            if (param_1[0x3b] == 0) {
              FUN_00421fe0();
            }
            else {
              FUN_00422060();
            }
            FUN_0042c880(0x31);
            FUN_00422240(0x13,0x1e,0);
            FUN_0042c800(0);
            FUN_0042c840(1);
            param_1[0x15] = 0;
            param_1[0x10] = 0;
          }
          cVar1 = FUN_004218c0();
          if (cVar1 != '\0') {
            FUN_00421080(0);
            if ((char)param_1[0x21] != '\0') {
              return;
            }
            FUN_00421080(0x2b);
            param_1[0x16] = 0x3f000000;
            return;
          }
          if (param_1[0x3b] == 0) {
            param_1[0x20e] = param_1[0xca];
          }
          else {
            iVar2 = FUN_0066b668();
            param_1[0x20e] = iVar2;
          }
          if (param_1[0x3a] == 0) {
            (**(code **)(*param_1 + 0xc))(0x168,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
          }
          param_1[0x3a] = param_1[0x3a] + 1;
          param_1[0x1f0] = 100;
          param_1[0x1f1] = 0x3c;
          param_1[0x1eb] = 0x3c;
          param_1[0x16] = 0;
          param_1[0x18] = 0;
          param_1[0x21d] = 0;
          param_1[0x15] = 0;
        }
        else {
          switch(iVar2) {
          case 0xe6:
          case 0xe7:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0') {
              FUN_00421080(0);
              return;
            }
            if ((char)param_1[0x21] == '\0') {
              FUN_00421080(0x67);
              param_1[0x10] = 0;
              return;
            }
            if (param_1[0x2b81] == 0) {
              if (*(char *)((int)param_1 + 0xaeba) == '\x01') {
                FUN_004223d0(6,0x19,1);
              }
              else {
                FUN_004223d0(8,0x14,0);
              }
              param_1[0x18] = 0;
              param_1[0x15] = 0;
              param_1[0x21d] = 0;
            }
            param_1[0x15] = (int)((float)param_1[0x15] + 1.0);
            if (0.0 < (float)param_1[0x15]) {
              param_1[0x15] = 0;
            }
            break;
          case 0xe9:
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
              param_1[0x18] = 0;
              FUN_0042c800(0);
              FUN_0042c840(1);
              param_1[0x15] = (int)((float)param_1[0x21e] * 0.01);
              param_1[0x21d] = 0;
              param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
              param_1[0x16] = 0x3e99999a;
              param_1[0x3a] = 0;
            }
            if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
              param_1[0x10] = 0;
              param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
              FUN_00421080(0x77);
              FUN_0042c8b0(0x28);
              (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
              (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
              return;
            }
            if (param_1[0x2b7d] < 2) {
              param_1[0x3a] = param_1[0x3a] + 1;
              if (0x3b < param_1[0x3a]) {
                FUN_00421100(2);
                param_1[0x3a] = 0;
                return;
              }
              if (*(char *)((int)param_1 + 0x85) != '\0') {
                (**(code **)(*param_1 + 0xc))(10,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
                FUN_0042c8b0(0x28);
                FUN_00421080(0x71);
                param_1[0x21e] = -0x3e600000;
                param_1[0x21f] = 0x40c00000;
                param_1[0xb] = 0;
                return;
              }
            }
            if (param_1[0x2b7d] == 2) {
              param_1[0x16] = 0x3e99999a;
              param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
              if ((float)param_1[0x15] < 4.0) {
                param_1[0x15] = 0x40800000;
              }
              param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            }
            break;
          case 0xea:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0') {
              FUN_00421080(0x78);
              return;
            }
            if ((char)param_1[0x21] == '\0') {
              FUN_00421080(0xcb);
              return;
            }
            if (param_1[0x2b81] == 0) {
              param_1[0x18] = 0;
              param_1[0x15] = 0x41a00000;
              param_1[0x21d] = 0;
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
            if ((float)param_1[0x15] < 0.0) {
              param_1[0x15] = 0;
            }
          }
        }
      }
      else if (iVar2 == 0x1f5) {
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
          (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
          param_1[0x3a] = 0;
          if (param_1[0x3b] == 0) {
            FUN_00421fe0();
          }
          else {
            FUN_00422060();
          }
          FUN_0042c880(0x31);
          FUN_00422240(0x13,0x1e,0);
          FUN_0042c800(0);
          FUN_0042c840(1);
          param_1[0x15] = 0;
          param_1[0x10] = 0;
        }
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          if ((char)param_1[0x21] != '\0') {
            return;
          }
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        if (param_1[0x3b] == 0) {
          param_1[0x20e] = param_1[0xca];
        }
        else {
          iVar2 = FUN_0066b668();
          param_1[0x20e] = iVar2;
        }
        if (param_1[0x3a] == 0) {
          (**(code **)(*param_1 + 0xc))(0x168,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        }
        param_1[0x3a] = param_1[0x3a] + 1;
        param_1[0x1f0] = 100;
        param_1[0x1f1] = 0x3c;
        param_1[0x1eb] = 0x3c;
        param_1[0x16] = 0;
        param_1[0x18] = 0;
        param_1[0x21d] = 0;
        param_1[0x15] = 0;
      }
      else if (iVar2 == 0x1f6) {
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
          (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
          param_1[0x3a] = 0;
          param_1[0x3e] = 0;
          param_1[0x15] = 0;
          param_1[0x10] = 0;
          param_1[0x16] = 0;
          FUN_00422160();
          FUN_0042c880(0x31);
          uVar3 = FUN_0065d150();
          if (uVar3 % 0x40 == 0) {
            FUN_00422300(0x14,1,0x1e,0);
          }
          else {
            FUN_00422300(0x14,0,0x1e,0);
          }
          FUN_0042c800(0);
          FUN_0042c840(0);
        }
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          if ((char)param_1[0x21] != '\0') {
            return;
          }
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        param_1[0x210] = param_1[0xca];
        if (param_1[0x3a] == 0) {
          (**(code **)(*param_1 + 0xc))(0x168,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        }
        param_1[0x1a1] = 4;
        param_1[0x3a] = param_1[0x3a] + 1;
        param_1[0x1f0] = 100;
        param_1[0x1f1] = 0x3c;
        param_1[0x1eb] = 0x3c;
        param_1[0x1e9] = 9999;
        param_1[0x16] = 0;
        param_1[0x18] = 0;
        param_1[0x21d] = 0;
        param_1[0x15] = 0;
        if ((param_1[0x2b81] == 10) && (param_1[0x3e] < 0x1e)) {
          param_1[0x3e] = param_1[0x3e] + 1;
          return;
        }
      }
      else if (iVar2 == 0x1f7) {
        if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
          (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
          (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
          param_1[0x3a] = 0;
          param_1[0x3e] = 0;
          param_1[0x15] = 0;
          param_1[0x10] = 0;
          param_1[0x16] = 0;
          FUN_00422160();
          FUN_0042c880(0x31);
          uVar3 = FUN_0065d150();
          if (uVar3 % 0x40 == 0) {
            FUN_00422300(0x14,1,0x1e,0);
          }
          else {
            FUN_00422300(0x14,0,0x1e,0);
          }
          FUN_0042c800(0);
          FUN_0042c840(0);
        }
        cVar1 = FUN_004218c0();
        if (cVar1 != '\0') {
          FUN_00421080(0);
          if ((char)param_1[0x21] != '\0') {
            return;
          }
          FUN_00421080(0x2b);
          param_1[0x16] = 0x3f000000;
          return;
        }
        param_1[0x210] = param_1[0xca];
        if (param_1[0x3a] == 0) {
          (**(code **)(*param_1 + 0xc))(0x168,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        }
        param_1[0x3a] = param_1[0x3a] + 1;
        param_1[0x1f0] = 100;
        param_1[0x1f1] = 0x3c;
        param_1[0x1eb] = 0x3c;
        param_1[0x1e9] = 9999;
        param_1[0x16] = 0;
        param_1[0x18] = 0;
        param_1[0x21d] = 0;
        param_1[0x15] = 0;
        if ((param_1[0x2b81] == 10) && (param_1[0x3e] < 0x1e)) {
          param_1[0x3e] = param_1[0x3e] + 1;
          return;
        }
      }
      goto switchD_00428568_caseD_2e;
    }
    if (iVar2 == 0xdd) {
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0x78);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        param_1[0x10] = 0;
        if ((float)param_1[0x15] < 0.0 != ((float)param_1[0x15] == 0.0)) {
          FUN_00421080(0x67);
          return;
        }
        FUN_00421080(0xcb);
        return;
      }
      if (param_1[0x2b81] == 0) {
        FUN_004223d0(8,0x14,0);
        param_1[0x15] = (int)((float)param_1[0x21e] * 0.01);
      }
      if ((0.0 < (float)param_1[0x15]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (((float)param_1[0x15] < 0.0) &&
         (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), 0.0 < (float)param_1[0x15])) {
        param_1[0x15] = 0;
      }
      goto switchD_00428568_caseD_2e;
    }
    switch(iVar2) {
    case 0xc1:
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0xc3);
        param_1[0x10] = 0;
        return;
      }
      if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
        param_1[0x18] = 0;
        param_1[0x15] = 0;
        param_1[0x21d] = 0;
      }
      param_1[0x15] = (int)((float)param_1[0x15] + 1.5);
      if (0.0 < (float)param_1[0x15]) {
        param_1[0x15] = 0;
      }
      if (((param_1[0x2b7d] == 1) && (param_1[0x3a] = param_1[0x3a] + 1, 0x1e < param_1[0x3a])) &&
         (iVar2 = FUN_00421930(), 0 < iVar2)) {
        FUN_00421080(0xc2);
        *(undefined1 *)((int)param_1 + 0xaecb) = 1;
        FUN_00421bd0();
        param_1[0x10] = 0;
        FUN_004219a0();
        return;
      }
      break;
    case 0xc2:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        iVar2 = FUN_00421930();
        if (iVar2 < 0x15) {
          FUN_004223d0(0x11,0x1e,0);
        }
        else {
          FUN_004223d0(0x1a,0x1e,0);
        }
      }
      if (((char)param_1[0x21] != '\0') &&
         ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0))) {
        FUN_00421080(0x2c);
        param_1[0x10] = 0;
        param_1[0x1eb] = 0x3c;
        return;
      }
      param_1[0x21d] = 0x3f800000;
      param_1[0x16] = 0x3f000000;
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      FUN_00421780();
      break;
    case 0xc3:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x18] = 0;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_00421080(0xc4);
        FUN_0042c8b0(0x28);
        return;
      }
      param_1[0x16] = 0x3e99999a;
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      break;
    case 0xc4:
      if ((char)param_1[0x21] == '\0') {
        param_1[0x10] = 0;
        FUN_00421080(0xc3);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x3a] = 0;
      }
      if ((0.0 < (float)param_1[0x15]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
        param_1[0x15] = 0;
      }
      if (((float)param_1[0x15] < 0.0) &&
         (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), 0.0 < (float)param_1[0x15])) {
        param_1[0x15] = 0;
      }
      if (param_1[0x2b7d] == 1) {
        param_1[0x1f0] = 100;
        param_1[0x1eb] = 0x1e;
        param_1[0x1f1] = 0;
        param_1[0x3a] = param_1[0x3a] + 1;
        if (0x1e < param_1[0x3a]) {
          FUN_004219a0();
          return;
        }
      }
      break;
    case 0xc5:
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0xc3);
        param_1[0x10] = 0;
        return;
      }
      if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
        param_1[0x18] = 0;
        param_1[0x15] = -0x3e900000;
        param_1[0x21d] = 0;
      }
      param_1[0x15] = (int)((float)param_1[0x15] + 1.5);
      if (0.0 < (float)param_1[0x15]) {
        param_1[0x15] = 0;
      }
      if (((param_1[0x2b7d] == 1) && (param_1[0x3a] = param_1[0x3a] + 1, 0x1e < param_1[0x3a])) &&
         (iVar2 = FUN_00421930(), 0 < iVar2)) {
        FUN_00421080(0xc2);
        *(undefined1 *)((int)param_1 + 0xaecb) = 1;
        FUN_00421bd0();
        param_1[0x10] = 0;
        FUN_004219a0();
        return;
      }
      break;
    case 0xc6:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422240(10,0x1e,0);
        param_1[0x18] = 0;
        param_1[0x21d] = 0;
        param_1[0x15] = -0x3e100000;
        param_1[0x10] = 0x41a00000;
        param_1[0x16] = 0x3e99999a;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_00421080(0xc4);
        FUN_0042c8b0(0x28);
        return;
      }
      if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
        FUN_00421100(2);
        return;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if ((float)param_1[0x15] < -4.0) {
        param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
      }
      break;
    case 199:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_00422240(10,0x1e,0);
        param_1[0x18] = 0;
        param_1[0x21d] = 0;
        param_1[0x15] = -0x3e100000;
        param_1[0x10] = 0x41a00000;
        param_1[0x16] = 0x3e99999a;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_00421080(0xc4);
        FUN_0042c8b0(0x28);
        return;
      }
      if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
        FUN_00421100(2);
        return;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if ((float)param_1[0x15] < -4.0) {
        param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
      }
      break;
    case 200:
    case 0xc9:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        param_1[0x10] = 0;
        param_1[0x16] = 0x3e99999a;
        FUN_00421080(0xcb);
        return;
      }
      if (param_1[0x2b81] == 0) {
        if (*(char *)((int)param_1 + 0xaeba) == '\x01') {
          FUN_004223d0(6,0x19,1);
        }
        else {
          FUN_004223d0(8,0x14,0);
        }
        param_1[0x18] = 0;
        param_1[0x15] = 0x41c80000;
        param_1[0x21d] = 0;
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      break;
    case 0xca:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if ((char)param_1[0x21] == '\0') {
        FUN_00421080(0x67);
        return;
      }
      if (param_1[0x2b81] == 0) {
        if (*(char *)((int)param_1 + 0xaeba) == '\x01') {
          FUN_004223d0(6,0x19,1);
        }
        else {
          FUN_004223d0(8,0x14,0);
        }
        param_1[0x18] = 0;
        param_1[0x15] = 0x41a00000;
        param_1[0x21d] = 0;
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      break;
    case 0xcb:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        param_1[0x10] = 0;
      }
      if ((5.0 < (float)param_1[0x15]) &&
         (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 5.0)) {
        param_1[0x15] = 0x40a00000;
      }
      if (((float)param_1[0x15] < -5.0) &&
         (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), -5.0 < (float)param_1[0x15])) {
        param_1[0x15] = -0x3f600000;
      }
      param_1[0x16] = 0x3e99999a;
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        FUN_00421080(0x77);
        return;
      }
      break;
    case 0xcc:
      cVar1 = FUN_004218c0();
      if (cVar1 != '\0') {
        FUN_00421080(0);
        return;
      }
      if (((char)param_1[0x21] == '\0') && (0 < param_1[0x2b7d])) {
        FUN_00421080(0xcb);
        return;
      }
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_004223d0(0x1f,0x14,0);
        FUN_0042c8b0(0x21);
        param_1[0x18] = 0;
        param_1[0x15] = 0;
      }
      if ((param_1[0x2b7d] == 0) && (0x3c < param_1[0x2b81])) {
        FUN_00421100(1);
        param_1[0x15] = 0x41700000;
        return;
      }
      param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
      if ((float)param_1[0x15] < 0.0) {
        param_1[0x15] = 0;
      }
      break;
    case 0xcd:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        FUN_004223d0(0x1f,0x14,0);
        FUN_0042c8b0(0x21);
        param_1[0x18] = 0;
        param_1[0x15] = 0;
        param_1[0x10] = 0;
      }
      if ((param_1[0x2b7d] == 0) && (0x3c < param_1[0x2b81])) {
        FUN_00421100(1);
        param_1[0x15] = (int)((float)param_1[0x21e] * 0.01);
        param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
        param_1[0x16] = 0x3e99999a;
        return;
      }
      if ((((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) && (0 < param_1[0x2b7d]))
      {
        param_1[0x10] = 0;
        FUN_00421080(0x77);
        FUN_0042c8b0(0x28);
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        return;
      }
      if (0 < param_1[0x2b7d]) {
        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      }
      if (4.0 < (float)param_1[0x15]) {
        param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
      }
      break;
    case 0xce:
      if (param_1[0x2b81] == 0) {
        FUN_004223d0(0xb,0x14,1);
        FUN_0042c8b0(0x24);
        param_1[0x18] = 0;
        param_1[0x15] = 0;
        param_1[0x10] = 0x41100000;
        param_1[0x16] = 0x3f19999a;
        param_1[0x21d] = 0;
      }
      if (param_1[0x1f7] == 0) {
        FUN_00421080(0x2b);
        return;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        FUN_00421080(0x6b);
        return;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (0.0 < (float)param_1[0x15]) {
        param_1[0x15] = 0;
      }
      break;
    case 0xd5:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        if (*(char *)((int)param_1 + 0xaeba) == '\x01') {
          FUN_004223d0(6,0x19,1);
        }
        else if (*(char *)((int)param_1 + 0xaebb) == '\0') {
          *(undefined1 *)((int)param_1 + 0xaebb) = 1;
          FUN_004223d0(9,0x14,0);
        }
        else {
          FUN_004223d0(8,0x14,0);
        }
        param_1[0x18] = 0;
        param_1[0x15] = (int)((float)param_1[0x21e] * 0.01);
        param_1[0x21d] = 0;
        param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
        param_1[0x16] = 0x3e99999a;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_00421080(0x77);
        FUN_0042c8b0(0x28);
        return;
      }
      if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
        FUN_00421100(2);
        return;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (4.0 < (float)param_1[0x15]) {
        param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
      }
      iVar2 = param_1[0x2b7d];
      goto joined_r0x0042b829;
    case 0xd6:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        if (*(char *)((int)param_1 + 0xaeba) == '\x01') {
          FUN_004223d0(6,0x19,1);
        }
        else if (*(char *)((int)param_1 + 0xaebb) == '\0') {
          *(undefined1 *)((int)param_1 + 0xaebb) = 1;
          FUN_004223d0(9,0x14,0);
        }
        else {
          FUN_004223d0(8,0x14,0);
        }
        param_1[0x18] = 0;
        param_1[0x15] = (int)((float)param_1[0x21e] * 0.01);
        param_1[0x21d] = 0;
        param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
        param_1[0x16] = 0x3e99999a;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_00421080(0x77);
        FUN_0042c8b0(0x28);
        return;
      }
      if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
        FUN_00421100(2);
        return;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (4.0 < (float)param_1[0x15]) {
        param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
      }
      iVar2 = param_1[0x2b7d];
      goto joined_r0x0042b829;
    case 0xd7:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        *(undefined1 *)((int)param_1 + 0xaebb) = 1;
        FUN_004223d0(9,0x14,0);
        param_1[0x18] = 0;
        param_1[0x15] = (int)((float)param_1[0x21e] * 0.01);
        param_1[0x21d] = 0;
        param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
        param_1[0x16] = 0x3e99999a;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_00421080(0x77);
        FUN_0042c8b0(0x28);
        return;
      }
      if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
        FUN_00421100(2);
        return;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if (4.0 < (float)param_1[0x15]) {
        param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
      }
      break;
    case 0xd8:
      if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
        if (*(char *)((int)param_1 + 0xaeba) == '\x01') {
          FUN_004223d0(6,0x19,1);
        }
        else if (*(char *)((int)param_1 + 0xaebb) == '\0') {
          *(undefined1 *)((int)param_1 + 0xaebb) = 1;
          FUN_004223d0(9,0x14,0);
        }
        else {
          FUN_004223d0(8,0x14,0);
        }
        param_1[0x18] = 0;
        param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
        param_1[0x21d] = 0;
        param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
        param_1[0x16] = 0x3f800000;
      }
      if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
        param_1[0x10] = 0;
        (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_00421080(0x77);
        FUN_0042c8b0(0x28);
        return;
      }
      if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
        FUN_00421100(2);
        return;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
      if ((float)param_1[0x15] < -4.0) {
        param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
      }
      iVar2 = param_1[0x2b7d];
      goto joined_r0x0042b829;
    }
    goto switchD_00428568_caseD_2e;
  }
  if (iVar2 == 0xc0) {
    if ((char)param_1[0x21] == '\0') {
      FUN_00421080(0xc3);
      param_1[0x10] = 0;
      return;
    }
    if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0)) {
      param_1[0x18] = 0;
      param_1[0x15] = -0x3e600000;
      param_1[0x21d] = 0;
    }
    param_1[0x15] = (int)((float)param_1[0x15] + 0.5);
    if (0.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0;
    }
    if (((param_1[0x2b7d] == 1) && (param_1[0x3a] = param_1[0x3a] + 1, 0x1e < param_1[0x3a])) &&
       (iVar2 = FUN_00421930(), 0 < iVar2)) {
      FUN_00421080(0xc2);
      *(undefined1 *)((int)param_1 + 0xaecb) = 1;
      FUN_00421bd0();
      param_1[0x10] = 0;
      FUN_004219a0();
      return;
    }
    goto switchD_00428568_caseD_2e;
  }
  switch(iVar2) {
  case 0x2d:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0);
      return;
    }
    if (param_1[0x2b81] == 0) {
      FUN_004223d0(0x17,0x14,0);
      param_1[0x1eb] = 0;
      param_1[0x1ec] = 0;
      param_1[0x1f0] = 0;
      param_1[0x1ee] = 0;
    }
    if (param_1[0x2b81] < 0x1a) {
      param_1[0x10] = (int)((float)param_1[0x10] - 1.0);
      if ((float)param_1[0x15] < -10.0) {
        param_1[0x15] = (int)((float)param_1[0x15] + 0.5);
      }
    }
    else {
      param_1[0x10] = 0;
    }
    if (param_1[0x2b81] == 0) {
      param_1[0x18] = 0;
      param_1[0x15] = -0x3e380000;
      param_1[0x10] = 0x41480000;
    }
    if ((param_1[0x2b81] == 0x19) && ((char)param_1[0x21] == '\0')) {
      return;
    }
    if (param_1[0x2b81] == 0x1a) {
      param_1[0x15] = 0;
    }
    break;
  case 100:
  case 0x65:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      FUN_00421080(0x67);
      param_1[0x10] = 0;
      return;
    }
    if (param_1[0x2b81] == 0) {
      FUN_004223d0(8,0x14,0);
      param_1[0x18] = 0;
      param_1[0x15] = -0x3e380000;
      param_1[0x21d] = 0;
    }
    param_1[0x15] = (int)((float)param_1[0x15] + 1.5);
    if (0.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0;
    }
    break;
  case 0x66:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      FUN_00421080(0x67);
      param_1[0x10] = 0;
      return;
    }
    if (param_1[0x2b81] == 0) {
      FUN_004223d0(8,0x14,0);
      param_1[0x18] = 0;
      param_1[0x15] = -0x3e600000;
      param_1[0x21d] = 0;
    }
    param_1[0x15] = (int)((float)param_1[0x15] + 0.5);
    if (0.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0;
    }
    break;
  case 0x67:
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      param_1[0x10] = 0;
    }
    if ((5.0 < (float)param_1[0x15]) &&
       (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 5.0)) {
      param_1[0x15] = 0x40a00000;
    }
    if (((float)param_1[0x15] < -5.0) &&
       (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), -5.0 < (float)param_1[0x15])) {
      param_1[0x15] = -0x3f600000;
    }
    param_1[0x16] = 0x3e99999a;
    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
      param_1[0x10] = 0;
      FUN_00421080(0x76);
      return;
    }
    break;
  case 0x68:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0);
      return;
    }
    if (((char)param_1[0x21] == '\0') && (0 < param_1[0x2b7d])) {
      param_1[0x10] = 0;
      FUN_00421080(0x67);
      return;
    }
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      FUN_004223d0(0x1f,0x14,0);
      FUN_0042c8b0(0x21);
      param_1[0x18] = 0;
      param_1[0x15] = 0;
    }
    if ((param_1[0x2b7d] == 0) && (0x3c < param_1[0x2b81])) {
      FUN_00421100(1);
      param_1[0x15] = -0x3e900000;
      return;
    }
    param_1[0x15] = (int)((float)param_1[0x15] + 1.5);
    if (0.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0;
    }
    break;
  case 0x69:
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      FUN_004223d0(0x1f,0x14,0);
      FUN_0042c8b0(0x21);
      param_1[0x18] = 0;
      param_1[0x15] = 0;
      param_1[0x10] = 0;
    }
    if ((param_1[0x2b7d] == 0) && (0x3c < param_1[0x2b81])) {
      FUN_00421100(1);
      param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
      param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
      param_1[0x16] = 0x3e99999a;
      return;
    }
    if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) {
      param_1[0x16] = 0x3e99999a;
    }
    if ((((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) && (0 < param_1[0x2b7d])) {
      param_1[0x10] = 0;
      FUN_00421080(0x76);
      FUN_0042c8b0(0x28);
      (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      return;
    }
    if (0 < param_1[0x2b7d]) {
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    }
    if ((float)param_1[0x15] < -4.0) {
      param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
    }
    break;
  case 0x6a:
    if (param_1[0x2b81] == 0) {
      FUN_004223d0(0xb,0x14,1);
      FUN_0042c8b0(0x24);
      param_1[0x18] = 0;
      param_1[0x15] = 0;
      param_1[0x10] = 0x41100000;
      param_1[0x16] = 0x3f19999a;
      param_1[0x21d] = 0;
    }
    if (param_1[0x1f7] == 0) {
      FUN_00421080(0x2b);
      return;
    }
    if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
      FUN_00421080(0x6b);
      param_1[0x10] = 0;
      return;
    }
    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    if (0.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0;
    }
    break;
  case 0x6b:
    if (param_1[0x1f7] == 0) {
      FUN_00421080(0);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      FUN_00421080(0x6c);
      param_1[0x10] = 0;
      return;
    }
    if (param_1[0x2b81] == 0) {
      param_1[0x18] = 0;
      param_1[0x21d] = 0;
    }
    param_1[0x21d] = 0x40000000;
    FUN_00421780();
    param_1[0x15] = 0x41a00000;
    break;
  case 0x6c:
    if (param_1[0x1f7] == 0) {
      FUN_00421080(0x2b);
      return;
    }
    if ((char)param_1[0x21] != '\0') {
      FUN_00421080(0x6b);
      param_1[0x10] = 0;
      return;
    }
    if (param_1[0x2b81] == 0) {
      param_1[0x16] = 0x3f000000;
      param_1[0x10] = 0;
      param_1[0x21d] = 0;
    }
    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    if (10.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0x41200000;
    }
    break;
  case 0x71:
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      param_1[0x18] = 0;
      param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
      param_1[0x21d] = 0;
      param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
      param_1[0x16] = 0x3e99999a;
      if (*(char *)((int)param_1 + 0xaebb) == '\0') {
        FUN_004223d0(9,0x14,0);
        *(undefined1 *)((int)param_1 + 0xaebb) = 1;
      }
      else {
        FUN_004223d0(8,0x14,0);
      }
    }
    if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
      if ((param_1[0x1f0] < 100) && (param_1[0xa0] != 0)) {
        FUN_00421080(0x2d);
        param_1[0x1eb] = 1;
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        return;
      }
      (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      param_1[0x10] = 0;
      FUN_00421080(0x76);
      FUN_0042c8b0(0x28);
      return;
    }
    if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
      FUN_00421100(2);
      return;
    }
    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    if ((float)param_1[0x15] < -4.0) {
      param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
    }
    iVar2 = param_1[0x2b7d];
    goto joined_r0x0042b829;
  case 0x72:
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      if (*(char *)((int)param_1 + 0xaebb) == '\0') {
        FUN_004223d0(9,0x14,0);
        *(undefined1 *)((int)param_1 + 0xaebb) = 1;
      }
      else {
        FUN_004223d0(8,0x14,0);
      }
      param_1[0x18] = 0;
      param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
      param_1[0x21d] = 0;
      param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
      param_1[0x16] = 0x3e99999a;
    }
    if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
      if ((param_1[0x1f0] < 100) && (param_1[0xa0] != 0)) {
        FUN_00421080(0x2d);
        param_1[0x1eb] = 1;
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        return;
      }
      (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      param_1[0x10] = 0;
      FUN_00421080(0x76);
      FUN_0042c8b0(0x28);
      return;
    }
    if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
      FUN_00421100(2);
      return;
    }
    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    if ((float)param_1[0x15] < -4.0) {
      param_1[0x15] = (int)((float)param_1[0x15] + 0.5);
    }
    iVar2 = param_1[0x2b7d];
    goto joined_r0x0042b829;
  case 0x73:
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      FUN_004223d0(9,0x14,0);
      *(undefined1 *)((int)param_1 + 0xaebb) = 1;
      param_1[0x18] = 0;
      param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
      param_1[0x21d] = 0;
      param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
      param_1[0x16] = 0x3e99999a;
    }
    if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
      if ((param_1[0x1f0] < 100) && (param_1[0xa0] != 0)) {
        FUN_00421080(0x2d);
        param_1[0x1eb] = 1;
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        return;
      }
      param_1[0x10] = 0;
      (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      FUN_00421080(0x76);
      FUN_0042c8b0(0x28);
      return;
    }
    if ((((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) && (param_1[0x2b81] % 0x11 == 0)) {
      FUN_00421100(2);
      return;
    }
    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    if ((float)param_1[0x15] < -4.0) {
      param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
    }
    break;
  case 0x74:
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      if (*(char *)((int)param_1 + 0xaebb) == '\0') {
        FUN_004223d0(9,0x14,0);
        *(undefined1 *)((int)param_1 + 0xaebb) = 1;
      }
      else {
        FUN_004223d0(8,0x14,0);
      }
      param_1[0x18] = 0;
      param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
      param_1[0x21d] = 0;
      param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
      param_1[0x16] = 0x3f800000;
    }
    if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
      if ((param_1[0x1f0] < 100) && (param_1[0xa0] != 0)) {
        FUN_00421080(0x2d);
        param_1[0x1eb] = 1;
        param_1[0x10] = 0;
        param_1[0x15] = 0;
        return;
      }
      (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      param_1[0x10] = 0;
      FUN_00421080(0x76);
      FUN_0042c8b0(0x28);
      return;
    }
    if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1)) {
      FUN_00421100(2);
      return;
    }
    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    if ((float)param_1[0x15] < -4.0) {
      param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
    }
    iVar2 = param_1[0x2b7d];
joined_r0x0042b829:
    if (iVar2 == 3) {
      return;
    }
    break;
  case 0x76:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0x78);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      param_1[0x10] = 0;
      if ((float)param_1[0x15] < 0.0 != ((float)param_1[0x15] == 0.0)) {
        FUN_00421080(0x67);
        return;
      }
      FUN_00421080(0xcb);
      return;
    }
    if ((0.0 < (float)param_1[0x15]) &&
       (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
      param_1[0x15] = 0;
    }
    if (((float)param_1[0x15] < 0.0) &&
       (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), 0.0 < (float)param_1[0x15])) {
      param_1[0x15] = 0;
    }
    break;
  case 0x77:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0x78);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      param_1[0x10] = 0;
      if ((float)param_1[0x15] < 0.0 != ((float)param_1[0x15] == 0.0)) {
        FUN_00421080(0x67);
        return;
      }
      FUN_00421080(0xcb);
      return;
    }
    if ((0.0 < (float)param_1[0x15]) &&
       (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
      param_1[0x15] = 0;
    }
    if (((float)param_1[0x15] < 0.0) &&
       (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), 0.0 < (float)param_1[0x15])) {
      param_1[0x15] = 0;
    }
    break;
  case 0x78:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) {
        FUN_00421080(0x80);
        return;
      }
      FUN_00421080(0x7c);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      param_1[0x10] = 0;
      if ((float)param_1[0x15] < 0.0 != ((float)param_1[0x15] == 0.0)) {
        FUN_00421080(0x67);
        return;
      }
      FUN_00421080(0xcb);
      return;
    }
    if ((0.0 < (float)param_1[0x15]) &&
       (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
      param_1[0x15] = 0;
    }
    if (((float)param_1[0x15] < 0.0) &&
       (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), 0.0 < (float)param_1[0x15])) {
      param_1[0x15] = 0;
    }
    break;
  case 0x79:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0x78);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      param_1[0x10] = 0;
      if ((float)param_1[0x15] < 0.0 != ((float)param_1[0x15] == 0.0)) {
        FUN_00421080(0x67);
        return;
      }
      FUN_00421080(0xcb);
      return;
    }
    if (param_1[0x2b81] == 0) {
      FUN_004223d0(8,0x14,0);
      param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
    }
    if ((0.0 < (float)param_1[0x15]) &&
       (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
      param_1[0x15] = 0;
    }
    if (((float)param_1[0x15] < 0.0) &&
       (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), 0.0 < (float)param_1[0x15])) {
      param_1[0x15] = 0;
    }
    break;
  case 0x7c:
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
    if (param_1[0x1fd] < 1) {
      param_1[0x20d] = param_1[0x20d] + 0x28;
    }
    else {
      param_1[0x20d] = param_1[0x20d] + 5;
    }
    if (1000 < param_1[0x20d]) {
      param_1[0x20d] = 1000;
    }
    if (param_1[0x2b7d] == 0) {
      param_1[0x3a] = 0;
      param_1[0x18] = 0;
      param_1[0x21d] = 0x43340000;
      FUN_00421780();
    }
    if (param_1[0x2b7d] == 1) {
      param_1[0x21d] = 0x40400000;
      FUN_00421780();
      param_1[0x15] = 0x41200000;
      param_1[0x3a] = param_1[0x3a] + 1;
      if ((0x96 < param_1[0x3a]) ||
         ((0x1e < param_1[0x3a] &&
          (((param_1[0xa1] != 0 || (param_1[0xa2] != 0)) || (param_1[0xa0] != 0)))))) {
        FUN_00421100(2);
        return;
      }
    }
    if (param_1[0x2b7d] == 2) {
      param_1[0x15] = 0;
      param_1[0x21d] = 0x40c00000;
    }
    break;
  case 0x80:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      param_1[0x10] = 0;
      FUN_00421080(0x2b);
      param_1[0x16] = 0x3f000000;
      return;
    }
    param_1[0x15] = 0;
    break;
  case 0x82:
  case 0x83:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      FUN_00421080(0x67);
      param_1[0x10] = 0;
      return;
    }
    if (param_1[0x2b81] == 0) {
      FUN_004223d0(8,0x14,0);
      param_1[0x18] = 0;
      param_1[0x15] = 0;
      param_1[0x21d] = 0;
    }
    param_1[0x15] = (int)((float)param_1[0x15] + 1.0);
    if (0.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0;
    }
    break;
  case 0x85:
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      param_1[0x18] = 0;
      FUN_0042c800(0);
      FUN_0042c840(1);
      param_1[0x15] = (int)(-(float)param_1[0x21e] * 0.01);
      param_1[0x21d] = 0;
      param_1[0x10] = (int)((float)param_1[0x21f] * 0.01);
      param_1[0x16] = 0x3e99999a;
      param_1[0x3a] = 0;
    }
    if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0)) {
      param_1[0x10] = 0;
      param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
      FUN_00421080(0x76);
      FUN_0042c8b0(0x28);
      (**(code **)(*param_1 + 0xc))(300,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      (**(code **)(*param_1 + 0xc))(0x136,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
      return;
    }
    if (param_1[0x2b7d] < 2) {
      param_1[0x3a] = param_1[0x3a] + 1;
      if (0x3b < param_1[0x3a]) {
        FUN_00421100(2);
        param_1[0x3a] = 0;
        return;
      }
      if (*(char *)((int)param_1 + 0x85) != '\0') {
        (**(code **)(*param_1 + 0xc))(10,param_1[5],param_1[6],param_1[7],param_1[0x17],0);
        FUN_0042c8b0(0x28);
        FUN_00421080(0x71);
        param_1[0x21e] = 0x41a00000;
        param_1[0x21f] = 0x40c00000;
        param_1[0xb] = 0;
        return;
      }
    }
    if (param_1[0x2b7d] == 2) {
      param_1[0x16] = 0x3e99999a;
      param_1[0x15] = (int)((float)param_1[0x15] + 0.25);
      if (-4.0 < (float)param_1[0x15]) {
        param_1[0x15] = -0x3f800000;
      }
      param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
    }
    break;
  case 0x86:
    cVar1 = FUN_004218c0();
    if (cVar1 != '\0') {
      FUN_00421080(0x78);
      return;
    }
    if ((char)param_1[0x21] == '\0') {
      param_1[0x10] = 0;
      param_1[0x16] = 0x3f000000;
      FUN_00421080(0x67);
      return;
    }
    if (param_1[0x2b81] == 0) {
      param_1[0x18] = 0;
      param_1[0x15] = -0x3e600000;
      param_1[0x21d] = 0;
    }
    param_1[0x15] = (int)((float)param_1[0x15] + 0.5);
    if (0.0 < (float)param_1[0x15]) {
      param_1[0x15] = 0;
    }
    break;
  case 0xbc:
    if (param_1[0x2b81] < 0x28) {
      param_1[0x2b81] = 0x28;
      param_1[0x2b82] = 0x28;
      return;
    }
    if (param_1[0x2b81] == 0x37) {
      param_1[0x2b81] = param_1[0x2b81] + -1;
      param_1[0x2b82] = param_1[0x2b82] + -1;
    }
    break;
  case 0xbd:
    param_1[0x2b81] = 0x11;
    param_1[0x2b82] = 0x11;
    return;
  case 0xbf:
    if ((char)param_1[0x21] == '\0') {
      param_1[0x10] = 0;
      FUN_00421080(0xc3);
      return;
    }
    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0)) {
      param_1[0x3a] = 0;
      param_1[0x15] = -0x3e600000;
    }
    if (param_1[0x2b7d] == 1) {
      param_1[0x1f0] = 100;
      param_1[0x1eb] = 0x1e;
      param_1[0x1f1] = 0;
      param_1[0x3a] = param_1[0x3a] + 1;
      if ((0x1e < param_1[0x3a]) && (iVar2 = FUN_00421930(), 0 < iVar2)) {
        FUN_004219a0();
        return;
      }
    }
    if ((0.0 < (float)param_1[0x15]) &&
       (param_1[0x15] = (int)((float)param_1[0x15] - 0.25), (float)param_1[0x15] < 0.0)) {
      param_1[0x15] = 0;
    }
    if (((float)param_1[0x15] < 0.0) &&
       (param_1[0x15] = (int)((float)param_1[0x15] + 0.25), 0.0 < (float)param_1[0x15])) {
      param_1[0x15] = 0;
    }
  }
switchD_00428568_caseD_2e:
  param_1[0x2b81] = param_1[0x2b81] + 1;
  param_1[0x2b82] = param_1[0x2b82] + 1;
  FUN_004212f0();
  if ((*(int *)param_1[0x2b79] < param_1[0x2b81]) && (*(int *)(param_1[0x2b79] + 0x20) == 0)) {
    FUN_00421100(param_1[0x2b7d] + 1);
  }
  return;
}

