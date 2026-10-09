# Nosso projeto vs. Ginkiha — estado do combate e animações

Branch `ginkiha-help` · 2026-10-09 · somente leitura do lado Ginkiha (nada executado)
Fontes Ginkiha (git-ignored, fora do remoto): `.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/`,
`.local-analysis/balance-reference/balance-reference-v0.10/`, consolidação em
`.local-analysis/RELATORIO-combate-daybreak.md`.
Fontes nossas: `remake/foundation/src/gameplay/`, `remake/docs/decisions.md`,
`remake/docs/game-spec.md`, `research/symbols/`, `research/progress/coverage.json`, `docs/status.md`.

## 1. Resumo executivo

- Nosso `remake/` tem **forma recuperada, valores majoritariamente port rules**: 6 seletores
  estado→move, `resolve_attack_move` 300/330/340, dash 20/27, jump 40/41/42, programa só para
  Rena 0 (`handler 0x43ffc0`), `startup=activeFrame / active=delta senão 8 / recovery 17 legacy`,
  `kProjectileBehavior` só arma 1, `shot_params()` compartilhado, guard 20%, respawn 3s (PORT RULE).
- Nosso `research/` tem **3169 entries, 48 reviewed/locked, ZERO de combate**: nenhum símbolo com
  damage/hit/throw/magazine/camera/anim/weapon/combo/guard/shot/melee/projectile/cpu/stagger/reload/charge;
  a janela hit/damage `0x637960–0x638f98` + `0x638A18` **não tem `.c` nem símbolo** (em `00637*` só
  existem `00637680`/`00637950`; em `00638*` só `00638fd0`); `types.json` vazio; `notes.json` sem combate.
- Ginkiha tem os dois lados que nos faltam: **lógica executável** (DaybreakRebuild: 46 combos, pipeline
  hit/dano com fórmulas e FUN_, 47 birth-profiles, walks 16×3, CPU 6 comandos, replay stage04 0 diffs) e
  **tabelas de balance** (balance-reference: 637 rows, 92 magazines todos mode 2/interval 0, thresholds
  850/900 com exceção Hanyuu 700/1800, timing Rena 12F→18F/50F→66F, 2924 combat sites, 7741 time sites).
- Ambos os lados Ginkiha já são **personagem+arma** (`parameters[3]==item_id` 46/46) — compatível com a
  regra 7 do `AGENTS.md`. O port deve trazer **tabelas + fórmulas**, nunca runtime Windows/D3D9/rede nem
  patches de EXE.

## 2. Nosso `remake/` hoje (o que existe de verdade)

### 2.1 Arquivos e responsabilidades
- `gameplay/fighter.h` (~900L) / `fighter.cpp` (1879L): `Fighter`, `FighterState` (17 labels),
  `state_to_move_id()` só recupera Idle=0, Walk=10, Hit=103, Knockdown=196, KO=203, BattleStart=194
  (resto → -1); `take_damage()`, `try_melee_hit()`, `resolve_attack_move()/resolve_swing()/dash_move_for()`,
  `advance_animation_phase()/enter_phase()`, `shot_params_for_*()`.
- `gameplay/character_moves.h/cpp`: parser `data/<char>/NN.dat` (`FUN_0041e180`), `MovePhase`,
  `CharacterMove` (priority row+0, cancelThreshold row+4), `weapon_id()` offset arquivo 0x114 (46/46 ok).
- `gameplay/move_behavior.h`: `kLocomotion[]` com números por combo (ex. Rena0
  `{0,0,0x43ffc0,7.2,17,0.75,1.20,4.0,1,15}`); `kNataRules[]` ~70 regras; `move_program()` retorna nata
  **só se `handler==0x43ffc0`**, senão nullptr — 1 combo com programa, 45 sem.
- `gameplay/weapon_definition.h/cpp` (329L): `parse(itemId)` (`FUN_00433eb0`), `MagazineDefinition`,
  `BulletDefinition`, `BulletParameter` (bloco 0x50 verbatim: `hitRadius`, `baseDamage`, `gaugeGainA/B`,
  `attackerHitstun`, `hitSound`, `impactEffect`, `modelName` 260B); `kWeaponIds[16][3]`, `comboSlotLabel()`.
- `gameplay/projectile.h/cpp`, `projectile_behavior.h` (49L): `ShotTier` (tiers do port), `shot_params(tier)`
  hardcoded (Tap 650u/s…, Red 460/16/80…), `ProjectilePool` 32+32, `kProjectileBehavior[9]` **só `weapon=1`**.
