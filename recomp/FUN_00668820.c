// ============================================
// Address:  0x00668820
// Original: FUN_00668820
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00668820(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int local_1a0;
  char local_19c [16];
  uint auStack_18c [28];
  int local_11c;
  undefined4 local_118;
  undefined1 local_114 [264];
  undefined4 local_c;
  size_t local_8;
  
  local_c = DAT_006b77f4;
  *(undefined8 *)(param_1 + 0x12f0) = 0;
  *(undefined8 *)(param_1 + 0x12e8) = 0;
  FUN_0066b860(local_114,param_2);
  local_8 = _strlen(param_2);
  local_114[local_8 - 3] = 0x73;
  local_114[local_8 - 2] = 0x66;
  local_114[local_8 - 1] = 0x6c;
  cVar1 = FUN_00653540(local_114);
  if (cVar1 != '\0') {
    iVar2 = FUN_00653a40();
    if (iVar2 != 0) {
      FUN_00653760(local_19c,0x80);
      local_118 = 0;
      local_11c = 0;
      for (local_1a0 = 0; local_1a0 < 0x60; local_1a0 = local_1a0 + 1) {
        if (((local_19c[local_1a0] == 'c') && (local_19c[local_1a0 + 1] == 'u')) &&
           (local_19c[local_1a0 + 2] == 'e')) {
          local_118 = *(uint *)(local_19c + local_1a0 + 0x10);
        }
        else if (((local_19c[local_1a0] == 'a') && (local_19c[local_1a0 + 1] == 'd')) &&
                ((local_19c[local_1a0 + 2] == 't' && (local_19c[local_1a0 + 3] == 'l')))) {
          local_11c = *(int *)(local_19c + local_1a0 + 0x10);
        }
      }
      if ((local_118 != 0) && (local_11c != 0)) {
        *(double *)(param_1 + 0x12e8) = (double)local_118 / (double)*(uint *)(param_1 + 0x12fc);
        *(double *)(param_1 + 0x12f0) =
             (double)(local_118 + local_11c) / (double)*(uint *)(param_1 + 0x12fc);
      }
    }
  }
  return;
}

