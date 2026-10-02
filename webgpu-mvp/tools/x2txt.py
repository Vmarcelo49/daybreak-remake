#!/usr/bin/env python3
"""
x2txt.py — DirectX .x reference converter (text | binary | MSZIP-compressed).

Reference implementation of the binary token stream that xmodel.h ports to C++.
Useful on its own for inspecting the shipped assets:

    python3 tools/x2txt.py data/rika/01.X out.x     # convert
    python3 tools/x2txt.py --stats data/rika/01.X   # template census
    python3 tools/x2txt.py --probe data/rika/01.X Material
    python3 tools/x2txt.py --quat data/rika/01.X    # quaternion convention check

Format notes (verified against the shipped game assets):
  * Token stream is 16-bit tokens, not the 32-bit ones the MSDN text implies.
  * Magic "xof 0303bin 0032" / "xof 0303bzip0032"; float size 0032 or 0064.
  * bzip payload = 4-byte decompressed size (incl. the 16-byte header),
    4-byte checksum, then MSZIP blocks: "CK" + raw DEFLATE, 32 KB window each.
  * Declared template members are *flattened* into INTEGER_LIST / REALNUM_LIST
    runs (no braces); only undeclared children and { refs } are real objects.
"""

import struct
import sys
import zlib

# ---- tokens ---------------------------------------------------------------
T_NAME, T_STRING, T_INTEGER = 1, 2, 3
T_GUID, T_INTLIST, T_FLOATLIST = 5, 6, 7
T_OBRACE, T_CBRACE, T_OPAREN, T_CPAREN = 10, 11, 12, 13
T_OBRACKET, T_CBRACKET, T_OANGLE, T_CANGLE = 14, 15, 16, 17
T_DOT, T_COMMA, T_SEMI, T_TEMPLATE = 18, 19, 20, 31
T_WORD, T_DWORD, T_FLOAT, T_DOUBLE = 40, 41, 42, 43
T_CHAR, T_UCHAR, T_SWORD, T_SDWORD = 44, 45, 46, 47
T_VOID, T_LPSTR, T_UNICODE, T_CSTRING, T_ARRAY = 48, 49, 50, 51, 52

PRIM = {T_WORD, T_DWORD, T_FLOAT, T_DOUBLE, T_CHAR, T_UCHAR,
        T_SWORD, T_SDWORD, T_VOID, T_LPSTR, T_UNICODE, T_CSTRING}

PRIM_NAME = {T_WORD: 'WORD', T_DWORD: 'DWORD', T_FLOAT: 'FLOAT', T_DOUBLE: 'DOUBLE',
             T_CHAR: 'CHAR', T_UCHAR: 'UCHAR', T_SWORD: 'SWORD', T_SDWORD: 'SDWORD',
             T_VOID: 'VOID', T_LPSTR: 'STRING', T_UNICODE: 'UNICODE',
             T_CSTRING: 'CSTRING'}
NAME_PRIM = {v: k for k, v in PRIM_NAME.items()}

INT_TYPES = {T_WORD, T_DWORD, T_CHAR, T_UCHAR, T_SWORD, T_SDWORD, T_INTEGER}
FLOAT_TYPES = {T_FLOAT, T_DOUBLE}
STRING_TYPES = {T_LPSTR, T_UNICODE, T_CSTRING}


class XError(Exception):
    pass


