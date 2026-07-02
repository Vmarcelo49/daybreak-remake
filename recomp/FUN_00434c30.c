// ============================================
// Address:  0x00434c30
// Original: FUN_00434c30
// Status:   unreviewed
// ============================================


void __fastcall FUN_00434c30(int param_1)

{
  float10 fVar1;
  allocator<char> local_1c [12];
  float local_10;
  float local_c;
  float local_8;
  
  std::allocator<char>::allocator<char>(local_1c);
  FUN_00434cc0(0,local_1c);
  FUN_0042dfd0(&local_10,local_1c);
  local_c = local_c + 70.0;
  fVar1 = (float10)FUN_0042de80(local_8 * local_8 + local_10 * local_10);
  fVar1 = (float10)FUN_004235a0(local_c,(float)fVar1);
  *(float *)(param_1 + 0x100) = (float)((fVar1 * (float10)180.0) / (float10)3.1415927);
  return;
}

