// ============================================
// Address:  0x00689f30
// Original: FUN_00689f30
// Status:   unreviewed
// ============================================

undefined4 FUN_00689f30(int param_1,
                        undefined4 param_2,
                        undefined4 param_3,
                        undefined4 param_4,
                        undefined4 param_5,
                        undefined8 param_6)

{
    FUN_0068d8f0(param_2, param_3);
    FUN_0068d8f0(param_4, param_5);
    *(undefined8 *)(param_1 + 0x84) = param_6;
    return 0;
}