# ---- MSZIP ---------------------------------------------------------------
def decompress_mszip(payload):
    """payload = bytes after the 16-byte .x header of a 'bzip' file.

    Verified framing (all 223 shipped bzip assets):

        "xof 0303bzip0032"            16 bytes
        u32 total_uncompressed_size   (includes the 16-byte header)
        per block:
            u16 block_out_size
            u16 block_comp_size       (includes the 2-byte 'CK')
            "CK"
            raw DEFLATE stream, using the previous 32 KB of output as its
            LZ77 preset dictionary (cross-block back-references are real;
            decoding each block standalone fails with "distance too far back")

    Because the dictionary is just the preceding output, decoding every block
    into one continuous buffer makes the back-references resolve on their own.
    """
    if len(payload) < 4:
        raise XError('bzip payload too short')
    total, = struct.unpack_from('<I', payload, 0)
    want = total - 16
    out = bytearray()
    pos = 4
    nblk = 0
    while len(out) < want:
        if pos + 4 > len(payload):
            raise XError('bzip: truncated block header at %d' % pos)
        blk_out, blk_comp = struct.unpack_from('<HH', payload, pos)
        pos += 4
        if payload[pos:pos + 2] != b'CK':
            raise XError('bzip: missing CK signature at %d' % pos)
        pos += 2
        d = zlib.decompressobj(-15, zdict=bytes(out[-32768:]))
        chunk = d.decompress(payload[pos:])
        if not d.eof:
            raise XError('bzip: truncated deflate block %d' % nblk)
        used = len(payload) - pos - len(d.unused_data)
        if used <= 0 or used + 2 != blk_comp:
            raise XError('bzip: block %d size %d, header says %d'
                         % (nblk, used + 2, blk_comp))
        if len(chunk) != blk_out:
            raise XError('bzip: block %d produced %d bytes, header says %d'
                         % (nblk, len(chunk), blk_out))
        out += chunk
        pos += used
        nblk += 1
    if len(out) != want:
        raise XError('bzip: decoded %d bytes, header says %d' % (len(out), want))
    return bytes(out)


def load_any(path):
    """Returns (data, start, float64, kind); start skips the .x header if present."""
    raw = open(path, 'rb').read()
    if len(raw) < 16 or raw[:4] != b'xof ':
        raise XError('not a .x file')
    kind = raw[8:12].decode('ascii', 'replace').strip()
    float64 = raw[12:16] == b'0064'
    if kind == 'bzip':
        # Decompressed payload is the token stream only, all offsets are 0-based.
        return decompress_mszip(raw[16:]), 0, float64, 'bin'
    if kind not in ('txt', 'bin'):
        raise XError('unsupported encoding %r' % kind)
    return raw, 16, float64, kind


# ---- binary token reader -------------------------------------------------
class Reader:
    def __init__(self, data, start=16, float64=False):
        self.b = data
        self.p = start
        self.start = start
        self.float64 = float64

    def u8(self):
        v = self.b[self.p]
        self.p += 1
        return v

    def u16(self):
        v, = struct.unpack_from('<H', self.b, self.p)
        self.p += 2
        return v

    def u32(self):
        v, = struct.unpack_from('<I', self.b, self.p)
        self.p += 4
        return v

    def raw(self, n):
        v = self.b[self.p:self.p + n]
        if len(v) != n:
            raise XError('truncated stream')
        self.p += n
        return v

    def name(self):
        t = self.u16()
        if t != T_NAME:
            raise XError('expected NAME token, got %d at %d' % (t, self.p - 2))
        return self.raw(self.u32())

    def name_after_token(self):
        """Length + bytes when the NAME token itself was already consumed."""
        return self.raw(self.u32())

    def string(self):
        t = self.u16()
        if t != T_STRING:
            raise XError('expected STRING token, got %d at %d' % (t, self.p - 2))
        s = self.raw(self.u32())
        term = self.u16()
        if term not in (T_COMMA, T_SEMI):
            raise XError('bad string terminator %d' % term)
        return s


class Member:
    """kind: 'prim' | 'array' | 'ref'"""

    def __init__(self, kind, type_token, type_name, name, dims):
        self.kind = kind
        self.type_token = type_token      # prim token, or None for ref
        self.type_name = type_name        # template name for refs
        self.name = name
        self.dims = dims                  # list of int or str (member name)

    def is_float(self):
        return self.type_token in FLOAT_TYPES


class TemplateDef:
    def __init__(self, name, guid):
        self.name = name
        self.guid = guid
        self.members = []


