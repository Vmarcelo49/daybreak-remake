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
    # Cuidado: só renomear identificadores completos, não substrings
    # Use word boundaries
    pattern = r'\b' + re.escape(old_name) + r'\b'
    return re.sub(pattern, new_name, code)

def generate():
    RECOMP.mkdir(exist_ok=True)
    symbols = load_symbols()
    notes = load_notes()
    entries = symbols.get("entries", {})

    stats = {"total": 0, "renamed": 0, "suggested_only": 0, "unreviewed": 0}

    for c_file in sorted(DECOMPILED.glob("*.c")):
        addr = extract_addr(c_file)
        if not addr:
            continue

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
    print(f"  Renomeados (reviewed/locked): {stats['renamed']}")
    print(f"  Sugestão em comentário: {stats['suggested_only']}")
    print(f"  Sem revisão (unreviewed): {stats['unreviewed']}")
    print(f"\nSaída em: {RECOMP}")

if __name__ == "__main__":
    generate()
