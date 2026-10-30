# Spec: Substituição do FFmpeg pelo pl_mpeg no VideoPlayer

**Data:** 2026-07-15
**Status:** Aprovado (pending implementation plan)
**Biblioteca:** [phoboslab/pl_mpeg](https://github.com/phoboslab/pl_mpeg) — single-file C, MIT license

## Motivação

A implementação atual de vídeo (`src/render/video_player.{h,cpp}`) usa FFmpeg
(libavformat/libavcodec/swscale/swresample) e tem dois problemas:

1. **Custo de dependência pesado.** FFmpeg traz ~5 DLLs compartilhadas
   (~30 MB) copiadas para o diretório do `.exe`, além de headers e import
   libs baixados pelo `scripts/fetch_deps.sh` (seção 7) e vinculados no
   `CMakeLists.txt` (linhas 152-208).

2. **A/V sync frágil.** O `VideoPlayer::start()` contém um workaround
   complicado para impedir que o thread de áudio roube pacotes de vídeo do
   decoder: ele lê até 500 packets em loop, envia só os de áudio para o
   decoder de áudio, depois faz `av_seek_frame(..., 0, BACKWARD)` +
   `avcodec_flush_buffers(m_videoCtx)` para rebobinar o vídeo. Esse hack
   é fonte de bugs sutis de sincronização.

O pl_mpeg decodifica nativamente MPEG1 Video + MP2 Audio + demuxer MPEG-PS
— exatamente o que um arquivo `.mpg` dessa era é — numa biblioteca C
single-file sem dependências, e oferece `plm_decode(plm, dt)` que cuida do
A/V sync automaticamente via callbacks.

## Escopo

**DENTRO:**
- Reescrever `VideoPlayer` sobre pl_mpeg.
- Vendorizar `pl_mpeg.h` no repositório.
- Remover **completamente** o FFmpeg (CMake, fetch_deps, post-build copy).
- Manter a interface pública de `VideoPlayer` idêntica (nenhuma mudança em
  `Scene_Opening`).

**FORA:**
- Carregar o `.mpg` direto da memória (`plm_create_with_memory`) em vez do
  arquivo temp — fica como melhoria futura para reduzir o escopo deste diff.
- Decodificar formatos que não sejam MPEG1/MP2/MPEG-PS.
- Adicionar testes que reproduzam vídeo (dependem do bundle real e device DX9).

## Premissa a validar em runtime

O `op.mpg` (e quaisquer outros vídeos do jogo) **não pôde ser inspecionado**
diretamente: ele vive dentro do bundle `.DAT` proprietário do jogo original,
que não está no repositório. Há fortes evidências de que seja MPEG1/MP2 em
MPEG-PS:

1. É **Higurashi Daybreak** (~2006, jogo JP); FMVs em MPEG1/MPEG-PS era o
   padrão da época no Windows JP.
2. O arquivo chama-se `op.mpg` (não `.mp4`/`.avi`).
3. O código FFmpeg atual já decodifica áudio **MP2** (estéreo, 44100 Hz),
   não AAC — o codec de áudio nativo do MPEG-PS.
4. O pl_mpeg decodifica exatamente o trio MPEG1+MP2+MPEG-PS.

**Validação:** o primeiro passo do plano de implementação é um teste de
sanidade — logar `plm_get_width()`, `plm_get_height()`,
`plm_get_framerate()` após `plm_create_with_filename` no `op.mpg` real, para
confirmar a premissa antes de refinar o restante.

Se o vídeo não for MPEG1/MP2, o pl_mpeg não serve e o plano precisa ser
revisto (voltar ao brainstorming).

## Arquitetura

```
┌─────────────────────────────────────────────────────────┐
│ Scene_Opening (scenes.cpp) — NÃO MUDA                   │
│   open(path) → start(device) → update(dt) → render(dev) │
│   is_finished() / skip-on-input                         │
└──────────────────────┬──────────────────────────────────┘
                       │ mesma interface pública
┌──────────────────────▼──────────────────────────────────┐
│ VideoPlayer (video_player.h/.cpp) — REESCRITO           │
│                                                         │
│   plm_t* m_plm  ◄── plm_create_with_filename(path)      │
│   plm_set_video_decode_callback() ─┐                    │
│   plm_set_audio_decode_callback() ─┤                    │
│                                     │                    │
│   update(dt): plm_decode(m_plm, dt) ◄── sync automático │
│                                     │                    │
│   ┌─────────────────────────────────┴──────────────┐    │
│   │ video_cb(plm, frame, user):                    │    │
│   │   plm_frame_to_bgra(frame, m_bgra, stride)     │    │
│   │   → LockRect texture + memcpy linha-a-linha    │    │
│   │   m_textureDirty = true                        │    │
│   ├─────────────────────────────────────────────────┤    │
│   │ audio_cb(plm, samples, user):                  │    │
│   │   float[-1,1] → S16 stereo                     │    │
│   │   → push p/ m_audioChunks (mutex existente)    │    │
│   └─────────────────────────────────────────────────┘    │
│                                                         │
│   Mix_HookMusic(audio_callback) — DRAIN fila (igual hoje)│
└─────────────────────────────────────────────────────────┘
```

### Abordagem selecionada

**`plm_decode()` de alto nível com callbacks** (a "usage mode 1" do README
do pl_mpeg). Chamamos `plm_decode(plm, dt)` em `update(dt)` passando o
delta time desde a última chamada; a biblioteca demuxa, decodifica e invoca
os callbacks na cadência certa, fazendo o A/V sync internamente.

Abordagens descartadas:
- **Decode manual** (`plm_decode_video`/`plm_decode_audio` um frame por vez
  com pacing manual): reintroduz exatamente a complexidade de sync que se
  quer eliminar.
- **Carga via memória** (`plm_create_with_memory`) eliminando o arquivo
  temp: alargaria o escopo mudando o contrato do `AssetManager`. Fica como
  melhoria futura.

## Interface pública (preservada)

A interface pública de `VideoPlayer` é mantida idêntica, de modo que
`Scene_Opening` e qualquer outro consumidor não precisem mudar:

```cpp
bool open(const std::string& path);
bool start(IDirect3DDevice9* device);
void update(double dt);
void render(IDirect3DDevice9* device);
void stop();
void close();

bool is_open()     const;
bool is_playing()  const;
bool is_finished() const;
int  width()       const;
int  height()      const;
double duration()      const;
double current_time()  const;
double video_fps()     const;
```

## Componentes e responsabilidades

| Componente | Responsabilidade | Mudança |
|---|---|---|
| `src/third_party/pl_mpeg.h` (novo) | Biblioteca single-file | Vendored no repositório. |
| `src/render/video_player.h` | Declara interface pública | Remove forward-decls FFmpeg; expõe apenas `plm_t*` opaco (forward decl). Membros FFmpeg → `plm_t* m_plm` + `std::vector<uint8_t> m_bgra`. Adiciona métodos estáticos `video_decode_callback`/`audio_decode_callback`. |
| `src/render/video_player.cpp` | Decodificação + upload textura + áudio | Reescrito sobre pl_mpeg. `update(dt)` reduz-se a `plm_decode()`. Elimina o hack de preload+seek+flush. |
| `CMakeLists.txt` | Build | Remove bloco FFmpeg (L152-166), links (L160-161) e copy de DLLs (L196-208). pl_mpeg é header-only compilado junto do `video_player.cpp` (define `PLM_IMPLEMENTATION` num único TU). |
| `scripts/fetch_deps.sh` | Bootstrap deps | Remove a seção 7 (download do FFmpeg). |
| `src/core/scenes.{h,cpp}` | Consumidor | **Sem mudança de código.** (Comentário opcional no header deixando de citar FFmpeg.) |

## Decisões técnicas

### Vídeo — conversão de cor

`plm_frame_to_bgra()` escreve BGRA que casa 1:1 com o formato de textura
`D3DFMT_A8R8G8B8`. Observação do header do pl_mpeg (L745): "the alpha
component of the dest buffer is always left untouched". Logo:

- Alocar `m_bgra` com `width * height * 4` bytes, **inicializado com
  alpha=255 em todos os pixels** (preencher o byte A uma vez na alocação).
- A cada frame, `plm_frame_to_bgra()` sobrescreve só os bytes B/G/R; o byte
  A permanece 255 entre frames. Assim o upload para a textura é um único
  `memcpy` por linha sobre `D3DLOCKED_RECT`, sem tocar alpha.

Isso elimina o loop pixel-a-pixel RGB→BGR manual de hoje
(`video_player.cpp` L398-407), que troca R e B à mão e é lento.

### Áudio — formato e roteamento

- O callback de áudio recebe `plm_samples_t` com `interleaved[1152*2]`
  float normalizado [-1, 1], estéreo.
- Conversão para S16: `sample_clamped = (int16_t)(s * 32767.0f)` com clamp
  para [-32768, 32767].
- Resultado empurrado para a fila existente `m_audioChunks` (vetor de bytes
  S16 stereo) sob o `m_audioMutex`.
- `Mix_HookMusic` + `audio_callback` (drain da fila) **permanecem
  idênticos** ao de hoje — só a fonte dos samples muda.

### A/V sync

`plm_decode(plm, dt)` é o ponto único de decodificação. Substitui, no
`update()`:
- o loop `while (m_displayTime >= m_frameDuration)`,
- o `decode_next_frame()`,
- o `feed_audio()`,
- o preload de 500 packets,
- o `av_seek_frame` + `avcodec_flush_buffers`.

`m_currentTime` passa a ser atualizado a partir de `frame->time` no callback
de vídeo.

### Finalização

`plm_has_ended()` substitui a detecção manual de EOS → seta `m_finished`.
`plm_destroy()` substitui toda a faxina FFmpeg (`swr_free`, `sws_freeContext`,
`av_frame_free` ×3, `avcodec_free_context` ×2, `avformat_close_input`).

## Tratamento de erros

- `plm_create_with_filename(path)` retorna `NULL` → `open()` retorna
  `false`. `Scene_Opening` já trata esse caso caindo para `Scene_Title`.
- Frames decodificados mas com dimensões inesperadas: loga e segue.
- Não há mudança no contrato de erro vs. implementação atual.

## Testes

- Não há testes unitários de vídeo hoje (`tests/` não cobre `video_player`).
- Não serão adicionados testes que reproduzam vídeo (dependem do bundle
  real e de um device DX9).
- **Gate de build:** compilar com sucesso via MinGW cross-compile
  (`./build.sh`) é o gate automatizado. O `video_player.cpp` deve compilar
  limpo sob `-Wall -Wextra -Wpedantic` em C++23, como o restante do projeto.
- **Validação funcional:** manual, em runtime no Windows com o bundle real.

## Arquivos afetados

- **Novo:** `src/third_party/pl_mpeg.h`
- **Reescrito:** `src/render/video_player.h`, `src/render/video_player.cpp`
- **Editado:** `CMakeLists.txt`, `scripts/fetch_deps.sh`
- **Inalterado (código):** `src/core/scenes.h`, `src/core/scenes.cpp`