def parse_member(r, t):
    if t == T_ARRAY:
        et = r.u16()
        if et in PRIM:
            tname, ttoken = PRIM_NAME[et], et
        elif et == T_NAME:
            # ARRAY token consumed above; the element type NAME token was not
            tname, ttoken = r.name().decode('cp932', 'replace'), None
        else:
            raise XError('bad array element type %d' % et)
        name = r.name().decode('cp932', 'replace')
        dims = []
        while True:
            u = r.u16()
            if u == T_SEMI:
                break
            if u != T_OBRACKET:
                raise XError('bad dim token %d' % u)
            d = r.u16()
            if d == T_INTEGER:
                dims.append(r.u32())
            elif d == T_NAME:
                dims.append(r.name_after_token().decode('cp932', 'replace'))
            else:
                raise XError('bad dimension token %d' % d)
            if r.u16() != T_CBRACKET:
                raise XError('expected CBRACKET')
        return Member('array', ttoken, tname, name, dims)

    if t in PRIM:
        name = ''
        save = r.p
        u = r.u16()
        if u == T_NAME:
            name = r.name_after_token().decode('cp932', 'replace')
        else:
            r.p = save
        if r.u16() != T_SEMI:
            raise XError('expected SEMICOLON after primitive member')
        return Member('prim', t, PRIM_NAME[t], name, [])

    if t == T_NAME:
        # the NAME token was already consumed by the caller
        tname = r.name_after_token().decode('cp932', 'replace')
        name = ''
        save = r.p
        u = r.u16()
        if u == T_NAME:
            name = r.name_after_token().decode('cp932', 'replace')
        else:
            r.p = save
        if r.u16() != T_SEMI:
            raise XError('expected SEMICOLON after template member')
        return Member('ref', None, tname, name, [])

    raise XError('bad member token %d' % t)


def parse_template(r):
    if r.u16() != T_TEMPLATE:
        raise XError('expected TEMPLATE')
    name = r.name().decode('cp932', 'replace')
    if r.u16() != T_OBRACE:
        raise XError('expected OBRACE in template')
    if r.u16() != T_GUID:
        raise XError('expected GUID in template')
    guid = r.raw(16)
    td = TemplateDef(name, guid)
    while True:
        t = r.u16()
        if t == T_CBRACE:
            break
        if t == T_OBRACKET:          # [ ... ] open/restricted info
            depth = 1
            while depth:
                u = r.u16()
                if u == T_OBRACKET:
                    depth += 1
                elif u == T_CBRACKET:
                    depth -= 1
            continue
        td.members.append(parse_member(r, t))
    return td


# ---- builtin standard templates -----------------------------------------
# D3DX's binary writer omits the definitions of the standard templates (the
# reader is expected to pre-register them), so they must be supplied here.
def _prim(tok, name=''):
    return Member('prim', tok, PRIM_NAME[tok], name, [])


def _arr(tok, tname, name, dims):
    return Member('array', tok, tname, name, dims)


def _ref(tname, name):
    return Member('ref', None, tname, name, [])


def _tpl(name, *members):
    td = TemplateDef(name, b'')
    td.members = list(members)
    return td


