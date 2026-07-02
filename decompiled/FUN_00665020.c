// Function: FUN_00665020
// Address:  0x00665020
// Source:   batch_decompile (mass dump)
// Hash:     7d3890508dbc0e56


undefined4 __thiscall FUN_00665020(byte *param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined4 uVar5;
  uint uVar6;
  short *_Memory;
  void *pvVar7;
  uint local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_4c;
  uint local_48;
  int local_40;
  int local_3c;
  int local_38;
  uint local_1c;
  ushort *local_c;
  uint *local_8;
  
  cVar4 = FUN_00653540(param_2);
  if (cVar4 == '\0') {
    uVar5 = 0;
  }
  else {
    local_c = (ushort *)0x0;
    local_8 = (uint *)0x0;
    uVar6 = FUN_00653a40();
    _Memory = operator_new(uVar6);
    FUN_00653760(_Memory,uVar6);
    if (*_Memory == 0x4d42) {
      iVar2 = *(int *)(_Memory + 5);
      bVar1 = *(byte *)(_Memory + 0xe);
      if ((*param_1 == 0) && (*param_1 = bVar1, *param_1 < 8)) {
        *param_1 = 8;
      }
      if ((*param_1 == 0x20) && (bVar1 < 0x19)) {
        *param_1 = 0x18;
      }
      *(undefined4 *)(param_1 + 4) = *(undefined4 *)(_Memory + 9);
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(_Memory + 0xb);
      *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 4);
      if (*(uint *)(param_1 + 0xc) % 4 != 0) {
        *(uint *)(param_1 + 0xc) = (*(uint *)(param_1 + 0xc) & 0xfffffffc) + 4;
      }
      local_1c = (uint)bVar1 * *(int *)(param_1 + 4) >> 3;
      if (local_1c % 4 != 0) {
        local_1c = (local_1c & 0xfffffffc) + 4;
      }
      if ((bVar1 < 9) && (0xf < *param_1)) {
        pvVar7 = operator_new(0x400);
        for (local_38 = 0; local_38 < 1 << (bVar1 & 0x1f); local_38 = local_38 + 1) {
          *(char *)((int)pvVar7 + local_38 * 4) = (char)_Memory[local_38 * 2 + 0x1c];
          *(undefined1 *)((int)pvVar7 + local_38 * 4 + 1) =
               *(undefined1 *)((int)_Memory + local_38 * 4 + 0x37);
          *(char *)((int)pvVar7 + local_38 * 4 + 2) = (char)_Memory[local_38 * 2 + 0x1b];
          *(undefined1 *)((int)pvVar7 + local_38 * 4 + 3) =
               *(undefined1 *)((int)_Memory + local_38 * 4 + 0x39);
        }
        if (*param_1 == 0x10) {
          local_c = operator_new(0x200);
          for (local_3c = 0; local_3c < 0x100; local_3c = local_3c + 1) {
            local_c[local_3c] = (ushort)((int)(uint)*(byte *)((int)pvVar7 + local_3c * 4 + 2) >> 3);
            local_c[local_3c] =
                 local_c[local_3c] |
                 (ushort)(((int)(uint)*(byte *)((int)pvVar7 + local_3c * 4 + 1) >> 3) << 5);
            local_c[local_3c] =
                 local_c[local_3c] |
                 (ushort)(((int)(uint)*(byte *)((int)pvVar7 + local_3c * 4) >> 3) << 10);
            local_c[local_3c] = local_c[local_3c] | 0x8000;
          }
          *local_c = *local_c & 0x7fff;
        }
        else if (*param_1 == 0x18) {
          local_8 = operator_new(0x400);
          for (local_40 = 0; local_40 < 0x100; local_40 = local_40 + 1) {
            local_8[local_40] = (uint)*(byte *)((int)pvVar7 + local_40 * 4 + 2);
            local_8[local_40] =
                 (uint)*(byte *)((int)pvVar7 + local_40 * 4 + 1) << 8 | local_8[local_40];
            local_8[local_40] =
                 (uint)*(byte *)((int)pvVar7 + local_40 * 4) << 0x10 | local_8[local_40];
            local_8[local_40] = local_8[local_40] | 0xff000000;
          }
          *local_8 = *local_8 & 0xffffff;
        }
        _free(pvVar7);
      }
      switch(*param_1) {
      case 8:
        pvVar7 = operator_new(*(int *)(param_1 + 8) * *(int *)(param_1 + 0xc));
        *(void **)(param_1 + 0x18) = pvVar7;
        iVar3 = *(int *)(param_1 + 0x18);
        for (local_48 = 0; local_48 < *(uint *)(param_1 + 8); local_48 = local_48 + 1) {
          for (local_4c = 0; local_4c < *(uint *)(param_1 + 4); local_4c = local_4c + 1) {
            *(undefined1 *)
             (iVar3 + ((*(int *)(param_1 + 8) + -1) - local_48) * *(int *)(param_1 + 0xc) + local_4c
             ) = *(undefined1 *)((int)_Memory + local_48 * local_1c + local_4c + iVar2);
          }
        }
        break;
      case 0x10:
        pvVar7 = operator_new(*(int *)(param_1 + 8) * *(int *)(param_1 + 0xc) * 2);
        *(void **)(param_1 + 0x18) = pvVar7;
        iVar3 = *(int *)(param_1 + 0x18);
        if (bVar1 < 9) {
          for (local_54 = 0; local_54 < *(uint *)(param_1 + 8); local_54 = local_54 + 1) {
            for (local_58 = 0; local_58 < *(uint *)(param_1 + 4); local_58 = local_58 + 1) {
              *(ushort *)
               (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_54) * *(int *)(param_1 + 0xc) +
                        local_58) * 2) =
                   local_c[*(byte *)((int)_Memory + local_54 * local_1c + local_58 + iVar2)];
            }
          }
        }
        else {
          for (local_5c = 0; local_5c < *(uint *)(param_1 + 8); local_5c = local_5c + 1) {
            for (local_60 = 0; local_60 < *(uint *)(param_1 + 4); local_60 = local_60 + 1) {
              *(short *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) *
                                  *(int *)(param_1 + 0xc) + local_60) * 2) =
                   (short)((int)(uint)*(byte *)((int)_Memory +
                                               local_60 * 3 + local_5c * local_1c + iVar2) >> 3);
              *(ushort *)
               (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc) +
                        local_60) * 2) =
                   *(ushort *)
                    (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc) +
                             local_60) * 2) |
                   (ushort)(((int)(uint)*(byte *)((int)_Memory +
                                                 local_60 * 3 + local_5c * local_1c + iVar2 + 1) >>
                            3) << 5);
              *(ushort *)
               (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc) +
                        local_60) * 2) =
                   *(ushort *)
                    (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc) +
                             local_60) * 2) |
                   (ushort)(((int)(uint)*(byte *)((int)_Memory +
                                                 local_60 * 3 + local_5c * local_1c + iVar2 + 2) >>
                            3) << 10);
              if ((*(char *)((int)_Memory + local_60 * 3 + local_5c * local_1c + iVar2) == '\0' &&
                  *(char *)((int)_Memory + local_60 * 3 + local_5c * local_1c + iVar2 + 1) == '\0')
                  && *(char *)((int)_Memory + local_60 * 3 + local_5c * local_1c + iVar2 + 2) ==
                     '\0') {
                *(ushort *)
                 (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc) +
                          local_60) * 2) =
                     *(ushort *)
                      (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc)
                               + local_60) * 2) & 0x7fff;
              }
              else {
                *(ushort *)
                 (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc) +
                          local_60) * 2) =
                     *(ushort *)
                      (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_5c) * *(int *)(param_1 + 0xc)
                               + local_60) * 2) | 0x8000;
              }
            }
          }
        }
        break;
      case 0x18:
        pvVar7 = operator_new(*(int *)(param_1 + 8) * *(int *)(param_1 + 0xc) * 4);
        *(void **)(param_1 + 0x18) = pvVar7;
        iVar3 = *(int *)(param_1 + 0x18);
        if (bVar1 < 9) {
          for (local_68 = 0; local_68 < *(uint *)(param_1 + 8); local_68 = local_68 + 1) {
            for (local_6c = 0; local_6c < *(uint *)(param_1 + 4); local_6c = local_6c + 1) {
              *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_68) * *(int *)(param_1 + 0xc)
                                + local_6c) * 4) =
                   local_8[*(byte *)((int)_Memory + local_68 * local_1c + local_6c + iVar2)];
            }
          }
        }
        else {
          for (local_70 = 0; local_70 < *(uint *)(param_1 + 8); local_70 = local_70 + 1) {
            for (local_74 = 0; local_74 < *(uint *)(param_1 + 4); local_74 = local_74 + 1) {
              *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) * *(int *)(param_1 + 0xc)
                                + local_74) * 4) =
                   (uint)*(byte *)((int)_Memory + local_74 * 3 + local_70 * local_1c + iVar2);
              *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) * *(int *)(param_1 + 0xc)
                                + local_74) * 4) =
                   (uint)*(byte *)((int)_Memory + local_74 * 3 + local_70 * local_1c + iVar2 + 1) <<
                   8 | *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) *
                                          *(int *)(param_1 + 0xc) + local_74) * 4);
              *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) * *(int *)(param_1 + 0xc)
                                + local_74) * 4) =
                   (uint)*(byte *)((int)_Memory + local_74 * 3 + local_70 * local_1c + iVar2 + 2) <<
                   0x10 | *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) *
                                             *(int *)(param_1 + 0xc) + local_74) * 4);
              if (((*(char *)((int)_Memory + local_74 * 3 + local_70 * local_1c + iVar2) == '\0') &&
                  (*(char *)((int)_Memory + local_74 * 3 + local_70 * local_1c + iVar2 + 1) == -1))
                 && (*(char *)((int)_Memory + local_74 * 3 + local_70 * local_1c + iVar2 + 2) ==
                     '\0')) {
                *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) *
                                   *(int *)(param_1 + 0xc) + local_74) * 4) =
                     *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) *
                                        *(int *)(param_1 + 0xc) + local_74) * 4) & 0xffffff;
              }
              else {
                *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) *
                                   *(int *)(param_1 + 0xc) + local_74) * 4) =
                     *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_70) *
                                        *(int *)(param_1 + 0xc) + local_74) * 4) | 0xff000000;
              }
            }
          }
        }
        break;
      case 0x20:
        pvVar7 = operator_new(*(int *)(param_1 + 8) * *(int *)(param_1 + 0xc) * 4);
        *(void **)(param_1 + 0x18) = pvVar7;
        iVar3 = *(int *)(param_1 + 0x18);
        if (bVar1 < 9) {
          for (local_7c = 0; local_7c < *(uint *)(param_1 + 8); local_7c = local_7c + 1) {
            for (local_80 = 0; local_80 < *(uint *)(param_1 + 4); local_80 = local_80 + 1) {
              *(uint *)(iVar3 + (((*(int *)(param_1 + 8) + -1) - local_7c) * *(int *)(param_1 + 0xc)
                                + local_80) * 4) =
                   local_8[*(byte *)((int)_Memory + local_7c * local_1c + local_80 + iVar2)];
            }
          }
        }
        else {
          for (local_84 = 0; local_84 < *(uint *)(param_1 + 8); local_84 = local_84 + 1) {
            for (local_88 = 0; local_88 < *(uint *)(param_1 + 4); local_88 = local_88 + 1) {
              *(undefined4 *)
               (iVar3 + (((*(int *)(param_1 + 8) + -1) - local_84) * *(int *)(param_1 + 0xc) +
                        local_88) * 4) =
                   *(undefined4 *)((int)_Memory + local_84 * local_1c + local_88 * 4 + iVar2);
            }
          }
        }
      }
      if (local_c != (ushort *)0x0) {
        _free(local_c);
      }
      if (local_8 != (uint *)0x0) {
        _free(local_8);
      }
      _free(_Memory);
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
  }
  return uVar5;
}

