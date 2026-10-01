xof 0303txt 0032

// Minimal daybreak test .x — a single quad (no skinning, no anim).
// Used to validate the loader pipeline without a real asset.

Material Material_0 {
    1.0; 0.4; 0.4; 1.0;;
    0.0;
    0.0; 0.0; 0.0;;
    0.0; 0.0; 0.0;;
}

Mesh Mesh_0 {
    4;
    -1.0; -1.0; 0.0;,
    1.0; -1.0; 0.0;,
    1.0;  1.0; 0.0;,
    -1.0;  1.0; 0.0;;
    2;
    3; 0, 1, 2;,
    3; 0, 2, 3;;

    MeshMaterialList {
        1;
        2;
        0,
        0;;
        { Material_0 }
    }
}
