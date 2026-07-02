// Function: FUN_00667050
// Address:  0x00667050
// Source:   batch_decompile (mass dump)
// Hash:     6986fc846c452a9b


undefined4 FUN_00667050(void)

{
  HANDLE pvVar1;
  undefined4 *puVar2;
  undefined4 local_8;
  
  local_8 = 0;
  FUN_0065d670();
  FUN_006672b0(&local_8);
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  puVar2 = (undefined4 *)FUN_00667280();
  *puVar2 = pvVar1;
  FUN_0065d6a0();
  puVar2 = (undefined4 *)FUN_00667280();
  return *puVar2;
}

