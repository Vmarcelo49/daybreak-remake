"""Reuse tools/asset-tools/gmo_blender.py outside Blender.

gmo_blender.py imports bpy/mathutils at module level but its GMO/GIM/TGA parsing
functions are pure Python. This shim installs stand-ins for those modules and
re-exports the parsing entry points, so the study exercises the repository's own
parser rather than a second, divergent one.
"""
import importlib.util
import os
import sys
import types

REPO = "/home/marcelo/Projects/daybreak-remake"
TOOL = os.path.join(REPO, "tools", "asset-tools", "gmo_blender.py")


class _Any:
    def __init__(self, *a, **k):
        pass

    def __getattr__(self, name):
        return _Any()

    def __call__(self, *a, **k):
        return _Any()

    def __iter__(self):
        return iter(())

    def __mul__(self, other):
        return _Any()

    __rmul__ = __mul__


def _install_stubs():
    bpy = types.ModuleType("bpy")
    bpy.ops = _Any()
    bpy.data = _Any()
    bpy.context = _Any()
    bpy.types = types.SimpleNamespace(Operator=_Any)
    sys.modules.setdefault("bpy", bpy)

    mu = types.ModuleType("mathutils")
    mu.Matrix = _Any
    mu.Quaternion = _Any
    mu.Vector = _Any
    sys.modules.setdefault("mathutils", mu)


def load():
    _install_stubs()
    spec = importlib.util.spec_from_file_location("gmo_blender_shim", TOOL)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


MOD = load()
parse_gmo = MOD.parse_gmo
decode_gim = MOD.decode_gim
decode_tga = MOD.decode_tga
walk = MOD.walk
vertex_layout = MOD.vertex_layout
chunk_name = MOD.chunk_name
HEAD_PICTURES = MOD.HEAD_PICTURES
