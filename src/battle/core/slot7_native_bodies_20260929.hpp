// NEW all46 whole-slot7 handlers. Generation is not a native/world proof.
#pragma once
inline void slot7_body_0_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 100;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) || (((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && (299 < (n.w[0x2b7b])))) && ((n.w[0x2b7b]) < 0x15e)))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if (((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || (((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda)) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118)))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xbb2])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x15e);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.w[0x20d]) < 1) || ((((n.byte(0x84)) == '\0') || ((n.w[0xcca]) < (n.current_priority()))) || (((n.frame_flags) & 0x100) == 0))))
    {
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xc3e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x172);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x168);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x198);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d))) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_0_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xbb2])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x15e);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xc3e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x172);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x168);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xb34])) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && ((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_0_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x32;
  n.w[0x1f4] = 0x32;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((((n.current_priority()) <= (n.w[0x2dd])) || (((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && (299 < (n.w[0x2b7b])))) && ((n.w[0x2b7b]) < 0x15e))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0'))))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.w[0x20d]) < 1) || ((((n.byte(0x84)) == '\0') || ((n.w[0xcca]) < (n.current_priority()))) || (((n.frame_flags) & 0x100) == 0))))
    {
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((((n.w[0x9f]) < 0) && ((n.w[0x2b7b]) != 0x136)) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) != 0x137)) && (((n.current_priority()) <= (n.w[0xaa1])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((n.w[0x2b7b]) != 300) && ((((n.current_priority()) <= (n.w[0xa54])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_1_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.w[0x20d]) < 1) || ((((n.byte(0x84)) == '\0') || ((n.w[0xcca]) < (n.current_priority()))) || (((n.frame_flags) & 0x100) == 0))))
    {
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c6);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1b) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c5);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if (0 < (n.w[0x9e]))
            {
              n.FUN_00421080(0x19b);
              return;
            }
            if ((n.w[0x9e]) < 0)
            {
              n.FUN_00421080(0x19c);
              return;
            }
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x19a);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x191);
              return;
            }
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154)))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && (((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_1_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (1 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((0 < (n.w[0x9e])) && ((n.current_priority()) <= (n.w[0xd5d])))
            {
              n.FUN_00421080(0x19b);
              return;
            }
            if (((n.w[0x9e]) < 0) && ((n.current_priority()) <= (n.w[0xd64])))
            {
              n.FUN_00421080(0x19c);
              return;
            }
            if (((n.w[0x9f]) < 0) && ((n.current_priority()) <= (n.w[0xd56])))
            {
              n.FUN_00421080(0x19a);
              return;
            }
            if ((0 < (n.w[0x9f])) && ((n.current_priority()) <= (n.w[0xd17])))
            {
              n.FUN_00421080(0x191);
              return;
            }
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154)))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && (((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_1_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154)))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && (((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_2_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.w[0x20d]) < 1) || ((((n.byte(0x84)) == '\0') || ((n.w[0xcca]) < (n.current_priority()))) || (((n.frame_flags) & 0x100) == 0))))
    {
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x198);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d))) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_2_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d))) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_2_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.w[0x20d]) < 1) || ((((n.byte(0x84)) == '\0') || ((n.w[0xcca]) < (n.current_priority()))) || (((n.frame_flags) & 0x100) == 0))))
    {
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if (((n.real(0x64)) <= slot7_word_real(0x42c80000u)) && (slot7_word_real(0xc2c80000u) <= (n.real(0x64))))
            {
              n.FUN_00421080(0x191);
              return;
            }
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d))) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_3_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && ((((n.current_priority()) <= (n.w[0x2c1])) || (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c8])) || (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), (uVar4 & 1) != 0))) && (((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)) && (((n.w[0x2b7b]) != 0x140) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7d]) == 1)) && ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xebb]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cd);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe75])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1b) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe7c]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_3_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && ((((n.current_priority()) <= (n.w[0x2c1])) || ((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 == 0)))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if ((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((((n.current_priority()) <= (n.w[0x2c1])) || ((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 == 0)))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), (uVar4 & 1) != 0))) && (((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)) && (((n.w[0x2b7b]) != 0x140) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x9f]) < 0) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x9e]) != 0) && ((n.current_priority()) <= (n.w[0xe7c]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && (((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_3_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && ((((n.current_priority()) <= (n.w[0x2c1])) || (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c8])) || (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if ((((n.byte(0x318)) == '\x01') && ((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0'))) && ((n.w[0xcb]) <= (n.w[0x20f])))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7d]) == 1)) && ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xebb]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe75])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1b) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe7c]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_4_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x73;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((((n.current_priority()) <= (n.w[0xc3e])) && ((piVar4 = n.FUN_00658a10(0), n.global_actor_word(n.partner_word(*piVar4, 0x8)) == 3))) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || ((n.byte(0x844)) != '\0')) || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7d]) == 1)) && (((n.w[0x2b7b]) == 0x1e) || ((n.w[0x2b7b]) == 0x198))) && ((n.current_priority()) <= (n.w[0xebb]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cd);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) == 1) && ((n.current_priority()) <= (n.w[0xd48])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x198);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb6c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb6c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb26])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x14a))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && ((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x14a)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_4_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x73;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((((n.current_priority()) <= (n.w[0xc3e])) && ((piVar4 = n.FUN_00658a10(0), n.global_actor_word(n.partner_word(*piVar4, 0x8)) == 3))) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || ((n.byte(0x844)) != '\0')) || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (1 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) == 1) && ((n.current_priority()) <= (n.w[0xebb])))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cd);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) == 1) && ((n.current_priority()) <= (n.w[0xd48])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x198);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb6c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb6c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb26])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && ((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_4_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x78;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && (((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0'))) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0')))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7d]) == 1)) && (((n.w[0x2b7b]) == 0x1e) || ((n.w[0x2b7b]) == 0x198))) && ((n.current_priority()) <= (n.w[0xebb]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x1cd);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x1cd);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x1c5);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x1c5);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c5);
            if ((n.w[0x9e]) < 1)
            {
              return;
            }
            n.FUN_00421080(0x1c4);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x1c5);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) == 1) && ((n.current_priority()) <= (n.w[0xd48])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((n.w[0x2b7b]) == 0x154) && ((((n.current_priority()) <= (n.w[0xb73])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)))) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x14a))) && ((n.w[0x2b7b]) != 0x155))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d))) && ((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x14a)) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && ((n.w[0x2b7b]) != 0x14a)) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_5_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x73;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((n.w[0x20c]) == 4) && (0 < (n.w[0x20d])))
  {
    if ((n.w[0x2c1]) < (n.current_priority()))
    {
      if (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13))
      {
        n.FUN_0042c7b0();
      }
    }
    else
      if (((n.frame_flags) & 0x100) != 0)
    {
      if ((n.byte(0x84)) != '\0')
      {
        n.FUN_00421080(0x17);
        return;
      }
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((n.w[0x20c]) == 3) && (0 < (n.w[0x20d])))
  {
    if ((n.w[0x2c8]) < (n.current_priority()))
    {
      if (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13))
      {
        n.FUN_0042c7b0();
      }
    }
    else
      if (((n.frame_flags) & 0x100) != 0)
    {
      if ((n.byte(0x84)) != '\0')
      {
        n.FUN_00421080(0x18);
        return;
      }
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), (uVar4 & 1) != 0))) && (((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)) && (((n.w[0x2b7b]) != 0x140) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && (((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')))) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0')))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((0 < (n.w[0x9f])) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_5_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x73;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) || (((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) || ((n.current_priority()) == 0x59)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 == 0))))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) != '\0')
    {
      n.FUN_00421080(0x17);
      return;
    }
    if ((n.w[0x2b7b]) != 0x192)
    {
      n.FUN_00421080(0x1e);
      return;
    }
    if (499 < (n.w[0x20d]))
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], -500);
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c8])) || (((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) || ((n.current_priority()) == 0x59)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 == 0))))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) != '\0')
    {
      n.FUN_00421080(0x18);
      return;
    }
    if ((n.w[0x2b7b]) != 0x192)
    {
      n.FUN_00421080(0x1e);
      return;
    }
    if (499 < (n.w[0x20d]))
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], -500);
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), (uVar4 & 1) != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))) && (((n.w[0x2b7b]) != 0x140) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && (((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')))) && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((0 < (n.w[0x9f])) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_5_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x73;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((n.w[0x20c]) == 4) && (0 < (n.w[0x20d])))
  {
    if ((n.w[0x2c1]) < (n.current_priority()))
    {
      if (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13))
      {
        n.FUN_0042c7b0();
      }
    }
    else
      if (((n.frame_flags) & 0x100) != 0)
    {
      if ((n.byte(0x84)) != '\0')
      {
        n.FUN_00421080(0x17);
        return;
      }
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((n.w[0x20c]) == 3) && (0 < (n.w[0x20d])))
  {
    if ((n.w[0x2c8]) < (n.current_priority()))
    {
      if (((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13))
      {
        n.FUN_0042c7b0();
      }
    }
    else
      if (((n.frame_flags) & 0x100) != 0)
    {
      if ((n.byte(0x84)) != '\0')
      {
        n.FUN_00421080(0x18);
        return;
      }
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), (uVar4 & 1) != 0))) && (((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)) && (((n.w[0x2b7b]) != 0x140) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && (((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')))) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0')))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((0 < (n.w[0x9f])) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_6_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5a;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) || (((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) || ((n.current_priority()) == 0x62)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 == 0))))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c8])) || (((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) || ((n.current_priority()) == 0x62)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 == 0))))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), (uVar4 & 1) != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))) && (((n.w[0x2b7b]) != 0x140) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((((std::uint32_t(n.w[0xa2])) < 3) && (((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0'))) && ((n.byte(0x845)) == '\0'))) && ((n.byte(0x846)) == '\0'))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x19a);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x19d);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x19b);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x19c);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_6_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0'))))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && (((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99))) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_6_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((n.w[0x20c]) == 4) && (0 < (n.w[0x20d])))
  {
    if ((n.w[0x2c1]) < (n.current_priority()))
    {
      if ((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) || ((n.current_priority()) == 0x62))
      {
        n.FUN_0042c7b0();
      }
    }
    else
      if (((n.frame_flags) & 0x100) != 0)
    {
      if ((n.byte(0x84)) != '\0')
      {
        n.FUN_00421080(0x17);
        return;
      }
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((n.w[0x20c]) == 3) && (0 < (n.w[0x20d])))
  {
    if ((n.w[0x2c8]) < (n.current_priority()))
    {
      if ((((n.current_priority()) == 0x27) || ((n.current_priority()) == 0x13)) || ((n.current_priority()) == 0x62))
      {
        n.FUN_0042c7b0();
      }
    }
    else
      if (((n.frame_flags) & 0x100) != 0)
    {
      if ((n.byte(0x84)) != '\0')
      {
        n.FUN_00421080(0x18);
        return;
      }
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), (uVar4 & 1) != 0))) && (((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)) && (((n.w[0x2b7b]) != 0x140) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((((std::uint32_t(n.w[0xa2])) < 3) && (((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0'))) && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0')))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd41]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x428c0000u)) && (slot7_word_real(0xc28c0000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x428c0000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc28c0000u)) != ((n.real(0x64)) == slot7_word_real(0xc28c0000u)))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_7_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c6);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1b) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c5);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_7_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1b) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (2 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x191);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.FUN_00421080(0x191);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_00421080(400);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_00421080(400);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_7_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if (((n.real(0x14)) < (n.real(0xaf60))) && ((n.set_real(0xaf6c, (n.real(0xaf6c)) - slot7_word_real(0x3d4ccccdu)), (n.real(0xaf6c)) < slot7_word_real(0xc0800000u))))
  {
    n.w[0x2bdb] = 0xc0800000;
  }
  if (((n.real(0xaf60)) < (n.real(0x14))) && ((n.set_real(0xaf6c, (n.real(0xaf6c)) + slot7_word_real(0x3d4ccccdu)), slot7_word_real(0x40800000u) < (n.real(0xaf6c)))))
  {
    n.w[0x2bdb] = 0x40800000;
  }
  if (((n.real(0x1c)) < (n.real(0xaf68))) && ((n.set_real(0xaf70, (n.real(0xaf70)) - slot7_word_real(0x3d4ccccdu)), (n.real(0xaf70)) < slot7_word_real(0xc0800000u))))
  {
    n.w[0x2bdc] = 0xc0800000;
  }
  if (((n.real(0xaf68)) < (n.real(0x1c))) && ((n.set_real(0xaf70, (n.real(0xaf70)) + slot7_word_real(0x3d4ccccdu)), slot7_word_real(0x40800000u) < (n.real(0xaf70)))))
  {
    n.w[0x2bdc] = 0x40800000;
  }
  n.set_real(0xaf60, (n.real(0xaf60)) + (n.real(0xaf6c)));
  n.set_real(0xaf68, (n.real(0xaf68)) + (n.real(0xaf70)));
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.w[0x2b7d]) < 2)) && (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1b) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if (((n.real(0x64)) <= slot7_word_real(0x42c80000u)) && (slot7_word_real(0xc2c80000u) <= (n.real(0x64))))
            {
              n.FUN_00421080(0x191);
              return;
            }
            n.FUN_00421080(400);
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_8_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x4b;
  n.w[0x1f4] = 100;
  if ((((((n.w[0x2b7b]) == 300) && ((n.w[0x2b7d]) == 1)) || (((n.w[0x2b7b]) == 0x136) && ((n.w[0x2b7d]) == 1))) || (((n.w[0x2b7b]) == 0x140) && ((n.w[0x2b7d]) == 1))) || ((((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)) || ((((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)) || (((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)))))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3f666666u);
    n.w[0x1f4] = uVar3;
  }
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) == '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && ((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x154)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_8_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if (0 < (n.w[0x2bd8]))
  {
    n.w[0x2bd9] = slot7_word_add(n.w[0x2bd9], -1);
    if (((n.w[0x2bd9]) < 1) && ((n.w[0x2b7b]) < 500))
    {
      n.FUN_00422bd0(0x71, 0xc6, 0, 1, 0, 0x43fa0000, 0x43fa0000);
      n.w[0x2bd8] = 0;
      n.w[0x2bd9] = 0;
      if ((n.byte(0x84)) != '\0')
      {
        n.FUN_00421080(0x189);
        return;
      }
      n.FUN_00421080(0x18a);
      return;
    }
    if ((99 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 300))
    {
      n.FUN_00422bd0(0x71, 0xc6, 0, 1, 0, 0x43fa0000, 0x43fa0000);
      n.w[0x2bd8] = 0;
      n.w[0x2bd9] = 0;
    }
  }
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x4b;
  n.w[0x1f4] = 100;
  if ((((((n.w[0x2b7b]) == 300) && ((n.w[0x2b7d]) == 1)) || (((n.w[0x2b7b]) == 0x136) && ((n.w[0x2b7d]) == 1))) || (((n.w[0x2b7b]) == 0x140) && ((n.w[0x2b7d]) == 1))) || ((((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)) || ((((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)) || (((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)))))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
    n.w[0x1f4] = uVar3;
  }
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
      {
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) == '\0')))
        {
          n.FUN_00421080(0x172);
          return;
        }
        if (((((n.current_priority()) <= (n.w[0xbb2])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
        {
          n.FUN_00421080(0x15e);
          return;
        }
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if ((((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0)) && ((n.w[0x2bd8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x169);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          if ((n.w[0x2bd8]) == 0)
          {
            return;
          }
          n.FUN_00421080(0x15f);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((0 < (n.w[0x1b7])) || ((n.w[0x2bd8]) != 0)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x194);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x194);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x191);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x14f);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x14f);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) || ((n.w[0x2b7b]) == 0x131)) && (((n.current_priority()) <= (n.w[0xa5b])) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && ((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x131)) && (((n.w[0x2b7b]) != 300) && (((n.w[0x2b7b]) != 0x12d) && ((n.w[0x2b7b]) != 0x12e)))) && ((n.w[0x2b7b]) != 0x140)) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            if ((n.w[0x2bd8]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x131);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_8_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x4b;
  n.w[0x1f4] = 100;
  if ((((((n.w[0x2b7b]) == 300) && ((n.w[0x2b7d]) == 1)) || (((n.w[0x2b7b]) == 0x136) && ((n.w[0x2b7d]) == 1))) || (((n.w[0x2b7b]) == 0x140) && ((n.w[0x2b7d]) == 1))) || ((((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)) || ((((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)) || (((n.w[0x2b7b]) == 0x14a) && ((n.w[0x2b7d]) == 1)))))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
    n.w[0x1f4] = uVar3;
  }
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0))))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) == '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if (((n.w[0x2bd8]) == 5) || ((n.w[0x2bd8]) == 6))
            {
              n.FUN_00421080(0x1cf);
            }
            if ((n.w[0x2bd8]) == 7)
            {
              n.FUN_00421080(0x1c3);
            }
            if ((n.w[0x2bd8]) == 8)
            {
              n.FUN_00421080(0x1d0);
            }
            if ((n.w[0x2bd8]) != 9)
            {
              return;
            }
            n.FUN_00421080(0x1d1);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
          n.FUN_00421080(0x1c2);
          if (((n.w[0x2bd8]) == 5) || ((n.w[0x2bd8]) == 6))
          {
            n.FUN_00421080(0x1c5);
          }
          if ((n.w[0x2bd8]) == 7)
          {
            n.FUN_00421080(0x1c3);
          }
          if ((n.w[0x2bd8]) == 8)
          {
            n.FUN_00421080(0x1c6);
          }
          if ((n.w[0x2bd8]) != 9)
          {
            return;
          }
          n.FUN_00421080(0x1c7);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            if ((n.w[0x2bd8]) == 2)
            {
              n.FUN_00421080(0x158);
            }
            if ((n.w[0x2bd8]) == 3)
            {
              n.FUN_00421080(0x156);
            }
            if ((n.w[0x2bd8]) != 4)
            {
              return;
            }
            n.FUN_00421080(0x157);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            if ((n.w[0x2bd8]) == 2)
            {
              n.FUN_00421080(0x152);
            }
            if ((n.w[0x2bd8]) == 3)
            {
              n.FUN_00421080(0x150);
            }
            if ((n.w[0x2bd8]) != 4)
            {
              return;
            }
            n.FUN_00421080(0x151);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            if ((n.w[0x2bd8]) == 2)
            {
              n.FUN_00421080(0x152);
            }
            if ((n.w[0x2bd8]) == 3)
            {
              n.FUN_00421080(0x150);
            }
            if ((n.w[0x2bd8]) != 4)
            {
              return;
            }
            n.FUN_00421080(0x151);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            if ((n.w[0x2bd8]) == 2)
            {
              n.FUN_00421080(0x158);
            }
            if ((n.w[0x2bd8]) == 3)
            {
              n.FUN_00421080(0x156);
            }
            if ((n.w[0x2bd8]) != 4)
            {
              return;
            }
            n.FUN_00421080(0x157);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if (((((n.w[0x2b7b]) == 300) || ((n.w[0x2b7b]) == 0x131)) || (((n.w[0x2b7b]) == 0x132) || ((n.w[0x2b7b]) == 0x133))) && (((n.current_priority()) <= (n.w[0xa5b])) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if (((n.w[0x2bd8]) == 4) && ((((n.current_priority()) <= (n.w[0xa7e])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x132)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)))) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x132);
            return;
          }
          if ((((n.w[0x2bd8]) == 3) && (((n.current_priority()) <= (n.w[0xa77])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && ((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x131)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x131);
            return;
          }
          if ((((n.w[0x2bd8]) == 2) && (((n.current_priority()) <= (n.w[0xa85])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x133)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154))))) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x133);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))))) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_9_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 100;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 2) && (0 < (n.w[0x1c8]))))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((n.w[0x2b7b]) != 0x156)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x155) && ((n.current_priority()) <= (n.w[0xb7a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x156);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x156)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_9_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1cd);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1cd);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c3);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((n.w[0x2b7b]) != 0x156)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x155) && ((n.current_priority()) <= (n.w[0xb7a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x156);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x156)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_9_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  if (((n.w[0x2b7b]) == 0x15e) || ((n.w[0x2b7b]) == 0x168))
  {
    n.w[0x1f2] = slot7_word_add((n.w[0x3d]) * 0x28, n.w[0x1f2]);
  }
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd10]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((n.w[0x2b7b]) != 0x156)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x155) && ((n.current_priority()) <= (n.w[0xb7a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x156);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x156)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_10_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 100;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if (((((n.w[0x2b7b]) == 0x14) || ((n.w[0x2b7b]) == 0x17)) || (((n.w[0x2b7b]) == 0x18) || ((n.w[0x2b7b]) == 0x1b))) && (((n.current_priority()) <= (n.w[0xe75])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_10_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 100;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if (((((n.w[0x2b7b]) == 0x14) || ((n.w[0x2b7b]) == 0x17)) || (((n.w[0x2b7b]) == 0x18) || ((n.w[0x2b7b]) == 0x1b))) && (((n.current_priority()) <= (n.w[0xe75])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_10_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 100;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if (((((n.w[0x2b7b]) == 0x14) || ((n.w[0x2b7b]) == 0x17)) || (((n.w[0x2b7b]) == 0x18) || ((n.w[0x2b7b]) == 0x1b))) && (((n.current_priority()) <= (n.w[0xe75])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && (((n.w[0x2b7b]) != 0x12d) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x140) && ((n.w[0x2b7b]) != 0x154)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && (((n.frame_flags) & 0x100) != 0))) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_11_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0'))))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.w[0x2b7b]) == 0x1a6) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x1a7);
            return;
          }
          if (((n.w[0x2b7b]) == 0x192) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x1a6);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if (((n.w[0x2b7b]) == 0x1a4) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x1a5);
            return;
          }
          if (((n.w[0x2b7b]) == 400) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x1a4);
            return;
          }
          if (((n.w[0x2b7b]) == 0x14a) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14f);
            return;
          }
          if (((n.w[0x2b7b]) == 0x12e) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12f);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x2b7b]) == 0x14b) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x150);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((0 < (n.w[0x9f])) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x14b))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x14b)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_11_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0'))))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.w[0x2b7b]) == 0x192) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x1a5);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 400) || ((n.w[0x2b7b]) == 0x191)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x1a4);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x2b7b]) == 0x14b) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x150);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((0 < (n.w[0x9f])) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x14b))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x14b)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_11_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')) && (((n.byte(0x845)) == '\0') && ((n.byte(0x846)) == '\0'))))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar5 = n.FUN_00658a10(0);
        iVar1 = *piVar5;
        piVar5 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x2b7b]) == 0x14b) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x150);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if (((0 < (n.w[0x9f])) && (((n.current_priority()) <= (n.w[0xaa8])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x14b))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x14b)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_12_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if ((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && ((((n.frame_flags) & 0x100) != 0) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_12_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && ((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.w[0x2b7d]) < 2)))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c6);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && ((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.w[0x2b7d]) < 2)))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))) && ((n.w[0x2b7d]) < 2))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c4);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))) && ((n.w[0x2b7d]) < 2))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c5);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x194);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x195);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd41]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && ((((n.frame_flags) & 0x100) != 0) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_12_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0x2b7b]) != 0x15e)
  {
    n.FUN_00422f40();
  }
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x5f;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if ((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((n.w[0x9f]) < 0)
            {
              n.FUN_00421080(0x191);
              return;
            }
            if (0 < (n.w[0x9f]))
            {
              n.FUN_00421080(0x191);
              return;
            }
            if (0 < (n.w[0x9e]))
            {
              n.set_real(0x64, (n.real(0x64)) + slot7_word_real(0x42b40000u));
              n.FUN_00421080(0x191);
              return;
            }
            if ((-1) < (n.w[0x9e]))
            {
              return;
            }
            n.set_real(0x64, (n.real(0x64)) - slot7_word_real(0x42b40000u));
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)))) && ((n.w[0x2b7b]) != 0x12d)) && ((((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || (((n.current_priority()) == 0x31) || ((n.current_priority()) == 99))) && ((((n.frame_flags) & 0x100) != 0) && (((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_13_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 2) && (0 < (n.w[0x1c8]))))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x198);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.w[0x9f]) < 0) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((n.w[0x2b7b]) != 0x156)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x155) && ((n.current_priority()) <= (n.w[0xb7a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x156);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x156)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_13_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1ce);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1ce);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c4);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c4);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c4);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c4);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c4);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            if ((n.byte(0x845)) == '\0')
            {
              return;
            }
            if ((n.w[0x212]) == 0)
            {
              return;
            }
            n.FUN_00421080(0x1c4);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((n.w[0x2b7b]) != 0x156)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x155) && ((n.current_priority()) <= (n.w[0xb7a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x156);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x156)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_13_2(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((n.w[0x20c]) == 2) && (((0 < (n.w[0x20d])) && ((n.current_priority()) <= (n.w[0x2dd]))) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if (((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((std::uint32_t(n.w[0xa2])) < 3)) && ((std::uint32_t(n.w[0xa1])) < 3))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if ((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && ((((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0'))) && ((n.byte(0x84)) != '\0')))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 2) && (0 < (n.w[0x1c8]))))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if ((((n.w[0x9f]) < 0) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))) && ((n.w[0x2b7b]) != 0x156)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x155) && ((n.current_priority()) <= (n.w[0xb7a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x156);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && (((n.w[0x2b7b]) != 0x154) && (((n.w[0x2b7b]) != 0x155) && ((n.w[0x2b7b]) != 0x156)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && (((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_14_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0x20a]) != 0)
  {
    n.w[0x1eb] = 3;
  }
  if (((n.w[0xa2]) != 0) && ((n.w[0x20a]) == 0))
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x6e;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar4 = n.FUN_00658a10(0);
          iVar1 = *piVar4;
          piVar4 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7d]) == 1)) && (((n.w[0x2b7b]) == 0x1e) || ((n.w[0x2b7b]) == 0x198))) && ((n.current_priority()) <= (n.w[0xebb]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && (((n.w[0x2b7d]) == 1) && ((n.current_priority()) <= (n.w[0xd48])))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb6c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb6c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x14a))) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && ((((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && ((n.w[0x2b7b]) != 0x14a)) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && (((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0'))) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_14_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 0x5a;
  n.w[0x1f3] = 0x73;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(4);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fcccccdu);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3eb33333u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    n.w[0x1e9] = slot7_word_add(n.w[0x1e9], 3);
    uVar3 = n.slot7_ftol(0x7c8, 0x3fe00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e4ccccdu);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && ((((std::uint32_t(n.w[0xa2])) < 3) && ((((std::uint32_t(n.w[0xa1])) < 3) && ((n.byte(0x844)) == '\0')) && ((n.byte(0x845)) == '\0'))) && ((n.byte(0x846)) == '\0')))
    {
      if ((n.byte(0x318)) == '\0')
      {
        if ((((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || ((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda))) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
        {
          if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
          {
            n.w[0x3b] = 0;
          }
          else
          {
            n.w[0x3b] = 1;
          }
          if ((n.byte(0x84)) != '\0')
          {
            n.FUN_00421080(500);
            return;
          }
          n.FUN_00421080(0x1f5);
          return;
        }
      }
      else
        if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
      {
        n.FUN_004220e0();
        n.w[0xa4] = 0x14;
        n.w[0xa2] = 0x14;
        n.w[0xa1] = 0x14;
        piVar4 = n.FUN_00658a10(0);
        iVar1 = *piVar4;
        piVar4 = n.FUN_00658a10(0);
        if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar4, 0x83c))) < 0x78) && ((piVar4 = n.FUN_00658a10(0), (n.partner_byte(*piVar4, 0x845)) != '\0')))
        {
          n.FUN_00422240(0x23, 0x1e, 0);
          return;
        }
        n.FUN_00422240(0x24, 0x1e, 0);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.byte(0x84)) == '\0') || (((n.w[0xcca]) < (n.current_priority())) || (((n.frame_flags) & 0x100) == 0))))
    {
      if ((0 < (n.w[0xae])) && (((n.w[0x1cc]) == 1) && ((n.w[0x1c8]) == 0)))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            if (((n.byte(0x845)) == '\0') && (((n.byte(0x846)) == '\0') && ((n.byte(0x844)) == '\0')))
            {
              return;
            }
            n.FUN_00421080(0x169);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          if (((n.byte(0x845)) == '\0') && (((n.byte(0x846)) == '\0') && ((n.byte(0x844)) == '\0')))
          {
            return;
          }
          n.FUN_00421080(0x15f);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.w[0x2b7d]) == 1)) && (((n.w[0x2b7b]) == 0x1e) || ((n.w[0x2b7b]) == 0x198))) && ((n.current_priority()) <= (n.w[0xebb]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe75]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c3);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd2c]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x194);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x197);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd10])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            if ((slot7_word_real(0x42c80000u) < (n.real(0x64))) || ((n.real(0x64)) < slot7_word_real(0xc2c80000u)))
            {
              n.FUN_00421080(400);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0x42200000u)) && (slot7_word_real(0xc2200000u) < (n.real(0x64))))
            {
              n.FUN_004211f0(0x19a);
              return;
            }
            if (slot7_word_real(0x42200000u) <= (n.real(0x64)))
            {
              n.FUN_004211f0(0x19c);
              return;
            }
            if (((n.real(0x64)) < slot7_word_real(0xc2200000u)) != ((n.real(0x64)) == slot7_word_real(0xc2200000u)))
            {
              n.FUN_004211f0(0x19b);
              return;
            }
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if ((((n.byte(0x845)) == '\0') && ((n.byte(0x844)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
        {
          if ((n.byte(0x84)) == '\0')
          {
            if ((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && (((n.w[0x2b7b]) == 0x1e) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0))))
            {
              n.FUN_00421080(0x140);
              return;
            }
            if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
            {
              n.FUN_00421080(0x140);
              return;
            }
          }
          else
          {
            if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
            {
              n.FUN_00421080(0x14b);
              return;
            }
            if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
            {
              n.FUN_00421080(0x14a);
              return;
            }
            if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
            {
              n.FUN_00421080(0x14a);
              return;
            }
            if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
            {
              n.FUN_00421080(0x14b);
              return;
            }
            if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
            {
              n.FUN_00421080(0x136);
              return;
            }
            if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
            {
              n.FUN_00421080(0x137);
              return;
            }
            if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && (((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x14a)))) && ((n.w[0x2b7b]) != 0x154))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
            {
              n.FUN_00421080(0x154);
              return;
            }
            if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
            {
              n.FUN_00421080(0x12d);
              return;
            }
            if ((((n.current_priority()) <= (n.w[0xa54])) || ((((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((n.w[0x2b7b]) != 0x12d)) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140))) && (((n.w[0x2b7b]) != 0x14a) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
            {
              n.FUN_00421080(300);
              return;
            }
          }
        }
      }
      else
        if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x9e]) != 0) || ((n.w[0x9f]) != 0)) && ((n.w[0x2b7b]) == 0x1e)) && ((((n.w[0x2b7d]) < 2) && ((n.current_priority()) <= (n.w[0xae0]))) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x140);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if ((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && (((n.current_priority()) <= (n.w[0xb50])) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x150);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb49]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14f);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb49]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14f);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && (((n.current_priority()) <= (n.w[0xb50])) && (((n.frame_flags) & 0x100) != 0)))
          {
            n.FUN_00421080(0x150);
            return;
          }
          if ((((n.w[0x9f]) < 0) && (((n.current_priority()) <= (n.w[0xaa8])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x138))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x138);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaaf])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x139))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x139);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb73])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x12e))) && ((n.w[0x2b7b]) != 0x12f)) && ((((n.w[0x2b7b]) != 0x130) && ((n.w[0x2b7b]) != 0x14f)) && ((n.w[0x2b7b]) != 0x155)))))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12f) && ((n.current_priority()) <= (n.w[0xa70]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x130);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12e) && ((n.current_priority()) <= (n.w[0xa69]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12f);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa62])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x12e)) && ((n.w[0x2b7b]) != 0x12f)) && (((n.w[0x2b7b]) != 0x130) && ((n.w[0x2b7b]) != 0x140))))) && ((n.w[0x2b7b]) != 0x14f)) && ((n.w[0x2b7b]) != 0x154))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(0x12e);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if (((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && (((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99))) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d]))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_15_0(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if (((n.w[0xa2]) != 0) && ((n.w[0x2b7b]) != 0x15f))
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) || (((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && (299 < (n.w[0x2b7b])))) && ((n.w[0x2b7b]) < 0x15e)))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if (((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || (((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda)) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118)))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.w[0x20d]) < 1) || ((((n.byte(0x84)) == '\0') || ((n.w[0xcca]) < (n.current_priority()))) || (((n.frame_flags) & 0x100) == 0))))
    {
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x198);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd17]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d))) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

