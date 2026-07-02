// Function: FUN_0040e0b0
// Address:  0x0040e0b0
// Source:   batch_decompile (mass dump)
// Hash:     723442e5246e6456


undefined4 __fastcall FUN_0040e0b0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int local_10;
  int local_c;
  int local_8;
  
  cVar1 = FUN_00405250();
  if (cVar1 == '\0') {
    switch(*(undefined4 *)(param_1 + 0x1f0)) {
    case 0:
      *(undefined4 *)(param_1 + 0x1f0) = 1;
      FUN_0065c950();
      uVar2 = 0x15;
      break;
    case 1:
      FUN_006584e0();
      FUN_006585f0();
      cVar1 = FUN_0065c9d0();
      if (cVar1 == '\0') {
        FUN_0065b870("data/bgm/title.ogg");
        uVar2 = 1;
      }
      else {
        for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
          FUN_00657390();
          if (((&DAT_006caeb8)[local_8 * 0x19] == 1) || (cVar1 = FUN_006586d0(1), cVar1 != '\0')) {
            FUN_0065c990();
            FUN_0065b870("data/bgm/title.ogg");
            DAT_006cf3b4 = 100;
            return 1;
          }
        }
        uVar2 = 0x15;
      }
      break;
    case 2:
      *(int *)(param_1 + 500) = *(int *)(param_1 + 500) + 5;
      if (*(int *)(param_1 + 500) == 0xff) {
        *(undefined4 *)(param_1 + 0x1f0) = 3;
      }
      uVar2 = 0x15;
      break;
    case 3:
      FUN_006584e0();
      FUN_006585f0();
      for (local_c = 0; local_c < 4; local_c = local_c + 1) {
        FUN_00657390();
        if ((((&DAT_006cae9c)[local_c * 0x19] == 1) || ((&DAT_006caea0)[local_c * 0x19] == 1)) ||
           ((&DAT_006caeb8)[local_c * 0x19] == 1)) {
          if (-1 < *(int *)(param_1 + 0x200)) {
            *(undefined4 *)(param_1 + 0x1f0) = 4;
            return 0x15;
          }
          FUN_0065b870("data/bgm/title.ogg");
          DAT_006cf3b4 = 100;
          return 1;
        }
      }
      uVar2 = 0x15;
      break;
    case 4:
      *(int *)(param_1 + 500) = *(int *)(param_1 + 500) + -5;
      if (*(int *)(param_1 + 500) == 0) {
        FUN_0064aed0(0x14);
        *(undefined4 *)(param_1 + 0x1f0) = 5;
      }
      uVar2 = 0x15;
      break;
    case 5:
      *(int *)(param_1 + 500) = *(int *)(param_1 + 500) + 5;
      if (*(int *)(param_1 + 500) == 0xff) {
        *(undefined4 *)(param_1 + 0x1f0) = 6;
      }
      uVar2 = 0x15;
      break;
    case 6:
      FUN_006584e0();
      FUN_006585f0();
      for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
        FUN_00657390();
        if ((((&DAT_006cae9c)[local_10 * 0x19] == 1) || ((&DAT_006caea0)[local_10 * 0x19] == 1)) ||
           ((&DAT_006caeb8)[local_10 * 0x19] == 1)) {
          FUN_0065b870("data/bgm/title.ogg");
          DAT_006cf3b4 = 100;
          return 1;
        }
      }
      uVar2 = 0x15;
      break;
    default:
      uVar2 = 0x15;
    }
  }
  else {
    uVar2 = 0x15;
  }
  return uVar2;
}

