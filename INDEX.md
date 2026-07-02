# Índice — DaybreakDX.exe Decompilation

> Arquivo gerado automaticamente pelo GitHub Action `.github/workflows/build-index.yml`
> Não editar manualmente — editar os artefatos fonte e fazer push.

## 📊 Estatísticas

| Métrica | Valor |
|---------|-------|
| Total de funções no binário | 4,092 |
| Funções em `decompiled/` (curado) | 3191 |
| Funções em `binary_data/functions/` (mass dump) | 3,087 |
| **Cobertura total** | **75.44%** |

## 📁 Estrutura do repo

```
daybreak-decomp/
├── PLANO.md                       Plano completo de decompilação
├── PROGRESSO.md                   Status em tempo real
├── INDEX.md                       Este arquivo
├── INDEX.json                     Índice legível por máquina
├── docs/                          Documentação de referência
│   ├── CONTEXT.md, PLANO_RECOMP.md, AGENT_*_ONBOARDING.md
│   ├── RELATORIO_COMPLETO.md, RELATORIO_EXECUTIVO_FINAL.md
│   └── conventions.md
├── decompiled/                    Funções curadas (106 .c)
├── binary_data/                   Dump massivo do Ghidra
│   ├── other/                       (48 arquivos)
│   ├── segments/                       (2 arquivos)
│   ├── types/                       (26 arquivos)
│   ├── strings/                       (23 arquivos)
│   ├── callgraph/                       (1 arquivos)
│   └── functions/                 JSON por função (~3.000+)
├── extraction_phases/             Dados brutos das fases 1-6 (01_*.txt — 06_*.txt)
└── .github/
    ├── workflows/build-index.yml  Action que gera este índice
    └── scripts/generate_index.py  Script gerador
```

## 🔍 Funções curadas (`decompiled/`)

