# Plano de port — animações + combate data-driven (a partir do Ginkiha)

Branch `ginkiha-help` · 2026-10-09 (revisto: Fase 0 enxuta, implementação primeiro) · companheiro de
`docs/reports/ginkiha-comparison.md`.

**Mudança de postura:** o bundle do Ginkiha (`.local-analysis/balance-reference/` e
`.local-analysis/daybreak-rebuild/`) já contém as tabelas e fórmulas que precisamos, contra o **mesmo
binário** que analisamos (`DaybreakDX.exe` vanilla, SHA `27e61475…`). Re-promover símbolos no `research/`
só re-provaria o que ele já provou. Portanto: **implementar direto no `remake/`, citando proveniência
(bundle / arquivo original / VA)**. `research/` só é tocado em caso obscuro — gatilhos objetivos no §6.

Regras duras vigentes (`AGENTS.md`): nunca editar `research/recomp/`; manter `.X` sem conversão (SDL3+WebGPU
D2); todo ataque é personagem+arma (`comboSlotLabel`); **full diff review antes de CADA commit**;
comentários `why` + proveniência.

## Status das fases

| Fase | Estado | Data | Hora de conclusão |
|---|---|---|---|
| 0 — data layer (script + tabela + teste) | concluída | 2026-10-09 | 19:46 |
| 1 — piloto Rena 0 (timing→animação→valores→teste) | concluída | 2026-10-09 | 20:25 |
| 2 — generalizar 46 combos | pendente | 2026-10-09 | — |
| 3 — combate overall | pendente | 2026-10-09 | — |
| 4 — CPU/câmera | pendente | 2026-10-09 | — |
| 5 — paridade stage04 | pendente | 2026-10-09 | — |

## 0. Princípios

1. **Fonte primária quando existir**: se o campo está num arquivo original jogável (DAT de personagem/arma/
   bullet), ler do arquivo — a tabela do Ginkiha apenas confirma o campo/significado. Se não está em arquivo
   (comportamento de handler, decisão de CPU, timing ancorado em código), usar o valor do bundle citado.
2. **Lógica pura, sem plataforma**: portar só headers sem `windows.h`/D3D/DirectSound/rede. Nada de
   `runtime_*`/`windows_*`, rede UDP própria, ou patch de EXE.
3. **Sem fallback silencioso**: onde handler é desconhecido (ex. steering 40/46, expiry 34/46),
   rejeitar explicitamente, como o planner dele faz.
4. **Proveniência em três sabores**: `[bundle: <arquivo> <chave>]`, `[DAT: <arquivo> <campo>]`,
   `[VA 0x…, SHA 27e61475…]`. Campos desconhecidos (`fields[4,11,12]`, `flags28`, `parameters[2]`,
   effect IDs) preservados raw, nunca zerados.
5. **Paridade como gate**: replay stage04 (4 atores, 3968 frames, 59 campos) vira teste do remake.

## 1. Fase 0 — data layer enxuta (horas, não semanas)

- **0.1 Script de importação versionado** na árvore do remake (ex. `remake/foundation/tools/`): lê o bundle
  local e emite tabela(s) **commitadas** — só o que **não** está em arquivo original: timings ancorados
  (Rena state400 12F→18F/50F→66F), births (591 velocidades, ex. `1:0 → 37.5`), walks 46 VAs, parâmetros de
  CPU por arma, steering/lifetime handler-level. Nada de copiar os 15MB de catálogo para o repo.
- **0.2 Hash de reprodutibilidade**: o script registra os SHA256 do bundle (`bundle-manifest.json`) e falha
  em drift; reimportar é um comando. O que está em arquivo original **não** entra na tabela — continua lido
  em runtime (magazines, damage values, `parameters[3]` etc.).
- **0.3 Comentário de proveniência** em cada linha/tabela gerada (regra 0.4).
- **0.4 Não tocar**: `research/` (qualquer subárvore), install `Higurashi-Daybreak/`, build outputs.
- **Aceite**: Rena 0 consome a tabela importada em teste; `ctest` verde; zero arquivo de research modificado.

## 2. Fase 1 — piloto Rena 0 (prova o pipeline ponta a ponta)

