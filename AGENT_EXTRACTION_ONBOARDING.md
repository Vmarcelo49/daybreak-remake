# Onboarding — Agente de Extração (Ghidra/MCP)

> **Seu papel**: executar fases que requerem acesso direto ao Ghidra via túnel MCP. Você é o único que pode tocar no projeto Ghidra e rodar ferramentas MCP.
>
> **Pré-requisito**: ter lido `CONTEXT.md` primeiro.
> **Você precisa do túnel MCP ativo** — pedido ao operador para subir.

## 1. TL;DR

Seu trabalho se divide em duas frentes:

### 1.1 Frentes principais
1. **Fase 9**: confirmar a natureza de `0x006a16c0` e mapear scene handlers
2. **Fase 11**: análise de multiplayer/network (pode ser offline se strings revelarem)
3. **Fase 12**: rodar `detect_malware_behaviors` (última sessão MCP antes de fechar túnel)
4. **Re-extração**: se `binary_data/` precisar ser atualizado (ex: dump completo de `.rdata`)

### 1.2 O que você NÃO faz
- ❌ **Não edita `symbols/functions.json` diretamente quando há conflito** — vira nota em `notes.json` e operador decide
- ❌ **Não usa `rename_function` no Ghidra** — usa `set_plate_comment` + `add_function_tag` no máximo
- ❌ **Não edita arquivos em `recomp/`** — build output
- ❌ **Não faz trabalho do agente local** — não analisa `unreviewed` em massa; você só sugere com base no contexto do Ghidra (call graph, xrefs, strings)

## 2. Setup do túnel MCP

### 2.1 Confirmar com operador antes de começar
- [ ] Ghidra 11.x aberto com `DaybreakDX.exe` carregado e analisado
- [ ] Plugin GhidraMCP ativo (CodeBrowser → File → Configure → Miscellaneous → GhidraMCPPlugin)
- [ ] `mcp-proxy` rodando em `localhost:8081` (ou outra porta)
- [ ] `cloudflared tunnel --url http://localhost:8081` ativo
- [ ] Operador te passou a URL `https://<random>.trycloudflare.com`

### 2.2 Inicializar sessão MCP
```bash
URL="https://<random>.trycloudflare.com/mcp"

# Initialize e captura session ID do header
curl -s -m 15 -D /tmp/headers.txt -o /tmp/resp.txt -X POST "$URL" \
  -H "Content-Type: application/json" \
  -H "Accept: application/json, text/event-stream" \
  -d '{"jsonrpc":"2.0","id":1,"method":"initialize","params":{"protocolVersion":"2025-03-26","capabilities":{},"clientInfo":{"name":"super-z","version":"1.0"}}}'

# Pega o session ID
SESSION=$(grep -i "mcp-session" /tmp/headers.txt | awk '{print $2}' | tr -d '\r\n')
echo "Session: $SESSION"
```

### 2.3 Atualizar o helper
Edite `/home/z/my-project/scripts/ghidra_mcp.py` e troque `URL` e `SESSION`:
```python
URL = "https://<nova-url>.trycloudflare.com/mcp"
SESSION = "<novo-session-id>"
```

### 2.4 Testar
```bash
python3 /home/z/my-project/scripts/ghidra_mcp.py "list_open_programs" "{}" "/tmp/test.txt"
cat /tmp/test.txt
```
Se vier JSON com `DaybreakDX.exe`, está pronto.

## 3. Ferramentas MCP mais usadas

### 3.1 Leitura
| Tool | Quando usar |
|------|-------------|
| `list_open_programs` | Confirmar que o projeto está aberto |
| `get_current_program_info` | Metadata detalhada do programa |
| `get_function_by_address` | Info de uma função específica |
| `get_function_callees` / `get_function_callers` | Call graph direto (param: `name` ou `function_address`) |
| `get_xrefs_to` / `get_xrefs_from` | Xrefs de um endereço |
| `get_full_call_graph` | Todos os edges do call graph |
| `list_strings` (com `filter`) | Buscar strings por padrão |
| `search_strings` (com `search_term`) | Buscar strings por regex |
| `read_memory` | Ler bytes (max 16 por chamada) |
| `inspect_memory_content` | Ler bytes com análise (64 por chamada) |

### 3.2 Anotação (use com cautela — sem rename!)
| Tool | Quando usar |
|------|-------------|
| `set_plate_comment` | Documentar função identificada |
| `add_function_tag` | Marcar função com categoria |
| `set_disassembly_comment` | Anotar instrução específica |

