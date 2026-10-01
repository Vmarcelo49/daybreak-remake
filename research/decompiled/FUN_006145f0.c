// Function: FUN_006145f0
// Address:  0x006145f0
// Source:   batch_decompile (mass dump)
// Hash:     7c1f10f0ec0e38c9


void __fastcall FUN_006145f0(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  float10 fVar4;
  undefined4 uVar5;
  float fVar6;
  
  uVar3 = FUN_0042c7b0();
  if (((uVar3 & 0x100) != 0) &&
     ((*(int *)(param_1 + 0x150) == 0 || (*(int *)(param_1 + 0x150) == 10)))) {
    FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x28;
      FUN_0042c840(1);
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.15;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    sVar2 = FUN_0042c7b0();
    if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
       (600 < *(int *)(param_1 + 0x154))) {
      FUN_005f6db0(4,0,0,0);
      FUN_0042c8b0(0x9f);
      FUN_005f5e00();
      return;
    }
    fVar4 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x3c) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    fVar4 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x44) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x28;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.2;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 4;
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    sVar2 = FUN_0042c7b0();
    if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
       (600 < *(int *)(param_1 + 0x154))) {
      FUN_005f6db0(5,0,0,0);
      FUN_0042c8b0(0x9f);
      FUN_005f5e00();
      return;
    }
    fVar4 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x3c) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    fVar4 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x44) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f6fd0(0xd,0,0,0);
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6880(0);
    }
    if (30.0 < *(float *)(param_1 + 0x40)) {
      *(undefined4 *)(param_1 + 0x40) = 0x41f00000;
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0x4a);
      FUN_005f6db0(6,0,0,0);
      FUN_005f5e00();
      return;
    }
    fVar4 = (float10)FUN_0042d980();
    fVar4 = (float10)FUN_0042de80((float)fVar4);
    if (fVar4 * (float10)0.05 < (float10)*(float *)(param_1 + 0x54)) {
      fVar4 = (float10)FUN_0042d980();
      fVar4 = (float10)FUN_0042de80((float)fVar4);
      *(float *)(param_1 + 0x54) = (float)(fVar4 * (float10)0.05);
    }
    if ((*(float *)(param_1 + 100) < 90.0) && (-90.0 < *(float *)(param_1 + 100))) {
      fVar4 = (float10)FUN_0042d980();
      fVar4 = (float10)FUN_0042de80((float)fVar4);
      if ((((float10)*(float *)(param_1 + 0x54) < fVar4 * (float10)0.05) &&
          ((*(float *)(param_1 + 0x40) < 0.0 &&
           (*(float *)(param_1 + 0x54) < -*(float *)(param_1 + 0x40) * 1.0)))) &&
         (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 2.5,
         -*(float *)(param_1 + 0x40) < *(float *)(param_1 + 0x54))) {
        *(float *)(param_1 + 0x54) = -*(float *)(param_1 + 0x40) * 1.0;
      }
    }
    if (*(float *)(param_1 + 0x54) < 40.0 - (float)*(int *)(param_1 + 0x154) * 1.0) {
      *(float *)(param_1 + 0x54) = 40.0 - (float)*(int *)(param_1 + 0x154) * 1.0;
    }
    if (*(float *)(param_1 + 0x54) < 0.0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (40.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if ((1.0 < *(float *)(param_1 + 100)) &&
         (*(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 1.0,
         *(float *)(param_1 + 100) < 1.0)) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
      if ((*(float *)(param_1 + 100) < -1.0) &&
         (*(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 1.0,
         -1.0 < *(float *)(param_1 + 100))) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
    }
    if ((*(float *)(param_1 + 0x54) <= -*(float *)(param_1 + 0x40) * 1.0) &&
       (*(float *)(param_1 + 0x40) < 0.0)) {
      *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
      if (0x3c < *(int *)(param_1 + 0xf0)) {
        *(undefined4 *)(param_1 + 0xf0) = 0x3c;
      }
      if ((1.0 < *(float *)(param_1 + 100)) &&
         (*(float *)(param_1 + 100) =
               *(float *)(param_1 + 100) - (float)*(int *)(param_1 + 0xf0) * 0.5,
         *(float *)(param_1 + 100) < 1.0)) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
      if ((*(float *)(param_1 + 100) < -1.0) &&
         (*(float *)(param_1 + 100) =
               (float)*(int *)(param_1 + 0xf0) * 0.1 + *(float *)(param_1 + 100),
         -1.0 < *(float *)(param_1 + 100))) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
    }
    fVar4 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x3c) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    fVar4 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x44) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f7450(0,0x41a00000,0x1e,1,0);
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      FUN_005f6fd0(0xd,0,0,0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0x4a);
      FUN_005f6db0(7,0,0,0);
      FUN_005f5e00();
      return;
    }
    fVar4 = (float10)FUN_0042d980();
    fVar4 = (float10)FUN_0042de80((float)fVar4);
    if (fVar4 * (float10)0.05 < (float10)*(float *)(param_1 + 0x54)) {
      fVar4 = (float10)FUN_0042d980();
      fVar4 = (float10)FUN_0042de80((float)fVar4);
      *(float *)(param_1 + 0x54) = (float)(fVar4 * (float10)0.05);
    }
    if ((*(float *)(param_1 + 100) < 90.0) && (-90.0 < *(float *)(param_1 + 100))) {
      fVar4 = (float10)FUN_0042d980();
      fVar4 = (float10)FUN_0042de80((float)fVar4);
      if ((((float10)*(float *)(param_1 + 0x54) < fVar4 * (float10)0.05) &&
          ((*(float *)(param_1 + 0x40) < 0.0 &&
           (*(float *)(param_1 + 0x54) < -*(float *)(param_1 + 0x40) * 1.0)))) &&
         (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 2.5,
         -*(float *)(param_1 + 0x40) < *(float *)(param_1 + 0x54))) {
        *(float *)(param_1 + 0x54) = -*(float *)(param_1 + 0x40) * 1.0;
      }
    }
    if (*(float *)(param_1 + 0x54) < 40.0 - (float)*(int *)(param_1 + 0x154) * 1.0) {
      *(float *)(param_1 + 0x54) = 40.0 - (float)*(int *)(param_1 + 0x154) * 1.0;
    }
    if (*(float *)(param_1 + 0x54) < 0.0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (40.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if ((1.0 < *(float *)(param_1 + 100)) &&
         (*(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 1.0,
         *(float *)(param_1 + 100) < 1.0)) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
      if ((*(float *)(param_1 + 100) < -1.0) &&
         (*(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 1.0,
         -1.0 < *(float *)(param_1 + 100))) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
    }
    if ((*(float *)(param_1 + 0x54) <= -*(float *)(param_1 + 0x40) * 1.0) &&
       (*(float *)(param_1 + 0x40) < 0.0)) {
      *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
      if (0x3c < *(int *)(param_1 + 0xf0)) {
        *(undefined4 *)(param_1 + 0xf0) = 0x3c;
      }
      if ((1.0 < *(float *)(param_1 + 100)) &&
         (*(float *)(param_1 + 100) =
               *(float *)(param_1 + 100) - (float)*(int *)(param_1 + 0xf0) * 0.5,
         *(float *)(param_1 + 100) < 1.0)) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
      if ((*(float *)(param_1 + 100) < -1.0) &&
         (*(float *)(param_1 + 100) =
               (float)*(int *)(param_1 + 0xf0) * 0.1 + *(float *)(param_1 + 100),
         -1.0 < *(float *)(param_1 + 100))) {
        *(undefined4 *)(param_1 + 100) = 0;
      }
    }
    fVar4 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x3c) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    fVar4 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x44) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0x74) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0x70) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x78))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x70))
    ;
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0x74) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0x70) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x78) =
         (float)(fVar4 * (float10)0.075 + (float10)*(float *)(param_1 + 0x78));
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x74) =
         (float)(fVar4 * (float10)0.075 + (float10)*(float *)(param_1 + 0x74));
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x70) =
         (float)(fVar4 * (float10)0.075 + (float10)*(float *)(param_1 + 0x70));
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x78))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x70))
    ;
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70))
    ;
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 1.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if (2.0 <= *(float *)(param_1 + 0x78)) {
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
    }
    else {
      fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
      *(float *)(param_1 + 0x78) =
           (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78));
      fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
      *(float *)(param_1 + 0x70) =
           (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70));
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      uVar3 = FUN_0065d150();
      fVar6 = (float)(uVar3 % 400) - 200.0;
      uVar5 = 0;
      uVar3 = FUN_0065d150(0,fVar6);
      FUN_005f6fd0(10,(float)(uVar3 % 400) - 200.0,uVar5,fVar6);
    }
    if (*(int *)(param_1 + 0x154) < 0xf1) {
      fVar4 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 6.0);
      *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.25 + (float10)0.75);
    }
    else {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x5a:
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 1.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if (3.0 <= *(float *)(param_1 + 0x78)) {
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
    }
    else {
      fVar4 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 3.0);
      *(float *)(param_1 + 0x78) =
           (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78));
      fVar4 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 3.0);
      *(float *)(param_1 + 0x70) =
           (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70));
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      uVar3 = FUN_0065d150();
      fVar6 = (float)(uVar3 % 400) - 200.0;
      uVar5 = 0;
      uVar3 = FUN_0065d150(0,fVar6);
      FUN_005f6fd0(10,(float)(uVar3 % 400) - 200.0,uVar5,fVar6);
    }
    if (*(int *)(param_1 + 0x154) < 0xf1) {
      fVar4 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 6.0);
      *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.25 + (float10)0.75);
    }
    else {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar3 % 0x14) * 0.1 + 2.0;
      *(undefined4 *)(param_1 + 0x6c) = 0x42b40000;
    }
    if (0x3b < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    uVar5 = FUN_0066b668();
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = uVar5;
    uVar5 = FUN_0066b668();
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = uVar5;
    uVar5 = FUN_0066b668();
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) = uVar5;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) &&
       (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5,
       *(float *)(param_1 + 0x54) < 3.0)) {
      *(undefined4 *)(param_1 + 0x54) = 0x40400000;
      *(undefined4 *)(param_1 + 0xe8) = 1;
      FUN_005f6db0(0xc,0,0,0);
    }
    if (*(int *)(param_1 + 0xe8) == 1) {
      *(undefined4 *)(param_1 + 100) = 0;
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
      }
    }
    if (*(int *)(param_1 + 0xe8) == 2) {
      FUN_005f5e00();
      return;
    }
    if ((0x4b0 < *(int *)(param_1 + 0x154)) ||
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf6c) == 1)) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf6c) = 1;
      *(undefined4 *)(param_1 + 0xe8) = 2;
    }
    break;
  case 0x78:
    *(float *)(param_1 + 0x14) =
         (float)*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60);
    *(float *)(param_1 + 0x18) =
         (float)*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64);
    *(float *)(param_1 + 0x1c) =
         (float)*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68);
    if (*(int *)(param_1 + 0x154) % 0x69 == 0) {
      FUN_0042c8b0(0x9a);
    }
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 1.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if (3.0 <= *(float *)(param_1 + 0x78)) {
        *(undefined4 *)(param_1 + 0x78) = 0x40400000;
        *(undefined4 *)(param_1 + 0x70) = 0x40400000;
        *(undefined4 *)(param_1 + 0xe8) = 1;
      }
      else {
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.1;
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.1;
      }
    }
    if ((*(int *)(param_1 + 0x154) % 5 == 0) && (*(int *)(param_1 + 0xe8) == 1)) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if ((*(int *)(param_1 + 0x154) % 5 == 0) && (*(int *)(param_1 + 0xe8) == 1)) {
      uVar3 = FUN_0065d150();
      fVar6 = (float)(uVar3 % 600) - 300.0;
      uVar5 = 0;
      uVar3 = FUN_0065d150(0,fVar6);
      FUN_005f6fd0(10,(float)(uVar3 % 600) - 300.0,uVar5,fVar6);
    }
    if (((*(int *)(param_1 + 0x154) < 0x4b1) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf6c) != 1)) ||
       (1 < *(int *)(param_1 + 0xe8))) {
      if (*(int *)(param_1 + 0xe8) < 2) {
        fVar4 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 6.0);
        *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.25 + (float10)0.75);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0xe8) = 2;
    }
    if (*(int *)(param_1 + 0xe8) == 2) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x82:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0x74) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0x78) = 0x3e19999a;
    }
    *(undefined4 *)(param_1 + 0x54) = 0;
    fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x70) =
         (float)(fVar4 * (float10)0.05 + (float10)*(float *)(param_1 + 0x70));
    fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x74) =
         (float)(fVar4 * (float10)0.05 + (float10)*(float *)(param_1 + 0x74));
    fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x78) =
         (float)(fVar4 * (float10)0.05 + (float10)*(float *)(param_1 + 0x78));
    if (0x1c < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x8c:
    *(undefined4 *)(param_1 + 0x14) =
         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
    *(undefined4 *)(param_1 + 0x18) =
         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18);
    *(undefined4 *)(param_1 + 0x1c) =
         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 1.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
    }
    if (2.0 <= *(float *)(param_1 + 0x78)) {
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
    }
    else {
      fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
      *(float *)(param_1 + 0x78) =
           (float)(fVar4 * (float10)0.15 + (float10)*(float *)(param_1 + 0x78));
      fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
      *(float *)(param_1 + 0x70) =
           (float)(fVar4 * (float10)0.15 + (float10)*(float *)(param_1 + 0x70));
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0x154) % 10 == 0) {
      uVar3 = FUN_0065d150();
      fVar6 = (float)(uVar3 % 300) - 150.0;
      uVar5 = 0;
      uVar3 = FUN_0065d150(0,fVar6);
      FUN_005f6fd0(10,(float)(uVar3 % 300) - 150.0,uVar5,fVar6);
    }
    if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x172) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadf4) == 0)) {
      *(undefined4 *)(param_1 + 0xf8) = 1;
    }
    if ((*(int *)(param_1 + 0x154) < 0x12d) && (*(int *)(param_1 + 0xf8) < 1)) {
      fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 6));
      *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.25 + (float10)0.75);
    }
    else {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x96:
    uVar5 = FUN_0066b668();
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = uVar5;
    uVar5 = FUN_0066b668();
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = uVar5;
    uVar5 = FUN_0066b668();
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) = uVar5;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      FUN_005f6fd0(0xd,0,0,0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    sVar2 = FUN_0042c7b0();
    if ((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0x4a);
      FUN_005f6db0(0x10,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (300 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0xa0:
    if (*(int *)(param_1 + 0x154) % 0x69 == 0) {
      FUN_0042c8b0(0x9a);
    }
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 1.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x6c) = 0;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if (3.0 <= *(float *)(param_1 + 0x78)) {
        *(undefined4 *)(param_1 + 0x78) = 0x40400000;
        *(undefined4 *)(param_1 + 0x70) = 0x40400000;
        *(undefined4 *)(param_1 + 0xe8) = 1;
      }
      else {
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.3;
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.3;
      }
    }
    if ((*(int *)(param_1 + 0x154) % 5 == 0) && (*(int *)(param_1 + 0xe8) == 1)) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0xe8) < 2) {
      *(undefined4 *)(param_1 + 100) = 0;
      fVar4 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar4;
    }
    if ((*(int *)(param_1 + 0x154) % 5 == 0) && (*(int *)(param_1 + 0xe8) == 1)) {
      uVar3 = FUN_0065d150();
      fVar6 = (float)(uVar3 % 600) - 300.0;
      uVar5 = 0;
      uVar3 = FUN_0065d150(0,fVar6);
      FUN_005f6fd0(10,(float)(uVar3 % 600) - 300.0,uVar5,fVar6);
    }
    if (((*(int *)(param_1 + 0x154) < 0x4b1) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf6c) != 1)) ||
       (1 < *(int *)(param_1 + 0xe8))) {
      if (*(int *)(param_1 + 0xe8) < 2) {
        fVar4 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 6.0);
        *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.25 + (float10)0.75);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0xe8) = 2;
    }
    if (*(int *)(param_1 + 0xe8) == 2) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

