// ============================================
// Address:  0x00692310
// Original: FUN_00692310
// Status:   unreviewed
// ============================================


int FUN_00692310(int *param_1)

{
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  FUN_00693400();
  CoInitialize((LPVOID)0x0);
  (**(code **)(*param_1 + 4))();
  do {
    (**(code **)*param_1)(&local_18);
    local_8 = (**(code **)(*param_1 + 8))(local_18,local_14,local_10,local_c);
  } while (local_8 == 0);
  CoUninitialize();
  return local_8;
}

