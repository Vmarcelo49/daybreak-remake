#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
// Native model argument multisets: 46/46, 625 calls. Retained request-order
// comparison: 224745 actual-DAT visits, 37 bindings (see analysis audit).
// Prefix covers all 46 bindings. Body covers current DAT-backed states350..499
// for characters3..15; completed character0..2 body handlers retain ownership.
// Commands are raw 434a70 requests, not loaded-model results. Consumer must
// apply native loaded-byte admission (missing/empty asset -> selected=-1).
// Use the original incoming phase/frame/scratch snapshot, before actor clock.
// body_is_current_DAT is supplied by actual loaded actor state/phase metadata.
struct RosterWeaponVisualInput {
 std::int32_t state=0,phase=0,frame=0,rank=0,scratch_ec=0,scratch_f4=0,scratch_f8=0;
 float vertical=0; bool blocked=false,complete=false,grounded=true;
 bool active0=false,active1=false,active2=false,body_is_current_DAT=true;
};
struct RosterWeaponModelCommand {int slot=0,model=0;};
struct RosterWeaponVisualEffects {std::array<RosterWeaponModelCommand,24> commands{};unsigned count=0;bool body_supported=false;};
inline RosterWeaponVisualEffects roster_weapon_visual_policy(unsigned character,unsigned weapon,const RosterWeaponVisualInput& s){
 RosterWeaponVisualEffects out;if(s.blocked)return out;
 auto model=[&](int slot,int index){out.commands[out.count++]={slot,index};};
 if(character==14&&weapon==1&&(s.active0||s.active1||s.active2)){model(0,2);}
 else {model(0,0);model(1,1);}
 if(character==8&&weapon==2&&1<=s.rank&&s.rank<=9)model(0,s.rank+1);
 if(character<3||!s.body_is_current_DAT||s.state<350||500<=s.state)return out;
 out.body_supported=true;
 // 0057f600 full350/360 reset EC before the model guard at phase0/frame0.
 const int scratch_ec=(character==10&&weapon==1&&(s.state==350||s.state==360)&&s.phase==0&&s.frame==0)?0:s.scratch_ec;
 switch(character*3+weapon){
 case 9: // character3, weapon0
  if((s.state==402)&&((0xf < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004a9c40.c:1927
  if((s.state==402)&&((0xf < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004a9c40.c:1928
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004a9c40.c:2025
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004a9c40.c:2026
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004a9c40.c:2104
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004a9c40.c:2105
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004a9c40.c:2183
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004a9c40.c:2184
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004a9c40.c:2262
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004a9c40.c:2263
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004a9c40.c:2347
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004a9c40.c:2348
  break;
 case 10: // character3, weapon1
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004b4090.c:1878
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004b4090.c:1879
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004b4090.c:2093
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004b4090.c:2094
  break;
 case 11: // character3, weapon2
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004bc040.c:2582
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004bc040.c:2583
  break;
 case 12: // character4, weapon0
  if((s.state==371)&&((!(s.blocked != 0))))model(0,-1); // 00484be0.c:1393
  if((s.state==371)&&((!(s.blocked != 0))))model(1,-1); // 00484be0.c:1394
  break;
 case 13: // character4, weapon1
  if((s.state==360)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 00492f70.c:58
  if((s.state==360)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,3); // 00492f70.c:59
  if((s.state==350)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 00492f70.c:1336
  if((s.state==350)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,3); // 00492f70.c:1337
  if((s.state==371)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(0,-1); // 00492f70.c:1443
  if((s.state==371)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(1,-1); // 00492f70.c:1444
  if((s.state==400)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:1701
  if((s.state==400)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:1702
  if((s.state==401)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:1775
  if((s.state==401)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:1776
  if((s.state==402)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,4); // 00492f70.c:1914
  if((s.state==402)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,5); // 00492f70.c:1915
  if((s.state==404)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2011
  if((s.state==404)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2012
  if((s.state==405)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2089
  if((s.state==405)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2090
  if((s.state==406)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2177
  if((s.state==406)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2178
  if((s.state==407)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2256
  if((s.state==407)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2257
  if((s.state==410)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2434
  if((s.state==410)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2435
  if((s.state==411)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2522
  if((s.state==411)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2523
  if((s.state==412)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2610
  if((s.state==412)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2611
  if((s.state==450)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,4); // 00492f70.c:2702
  if((s.state==450)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,5); // 00492f70.c:2703
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,4); // 00492f70.c:2928
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,5); // 00492f70.c:2929
  break;
 case 15: // character5, weapon0
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004f92a0.c:2085
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004f92a0.c:2086
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004f92a0.c:2507
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004f92a0.c:2508
  break;
 case 16: // character5, weapon1
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00503510.c:1950
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 00503510.c:1951
  break;
 case 17: // character5, weapon2
  if((s.state==360)&&((!(s.blocked != 0))))model(0,2); // 0050aea0.c:48
  if((s.state==350)&&((!(s.blocked != 0))))model(0,2); // 0050aea0.c:1663
  if((s.state==400)&&((((s.phase == 0) && (0xe < s.frame)) || (0 < s.phase)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0050aea0.c:2164
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 0050aea0.c:2233
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 0050aea0.c:2234
  if((s.state==402)&&((((s.phase == 0) && (0xe < s.frame)) || (0 < s.phase)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(((s.grounded != 0) && (0 < s.frame)) && (s.phase == 2)))))model(0,2); // 0050aea0.c:2284
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 0050aea0.c:2676
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 0050aea0.c:2677
  if((s.state==450)&&((!(s.blocked != 0))))model(0,2); // 0050aea0.c:3333
  if((s.state==451)&&((!(s.blocked != 0))))model(0,2); // 0050aea0.c:3403
  if((s.state==460)&&((!(s.blocked != 0))))model(0,2); // 0050aea0.c:3472
  if((s.state==461)&&((!(s.blocked != 0))))model(0,2); // 0050aea0.c:3543
  break;
 case 19: // character6, weapon1
  if((s.state==350)&&((s.frame < 0x31) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0051f880.c:1349
  if((s.state==350)&&((s.frame < 0x31) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 0051f880.c:1350
  if((s.state==350)&&((!(s.frame < 0x31)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,0); // 0051f880.c:1353
  if((s.state==350)&&((!(s.frame < 0x31)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,1); // 0051f880.c:1354
  if((s.state==360)&&((s.frame < 0x31) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(0,2); // 0051f880.c:1420
  if((s.state==360)&&((s.frame < 0x31) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(1,-1); // 0051f880.c:1421
  if((s.state==360)&&((!(s.frame < 0x31)) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 0051f880.c:1424
  if((s.state==360)&&((!(s.frame < 0x31)) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 0051f880.c:1425
  if((s.state==450)&&((s.frame < 0x1b) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0051f880.c:2299
  if((s.state==450)&&((s.frame < 0x1b) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 0051f880.c:2300
  if((s.state==450)&&((!(s.frame < 0x1b)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,0); // 0051f880.c:2303
  if((s.state==450)&&((!(s.frame < 0x1b)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,1); // 0051f880.c:2304
  if((s.state==460)&&((s.frame < 0x1b) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 0051f880.c:2372
  if((s.state==460)&&((s.frame < 0x1b) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 0051f880.c:2373
  if((s.state==460)&&((!(s.frame < 0x1b)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,0); // 0051f880.c:2376
  if((s.state==460)&&((!(s.frame < 0x1b)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,1); // 0051f880.c:2377
  break;
 case 20: // character6, weapon2
  if((s.state==450)&&((!(s.blocked != 0))))model(0,2); // 00527880.c:3014
  if((s.state==460)&&((!(s.blocked != 0))))model(0,2); // 00527880.c:3088
  break;
 case 21: // character7, weapon0
  if((s.state==360)&&(((9 < s.frame) && (s.frame < 0x1e)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(((s.grounded != 0) && (s.vertical < 0.0f)) && (0x1e < s.frame)))))model(1,-1); // 00531ce0.c:65
  if((s.state==360)&&(((9 < s.frame) && (s.frame < 0x1e)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(((s.grounded != 0) && (s.vertical < 0.0f)) && (0x1e < s.frame)))))model(0,2); // 00531ce0.c:66
  if((s.state==350)&&(((9 < s.frame) && (s.frame < 0x1e)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 00531ce0.c:1423
  if((s.state==350)&&(((9 < s.frame) && (s.frame < 0x1e)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 00531ce0.c:1424
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 00531ce0.c:1482
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 00531ce0.c:1483
  if((s.state==450)&&(((9 < s.frame) && (s.frame < 0x12)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00531ce0.c:2877
  if((s.state==450)&&(((9 < s.frame) && (s.frame < 0x12)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00531ce0.c:2878
  if((s.state==451)&&(((9 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00531ce0.c:2938
  if((s.state==451)&&(((9 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00531ce0.c:2939
  if((s.state==452)&&(((9 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00531ce0.c:2993
  if((s.state==452)&&(((9 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00531ce0.c:2994
  if((s.state==453)&&(((9 < s.frame) && (s.frame < 0x14)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00531ce0.c:3051
  if((s.state==453)&&(((9 < s.frame) && (s.frame < 0x14)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00531ce0.c:3052
  if((s.state==454)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00531ce0.c:3108
  if((s.state==454)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00531ce0.c:3109
  if((s.state==460)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,2); // 00531ce0.c:3156
  if((s.state==460)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,-1); // 00531ce0.c:3157
  break;
 case 22: // character7, weapon1
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 0053bc00.c:1422
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 0053bc00.c:1423
  if((s.state==450)&&(((-1 < s.frame) && (s.frame < 0x12)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 0053bc00.c:2934
  if((s.state==450)&&(((-1 < s.frame) && (s.frame < 0x12)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 0053bc00.c:2935
  if((s.state==451)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 0053bc00.c:3016
  if((s.state==451)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 0053bc00.c:3017
  if((s.state==452)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 0053bc00.c:3089
  if((s.state==452)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 0053bc00.c:3090
  if((s.state==453)&&(((-1 < s.frame) && (s.frame < 0x14)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 0053bc00.c:3157
  if((s.state==453)&&(((-1 < s.frame) && (s.frame < 0x14)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 0053bc00.c:3158
  if((s.state==454)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 0053bc00.c:3228
  if((s.state==454)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 0053bc00.c:3229
  if((s.state==460)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,2); // 0053bc00.c:3297
  if((s.state==460)&&(((-1 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,-1); // 0053bc00.c:3298
  break;
 case 23: // character7, weapon2
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 00545f00.c:1465
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 00545f00.c:1466
  if((s.state==451)&&(((-1 < s.frame) && (s.frame < 0x50)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 00545f00.c:2981
  if((s.state==451)&&(((-1 < s.frame) && (s.frame < 0x50)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 00545f00.c:2982
  if((s.state==452)&&(((9 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00545f00.c:3112
  if((s.state==452)&&(((9 < s.frame) && (s.frame < 0x11)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00545f00.c:3113
  if((s.state==453)&&(((9 < s.frame) && (s.frame < 0x14)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00545f00.c:3186
  if((s.state==453)&&(((9 < s.frame) && (s.frame < 0x14)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00545f00.c:3187
  if((s.state==454)&&((9 < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,2); // 00545f00.c:3259
  if((s.state==454)&&((9 < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 00545f00.c:3260
  if((s.state==454)&&((s.frame == 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,3); // 00545f00.c:3274
  if((s.state==454)&&((s.frame == 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 00545f00.c:3275
  break;
 case 24: // character8, weapon0
  if((s.state==400)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 004c57f0.c:1592
  if((s.state==400)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004c57f0.c:1593
  if((s.state==401)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 004c57f0.c:1641
  if((s.state==401)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004c57f0.c:1642
  if((s.state==402)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,2); // 004c57f0.c:1687
  if((s.state==402)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004c57f0.c:1688
  if((s.state==404)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 004c57f0.c:1761
  if((s.state==404)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004c57f0.c:1762
  if((s.state==405)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 004c57f0.c:1817
  if((s.state==405)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004c57f0.c:1818
  if((s.state==406)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 004c57f0.c:1867
  if((s.state==406)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004c57f0.c:1868
  if((s.state==407)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 004c57f0.c:1917
  if((s.state==407)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004c57f0.c:1918
  if((s.state==408)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,2); // 004c57f0.c:1973
  if((s.state==408)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004c57f0.c:1974
  break;
 case 26: // character8, weapon2
  if((s.state==451)&&((s.rank != 0) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(0,11); // 004d5980.c:2321
  if((s.state==454)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,9); // 004d5980.c:2436
  if((s.state==455)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,10); // 004d5980.c:2501
  if((s.state==464)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded != 0))))model(0,9); // 004d5980.c:2714
  if((s.state==465)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded != 0))))model(0,10); // 004d5980.c:2787
  break;
 case 27: // character9, weapon0
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004dee70.c:2153
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004dee70.c:2154
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004dee70.c:2214
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004dee70.c:2215
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004dee70.c:2270
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004dee70.c:2271
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004dee70.c:2326
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004dee70.c:2327
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004dee70.c:2378
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004dee70.c:2379
  break;
 case 28: // character9, weapon1
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004e7680.c:2036
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004e7680.c:2037
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004e7680.c:2092
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004e7680.c:2093
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004e7680.c:2148
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004e7680.c:2149
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004e7680.c:2204
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004e7680.c:2205
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004e7680.c:2256
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004e7680.c:2257
  break;
 case 29: // character9, weapon2
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004f0040.c:2074
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004f0040.c:2075
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004f0040.c:2130
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004f0040.c:2131
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004f0040.c:2186
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004f0040.c:2187
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 004f0040.c:2242
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 004f0040.c:2243
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 004f0040.c:2294
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 004f0040.c:2295
  break;
 case 30: // character10, weapon0
  if((s.state==350)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 00571ca0.c:56
  if((s.state==350)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,3); // 00571ca0.c:57
  if((s.state==360)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(0,2); // 00571ca0.c:1433
  if((s.state==360)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(1,3); // 00571ca0.c:1434
  if((s.state==450)&&((s.frame < 0x16) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 00571ca0.c:3832
  if((s.state==450)&&((s.frame < 0x16) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 00571ca0.c:3833
  if((s.state==451)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 00571ca0.c:3894
  if((s.state==451)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 00571ca0.c:3895
  if((s.state==460)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 00571ca0.c:3939
  if((s.state==460)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 00571ca0.c:3940
  break;
 case 31: // character10, weapon1
  if((s.state==350)&&((s.complete != 0) && (!(s.blocked != 0))))model(0,0); // 0057f600.c:38
  if((s.state==350)&&((s.complete != 0) && (!(s.blocked != 0))))model(1,1); // 0057f600.c:39
  if((s.state==350)&&((s.grounded == 0) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 0057f600.c:45
  if((s.state==350)&&((s.grounded == 0) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 0057f600.c:46
  if((s.state==350)&&((scratch_ec < 5) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0057f600.c:74
  if((s.state==350)&&((scratch_ec < 5) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,3); // 0057f600.c:75
  if((s.state==360)&&((scratch_ec < 5) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(0,2); // 0057f600.c:1361
  if((s.state==360)&&((scratch_ec < 5) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(1,3); // 0057f600.c:1362
  if((s.state==450)&&((s.frame < 0x16) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0057f600.c:3135
  if((s.state==450)&&((s.frame < 0x16) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 0057f600.c:3136
  if((s.state==451)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0057f600.c:3192
  if((s.state==451)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 0057f600.c:3193
  if((s.state==460)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 0057f600.c:3242
  if((s.state==460)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 0057f600.c:3243
  break;
 case 32: // character10, weapon2
  if((s.state==350)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0058a6a0.c:54
  if((s.state==350)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,3); // 0058a6a0.c:55
  if((s.state==360)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(0,2); // 0058a6a0.c:1353
  if((s.state==360)&&((s.frame < 0x1e) && (!(s.blocked != 0)) && (!(s.complete != 0))))model(1,3); // 0058a6a0.c:1354
  if((s.state==450)&&((s.frame < 0x16) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0058a6a0.c:3105
  if((s.state==450)&&((s.frame < 0x16) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 0058a6a0.c:3106
  if((s.state==451)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 0058a6a0.c:3159
  if((s.state==451)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 0058a6a0.c:3160
  if((s.state==460)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 0058a6a0.c:3204
  if((s.state==460)&&((s.frame < 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 0058a6a0.c:3205
  break;
 case 36: // character12, weapon0
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 005b0990.c:36
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 005b0990.c:37
  if((s.state==450)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b0990.c:2470
  if((s.state==450)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b0990.c:2471
  if((s.state==451)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b0990.c:2514
  if((s.state==451)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b0990.c:2515
  if((s.state==452)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b0990.c:2563
  if((s.state==452)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b0990.c:2564
  if((s.state==453)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b0990.c:2614
  if((s.state==453)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b0990.c:2615
  if((s.state==454)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b0990.c:2661
  if((s.state==454)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b0990.c:2662
  if((s.state==454)&&((s.frame == 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,3); // 005b0990.c:2669
  if((s.state==454)&&((s.frame == 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b0990.c:2670
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 005b0990.c:2707
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 005b0990.c:2708
  break;
 case 37: // character12, weapon1
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 005b9680.c:36
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 005b9680.c:37
  if((s.state==350)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,3); // 005b9680.c:1288
  if((s.state==350)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b9680.c:1289
  if((s.state==360)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,3); // 005b9680.c:1366
  if((s.state==360)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 005b9680.c:1367
  if((s.state==450)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b9680.c:2508
  if((s.state==450)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b9680.c:2509
  if((s.state==451)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b9680.c:2575
  if((s.state==451)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b9680.c:2576
  if((s.state==452)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b9680.c:2662
  if((s.state==452)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b9680.c:2663
  if((s.state==453)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b9680.c:2735
  if((s.state==453)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b9680.c:2736
  if((s.state==454)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005b9680.c:2808
  if((s.state==454)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b9680.c:2809
  if((s.state==454)&&((s.frame == 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,3); // 005b9680.c:2816
  if((s.state==454)&&((s.frame == 0x11) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005b9680.c:2817
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 005b9680.c:2873
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 005b9680.c:2874
  break;
 case 38: // character12, weapon2
  if((s.state==350)&&((!(s.blocked != 0))))model(0,2); // 005c3350.c:31
  if((s.state==360)&&((!(s.blocked != 0))))model(0,2); // 005c3350.c:1309
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(0,0); // 005c3350.c:1372
  if((s.state==361)&&((!(s.blocked != 0)) && (!(s.complete != 0))))model(1,1); // 005c3350.c:1373
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(0,2); // 005c3350.c:2446
  if((s.state==460)&&((!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (s.vertical < 0.0f)))))model(1,-1); // 005c3350.c:2447
  break;
 case 39: // character13, weapon0
  if((s.state==350)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:1487
  if((s.state==360)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:1549
  if((s.state==370)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:1643
  if((s.state==400)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:1939
  if((s.state==401)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2008
  if((s.state==402)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2064
  if((s.state==404)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2155
  if((s.state==405)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2215
  if((s.state==406)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2287
  if((s.state==407)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2362
  if((s.state==409)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2428
  if((s.state==450)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2450
  if((s.state==451)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2523
  if((s.state==452)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2596
  if((s.state==453)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2639
  if((s.state==454)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2682
  if((s.state==460)&&((!(s.blocked != 0))))model(0,2); // 00595460.c:2725
  break;
 case 40: // character13, weapon1
  if((s.state==350)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:1488
  if((s.state==360)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:1618
  if((s.state==370)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:1694
  if((s.state==400)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:1990
  if((s.state==402)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2058
  if((s.state==404)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2152
  if((s.state==405)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2203
  if((s.state==406)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2254
  if((s.state==407)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2308
  if((s.state==450)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2380
  if((s.state==451)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2468
  if((s.state==452)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2498
  if((s.state==460)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2601
  if((s.state==461)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2738
  if((s.state==462)&&((!(s.blocked != 0))))model(0,2); // 0059e630.c:2764
  break;
 case 41: // character13, weapon2
  if((s.state==350)&&((s.phase == 2) && (!(s.blocked != 0))))model(0,2); // 005a7ea0.c:1488
  if((s.state==360)&&((s.phase == 2) && (!(s.blocked != 0))))model(0,2); // 005a7ea0.c:1567
  if((s.state==370)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:1645
  if((s.state==400)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:1941
  if((s.state==402)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2020
  if((s.state==404)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2144
  if((s.state==405)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2204
  if((s.state==406)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2276
  if((s.state==407)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2351
  if((s.state==409)&&((!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2417
  if((s.state==450)&&((s.phase == 2) && (!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2439
  if((s.state==460)&&((s.phase == 2) && (!(s.blocked != 0))))model(0,2); // 005a7ea0.c:2515
  break;
 case 45: // character15, weapon0
  if((s.state==400)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2034
  if((s.state==400)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2035
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2119
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2120
  if((s.state==402)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 005e2af0.c:2200
  if((s.state==402)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 005e2af0.c:2201
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2305
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2306
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2391
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2392
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2477
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2478
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2563
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2564
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 005e2af0.c:2655
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 005e2af0.c:2656
  if((s.state==450)&&((s.scratch_f8 == 0) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005e2af0.c:2758
  if((s.state==450)&&((!(s.scratch_f8 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2761
  if((s.state==450)&&((!(s.scratch_f8 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2762
  if((s.state==451)&&((s.scratch_f8 == 0) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005e2af0.c:2843
  if((s.state==451)&&((!(s.scratch_f8 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2846
  if((s.state==451)&&((!(s.scratch_f8 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2847
  if((s.state==452)&&((s.scratch_f8 == 0) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,2); // 005e2af0.c:2901
  if((s.state==452)&&((!(s.scratch_f8 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005e2af0.c:2904
  if((s.state==452)&&((!(s.scratch_f8 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005e2af0.c:2905
  if((s.state==460)&&((s.scratch_f4 == 0) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.phase == 2) && (s.grounded != 0)))))model(0,2); // 005e2af0.c:3000
  if((s.state==460)&&((!(s.scratch_f4 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.phase == 2) && (s.grounded != 0)))))model(0,-1); // 005e2af0.c:3003
  if((s.state==460)&&((!(s.scratch_f4 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.phase == 2) && (s.grounded != 0)))))model(1,-1); // 005e2af0.c:3004
  if((s.state==461)&&((s.scratch_f4 == 0) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((0x1e < s.frame) && (s.grounded != 0)))))model(0,2); // 005e2af0.c:3089
  if((s.state==461)&&((!(s.scratch_f4 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((0x1e < s.frame) && (s.grounded != 0)))))model(0,-1); // 005e2af0.c:3092
  if((s.state==461)&&((!(s.scratch_f4 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((0x1e < s.frame) && (s.grounded != 0)))))model(1,-1); // 005e2af0.c:3093
  if((s.state==462)&&((s.scratch_f4 == 0) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((0x1e < s.frame) && (s.grounded != 0)))))model(0,2); // 005e2af0.c:3163
  if((s.state==462)&&((!(s.scratch_f4 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((0x1e < s.frame) && (s.grounded != 0)))))model(0,-1); // 005e2af0.c:3166
  if((s.state==462)&&((!(s.scratch_f4 == 0)) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((0x1e < s.frame) && (s.grounded != 0)))))model(1,-1); // 005e2af0.c:3167
  break;
 case 46: // character15, weapon1
  if((s.state==400)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005ed860.c:1921
  if((s.state==400)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005ed860.c:1922
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005ed860.c:1976
  if((s.state==401)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005ed860.c:1977
  if((s.state==402)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 005ed860.c:2027
  if((s.state==402)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 005ed860.c:2028
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005ed860.c:2102
  if((s.state==404)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005ed860.c:2103
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005ed860.c:2158
  if((s.state==405)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005ed860.c:2159
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005ed860.c:2214
  if((s.state==406)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005ed860.c:2215
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(0,-1); // 005ed860.c:2270
  if((s.state==407)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!(s.grounded == 0))))model(1,-1); // 005ed860.c:2271
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(0,-1); // 005ed860.c:2332
  if((s.state==408)&&((0xd < s.frame) && (!(s.blocked != 0)) && (!(s.complete != 0)) && (!((s.grounded != 0) && (0 < s.frame)))))model(1,-1); // 005ed860.c:2333
  break;
 default:break;
 }
 return out;
}
template<class Loaded> inline std::array<int,2> apply_roster_weapon_models(std::array<int,2> selected,const RosterWeaponVisualEffects& effects,Loaded loaded){
 for(unsigned i=0;i<effects.count;++i){const auto e=effects.commands[i];selected[e.slot]=(e.model>=0&&loaded(e.model))?e.model:-1;}return selected;
}
}
