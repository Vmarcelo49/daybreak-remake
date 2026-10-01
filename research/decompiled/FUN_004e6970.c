// Function: FUN_004e6970
// Address:  0x004e6970
// Source:   batch_decompile (mass dump)
// Hash:     b28a171e5d0bab11


void __fastcall FUN_004e6970(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xadec) < 100) {
    if ((*(int *)(param_1 + 0x7a4) < 0x9c4) && (*(char *)(param_1 + 0xaebd) < '\x04')) {
      *(undefined1 *)(param_1 + 0xaebd) = 4;
      FUN_00422490(0xe,3,0xf,0);
    }
    if ((*(int *)(param_1 + 0x7a4) < 5000) && (*(char *)(param_1 + 0xaebd) < '\x03')) {
      *(undefined1 *)(param_1 + 0xaebd) = 3;
      FUN_00422490(0xe,2,0xf,0);
    }
    if ((*(int *)(param_1 + 0x7a4) < 0x1d4c) && (*(char *)(param_1 + 0xaebd) < '\x02')) {
      *(undefined1 *)(param_1 + 0xaebd) = 2;
      FUN_00422490(0xe,1,0xf,0);
    }
    if ((*(int *)(param_1 + 0x7a4) < 10000) && (*(char *)(param_1 + 0xaebd) < '\x01')) {
      *(undefined1 *)(param_1 + 0xaebd) = 1;
      FUN_00422490(0xe,0,0xf,0);
    }
    if (*(char *)(param_1 + 0xaebf) == '\x01') {
      *(undefined1 *)(param_1 + 0xaebf) = 0;
      FUN_00422240(0x10,0x14,0);
    }
    if (*(char *)(param_1 + 0xaeb8) == '\x01') {
      iVar1 = FUN_00421930();
      if (0 < iVar1) {
        *(undefined1 *)(param_1 + 0xaeb8) = 0;
        iVar1 = FUN_00421930();
        if (iVar1 < 0x15) {
          FUN_004223d0(0x12,0xf,0);
        }
        else {
          FUN_004223d0(4,0xf,0);
        }
      }
    }
    if (*(char *)(param_1 + 0xaec0) == '\x01') {
      *(undefined1 *)(param_1 + 0xaec0) = 0;
      FUN_004223d0(0x15,0xf,0);
    }
    if (*(char *)(param_1 + 0xaec1) == '\x01') {
      *(undefined1 *)(param_1 + 0xaec1) = 0;
      FUN_004223d0(0x26,0xf,0);
    }
  }
  if ((*(int *)(param_1 + 0xadec) < 100) && (*(char *)(param_1 + 0xaec2) == '\x01')) {
    *(undefined1 *)(param_1 + 0xaec2) = 0;
    FUN_004223d0(0x25,0xf,0);
  }
  return;
}

