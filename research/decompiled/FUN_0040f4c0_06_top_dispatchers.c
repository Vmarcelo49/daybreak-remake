// Function: FUN_0040f4c0
// Address:  0x0040f4c0
// Source:  06_top_dispatchers.txt


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_0040f4c0(int param_1)

{
  undefined4 uVar1;
  size_t sVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_148 [4];
  undefined1 local_144 [4];
  undefined1 local_140 [4];
  int local_13c;
  int local_138;
  int local_134;
  int local_130;
  CHAR local_12c [264];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_24 = DAT_006b77f4;
switchD_0040f510_default:
  do {
    uVar1 = FUN_0040fb40(&local_8);
    switch(uVar1) {
    case 0:
      local_c = local_8;
      *(undefined4 *)(param_1 + 0x75c) = 0;
      FUN_0065d670();
      FUN_00656200(*(undefined4 *)(param_1 + 0x4c));
      puVar4 = (undefined4 *)
               FUN_00656190(local_140,*(undefined4 *)(local_c + 4),*(undefined4 *)(param_1 + 0x40));
      *(undefined4 *)(param_1 + 0x4c) = *puVar4;
      FUN_00655690(*(undefined4 *)(param_1 + 0x4c),0,0,0x18,0x22);
      FUN_0065d6a0();
      *(undefined1 *)(param_1 + 0x758) = 1;
      sVar2 = _strlen(*(char **)(local_c + 4));
      *(size_t *)(param_1 + 0x760) = sVar2;
      return 0;
    case 1:
      local_1c = local_8;
      FUN_0066b860(param_1 + 0x774,local_8 + 4);
      *(undefined1 *)(param_1 + 0x76b) = 1;
      break;
    case 2:
      local_20 = local_8;
      wsprintfA(local_12c,"data/bgm/%s",local_8 + 4);
      FUN_0065b870(local_12c);
      break;
    case 3:
      local_10 = local_8;
      FUN_0065d670();
      FUN_00656200(*(undefined4 *)(param_1 + 0x54 + *(int *)(local_10 + 4) * 4));
      iVar3 = __stricmp((char *)(local_10 + 0xd),"NULL");
      if (iVar3 != 0) {
        puVar4 = (undefined4 *)FUN_006560c0(local_144,local_10 + 0xd);
        *(undefined4 *)(param_1 + 0x54 + *(int *)(local_10 + 4) * 4) = *puVar4;
        iVar3 = FUN_0068de10();
        if ((iVar3 != 0) &&
           (FUN_00655b20(*(undefined4 *)(param_1 + 0x54 + *(int *)(local_10 + 4) * 4),0,0,0x200,
                         0x200,0x100,0), 1 < *(int *)(local_10 + 4))) {
          FUN_0040da60(0xbf800000,0x3f800000);
        }
        if (*(char *)(local_10 + 0xc) != '\0') {
          *(float *)(param_1 + 0x6ac + *(int *)(local_10 + 4) * 4) = (float)*(int *)(local_10 + 8);
        }
      }
      FUN_0065d6a0();
      break;
    case 4:
      local_14 = local_8;
      FUN_0065b1d0(*(undefined4 *)(param_1 + 0x44));
      puVar4 = (undefined4 *)FUN_0065b0d0(local_148,local_14 + 4);
      *(undefined4 *)(param_1 + 0x44) = *puVar4;
      if ((*(char *)(param_1 + 0x76a) == '\0') && (*(int *)(param_1 + 0x878) == 0)) {
        FUN_0065b330(*(undefined4 *)(param_1 + 0x44),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x878) = 0x1e;
      }
      break;
    case 5:
      local_130 = local_8;
      uVar1 = FUN_004370d0((float)*(int *)(local_8 + 8),*(undefined4 *)(local_8 + 0xc));
      FUN_0040fd00(uVar1);
      break;
    case 6:
      local_134 = local_8;
      for (local_138 = 0; local_138 < 6; local_138 = local_138 + 1) {
        iVar3 = local_138;
        if (*(int *)(param_1 + 0x740 + local_138 * 4) == *(int *)(local_8 + 4)) goto LAB_0040f8df;
      }
      break;
    case 7:
      local_18 = local_8;
      WaitForSingleObject(*(HANDLE *)(param_1 + 0x73c),*(DWORD *)(local_8 + 4));
      break;
    case 8:
      return 1;
    }
  } while( true );
LAB_0040f8df:
  while (local_13c = iVar3 + 1, local_13c < 6) {
    *(undefined4 *)(param_1 + 0x73c + local_13c * 4) =
         *(undefined4 *)(param_1 + 0x740 + local_13c * 4);
    iVar3 = local_13c;
  }
  *(undefined4 *)(param_1 + 0x754) = *(undefined4 *)(local_8 + 4);
  goto switchD_0040f510_default;
}

