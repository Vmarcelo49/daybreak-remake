// Function: FUN_0041dcb0
// Address:  0x0041dcb0
// Source:   batch_decompile (mass dump)
// Hash:     ec2d31d62dee37bd


void __fastcall FUN_0041dcb0(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_00423420(param_1 + 5,param_1[2]);
  iVar1 = FUN_004233a0();
  param_1[1] = iVar1;
  uVar2 = FUN_004233e0();
  FUN_00434770(uVar2);
  param_1[0x15] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0xc0] = 0;
  param_1[0xc1] = -1;
  FUN_0065a5e0();
  FUN_0065a5e0();
  param_1[0x17] = 0x43340000;
  param_1[0x1a] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  *(undefined1 *)((int)param_1 + 0xaec9) = 0;
  *(undefined1 *)((int)param_1 + 0xaeca) = 0;
  *(undefined1 *)((int)param_1 + 0xaecb) = 0;
  *(undefined1 *)(param_1 + 0x21) = 1;
  *(undefined1 *)((int)param_1 + 0x85) = 0;
  *(undefined1 *)(param_1 + 0x211) = 0;
  *(undefined1 *)((int)param_1 + 0x845) = 0;
  *(undefined1 *)((int)param_1 + 0x846) = 0;
  *(undefined1 *)(param_1 + 0x2bb2) = 0;
  *(undefined1 *)(param_1 + 0x2bb3) = 0;
  param_1[0x212] = 0;
  param_1[0x213] = 0;
  *(undefined1 *)(param_1 + 0xcd) = 0;
  _memset(param_1 + 0x1f7,0,0x24);
  _memset(param_1 + 0x200,0,0x24);
  *(undefined1 *)(param_1 + 0x209) = 0;
  param_1[0x2b7b] = 0;
  param_1[0x2b7c] = 0;
  param_1[0x2b7d] = 0;
  param_1[0x2b81] = 0;
  param_1[param_1[0x2b7b] * 0xe + 0x1d7b] = 0x3f800000;
  param_1[param_1[0x2b7b] * 0xe + 0x1d7c] = 0x3f800000;
  param_1[0x2b84] = -1;
  param_1[0x2b83] = -1;
  FUN_00421080(param_1[0x2b7b]);
  param_1[0x20c] = 0;
  _memset(param_1 + 0x9e,0,0x28);
  FUN_004246f0(0xf,param_1 + 0x9e);
  param_1[0x1e9] = 10000;
  param_1[0x1ea] = 10000;
  param_1[0x20e] = 0;
  param_1[0x20f] = 0;
  param_1[0x210] = 0;
  param_1[0x20d] = 1000;
  param_1[0x1eb] = 0;
  param_1[0x1ec] = 0;
  param_1[0x1ed] = 0;
  param_1[0x1ee] = 0;
  param_1[0x1ef] = 0;
  param_1[0x1f0] = 0;
  param_1[0x1f1] = 0;
  param_1[0x28] = 0;
  param_1[0x20a] = 0;
  param_1[0x20b] = 0;
  param_1[0x1a1] = -1;
  param_1[0xc3] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xb6] = 0;
  *(undefined1 *)(param_1 + 0xb7) = 0;
  param_1[0x1f2] = 100;
  param_1[499] = 100;
  param_1[500] = 100;
  FUN_00434790();
  _memset(param_1 + 0x219,0,0x10);
  _memset(param_1 + 0x2bae,0,0x10);
  param_1[0x1f5] = -1;
  if ((char)param_1[0x218] == '\0') {
    *(undefined1 *)(param_1 + 0xc4) = 0xff;
  }
  else {
    *(undefined1 *)(param_1 + 0xc4) = 0;
  }
  param_1[0xc5] = -0x3ee00000;
  *(undefined1 *)(param_1 + 0x1a7) = 0;
  if (((-1 < *(int *)(&DAT_006cfb08 + param_1[2] * 4)) &&
      (-1 < (int)(&DAT_006cfb18)[*(int *)(&DAT_006cfb08 + param_1[2] * 4)])) &&
     ((&DAT_006cfb54)[(&DAT_006cfb18)[*(int *)(&DAT_006cfb08 + param_1[2] * 4)]] != '\0')) {
    *(undefined1 *)(param_1 + 0x1a7) = 1;
  }
  param_1[0x2bb4] = 0;
  FUN_00420880();
  FUN_00430840();
  (**(code **)(*param_1 + 0x10))();
  return;
}

