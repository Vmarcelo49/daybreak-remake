# Índice — DaybreakDX.exe Decompilation

> Arquivo gerado automaticamente pelo GitHub Action `.github/workflows/build-index.yml`
> Não editar manualmente — editar os artefatos fonte e fazer push.

## 📊 Estatísticas

| Métrica | Valor |
|---------|-------|
| Total de funções no binário | 4,092 |
| Funções em `decompiled/` (curado) | 104 |
| Funções em `binary_data/functions/` (mass dump) | 3,087 |
| **Cobertura total** | **75.44%** |

## 📁 Estrutura do repo

```
daybreak-decomp/
├── PLANO.md                       Plano completo de decompilação
├── PROGRESSO.md                   Status em tempo real
├── RELATORIO_COMPLETO.md          Relatório final consolidado
├── INDEX.md                       Este arquivo
├── INDEX.json                     Índice legível por máquina
├── decompiled/                    Funções curadas (106 .c)
├── binary_data/                   Dump massivo do Ghidra
│   ├── other/                       (19 arquivos)
│   ├── strings/                       (46 arquivos)
│   ├── segments/                       (2 arquivos)
│   ├── callgraph/                       (2 arquivos)
│   ├── types/                       (50 arquivos)
│   └── functions/                 JSON por função (~3.000+)
├── 01_*.txt — 06_*.txt            Dados brutos das fases 1-6
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
| `decompiled/FUN_004020a0_06_top_dispatchers.c` | `0x004020a0` | `FUN_004020a0` |  |
| `decompiled/FUN_004039d0_06_top_hubs.c` | `0x004039d0` | `FUN_004039d0` |  |
| `decompiled/FUN_00403a50_06_top_hubs.c` | `0x00403a50` | `FUN_00403a50` |  |
| `decompiled/FUN_00406850_loadnextcallee.c` | `` | `FUN_00406850_loadnextcallee` |  |
| `decompiled/FUN_00408330_06_top_dispatchers.c` | `0x00408330` | `FUN_00408330` |  |
| `decompiled/FUN_0040eb30_06_top_dispatchers.c` | `0x0040eb30` | `FUN_0040eb30` |  |
| `decompiled/FUN_0040f4c0_06_top_dispatchers.c` | `0x0040f4c0` | `FUN_0040f4c0` |  |
| `decompiled/FUN_00412110_06_top_dispatchers.c` | `0x00412110` | `FUN_00412110` |  |
| `decompiled/FUN_00412ac0_06_top_dispatchers.c` | `0x00412ac0` | `FUN_00412ac0` |  |
| `decompiled/FUN_00414750_06_top_dispatchers.c` | `0x00414750` | `FUN_00414750` |  |
| `decompiled/FUN_00414d30_06_top_dispatchers.c` | `0x00414d30` | `FUN_00414d30` |  |
| `decompiled/FUN_00415630_06_top_dispatchers.c` | `0x00415630` | `FUN_00415630` |  |
| `decompiled/FUN_00415d30_06_top_hubs.c` | `0x00415d30` | `FUN_00415d30` |  |
| `decompiled/FUN_00415ec0_06_top_hubs.c` | `0x00415ec0` | `FUN_00415ec0` |  |
| `decompiled/FUN_00416bb0_06_top_dispatchers.c` | `0x00416bb0` | `FUN_00416bb0` |  |
| `decompiled/FUN_0064aed0_06_top_hubs.c` | `0x0064aed0` | `FUN_0064aed0` |  |
| `decompiled/FUN_0064d250_entry_sub.c` | `` | `FUN_0064d250_entry_sub` |  |
| `decompiled/FUN_00655af0_06_top_hubs.c` | `0x00655af0` | `FUN_00655af0` |  |
| `decompiled/FUN_00655d60_06_top_hubs.c` | `0x00655d60` | `FUN_00655d60` |  |
| `decompiled/FUN_006560c0_06_top_hubs.c` | `0x006560c0` | `FUN_006560c0` |  |
| `decompiled/FUN_00656200_06_top_hubs.c` | `0x00656200` | `FUN_00656200` |  |
| `decompiled/FUN_00657390_06_top_hubs.c` | `0x00657390` | `FUN_00657390` |  |
| `decompiled/GetConnectionInterface.c` | `0x00695a30` | `GetConnectionInterface` | keyword:connect |
| ... | ... | ... | _(e mais 54 funções)_ |

## 📦 Artefatos em `binary_data/`

### `other/` (19 arquivos)

- `binary_data/segments_list.txt.full.json` (551 bytes)
- `binary_data/external_locations.txt` (7,178 bytes)
- `binary_data/globals.txt.full.json` (9,751 bytes)
- `binary_data/imports.txt` (5,604 bytes)
- `binary_data/data_items.txt.full.json` (9,415 bytes)
- `binary_data/imports.txt.full.json` (13,025 bytes)
- `binary_data/entry_points.txt` (116 bytes)
- `binary_data/metadata.txt.full.json` (873 bytes)
- `binary_data/exports.txt` (17 bytes)
- `binary_data/entry_points.txt.full.json` (451 bytes)
- `binary_data/data_items.txt` (4,500 bytes)
- `binary_data/mass_decompile_progress.json` (37,466 bytes)
- `binary_data/metadata.txt` (316 bytes)
- `binary_data/open_programs.txt.full.json` (1,125 bytes)
- `binary_data/globals.txt` (4,680 bytes)
- `binary_data/exports.txt.full.json` (251 bytes)
- `binary_data/external_locations.txt.full.json` (16,973 bytes)
- `binary_data/open_programs.txt` (410 bytes)
- `binary_data/segments_list.txt` (162 bytes)

### `strings/` (46 arquivos)

- `binary_data/strings/filter_player.txt.full.json` (341 bytes)
- `binary_data/strings/filter_ERROR.txt` (864 bytes)
- `binary_data/strings/filter_select.txt` (1,303 bytes)
- `binary_data/strings/filter_dat.txt.full.json` (1,099 bytes)
- `binary_data/strings/filter_select.txt.full.json` (3,055 bytes)
- `binary_data/strings/filter_data.txt.full.json` (7,597 bytes)
- `binary_data/strings/filter_keyconfig.txt.full.json` (291 bytes)
- `binary_data/strings/filter_s.txt.full.json` (2,835 bytes)
- `binary_data/strings/filter_Error.txt.full.json` (2,125 bytes)
- `binary_data/strings/filter_player.txt` (62 bytes)
- `binary_data/strings/filter_bmp.txt.full.json` (6,683 bytes)
- `binary_data/strings/filter_file.txt` (521 bytes)
- `binary_data/strings/filter_ERROR.txt.full.json` (2,125 bytes)
- `binary_data/strings/filter_Error.txt` (864 bytes)
- `binary_data/strings/filter_Cmovie.txt` (25 bytes)
- `binary_data/strings/filter_data.txt` (3,391 bytes)
- `binary_data/strings/all_strings.txt` (45 bytes)
- `binary_data/strings/filter_s.txt` (1,188 bytes)
- `binary_data/strings/filter_teamselect.txt.full.json` (691 bytes)
- `binary_data/strings/filter_bmp.txt` (2,966 bytes)
- _(e mais 26 arquivos)_

### `segments/` (2 arquivos)

- `binary_data/segments/Headers.bin` (4,096 bytes)
- `binary_data/segments/segments_list.txt` (162 bytes)

### `callgraph/` (2 arquivos)

- `binary_data/callgraph/full_call_graph.txt.full.json` (107,817 bytes)
- `binary_data/callgraph/full_call_graph.txt` (52,801 bytes)

### `types/` (50 arquivos)

- `binary_data/types/cat_mtdll.h.txt.full.json` (1,091 bytes)
- `binary_data/types/cat_fltintrn.h.txt.full.json` (799 bytes)
- `binary_data/types/cat_search.h.txt` (42 bytes)
- `binary_data/types/cat_basetsd.h.txt` (387 bytes)
- `binary_data/types/cat_mmsystem.h.txt` (1,345 bytes)
- `binary_data/types/cat_PE.txt` (5,544 bytes)
- `binary_data/types/cat_stdlib.h.txt` (387 bytes)
- `binary_data/types/cat_wingdi.h.txt` (610 bytes)
- `binary_data/types/all_data_types.txt` (236 bytes)
- `binary_data/types/cat_winbase.h.txt.full.json` (3,169 bytes)
- `binary_data/types/cat_vadefs.h.txt.full.json` (421 bytes)
- `binary_data/types/cat_ehdata.h.txt` (56 bytes)
- `binary_data/types/cat_winnls.h.txt.full.json` (623 bytes)
- `binary_data/types/cat_winnls.h.txt` (200 bytes)
- `binary_data/types/cat_DOS.txt` (58 bytes)
- `binary_data/types/cat_crtdefs.h.txt.full.json` (2,833 bytes)
- `binary_data/types/cat_imm.h.txt.full.json` (465 bytes)
- `binary_data/types/cat_search.h.txt.full.json` (301 bytes)
- `binary_data/types/cat_mbstring.h.txt` (150 bytes)
- `binary_data/types/cat_wtypes.h.txt.full.json` (305 bytes)
- _(e mais 30 arquivos)_

## 📜 Documentos

- [`PLANO.md`](PLANO.md)
- [`PROGRESSO.md`](PROGRESSO.md)
- [`RELATORIO_COMPLETO.md`](RELATORIO_COMPLETO.md)

---

Última atualização: via GitHub Actions
