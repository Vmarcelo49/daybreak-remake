#!/usr/bin/env python3
"""
generate_recomp.py — Lê decompiled/*.c + symbols/*.json e gera recomp/*.c.

Regras:
- Para cada .c em decompiled/, cria .c correspondente em recomp/
- Substitui FUN_<addr> por suggested_name quando status in (reviewed, locked)
- Insere comentário "// suggested name: X (confidence: Y)" para status=suggested
- Aplica clang-format se disponível
- Não edita nada se status=unreviewed (copia só o código, sem renomear)

NUNCA editar arquivos em recomp/ manualmente — sempre rodar este script.
"""
import json, os, re, subprocess, shutil
from pathlib import Path

REPO = Path(__file__).parent.parent
DECOMPILED = REPO / "decompiled"
RECOMP = REPO / "recomp"
SYMBOLS = REPO / "symbols" / "functions.json"
NOTES = REPO / "symbols" / "notes.json"

def load_symbols():
    with open(SYMBOLS) as f:
        return json.load(f)

def load_notes():
    if not NOTES.exists():
        return {}
    with open(NOTES) as f:
        return json.load(f)

def extract_addr(filepath: Path) -> str:
    """Extrai endereço do cabeçalho // Address: 0x00401030. Retorna '00401030' (8 chars)."""
    try:
        with open(filepath) as f:
            for line in f:
                m = re.match(r'//\s*Address:\s*(\S+)', line)
                if m:
                    addr = m.group(1).lower().lstrip('0x')
                    return addr.zfill(8)
    except:
        pass
    m = re.search(r'([0-9a-f]{8})', filepath.stem)
    return m.group(1) if m else None

def extract_code_body(filepath: Path) -> str:
    with open(filepath) as f:
        lines = f.readlines()
    return ''.join(l for l in lines if not l.startswith('//'))

def extract_name(filepath: Path) -> str:
    try:
        with open(filepath) as f:
            for line in f:
                m = re.match(r'//\s*Function:\s*(.+)', line)
                if m:
                    return m.group(1).strip()
    except:
        pass
    return filepath.stem

def apply_clang_format(content: str) -> str:
    """Aplica clang-format se disponível."""
    if not shutil.which("clang-format"):
        return content
    try:
        result = subprocess.run(
            ["clang-format", "--style=file"],
            input=content,
            capture_output=True,
            text=True,
            timeout=5,
        )
        return result.stdout if result.returncode == 0 else content
    except:
        return content

def rename_in_code(code: str, addr: str, old_name: str, new_name: str) -> str:
    """Renomeia ocorrências de old_name por new_name no código."""
    # Guard: old_name vazio gera pattern r'\b\b' (zero-width), que casa entre
    # cada par de caracteres e insere new_name em todo lugar (corrompe o código).
    if not old_name:
        return code
    # Cuidado: só renomear identificadores completos, não substrings
    # Use word boundaries
    pattern = r'\b' + re.escape(old_name) + r'\b'
    return re.sub(pattern, new_name, code)

def generate():
    # Limpa arquivos .c antigos antes de regenerar. Sem isso, quando uma função
    # muda de status (ex: suggested -> reviewed) e ganha novo nome de arquivo,
    # o arquivo antigo (FUN_<addr>.c) fica órfão em recomp/.
    if RECOMP.exists():
        for old in RECOMP.glob("*.c"):
            old.unlink()
    RECOMP.mkdir(exist_ok=True)
    symbols = load_symbols()
    notes = load_notes()
    entries = symbols.get("entries", {})

    stats = {"total": 0, "renamed": 0, "suggested_only": 0, "unreviewed": 0, "deduped": 0}

    # Pré-escaneia decompiled/ para resolver duplicatas: há pares como
    # FUN_<addr>.c + FUN_<addr>_06_top_hubs.c (curação manual que duplicou o
    # endereço). Para cada endereço, fica só com o arquivo "cânone" — o que tem
    # o nome mais simples (sem sufixo _nn_*) e o // Function: preenchido.
    canonical: dict[str, Path] = {}
    for c_file in sorted(DECOMPILED.glob("*.c")):
        addr = extract_addr(c_file)
        if not addr:
            continue
        name = extract_name(c_file)
        prev = canonical.get(addr)
        if prev is None:
            canonical[addr] = c_file
            continue
        # Desempate: prefere (1) nome não-vazio, (2) stem sem sufixo _nn_*
        def _score(f: Path, n: str) -> tuple:
            return (bool(n), not re.search(r'_\d{2}_', f.stem))
        if _score(c_file, name) > _score(prev, extract_name(prev)):
            canonical[addr] = c_file

    for addr, c_file in sorted(canonical.items(), key=lambda kv: kv[1].name):
        code = extract_code_body(c_file)
        original_name = extract_name(c_file)
        entry = entries.get(addr, {})

        status = entry.get("status", "unreviewed")
        suggested = entry.get("suggested_name")
        confidence = entry.get("confidence", "low")

        # Gera cabeçalho do recomp
        header_lines = [
            f"// ============================================",
            f"// Address:  0x{addr}",
            f"// Original: {original_name}",
        ]

        if status in ("reviewed", "locked") and suggested:
            # Renomeia no código
            code = rename_in_code(code, addr, original_name, suggested)
            header_lines.append(f"// Name:     {suggested} (status: {status})")
            stats["renamed"] += 1
        elif status == "suggested" and suggested:
            header_lines.append(f"// Suggested: {suggested} (confidence: {confidence})")
            header_lines.append(f"// Status:   {status} — name kept as comment until reviewed")
            stats["suggested_only"] += 1
        else:
            header_lines.append(f"// Status:   {status}")
            stats["unreviewed"] += 1

        # Adiciona notas se houver
        notes_key = suggested if suggested else original_name
        if notes_key in notes:
            for note in notes[notes_key]:
                if not note.get("resolved", False):
                    marker = "TODO(decomp)" if note.get("type") == "ambiguity" else "NOTE"
                    header_lines.append(f"// {marker}: {note['text']}")

        header_lines.append(f"// ============================================")
        header_lines.append("")

        final_code = "\n".join(header_lines) + code
        final_code = apply_clang_format(final_code)

        # Nome do arquivo
        if status in ("reviewed", "locked") and suggested:
            out_name = f"{suggested}.c"
        else:
            out_name = c_file.name

        out_path = RECOMP / out_name
        with open(out_path, "w", encoding="utf-8") as f:
            f.write(final_code)
        stats["total"] += 1

    print(f"=== generate_recomp.py report ===")
    print(f"Total gerado: {stats['total']}")
    # Quantos arquivos em decompiled/ foram ignorados por serem duplicatas
    total_sources = sum(1 for _ in DECOMPILED.glob("*.c"))
    deduped = total_sources - stats["total"]
    if deduped > 0:
        print(f"  Duplicatas ignoradas (endereço já processado): {deduped}")
    print(f"  Renomeados (reviewed/locked): {stats['renamed']}")
    print(f"  Sugestão em comentário: {stats['suggested_only']}")
    print(f"  Sem revisão (unreviewed): {stats['unreviewed']}")
    print(f"\nSaída em: {RECOMP}")

if __name__ == "__main__":
    generate()