STANDARD_TEMPLATES = {t.name: t for t in [
    _tpl('Header', _prim(T_WORD, 'major'), _prim(T_WORD, 'minor'), _prim(T_DWORD, 'flags')),
    _tpl('Vector', _prim(T_FLOAT, 'x'), _prim(T_FLOAT, 'y'), _prim(T_FLOAT, 'z')),
    _tpl('Coords2d', _prim(T_FLOAT, 'u'), _prim(T_FLOAT, 'v')),
    _tpl('Quaternion', _prim(T_FLOAT, 's'), _ref('Vector', 'v')),
    _tpl('Matrix4x4', _arr(T_FLOAT, 'FLOAT', 'matrix', [16])),
    _tpl('ColorRGBA', _prim(T_FLOAT, 'red'), _prim(T_FLOAT, 'green'),
         _prim(T_FLOAT, 'blue'), _prim(T_FLOAT, 'alpha')),
    _tpl('ColorRGB', _prim(T_FLOAT, 'red'), _prim(T_FLOAT, 'green'), _prim(T_FLOAT, 'blue')),
    _tpl('IndexedColor', _prim(T_DWORD, 'index'), _ref('ColorRGBA', 'indexColor')),
    _tpl('Boolean', _prim(T_WORD, 'truefalse')),
    _tpl('Boolean2d', _ref('Boolean', 'u'), _ref('Boolean', 'v')),
    _tpl('Material', _ref('ColorRGBA', 'faceColor'), _prim(T_FLOAT, 'power'),
         _ref('ColorRGB', 'specularColor'), _ref('ColorRGB', 'emissiveColor')),
    _tpl('TextureFilename', _prim(T_LPSTR, 'filename')),
    _tpl('MeshFace', _prim(T_DWORD, 'nFaceVertexIndices'),
         _arr(T_DWORD, 'DWORD', 'faceVertexIndices', ['nFaceVertexIndices'])),
    _tpl('MeshFaceWraps', _prim(T_DWORD, 'nFaceWrapValues'),
         _arr(None, 'Boolean2d', 'faceWrapValues', ['nFaceWrapValues'])),
    _tpl('MeshTextureCoords', _prim(T_DWORD, 'nTextureCoords'),
         _arr(None, 'Coords2d', 'textureCoords', ['nTextureCoords'])),
    _tpl('MeshNormals', _prim(T_DWORD, 'nNormals'),
         _arr(None, 'Vector', 'normals', ['nNormals']),
         _prim(T_DWORD, 'nFaceNormals'),
         _arr(None, 'MeshFace', 'faceNormals', ['nFaceNormals'])),
    _tpl('MeshVertexColors', _prim(T_DWORD, 'nVertexColors'),
         _arr(None, 'IndexedColor', 'vertexColors', ['nVertexColors'])),
    _tpl('MeshMaterialList', _prim(T_DWORD, 'nMaterials'), _prim(T_DWORD, 'nFaceIndexes'),
         _arr(T_DWORD, 'DWORD', 'faceIndexes', ['nFaceIndexes'])),
    _tpl('Mesh', _prim(T_DWORD, 'nVertices'), _arr(None, 'Vector', 'vertices', ['nVertices']),
         _prim(T_DWORD, 'nFaces'), _arr(None, 'MeshFace', 'faces', ['nFaces'])),
    _tpl('FrameTransformMatrix', _ref('Matrix4x4', 'frameMatrix')),
    _tpl('Frame'),
    _tpl('AnimTicksPerSecond', _prim(T_DWORD, 'AnimTicksPerSecond')),
    _tpl('AnimationKey', _prim(T_DWORD, 'keyType'), _prim(T_DWORD, 'nKeys'),
         _arr(None, 'TimedFloatKeys', 'keys', ['nKeys'])),
    _tpl('AnimationOptions', _prim(T_DWORD, 'openclosed'), _prim(T_DWORD, 'positionquality')),
    _tpl('Animation'),
    _tpl('AnimationSet'),
    _tpl('FloatKeys', _prim(T_DWORD, 'nValues'), _arr(T_FLOAT, 'FLOAT', 'values', ['nValues'])),
    _tpl('TimedFloatKeys', _prim(T_DWORD, 'time'), _ref('FloatKeys', 'tfkeys')),
    _tpl('VertexElement', _prim(T_DWORD, 'Type'), _prim(T_DWORD, 'Method'),
         _prim(T_DWORD, 'Usage'), _prim(T_DWORD, 'UsageIndex')),
    _tpl('DeclData', _prim(T_DWORD, 'nElements'),
         _arr(None, 'VertexElement', 'Elements', ['nElements']),
         _prim(T_DWORD, 'nDWords'), _arr(T_DWORD, 'DWORD', 'data', ['nDWords'])),
    _tpl('XSkinMeshHeader', _prim(T_WORD, 'nMaxSkinWeightsPerVertex'),
         _prim(T_WORD, 'nMaxSkinWeightsPerFace'), _prim(T_WORD, 'nBones')),
    _tpl('VertexDuplicationIndices', _prim(T_DWORD, 'nIndices'),
         _prim(T_DWORD, 'nOriginalVertices'),
         _arr(T_DWORD, 'DWORD', 'indices', ['nIndices'])),
    _tpl('SkinWeights', _prim(T_LPSTR, 'transformNodeName'), _prim(T_DWORD, 'nWeights'),
         _arr(T_DWORD, 'DWORD', 'vertexIndices', ['nWeights']),
         _arr(T_FLOAT, 'FLOAT', 'weights', ['nWeights']),
         _ref('Matrix4x4', 'matrixOffset')),
]}


