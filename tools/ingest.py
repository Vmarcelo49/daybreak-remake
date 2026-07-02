#!/usr/bin/env python3
"""
ingest.py — Detecta mudanças em decompiled/ via hash de arquivo e dispara reprocessamento.

Uso:
    python3 tools/ingest.py              # scan incremental
    python3 tools/ingest.py --full       # recalcula tudo (primeira vez)

Saída:
    - Atualiza signature_hash em symbols/functions.json
    - Lista funções novas/alteradas para o agente local processar
    - Marca status: "stale" para funções que mudaram desde última rodada
"""
import json, os, sys, re, hashlib, argparse
from pathlib import Path
from datetime import datetime, timezone

REPO = Path(__file__).parent.parent
DECOMPILED = REPO / "decompiled"
SYMBOLS = REPO / "symbols" / "functions.json"

def signature_hash(code: str) -> str:
    """Hash SHA-256 do código normalizado (sem whitespace trailing)."""
    normalized = re.sub(r'\s+', ' ', code).strip()
    return hashlib.sha256(normalized.encode()).hexdigest()[:16]

def extract_addr_from_file(filepath: Path) -> str:
    """Extrai o endereço do cabeçalho // Address: 0x00401030.
    Retorna SEM prefixo 0x e SEM zeros à esquerda: '00401030' (8 chars).
    """
    try:
        with open(filepath) as f:
            for line in f:
                m = re.match(r'//\s*Address:\s*(\S+)', line)
                if m:
                    addr = m.group(1).lower().lstrip('0x')
                    # Padding pra 8 chars
                    return addr.zfill(8)
    except:
        pass
    # Fallback: nome do arquivo
    m = re.search(r'([0-9a-f]{8})', filepath.stem)
    return m.group(1) if m else None

def extract_code_body(filepath: Path) -> str:
    """Extrai apenas o código C (ignora cabeçalho //)."""
    with open(filepath) as f:
        lines = f.readlines()
    code_lines = [l for l in lines if not l.startswith('//')]
    return ''.join(code_lines)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--full', action='store_true', help='Recalcula tudo')
    args = parser.parse_args()

    # Carrega symbols/functions.json
    with open(SYMBOLS) as f:
        symbols = json.load(f)
    entries = symbols.setdefault("entries", {})

    # Varre decompiled/
    new_count = 0
    changed_count = 0
    unchanged_count = 0
    new_files = []
    changed_files = []

    for c_file in sorted(DECOMPILED.glob("*.c")):
        addr = extract_addr_from_file(c_file)
        if not addr:
            continue

        code = extract_code_body(c_file)
        current_hash = signature_hash(code)

        existing = entries.get(addr)
        if not existing:
            # Nova função — ainda não está em symbols/functions.json
            new_count += 1
            new_files.append({
                "address": addr,
                "file": str(c_file.relative_to(REPO)),
                "hash": current_hash,
            })
            # Cria entrada mínima (status: unreviewed)
            entries[addr] = {
                "suggested_name": f"FUN_{addr}",
                "confidence": "low",
                "status": "unreviewed",
                "source_file": str(c_file.relative_to(REPO)),
                "signature_hash": current_hash,
                "depends_on_unresolved": [],
                "notes_ref": None,
                "suggested_by": None,
                "reviewed_by": None,
                "last_updated": datetime.now(timezone.utc).isoformat(timespec='seconds'),
            }
        else:
            old_hash = existing.get("signature_hash", "")
            if old_hash != current_hash and old_hash != "calculated_by_ingest":
                # Hash mudou — marca como stale
                if existing["status"] in ("reviewed", "locked"):
                    existing["status"] = "stale"
                    changed_count += 1
                    changed_files.append({
                        "address": addr,
                        "file": str(c_file.relative_to(REPO)),
                        "old_hash": old_hash,
                        "new_hash": current_hash,
                    })
                existing["signature_hash"] = current_hash
            else:
                unchanged_count += 1
                # Atualiza hash se era placeholder
                if old_hash == "calculated_by_ingest":
                    existing["signature_hash"] = current_hash

    # Atualiza estatísticas
    by_status = {}
    for entry in entries.values():
        status = entry.get("status", "unreviewed")
        by_status[status] = by_status.get(status, 0) + 1
    symbols["_statistics"] = {
        "total_functions_in_binary": 4092,
        "total_in_decompiled": len(list(DECOMPILED.glob("*.c"))),
        "total_in_symbols_json": len(entries),
        "by_status": by_status,
        "last_ingest": datetime.now(timezone.utc).isoformat(timespec='seconds'),
    }

    # Salva
    with open(SYMBOLS, "w") as f:
        json.dump(symbols, f, indent=2, ensure_ascii=False)

    # Report
    print(f"=== ingest.py report ===")
    print(f"Novas funções detectadas: {new_count}")
    print(f"Funções alteradas (marked stale): {changed_count}")
    print(f"Funções inalteradas: {unchanged_count}")
    print(f"Total em symbols/functions.json: {len(entries)}")
    if new_files[:5]:
        print(f"\nPrimeiras 5 novas (para o agente local processar):")
        for f in new_files[:5]:
            print(f"  - {f['address']}: {f['file']}")
    if changed_files[:5]:
        print(f"\nPrimeiras 5 alteradas (precisam re-review):")
        for f in changed_files[:5]:
            print(f"  - {f['address']}: {f['file']}")

    # Lista completa em JSON pra próximo agente consumir
    out = {
        "new_files": new_files,
        "changed_files": changed_files,
        "summary": {
            "new": new_count,
            "changed": changed_count,
            "unchanged": unchanged_count,
        },
    }
    out_file = REPO / "progress" / "last_ingest.json"
    with open(out_file, "w") as f:
        json.dump(out, f, indent=2, ensure_ascii=False)
    print(f"\nLista completa salva em: {out_file}")

if __name__ == "__main__":
    main()
