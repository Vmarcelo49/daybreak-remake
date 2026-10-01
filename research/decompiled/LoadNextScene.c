// Function: LoadNextScene
// Address:  0x00406310
// Reason:   keyword:Load


uint __fastcall LoadNextScene(int pGameState)

{
  char cVar1;
  uint uVar2;
  int local_playerCase3;
  int local_player;
  
  *(int *)(pGameState + 0x2e14) = *(int *)(pGameState + 0x2e14) + 1;
  FUN_006584e0();
  FUN_006585f0();
  cVar1 = FUN_006586d0(0x1c);
  if ((cVar1 != '\0') &&
     ((cVar1 = FUN_006586d0(0xb8), cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0')))) {
    FUN_0064ad70();
  }
  switch(*(undefined4 *)(pGameState + 0x2e18)) {
  case 0:
    FUN_00657390();
    if (DAT_006cae9c == 1) {
      for (local_player = 0; local_player < 2; local_player = local_player + 1) {
        *(undefined4 *)(pGameState + 0x2e28 + local_player * 4) = 0xffffffff;
        *(undefined4 *)(pGameState + 0x2e30 + local_player * 4) = 0;
        *(undefined4 *)(pGameState + 0x2e38 + local_player * 4) = 0;
        *(undefined4 *)(pGameState + 0x2e90 + local_player * 4) = 0xffffffff;
        *(undefined4 *)(pGameState + 0x2e98 + local_player * 4) = 0;
        *(undefined4 *)(pGameState + 0x2ea0 + local_player * 4) = 0xffffffff;
        *(undefined4 *)(pGameState + 0x2e50 + local_player * 4) = 0xffffffff;
        *(undefined4 *)(pGameState + 0x2e60 + local_player * 4) = 0xffffffff;
        *(undefined4 *)(pGameState + 0x2e70 + local_player * 4) = 0xffffffff;
        *(undefined4 *)(pGameState + 0x2e80 + local_player * 4) = 0;
        *(undefined4 *)(pGameState + 0x2e40 + local_player * 4) = 0xffffffff;
        *(undefined1 *)(pGameState + local_player + 0x2ea8) = 0;
      }
      *(undefined4 *)(pGameState + 0x2e28) = 0;
      FUN_0064aed0(0);
      FUN_00408050(0,(int)(char)(&DAT_006b710c)[*(int *)(pGameState + 0x2e20) * 2]);
      FUN_00408050(1,(int)(char)(&DAT_006b710d)[*(int *)(pGameState + 0x2e20) * 2]);
      *(undefined4 *)(pGameState + 0x2e18) = 1;
    }
    else if (DAT_006caea0 == 1) {
      FUN_0064aed0(1);
      FUN_0065b870("data/bgm/title.ogg");
      return 1;
    }
    if (DAT_006cae94 == 1) {
      *(int *)(pGameState + 0x2e20) = (int)(char)(&DAT_006b719c)[*(int *)(pGameState + 0x2e20)];
      FUN_0064aed0(2);
    }
    else if (DAT_006cae94 == -1) {
      *(int *)(pGameState + 0x2e20) = (int)(char)(&DAT_006b7190)[*(int *)(pGameState + 0x2e20)];
      FUN_0064aed0(2);
    }
    else if (DAT_006cae98 == 1) {
      *(int *)(pGameState + 0x2e20) = (int)(char)(&DAT_006b71b4)[*(int *)(pGameState + 0x2e20)];
      FUN_0064aed0(2);
    }
    else if (DAT_006cae98 == -1) {
      *(int *)(pGameState + 0x2e20) = (int)(char)(&DAT_006b71a8)[*(int *)(pGameState + 0x2e20)];
      FUN_0064aed0(2);
    }
    break;
  case 1:
    FUN_00406850(0);
    FUN_00406850(1);
    break;
  case 2:
    FUN_0065d670();
    if (*(char *)(pGameState + 0x2ebc) == -1) {
      *(undefined4 *)(pGameState + 0x2e18) = 3;
    }
    FUN_0065d6a0();
    if (*(char *)(pGameState + 0x2ebc) != -1) {
      *(char *)(pGameState + 0x2ebc) = *(char *)(pGameState + 0x2ebc) + '\x0f';
    }
    break;
  case 3:
    for (local_playerCase3 = 0; local_playerCase3 < 2; local_playerCase3 = local_playerCase3 + 1) {
      if (*(char *)(pGameState + local_playerCase3 + 0x2ea8) == '\0') {
        (&DAT_006cfb4c)[local_playerCase3] = 0;
        uVar2 = FUN_0065d150();
        (&DAT_006cfb48)[local_playerCase3] = (char)((ulonglong)uVar2 % 3);
        uVar2 = FUN_0065d150();
        *(int *)(&DAT_006cfb38 + local_playerCase3 * 4) = (int)(char)((ulonglong)uVar2 % 3);
        if (((&DAT_006b710c)[*(int *)(pGameState + 0x2e20) * 2] == '\0') ||
           ((&DAT_006b710c)[*(int *)(pGameState + 0x2e20) * 2 + local_playerCase3] == '\x04')) {
          uVar2 = FUN_0065d150();
          *(uint *)(&DAT_006cfb38 + local_playerCase3 * 4) = uVar2 % 2;
        }
        (&DAT_006cfaf8)[local_playerCase3] = 4;
      }
      else {
        (&DAT_006cfb48)[local_playerCase3] =
             *(undefined1 *)(pGameState + 0x2e70 + local_playerCase3 * 4);
        *(undefined4 *)(&DAT_006cfb38 + local_playerCase3 * 4) =
             *(undefined4 *)(pGameState + 0x2e60 + local_playerCase3 * 4);
        (&DAT_006cfaf8)[local_playerCase3] =
             *(undefined4 *)(pGameState + 0x2e40 + local_playerCase3 * 4);
        (&DAT_006cfb4c)[local_playerCase3] =
             *(undefined1 *)(pGameState + 0x2e80 + local_playerCase3 * 4);
      }
    }
    if ((DAT_006cfaf8 == 4) && (DAT_006cfafc == 4)) {
      DAT_006cfaf8 = 0;
    }
    DAT_006cfba0 = (uint)(DAT_006cfaf8 != 4) + (uint)(DAT_006cfafc != 4);
    if (DAT_006cfba0 == 2) {
      DAT_006cfba4 = 0;
      DAT_006cfba8 = 1;
    }
    else if (DAT_006cfaf8 < 4) {
      DAT_006cfba4 = 0;
    }
    else {
      DAT_006cfba4 = 1;
    }
    FUN_00648f30((int)(char)(&DAT_006b7100)[*(int *)(pGameState + 0x2e20)]);
    return 8;
  }
  return 5;
}

