// ============================================
// Address:  0x00645840
// Original: FUN_00645840
// Status:   unreviewed
// ============================================

void __fastcall FUN_00645840(int param_1)

{
    undefined4 *puVar1;
    void *pvVar2;
    undefined4 local_40;
    undefined4 local_3c;
    undefined1 local_24[4];
    undefined1 local_20[4];
    undefined1 local_1c[4];
    undefined1 local_18[4];
    undefined1 local_14[4];
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8                          = 0xffffffff;
    puStack_c                        = &LAB_0069e7d6;
    local_10                         = ExceptionList;
    ExceptionList                    = &local_10;
    puVar1                           = (undefined4 *)FUN_006560c0(local_14, "data/chat/chat.bmp");
    *(undefined4 *)(param_1 + 0x100) = *puVar1;
    puVar1 = (undefined4 *)FUN_006560c0(local_18, "data/chat/name_p1.bmp");
    *(undefined4 *)(param_1 + 0x104) = *puVar1;
    puVar1 = (undefined4 *)FUN_006560c0(local_1c, "data/chat/name_p2.bmp");
    *(undefined4 *)(param_1 + 0x108) = *puVar1;
    puVar1 = (undefined4 *)FUN_006560c0(local_20, "data/chat/name_p1s.bmp");
    *(undefined4 *)(param_1 + 0x10c) = *puVar1;
    puVar1 = (undefined4 *)FUN_006560c0(local_24, "data/chat/name_p2s.bmp");
    *(undefined4 *)(param_1 + 0x110) = *puVar1;
    pvVar2                           = operator_new(0x148);
    local_8                          = 0;
    if (pvVar2 == (void *)0x0)
    {
        local_3c = 0;
    }
    else
    {
        local_3c = FUN_0065d6f0(DAT_006d1850);
    }
    local_8                          = 0xffffffff;
    *(undefined4 *)(param_1 + 0x140) = local_3c;
    FUN_0065d7e0(&DAT_006a4d50, 0x10, 0xff, 0xff, 0xff);
    FUN_00646ea0(0);
    CPane::SetBorders(*(CPane **)(param_1 + 0x140), 300, 4, 0, 0);
    pvVar2  = operator_new(0x148);
    local_8 = 1;
    if (pvVar2 == (void *)0x0)
    {
        local_40 = 0;
    }
    else
    {
        local_40 = FUN_0065d6f0(DAT_006d1850);
    }
    local_8                          = 0xffffffff;
    *(undefined4 *)(param_1 + 0x144) = local_40;
    FUN_0065d7e0(&DAT_006a4d60, 0x10, 0, 0, 0);
    FUN_00646ea0(0);
    CPane::SetBorders(*(CPane **)(param_1 + 0x144), 300, 0xb, 0, 0x10);
    FUN_00655af0(*(undefined4 *)(param_1 + 0x100), 0, 0, 0x140, 0x60);
    FUN_00655b20(*(undefined4 *)(param_1 + 0x100), 0, 0xc0, 0x100, 0x40, 10, 0);
    FUN_00655af0(*(undefined4 *)(param_1 + 0x100), 0, 0x60, 0x180, 0x40);
    FUN_00655b20(*(undefined4 *)(param_1 + 0x100), 0, 0xa0, 0x20, 0x20, 0x10, 0x10);
    FUN_00655690(*(undefined4 *)(param_1 + 0x104), 0, 0, 0x20, 0x20);
    FUN_00655690(*(undefined4 *)(param_1 + 0x108), 0, 0, 0x20, 0x20);
    FUN_00655690(*(undefined4 *)(param_1 + 0x10c), 0, 0, 0x10, 0x10);
    FUN_00655690(*(undefined4 *)(param_1 + 0x110), 0, 0, 0x10, 0x10);
    FUN_00645df0();
    *(undefined1 *)(param_1 + 0xe60) = 0;
    *(undefined4 *)(param_1 + 0xdcc) = 0;
    FUN_00646ee0(0x22);
    FUN_00646ec0(1);
    ExceptionList = local_10;
    return;
}