- **Programa de move** completo para o combo: `Speed/Turn/Approach/Launch/Hold/ActionCamera/Hide/Active` +
  `shot{{…}}` (hoje `move_program()` só devolve o programa de Rena 0; `kLocomotion` já tem os números); cadeia genérica
  `priority (row+0)` vs `cancelThreshold (row+4)` em vez do micro-caso 300→301/302.
- **Timing**: `startup/active/recovery/cancel` tabelados — canônico 12F→18F, fim 50F→66F; `W(t)` bilinear +
  `floor(W+0.5)` como caso de teste. Substitui `startup=activeFrame/active=delta senão 8/recovery 17`.
- **Animação**: `state→set` sem fallback silencioso nos caminhos cobertos; bindings `+0x318` (muzzle), offset
  de arma em `Bip01_Prop1`, trailer `+0x1c/+0x20`; pesos `+0x75e0/+0xae14`; overlay base/arms se confirmado
  (124 sets hoje full-body).
- **Visual por arma**: trails (10 modelos hoje carregados mas nunca lidos — religar só com ribbons reais),
  aura `data/aura` (7 modelos, 11 ossos medidos), sem cubos stand-in no caminho final.
- **Valores**: dano 1750 (`rows`), mags `{6,2,300,0,60,1}+{2,2,300,0,180,2}`, recovery 900 ticks,
  birth 37.5 / turn 0.2, params do bullet DAT onde existirem.
- **Testes**: `animation_data_test`/`pose_test`/`fighter_script_test` + novo teste de timing por VA.
- **Aceite**: Rena 0 joga sem `anim_fallback` nos paths cobertos e sem valor hardcoded novo.

## 3. Fase 2 — generalizar para os 46 combos

Primeiro combo concluído 2026-10-09 20:52 (Mion 0: programa `mion` com regras medidas dos
bodies + `fire_shot` aceitando linha -1 + caso de teste; ver commits `f0ab4f4`/`5c0fdbc` —
o segundo também calibrou o predicado verde do `hud_view_geometry`, que nunca havia
medido um anel aliado).
Segundo combo concluído 2026-10-09 21:03 (Rika 1: programa `rika` com rajada de 15 ticks
pares + salvas gêmeas T10/T30 + caso de teste; rows do tap resolvidas via tabela do item).
Terceiro combo concluído 2026-10-09 21:20 (Tomitake 2: programa `tomitake` com tiros
gêmeos 7+5 a cada 3 ticks + freeze-then-fire no charge; rows via trace fire_attachment).
Quarto combo concluído 2026-10-09 21:45 (Keiichi 2: programa `keiichi` com rajada densa
todo-tick 10–20 + stalls por rewind modelados como Hold com latch por regra; cancel de
pulo generalizado por combo na mesma leva).
Quinto combo concluído 2026-10-09 21:55 (Chie 2: programa `chie` com rajada por
scratch-counter 15–24 + salvas únicas row 2 no 450@22 e 460@15).
Sexto e sétimo combos concluídos 2026-10-09 22:07 (Kasai 1: programa `kasai` com
gêmeos 2+0 e salva quádrupla row 4; Takano 0: programa `takano` com tripla row 0 e
salvas únicas row 1).
Oitavo combo concluído 2026-10-09 22:14 (Irie 1: programa `irie` com gêmeos 0+1 no
tap e salvas únicas row 4 nos charges).
Nono e décimo combos concluídos 2026-10-09 22:44 (Mion 2: programa `mion2` com tiro
único no entry-tick 10 e rajada 10× no charge; Rika 2: programa `rika2` com tick
único e fan triplo; pin do volley Kasai 0 corrigido para 21/31 eventos).
Décimo primeiro combo concluído 2026-10-09 22:56 (Satoko 0: programa `satoko` com
salva quíntupla no tap e salvas gêmeas congeladas no charge).
Décimo segundo combo concluído 2026-10-09 23:06 (Rika 0: programa `rika0` com gêmeos
no tap e salvas duplas nos charges).
Décimo terceiro combo concluído 2026-10-09 23:52 (Rena 1: programa `rena1` como subconjunto
normal das agendas fixed-row 400/450, medido no runtime helper e corroborado pelo oracle de
state400; 402 condicional, spread RNG, state460 e second-charge pitch/origin ficam documentados
e sem binding).
Akane 2 analisado 2026-10-10: dispatch, usage, birth, walks e origem dos callbacks pinados; adiado
como programa porque os corpos usam `FUN_00435450` (origem mundial com XYZ calculado), que não cabe
em `MoveRule::Launch` (origem attachment/bone). O próximo combo escolhido foi Natsumi 0.
Décimo quarto combo concluído 2026-10-10 01:56 (Natsumi 0: somente state400 normal grounded,
Hide das duas props a partir do tick 14 e row 0 em 14F; callback/registration pinados. Sem claims
sobre alcance natural das fases, flag bruto, admissão/spawn ou geometria. State402 e cargas permanecem
abertos).
Keiichi 0 analisado 2026-10-10: identidade/uso/birth/walk e callback hand-origin pinados; adiado,
pois FUN_00435220 recebe a matriz de Bip01_R_Hand e o port só oferece Launch via Prop1. Não simular
o callback com origem/row incertos. Keiichi 1 audit concluído 2026-10-10 10:40 (São Paulo): actor01 + item018, swap8,
handler/vtable 0x473610/0x6a4f28, walk0x473a5a, birth30/turn0.1 pinados. State400:
normal slot0/tag slot1, uma requisição hand-origin em 13F por fase forçada. Corpos400/402
usam Bip01_R_Hand; 450/460 fazem duas requisições world-origin em 20F (operandos brutos
9 + 2/3), com XYZ/yaw/pitch calculados e alturas +40/+20. Nenhum subconjunto de firing
cabe no Launch atual; regras de movimento isoladas não justificam binding que omita os
tiros. Mantido sem MoveProgram. Gate: rebuild Linux + CTest 65/65; tables387/fighter637,
zero falhas. Próximo: Satoko 2, com recon e body audit antes de portar.