inline void slot7_body_15_1(Slot7BodyContext& n)
{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  if ((n.w[0xa2]) != 0)
  {
    n.FUN_0043f3e0();
  }
  n.w[0x1f2] = 100;
  n.w[0x1f3] = 0x69;
  n.w[0x1f4] = 100;
  n.FUN_00435560(1);
  if (0 < (n.w[0x1fd]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3e800000u);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f8]))
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3f99999au);
    n.w[0x1f2] = uVar3;
  }
  if (0 < (n.w[0x1f9]))
  {
    uVar3 = n.slot7_ftol(0x7cc, 0x3f4ccccdu);
    n.w[0x1f3] = uVar3;
  }
  if ((n.byte(0x846)) == '\0')
  {
    if ((n.byte(0x844)) == '\0')
    {
      if ((n.byte(0x845)) != '\0')
      {
        n.FUN_00435560(3);
      }
    }
    else
    {
      uVar3 = n.slot7_ftol(0x7c8, 0x3fb33333u);
      n.w[0x1f2] = uVar3;
      uVar3 = n.slot7_ftol(0x7cc, 0x3f000000u);
      n.w[0x1f3] = uVar3;
      uVar3 = n.slot7_ftol(0x7d0, 0x3f000000u);
      n.w[0x1f4] = uVar3;
    }
  }
  else
  {
    uVar3 = n.slot7_ftol(0x7c8, 0x3fc00000u);
    n.w[0x1f2] = uVar3;
    uVar3 = n.slot7_ftol(0x7cc, 0x3e800000u);
    n.w[0x1f3] = uVar3;
    uVar3 = n.slot7_ftol(0x7d0, 0x3e800000u);
    n.w[0x1f4] = uVar3;
    n.FUN_00435560(2);
    if ((n.w[0x20d]) < 1000)
    {
      n.w[0x20d] = slot7_word_add(n.w[0x20d], 1);
    }
  }
  if ((n.w[0x20c]) == 1)
  {
    if (((((n.byte(0x84)) != '\0') && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2ac]))) && (((n.frame_flags) & 0x100) != 0))
    {
      n.FUN_00421080(0x14);
      return;
    }
    if ((((n.byte(0x84)) == '\0') && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2ac])) && (((n.frame_flags) & 0x100) != 0)))
    {
      n.FUN_00421080(0x1e);
      return;
    }
  }
  if ((((n.w[0x20c]) == 4) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2c1])) && (((n.frame_flags) & 0x100) != 0)))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x17);
    }
  }
  else
    if (((((n.w[0x20c]) == 3) && (0 < (n.w[0x20d]))) && ((n.current_priority()) <= (n.w[0x2c8]))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x18);
    }
  }
  else
    if ((((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && ((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))) && ((n.w[0x2b7b]) != 0x140)) && (((n.byte(0x84)) != '\0') && (((n.frame_flags) & 0x100) != 0)))
  {
    n.FUN_00421080(0x1c);
  }
  else
    if (((((n.w[0x20c]) == 2) && (0 < (n.w[0x20d]))) && (((n.current_priority()) <= (n.w[0x2dd])) || (((uVar4 = n.FUN_0042c7b0(), ((uVar4 & 1) != 0) && (299 < (n.w[0x2b7b])))) && ((n.w[0x2b7b]) < 0x15e)))) && (((n.frame_flags) & 0x100) != 0))
  {
    if ((n.byte(0x84)) == '\0')
    {
      n.FUN_00421080(0x1e);
    }
    else
    {
      n.FUN_00421080(0x1b);
    }
  }
  else
  {
    if ((((n.w[0xa2]) != 0) && ((n.w[0xa1]) != 0)) && (((std::uint32_t(n.w[0xa2])) < 3) && ((std::uint32_t(n.w[0xa1])) < 3)))
    {
      if ((((n.byte(0x844)) == '\0') && ((n.byte(0x845)) == '\0')) && ((n.byte(0x846)) == '\0'))
      {
        if ((n.byte(0x318)) == '\0')
        {
          if (((((n.w[0x2b7b]) < 0x76) || ((0x81 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xb4))) || (((199 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0xda)) || ((0xe5 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x118)))) && (((n.w[0xc9]) <= (n.w[0x20e])) && ((n.byte(0x844)) == '\0')))
          {
            if (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b])))
            {
              n.w[0x3b] = 0;
            }
            else
            {
              n.w[0x3b] = 1;
            }
            if ((n.byte(0x84)) != '\0')
            {
              n.FUN_00421080(500);
              return;
            }
            n.FUN_00421080(0x1f5);
            return;
          }
        }
        else
          if (((n.byte(0x318)) == '\x01') && (((((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))) && ((n.byte(0x845)) == '\0')) && ((n.w[0xcb]) <= (n.w[0x20f]))))
        {
          n.FUN_004220e0();
          n.w[0xa4] = 0x14;
          n.w[0xa2] = 0x14;
          n.w[0xa1] = 0x14;
          piVar5 = n.FUN_00658a10(0);
          iVar1 = *piVar5;
          piVar5 = n.FUN_00658a10(0);
          if ((((n.partner_word(iVar1, 0x330)) - (n.partner_word(*piVar5, 0x83c))) < 0x78) && ((piVar5 = n.FUN_00658a10(0), (n.partner_byte(*piVar5, 0x845)) != '\0')))
          {
            n.FUN_00422240(0x23, 0x1e, 0);
            return;
          }
          n.FUN_00422240(0x24, 0x1e, 0);
          return;
        }
      }
      else
        if (((((n.current_priority()) <= (n.w[0xc3e])) && (((n.frame_flags) & 0x100) != 0)) && (((n.byte(0x845)) != '\0') || (((n.byte(0x844)) != '\0') || ((n.byte(0x846)) != '\0')))) && ((n.byte(0x84)) != '\0'))
      {
        n.FUN_00421080(0x172);
        return;
      }
    }
    if ((((n.w[0xa0]) == 0) || ((n.w[0xa1]) == 0)) || (((n.w[0x20d]) < 1) || ((((n.byte(0x84)) == '\0') || ((n.w[0xcca]) < (n.current_priority()))) || (((n.frame_flags) & 0x100) == 0))))
    {
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && ((n.w[0x1c8]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && ((n.w[0x1b7]) == 0))
      {
        n.FUN_00422560(n.w[0x2], 0x18, 10, 1);
        n.w[0x2bd3] = slot7_word_add(n.w[0x2bd3], 1);
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 2)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((n.current_priority()) <= (n.w[0xbf8])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
            n.FUN_00421080(0x168);
            return;
          }
        }
        else
          if (((n.current_priority()) <= (n.w[0xbb2])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
        {
          n.w[0x2bd4] = slot7_word_add(n.w[0x2bd4], 1);
          n.FUN_00421080(0x15e);
          return;
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0x1cc]) == 1)) && (0 < (n.w[0x1c8])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if ((((n.w[0x2b7b]) == 0x1e) && ((n.current_priority()) <= (n.w[0xeb4]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xeb4])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1cc);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xe6e]))) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xe6e])) && ((n.w[0x2b7b]) == 10)) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xe6e])) && (((n.w[0x2b7b]) < 100) || (299 < (n.w[0x2b7b]))))
          {
            n.w[0x2bd5] = slot7_word_add(n.w[0x2bd5], 1);
            n.FUN_00421080(0x1c2);
            return;
          }
        }
      }
      if (((0 < (n.w[0xae])) && ((n.w[0xae]) < 0x14)) && (0 < (n.w[0x1b7])))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xd48]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x198);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd1e])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x192);
            return;
          }
        }
        else
        {
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xd1e]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x17) && ((n.current_priority()) <= (n.w[0xd33]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x195);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x18) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x196);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x1b) && ((n.current_priority()) <= (n.w[0xd3a]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xd17])) && ((n.w[0x2b7b]) == 10)) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x191);
            return;
          }
          if (((n.current_priority()) <= (n.w[0xd10])) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(400);
            return;
          }
        }
      }
      if (((n.w[0xa1]) == 3) || ((0 < (n.w[0xad])) && ((n.w[0xad]) < 3)))
      {
        if ((n.byte(0x84)) == '\0')
        {
          if (((((n.w[0x2b7b]) == 0x1e) && ((n.w[0x2b7d]) < 2)) && ((n.current_priority()) <= (n.w[0xb34]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14c);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xae0])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x140))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x140);
            return;
          }
        }
        else
        {
          if (((((n.w[0x9e]) != 0) && ((n.w[0x2b7b]) == 0x14)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x14) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x9f]) < 0) && (((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18))) && ((n.current_priority()) <= (n.w[0xb26]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14a);
            return;
          }
          if (((((n.w[0x2b7b]) == 0x17) || ((n.w[0x2b7b]) == 0x18)) && ((n.current_priority()) <= (n.w[0xb2d]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x14b);
            return;
          }
          if (((n.w[0x9f]) < 0) && ((((n.current_priority()) <= (n.w[0xa9a])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x136))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e))))))
          {
            n.FUN_00421080(0x136);
            return;
          }
          if ((((n.w[0x9e]) != 0) && (((n.current_priority()) <= (n.w[0xaa1])) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((299 < (n.w[0x2b7b])) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 0x137)))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x137);
            return;
          }
          if ((((((n.w[0x2b7b]) == 0x149) || ((n.w[0x2b7b]) == 0x14d)) || ((n.w[0x2b7b]) == 0x2c)) && (((n.current_priority()) <= (n.w[0xb6c])) || ((((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (299 < (n.w[0x2b7b]))) && (((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300))) && ((((n.w[0x2b7b]) != 0x12d) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x154))) && ((n.w[0x2b7b]) != 0x155))))) && ((((n.frame_flags) & 0x100) != 0) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), sVar2 != 0))) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))
          {
            n.FUN_00421080(0x154);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x154) && ((n.current_priority()) <= (n.w[0xb73]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x155);
            return;
          }
          if ((((n.w[0x2b7b]) == 0x12d) && ((n.current_priority()) <= (n.w[0xa62]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12e);
            return;
          }
          if ((((n.w[0x2b7b]) == 300) && ((n.current_priority()) <= (n.w[0xa5b]))) && (((n.frame_flags) & 0x100) != 0))
          {
            n.FUN_00421080(0x12d);
            return;
          }
          if ((((n.current_priority()) <= (n.w[0xa54])) || (((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && (((299 < (n.w[0x2b7b])) && ((((n.w[0x2b7b]) < 0x15e) && ((n.w[0x2b7b]) != 300)) && ((n.w[0x2b7b]) != 0x12d))) && (((n.w[0x2b7b]) != 0x12e) && ((n.w[0x2b7b]) != 0x140)))) && (((n.w[0x2b7b]) != 0x154) && ((n.w[0x2b7b]) != 0x155)))) && ((((n.frame_flags) & 0x100) != 0) || ((((n.byte(0x845)) != '\0') && ((n.w[0x212]) != 0)) && ((sVar2 = n.FUN_0042c7b0(), (sVar2 != 0) && ((299 < (n.w[0x2b7b])) && ((n.w[0x2b7b]) < 0x15e)))))))
          {
            n.FUN_00421080(300);
            return;
          }
        }
      }
      if ((((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((n.current_priority()) <= (n.w[0x2f2]))) && ((((n.frame_flags) & 0x100) != 0) && ((((n.w[0x9f]) != 0) || ((n.w[0x9e]) != 0)) && ((n.byte(0x84)) == '\0')))) && (0 < (n.w[0x20d])))
      {
        n.FUN_00421080(0x1e);
      }
      else
        if ((((n.w[0xa0]) == 3) || ((0 < (n.w[0xac])) && ((n.w[0xac]) < 3))) && ((((n.current_priority()) <= (n.w[0x338])) || ((n.current_priority()) == 99)) && (((((n.frame_flags) & 0x100) != 0) && ((n.byte(0x84)) != '\0')) && (0 < (n.w[0x20d])))))
      {
        n.FUN_00421080(0x28);
      }
    }
    else
    {
      n.FUN_00421080(0x186);
    }
  }
  return;
}