| Arquivo | Endereço | Nome | Razão |
|---------|----------|------|-------|
| `decompiled/CRegKey.c` | `0x006940f0` | `CRegKey` | keyword:Key |
| `decompiled/CommonInit.c` | `0x00543c70` | `CommonInit` | keyword:Init |
| `decompiled/D3DXComputeNormals.c` | `0x00669d56` | `D3DXComputeNormals` | keyword:D3D |
| `decompiled/D3DXCreateEffect.c` | `0x00669d38` | `D3DXCreateEffect` | keyword:D3D |
| `decompiled/D3DXCreateTexture.c` | `0x00669d4a` | `D3DXCreateTexture` | keyword:D3D |
| `decompiled/D3DXFrameDestroy.c` | `0x00669d2c` | `D3DXFrameDestroy` | keyword:D3D |
| `decompiled/D3DXFrameFind.c` | `0x00669d32` | `D3DXFrameFind` | keyword:D3D |
| `decompiled/D3DXGetFVFVertexSize.c` | `0x00669d02` | `D3DXGetFVFVertexSize` | keyword:D3D |
| `decompiled/D3DXIntersect.c` | `0x00669d08` | `D3DXIntersect` | keyword:D3D |
| `decompiled/D3DXLoadMeshHierarchyFromXInMemory.c` | `0x00669d26` | `D3DXLoadMeshHierarchyFromXInMemory` | keyword:D3D |
| `decompiled/D3DXMatrixInverse.c` | `0x00669cf6` | `D3DXMatrixInverse` | keyword:D3D |
| `decompiled/D3DXMatrixLookAtLH.c` | `0x00669d44` | `D3DXMatrixLookAtLH` | keyword:D3D |
| `decompiled/D3DXMatrixMultiply.c` | `0x00669cd8` | `D3DXMatrixMultiply` | keyword:D3D |
| `decompiled/D3DXMatrixPerspectiveFovLH.c` | `0x00669d3e` | `D3DXMatrixPerspectiveFovLH` | keyword:D3D |
| `decompiled/D3DXMatrixRotationAxis.c` | `0x00669d50` | `D3DXMatrixRotationAxis` | keyword:D3D |
| `decompiled/D3DXMatrixRotationX.c` | `0x00669cea` | `D3DXMatrixRotationX` | keyword:D3D |
| `decompiled/D3DXMatrixRotationY.c` | `0x00669ce4` | `D3DXMatrixRotationY` | keyword:D3D |
| `decompiled/D3DXMatrixRotationYawPitchRoll.c` | `0x00669d20` | `D3DXMatrixRotationYawPitchRoll` | keyword:D3D |
| `decompiled/D3DXMatrixRotationZ.c` | `0x00669d14` | `D3DXMatrixRotationZ` | keyword:D3D |
| `decompiled/D3DXMatrixScaling.c` | `0x00669cd2` | `D3DXMatrixScaling` | keyword:D3D |
| `decompiled/D3DXMatrixTranslation.c` | `0x00669cf0` | `D3DXMatrixTranslation` | keyword:D3D |
| `decompiled/D3DXVec2Normalize.c` | `0x00669d1a` | `D3DXVec2Normalize` | keyword:D3D |
| `decompiled/D3DXVec3Normalize.c` | `0x00669cfc` | `D3DXVec3Normalize` | keyword:D3D |
| `decompiled/D3DXVec3Transform.c` | `0x00669cde` | `D3DXVec3Transform` | keyword:D3D |
| `decompiled/D3DXVec4Transform.c` | `0x00669d0e` | `D3DXVec4Transform` | keyword:D3D |
| `decompiled/Direct3DCreate9.c` | `0x00669d5c` | `Direct3DCreate9` | keyword:Direct3D |
| `decompiled/DirectInput8Create.c` | `0x00669d62` | `DirectInput8Create` | keyword:Input |
| `decompiled/FUN_00401030.c` | `0x00401030` | `FUN_00401030` |  |
| `decompiled/FUN_004010c0.c` | `0x004010c0` | `FUN_004010c0` |  |
| `decompiled/FUN_004011f0.c` | `0x004011f0` | `FUN_004011f0` |  |
| `decompiled/FUN_00401a00.c` | `0x00401a00` | `FUN_00401a00` |  |
| `decompiled/FUN_00401a60.c` | `0x00401a60` | `FUN_00401a60` |  |
| `decompiled/FUN_00401b30.c` | `0x00401b30` | `FUN_00401b30` |  |
| `decompiled/FUN_00401b80.c` | `0x00401b80` | `FUN_00401b80` |  |
| `decompiled/FUN_00401e80.c` | `0x00401e80` | `FUN_00401e80` |  |
| `decompiled/FUN_00402010.c` | `0x00402010` | `FUN_00402010` |  |
| `decompiled/FUN_00402040.c` | `0x00402040` | `FUN_00402040` |  |
| `decompiled/FUN_00402060.c` | `0x00402060` | `FUN_00402060` |  |
| `decompiled/FUN_00402080.c` | `0x00402080` | `FUN_00402080` |  |
| `decompiled/FUN_004020a0.c` | `0x004020a0` | `FUN_004020a0` |  |
| `decompiled/FUN_004020a0_06_top_dispatchers.c` | `0x004020a0` | `FUN_004020a0` |  |
| `decompiled/FUN_00402890.c` | `0x00402890` | `FUN_00402890` |  |
| `decompiled/FUN_00402b60.c` | `0x00402b60` | `FUN_00402b60` |  |
| `decompiled/FUN_00402be0.c` | `0x00402be0` | `FUN_00402be0` |  |
| `decompiled/FUN_00403470.c` | `0x00403470` | `FUN_00403470` |  |
| `decompiled/FUN_00403930.c` | `0x00403930` | `FUN_00403930` |  |
| `decompiled/FUN_004039d0.c` | `0x004039d0` | `FUN_004039d0` |  |
| `decompiled/FUN_004039d0_06_top_hubs.c` | `0x004039d0` | `FUN_004039d0` |  |
| `decompiled/FUN_004039f0.c` | `0x004039f0` | `FUN_004039f0` |  |
| `decompiled/FUN_00403a20.c` | `0x00403a20` | `FUN_00403a20` |  |
| ... | ... | ... | _(e mais 3141 funções)_ |

## 📦 Artefatos em `binary_data/`

### `other/` (48 arquivos)