1. **Prioridade**: matriz `shot400_usage` (52 normal + 60 tag em state400) ordena quais combos saem do piloto
   primeiro; cada combo entra com teste, nunca com fallback set 0 silencioso.
2. **Walks** 16×3 por combo (VAs do `exe-catalog.walks` como oráculo de tuning; valor do DAT quando existir).
3. **Projéteis por arma**: 591 births; 92 mags; `burst/tag_burst 0–8`, `shot_speed 0–1000%`, `spread 0–90°`,
   `homing` (só horizontal, 42DB10), `lifetime`, `life_cap`, `r=0..255`; campos já parseados passam a
   consumidos (`gauge 7/8`, `attackerHitstun 9`, `blob13/14 → +0x64/+0x68`, `hitSound +0x6C`,
   `impactEffect +0x70`, modelo 260B).
4. **Melee `vtable+0x20`** (o "Next dig" do roadmap): dano/alcance/stun por personagem; escala 100/70/50/33.
- **Aceite**: `weapon_definition_test`/`move_behavior` estendidos por combo; zero comportamento compartilhado
  entre armas onde o bundle mostra valores distintos.

## 4. Fase 3 — combate overall (regras)

- **Hit**: `eligible/query_battle_hit` — raio 30, esfera×segmento, flags `0x10000/0x8000/0x20000`,
  `hit_gate==0`+HP≤0; filtro **dano positivo + raio positivo no mesmo record**.
- **Guarda**: `|relative|≤45°`, states 390/391/392, dreno 10/tick, `cooldown=2|0x100`, `guard_count++`.
- **Dano**: pipeline `pre_damage→hit_resolution→damage` (0x638287–0x638f98); inteiro truncado com `/3`
  quando `base≥10000`; morte `over/1000+20+extra`.
- **Stagger/survival/status**: `accum+=gate*resist/100`, `timer=120`, `accum≥100`; survival modo2 (HP=1,
  next 502/503); status 8 slots + DoT/pulsos.
- **Cargas**: `SpecialGauges::tick/begin*` (`/133`, `/225`, `/90`; `begin2` HP=10000; modo2 −7 HP/tick);
  `charge_battle_magazine`.
- **Throw**: `capture/damage/release_held` com a mesma escala 100/70/50/33.
- **Economia**: KO/overkill/timeout/respawn já recuperados — respawn passa a seguir o fim do KO move
  (hoje 3s = PORT RULE) e ponto/capacidade conforme o original.
- **Aceite**: cada fórmula com teste unitário citando a VA; facing-mask/8-way e combo-scaling só entram com
  evidência (hoje deliberadamente ausentes).

## 5. Fase 4 — CPU e câmera

