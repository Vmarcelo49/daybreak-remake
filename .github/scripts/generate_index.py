#!/usr/bin/env python3
"""
Gera INDEX.md e INDEX.json navegáveis a partir dos artefatos do repo.
Roda no GitHub Actions a cada push.
"""
import json
import os
import re
import sys
from pathlib import Path
from collections import Counter

REPO_ROOT = Path(__file__).parent.parent.parent
print(f"Repo root: {REPO_ROOT}")

# === 1. Coleta funções decompiled/ ===
decompiled_dir = REPO_ROOT / "decompiled"
functions = []
if decompiled_dir.exists():
    for f in sorted(decompiled_dir.glob("*.c")):
        # Lê cabeçalho do arquivo
        head = ""
        try:
            with open(f, encoding="utf-8") as fh:
                head = fh.read(2000)
        except:
            pass
        # Extrai metadados do comentário
        name = f.stem
        addr = ""
        reason = ""
        for line in head.split("\n"):
            m = re.match(r'//\s*Function:\s*(.+)', line)
            if m:
                name = m.group(1).strip()
            m = re.match(r'//\s*Address:\s*(\S+)', line)
            if m:
                addr = m.group(1)
            m = re.match(r'//\s*Reason:\s*(.+)', line)
            if m:
                reason = m.group(1).strip()
        functions.append({
            "name": name,
            "address": addr,
            "file": str(f.relative_to(REPO_ROOT)),
            "reason": reason,
            "size_bytes": f.stat().st_size,
        })

# === 2. Coleta binary_data/functions/ ===
bd_funcs_dir = REPO_ROOT / "binary_data" / "functions"
bd_funcs = []
if bd_funcs_dir.exists():
    for f in sorted(bd_funcs_dir.glob("*.json")):
        try:
            with open(f) as fh:
                d = json.load(fh)
            bd_funcs.append({
                "address": d.get("address", f.stem),
                "name": d.get("name", ""),
                "isThunk": d.get("isThunk", False),
                "isExternal": d.get("isExternal", False),
                "file": str(f.relative_to(REPO_ROOT)),
                "decompiled_size": len(d.get("decompiled", "")),
            })
        except Exception as e:
            print(f"  WARN: {f}: {e}", file=sys.stderr)

# === 3. Coleta binary_data/ artefatos ===
bd_artifacts = {}
binary_data = REPO_ROOT / "binary_data"
if binary_data.exists():
    for root, dirs, files in os.walk(binary_data):
        for f in files:
            p = Path(root) / f
            rel = str(p.relative_to(REPO_ROOT))
            # Pula functions/ (já tratado)
            if "functions/" in rel:
                continue
            category = "other"
            if "strings/" in rel:
                category = "strings"
            elif "types/" in rel:
                category = "types"
            elif "segments/" in rel:
                category = "segments"
            elif "callgraph/" in rel:
                category = "callgraph"
            bd_artifacts.setdefault(category, []).append({
                "file": rel,
                "size_bytes": p.stat().st_size,
            })

# === 4. Estatísticas ===
stats = {
    "total_functions_in_binary": 4092,
    "decompiled_in_decompiled_dir": len(functions),
    "decompiled_in_binary_data": len(bd_funcs),
    "total_coverage_pct": round(len(bd_funcs) / 4092 * 100, 2),
    "binary_data_categories": {k: len(v) for k, v in bd_artifacts.items()},
}

# === 5. INDEX.json ===
index = {
    "target": "DaybreakDX.exe",
    "target_info": {
        "format": "PE32",
        "arch": "x86 32-bit LE",
        "image_base": "0x00400000",
        "total_functions": 4092,
    },
    "stats": stats,
    "functions": functions,
    "binary_data_functions": bd_funcs,
    "binary_data_artifacts": bd_artifacts,
    "documents": [
        "PLANO.md",
        "PROGRESSO.md",
        "docs/RELATORIO_COMPLETO.md",
    ] if all((REPO_ROOT / d).exists() for d in ["PLANO.md", "PROGRESSO.md", "docs/RELATORIO_COMPLETO.md"]) else [],
}

