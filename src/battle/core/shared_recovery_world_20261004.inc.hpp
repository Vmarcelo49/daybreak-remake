// Whole NEW source bodies own recovery/held clocks before pool scripts.
void advance_shared_recovery_handler(BattleWorld& world,unsigned i,const net::Input& input){
 auto& actor=world.actors[i];const auto& data=actor_assets(i);const auto& binding=action_binding(i);
 // All46 slot6 entry points return on+a0 before their prefix/default call.
 // The raw428510 oracle proves the body only after this caller gate.
 shared_recovery_visited[i]=true;
 if(stop_ticks[i])return; // +A0 hitstop, distinct from capture+AECC.
 const auto state=current_action_state(i);const bool recovering=recovery_state[i]!=0;
 unsigned& phase=recovering?recovery_phase[i]:reaction_phase[i];
 unsigned& frame=recovering?recovery_tick[i]:reaction_tick[i];
 const auto& phases=data.state_frames_.at(reaction_animation_state(i,state));const auto id=phases.at(phase).value;
 SharedRecoveryContext n(damage_signed(data.animation_durations_.at(id)),data.animation_settings_.at(id).hold_phase,
  phase+1==phases.size()&&frame+1>=data.animation_durations_.at(id));
 const auto real=[&](unsigned offset,float value){n.w.at(offset/4)=remaining_bits(value);};
 auto& m=actor.motion;float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
 for(const auto p:{std::pair<unsigned,float>{0x54,m.speed},{0x64,offset},{0x60,m.angles[1]},
  {0x40,m.velocity[1]},{0x58,common_hit_gravity_[i]},{0x874,walk_motion_[i].step},
  {0x2c,air_melee_[i].pitch},{0x30,native_extra_yaw[i]},{0x34,native_orientation34[i]},{0x5c,actor.heading}})real(p.first,p.second);
 for(unsigned axis=0;axis<3;++axis)real(0x14+axis*4,actor.position[axis]);
 auto scratch=native_melee_scratch(i);
 for(const auto p:{std::pair<unsigned,int>{0xe8,scratch.e8},{0xec,scratch.ec},{0xf0,scratch.f0},{0xf4,scratch.f4},{0xf8,scratch.f8},
  {0x684,native_contact_mode[i]},{0x7d4,status_aura_models[i]},{0x7d8,last_hit[i].last_owner},
  {0x834,gauge[i]},{0x7f4,damage_signed(status[i].duration[6])},{0x280,int(jump_held_[i])},
  {0x284,int(melee_held_[i])},{0x288,int(shoot_held[i])},{0x278,actor_input_x(i,input)},{0x27c,actor_input_z(i,input)},
  {0xadec,int(state)},{0xadf0,int(state)},{0xadf4,int(phase)},{0xadf8,int(phase)},
  {0xadfc,int(cursors_[i].index)},{0xae04,int(frame)},{0xae08,int(common_hit_second_tick_[i])},
  {0x84,int(actor.grounded)},{0xa0,damage_signed(stop_ticks[i])},{0xaf60,damage_signed(field_contact_rank[i])},
  {0xaf64,damage_signed(field_contact_rank_timer[i])},{0xaf68,damage_signed(satoko_mine_clock[i])}})n.w.at(p.first/4)=p.second;
 dispatch_shared_recovery_body(n,binding.character,binding.weapon,state);
 shared_recovery_visited[i]=true;shared_recovery_events[i]=n.events;
 const auto read=[&](unsigned at){return remaining_real(unsigned(n.w.at(at/4)));};
 m.speed=read(0x54);m.velocity[1]=read(0x40);m.angles[1]=read(0x60);
 offset=read(0x64);std::memcpy(&actor.relationships.heading_offset_bits,&offset,4);
 common_hit_gravity_[i]=ground_shot_[i].gravity=air_melee_[i].gravity=jump_motion_[i].gravity=read(0x58);
 walk_motion_[i].step=read(0x874);air_melee_[i].pitch=read(0x2c);native_extra_yaw[i]=read(0x30);native_orientation34[i]=read(0x34);
 native_contact_mode[i]=n.w[0x684/4];status_aura_models[i]=n.w[0x7d4/4];
 // +7d8 is a distinct damage owner and is never cleared by428510's aura write.
 gauge[i]=n.w[0x834/4];field_contact_rank[i]=n.w[0xaf60/4];field_contact_rank_timer[i]=n.w[0xaf64/4];satoko_mine_clock[i]=n.w[0xaf68/4];
 scratch.e8=n.w[0xe8/4];scratch.ec=n.w[0xec/4];scratch.f0=n.w[0xf0/4];scratch.f4=n.w[0xf4/4];scratch.f8=n.w[0xf8/4];
 scratch.known|=n.scratch_written;store_native_melee_scratch(i,scratch);recovery_move_ticks[i]=unsigned(scratch.e8);
 phase=unsigned(n.w[0xadf4/4]);frame=unsigned(n.w[0xae04/4]);common_hit_second_tick_[i]=unsigned(n.w[0xae08/4]);
 std::optional<ActorSkeleton> muzzle;bool state_reset=false;
 for(const auto& e:n.events){const auto& a=e.args;switch(e.kind){
  case 'N':set_common_hit_action(i,unsigned(a[0]),false);state_reset=true;attack_return_[i]=true;break;
  case 'H':
   if(!state_reset){
    if(unsigned(a[0])>=phases.size())throw std::out_of_range("Recovery phase outside original DAT");
    phase=unsigned(a[0]);frame=common_hit_second_tick_[i]=0;cursors_[i]={};bind_actor_animation_state(i,state,phase);
   }break;
  case 'I':cursors_[i].advance(phases.at(unsigned(a[1])),a[2]);break;
  case 'W':{
   GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=unsigned(a[0]);shot.origin=GroundShotOrigin::World;
   append_actor_projectile_request(world,i,shot,{remaining_real(unsigned(a[1])),remaining_real(unsigned(a[2])),remaining_real(unsigned(a[3]))},remaining_real(unsigned(a[4])),offset,muzzle);break;
  }
  case 'V':queue_voice({i,unsigned(a[0]),unsigned(a[2]),a[1],-1,e.address,unsigned(a[3])});break;
  case 'E':queue_sound({i,unsigned(a[0]),actor.position,native_battle_sound_mode(e.address)});break;
  case 'J':shots_attempted[i]+=unsigned(a[0]);record_shooting_attack(world,i,unsigned(a[0]));break;
  case 'M':case 'L':break; // prepare_roster_weapon_visuals already applied this prefix once.
  case 'T':case 'C':break;
  default:throw std::logic_error("Unknown shared recovery service");
 }}
}
