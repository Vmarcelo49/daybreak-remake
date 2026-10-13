#!/usr/bin/env python3
"""
coverage_report.py — Gera progress/coverage.json a partir de symbols/functions.json.

Saída é a MÉTRICA OFICIAL de progresso do projeto (ver PLANO_RECOMP.md seção 5.3).
"""
import json, os
from pathlib import Path
from datetime import datetime, timezone
from collections import Counter

REPO = Path(__file__).parent.parent
SYMBOLS = REPO / "symbols" / "functions.json"
CALLGRAPH = REPO / "binary_data" / "callgraph" / "full_call_graph.txt"
OUT = REPO / "progress" / "coverage.json"

def main():
    with open(SYMBOLS) as f:
        symbols = json.load(f)
    entries = symbols.get("entries", {})

    # Conta por status
    by_status = Counter(e.get("status", "unreviewed") for e in entries.values())

    # Identifica hot spots (funções com status unreviewed que são muito chamadas)
    # Lê call graph
    hot_spots = []
    in_degree = Counter()
    if CALLGRAPH.exists():
        with open(CALLGRAPH) as f:
            for line in f:
                m = __import__('re').match(r'\S+@([0-9a-fA-F]+) -> \S+@([0-9a-fA-F]+)', line.strip())
                if m:
                    in_degree[m.group(2)] += 1

    # Top 20 mais chamadas que estão unreviewed, ordenadas pelo in-degree do callgraph.
    unreviewed_addrs = [addr for addr, e in entries.items()
                       if e.get("status") == "unreviewed"]
    sorted_unreviewed = sorted(
        [(addr, in_degree.get(addr, 0)) for addr in unreviewed_addrs],
        key=lambda x: -x[1]
    )
    hot_spots = [
        {
            "symbol": f"FUN_{addr}",
            "address": addr,
            "called_by_count": count,
            "status": entries[addr].get("status", "unreviewed"),
            "source_file": entries[addr].get("source_file"),
        }
        for addr, count in sorted_unreviewed[:20]
        if count > 0
    ]

    # Calcula cobertura
    total_in_binary = 4092
    total_in_decompiled = len(list((REPO / "decompiled").glob("*.c")))
    reviewed_or_locked = by_status.get("reviewed", 0) + by_status.get("locked", 0)
    suggested = by_status.get("suggested", 0)
    stale = by_status.get("stale", 0)
    unreviewed = by_status.get("unreviewed", 0)

    coverage_percent = round(reviewed_or_locked / max(total_in_decompiled, 1) * 100, 2)
    suggestion_coverage = round((reviewed_or_locked + suggested) / max(total_in_decompiled, 1) * 100, 2)

    report = {
        "generated_at": datetime.now(timezone.utc).isoformat(timespec='seconds'),
        "total_functions_in_binary": total_in_binary,
        "total_in_decompiled": total_in_decompiled,
        "decompilation_coverage_percent": round(total_in_decompiled / total_in_binary * 100, 2),
        "functions_named_reviewed_or_locked": reviewed_or_locked,
        "functions_with_suggestion": suggested,
        "functions_unreviewed": unreviewed,
        "functions_stale": stale,
        "review_coverage_percent": coverage_percent,
        "suggestion_coverage_percent": suggestion_coverage,
        "hot_spots": hot_spots,
    }

    OUT.parent.mkdir(exist_ok=True)
    with open(OUT, "w") as f:
        json.dump(report, f, indent=2, ensure_ascii=False)

    print(f"=== coverage_report.py ===")
    print(f"Total no binário: {total_in_binary}")
    print(f"Total decompilado: {total_in_decompiled} ({report['decompilation_coverage_percent']}%)")
    print(f"Revisados/locked: {reviewed_or_locked} ({coverage_percent}%)")
    print(f"Com sugestão: {suggested}")
    print(f"Unreviewed: {unreviewed}")
    print(f"Stale: {stale}")
    print(f"\nTop 5 hot spots:")
    for h in hot_spots[:5]:
        print(f"  - {h['symbol']} (chamada {h['called_by_count']}x) — {h['source_file']}")
    print(f"\nSaída: {OUT}")

if __name__ == "__main__":
    main()