- `binary_data/exports.txt` (17 bytes)
- `binary_data/segments_list.txt` (162 bytes)
- `binary_data/entry_points.txt` (116 bytes)
- `binary_data/external_locations.txt` (7,178 bytes)
- `binary_data/metadata.txt` (316 bytes)
- `binary_data/imports.txt` (5,604 bytes)
- `binary_data/data_items.txt` (4,500 bytes)
- `binary_data/globals.txt` (4,680 bytes)
- `binary_data/mass_decompile_progress.json` (37,466 bytes)
- `binary_data/open_programs.txt` (410 bytes)
- `binary_data/network_analysis/candidates.json` (14,668 bytes)
- `binary_data/network_analysis/FASE11C_REPORT.md` (14,964 bytes)
- `binary_data/network_analysis/FASE11B_REPORT.md` (11,063 bytes)
- `binary_data/network_analysis/FASE11_REPORT.md` (12,813 bytes)
- `binary_data/anti_analysis/FASE12_REPORT.md` (3,971 bytes)
- `binary_data/anti_analysis/anti_debug.txt` (11,666 bytes)
- `binary_data/anti_analysis/iocs.txt` (10,439 bytes)
- `binary_data/anti_analysis/malware_behaviors.txt` (260 bytes)
- `binary_data/render_pipeline/FASE_D3D_REPORT.md` (11,371 bytes)
- `binary_data/render_pipeline/FASE_RENDER_LOOP_REPORT.md` (15,191 bytes)
- _(e mais 28 arquivos)_

### `segments/` (2 arquivos)

- `binary_data/segments/segments_list.txt` (162 bytes)
- `binary_data/segments/Headers.bin` (4,096 bytes)

### `types/` (26 arquivos)

- `binary_data/types/cat_winnt.h.txt` (2,793 bytes)
- `binary_data/types/cat_WinDef.h.txt` (3,173 bytes)
- `binary_data/types/cat_basetsd.h.txt` (387 bytes)
- `binary_data/types/cat_mbstring.h.txt` (150 bytes)
- `binary_data/types/categories.txt` (520 bytes)
- `binary_data/types/cat_stdlib.h.txt` (387 bytes)
- `binary_data/types/cat_winuser.h.txt` (670 bytes)
- `binary_data/types/cat_winbase.h.txt` (1,456 bytes)
- `binary_data/types/cat_crtdefs.h.txt` (1,289 bytes)
- `binary_data/types/cat_excpt.h.txt` (388 bytes)
- `binary_data/types/cat_Demangler.txt` (1,692 bytes)
- `binary_data/types/cat_guiddef.h.txt` (235 bytes)
- `binary_data/types/cat_ehdata.h.txt` (56 bytes)
- `binary_data/types/cat_search.h.txt` (42 bytes)
- `binary_data/types/cat_vadefs.h.txt` (101 bytes)
- `binary_data/types/cat_unknwn.h.txt` (281 bytes)
- `binary_data/types/cat_wingdi.h.txt` (610 bytes)
- `binary_data/types/all_data_types.txt` (236 bytes)
- `binary_data/types/cat_mtdll.h.txt` (431 bytes)
- `binary_data/types/cat_mmsystem.h.txt` (1,345 bytes)
- _(e mais 6 arquivos)_

### `strings/` (23 arquivos)

- `binary_data/strings/filter_wav.txt` (584 bytes)
- `binary_data/strings/filter_file.txt` (521 bytes)
- `binary_data/strings/filter_select.txt` (1,303 bytes)
- `binary_data/strings/filter_dat.txt` (400 bytes)
- `binary_data/strings/filter_x.txt` (196 bytes)
- `binary_data/strings/filter_mpg.txt` (121 bytes)
- `binary_data/strings/filter_s.txt` (1,188 bytes)
- `binary_data/strings/filter_Cdata.txt` (98 bytes)
- `binary_data/strings/filter_voice.txt` (586 bytes)
- `binary_data/strings/filter_bgm.txt` (828 bytes)
- `binary_data/strings/filter_stage.txt` (78 bytes)
- `binary_data/strings/filter_teamselect.txt` (220 bytes)
- `binary_data/strings/filter_ERROR.txt` (864 bytes)
- `binary_data/strings/filter_File.txt` (521 bytes)
- `binary_data/strings/filter_Cmovie.txt` (25 bytes)
- `binary_data/strings/filter_bmp.txt` (2,966 bytes)
- `binary_data/strings/filter_ogg.txt` (804 bytes)
- `binary_data/strings/filter_error.txt` (864 bytes)
- `binary_data/strings/filter_keyconfig.txt` (35 bytes)
- `binary_data/strings/filter_data.txt` (3,391 bytes)
- _(e mais 3 arquivos)_

### `callgraph/` (1 arquivos)

- `binary_data/callgraph/full_call_graph.txt` (52,801 bytes)

## 📜 Documentos

- [`PLANO.md`](PLANO.md)
- [`PROGRESSO.md`](PROGRESSO.md)
- [`docs/RELATORIO_COMPLETO.md`](docs/RELATORIO_COMPLETO.md)

---

Última atualização: via GitHub Actions
