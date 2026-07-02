// ============================================
// Address:  0x00422f90
// Original: FUN_00422f90
// Status:   unreviewed
// ============================================


void FUN_00422f90(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_28 [12];
  undefined1 local_1c [12];
  allocator<char> local_10 [12];
  
  std::allocator<char>::allocator<char>(local_10);
  FUN_00434cc0(0,param_1);
  FUN_00434d60(local_10);
  uVar1 = FUN_004241d0(local_1c,0x447a0000);
  puVar2 = (undefined4 *)FUN_00424180(local_28,uVar1);
  *param_2 = *puVar2;
  param_2[1] = puVar2[1];
  param_2[2] = puVar2[2];
  return;
}