with open(REPO_ROOT / "INDEX.json", "w", encoding="utf-8") as f:
    json.dump(index, f, indent=2, ensure_ascii=False)
print(f"INDEX.json: {len(json.dumps(index))} chars")

# === 6. INDEX.md (human-readable) ===
md = []
md.append("# Índice — DaybreakDX.exe Decompilation")
md.append("")
md.append("> Arquivo gerado automaticamente pelo GitHub Action `.github/workflows/build-index.yml`")
md.append("> Não editar manualmente — editar os artefatos fonte e fazer push.")
md.append("")
md.append("## 📊 Estatísticas")
md.append("")
md.append(f"| Métrica | Valor |")
md.append(f"|---------|-------|")
md.append(f"| Total de funções no binário | {stats['total_functions_in_binary']:,} |")
md.append(f"| Funções em `decompiled/` (curado) | {stats['decompiled_in_decompiled_dir']} |")
md.append(f"| Funções em `binary_data/functions/` (mass dump) | {stats['decompiled_in_binary_data']:,} |")
md.append(f"| **Cobertura total** | **{stats['total_coverage_pct']}%** |")
md.append("")
md.append("## 📁 Estrutura do repo")
md.append("")
md.append("```")
md.append("daybreak-decomp/")
md.append("├── PLANO.md                       Plano completo de decompilação")
md.append("├── PROGRESSO.md                   Status em tempo real")
md.append("├── INDEX.md                       Este arquivo")
md.append("├── INDEX.json                     Índice legível por máquina")
md.append("├── docs/                          Documentação de referência")
md.append("│   ├── CONTEXT.md, PLANO_RECOMP.md, AGENT_*_ONBOARDING.md")
md.append("│   ├── RELATORIO_COMPLETO.md, RELATORIO_EXECUTIVO_FINAL.md")
md.append("│   └── conventions.md")
md.append("├── decompiled/                    Funções curadas (106 .c)")
md.append("├── binary_data/                   Dump massivo do Ghidra")
for cat, files in bd_artifacts.items():
    md.append(f"│   ├── {cat}/{'':<22} ({len(files)} arquivos)")
md.append("│   └── functions/                 JSON por função (~3.000+)")
md.append("├── extraction_phases/             Dados brutos das fases 1-6 (01_*.txt — 06_*.txt)")
md.append("└── .github/")
md.append("    ├── workflows/build-index.yml  Action que gera este índice")
md.append("    └── scripts/generate_index.py  Script gerador")
md.append("```")
md.append("")
md.append("## 🔍 Funções curadas (`decompiled/`)")
md.append("")
md.append("| Arquivo | Endereço | Nome | Razão |")
md.append("|---------|----------|------|-------|")
for fn in functions[:50]:
    md.append(f"| `{fn['file']}` | `{fn['address']}` | `{fn['name']}` | {fn['reason']} |")
if len(functions) > 50:
    md.append(f"| ... | ... | ... | _(e mais {len(functions)-50} funções)_ |")
md.append("")
md.append("## 📦 Artefatos em `binary_data/`")
md.append("")
for cat, files in bd_artifacts.items():
    md.append(f"### `{cat}/` ({len(files)} arquivos)")
    md.append("")
    for f in files[:20]:
        md.append(f"- `{f['file']}` ({f['size_bytes']:,} bytes)")
    if len(files) > 20:
        md.append(f"- _(e mais {len(files)-20} arquivos)_")
    md.append("")

md.append("## 📜 Documentos")
md.append("")
for d in index.get("documents", []):
    md.append(f"- [`{d}`]({d})")
md.append("")
md.append("---")
md.append("")
md.append(f"Última atualização: via GitHub Actions")
md.append("")

with open(REPO_ROOT / "INDEX.md", "w", encoding="utf-8") as f:
    f.write("\n".join(md))
print(f"INDEX.md: {len('\n'.join(md))} chars")
