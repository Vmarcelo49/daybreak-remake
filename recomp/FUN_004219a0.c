// ============================================
// Address:  0x004219a0
// Original: FUN_004219a0
// Status:   unreviewed
// ============================================


bool __fastcall FUN_004219a0(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00421930();
  if (0 < iVar1) {
    *(undefined4 *)(param_1 + 0x7a4) = 10000;
    *(undefined4 *)(param_1 + 0x7a8) = 10000;
    *(undefined4 *)(param_1 + 0x7c0) = 0;
    *(undefined4 *)(param_1 + 0x7c4) = 0;
    *(undefined4 *)(param_1 + 0x7ac) = 0x1e;
    *(undefined4 *)(param_1 + 0x834) = 1000;
    *(undefined4 *)(param_1 + 0x84c) = 0;
    _memset((void *)(param_1 + 0xaeb8),0,0x10);
    _memset((void *)(param_1 + 0x7dc),0,0x24);
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined1 *)(param_1 + 0xaecb) = 1;
    FUN_00421bd0();
    FUN_004347c0();
    FUN_00421080(0xc2);
  }
  return 0 < iVar1;
}

