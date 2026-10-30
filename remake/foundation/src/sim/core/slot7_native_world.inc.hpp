// NEW whole-slot7 runtime composition. Include in DevelopmentAnimatedCombat.
// Source/native proof is closed; production enabling requires the world gate.
bool enable_native_slot7=true; // Whole46 actual-DAT world gate passed.
std::array<bool,4> slot7_native_visited{};
std::array<std::vector<Slot7NativeEvent>,4> slot7_native_events{};
struct Slot7DatRecovery{unsigned current=0,requested=0;bool missing_priority=false;};
std::array<std::vector<Slot7DatRecovery>,4> slot7_dat_recoveries{};
std::array<unsigned,4> slot7_last_state{},slot7_last_lower{},slot7_last_phase{},slot7_last_primary{},slot7_last_secondary{};

template<class Wall>void advance_native_slot7_body(BattleWorld& world,unsigned slot,const net::InputChannel::Frame& inputs,unsigned jump_released,Wall& wall){
 const auto& binding=action_binding(slot);const auto& data=actor_assets(slot);auto& actor=world.actors.at(slot);
 auto& special=special_gauges[slot];const unsigned before=current_action_state(slot);
 if(binding.character==7&&binding.weapon==2&&!projectile_owner_aim_initialized[slot]){
  initialize_item41_owner_aim(projectile_owner_aim[slot],projectile_owner_aim_velocity[slot],actor.position);projectile_owner_aim_initialized[slot]=true;
 }
 Slot7NativeServices services;
 services.invoke=[&](const Slot7NativeEvent& e,Slot7BodyContext& n)->int{
  const auto& args=e.args;
  switch(e.kind){
   case 'N':case 'Y':{
    unsigned next=unsigned(args.at(0));const bool upper=e.kind=='Y';
    const auto found=data.state_frames_.find(next);
    if(found==data.state_frames_.end()||found->second.empty()||found->second[0].frames.empty()){
     // Original lookup would dereference absent phase/frame metadata. Retain
     // the request and recover explicitly, rather than invent a new action.
     slot7_dat_recoveries[slot].push_back({unsigned(n.w[0xadec/4]),next,false});next=actor.grounded?0u:43u;
    }
    const unsigned prior_lower=unsigned(n.w[0xadf0/4]),prior_secondary=unsigned(n.w[0xae08/4]);
    if(upper&&next!=0&&next!=43){
     reset_native_upper_state_metadata(slot);geometry[slot]={};
     attack_state[slot]=next;attack_phase[slot]=0;elapsed[slot]=0;walking[slot]=false;
     walk_shot_[slot]={};walk_shot_[slot].lower_tick=prior_secondary;walk_shot_[slot].direction=native_melee_scratch(slot).e8;walk_shot_[slot].stopped=prior_lower==0;
     native_melee_second_tick[slot]=prior_secondary;rena_full_charge[slot].second_frame=prior_secondary;
     bind_actor_animation_state(slot,next,0,true);
     n.w[0xadf0/4]=int(prior_lower);n.w[0xae08/4]=int(prior_secondary);
    }else{
     special_entry[slot]={};death_state[slot]=death_phase[slot]=death_tick[slot]=0;
     admit_remaining_melee_state(slot,next);
     rena_full_charge[slot].second_frame=0;
     if(next>=500&&next<=503){
      special_entry[slot]={next,0,0,0,0,n.w[0xec/4]!=0};elapsed[slot]=-1;
     }
     // Gravity is one actor field, carried between different body adapters.
     jump_motion_[slot].gravity=air_melee_[slot].gravity=ground_shot_[slot].gravity;
     bind_actor_animation_state(slot,next);
     n.w[0xadf0/4]=int(next);n.w[0xadf8/4]=n.w[0xae08/4]=0;
     n.w[0x2c/4]=n.w[0x30/4]=n.w[0x34/4]=0;
    }
    n.w[0x684/4]=-1;n.w[0xadec/4]=int(next);n.w[0xadf4/4]=n.w[0xadfc/4]=n.w[0xae04/4]=0;
    n.frame_flags=actor_frame(slot).flags28;
    return 0;
   }
   case 'A':special.begin1();special_activation_events.push_back({slot,7,0});return 0;
   case 'V':{
    const bool alternate=n.byte(0x844)||n.byte(0x845)||n.byte(0x846);
    queue_voice({slot,unsigned(args.at(0)),unsigned(args.at(1)),-1,int(alternate),e.address,unsigned(args.at(2))&255u});
    if(!special_activation_events.empty()&&special_activation_events.back().slot==slot&&special_activation_events.back().voice==0)special_activation_events.back().voice=unsigned(args.at(0));
    return 0;
   }
   case 'v':{
    const unsigned receiver=unsigned(args.at(0));if(receiver>=4)throw std::out_of_range("Slot7 voice actor tag");
    queue_voice({slot,unsigned(args.at(1)),unsigned(args.at(2)),-1,int(n.byte(0x844)||n.byte(0x845)||n.byte(0x846)),e.address,unsigned(args.at(3))&255u,int(receiver)});return 0;
   }
   case 'T':{
    BattleThrowRelease release;release.normal_state=std::int16_t(args.at(0));release.death_state=std::int16_t(args.at(1));
    release.damage=std::int16_t(args.at(2));release.scaling=std::uint8_t(args.at(3));release.rotation=slot7_word_real(unsigned(args.at(4)));
    release.horizontal=slot7_word_real(unsigned(args.at(5)));release.vertical=slot7_word_real(unsigned(args.at(6)));
    const int result=release_held_actor(world,slot,release,wall);
    n.w[0xaed0/4]=target_availability[slot].paired_actor<4?int(target_availability[slot].paired_actor+1):0;return result;
   }
   case 'Z':set_native_manual_aim(slot,unsigned(n.w[0x2dc/4]),full_charge_manual_aim_[slot]);return 0;
   case 'R':n.contact=contact_ledger[slot].combined();return int(n.contact);
   case 'P':{
    if(actor.relationships.allies.empty())throw std::runtime_error("Slot7 actor-owned ally list missing");
    const unsigned ally=actor.relationships.allies.at(0);const auto& s=special_gauges.at(ally);
    n.partner[8/4]=int(ally);n.partner[0x330/4]=damage_signed(s.duration1);n.partner[0x83c/4]=damage_signed(s.charge1);
    n.partner[0x844/4]=int(s.active0)|(int(s.active1)<<8)|(int(s.active2)<<16);return 0;
   }
   default:throw std::logic_error("Unknown original slot7 world service");
  }
 };
 Slot7BodyContext n(services);
 // No initialized default for an absent original priority row has been
 // established. Do not treat zero as native evidence; poison absent rows so
 // an undefined DAT action cannot be made admissible by a guessed default.
 for(unsigned state=0;state<1000;++state){n.w[(0x880+state*0x1c)/4]=std::numeric_limits<int>::min();n.w[(0x884+state*0x1c)/4]=std::numeric_limits<int>::max();}
 for(const auto& row:data.state_priorities_){if(row.first>=1000)throw std::out_of_range("Slot7 original priority table limit");
  n.w[(0x880+row.first*0x1c)/4]=damage_signed(row.second[0]);n.w[(0x884+row.first*0x1c)/4]=damage_signed(row.second[1]);}
 if(!data.state_priorities_.count(before))slot7_dat_recoveries[slot].push_back({before,before,true});
 const auto word=[&](unsigned offset,unsigned value){n.w.at(offset/4)=damage_signed(value);};
 const auto real=[&](unsigned offset,float value){n.w.at(offset/4)=slot7_real_word(value);};
 word(8,slot);real(0x14,actor.position[0]);real(0x1c,actor.position[2]);word(0x84,actor.grounded);
 word(0x278,unsigned(actor_input_x(slot,inputs[slot])));word(0x27c,unsigned(actor_input_z(slot,inputs[slot])));word(0x280,jump_held_[slot]);word(0x284,melee_held_[slot]);word(0x288,shoot_held[slot]);word(0x290,special_button290[slot]);
 word(0x2b0,jump_released);word(0x2b4,melee_released_[slot]);word(0x2b8,shoot_released[slot]);word(0x2dc,full_charge_manual_flag_[slot]);
 word(0x318,special.mode);word(0x324,special.limit0);word(0x32c,special.limit1);word(0x330,special.duration1);
 word(0x7a4,health[slot]);word(0x7ac,stagger[slot].invincible);word(0x7c8,combat_modifiers[slot].attack);word(0x7cc,combat_modifiers[slot].received);word(0x7d0,combat_modifiers[slot].stagger);
 word(0x7f4,status[slot].duration[6]);word(0x7e0,status[slot].duration[1]);word(0x7e4,status[slot].duration[2]);word(0x828,time_stop_ticks[slot]);word(0x830,dash_command_cache_[slot]);word(0x834,unsigned(gauge[slot]));
 word(0x838,special.charge0);word(0x83c,special.charge1);word(0x844,unsigned(special.active0)|(unsigned(special.active1)<<8)|(unsigned(special.active2)<<16));word(0x848,special.ready1);
 word(0xadec,before);word(0xadf4,projectile_owner_phase(slot));word(0xae04,projectile_owner_animation_frame(slot));word(0xae08,actor_secondary_animation_frame(slot));
 word(0xadf0,pose_bound_state_[slot][0]);word(0xadf8,pose_bound_phase_[slot][0]);word(0x684,unsigned(native_contact_mode[slot]));
 const auto scratch=native_melee_scratch(slot);word(0xe8,unsigned(scratch.e8));word(0xec,unsigned(scratch.ec));word(0xf0,unsigned(scratch.f0));word(0xf4,unsigned(scratch.f4));word(0xf8,unsigned(scratch.f8));
 // 6A0 is the weapon manager; its magazines begin at6C4 and708.
 std::memcpy(n.w.data()+0x6c4/4,&magazines[slot][0],sizeof(BattleMagazine));std::memcpy(n.w.data()+0x708/4,&magazines[slot][1],sizeof(BattleMagazine));
 word(0xaf4c,statistics[slot].empty_shots);word(0xaf50,statistics[slot].full_charge_shots);word(0xaf54,statistics[slot].charge_shots);
 word(0xaf60,field_contact_rank[slot]);word(0xaf64,field_contact_rank_timer[slot]);word(0xaf68,satoko_mine_clock[slot]);
 float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);real(0x64,offset);
 if(binding.character==7&&binding.weapon==2){real(0xaf60,projectile_owner_aim[slot][0]);real(0xaf68,projectile_owner_aim[slot][2]);real(0xaf6c,projectile_owner_aim_velocity[slot][0]);real(0xaf70,projectile_owner_aim_velocity[slot][1]);}
 for(unsigned i=0;i<4;++i)n.global_6cfb28[i]=action_binding(i).character;
 n.contact=contact_ledger[slot].combined();n.frame_flags=actor_frame(slot).flags28;
 dispatch_slot7_body(n,binding.character,binding.weapon);
 // Source stores after callbacks win, including mode1 input counters and
 // Ohishi timer/reset. State/pose callbacks have already completed in order.
 health[slot]=unsigned(n.w[0x7a4/4]);stagger[slot].invincible=unsigned(n.w[0x7ac/4]);gauge[slot]=n.w[0x834/4];
 actor.relationships.heading_offset_bits=unsigned(n.w[0x64/4]);
 special.charge0=unsigned(n.w[0x838/4]);special.charge1=unsigned(n.w[0x83c/4]);special.ready1=unsigned(n.w[0x848/4]);
 special.active0=n.byte(0x844)!=0;special.active1=n.byte(0x845)!=0;special.active2=n.byte(0x846)!=0;
 jump_held_[slot]=unsigned(n.w[0x280/4]);melee_held_[slot]=unsigned(n.w[0x284/4]);shoot_held[slot]=unsigned(n.w[0x288/4]);special_button290[slot]=unsigned(n.w[0x290/4]);
 combat_modifiers[slot]={unsigned(n.w[0x7c8/4]),unsigned(n.w[0x7cc/4]),unsigned(n.w[0x7d0/4])};
 std::memcpy(&magazines[slot][0],n.w.data()+0x6c4/4,sizeof(BattleMagazine));std::memcpy(&magazines[slot][1],n.w.data()+0x708/4,sizeof(BattleMagazine));
 if(shoot_released[slot])shoot_release_charge[slot]=magazines[slot][1].word28;
 statistics[slot].empty_shots=unsigned(n.w[0xaf4c/4]);statistics[slot].full_charge_shots=unsigned(n.w[0xaf50/4]);statistics[slot].charge_shots=unsigned(n.w[0xaf54/4]);
 auto next_scratch=native_melee_scratch(slot);next_scratch.ec=n.w[0xec/4];next_scratch.known|=2u;store_native_melee_scratch(slot,next_scratch);
 if(binding.character==7&&binding.weapon==2){projectile_owner_aim[slot][0]=n.real(0xaf60);projectile_owner_aim[slot][2]=n.real(0xaf68);projectile_owner_aim_velocity[slot]={n.real(0xaf6c),n.real(0xaf70)};}
 else{field_contact_rank[slot]=unsigned(n.w[0xaf60/4]);field_contact_rank_timer[slot]=unsigned(n.w[0xaf64/4]);satoko_mine_clock[slot]=unsigned(n.w[0xaf68/4]);}
 full_charge_manual_flag_[slot]=unsigned(n.w[0x2dc/4]);
 slot7_native_visited[slot]=true;slot7_native_events[slot]=std::move(n.events);
 slot7_last_state[slot]=unsigned(n.w[0xadec/4]);slot7_last_lower[slot]=unsigned(n.w[0xadf0/4]);slot7_last_phase[slot]=unsigned(n.w[0xadf4/4]);slot7_last_primary[slot]=unsigned(n.w[0xae04/4]);slot7_last_secondary[slot]=unsigned(n.w[0xae08/4]);
}
