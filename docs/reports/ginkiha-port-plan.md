# Plano de port — animações + combate data-driven (a partir do Ginkiha)

Branch `ginkiha-help` · 2026-10-09 · companheiro de `docs/reports/ginkiha-comparison.md`.
Objetivo do usuário: nosso combate/animação é rudimentar e pouco data-driven — portar o que Ginkiha fez
de correto. Regras duras vigentes (`AGENTS.md`): nunca editar `research/recomp/`; manter `.X` sem conversão
(SDL3+WebGPU D2); todo ataque é personagem+arma (`comboSlotLabel`); `coverage_report.py` antes de commit em
research; **full diff review antes de CADA commit**; comentários `why` + proveniência (`FUN_`/endereço).

## 0. Princípios do port

1. **Dados antes de código**: ingestar tabelas como dado revisável (research) e consumir no remake; sem
   colar 6MB de corpos gerados.
2. **Lógica pura, sem plataforma**: portar só headers sem `windows.h`/D3D/DirectSound/rede; nada de
   `runtime_*`/`windows_*`, rede UDP própria, ou patch de EXE.
3. **Sem fallback silencioso**: onde handler é desconhecido (steering 40/46, expiry 34/46, `+0x20` melee),
   rejeitar explicitamente como o planner deles faz.
4. **Cada número com proveniência**: citar VA/`FUN_` + SHA do EXE (`27e61475…`) ou DAT; campos desconhecidos
   (`fields[4,11,12]`, `flags28`, `parameters[2]`, effect IDs) preservados raw, nunca zerados.
5. **Paridade como gate**: replay stage04 (4 atores, 3968 frames, 59 campos) vira teste do remake; contagens
   via `ctest`, nunca via linha deste doc.

## 1. Fase 0 — fundação de evidência (research, pré-requisito)

- **0.1 Promover o que já existe**: `00421080` (move binda phase), `0041e180` (move-table reader, 9KB),
  `00433eb0` (weapon-item reader, 160 linhas), `00649790` (factory 649790, 14KB) de unreviewed → suggested →
  reviewed com notas (binding personagem+arma, `param[3]==item_id`, loaders 41E180/433EB0). Não forçar locked
  se `depends_on_unresolved` bloquear.
- **0.2 Endereçar a janela ausente**: `0x637960–0x638f98` + `0x638A18` não têm `.c` nem símbolo (buraco medido).
  Opções: (a) re-extrair a faixa do binário para `decompiled/` via pipeline; (b) enquanto isso, modelar as
  fórmulas Ginkiha como **decisões citadas** no remake (D-novos), não como símbolos confirmados.
- **0.3 Ingestar DATs como dado** (hoje zero): tabela 46 (ch/we→folder/item/vtable/swap 1..46), 92 magazines,
  thresholds `[850,900]` vs Hanyuu `[700,1800]`, `shot400_usage` (52 normal + 60 tag), `positive_damage_values`
  (408 rows, flag D vs N), walks 46 VAs. `types.json` hoje vazio — propor `FighterState/Hitbox/MoveTable/
  Magazine/Projectile` como hipóteses, sem travar errado.
- **0.4 Medir combate no coverage**: estender `coverage_report.py` (hoje só contagem + in-degree) com dimensão
  combate/região/DAT — sem isso o progresso do port fica invisível.
- Aceite: 4 loaders promovidos com notas; janela com plano (a) ou (b) registrado; `coverage_report.py` roda verde.

## 2. Fase 1 — tabelas data-driven (remake, sem mudar gameplay ainda)

- **1.1 Roster 46**: `kWeaponIds` já 46/46 — adicionar `factory_vtable/update/slot7` + `swap_to` como tabela
  de referência (seed de `weapon_definition.*`/`character_moves.*`), com `comboSlotLabel` Nome+N/Nome+Arma.
- **1.2 Magazines 92**: baseline original (`capacity,mode,reload_threshold,shot_interval,charge_stage_threshold,
  max_charge_stage`; todos mode 2/interval 0) para `match_economy.*`; fórmula recovery modo-2 como decisão.
- **1.3 Dano**: `positive_damage_values` como defaults (`melee_rules.h`/`projectile_behavior.h`/
  `weapon_definition.cpp`); fórmula inteira truncada + `/3` ≥10000 como D-novo com citação 638A18–638B9C.
- **1.4 Usage**: matriz `shot400_usage` (fase/frame por slot, ex. Rena0 reg0 fases 0–5 frame 12) para priorizar
  quais ataques implementar/animar primeiro.
