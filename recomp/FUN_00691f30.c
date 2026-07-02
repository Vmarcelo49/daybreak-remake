// ============================================
// Address:  0x00691f30
// Original: FUN_00691f30
// Status:   unreviewed
// ============================================

undefined4 FUN_00691f30(undefined4 *param_1)

{
    int iVar1;
    undefined4 uVar2;

    iVar1 = FUN_00692180();
    uVar2 = (**(code **)*param_1)();
    if (-1 < iVar1)
    {
        CoUninitialize();
    }
    return uVar2;
}