### 3.3 Análise
| Tool | Quando usar |
|------|-------------|
| `analyze_call_graph` | Caminhos entre funções |
| `analyze_function_complete` | Análise 360° de uma função |
| `detect_malware_behaviors` | Fase 12 |
| `find_anti_analysis_techniques` | Fase 12 |
| `extract_iocs_with_context` | Buscar IOCs |

### 3.4 ⚠️ Ferramentas PROIBIDAS (sem aprovação do operador)
- `rename_function` / `rename_function_by_address` — use `set_plate_comment` no lugar
- `delete_function` / `create_function` — manipulação estrutural
- `set_image_base` — rebase global
- `run_ghidra_script` / `run_script_inline` — execução arbitrária

## 4. Fase 9 — Análise da "tabela" em 0x006a16c0

### 4.1 Estado atual do conhecimento
- `LoadNextScene` (0x00406310) é state machine baseada em `switch(*(pGameState + 0x2e18))`
- Tem cases 0, 1, 2, 3, ... cada um chamando FUN_* específicas (os "scene handlers")
- Xref: `From 006a16c0 [DATA]` indica que 0x006a16c0 é **um ponteiro** para LoadNextScene
- **Hipótese original estava parcialmente errada**: 0x006a16c0 provavelmente NÃO é uma tabela de scene handlers — é só um slot numa tabela maior de ponteiros de função

### 4.2 O que verificar (prioridade)
1. **Ler 256 bytes a partir de 0x006a16c0** com `read_memory` em chunks de 16
2. **Parsear como array de ponteiros de função** (cada 4 bytes = um endereço)
3. **Para cada ponteiro encontrado**: verificar se aponta para função (entre 0x00401000 e 0x006a0fff = .text)
4. **Cruzar com `binary_data/callgraph/full_call_graph.txt`** para confirmar quem é cada função apontada
5. **Decompilar 2-3 funções apontadas** para entender o padrão

### 4.3 O que esperar
Provavelmente 0x006a16c0 é o início (ou slot dentro) de uma **vtable** ou **dispatch table** — talvez:
- `static void (*scene_handlers[])(GameState*) = { LoadNextScene, ... };`
- Ou `static SceneHandler scene_table[] = { {1, LoadNextScene, ...}, ... };`

### 4.4 Entrega
Atualize `symbols/types.json` elevando hipótese `SceneHandler` de `confidence: low` para `medium` ou `high` conforme confirmado. Adicione entradas para cada scene handler encontrado em `symbols/functions.json` com `suggested_by: "agent:extraction"`.

## 5. Fase 11 — Análise de multiplayer/network

### 5.1 Passo a passo (maior parte offline)
```bash
# 1. Buscar imports de ws2_32.dll (Winsock)
grep -i "ws2_32\|ws2_32.dll\|winsock" binary_data/imports.txt

# 2. Buscar strings de rede
grep -iE "(socket|connect|listen|accept|send|recv|bind|127\.0\.0\.1|localhost)" binary_data/strings/*.txt

# 3. Se achar indícios: decompilar funções que chamam essas APIs
grep -l "ws2_32\|socket\|connect" decompiled/*.c
```

### 5.2 Se MCP estiver ativo
- `search_strings` com `search_term: "socket|connect|127\\."`
- `list_imports` filtrado por DLL de rede
- `analyze_call_graph` das funções que chamam APIs de rede

### 5.3 Entrega
- Listar todas as funções de network em `symbols/notes.json` sob chave `network_analysis`
- Sugerir nomes para as principais (`EstablishConnection`, `SendPlayerState`, etc.) em `symbols/functions.json`

## 6. Fase 12 — Detecção de anti-analysis (última sessão MCP)

### 6.1 Por que é a última
Essas tools são pesadas e o resultado esperado é "tudo limpo". Faz sentido rodar uma vez, salvar resultado, e fechar o túnel pra sempre.

### 6.2 Comandos
```bash
python3 /home/z/my-project/scripts/ghidra_mcp.py "detect_malware_behaviors" "{}" "binary_data/anti_analysis/malware_behaviors.txt"

python3 /home/z/my-project/scripts/ghidra_mcp.py "find_anti_analysis_techniques" "{}" "binary_data/anti_analysis/anti_debug_techniques.txt"

python3 /home/z/my-project/scripts/ghidra_mcp.py "extract_iocs_with_context" "{}" "binary_data/anti_analysis/iocs.txt"
```

### 6.3 Entrega
Criar `binary_data/anti_analysis/REPORT.md` com sumário do encontrado (provavelmente "nada relevante — binário limpo").

## 7. Convenções de commit para o agente de extração