- **CPU**: 6 comandos por arma (pesos `rangeScale/engage/power`; ranges 250000/160000/90000; rolls
  `0x32/0x96/0x9c4`), awakening por acorde, salto (`gauge>650`), charge aleatório — como dado por arma em
  `bot_brain.*`, não pesos globais.
- **Câmera**: `ordinary_battle_camera_view` + anchor/target + projeção (FOV 45°, near 50/100 far 150000);
  pendentes explícitos: auto-target-on-death, team awareness 2v2, shake em specials, target-switch dispatch.
- **Aceite**: `bot_brain`/`target_lock`/`arena_camera`/`live_camera` verdes + caso 2v2 quatro-views.

## 6. Quando (e só então) mexer em `research/`

Gatilhos objetivos — qualquer um desses, e só para o endereço envolvido:

1. Campo sem semântica (`fields[4,11,12]`, `flags28`, `parameters[2]`, `hit_effect`) que o port precisa.
2. VA citada pelo bundle sem `.c` no corpus (ex. janela `0x637960–0x638f98`) onde precisamos confirmar
   um comportamento antes de implementar.
3. Divergência medida entre tabela do bundle e o arquivo original.

Ação: ingestão pontual do endereço (`ingest.py`), promover a reviewed com nota, `coverage_report.py`,
commit separado. **Nada de varredura geral** — cobertura continua sendo métrica do pipeline, não pré-requisito
do port.

## 7. Fase 5 — validação e gates

- **Paridade**: replicar replay stage04 de Ginkiha (chars 15/0,11/1,8/1,14/1; modos 0,1,0,2; 3968 frames,
  59 campos) como teste do remake; os 0 diffs dele viram baseline nossa (gate dele hoje `false` por
  `awake_airdash`/`attack_cancel`).
- **Testes**: unitários por VA/intervalo; `ctest` como gate (ler o próprio summary — o denominador muda a
  cada suite); `RELEASE-CHECKLIST.md` §2–§3.5 para builds vivos (capture ≠ live run, D9).
- **Commits**: um por fase, cada um com full diff review (sem código morto, sem logs temporários, sem
  duplicação, sem comentário óbvio).

## 8. Ordem de execução

1. Fase 0 (script + tabela importada) — destrava tudo, risco quase zero.
2. Fase 1: piloto Rena 0 ponta a ponta (timing→animação→valores→teste).
3. Fase 2: generalizar tabelas (uso/walks/projéteis) combo a combo, pilotos primeiro.
4. Fase 3: combate overall (fórmulas com teste).
5. Fase 2.4 (`+0x20` melee) + Fase 4 (CPU/câmera) — maior incerteza, por último.
6. Fase 5: paridade stage04 como gate final antes de merge na `main`.

## 9. Follow-ups com o Ginkiha

1. Os 2 `.jsonl` sources do attack-preview (sem eles, births/shot400 não são re-verificáveis). **aberto**
2. Mapa ID→nome de `hit_effect` + semântica de `fields[4,11,12]/flags28/parameters[2]`. **aberto**
3. Cancels/recovery por state (hoje: "post-anchor ≠ recovery"). **aberto**
4. SHA do binário. **resolvido 2026-10-09**: `DaybreakDX.exe` = `27e61475…a6a07f02` = alvo do bundle.
5. Licença. **resolvido 2026-10-09**: uso integral liberado; reimplementar com citação, sem colar runtime.

## 10. Riscos assumidos

- Tabela derivada do bundle pode derivar: script versionado + hash do bundle; drift falha ruidosamente.
- Binário canônico único = `DaybreakDX.exe` vanilla 2007 (`27e61475…`, "ver1.11"); `daybreakdx_111s.exe` é
  instalador SFX, não codebase; nunca citar VA de outro binário.
- Janela hit/damage fora do corpus: só ingestão pontual via gatilho do §6; nunca símbolo inventado.
- Corpos 6MB inauditáveis: não importar; reimplementar por família (dash→jump→melee→shoot).
- `shot_interval` original sempre 0: cadência é clock de animação — não criar "fire-rate de magazine".
- Nomenclatura: `q` vs `r`, `swap_to` 1..46 ≠ ch/we, serial `+0x160` ≠ slot, `trail_root/tip` ≠ Euler,
  `label` ≠ nome da arma.
