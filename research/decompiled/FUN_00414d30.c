// Function: FUN_00414d30
// Address:  0x00414d30
// Source:   batch_decompile (mass dump)
// Hash:     5a0976b982268091


undefined4 __fastcall FUN_00414d30(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_10 [8];
  int local_8;
  
  FUN_00416180();
  if (*(int *)(param_1 + 0x1088) == 1) {
    iVar2 = FUN_00416350(0xc,0xe);
    if (iVar2 == 0xe) {
      for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
        if ((&DAT_006cfb18)[local_8] == 0) {
          FUN_00414670();
        }
        else {
          FUN_0040da90();
        }
      }
      uVar3 = 0xe;
    }
    else {
      uVar3 = 0xc;
    }
  }
  else {
    FUN_00416280(0xc);
    FUN_006584e0();
    FUN_006585f0();
    cVar1 = FUN_006586d0(0x1c);
    if ((cVar1 != '\0') &&
       ((cVar1 = FUN_006586d0(0xb8), cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))))
    {
      FUN_0064ad70();
    }
    cVar1 = FUN_00416330();
    if (cVar1 == '\0') {
      uVar3 = 0xc;
    }
    else {
      cVar1 = FUN_00645e10();
      if (cVar1 == '\0') {
        FUN_00657390();
        if (*(char *)(param_1 + 0x108c) == '\0') {
          if (DAT_006cae9c == 1) {
            FUN_00415ae0(0);
          }
          if (DAT_006caea0 == 1) {
            if (DAT_006cfde1 == -1) {
              FUN_0064aed0(1);
              FUN_00416470();
              FUN_00415d30(0,local_10,0,8);
              return 0xb;
            }
            FUN_00415be0(0);
          }
          if ((DAT_006cae98 == 1) || ((DAT_006cae98 % 6 == 1 && (0x3c < DAT_006cae98)))) {
            FUN_006463c0();
          }
          if ((DAT_006cae98 == -1) || ((-DAT_006cae98 % 6 == 1 && (DAT_006cae98 < -0x3c)))) {
            FUN_00646460();
          }
        }
        else {
          iVar2 = FUN_00403aa0(DAT_006cae94);
          if (iVar2 == 1) {
            if (*(int *)(param_1 + 0x1070) < 2) {
              *(int *)(param_1 + 0x1070) = *(int *)(param_1 + 0x1070) + 2;
            }
            else {
              *(int *)(param_1 + 0x1070) = *(int *)(param_1 + 0x1070) + -2;
            }
            *(undefined1 *)(param_1 + 0x1f1) = *(undefined1 *)(param_1 + 0x1070);
            FUN_00415d30(0,param_1 + 0x188,0,0x88);
          }
          else {
            iVar2 = FUN_00403aa0(DAT_006cae98);
            if (iVar2 == 1) {
              if ((*(int *)(param_1 + 0x1070) == 1) || (*(int *)(param_1 + 0x1070) == 3)) {
                *(int *)(param_1 + 0x1070) = *(int *)(param_1 + 0x1070) + -1;
              }
              else {
                *(int *)(param_1 + 0x1070) = *(int *)(param_1 + 0x1070) + 1;
              }
              *(undefined1 *)(param_1 + 0x1f1) = *(undefined1 *)(param_1 + 0x1070);
              FUN_00415d30(0,param_1 + 0x188,0,0x88);
            }
          }
          if (DAT_006cae9c == 1) {
            switch(*(undefined4 *)(param_1 + 0x1070)) {
            case 0:
              DAT_006cfdd0 = DAT_006cfdd0 + '\x01';
              if ('\b' < DAT_006cfdd0) {
                DAT_006cfdd0 = '\x02';
              }
              break;
            case 1:
              DAT_006cfdf9 = (char)((DAT_006cfdf9 + 1) % 5);
              break;
            case 2:
              DAT_006cfe1c = (char)((DAT_006cfe1c + 1) % 3);
              break;
            case 3:
              DAT_006cfe1e = '\x01' - (DAT_006cfe1e != '\0');
            }
            *(char *)(param_1 + 0x1ec) = DAT_006cfdd0;
            *(char *)(param_1 + 0x1ed) = DAT_006cfdf9;
            *(char *)(param_1 + 0x1ee) = DAT_006cfe1c;
            *(char *)(param_1 + 0x1ef) = DAT_006cfe1e;
            FUN_00415d30(0,param_1 + 0x188,0,0x88);
          }
        }
        if (DAT_006caea8 == 1) {
          *(char *)(param_1 + 0x108c) = '\x01' - (*(char *)(param_1 + 0x108c) != '\0');
          *(undefined1 *)(param_1 + 0x1f0) = *(undefined1 *)(param_1 + 0x108c);
          FUN_00415d30(0,param_1 + 0x188,0,0x88);
        }
        *(int *)(param_1 + 0x1090) = *(int *)(param_1 + 0x1090) + 1;
        if (*(uint *)(param_1 + 0x1090) % 0x1e == 0) {
          FUN_00415d30(0,param_1 + 0x188,0,8);
        }
        uVar3 = 0xc;
      }
      else {
        uVar3 = 0xc;
      }
    }
  }
  return uVar3;
}

