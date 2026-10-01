# Roadmap: Higurashi Daybreak — Port de Gameplay

## Escopo revisado (após contexto do user + RE round 3)

**DENTRO de escopo:** mesma estrutura de jogo do original — máquina de estados
de cenas frontend (opening → menu → mode select → character/team select →
config screens → gameplay → result), e gameplay 2v2 com câmera de arena
fighter que locka num fighter e cicla via botão. Suporte a 1P, 2P split, 4P
split (4 viewports 256×448 em grid 2×2 dentro de 800×600).

**FORA de escopo** (declarar explicitamente — exceto netplay, ver `decisions.md` D6):

- ❌ Matchmaking online além de LAN (netplay via LAN **é** escopo e foco;
  DirectPlay 8 substituído, não portado)
- ❌ Modo história com cutscenes (os vídeos `.mpg` rodam mas o story mode
  completo — branching, scenario data, save — não)
- ❌ Save / load de progresso
- ❌ Localização (textos ficam em japonês)
- ❌ Replay / training / survival / boss rush
- ❌ Settings gráficos (resolução fixa 800×600)
- ❌ Anti-cheat, mod support

## Achados de RE que mudam o plano

### 800×600 hardcoded

O binário tem `push 0x258` (600) e `push 0x320` (800) em sequência em
`fcn.00402890` — esse é o tamanho do backbuffer.  **Resolução é fixa**,
não tem menu de opções.  A janela client-area é 800×600.

### 4 viewports pra split-screen 4P

Em `fcn.00402890` vemos o setup de **4 viewports** em grid 2×2:
- Cada viewport: 256×448 pixels (`push 0x100` + `push 0x1c0`)
- Offsets: 32×32 (`push 0x20` + `push 0x20`)

Isso significa: 4P split-screen = grid 2×2 com margem de 32px.  2P split
provavelmente é 2 viewports lado a lado ou empilhados.

### Máquina de cenas (state machine) confirmada via strings

O binário tem strings `.data` que são **nomes de estados** (não de cenas
diretamente, mas de sub-estados de animação/gameplay):

```
opening (vídeo) → title (menu principal) → mode select → config (sons, controls)
                                                       → keyconfig (key bindings)
                                                       → teamselect → character select → gameplay
                                                                                          ↓
                                                                                       result → back to title
```

Backgrounds de cada cena (via BMPs no `daybreak00.dat`):

| Cena | Assets BMP |
|---|---|
| Title | `data/select/bg00.bmp`, `bg01.bmp` |
| Character Select | `data/select/p00-p03.bmp` (portraits), `data/select/%02d.bmp` (outros chars), `data/select/cos%02d.bmp` (costumes), `data/select/s1p-s4p.bmp` (1P/2P/3P/4P mode indicators) |
| Team Select | `data/teamselect/bg00.bmp`, `p00-p01.bmp`, `t%02d.bmp`, `add0/add1.bmp` |
| Config | `data/config/%04d.bmp` (4-digit numbered — many screens) |
| Key Config | `data/keyconfig/%04d.bmp` |
| Game Over | `data/object/gameover.bmp` |
| Result | `data/select/w%02d.bmp` (winner portraits) |

### Vídeos (4 total, no daybreak06.dat)

| Arquivo | Quando toca | Skip |
|---|---|---|
| `movie/op.mpg` | No boot, antes do title | Sim, qualquer botão do controle |
| `movie/prologue.mpg` | Início do story mode | Sim (story mode fora de escopo, mas se rodarmos o opening, o skip é igual) |
| `movie/staffroll.mpg` | Fim do story mode | — |
| `movie/staffroll2.mpg` | Alternativo do staffroll | — |

**Sem DirectShow import** — o jogo deve usar WinMM (`MciSendCommand`?) ou
um decoder MPEG próprio.  Confirmar quando implementarmos.

### Estado de animação do fighter (40+ sub-estados)

A string table `.data` em `0x6b73b0`-`0x6b7xxx` contém os nomes de
sub-estados de gameplay/anim que o fighter usa pra voice cues e anim:

```
attackA, attackB, attackC         → 3 tiers de light/heavy/special attacks
attackKO, damageKO                → KO animations
backattack, backdamage            → back attacks (presumably when getting hit from behind)
battlestart                       → round start animation
damage, damagedown                → taking damage (down = knocked down?)
fire, shotA, shotB, shotC, shotFinal → 4 projectile types (hadoukens, supers)
guard, guarded                    → blocking state
HPcheck                           → low HP state
intercept                         → counter-attack state
missdamage                        → missed attack recovery
nearLose, nearWin                 → dramatic near-loss / near-win states
oyashiro, oyashiroB               → "Oyashiro" = the Higurashi deity — special move?
poison                            → status effect
provoke                           → taunt
recovery                          → getting up from knockdown
reloadNG, reloadOK                → reload states (for projectile-using fighters)
revival                           → revive state (team mechanic for 2v2?)
spark                             → hit spark (VFX trigger)
specialA, specialB, specialC      → 3 special moves per fighter
tactics                           → pre-fight tactic pose
tagback, tagfront, tagOK          → tag-team mechanics (2v2 specific!)
thank                             → win/thank animation
```

