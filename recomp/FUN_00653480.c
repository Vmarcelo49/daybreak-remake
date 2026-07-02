// ============================================
// Address:  0x00653480
// Original: FUN_00653480
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00653480(int param_1, undefined4 param_2)

{
    char cVar1;
    undefined4 uVar2;
    undefined4 *puVar3;
    undefined1 local_c[4];
    undefined1 local_8[4];

    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0')
    {
        uVar2 = FUN_006543d0(param_2);
        FUN_00653d40(uVar2);
        puVar3                          = (undefined4 *)FUN_00653d10(local_8);
        *(undefined4 *)(param_1 + 0x74) = *puVar3;
        puVar3                          = (undefined4 *)FUN_00654620(local_c);
        uVar2                           = *puVar3;
        *(undefined4 *)(param_1 + 0x78) = uVar2;
        uVar2                           = CONCAT31((int3)((uint)uVar2 >> 8), 1);
    }
    else
    {
        uVar2 = 0;
    }
    return uVar2;
}
