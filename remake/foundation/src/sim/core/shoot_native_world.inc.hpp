// NEW synchronous shooting bridge. Include inside DevelopmentAnimatedCombat
// only after the original-body comparison and NEW composition gate pass.
std::array<bool,4> shoot_native_visited{};
bool enable_native_shooting=true; // NEW source and whole-world gates passed.
std::array<ShootNativeEffects,4> shoot_native_effects{};
std::array<float,4> shoot_extra100{},shoot_extra10c{};
std::array<ShootNativeDat,4> shoot_native_dat{};
bool owns_native_shooting(unsigned slot,unsigned state)const{
 const auto& b=action_binding(slot);return shoot_native_body_binding(b.character,b.weapon,state);
}
void prepare_native_shooting_dat(unsigned slot){
 auto& catalog=shoot_native_dat.at(slot);if(!catalog.empty())return;const auto& data=actor_assets(slot);
 for(const auto& state:data.state_frames_){auto& phases=catalog[state.first];for(const auto& p:state.second){const auto id=p.value;phases.push_back({int(id),damage_signed(data.animation_durations_.at(id)),int(data.animation_settings_.at(id).hold_phase)});}}
}
void record_native_shooting_stat(const BattleWorld& world,unsigned slot,bool shooting){
 const auto& a=world.actors.at(slot);const auto target=a.relationships.secondary_target;
 const unsigned bucket=world.actors.at(target).relationships.secondary_target==slot?0u:1u;
 ++statistics[slot].attacks_issued[bucket];++statistics[target].attacks_received[bucket];
 const auto ally=a.relationships.allies.empty()?0u:a.relationships.allies[0];
 if(target==world.actors.at(ally).relationships.secondary_target)++statistics[slot].attacks_at_primary_target;
 if(shooting){++shots_attempted[slot];++statistics[slot].shooting_attacks;}else ++statistics[slot].attacks_total;
}
template<class Wall> void advance_native_shooting_body(BattleWorld& world,unsigned slot,const net::InputChannel::Frame& inputs,Wall& wall){
 prepare_native_shooting_dat(slot);const auto& binding=action_binding(slot);auto& actor=world.actors.at(slot);const auto state=current_action_state(slot),phase=projectile_owner_phase(slot);const auto& data=actor_assets(slot);
 ShootNativeInput in;in.character=binding.character;in.weapon=binding.weapon;in.state=state;in.phase=phase;in.frame=projectile_owner_animation_frame(slot);in.tick2=native_melee_second_tick[slot];in.dat=&shoot_native_dat[slot];
 // Bind0 can select animation0 even when no State phase references it.
 // Use the complete loaded animation table, as native421410 does.
 in.animation_metadata=[&](int id){return ShootNativePhase{id,damage_signed(data.animation_durations_.at(unsigned(id))),int(data.animation_settings_.at(unsigned(id)).hold_phase)};};
 const bool layered=uses_layered_walk_shot(slot);in.lower_state=layered?int(pose_bound_state_[slot][0]):int(state);in.lower_phase=layered?int(pose_bound_phase_[slot][0]):int(phase);in.lower_animation=pose_full_admission_pending_[slot]&&!layered?in.dat->at(state).at(phase).animation:int(animation_services_[slot].channels[0].selected);
 if(layered)in.tick2=walk_shot_[slot].lower_tick;
 in.x=actor_input_x(slot,inputs[slot]);in.z=actor_input_z(slot,inputs[slot]);in.jump=jump_held_[slot];in.held=melee_held_[slot];in.released=melee_released_[slot];in.shoot_held=shoot_held[slot];in.shoot_released=shoot_released[slot];in.stop=stop_ticks[slot];in.grounded=actor.grounded!=0;in.floor_height=actor.floor_distance;in.slow=damage_signed(status[slot].duration[6]);
 in.origin=actor.position;in.heading=actor.heading;in.contact=contact_ledger[slot].combined();in.ammunition_primary=damage_signed(magazines[slot][0].rounds);in.ammunition_secondary=damage_signed(magazines[slot][1].rounds);in.ally_index=targeting[slot].ally_index;in.voice_flag2=melee_voice_flags[slot][2];
 const auto target=actor.relationships.target;const auto& p=world.actors.at(target).position;in.distance_squared=battle_target_distance_squared(actor.position,p);in.height=p[1]-actor.position[1];const auto points=body_contact_points(world,target);for(unsigned axis=0;axis<3;++axis)in.target_spine[axis]=points[1][axis];in.target_spine_valid=true;
 const auto& special=special_gauges[slot];in.active0=special.active0;in.active1=special.active1;in.active2=special.active2;in.ready1=special.ready1;in.random=[&]{return random_.next();};
 ShootNativeMotion motion;static_cast<RemainingMeleeNativeMotion&>(motion)=native_remaining_melee_motion(world,slot);motion.extra68=native_extra68[slot];motion.last_hit_owner=status_aura_models[slot];motion.field_exit=damage_signed(projectile_owner_field_exit[slot]);motion.dash_count=damage_signed(statistics[slot].step_starts);motion.extra100=shoot_extra100[slot];motion.extra10c=shoot_extra10c[slot];auto scratch=native_melee_scratch(slot);
 std::optional<ActorSkeleton> muzzle;ShootNativeServices services;
 services.invoke=[&](const ShootNativeEvent& e,ShootBodyContext& n)->int{
  const auto& a=e.args;const auto f=[&](unsigned index){return remaining_real(unsigned(n.w.at(index)));};const auto realarg=[&](unsigned index){return remaining_real(unsigned(a.at(index)));};
  switch(e.kind){
   case 'D':return in.dat->at(unsigned(n.w[0xadf0/4])).at(unsigned(a.at(0))).animation;
   case 'I':{const unsigned layer=unsigned(a.at(0)),id=unsigned(a.at(1));animation_services_[slot].bind(layer,id);if(layer==0){pose_bound_state_[slot][0]=unsigned(n.w[0xadf0/4]);pose_bound_phase_[slot][0]=unsigned(n.w[0xadf8/4]);walk_shot_[slot].stopped=id==0;}return damage_signed(data.animation_durations_.at(id))<=1;}
   case 'F':{const auto st=unsigned(n.w[0xadec/4]),ph=unsigned(n.w[0xadf4/4]);cursors_[slot].advance(data.state_frames_.at(st).at(ph),n.w[0xae04/4]);return 0;}
   case 'N':admit_remaining_melee_state(slot,unsigned(a.at(0)));bind_actor_animation_state(slot,unsigned(a.at(0)));return 0;
   case 'Y':{const unsigned next=unsigned(a.at(0));reset_native_upper_state_metadata(slot);geometry[slot]={};if(next==0||next==10){elapsed[slot]=-1;air_state[slot]=0;walking[slot]=next==10;locomotion_phase[slot]=0;}else{attack_state[slot]=next;attack_phase[slot]=0;elapsed[slot]=0;}bind_actor_animation_state(slot,next,0,true);return 0;}
   case 'H':{const unsigned ph=unsigned(a.at(0)),upper=unsigned(n.w[0xadec/4]),lower=unsigned(n.w[0xadf0/4]);if(ph>=in.dat->at(upper).size()||ph>=in.dat->at(lower).size())return 0;cursors_[slot]={};animation_services_[slot].bind(0,unsigned(in.dat->at(lower).at(ph).animation));animation_services_[slot].bind(1,unsigned(in.dat->at(upper).at(ph).animation));pose_bound_state_[slot]={lower,upper};pose_bound_phase_[slot]={ph,ph};pose_full_admission_pending_[slot]=false;return 0;}
   case 'M':case 'L':case 'U':case 'K':{RosterWeaponTrailEffects effects;effects.count=1;auto& command=effects.commands[0];command.kind=e.kind=='M'?RosterTrailCommandKind::Model:e.kind=='L'?RosterTrailCommandKind::Off:e.kind=='U'?RosterTrailCommandKind::BothOn:RosterTrailCommandKind::SlotOn;if(e.kind=='M'){command.slot=a.at(0);command.model=a.at(1);}if(e.kind=='K')command.slot=a.at(0);
    // The renderer consumes this ordered stream with the prior bone pose.
    // Updating only the logic controller drops model history and trail flags.
    auto& visual=weapon_visual_commands[slot];if(visual.count>=visual.commands.size())throw std::length_error("Native shooting visual stream overflow");visual.commands[visual.count++]=command;visual.body_supported=true;
    apply_roster_weapon_trails(weapon_visual_controllers[slot],effects,[&](int model){return data.weapon_item&&unsigned(model)<data.weapon_item->attachments.size()&&!data.weapon_item->attachments[unsigned(model)].model.empty();},[](int,int){});roster_held_models[slot]=weapon_visual_controllers[slot].selected;roster_held_models_initialized[slot]=true;return 0;}
   case 'O':{const auto bone=cached_poses_[slot].find(e.name);if(!bone)throw std::runtime_error("Missing native shooting hand matrix");return e.name=="Bip01_R_Hand"?100:e.name=="Bip01_L_Hand"?101:throw std::runtime_error("Unknown shooting bone handle");}
   case 'B':case 'W':{GroundShotEffects shot;shot.fire=true;shot.count_attack=false;std::array<float,3> position=actor.position;float heading=actor.heading;unsigned aim=0;
    if(e.kind=='W'){shot.bullet_slot=unsigned(a.at(0));shot.origin=GroundShotOrigin::World;position={realarg(1),realarg(2),realarg(3)};heading=realarg(4);shot.pitch=realarg(5);}
    else if(e.address==0x435220){shot.bullet_slot=unsigned(a.at(1));if(a.at(0)!=100&&a.at(0)!=101)throw std::runtime_error("Invalid cached shooting bone handle");shot.origin=a.at(0)==100?GroundShotOrigin::RightHand:GroundShotOrigin::LeftHand;shot.yaw=realarg(2);shot.pitch=realarg(3);}
    else {const unsigned shift=e.address==0x435000?1u:0u;shot.origin=GroundShotOrigin::AttachmentZero;shot.attachment_slot=shift?unsigned(a.at(0)):0u;shot.bullet_slot=unsigned(a.at(shift));shot.yaw=realarg(shift+1);shot.pitch=realarg(shift+2);aim=unsigned(a.at(shift+3))&255u;}
    const auto model=shot.origin==GroundShotOrigin::AttachmentZero?std::optional<int>(weapon_visual_controllers[slot].selected.at(shot.attachment_slot)):std::nullopt;
    const bool accepted=append_actor_projectile_request(world,slot,shot,position,heading,f(0x64/4),muzzle,model);
    if(accepted&&aim){auto& request=shot_requests.back();const auto& t=world.actors.at(request.target).position;request.heading=float(std::atan2(double(t[2]-request.position[2]),double(t[0]-request.position[0]))/double(3.1415927410125732421875f)*180.)+shot.yaw;}
    n.w[0x6dc/4]=damage_signed(magazines[slot][0].rounds);n.w[0x720/4]=damage_signed(magazines[slot][1].rounds);return accepted;
   }
   case 'T':if(e.address==0x422950)return capture_actor(world,slot,std::int16_t(a.at(0)),std::uint8_t(a.at(1)),{},wall);else {BattleThrowRelease r;r.normal_state=std::int16_t(a.at(0));r.death_state=std::int16_t(a.at(1));r.damage=std::int16_t(a.at(2));r.scaling=std::uint8_t(a.at(3));r.rotation=realarg(4);r.horizontal=realarg(5);r.vertical=realarg(6);return release_held_actor(world,slot,r,wall);}
   case 'R':return contact_ledger[slot].combined();case 'C':contact_ledger[slot].clear_flags();contacted_[slot]={};return 0;case 'Q':contact_ledger[slot].set_capacity(unsigned(a.at(0)));return 0;
   case 'A':activate_presentation(slot);return 0;case 'S':record_native_shooting_stat(world,slot,false);return 0;case 'J':record_native_shooting_stat(world,slot,true);return 0;
   case 'E':queue_sound({slot,unsigned(a.at(0)),actor.position,native_battle_sound_mode(e.address)});return 0;
   case 'V':{const bool alternate=n.byte(0x844)||n.byte(0x845)||n.byte(0x846),specific=e.address==0x422490||e.address==0x422300;queue_voice({slot,unsigned(a.at(0)),unsigned(a.at(specific?2:1)),specific?a.at(1):-1,int(alternate),e.address,unsigned(a.at(specific?3:2))&255u});return 0;}
   case 'P':queue_effect({slot,unsigned(a.at(0)),{realarg(1),realarg(2),realarg(3)},realarg(4),realarg(5)});return 0;
   default:throw std::logic_error("Unbound native shooting world service");
  }
 };
 const auto effects=advance_shoot_native_control(scratch,motion,in,services);shoot_native_effects[slot]=effects;shoot_native_visited[slot]=true;store_native_melee_scratch(slot,scratch);store_native_remaining_melee_motion(world,slot,motion);
 jump_motion_[slot].gravity=motion.gravity;native_extra68[slot]=motion.extra68;status_aura_models[slot]=motion.last_hit_owner;projectile_owner_field_exit[slot]=unsigned(motion.field_exit);statistics[slot].step_starts=unsigned(motion.dash_count);shoot_extra100[slot]=motion.extra100;shoot_extra10c[slot]=motion.extra10c;
 if(unsigned(effects.state)>=400&&unsigned(effects.state)<=469){attack_state[slot]=unsigned(effects.state);attack_phase[slot]=unsigned(effects.phase);elapsed[slot]=effects.frame;}else if(effects.state==0||effects.state==10){locomotion_phase[slot]=unsigned(effects.phase);if(walking[slot])walk_tick[slot]=unsigned(effects.frame);else idle_tick[slot]=unsigned(effects.frame);locomotion_second_tick[slot]=unsigned(effects.tick2);}
 else if(air_state[slot]){air_phase[slot]=unsigned(effects.phase);air_tick[slot]=unsigned(effects.frame);}
 native_melee_second_tick[slot]=unsigned(effects.tick2);walk_shot_[slot].lower_tick=unsigned(effects.tick2);attack_return_[slot]=true;attack_effects[slot]={};
}
