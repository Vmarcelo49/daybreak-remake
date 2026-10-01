// Function: FUN_00691f30
// Address:  0x00691f30
// Source:   batch_decompile (mass dump)
// Hash:     1f9762dd303399a5


undefined4 FUN_00691f30(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00692180();
  uVar2 = (**(code **)*param_1)();
  if (-1 < iVar1) {
    CoUninitialize();
  }
  return uVar2;
}