- **1.5 Walks/births**: `walks` 46 VAs como oráculo de tuning (ex. f32 0.5); `births` 591 speeds (ex. 37.5)
  como defaults `projectile.h/cpp`; `controllers` D3DX (20 modelos) para calibrar durações.
- Aceite: testes `weapon_definition_test` estendidos passam; nenhum comportamento muda ainda (só dados + testes).

## 3. Fase 2 — animações (o coração do pedido)

Atual: 6 seletores + inferências 300/330/340 + jump + nata só Rena0; resto fallback set 0 (`anim_fallback`).
- **2.1 Mapeamento state→set por combo**: expandir `state_to_move_id()`/`move_program()` de 1 para 46 programas
  (famílias 300/330/340 + shots 400/402/450/460/360/370 + jump 40/41/42 + FA/HA/LA/StepA conforme evidência;
  sem inventar variantes — o que não tem input mapeado continua `anim_fallback` explícito, nunca set 0 silencioso).
- **2.2 Timing por move**: trocar `startup=activeFrame/active=delta senão 8/recovery 17` por
  `startup/active/recovery/cancel` tabelados (canônico Rena state400 12F→18F/50F→66F; `W(t)` bilinear +
  `floor(W+0.5)` como caso de teste). `phase.frame_count` (nº records) **nunca** como duração;
  `post-anchor ≠ recovery`.
- **2.3 Regras de move**: `kNataRules`-equivalente por combo (Speed/Turn/Approach/Decelerate/Launch/Hold/
  ActionCamera/Hide/Active) + `shot{{…}}` por tier; cadeia genérica `priority (row+0)` vs `cancelThreshold (row+4)`
  em vez do micro-caso 300→301/302.
- **2.4 Bindings**: muzzle por `+0x318` (hoje por tier, colide slot5); offsets arma em `Bip01_Prop1`;
  pesos `+0x75e0/+0xae14`; overlay base/arms se confirmado (124 sets hoje full-body); `FUN_004218c0` budget.
- **2.5 Trails/aura**: 10 trails hoje nunca lidos — religar só com ribbons reais; aura 7 `data/aura` com ossos
  medidos (11 ossos), sem cubos stand-in no caminho final.
- Aceite: Rena 0 sem `anim_fallback` nos paths cobertos; cada novo combo entra com teste
  (`animation_data_test/pose_test` + `fighter_script_test`) e sem fallback silencioso.

## 4. Fase 3 — combate overall (regras)

- **3.1 Hit**: `eligible_battle_hit` + `query_battle_hit` (raio 30, esfera×segmento, flags `0x10000/0x8000/
  0x20000`, `hit_gate==0`+HP≤0); filtro **dano positivo + raio positivo no mesmo record**.
- **3.2 Guarda**: `|relative|≤45°`, states 390/391/392, dreno 10/tick, `cooldown=2|0x100`, `guard_count++`.
- **3.3 Dano/stagger/survival/status**: pipeline `pre_damage→hit_resolution→damage` (0x638287–0x638f98);
  stagger `accum+=gate*resist/100`, `timer=120`, `accum≥100`; survival modo2 (HP=1, next 502/503); status 8 slots
  + DoT/pulsos; morte `over/1000+20+extra`.
- **3.4 Cargas**: `BattleAttackCharge/HitCharge/SpecialGauges::tick/begin*` (fórmulas `/133`, `/225`, `/90`;
  `begin2` HP=10000; modo2 −7 HP/tick); `tick/consume/charge_battle_magazine`.
- **3.5 Throw**: `capture/damage/release_held` + mesma escala 100/70/50/33; `vtable+0x20` melee ("Next dig")
  é o passo que destrava dano/reach/stun por personagem — atacar por último, com testes dedicados.
- Aceite: cada fórmula com teste unitário por intervalo FUN_; sem combo-scaling até evidência (hoje deliberado);
  facing-mask só quando implementado de verdade.

## 5. Fase 4 — projéteis por arma (fim do "idêntico para 45 armas")

- Expandir `kProjectileBehavior` de 9 linhas (só `weapon=1`) para tabela por arma: `damage/radius_percent|absolute`
  (mutuamente exclusivos), `length_percent`, `hit_effect`, `model_scale_percent`, `donor`; `burst/tag_burst 0–8
  (=herda)`, `shot_speed 0–1000%`, `spread 0–90°`, `homing` (só horizontal 42DB10, 40/46 handlers),
  `lifetime` (34/46), `life_cap`, `r=0..255`. `magazine→ammo`, `chargeMax→hold sec`, `tier→bullet`, `gauge 7/8`,
  `attackerHitstun 9`, `blob13/14 (+0x64/+0x68)` passam a consumidos, não parseados.