- `gameplay/melee_rules.h` / `combat_volume.h` / `combat_record.h`: `bodyRadius=30.0`, esfera/cápsula
  (`FUN_0063b470/4d0`), `MeleeWindow{5,8,17}` + legados, `MoveEntry` com `baseDamage=combat0`.
- `match.*`, `match_economy.*`, `rng.h` (splitmix64, não MT19937), `target_lock.h`, `bot_brain.*` (721L),
  `arena_camera.*` (preset original `{211,289,138,0,pi/4,50,150000}` vs remake), `fixed_step.h` (D9 64Hz),
  HUD (`ui/hud.h`, `game/hud_values.h`, `hud_bridge.h`), `xmodel.h` (`xm::Model`, `Controller`,
  `setAnimationBothTracks=FUN_00421100`), `fighter_pose.h`, `effect_catalog.h`, trails carregados mas nunca
  lidos (feature cortada).

### 2.2 O que já é data-driven vs. hardcoded
Data-driven (lê DAT/exe): inventário de moves + phase→set via `NN.dat`; `weapon_id()` 0x114 46/46;
trailer `+0x1c/+0x20`, período `.X`; melee geometria/dano parcial (`startup=activeFrame`,
`radius=hitRadius`, `damage=combat0`, `hitstun=combat10`); tiros parcial (damage/hitRadius/hitstun/effect/sound/model);
locomoção `kLocomotion`; jump chain 40→[2],41→[3,4],42→[5,43]; economia KO/overkill/timeout/respawn aéreo 1000.
Hardcoded (PORT RULE/provisório): `FighterConstants` (`kWalkSpeed=420`, `kMaxHP=100`, `kHitStunFrames=15`,
`kMeleeRange=160`, holds 0.45/1.10s, gravidade 1800, etc.); `hypermode_params()` (wiki);
`shot_params()` por tier; guard 20%; `kLegacyRadius/Window`; seleção 300/330/340 + 20/27 (inferência);
fallback set 0; muzzle por tier (sem `+0x318`); countdown 3s (original: 3 frames); spawn = próprio slot;
câmera retarget 0.45/10. Sem combo-scaling, sem facing-mask, sem swap, sem handlers `vtable+0x20`
(`ROADMAP-PENDING.md` "Next dig").

### 2.3 Animação: pipeline e limites
`bundle→decrypt→xm::loadMemory` → `Model{frames,meshes,anims Anim-1…124}` + `Controller` →
`state_move_id()` → `try_switch_animation()` → `tick_blend()/commit_blend()` →
`advance_animation_phase()` (gate `+0x20`) / `enter_phase()` → âncoras hurtbox/hitbox, aura (11 ossos),
arma em `Bip01_Prop1` sem offset (gap). Limites: 6/17 seletores + 3 inferências + jump + nata; resto set 0;
sem FA/HA/LA/StepA; sem cadeia 300→301→302 genérica (só micro-caso priority vs cancelThreshold);
sem overlay base/arms; sem offsets arma; sem `FUN_004218c0` budget.

### 2.4 Testes que pinam o pouco que há
`fighter_script_test`, `melee_rules_test` (80 checks), `weapon_definition_test` (709 checks, 46-combos smoke),
`animation_data_test/pose_test`, `match_economy/bot_brain/target_lock/arena_camera/live_camera`,
paridade congelada (33 casos/36 caps/47 logs, só cam-lines). Cobrem forma, não cobertura Ginkiha.

## 3. Nosso `research/` hoje (evidência)

- `symbols/functions.json`: 3169 entries — unreviewed 3106, locked 26, reviewed 22, suggested 15.
  Dos 48 reviewed/locked, **zero combate** (D3DX/Direct/entry/WinMain/input/file-IO/sprites/MT rand…).
  Nenhum `suggested_name` contém combate (grep confirma só ruído).
- VAs: `00421080` existe unreviewed (8 linhas, move binda 1ª phase); `0041e180` unreviewed (9KB, move-table
  reader); `00433eb0` unreviewed (160 linhas, única ocorrência de "magazine" nos dumps);
  `00649790` unreviewed (14KB, factory 649790). **Janela `00637960/00638f98/00638a18` ausente** em
  functions.json e sem `.c` — coração hit/damage fora do corpus.
