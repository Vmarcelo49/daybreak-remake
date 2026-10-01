// Function: FUN_0064d5e0
// Address:  0x0064d5e0
// Source:   batch_decompile (mass dump)
// Hash:     0350e2ea3445d31c


LRESULT FUN_0064d5e0(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  char cVar1;
  LRESULT LVar2;
  
  cVar1 = FUN_00661350(param_1,param_2,param_3,param_4);
  if (cVar1 != '\0') {
    return 0;
  }
  if (param_2 < 0x105) {
    if (param_2 == 0x104) {
      if (param_3 == 0x73) {
        LVar2 = DefWindowProcA(param_1,0x104,0x73,param_4);
        return LVar2;
      }
    }
    else if (param_2 == 1) {
      DAT_006d11a0 = 1;
    }
    else if (param_2 == 2) {
      PostQuitMessage(0);
    }
    else if (param_2 != 0x12) goto LAB_0064d6bd;
  }
  else if (param_2 != 0x105) {
    if (param_2 != 0x112) {
LAB_0064d6bd:
      LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
      return LVar2;
    }
    if (param_3 != 0xf140) {
      LVar2 = DefWindowProcA(param_1,0x112,param_3,param_4);
      return LVar2;
    }
  }
  return 0;
}