class Cursor:
    """Number stream: pulls from INTEGER_LIST / REALNUM_LIST runs."""

    def __init__(self, r):
        self.r = r
        self.items = None
        self.is_float = False
        self.i = 0

    def _refill(self, want_float):
        if self.items is not None and self.i < len(self.items):
            raise XError('list kind mismatch: wanted %s, %d values left'
                         % ('float' if want_float else 'int', len(self.items) - self.i))
        t = self.r.u16()
        if t not in (T_INTLIST, T_FLOATLIST):
            raise XError('expected number list, got token %d at %d' % (t, self.r.p - 2))
        n = self.r.u32()
        if t == T_FLOATLIST:
            if self.r.float64:
                self.items = list(struct.unpack_from('<%dd' % n, self.r.b, self.r.p))
                self.r.p += 8 * n
            else:
                self.items = list(struct.unpack_from('<%df' % n, self.r.b, self.r.p))
                self.r.p += 4 * n
            self.is_float = True
        else:
            self.items = list(struct.unpack_from('<%di' % n, self.r.b, self.r.p))
            self.r.p += 4 * n
            self.is_float = False
        self.i = 0

    def num(self, want_float):
        if self.items is None or self.i >= len(self.items) or self.is_float != want_float:
            self._refill(want_float)
        v = self.items[self.i]
        self.i += 1
        return v

    def drained(self):
        return self.items is None or self.i >= len(self.items)


# ---- binary -> text ------------------------------------------------------
def fmt_float(v):
    return '%.9g' % v