- `types.json`: `entries` vazio. `notes.json`: ~13 chaves, zero combate.
- `coverage.json` (2026-10-07): 4092 binário, 3191 decompilados (77.98%), 48 reviewed (1.5%).
  `coverage_report.py` mede só contagem + top-20 in-degree — **não mede combate/região/DATs**.
- Pipeline: ingest → suggested+notes → reviewed→locked → generate_recomp (só reviewed/locked) → coverage.
  `recomp/` gerado (nunca editar); `symbols/` fonte de verdade; `decompiled/` dump read-only.
  Busca por palavra-chave no decompiled é inútil (damage/stagger/guard/projectile/melee/anim/hit/combo/weapon/shot/balloon: 0 hits; throw/lock/cpu/bullet: ruído).
- Docs afirmam via **citações cirúrgicas no remake sobre dumps unreviewed** (balloon, LIMIT, KO melee,
  overkill, respawn 1000.0f, target lock, yaw 45°, tactic cells, COM classes, split 1/2/4…), e marcam como
  pendente: inputs, FA/HA/LA/StepA, tap/yellow/red, tag/swap (voice keys, não estabelecido), 503 EX binding,
  side/air-dash selectors, guard sem move, cross-fades só Rena slot-2, respawn clock/point, red-capacity,
  aura VFX, EX por char, countdown (PORT RULE), câmera (auto-target-on-death, 2v2 awareness, shake…).
- Regra 7 **não expressa no research**: zero hits para comboSlotLabel/kWeaponIds/0x114 (os 0x114 crus são
  vtable/memcpy sem semântica). O datum vive só no remake (`ASSET-CATALOG.md` §3.2–3.3, `kWeaponIds`).

## 4. Lado Ginkiha (o que ele tem de correto)

### 4.1 DaybreakRebuild — lógica executável
46 combos (`character_dispatch.hpp`), transição canônica 0x421080/0x421100, 7 corpos nativos (~6MB),
assets imutáveis (`parameters[6]` = DAT 0x108–0x11f), loop CPU→movimento→projéteis→hit→dano→câmera/HUD.
Hit (raio 30, esfera×segmento, flags), guarda (±45°, states 390–392), dano
(`((base*mod/100)*atk/100)*def/100`, `/3` ≥10000, scaling 100/70/50/33), stagger (accum≥100),
survival modo2, status 8 slots + DoT, 3 gauges awakening, walks 16×3 (+exceção Hanyuu1),
dash-history 15f, air-dash 15.5, throws, CPU 6 comandos, 47 birth-profiles (27.5–80), câmera
(anchor .2/.3, FOV 45°). Proveniência: ~32024 menções `FUN_`, dezenas de intervalos. Validação: clean-build
247s + replay stage04 (3968 frames, 936448 obs, **0 diffs**), limites declarados
(`awake_airdash:false`, `attack_cancel:[]`, `coverage_gate_pass:false`, sem whole-game/pixel/rede).

### 4.2 balance-reference — tabelas + metodologia
46/46 perfis, `reference-data.json` (637 rows / 623 enabled / 591 present, 92 magazines, 2924 combat sites,
7741 time sites), `registrations[]` (r=factory_slot, q=file*10+variant, `positive_damage_values`, usage
normal/tag — ex. Rena reg0 `[1750]` `[[0,12]…[5,12]]`), magazines **todos mode 2 / interval 0**
(ex. Rena `{6,2,300,0,60,1}+{2,2,300,0,180,2}`), params `[850,900,0,item,850,900]` exceção Hanyuu
`[700,1800,0,32,700,1800]`, dano truncado inteiro, estatística 408/637 (50–10000, média ~1591),
`exe-catalog` (5210 records VA+offset+bytes), `combat-hooks` (2924 sites + shot400_usage: só 52 normal +
60 tag em state400), `timing-hooks` (7741 sites, 40/46 steering), `attack-preview` (552 shot400 + 591 births,
ex. 37.5), timing Rena **12F→18F / 50F→66F**, `W(t)` bilinear. Cobertura só state400 grounded; resto fora
(caps 20–21). Evidências v03→v10 `ok:true` retidas.

## 5. Comparativo por dimensão

