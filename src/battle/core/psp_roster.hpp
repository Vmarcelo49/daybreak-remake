#pragma once
#include "character_names.hpp"
#include <array>
#include <string_view>
namespace daybreak {
// The three fighters that exist only in Higurashi Daybreak Portable (PSP, ULJM05557), added by
// issue #91 under plan decisions D-1/D-2 (docs/PSP-CHARACTERS-WORKLOG.md). They join the roster
// *after* the PC sixteen so that every table the 46 PC combos key on keeps its meaning:
// character_names stays 16 wide, sim::character_count() stays 16, and the [16][3] tunings and
// character*3+weapon switches never see these indices. Reaching them goes through this header.
inline constexpr unsigned psp_character_first=16;
inline constexpr unsigned psp_weapon_count=4;
inline constexpr std::array<std::string_view,3> psp_character_names{{"satoshi","miyoko","okonogi"}};
// Dispatch pairs (D-2): the PC combo whose recovered update body runs for a PSP fighter. Fixed
// from the moveset study (docs/PSP-CHARACTERS-PLAN.md: Satoshi near Keiichi, Miyoko near Satoko,
// Okonogi near Tomitake). Weapon slot 0 for all four PSP weapons: the .atp/.acs of one PSP
// fighter's four weapons differ in power and row population but not in kind, while the three PC
// slots of one character share one melee damage profile on the eleven measured moves
// (docs/psp/COMBAT.md §1 has the least-squares measurement and the byte-identical model evidence
// for Satoshi d = Keiichi's bat, PSP wpn17d == wpn02a).
inline constexpr std::array<unsigned,3> psp_dispatch_characters{{2,3,6}};
inline constexpr std::array<std::array<unsigned,4>,3> psp_dispatch_weapons{{
 {{0,0,0,0}},{{0,0,0,0}},{{0,0,0,0}}
}};
// data/item/NNN.dat ids of the converted PSP weapons: 101 = Satoshi a .. 112 = Okonogi d.
// Fixed by the issue so the product side (Track B) names the same files.
inline constexpr unsigned psp_item_first=101;
inline constexpr bool is_psp_character(unsigned character){return character>=psp_character_first&&character<psp_character_first+psp_character_names.size();}
inline constexpr unsigned psp_character_index(unsigned character){return character-psp_character_first;}
inline constexpr std::string_view psp_character_name(unsigned character){return psp_character_names.at(psp_character_index(character));}
inline constexpr unsigned psp_dispatch_character(unsigned character){return psp_dispatch_characters.at(psp_character_index(character));}
inline constexpr unsigned psp_dispatch_weapon(unsigned character,unsigned weapon){return psp_dispatch_weapons.at(psp_character_index(character)).at(weapon);}
inline constexpr unsigned psp_item_id(unsigned character,unsigned weapon){return psp_item_first+psp_character_index(character)*psp_weapon_count+weapon;}
// The same three answers for the whole roster, PC first. Callers that must work for both casts
// (the asset loader, sim's name and weapon-count queries) use these instead of character_names.
inline constexpr unsigned roster_character_count(){return psp_character_first+psp_character_names.size();}
inline constexpr bool roster_has_character(unsigned character){return character<roster_character_count();}
inline constexpr unsigned roster_weapon_count(unsigned character){return is_psp_character(character)?psp_weapon_count:(character<14?3u:2u);}
// The data/ directory name of a roster fighter: the PC table first, then the PSP three.
inline constexpr std::string_view roster_character_name(unsigned character){return is_psp_character(character)?psp_character_name(character):character_names.at(character);}
}