Use prefixos:
- `feat:` para nova fase executada ou nova função decompilada
- `docs:` para atualização de PLANO.md / RELATORIO_COMPLETO.md
- `symbols:` para alterações em `symbols/*.json` vindas do contexto Ghidra
- `fix:` para correções

### 7.1 Exemplos
```
feat: Fase 9 — confirm scene handler table structure at 0x006a16c0
feat: Fase 11 — map 12 network functions (Winsock-based multiplayer)
feat: Fase 12 — anti-analysis scan complete (clean)
symbols: suggest names for 8 scene handlers (agent:extraction)
docs: update PLANO.md — Fase 9 completed
```

### 7.2 Escopo de push direto na `main`
- ✅ `decompiled/*.c` (novos arquivos do dump)
- ✅ `binary_data/*` (todos os dumps do MCP)
- ✅ `symbols/*.json` (suas sugestões)
- ✅ `progress/*`
- ✅ `*.md`, `NN_*.txt`
- ❌ `recomp/*.c` (build output)

## 8. Quando extrair dados novos para `binary_data/`

### 8.1 Cenários
- Descobriu que precisa de dados que não estão no dump (ex: dump completo de `.rdata`)
- Re-extração após mudança de versão do Ghidra (raro)
- Operador pediu nova análise específica

### 8.2 Como fazer
Use `read_memory` em chunks de 16 bytes (limitação do GhidraMCP v1.28.1) ou `inspect_memory_content` em chunks de 64. Para segmentos grandes, use script `mass_decompile_bounded.py` como template.

### 8.3 Dump completo de segmentos
Os segmentos que faltam dump completo:
- `.text` (0x00401000 - 0x006a0fff) — ~2.6 MB
- `.rdata` (0x006a1000 - 0x006b6fff) — ~90 KB ← **mais útil para Fase 9**
- `.data` (0x006b7000 - 0x006d9d07) — ~140 KB
- `.rsrc` (0x006da000 - 0x006dafff) — 4 KB

Dumpar `.rdata` é o mais valioso para Fase 9 (é onde está a "tabela" em 0x006a16c0). ~90 KB em chunks de 64 = ~1.440 chamadas MCP ≈ 30 min.

## 9. Cuidados com a sessão MCP

### 9.1 Sessões expiram
URLs `trycloudflare.com` são efêmeras — duram enquanto o `cloudflared` estiver rodando. Se o operador reiniciar o túnel, você precisa:
1. Pegar nova URL com ele
2. Re-rodar `initialize`
3. Atualizar `SESSION` em `/home/z/my-project/scripts/ghidra_mcp.py`

### 9.2 Timeouts
O túnel Cloudflare tem timeout de 100s por requisição. Para operações longas:
- Use batches pequenos (5-10 funções por chamada)
- Salve progresso incrementalmente
- Use `mass_decompile_bounded.py` como template — ele timeout-safe

### 9.3 Risco de segurança
Túnel expõe 192 ferramentas do MCP publicamente, **incluindo escrita**. Ver `PLANO.md` seção 2.1. Prática recomendada:
- Subir túnel só durante sessão ativa
- Derrubar ao finalizar
- Não aplicar tags/comments sensíveis sem revisão

## 10. Checklist inicial

- [ ] Li `CONTEXT.md` primeiro
- [ ] Li `PLANO.md` seção 5 (Fases 9, 11, 12) e seção 6 (achados-chave)
- [ ] Operador confirmou que túnel MCP está no ar
- [ ] Peguei nova URL + session ID
- [ ] Atualizei `/home/z/my-project/scripts/ghidra_mcp.py` com nova URL/SESSION
- [ ] Testei `list_open_programs` — confirmou `DaybreakDX.exe` aberto
- [ ] Li `AGENT_LOCAL_ONBOARDING.md` para entender o que o agente local faz (evitar sobreposição)
- [ ] Defini com operador qual fase vou executar primeiro

## 11. Próximas ações recomendadas (prioridade)

1. **Fase 9** (1-2h): análise de 0x006a16c0 — pode ser feita 80% offline (já temos LoadNextScene decompilado). Use MCP apenas para:
   - Ler bytes em 0x006a16c0 (confirmar é ponteiro único vs tabela)
   - Dumpar `.rdata` completo (opcional, mas útil)
2. **Fase 11** (1h): análise de network — 90% offline
3. **Fase 12** (5 min): rodar `detect_malware_behaviors` e fechar túnel pra sempre

## 12. Quando pedir ajuda ao operador

- Túnel caiu no meio de uma sessão
- Função crítica não faz sentido mesmo com MCP
- Conflito de sugestão com agente local precisa de decisão
- Quer fazer algo fora das fases planejadas (ex: Fase 13 opcional)
