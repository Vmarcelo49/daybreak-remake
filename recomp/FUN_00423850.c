// ============================================
// Address:  0x00423850
// Original: FUN_00423850
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00423850(undefined4 param_1, undefined4 *param_2, undefined4 param_3)

{
    int iVar1;
    allocator<char> *paVar2;
    undefined4 *puVar3;
    allocator<char> local_44[64];

    std::allocator<char>::allocator<char>(local_44);
    D3DXMatrixMultiply(local_44, param_1, param_3);
    paVar2 = local_44;
    puVar3 = param_2;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1)
    {
        *puVar3 = *(undefined4 *)paVar2;
        paVar2  = paVar2 + 4;
        puVar3  = puVar3 + 1;
    }
    return param_2;
}
