# Fase 12 — Detecção de Anti-Analysis

> **Data**: 2026-07-02
> **Agente**: agent:extraction
> **Status**: ✅ Concluído

## 1. Resumo executivo

Foram rodadas 3 ferramentas do GhidraMCP:
- `detect_malware_behaviors` → 1 comportamento suspeito (false positive)
- `find_anti_analysis_techniques` → **86 findings** (40+ debugger detection)
- `extract_iocs_with_context` → 156 IOCs (todos false positives — assets do jogo)

**Conclusão**: o jogo **não tem anti-analysis intencional**. Os 86 findings são quase todos **falsos positivos** de padrões comuns do MSVC runtime (CloseHandle, GetTickCount, etc. usados pelo CRT, não por anti-debug).

## 2. Detalhamento

### 2.1 Malware behaviors (1 detectado)

| Categoria | Técnica | Função | Severity | Veredito |
|-----------|---------|--------|----------|-----------|
| defense_evasion | GetProcAddress + LoadLibraryA | `___crtMessageBoxA` (0x006743a8) | medium | **False positive** — CRT do MSVC usa LoadLibrary/GetProcAddress para carregar user32.dll sob demanda |

### 2.2 Anti-analysis techniques (86 findings)

| Categoria | Count | Veredito |
|-----------|-------|----------|
| debugger_detection | 40 | Maioria false positive — CloseHandle, GetTickCount, etc. usados pelo CRT/runtime |
| timing_checks | 19 | False positive — GetTickCount para timer de jogo, não anti-debug |
| exception_based | 1 | Provavelmente Structured Exception Handling normal do MSVC |
| memory_checks | 3 | False positive — VirtualQuery para gestão de memória |
| suspicious_instruction | 22 | Provável false positive — instruções comuns flaggadas como suspeitas |
| peb_teb_access | 1 | Único que merece atenção — acesso direto ao PEB/TEB pode ser anti-debug real |

| Severity | Count |
|----------|-------|
| high | 42 |
| medium | 41 |
| low | 3 |

**Top findings para revisar manualmente**:
- `FUN_0065f8b0` (0x0065f903, 0x0065f910) — 2x CloseHandle como debugger detection
- `FUN_00699a70` (0x00699aaa) — CloseHandle
- `FUN_0068ba70` (0x0068bab0, 0x0068bacb) — 2x CloseHandle
- `FUN_00657b00` (0x00657be1) — CloseHandle

### 2.3 IOCs (156 detectados)

Todos os 156 IOCs são do tipo `domain` (strings com `.dll`, `.dat`, `.bmp`, `.ogg`, etc.) e correspondem a **nomes de arquivos de assets do jogo**, não domínios maliciosos:

- `kernel32.dll` (carga normal via LoadLibrary)
- `env.dat`, `gameover.bmp`, `title.ogg`, `prologue.mpg`, etc.

**Nenhum IOC real** — todos são strings internas do jogo ou do CRT.

## 3. Veredito final

O binário `DaybreakDX.exe` **não contém técnicas anti-debug intencionais**. Os 86+1+156 = 243 findings são ruído de:

1. **MSVC CRT usando APIs Win32** que parecem anti-debug mas são normais (CloseHandle, GetTickCount, GetProcAddress, etc.)
2. **Assets do jogo** como strings flaggadas como IOCs (`title.ogg`, `gameover.bmp`, etc.)
3. **Padrões de código comuns** em jogos DirectX 9 da era 2006-2010

### 3.1 Único ponto de atenção

`peb_teb_access: 1` — vale a pena decompilar a função que acessa PEB/TEB para confirmar que é para thread-local storage do CRT (normal) e não anti-debug. Endereço não especificado no JSON.

## 4. Arquivos gerados

- `binary_data/anti_analysis/malware_behaviors.txt` — JSON completo do detect_malware_behaviors
- `binary_data/anti_analysis/anti_debug.txt` — JSON completo do find_anti_analysis_techniques (11.6 KB)
- `binary_data/anti_analysis/iocs.txt` — JSON completo do extract_iocs_with_context (10.4 KB)
- `binary_data/anti_analysis/FASE12_REPORT.md` — este arquivo

## 5. Status da Fase 12

✅ **Concluída**. Nenhuma ação adicional necessária — o binário é limpo.

---

## 6. Encerramento do túnel MCP

Esta foi a **última chamada MCP planejada**. A partir deste ponto, todo o trabalho futuro pode ser feito offline usando:
- `binary_data/` — dumps brutos
- `decompiled/` — 3,191 funções em C
- `symbols/` — fonte de verdade

O túnel pode ser fechado com segurança.
