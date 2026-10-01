// Function: FUN_00436090
// Address:  0x00436090
// Source:   batch_decompile (mass dump)
// Hash:     3eff7d31b57683e4


undefined4 __fastcall FUN_00436090(int param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x130) = 0;
  *(undefined4 *)(param_1 + 0x134) = 0;
  *(undefined4 *)(param_1 + 0x138) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
  uVar1 = 0;
  FUN_004244e0(0);
  uVar1 = FUN_00424370(uVar1);
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  D3DXVec3Normalize(param_1 + 0x3c,param_1 + 0x3c);
  return 1;
}

