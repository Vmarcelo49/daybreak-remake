#pragma once
#include <array>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
namespace daybreak {
// 645dc0/646cf0: eight cell indices followed by a per-cell second-sheet mask.
// Keep the encoded form available for original lobby/config names. UTF-8 is
// the modern lobby's representation, not an original name packet field.
struct BattlePlayerName {
 bool present=false,native_font=false;
 std::string text;
 std::array<std::uint8_t,9> encoded{};
};
inline std::vector<char32_t> battle_name_codepoints(std::string_view text){
 std::vector<char32_t> out;
 for(std::size_t at=0;at<text.size();){
  const unsigned first=static_cast<unsigned char>(text[at++]);unsigned code=0,extra=0,minimum=0;
  if(first<128)code=first;
  else if(first>=0xc2&&first<=0xdf){code=first&31;extra=1;minimum=128;}
  else if(first>=0xe0&&first<=0xef){code=first&15;extra=2;minimum=2048;}
  else if(first>=0xf0&&first<=0xf4){code=first&7;extra=3;minimum=65536;}
  else throw std::invalid_argument("Invalid player name UTF-8");
  if(extra>text.size()-at)throw std::invalid_argument("Truncated player name UTF-8");
  while(extra--){const unsigned next=static_cast<unsigned char>(text[at++]);if((next&0xc0)!=0x80)throw std::invalid_argument("Invalid player name continuation");code=(code<<6)|(next&63);}
  if(code<minimum||code>0x10ffff||(code>=0xd800&&code<=0xdfff)||code==0)throw std::invalid_argument("Invalid player name codepoint");
  out.push_back(char32_t(code));
 }
 return out;
}
inline void append_battle_name_utf8(std::string& text,char32_t code){
 if(code<128)text+=char(code);
 else if(code<2048){text+=char(0xc0|(code>>6));text+=char(0x80|(code&63));}
 else if(code<65536){text+=char(0xe0|(code>>12));text+=char(0x80|((code>>6)&63));text+=char(0x80|(code&63));}
 else {text+=char(0xf0|(code>>18));text+=char(0x80|((code>>12)&63));text+=char(0x80|((code>>6)&63));text+=char(0x80|(code&63));}
}
// Visually verified cells of the supplied name_p1s sheet. Unmapped Unicode
// uses a readable GDI fallback; it must never be guessed as a native index.
inline std::optional<std::pair<unsigned,bool>> battle_name_native_cell(char32_t code){
 static constexpr std::array<std::u32string_view,15> rows{{
  U" 0123456789@+-*/",U"ABCDEFGHIJKLM#!?",U"NOPQRSTUVWXYZ<>=",
  U"abcdefghijklm%&^",U"nopqrstuvwxyz()_",
  U"あかさたなはまやらわがざだばぱぁ",U"いきしちにひみゃりょぎじぢびぴぃ",
  U"うくすつぬふむゆるをぐずづぶぷぅ",U"えけせてねへめゅれっげぜでべぺぇ",
  U"おこそとのほもよろんごぞどぼぽぉ",U"アカサタナハマヤラワガザダバパァ",
  U"イキシチニヒミャリョギジヂビピィ",U"ウクスツヌフムユルヲグズヅブプゥ",
  U"エケセテネヘメュレッゲゼデベペェ",U"オコソトノホモヨロンゴゾドボポォ"}};
 for(unsigned row=0;row<rows.size();++row){const auto col=rows[row].find(code);if(col!=std::u32string_view::npos)return std::pair<unsigned,bool>{row*16+unsigned(col),false};}
 switch(code){case U'ヴ':return {{0xf0,false}};case U'ー':return {{0xf1,false}};case U'～':case U'~':return {{0xf2,false}};case U'、':return {{0xf3,false}};case U'。':return {{0xf4,false}};case U'￥':return {{0xf5,false}};case U'＄':case U'$':return {{0xf6,false}};
  case U'愛':return {{0,true}};case U'哀':return {{1,true}};case U'悪':return {{2,true}};case U'一':return {{3,true}};default:return {};}
}
inline BattlePlayerName make_battle_player_name(std::string_view text){
 BattlePlayerName out;auto points=battle_name_codepoints(text);out.present=!points.empty();out.native_font=out.present;
 for(unsigned i=0;i<points.size()&&i<8;++i){append_battle_name_utf8(out.text,points[i]);const auto cell=battle_name_native_cell(points[i]);
  if(!cell)out.native_font=false;else{out.encoded[i]=std::uint8_t(cell->first);if(cell->second)out.encoded[8]|=std::uint8_t(1u<<i);}}
 return out;
}
inline BattlePlayerName make_native_battle_player_name(const std::array<std::uint8_t,9>& encoded){BattlePlayerName out;out.present=out.native_font=true;out.encoded=encoded;return out;}
}