class Converter:
    def __init__(self, data, start=16, float64=False, drop_templates=True):
        self.r = Reader(data, start, float64)
        self.cur = Cursor(self.r)
        self.templates = dict(STANDARD_TEMPLATES)
        self.out = bytearray()
        self.depth = 0
        self.stats = {}
        self.keep_names = {'Frame', 'Mesh', 'Material', 'AnimationSet', 'Animation'}
        self.drop_templates = drop_templates

    # -- output helpers
    def w(self, s):
        self.out += s if isinstance(s, bytes) else s.encode('ascii')

    def nl(self):
        self.out += b'\n' + b'  ' * self.depth

    # -- main
    def run(self):
        data = self.r.b
        self.r.p = self.r.start
        while self.r.p < len(data):
            save = self.r.p
            t = self.r.u16()
            self.r.p = save
            if t == T_TEMPLATE:
                td = parse_template(self.r)
                self.templates[td.name] = td
                if not self.drop_templates:
                    self.emit_template(td)
            elif t == T_NAME or t in PRIM:
                self.object_()
                self.nl()
            else:
                raise XError('unexpected top-level token %d at %d' % (t, save))
        return bytes(self.out)

    def emit_template(self, td):
        self.w('template %s {\n' % td.name)
        for m in td.members:
            self.w('  // %s\n' % self.member_sig(m))
        self.w('}\n')

    @staticmethod
    def member_sig(m):
        if m.kind == 'array':
            return 'array %s %s%s;' % (m.type_name, m.name,
                                       ''.join('[%s]' % d for d in m.dims))
        return '%s %s;' % (m.type_name, m.name)

    # -- objects
    def object_(self):
        t = self.r.u16()
        if t == T_NAME:
            tpl = self.r.name_after_token().decode('cp932', 'replace')
        elif t in PRIM:
            tpl = PRIM_NAME[t]
        else:
            raise XError('bad object identifier token %d' % t)
        inst = None
        save = self.r.p
        if self.r.u16() == T_NAME:
            inst = self.r.name_after_token()
        else:
            self.r.p = save
        if self.r.u16() != T_OBRACE:
            raise XError('expected OBRACE for %s' % tpl)
        save = self.r.p
        if self.r.u16() == T_GUID:
            self.r.raw(16)
        else:
            self.r.p = save

        self.stats[tpl] = self.stats.get(tpl, 0) + 1

        name = inst.decode('cp932', 'replace') if inst else ''
        self.w(tpl.encode('ascii'))
        if inst and tpl in self.keep_names:
            self.w(b' ')
            self.emit_name(inst)
        self.w(' {')
        self.depth += 1

        scopes = [{}]
        td = self.templates.get(tpl)
        if td is None:
            raise XError('object of unknown template %s' % tpl)
        for m in td.members:
            self.nl()
            self.read_member(m, scopes, td.members)

        self.read_children(scopes)

        self.depth -= 1
        self.nl()
        self.w('}')

    def read_children(self, scopes):
        """Undeclared children / { refs } after the declared members."""
        while True:
            save = self.r.p
            t = self.r.u16()
            if t == T_CBRACE:
                return
            if t == T_OBRACE:                      # data reference
                if self.r.u16() != T_NAME:
                    raise XError('bad reference')
                ref = self.r.name_after_token()
                save2 = self.r.p
                if self.r.u16() == T_GUID:
                    self.r.raw(16)
                else:
                    self.r.p = save2
                if self.r.u16() != T_CBRACE:
                    raise XError('bad reference end')
                self.nl()
                self.w(b'{ ')
                self.emit_name(ref)
                self.w(b' }')
                continue
            self.r.p = save
            # nested object: separator before it
            self.nl()
            self.object_()

    # -- member values (flattened into the number lists)
    def read_member(self, m, scopes, members):
        if m.kind == 'prim':
            if m.type_token in STRING_TYPES:
                # Strings are their own token, never inside a number list.
                if not self.cur.drained():
                    raise XError('string member %s: pending numbers' % m.name)
                v = self.r.string()
                self.emit_string(v)
                self.w(';')
                return
            v = self.cur.num(m.is_float())
            if m.name:
                scopes[-1][m.name] = v
            self.emit_value(v, m.is_float())
            self.w(';')
            return
        if m.kind == 'array':
            n = self.resolve_count(m, scopes)
            for i in range(n):
                if i:
                    self.w(',')
                self.read_element(m, scopes, members)
            self.w(';')
            return
        # ref: recurse into the referenced template's members
        self.read_ref(m.type_name, scopes, members)

    def read_ref(self, type_name, scopes, members):
        td = self.templates.get(type_name)
        if td is None:
            raise XError('unknown member template %s' % type_name)
        scopes.append({})
        for m in td.members:
            self.read_member(m, scopes, td.members)
        scopes.pop()

    def read_element(self, m, scopes, members):
        if m.type_token is not None:
            v = self.cur.num(m.is_float())
            self.emit_value(v, m.is_float())
            return
        td = self.templates.get(m.type_name)
        if td is None:
            raise XError('unknown array element template %s' % m.type_name)
        scopes.append({})
        for mm in td.members:
            self.read_member(mm, scopes, td.members)
        scopes.pop()

    def resolve_count(self, m, scopes):
        n = 1
        for d in m.dims:
            if isinstance(d, int):
                n *= d
            else:
                for sc in reversed(scopes):
                    if d in sc:
                        n *= int(sc[d])
                        break
                else:
                    raise XError('unresolved dimension %s for %s' % (d, m.name))
        return n

    @staticmethod
    def name_needs_quotes(s):
        if not s:
            return True
        return any(c in b' \t\r\n;,{}"' or c >= 0x80 for c in s)

    def emit_name(self, raw):
        if self.name_needs_quotes(raw):
            self.emit_string(raw)
        else:
            self.w(raw)

    def emit_string(self, raw):
        # Quoted: CP932 trail bytes can collide with '{' / '}' / ';'.
        if b'\x00' in raw:
            raw = raw.split(b'\x00')[0]
        self.w(b'"' + raw.replace(b'\\', b'\\\\').replace(b'"', b'\\"') + b'"')

    def emit_value(self, v, is_float):
        if is_float:
            self.w(fmt_float(v))
        else:
            self.w(str(int(v)))


def convert(path, dump_templates=False):
    data, start, float64, kind = load_any(path)
    if kind == 'txt':
        return data, {}
    c = Converter(data, start, float64, drop_templates=not dump_templates)
    text = c.run()
    return text, c.stats


# ---- CLI -----------------------------------------------------------------
def main(argv):
    if len(argv) < 2:
        print(__doc__)
        return 1
    args = argv[1:]
    dump = '--dump-templates' in args
    args = [a for a in args if not a.startswith('--') or a == '--dump-templates']
    path = args[0]

    if '--stats' in argv:
        _, stats = convert(path)
        for k, v in sorted(stats.items(), key=lambda kv: -kv[1]):
            print('%8d  %s' % (v, k))
        return 0

    text, stats = convert(path, dump_templates=dump)
    if len(args) > 1:
        open(args[1], 'wb').write(text)
        print('wrote %s (%d bytes)' % (args[1], len(text)), file=sys.stderr)
    else:
        sys.stdout.buffer.write(text)
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main(sys.argv))
    except XError as e:
        print('ERROR: %s' % e, file=sys.stderr)
        sys.exit(2)
