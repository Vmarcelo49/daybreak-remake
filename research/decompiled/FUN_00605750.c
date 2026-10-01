// Function: FUN_00605750
// Address:  0x00605750
// Source:   batch_decompile (mass dump)
// Hash:     2deaf96bb1bdcfe9


void __fastcall FUN_00605750(int param_1)

{
  float10 fVar1;
  
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.4;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.4;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.4;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.4;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.4;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.4;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x41a00000;
      *(undefined4 *)(param_1 + 0x74) = 0x41a00000;
      *(undefined4 *)(param_1 + 0x78) = 0x41a00000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 3.0;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 3.0;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 3.0;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x41a00000;
      *(undefined4 *)(param_1 + 0x74) = 0x41a00000;
      *(undefined4 *)(param_1 + 0x78) = 0x41a00000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 3.0;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 3.0;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 3.0;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar1 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x70) = (float)(fVar1 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70))
    ;
    fVar1 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x74) = (float)(fVar1 * (float10)0.2 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar1 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x78) = (float)(fVar1 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78))
    ;
    if ((0 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (0x14 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x41a00000;
      *(undefined4 *)(param_1 + 0x74) = 0x41a00000;
      *(undefined4 *)(param_1 + 0x78) = 0x41a00000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 3.0;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 3.0;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 3.0;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