**`tagback/tagfront/tagOK`** confirmam que **2v2 tem tag mechanics** — um
fighter pode "tag" o parceiro pra entrar.  Isso vai refletir no design do
state machine.

## Arquitetura revisada: Scene State Machine

O jogo é uma **máquina de estados de cenas**.  Cada cena é uma unidade
auto-contida com `enter()`, `update(dt)`, `render()`, `exit()`.  O
`SceneManager` mantém a pilha/corrente de cena ativa.

```
┌─────────────────────────────────────────────────────────────────┐
│  Bootstrap (main)                                               │
│   - CreateWindow 800×600, init D3D9, init SDL/DInput, load .DAT │
│   - Push Scene_Opening                                         │
│   v                                                             │
│  Scene_Opening (movie/op.mpg + skip-on-input)                  │
│   - Plays op.mpg, skip on any controller button                │
│   - On end/skip → Scene_Title                                  │
│   v                                                             │
│  Scene_Title (data/select/bg00.bmp background)                 │
│   - Menu items: Story, Multiplayer, Config, Key Config         │
│   - On select → Scene_ModeSelect                              │
│   v                                                             │
│  Scene_ModeSelect                                              │
│   - 1P vs CPU, 2P vs CPU, 2P vs 2P, 1P Story (skip story)     │
│   - On select → Scene_TeamSelect                              │
│   v                                                             │
│  Scene_TeamSelect (data/teamselect/*)                          │
│   - Each player picks 2 fighters (2v2)                         │
│   - On confirm → Scene_CharacterSelect (costumes)             │
│   v                                                             │
│  Scene_CharacterSelect (data/select/*)                         │
│   - Pick costumes, stage                                       │
│   - On confirm → Scene_Gameplay                              │
│   v                                                             │
│  Scene_Gameplay                                                │
│   - 2v2 arena fighter, 800×600, split-screen or shared        │
│   - Camera always locks on one fighter, Tab cycles target     │
│   - Tag mechanics (tagback/tagfront/tagOK)                    │
│   - On KO → Scene_Result                                       │
│   v                                                             │
│  Scene_Result (data/select/w%02d.bmp winner portrait)         │
│   - Shows winner, rematch or back to title                    │
│   - On rematch → Scene_Gameplay                              │
│   - On back → Scene_Title                                     │
└─────────────────────────────────────────────────────────────────┘

Side branches (entered from Title or paused):
  - Scene_Config (sound, screen brightness, etc)
  - Scene_KeyConfig (controller bindings)
```

## Milestones revisados

### M0 — Foundation (DONE)
Build, .DAT parser, .X loader, raycast, AssetManager, ArenaCamera.

### M1 — Asset Pipeline end-to-end (DONE)
- AssetManager extracts from .DAT → XModel::load_from_memory
- Validated against real game files (rika/01.X loads with magic `xof 0303bin 0032`)

### M4 — Arena Camera (DONE)
- ArenaCamera with target lock-on + cycle button + orbit + collision
- Constants ported from RE (height=300, distance=800, baseline angle=45°)

### M2 — Scene State Machine + Bootstrap (NEW, replaces old M2/M3 ordering)
**Objetivo**: arquitetura de cenas rodando, com 4 cenas stub (sem conteúdo
real, só fluxo).

- `src/core/scene.h` — `Scene` base class with `on_enter/on_exit/update/render`
- `src/core/scene_manager.h` — mantém scene ativa, transita com fade
- `src/main.cpp` refactor: bootstrap + scene manager, sem hard-coded model
  loading
- 4 scenes stub:
  - `Scene_Bootstrap` — carrega bundles, cria device, push Scene_Opening
  - `Scene_Opening` — placeholder black screen with "Press any button"
  - `Scene_Title` — placeholder menu com 1 item "Start"
  - `Scene_Gameplay` — carrega 1 fighter model via AssetManager + ArenaCamera
- Window fixa em 800×600 (mudar do atual 1280×720)

**Critério de sucesso**: ao abrir o .exe, vê cena preta "Press any button" →
aperta botão → vai pra cena title "Start" → aperta enter → vai pra gameplay
com o modelo.

### M3 — Video playback (opening.mpg)
**Objetivo**: rodar `movie/op.mpg` no boot com skip.

