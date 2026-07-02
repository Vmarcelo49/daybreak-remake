// Function: FUN_006515c0
// Address:  0x006515c0
// Source:   batch_decompile (mass dump)
// Hash:     b3b7b74d02bd7aee


void __thiscall FUN_006515c0(int param_1,int param_2)

{
  int *local_a0;
  float local_9c;
  float local_98;
  undefined1 local_94 [24];
  uint local_7c;
  uint local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  _vector_constructor_iterator_(&local_74,0x1c,4,FUN_0068d8d0);
  (**(code **)(**(int **)(param_1 + 0x30 + param_2 * 4) + 0x48))
            (*(undefined4 *)(param_1 + 0x30 + param_2 * 4),0,&local_a0);
  (**(code **)(*local_a0 + 0x30))(local_a0,local_94);
  local_9c = (float)local_7c / 4.0;
  local_98 = (float)local_78 / 4.0;
  (**(code **)(*local_a0 + 8))(local_a0);
  local_74 = 0xbf000000;
  local_70 = 0xbf000000;
  local_6c = 0;
  local_68 = 0x3f800000;
  local_58 = local_9c - 0.5;
  local_54 = 0xbf000000;
  local_50 = 0;
  local_4c = 0x3f800000;
  local_3c = 0xbf000000;
  local_38 = local_98 - 0.5;
  local_34 = 0;
  local_30 = 0x3f800000;
  local_20 = local_9c - 0.5;
  local_1c = local_98 - 0.5;
  local_18 = 0;
  local_14 = 0x3f800000;
  local_60 = 0;
  local_5c = 0;
  local_44 = 0x3f800000;
  local_40 = 0;
  local_28 = 0;
  local_24 = 0x3f800000;
  local_c = 0x3f800000;
  local_8 = 0x3f800000;
  local_10 = 0xffffffff;
  local_2c = 0xffffffff;
  local_48 = 0xffffffff;
  local_64 = 0xffffffff;
  (**(code **)(*DAT_006d16f8 + 0x170))(DAT_006d16f8,0);
  (**(code **)(*DAT_006d16f8 + 0x164))(DAT_006d16f8,0x144);
  (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8,0,*(undefined4 *)(param_1 + 0x30 + param_2 * 4))
  ;
  (**(code **)(*DAT_006d16f8 + 0x14c))(DAT_006d16f8,5,2,&local_74,0x1c);
  return;
}

