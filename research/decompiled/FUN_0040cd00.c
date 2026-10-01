// Function: FUN_0040cd00
// Address:  0x0040cd00
// Source:   batch_decompile (mass dump)
// Hash:     dac708e5c172d2e7


void __fastcall FUN_0040cd00(int param_1)

{
  undefined4 local_14;
  undefined4 local_10;
  
  FUN_00655d60(0,0);
  FUN_00655830(0x432f0000,0x42fa0000,0,*(undefined4 *)(param_1 + 0x3d48));
  if (*(int *)(param_1 + 0x3d48) != 0) {
    FUN_00655830(0x432f0000,0x432f0000,0,*(int *)(param_1 + 0x3d4c) + 1);
  }
  if (*(int *)(param_1 + 0x3d48) == 0) {
    FUN_00655830(0x440fc000,0x43160000,0,9);
  }
  else {
    FUN_00655830(0x440fc000,0x43160000,(*(int *)(param_1 + 0x3d48) + -1) / 3,
                 ((*(int *)(param_1 + 0x3d48) + -1) % 3) * 3 + *(int *)(param_1 + 0x3d4c));
  }
  FUN_00655830(0x432f0000,0x43898000,*(int *)(param_1 + 0x3c78) != 2,0);
  FUN_00655830(0x432f0000,0x43a28000,*(int *)(param_1 + 0x3c78) != 3,1);
  FUN_00655830(0x432f0000,0x43bb8000,*(int *)(param_1 + 0x3c78) != 4,2);
  FUN_00655830(0x432f0000,0x43d48000,*(int *)(param_1 + 0x3c78) != 5,0);
  FUN_00655830(0x432f0000,0x43ed8000,*(int *)(param_1 + 0x3c78) != 6,1);
  if ((*(int *)(param_1 + 0x3c78) == 7) && (*(int *)(param_1 + 0x3c7c) != 1)) {
    local_10 = 0;
  }
  else {
    local_10 = 1;
  }
  FUN_00655830(0x43898000,0x44098000,0,local_10);
  if ((*(int *)(param_1 + 0x3c78) == 7) && (*(int *)(param_1 + 0x3c7c) != 0)) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  FUN_00655830(0x44034000,0x44098000,1,local_14 + 1);
  if (DAT_006cf3c0 == 0) {
    FUN_00431ce0(0x44098000,0x437f0000,0x3f800000,6,1);
  }
  else {
    FUN_00431b20(DAT_006cf3c0,0x44160000,0x437f0000,0x3f800000,0);
  }
  FUN_00431b20(DAT_006cf3b8,0x44160000,0x43988000,0x3f800000,0);
  FUN_00431ce0(0x44160000,0x43988000,0x3f800000,5,1);
  FUN_00431b20(DAT_006cf3bc,0x44160000,0x43b18000,0x3f800000,0);
  FUN_00431ce0(0x44160000,0x43b18000,0x3f800000,5,1);
  FUN_00431b20(DAT_006cf3b0,0x44160000,0x43ca8000,0x3f800000,0);
  FUN_00431ce0(0x44160000,0x43ca8000,0x3f800000,5,1);
  FUN_00431b20(DAT_006cf3b4,0x44160000,0x43e38000,0x3f800000,0);
  FUN_00431ce0(0x44160000,0x43e38000,0x3f800000,5,1);
  if (DAT_006cfdb0 != '\0') {
    FUN_00646870(0x42c80000);
    FUN_00646500(0x43500000,0x44020000);
  }
  return;
}