#if defined(DAYBREAK_NATIVE_BODY_IMPLEMENTATION)
void dispatch_slot7_body(Slot7BodyContext& n,unsigned ch,unsigned we)
#else
inline void dispatch_slot7_body(Slot7BodyContext& n,unsigned ch,unsigned we)
#endif
{
 switch(ch*3u+we){
 case 0:slot7_body_0_0(n);return;
 case 1:slot7_body_0_1(n);return;
 case 2:slot7_body_0_2(n);return;
 case 3:slot7_body_1_0(n);return;
 case 4:slot7_body_1_1(n);return;
 case 5:slot7_body_1_2(n);return;
 case 6:slot7_body_2_0(n);return;
 case 7:slot7_body_2_1(n);return;
 case 8:slot7_body_2_2(n);return;
 case 9:slot7_body_3_0(n);return;
 case 10:slot7_body_3_1(n);return;
 case 11:slot7_body_3_2(n);return;
 case 12:slot7_body_4_0(n);return;
 case 13:slot7_body_4_1(n);return;
 case 14:slot7_body_4_2(n);return;
 case 15:slot7_body_5_0(n);return;
 case 16:slot7_body_5_1(n);return;
 case 17:slot7_body_5_2(n);return;
 case 18:slot7_body_6_0(n);return;
 case 19:slot7_body_6_1(n);return;
 case 20:slot7_body_6_2(n);return;
 case 21:slot7_body_7_0(n);return;
 case 22:slot7_body_7_1(n);return;
 case 23:slot7_body_7_2(n);return;
 case 24:slot7_body_8_0(n);return;
 case 25:slot7_body_8_1(n);return;
 case 26:slot7_body_8_2(n);return;
 case 27:slot7_body_9_0(n);return;
 case 28:slot7_body_9_1(n);return;
 case 29:slot7_body_9_2(n);return;
 case 30:slot7_body_10_0(n);return;
 case 31:slot7_body_10_1(n);return;
 case 32:slot7_body_10_2(n);return;
 case 33:slot7_body_11_0(n);return;
 case 34:slot7_body_11_1(n);return;
 case 35:slot7_body_11_2(n);return;
 case 36:slot7_body_12_0(n);return;
 case 37:slot7_body_12_1(n);return;
 case 38:slot7_body_12_2(n);return;
 case 39:slot7_body_13_0(n);return;
 case 40:slot7_body_13_1(n);return;
 case 41:slot7_body_13_2(n);return;
 case 42:slot7_body_14_0(n);return;
 case 43:slot7_body_14_1(n);return;
 case 45:slot7_body_15_0(n);return;
 case 46:slot7_body_15_1(n);return;
 default:throw std::invalid_argument("No original slot7 binding");
 }}
