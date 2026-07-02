// ============================================
// Address:  0x0063a740
// Original: FUN_0063a740
// Status:   unreviewed
// ============================================


void __fastcall FUN_0063a740(int param_1)

{
  int iVar1;
  int iVar2;
  int local_18;
  
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,5,1);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,6,1);
  iVar1 = *(int *)(param_1 + 0x41e0);
  if (iVar1 == 0) {
    FUN_00655f70((float)*(int *)(param_1 + 0x41dc) - 256.0,0,(float)*(int *)(param_1 + 0x41dc),
                 0x42700000);
    FUN_00655f70((float)*(int *)(param_1 + 0x41dc),0,0x44480000,0x42700000);
    FUN_00655f70((float)(0x420 - *(int *)(param_1 + 0x41dc)),0x43d40000,
                 (float)(800 - *(int *)(param_1 + 0x41dc)),0x44160000);
    FUN_00655f70((float)(800 - *(int *)(param_1 + 0x41dc)),0x43d40000,0,0x44160000);
  }
  else if (iVar1 == 1) {
    FUN_00655d60((float)*(int *)(param_1 + 0x41dc) + -32.0,0x42700000);
    FUN_00655d60((float)*(int *)(param_1 + 0x41dc) + 352.0,0x42700000);
    iVar1 = (&DAT_006cfaf8)[*(int *)(param_1 + 0x442c) * 2];
    iVar2 = (&DAT_006cfafc)[*(int *)(param_1 + 0x442c) * 2];
    if ((iVar1 < 4) && ((&DAT_006cfdd1)[(&DAT_006cfb18)[iVar1]] != '\0')) {
      FUN_00646bd0((&DAT_006cfb18)[iVar1],(float)*(int *)(param_1 + 0x41dc) + 112.0,0x428c0000,1);
    }
    if ((iVar2 < 4) && ((&DAT_006cfdd1)[(&DAT_006cfb18)[iVar2]] != '\0')) {
      FUN_00646bd0((&DAT_006cfb18)[iVar2],(float)*(int *)(param_1 + 0x41dc) + 512.0,0x428c0000,1);
    }
    FUN_00655f70(0,0,0x44480000,0x42700000);
    FUN_00655f70(0,0x43d40000,0x44480000,0x44160000);
    FUN_00655d60(0x42960000,0x43dc0000);
  }
  else if (iVar1 == 5) {
    FUN_00655d60(0xc2000000,0x42700000);
    FUN_00655d60(0x43b00000,0x42700000);
    iVar1 = (&DAT_006cfaf8)[*(int *)(param_1 + 0x442c) * 2];
    iVar2 = (&DAT_006cfafc)[*(int *)(param_1 + 0x442c) * 2];
    if ((iVar1 < 4) && ((&DAT_006cfdd1)[(&DAT_006cfb18)[iVar1]] != '\0')) {
      FUN_00646bd0((&DAT_006cfb18)[iVar1],0x42e00000,0x428c0000,1);
    }
    if ((iVar2 < 4) && ((&DAT_006cfdd1)[(&DAT_006cfb18)[iVar2]] != '\0')) {
      FUN_00646bd0((&DAT_006cfb18)[iVar2],0x44000000,0x428c0000,1);
    }
    FUN_00655f70(0,0,0x44480000,0x42700000);
    FUN_00655f70(0,0x43d40000,0x44480000,0x44160000);
    FUN_00655d60(0x42960000,0x43dc0000);
    FUN_00651860(0,0,0x44480000,0x44160000,0xc0000000);
    if (DAT_006cfce9 == '\0') {
      FUN_00655d60(0x43c80000,0x41e00000);
      for (local_18 = 0; (local_18 < 4 && (local_18 < (*(int *)(param_1 + 0x41dc) + -0x1e) / 0x1e));
          local_18 = local_18 + 1) {
        FUN_00655830(0x43480000,(float)local_18 * 72.0 + 100.0,(&DAT_006cfaf8)[local_18],0);
        FUN_004082f0(0xff000000);
        FUN_00655830(0x43970000,(float)local_18 * 72.0 + 100.0 + 32.0,0,local_18);
        FUN_00655830(0x43950000,(float)local_18 * 72.0 + 100.0 + 32.0,0,local_18);
        FUN_00655830(0x43960000,(float)local_18 * 72.0 + 100.0 + 2.0 + 32.0,0,local_18);
        FUN_00655830(0x43960000,(((float)local_18 * 72.0 + 100.0) - 2.0) + 32.0,0,local_18);
        FUN_00655830(0x43970000,(float)local_18 * 72.0 + 100.0 + 2.0 + 32.0,0,local_18);
        FUN_00655830(0x43970000,(((float)local_18 * 72.0 + 100.0) - 2.0) + 32.0,0,local_18);
        FUN_00655830(0x43950000,(float)local_18 * 72.0 + 100.0 + 2.0 + 32.0,0,local_18);
        FUN_00655830(0x43950000,(((float)local_18 * 72.0 + 100.0) - 2.0) + 32.0,0,local_18);
        FUN_004082f0(0xffffffff);
        FUN_00655830(0x43960000,(float)local_18 * 72.0 + 100.0 + 32.0,0,local_18);
        if (((int)(&DAT_006cfaf8)[local_18] < 4) &&
           ((-1 < (int)(&DAT_006cfb18)[(&DAT_006cfaf8)[local_18]] &&
            ((&DAT_006cfdd1)[(&DAT_006cfb18)[(&DAT_006cfaf8)[local_18]]] != '\0')))) {
          FUN_00646bd0((&DAT_006cfb18)[(&DAT_006cfaf8)[local_18]],0x438c0000,
                       (float)local_18 * 72.0 + 100.0,1);
        }
      }
    }
  }
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,1);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,3);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,5,2);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,6,2);
  return;
}

