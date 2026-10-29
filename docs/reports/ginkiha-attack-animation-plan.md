# Plano de ataque e animação — revisão da branch Ginkiha

> **Superseded as a work order — 2026-10-14.** This file is evidence and history.
> It does **not** authorize implementation work. The only active plan is
> [`docs/DIRECTION.md`](../DIRECTION.md); the mandate and the frozen list are in
> [`AGENTS.md`](../../AGENTS.md). Do not continue the per-combo porting this
> document describes.

2026-10-11 · `ginkiha-help` · revisão estática de HEAD `aa9588c` e seu código.
Companheiros: [plano geral](ginkiha-port-plan.md), [bloqueios de tiro](ginkiha-blockers-plan.md),
[grupo Rena](ginkiha-rena-iteration.md). Não houve execução do jogo nesta revisão.

## 1. Diagnóstico

O plano geral prometia timing→animação→combate, mas a expansão foi acompanhada sobretudo
por agendas de lançamento. O [ledger de tiros](ginkiha-shooting-coverage.md) declara
**0/46 combos auditados completos**. Bind de programa, linha correta e origem posada
não provam a admissão, a animação inteira nem o retorno do ataque ao movimento normal.
A antiga marcação de Fase 1 concluída era válida como piloto do pipeline; o aceite de
ataque completo fica reaberto. Isso não desfaz o que já foi implementado.

As animações não estão inteiramente ausentes dos commits. O commit `d6b03ce` inclui
rotas aéreas de Rena+0, dash lateral, ribbons e testes de execução. O problema é cobertura
parcial e um plano que não acompanha essa dimensão com o mesmo rigor que os projéteis.
Não foi medida aqui uma regressão visual específica; ela precisa de reprodução live.

| Dimensão | Evidência presente | Limite atual / ação necessária |
|---|---|---|
| Move→fase→clip | `Fighter::try_switch_animation`, `enter_phase`, `CharacterMoves`; NN.dat e `.X` reais | Selecionar a linha correta pelo handler/input, não só confirmar que o clip existe. Caminhos sem linha/set válido ainda usam set0 com `anim_fallback`. |
| Seleção de melee | `resolve_attack_move`: Rena+0 usa 300/320/330/332; outros combos aéreos usam 340 | Substituir a seleção simplificada por admissão e famílias por combo. A existência de 340 na tabela não prova que aquela entrada deve escolhê-lo. |
| Chains/cancels | `Fighter::update` encadeia 300→301→302 via flags/prioridade | Auditar direcional, lateral, dash, aterrissagem e follow-ups além dessa cadeia. |
| Fases/tempo | `.X` period + NN.dat `+0x20`; programas com Hold/Counter; gate especial de Rena+0 | Distinguir saída automática, saída controlada pelo body, seek e freeze. `animation_data_test::gated_attack_release` ainda aceita saída pelo timer fallback em um caminho com gate não zero. |
| Blend e canais | `bind_animation_set` / `tick_blend`, callback Rena+2 | Duas tracks de transição não demonstram dois canais corporais independentes. Comparar clocks e admissão parcial dos caminhos que usam tiro andando. |
| Arma visível | Muzzle por modelo e ribbons posados; testes de Rena+0 e Akane+0 | Rena+1 lança pelo modelo2, mas a troca da prop renderizada continua pendente no registro do grupo. Verificar hide/rebind/modelo e animação própria do item onde exigidos. |
| Testes | `animation_data_test` valida estrutura dos 46 combos e execuções específicas; `fighter_script_test` valida tiros | Contagens de parser e requisições não substituem cobertura de entrada, transições, pose e contato por ataque. |

`AttackA/B/C` e `ShotA/B/C` são chaves de voz, não nomes de clips (`fighter.h`,
`FUN_00431e70`). A unidade de port é **personagem+arma + caminho de ataque**, resolvido
através de move/fase/tag do NN.dat e do rig `.X` dessa combinação.

## 2. Fontes que devem entrar na implementação

O projeto local Ginkiha contém mais do que projéteis. Ler os headers sob
`.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src/` como referência,
sem importar o runtime de plataforma ou presumir paridade total do projeto doador:

- `battle_rena_melee_admission.hpp`: branches dos dispatchers `445ee0/44d850/43ded0`,
  incluindo direcional, dash, aéreo e chains. Conferir os gates nos handlers originais.
- `battle_rena_{ordinary,ground,directional,followup,landing}_melee.hpp` e
  `ground_melee_native_control.hpp`, `dash_melee_native_control.hpp`,
  `air_melee_native_control.hpp`, `directional_melee_native_control.hpp`: execução do
  movimento e suas transições; os `roster_*melee*.hpp` orientam a generalização seguinte.
