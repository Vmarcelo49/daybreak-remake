# Convenções — daybreak-decomp

> Documento vivo. Decisões técnicas ficam aqui; estrutura de pipeline fica em `PLANO.md` e `PLANO_RECOMP.md`.

## 1. Padrão de C

- **C11** (`-std=c11`)
- Justificativa: comentários `//`, declaração de variável em qualquer ponto do bloco, `stdint.h`, `_Static_assert`, anonymous unions.
- Não há objetivo de bit-matching contra o binário original.

## 2. Tipos

- Usar `stdint.h` para tamanho fixo: `uint32_t`, `int32_t`, `uint8_t`, etc.
- Para tipos Win32 manter os typedefs do Windows: `HWND`, `HMODULE`, `DWORD`, `BOOL`.
- Para tipos Direct3D manter `D3DXVECTOR3`, `D3DMATRIX`, etc.

## 3. Formatação

- `.clang-format` no raiz do repo, estilo LLVM com 4 espaços.
- Aplicado automaticamente por `tools/generate_recomp.py`.
- Ninguém formata manualmente — se o resultado não agrada, ajustar `.clang-format`, não o código.

## 4. Nomenclatura

### 4.1 Funções
- `PascalCase` para funções renomeadas (`LoadNextScene`, `CommonInit`).
- `FUN_<addr>` para funções ainda não identificadas (preservar endereço original).
- Nunca usar snake_case para funções (mantém estilo Win32 / DirectX).

### 4.2 Variáveis
- `snake_case` para variáveis locais (`count`, `scene_id`, `next_state`).
- `g_<nome>` para globais (`g_game_state`, `g_d3d_device`).
- `m_<nome>` para membros de struct (estilo COM/Hungarian-lite).

### 4.3 Structs
- `PascalCase` + sufixo `_T` se misturar com Win32 (`GameState`, `SceneHandler_T`).
- Campos em `snake_case`.

## 5. Comentários

### 5.1 Cabeçalho de função (gerado por `generate_recomp.py`)
```c
// ============================================
// Address:  0x00406310
// Original: FUN_00406310
// Name:     LoadNextScene (status: reviewed)
// ============================================
```

### 5.2 TODOs
- `// TODO(decomp): <descrição>` — ambiguidade não resolvida no decompilado
- `// TODO(recomp): <descrição>` — pendência de recomposição (ex: falta struct)
- `// NOTE: <descrição>` — observação útil sem ação pendente

### 5.3 Marcadores de rastreabilidade
- Sempre que renomear uma função, manter `// Original: FUN_<addr>` no cabeçalho.
- Se a função veio de sugestão do agente de extração (plate comment no Ghidra), incluir `// Suggested by: agent:extraction`.

## 6. Convenções de commit

### 6.1 Prefixos
- `feat:` nova função decompilada ou nova fase
- `fix:` correção em arquivo existente
- `docs:` atualização de relatório ou progresso
- `chore:` ajustes de config (`.gitignore`, scripts)
- `refactor:` renomeação ou reorganização
- `recomp:` reservado para commits do pipeline de recomp (gerados por `generate_recomp.py`)
- `symbols:` alterações em `symbols/functions.json` ou `symbols/notes.json`

### 6.2 Escopo de push direto na `main`
- ✅ `decompiled/*.c`
- ✅ `binary_data/*`
- ✅ `symbols/*.json` (com revisão humana)
- ✅ `progress/*`
- ✅ `*.md`, `NN_*.txt`
- ❌ `recomp/*.c` — commit apenas via `tools/generate_recomp.py` (commit automático) ou PR manual após revisão

## 7. Branches

- `main`: branch principal, sempre buildável
- `recomp-auto`: branch do pipeline automático (não usar para trabalho manual)

## 8. Quando uma função não pode ser renomeada

Status `unreviewed` ou `stale` → manter `FUN_<addr>` no código.
Colocar sugestão apenas como comentário:
```c
// suggested name: ParseAnimationHeader (confidence: medium, status: suggested)
void FUN_00401230(int param_1, char *param_2) {
```

## 9. Quando uma função PODE ser renomeada

Status `reviewed` ou `locked` → renomear livremente.
Manter rastreabilidade via cabeçalho:
```c
// ============================================
// Address:  0x00406310
// Original: FUN_00406310
// Name:     LoadNextScene (status: reviewed)
// Suggested by: agent:extraction
// Reviewed by: marcelo
// ============================================
uint __fastcall LoadNextScene(GameState *state) {
```

## 10. Quando uma função fica desatualizada

Se `signature_hash` mudar (função foi re-decompilada com resultado diferente):
- Status volta para `stale`
- Comentário automático em `notes.json` descrevendo o que mudou
- Re-review necessário antes de voltar para `reviewed`/`locked`
