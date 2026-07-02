// Function: FUN_00634760
// Address:  0x00634760
// Source:   batch_decompile (mass dump)
// Hash:     22d792afbd546195


void __fastcall FUN_00634760(int param_1)

{
  undefined4 local_8;
  
  *(undefined1 *)(param_1 + 0x4a40) = 0;
  *(undefined4 *)(param_1 + 0x44b4) = 0;
  *(undefined4 *)(param_1 + 0x1408) = 0;
  *(undefined4 *)(param_1 + 0x442c) = 0;
  *(undefined4 *)(param_1 + 0x4428) = 0;
  *(undefined4 *)(param_1 + 0x4424) = 0;
  *(undefined4 *)(param_1 + 0x4a3c) = 1;
  *(undefined4 *)(param_1 + 0x41e0) = 0;
  *(int *)(param_1 + 0x43d8) = *(int *)(param_1 + 0x43d4) * 0x3c;
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    FUN_00632e10();
  }
  _memset((void *)(param_1 + 0x43e4),0,0x10);
  _memset((void *)(param_1 + 0x4414),0,8);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  FUN_0063bf60();
  FUN_0063bf80();
  *(undefined1 *)(param_1 + 0x7f4) = DAT_006cfdc5;
  *(undefined1 *)(param_1 + 0x4430) = 0;
  *(undefined1 *)(param_1 + 0x4431) = 0;
  FUN_0065b1d0(*(undefined4 *)(param_1 + 0x4494));
  FUN_00642c10();
  return;
}

