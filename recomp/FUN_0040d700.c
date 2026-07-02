// ============================================
// Address:  0x0040d700
// Original: FUN_0040d700
// Status:   unreviewed
// ============================================


void __thiscall FUN_0040d700(int param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined1 local_8 [4];
  
  FUN_0065d670();
  wsprintfA((LPSTR)(param_1 + 0x3b34),"data/select/w%02d.bmp",param_3);
  FUN_00656200(*(undefined4 *)(param_1 + 0x2c + param_2 * 4));
  puVar1 = (undefined4 *)FUN_006560c0(local_8,param_1 + 0x3b34);
  *(undefined4 *)(param_1 + 0x2c + param_2 * 4) = *puVar1;
  FUN_006556c0(*(undefined4 *)(param_1 + 0x2c + param_2 * 4),0,0,0x100,0x40,0x80,0x20);
  FUN_0065d6a0();
  return;
}

