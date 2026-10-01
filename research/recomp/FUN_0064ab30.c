// ============================================
// Address:  0x0064ab30
// Original: FUN_0064ab30
// Status:   unreviewed
// ============================================

void __thiscall FUN_0064ab30(int param_1, int param_2)

{
    undefined4 *puVar1;
    undefined4 uVar2;
    uint uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar7;
    undefined3 uVar6;

    if (*(int *)(param_1 + 0x52c0 + param_2 * 4) != 0)
    {
        puVar1 = *(undefined4 **)(param_1 + 0x52c0 + param_2 * 4);
        if (puVar1 != (undefined4 *)0x0)
        {
            (**(code **)*puVar1)(1);
        }
        *(undefined4 *)(param_1 + 0x52c0 + param_2 * 4) = 0;
    }
    uVar2 = FUN_00649790(*(undefined4 *)(param_1 + 0x5308 + param_2 * 4),
                         *(undefined4 *)(param_1 + 0x5318 + param_2 * 4));
    *(undefined4 *)(param_1 + 0x52c0 + param_2 * 4) = uVar2;
    uVar3                                           = (uint) * (byte *)(param_1 + param_2 + 0x5334);
    uVar7 = CONCAT31((int3)((uint)(param_1 + param_2) >> 8),
                     *(undefined1 *)(param_1 + param_2 + 0x532c));
    uVar6 = (undefined3)((uint)(param_1 + param_2) >> 8);
    uVar4 = CONCAT31(uVar6, *(undefined1 *)(param_1 + param_2 + 0x5330));
    uVar5 = CONCAT31(uVar6, *(undefined1 *)(param_1 + 0x5318 + param_2 * 4));
    uVar2 = FUN_00649770(*(undefined4 *)(param_1 + 0x5308 + param_2 * 4));
    FUN_0041e180(uVar2, uVar5, uVar4, uVar7, uVar3);
    uVar3 = (uint) * (byte *)(param_1 + param_2 + 0x5328);
    uVar2 = FUN_0064ada0(*(undefined4 *)(param_1 + 0x52d8 + param_2 * 4));
    FUN_0041dc80(param_2, uVar2, uVar3);
    return;
}
