// Function: FUN_006967f0
// Address:  0x006967f0
// Source:   batch_decompile (mass dump)
// Hash:     1fe90524a9650129


int * __thiscall FUN_006967f0(int *param_1,int param_2,int param_3,undefined4 *param_4)

{
  ushort uVar1;
  undefined4 uVar2;
  void *pvVar3;
  undefined2 *puVar4;
  ushort *puVar5;
  undefined2 *puVar6;
  uint local_8;
  
  param_1[3] = 0;
  param_1[1] = 0;
  param_1[2] = param_2;
  if (param_1[2] == 0) {
    *param_1 = 0;
  }
  else {
    pvVar3 = operator_new(param_1[2] << 4);
    *param_1 = (int)pvVar3;
    if (*param_1 == 0) {
      param_1[2] = 0;
      if (param_4 != (undefined4 *)0x0) {
        *param_4 = 0x8007000e;
      }
    }
    else {
      for (local_8 = 0; local_8 < (uint)param_1[2]; local_8 = local_8 + 1) {
        puVar4 = (undefined2 *)(local_8 * 0x10 + *param_1);
        puVar6 = (undefined2 *)(local_8 * 0x10 + param_3);
        *puVar4 = *puVar6;
        switch(*puVar4) {
        case 2:
          puVar4[4] = puVar6[4];
          break;
        case 3:
          *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(puVar6 + 4);
          break;
        case 4:
          *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(puVar6 + 4);
          break;
        case 5:
          *(undefined8 *)(puVar4 + 4) = *(undefined8 *)(puVar6 + 4);
          break;
        case 6:
          uVar2 = *(undefined4 *)(puVar6 + 6);
          *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(puVar6 + 4);
          *(undefined4 *)(puVar4 + 6) = uVar2;
          break;
        case 7:
          *(undefined8 *)(puVar4 + 4) = *(undefined8 *)(puVar6 + 4);
          break;
        case 8:
          if (*(int *)(puVar6 + 4) == 0) {
            *(undefined4 *)(puVar4 + 4) = 0;
          }
          else {
            uVar1 = *(ushort *)(*(int *)(puVar6 + 4) + -2);
            puVar5 = operator_new((uint)uVar1 * 2 + 2);
            if (puVar5 == (ushort *)0x0) {
              param_1[2] = local_8;
              if (param_4 != (undefined4 *)0x0) {
                *param_4 = 0x8007000e;
              }
            }
            else {
              *puVar5 = uVar1;
              *(ushort **)(puVar4 + 4) = puVar5 + 1;
              _memcpy(*(void **)(puVar4 + 4),*(void **)(puVar6 + 4),(uint)uVar1 << 1);
            }
          }
          *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(puVar6 + 4);
          break;
        case 9:
          *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(puVar6 + 4);
          (**(code **)(**(int **)(puVar4 + 4) + 4))(*(undefined4 *)(puVar4 + 4));
          break;
        case 10:
          *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(puVar6 + 4);
          break;
        case 0xb:
          puVar4[4] = puVar6[4];
          break;
        case 0xd:
          *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(puVar6 + 4);
          (**(code **)(**(int **)(puVar4 + 4) + 4))(*(undefined4 *)(puVar4 + 4));
          break;
        case 0x11:
          *(undefined1 *)(puVar4 + 4) = *(undefined1 *)(puVar6 + 4);
        }
      }
    }
  }
  return param_1;
}