- Aceite: busca exaustiva nos 20 slots deixa de achar blobs zerados sem consumo; cada arma com comportamento
  distinto pinado em teste.

## 6. Fase 5 — CPU e câmera

- **CPU**: 6 comandos por arma (pesos `rangeScale/engage/power`, ranges 250000/160000/90000, rolls
  `0x32/0x96/0x9c4`), awakening por acorde, salto (`gauge>650`, dist²/obstáculo), charge aleatório —
  como dado por arma em `bot_brain.*`, não pesos globais.
- **Câmera**: `ordinary_battle_camera_view` + anchor/target + projeção (FOV 45°, near 50/100 far 150000);
  pendentes explícitos: auto-target-on-death, team awareness 2v2, shake em specials, target-switch dispatch.
- Aceite: `bot_brain`/`target_lock`/`arena_camera`/`live_camera` verdes + caso 2v2 quatro-views.

## 7. Fase 6 — validação e gates

- **Paridade**: replicar replay stage04 Ginkiha (chars 15/0,11/1,8/1,14/1; modos 0,1,0,2; 3968 frames, 59 campos)
  como teste do remake; antes, 0 diffs dele viram baseline nossa (gate hoje `false` por `awake_airdash`/`attack_cancel`).
- **Testes**: unitários por VA/intervalo; `ctest` como gate (ler o próprio summary, o denominador muda a cada suite);
  `RELEASE-CHECKLIST.md` §2–§3.5 para builds vivos (lembrar: capture ≠ live run, D9).
- **Commits**: um por fase, cada um com full diff review (sem código morto, sem logs temporários, sem duplicação,
  sem comentário óbvio) e `coverage_report.py` quando tocar research.

## 8. Ordem de execução sugerida (menor risco primeiro)

1. Fase 0 (evidência) + Fase 1 (tabelas sem mudar gameplay) — risco quase zero, destrava todo o resto.
2. Fase 2.1–2.2 (1–2 combos piloto, ex. Rena 0 + Mion 0) — prova o pipeline animação→timing→teste.
3. Fase 3.1–3.4 (hit/dano/guard/stagger/cargas) — núcleo testável.
4. Fase 4 (projéteis por arma) + Fase 2.3–2.5 (regras/bindings/trails).
5. Fase 3.5 (`+0x20` melee) + Fase 5 (CPU/câmera) — maior incerteza, por último.
6. Fase 6 (paridade stage04) como gate final antes de merge na `main`.

## 9. O que pedir ao Ginkiha (follow-up)

1. Os 2 `.jsonl` sources do attack-preview (sem eles, births/shot400 não são re-verificáveis). **aberto**
2. Mapa ID→nome de `hit_effect` + semântica de `fields[4,11,12]/flags28/parameters[2]`. **aberto**
3. Cancels/recovery por state (hoje: "post-anchor ≠ recovery"). **aberto**
4. Confirmação de SHA do binário. **resolvido 2026-10-09**: nosso `DaybreakDX.exe` = `27e61475…a6a07f02`,
   igual ao `original_exe_sha256` do bundle — todas as VAs aplicáveis (ver seção 7 do comparativo).
5. Licença/uso. **resolvido 2026-10-09**: Ginkiha liberou uso integral ("full use of everything");
   o alvo é DX vanilla + patch v1.11 oficial. Reimplementar com citação, sem colar runtime.

## 10. Riscos assumidos

- Binário canônico único = `DaybreakDX.exe` vanilla 2007 (`27e61475…`, "ver1.11"); `daybreakdx_111s.exe`
  é instalador SFX, não codebase. Nunca citar VA de outro binário (o base `daybreak.exe` 2006 tem SHA
  próprio e regiões que nosso corpus não tem).
- Janela hit/damage fora do corpus: ou re-extraímos, ou modelamos como decisão citada (nunca como símbolo falso).
- Corpos 6MB inauditáveis: não importar; reimplementar por família (dash→jump→melee→shoot).
- `shot_interval` original sempre 0: cadência é clock de animação — não criar "fire-rate de magazine" fictícia.
- Nomenclatura: `q` vs `r`, `swap_to` 1..46 ≠ ch/we, serial `+0x160` ≠ slot, `trail_root/tip` ≠ Euler, `label` ≠ nome.