- `src/render/video_player.{h,cpp}` — decoder MPEG1/MP2 via
  [pl_mpeg](https://github.com/phoboslab/pl_mpeg) (single-file C lib, MIT),
  vendored em `src/third_party/pl_mpeg.h`. Anteriormente usava FFmpeg.
- `Scene_Opening` atualizada pra tocar op.mpg
- Skip via qualquer botão do controle/teclado

**Critério de sucesso**: vídeo toca do começo ao fim OU é skipado ao apertar
botão, depois transita pra Scene_Title.

### M5 — Input subsystem
**Objetivo**: ler 4 controllers + teclado (4 players simultâneos).

- `src/input/input_manager.{h,cpp}` — SDL2 wrapper
- Suporta até 4 gamepads via SDL_GameController (XInput)
- Teclado = 4 layout de players (P1: WASD, P2: arrows, P3: IJKL, P4: numpad)
- Bindings em `src/input/bindings.h` — mapa player→action→button

**Critério de sucesso**: 4 jogadores conseguem pressionar 4 botões
simultaneamente e o jogo registra os 4 (não há ghosting).

### M6 — Menu frontend scenes
**Objetivo**: title, mode select, team select, char select — todas funcionais
com backgrounds BMP e navegação via controle.

- `Scene_Title` — mostra `data/select/bg00.bmp`, navega entre Story/
  Multiplayer/Config/KeyConfig
- `Scene_ModeSelect` — seleciona 1P/2P/2v2
- `Scene_TeamSelect` — cada player escolhe 2 fighters do time (2v2)
- `Scene_CharacterSelect` — escolhe costume + stage
- UI via SDL2 surface blit (pré-D3D, simples) ou via D3DXSprite
- Navegação: directional + face buttons (confirm/cancel)

**Critério de sucesso**: 2 players conseguem fazer select completo,
escolhendo teams e costume, chegando ao gameplay.

### M7 — Split-screen rendering
**Objetivo**: 4 viewports em grid 2×2, cada uma com sua câmera.

- `src/render/viewport_grid.{h,cpp}` — setup de N viewports (1, 2, ou 4)
- 800×600 com grid 2×2 (256×448 cada) ou 2×1 (400×600 cada) ou 1×1 (full)
- Cada viewport: SetViewport + clear zbuffer + render scene
- Cada player tem sua ArenaCamera, ciclando entre os 4 fighters

**Critério de sucesso**: 4P split-screen com 4 câmeras independentes,
cada uma mostrando a arena do ponto de vista daquele player.

### M8 — Fighter + combat (melee + projectiles)
**Objetivo**: combate funcional com todos os estados do RE.

- `src/gameplay/fighter.{h,cpp}` — struct com HP, stamina, position,
  velocity, current animation state
- State machine com 40+ estados mapeados do RE:
  idle, walk, run, dash, jump, attackA/B/C, attackKO, damage, damagedown,
  damageKO, backattack, backdamage, battlestart, fire, shotA/B/C/Final,
  guard, guarded, HPcheck, intercept, missdamage, nearLose, nearWin,
  oyashiro, poison, provoke, recovery, reloadOK/NG, revival, spark,
  specialA/B/C, tactics, tagback, tagfront, tagOK, thank
- Hit detection via raycast (M5 do roadmap antigo, agora M8)
- Tag mechanics: tagfront/tagback/tagOK (2v2 troca de fighter ativo)
- Damage model: 100 HP, light=5, heavy=12, special=25

**Critério de sucesso**: 2v2 jogável, com tag, KO, result screen.

### M9 — Polimento
- HUD (HP/stamina, timer, character names)
- Hit sparks VFX
- Audio (BGM via SDL_mixer, voice cues via daybreak07.dat)
- Result screen com winner portrait

## Próximos passos imediatos

1. **M2 — Scene State Machine** (próximo milestone)
   - Criar `src/core/scene.h`, `src/core/scene_manager.h`
   - Refatorar `main.cpp` pra usar SceneManager
   - Mudar resolução de 1280×720 → 800×600
   - 4 cenas stub

2. **M3 — Video playback** (depois de M2)
   - Pesquisar: SDL2 não tem MPEG player nativo, precisamos de lib ou
     Media Foundation.  Avaliar custo/benefício.

3. **M5 — Input** (paralelo com M6/M7)
   - Já temos SDL2, falta só o wrapper

## Roadmap antigo (referência, marcado como superseded)

~~M3 (Fighter) → M4 (Camera) → M5 (Combat melee) → M6 (Projectiles) → M7 (Combat full) → M8 (Polish)~~

Substituído por M2 (Scene SM) → M3 (Video) → M5 (Input) → M6 (Menus) →
M7 (Split-screen) → M8 (Fighter+Combat) → M9 (Polish).

A câmera (M4 no roadmap antigo) já está implementada e integrada.  O
combat (M5/M6/M7 antigos) virou M8 (um milestone único, mais coeso).

## Referências

- Engenharia reversa do binário: `docs/reverse-engineering.md` (sections 1-14)
- Estado da implementação: `README.md`
