#pragma once
#include "legacy_snapshot_assets.hpp"
#include <memory>
namespace daybreak {
//Keep ordinary combat storage small and preserve its value-copy behavior.
//A copied native client owns independent tracks/FIFOs at its service boundary.
class LegacyClientAnimationStorage {
 using Actors=std::array<LegacySnapshotAnimationActor,4>;
 std::unique_ptr<Actors> actors_;
public:
 LegacyClientAnimationStorage()=default;
 LegacyClientAnimationStorage(const LegacyClientAnimationStorage& other){if(other.actors_)actors_=std::make_unique<Actors>(*other.actors_);}
 LegacyClientAnimationStorage& operator=(const LegacyClientAnimationStorage& other){if(this!=&other){auto next=other.actors_?std::make_unique<Actors>(*other.actors_):nullptr;actors_=std::move(next);}return *this;}
 LegacyClientAnimationStorage(LegacyClientAnimationStorage&&)=default;
 LegacyClientAnimationStorage& operator=(LegacyClientAnimationStorage&&)=default;
 LegacyClientAnimationStorage& operator=(std::unique_ptr<Actors> actors){actors_=std::move(actors);return *this;}
 explicit operator bool()const{return bool(actors_);}
 Actors* operator->(){return actors_.get();}
 const Actors* operator->()const{return actors_.get();}
 Actors& operator*(){return *actors_;}
 const Actors& operator*()const{return *actors_;}
};
}
