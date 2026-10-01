// ============================================
// Address:  0x004261d0
// Original: FUN_004261d0
// Status:   unreviewed
// ============================================

void __fastcall FUN_004261d0(allocator<std::_Container_proxy> *param_1)

{
    _Container_proxy *p_Var1;
    undefined4 *puVar2;
    _Container_proxy *local_8;

    puVar2                       = (undefined4 *)FUN_00663590(*(undefined4 *)(param_1 + 4));
    local_8                      = (_Container_proxy *)*puVar2;
    puVar2                       = (undefined4 *)FUN_00663590(*(undefined4 *)(param_1 + 4));
    *puVar2                      = *(undefined4 *)(param_1 + 4);
    puVar2                       = (undefined4 *)FUN_00653df0(*(undefined4 *)(param_1 + 4));
    *puVar2                      = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(param_1 + 8) = 0;
    while (local_8 != *(_Container_proxy **)(param_1 + 4))
    {
        puVar2 = (undefined4 *)FUN_00663590(local_8);
        p_Var1 = (_Container_proxy *)*puVar2;
        std::allocator<std::_Container_proxy>::destroy(param_1, local_8);
        deallocate(local_8, 1);
        local_8 = p_Var1;
    }
    return;
}
