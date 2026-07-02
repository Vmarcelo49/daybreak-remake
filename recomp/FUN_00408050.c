// ============================================
// Address:  0x00408050
// Original: FUN_00408050
// Suggested: InitPlayerSlot (confidence: medium)
// Status:   suggested — name kept as comment until reviewed
// ============================================


void __thiscall FUN_00408050(int param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_0065d670();
  wsprintfA((LPSTR)(param_1 + 4),"data/select/w%02d.bmp",param_3);
  FUN_00656200(*(undefined4 *)(param_1 + 0x154 + param_2 * 4));
  puVar1 = (undefined4 *)FUN_006560c0(local_8,param_1 + 4);
  *(undefined4 *)(param_1 + 0x154 + param_2 * 4) = *puVar1;
  FUN_006556c0(*(undefined4 *)(param_1 + 0x154 + param_2 * 4),0,0,0x100,0x40,0x80,0x20);
  FUN_0065d6a0();
  FUN_0065d670();
  wsprintfA((LPSTR)(param_1 + 4),"data/select/cos%02d.bmp",param_3);
  FUN_00656200(*(undefined4 *)(param_1 + 0x164 + param_2 * 4));
  puVar1 = (undefined4 *)FUN_006560c0(local_c,param_1 + 4);
  *(undefined4 *)(param_1 + 0x164 + param_2 * 4) = *puVar1;
  FUN_006556c0(*(undefined4 *)(param_1 + 0x164 + param_2 * 4),0,0,0x50,0x80,0x28,0x50);
  FUN_0065d6a0();
  FUN_0065d670();
  wsprintfA((LPSTR)(param_1 + 4),"data/select/%02d.bmp",param_3);
  FUN_00656200(*(undefined4 *)(param_1 + 0x15c + param_2 * 4));
  puVar1 = (undefined4 *)FUN_006560c0(local_10,param_1 + 4);
  *(undefined4 *)(param_1 + 0x15c + param_2 * 4) = *puVar1;
  FUN_00655b20(*(undefined4 *)(param_1 + 0x15c + param_2 * 4),0,0,0x100,0x100,0x80,0x100);
  FUN_0065d6a0();
  return;
}

