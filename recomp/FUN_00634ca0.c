// ============================================
// Address:  0x00634ca0
// Original: FUN_00634ca0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00634ca0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 local_18 [8];
  undefined1 local_10;
  undefined1 local_f;
  int local_c;
  int local_8;
  
  local_8 = 1;
  if (DAT_006cfdb0 != '\0') {
    local_8 = 8;
  }
  for (local_c = 0; local_c < local_8; local_c = local_c + 1) {
    if ((*(int *)(*(int *)(param_1 + 19000) + local_c * 4) != 0) &&
       (((local_c != 0 || (DAT_006cfdb0 == '\0')) || (cVar1 = FUN_00645e10(), cVar1 == '\0')))) {
      FUN_00657390();
      FUN_0063b650();
      uVar4 = *(undefined4 *)
               (param_1 + 0x129c + **(char **)(*(int *)(param_1 + 19000) + local_c * 4) * 4);
      uVar2 = FUN_004233c0(uVar4);
      FUN_0063b750(uVar2,uVar4);
      if ((*(int *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 0x44) == 1) &&
         (*(char *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) =
               *(char *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) + '\x01',
         '\x06' < *(char *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1))) {
        *(undefined1 *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) = 1;
      }
      if ((*(int *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 0x48) == 1) &&
         (*(char *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) =
               *(char *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) + -1,
         *(char *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) < '\x01')) {
        *(undefined1 *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) = 6;
      }
      if (*(int *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 0x4c) == 1) {
        *(undefined1 *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1) = 0;
      }
      if (*(int *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 0x50) == 1) {
        uVar3 = (int)**(char **)(*(int *)(param_1 + 19000) + local_c * 4) + 1U & 0x80000003;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
        }
        **(undefined1 **)(*(int *)(param_1 + 19000) + local_c * 4) = (char)uVar3;
        (&DAT_006cfdd9)[local_c] = **(undefined1 **)(*(int *)(param_1 + 19000) + local_c * 4);
        if (local_c == 0) {
          DAT_006cfba4 = (int)*(char *)**(undefined4 **)(param_1 + 19000);
        }
        if ((0 < local_c) && (DAT_006cfdb0 == '\x01')) {
          FUN_0063b770();
          local_10 = (&DAT_006cfdd9)[local_c];
          local_f = *(undefined1 *)(*(int *)(*(int *)(param_1 + 19000) + local_c * 4) + 1);
          FUN_00415d30(local_c,local_18,0,8);
        }
      }
    }
  }
  return;
}