| Dimensão | Nós (remake) | Nós (research) | Ginkiha | Gap |
|---|---|---|---|---|
| Roster/combos | `kWeaponIds` 46/46, `comboSlotLabel` ok | zero símbolos | 46 dispatch + vtable/update/slot7 | promover loaders + factory a reviewed |
| Moves/timing | 6 seletores + inferências; startup/active inventados | move reader unreviewed, sem DAT como dado | 637 rows, usage [phase,frame], 12F→18F | tabela startup/active/recovery/cancel por move |
| Dano/hit | forma (esfera 30+r) ok, valores port rules | janela fora do corpus | fórmulas + guard 45° + scaling + stagger | endereçar janela (re-extrair ou modelar como decisão citada) |
| Projéteis/mags | 9 linhas só arma 1; resto compartilhado | 1 format string | 92 mags + 47 births + thresholds | mags/births/thresholds como dado |
| Melee | `combat0/10` parcial; vtable+0x20 aberto | sem semântica | pipeline completo | `+0x20` é o "Next dig" |
| Locomoção | `kLocomotion` com números, programa só Rena0 | tactic cells só citação | walks 16×3 + 46 VAs | 45 programas restantes |
| CPU | cells+pesos+jitter | COM só citação | 6 comandos por arma | decisões por arma como dado |
| Câmera | preset medido + retarget port | fcn 6333b0/raio 20 citados | anchor/view/projeção completas | auto-target-on-death, 2v2 awareness, shake |
| Animação | sets genéricos + fallback set 0 | ANIMATION-SETS com fallbacks | 124 sets + controllers D3DX medidos | mapeamento state→set por combo, offsets arma, overlay |
| Validação | 33 casos/36 caps (cam-lines) | contagem, sem dimensão combate | stage04 59 campos 0 diffs | replicar replay como parity |

## 6. Veredito: o que portar (e o que não portar)

Portar: tabelas 46 + 92 mags + damage values + usage + walks + births + thresholds; fórmulas (dano truncado,
recovery modo-2, `W(t)`, esfera×segmento + filtro dano+raio); programas de move por combo (Speed/Turn/Approach/
Launch/Hold/Camera/Hide/Active + `shot{{…}}`); decisões CPU por arma; 6 seletores → cobertura por combo.
Não portar: D3D9/DirectSound/DirectInput/winmm, PS1/Zig/Win32, rede UDP própria, patches de EXE, `frame_count`
como duração, `registration` histórico como slot, fallbacks silenciosos onde handler desconhecido.
Detalhe executivo no plano companheiro: `docs/reports/ginkiha-port-plan.md`.

## 7. Binário canônico (resposta do Ginkiha, 2026-10-09)

Ginkiha confirmou uso livre ("full use of everything") e que o alvo é o **DaybreakDX.exe vanilla + patch
oficial v1.11**. Verificação no nosso repo:

| Binário (local, git-ignored) | Data PE | Bytes | SHA256 | Papel |
|---|---|---|---|---|
| `daybreak.exe` | 2006-08 | 2.469.888 | `6d1a5e11…` | jogo base; **nunca analisado** |
| `DaybreakDX.exe` | 2007-07 | 2.920.448 | `27e61475…a6a07f02` | **alvo canônico do port** |
| `daybreakdx_111s.exe` | 2014 | 3.052.112 | `49ead25d…` | instalador WinSFX32/LHA do patch (`.text` 15KB — não é código de jogo) |

- Nosso corpus é exatamente o binário do Ginkiha: `research/binary_data/metadata.txt` (4267 funções,
  base `0x400000`) e `pe_info.json` (2.920.448 bytes, 4 seções) = `DaybreakDX.exe` vanilla, cujo SHA
  (`27e61475…`) é o mesmo registrado no `balance-reference` (`original_exe_sha256`). **Todas as VAs dele
  valem para nosso binário** — follow-up de versão resolvido, zero divergência.
- O próprio `DaybreakDX.exe` imprime `ver1.11`: "vanilla v1.11" = este binário. O `111s.exe` é o
  auto-extrator do patch final (LHA, WinSFX32 2.16.8.12), não um segundo codebase — não há dual-version
  a conciliar.
- **Gap conhecido (a observação que motivou esta seção):** DX é extensão do `daybreak.exe` base
  (`.text` 2,75MB vs 2,28MB) e o roster DX tem 16 personagens (`kWeaponIds[16][3]`) — compartilham
  muita lógica, mas nosso corpus **nunca** analisou o base, então não há como afirmar daqui o que
  difere entre os dois. Correto para o remake (alvo = DX), porém regiões sem dump no nosso research
  serão encontradas ao portar; é o que a Fase 0 do plano endereça.