- `actor_animation_service.hpp`, `actor_animation_settings.hpp`, `actor_track_time.hpp`,
  `actor_track_blend.hpp`: metadados, binds, pesos e clocks. O serviço possui dois canais;
  seu `step` atualiza posições com os pesos antigos antes de calcular o blend.
- `development_animated_combat.hpp`: integração, em particular
  `bind_actor_animation_state`, `synchronize_actor_animation_admission`,
  `actor_secondary_animation_frame` e `advance_actor_animation_service`. Os caminhos
  de tiro andando recuperados preservam o canal inferior e seu relógio e vinculam o
  superior separadamente. Auditar `uses_layered_walk_shot` por combo antes de generalizar.

Os handlers originais de Rena estão em `research/decompiled/FUN_0043ffc0.c`,
`FUN_00448220.c`, `FUN_00438310.c` e seus dispatchers; usar o corpus como leitura.
NN.dat/.X continuam sendo a fonte dos dados de animação. Não criar clips novos nem
converter os assets. Cada regra implementada deve citar a fonte e VA correspondente;
conflitos com o doador exigem conferir o handler canônico, não copiar seu comportamento.

## 3. Próxima execução — Rena+0/+1/+2

1. **Reproduzir a falha visível:** usar o host live com `--no-audio` e o instrumento
   existente (`remake/foundation/scripts/live_debug.py`) para registrar input, combo,
   estado/move, fase, tick, clip, clocks, arma e contatos. Registrar também o caminho
   correto no original quando possível. Capturas em ticks escolhidos complementam a
   execução; não provam fluidez live (D9).
2. **Matriz de admissão por arma:** neutral, direcional, dash frontal/lateral/traseiro,
   salto, air-dash, aterrissagem, chain/cancel, tap e duas cargas; normal/powered onde
   o handler distinguir. Para cada entrada, identificar move/fase de destino, flags,
   prioridade, target/facing e condições de retorno. Não assumir que uma família
   numérica inteira é legal para as três armas.
3. **Portar os seletores e bodies faltantes:** começar pelos caminhos que reproduzem
   o defeito. Fechar movimento, giro, gravidade, seek/freeze, fases, cancel/recovery e
   hit/miss/landing quando forem parte do ataque. Conservar as rotas Rena+0 já testadas;
   confirmar seus gates, em vez de estender 320/332 a todo o elenco.
4. **Fechar apresentação da arma:** Rena+1 modelo2 renderizado, hide/rebind de slots,
   offsets posados e ribbons; ligar animação própria do item somente onde a fonte exige.
   Verificar o conjunto corpo+arma no startup, disparo/contato e recovery.
5. **Auditar o serviço de animação:** confrontar bind/reset, clock e ordem de avaliação
   do remake com os canais Ginkiha e as VAs `00421100/00421410/0041f580`. Implementar
   canais/máscaras e clocks separados para os caminhos recuperados que precisem deles;
   não tratar blend entre duas poses como evidência de overlay corporal.
6. **Verificar o grupo inteiro:** entradas reais em testes, sem forçar a fase para o
   witness de alcance; sequência esperada independente do código sob teste; poses de
   ossos e item em ticks de referência, hit/miss e interrupção. Fechar também as rotas
   aéreas/follow-ons de tiro já listadas no registro Rena. Só então avançar para Mion.

## 4. Registro e aceite por caminho

Para cada personagem+arma, registrar os caminhos em uma tabela de revisão do grupo:

| Caminho/input | Fonte/VA | Move/fases/clips esperados | Clocks/movimento | Arma/contato | Teste e evidência live | Estado |
|---|---|---|---|---|---|---|
| A preencher na investigação do grupo | handler + DAT/.X | sequência esperada | seeks/holds/saída | modelo/slot/hit/miss | resultado + limites | pendente / implementado / verificado / N/A com fonte |

Um caminho só fica **verificado** quando input real alcança os moves corretos, a pose
completa e o item seguem os clocks/transições da fonte, o contato ou lançamento acontece
na fase certa, e recovery/cancel/landing retornam ao estado correto. Não admitir fallback
set0, timer provisório, prop errada ou fase forçada como gate de conclusão. Set0 legítimo
ou estado sem seletor não é fallback; documentar a diferença.

Testes automatizados de assets/execução e comparação visual live têm resultados separados.
Sem referência live comparável, declarar “implementado; paridade visual pendente”.
Ausência de header, de trace ou de uso em um replay não prova N/A. Guardar cada caminho
não resolvido como tarefa concreta com fonte a investigar, sem promover o combo.

Após mudanças de código: rebuild Linux + CTest completo, os testes específicos de
animação/fighter/melee afetados, builds Windows/web e smoke silencioso dos ataques
alterados. Builds cruzados não demonstram execução nesses alvos. Nesta revisão de
plano não se repetiram builds nem testes; os resultados citados nos registros anteriores
permanecem históricos. Antes de commit, revisar todo `git diff` e `git diff --cached`.
