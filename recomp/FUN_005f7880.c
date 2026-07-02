// ============================================
// Address:  0x005f7880
// Original: FUN_005f7880
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_005f7880(int param_1, undefined1 *param_2)

{
    *param_2                        = 0x3b;
    param_2[1]                      = *(undefined1 *)(param_1 + 8);
    param_2[2]                      = *(undefined1 *)(param_1 + 9);
    *(undefined4 *)(param_2 + 3)    = *(undefined4 *)(param_1 + 0xc);
    *(undefined2 *)(param_2 + 7)    = *(undefined2 *)(param_1 + 0x10);
    *(undefined4 *)(param_2 + 9)    = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(param_2 + 0xd)  = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)(param_2 + 0x11) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(param_2 + 0x15) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_2 + 0x19) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_2 + 0x1d) = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(param_2 + 0x21) = *(undefined4 *)(param_1 + 0x2c);
    return 0x25;
}
