// ============================================
// Address:  0x0065b870
// Original: FUN_0065b870
// Suggested: PlayBGM (confidence: high)
// Status:   suggested — name kept as comment until reviewed
// ============================================


bool __thiscall FUN_0065b870(int param_1,undefined4 param_2)

{
  char cVar1;
  
  FUN_0065d670();
  cVar1 = FUN_006683d0(param_2);
  if (cVar1 != '\0') {
    FUN_00667f20();
    FUN_00667b00(0,0x100000,param_1 + 0x1318);
    *(undefined4 *)(param_1 + 0x1354) = 0;
    *(undefined4 *)(param_1 + 0x1350) = 0;
    *(undefined4 *)(param_1 + 0x1358) = 0xffffffff;
    *(undefined1 *)(param_1 + 0x134d) = 1;
    FUN_0065bb70();
    FUN_0065a390((*(int *)(param_1 + 0x135c) * *(int *)(param_1 + 0x1360)) / 10000 + -10000);
    FUN_00667ed0(1);
    FUN_0065d6a0();
  }
  else {
    *(undefined1 *)(param_1 + 0x134d) = 0;
    FUN_0065d6a0();
  }
  return cVar1 != '\0';
}

