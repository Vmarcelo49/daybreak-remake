xof 0303txt 0032

// daybreak test .x — small animated cube.
//
// Validates:
//   - Frame hierarchy (root + 1 child mesh frame)
//   - Mesh with material
//   - AnimationSet with one Animation containing rotation keys
//
// Parsed by D3DXLoadMeshHierarchyFromXA → ID3DXAnimationController.
// Animation duration: ~2 seconds, looping.

Material Material_0 {
    0.6; 0.7; 0.9; 1.0;;
    0.0;
    0.0; 0.0; 0.0;;
    0.0; 0.0; 0.0;;
}

// --- Frame hierarchy ---
Frame Frame_Root {
    FrameTransformMatrix {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;;
    }

    Frame Frame_Cube {
        FrameTransformMatrix {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0;;
        }

        Mesh Mesh_Cube {
            8;
            -1.0; -1.0; -1.0;,
             1.0; -1.0; -1.0;,
             1.0;  1.0; -1.0;,
            -1.0;  1.0; -1.0;,
            -1.0; -1.0;  1.0;,
             1.0; -1.0;  1.0;,
             1.0;  1.0;  1.0;,
            -1.0;  1.0;  1.0;;
            12;
            3; 0, 1, 2;,
            3; 0, 2, 3;,
            3; 1, 5, 6;,
            3; 1, 6, 2;,
            3; 5, 4, 7;,
            3; 5, 7, 6;,
            3; 4, 0, 3;,
            3; 4, 3, 7;,
            3; 3, 2, 6;,
            3; 3, 6, 7;,
            3; 4, 5, 1;,
            3; 4, 1, 0;;

            MeshMaterialList {
                1;
                12;
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;;
                { Material_0 }
            }

            MeshNormals {
                8;
                -0.577; -0.577; -0.577;,
                 0.577; -0.577; -0.577;,
                 0.577;  0.577; -0.577;,
                -0.577;  0.577; -0.577;,
                -0.577; -0.577;  0.577;,
                 0.577; -0.577;  0.577;,
                 0.577;  0.577;  0.577;,
                -0.577;  0.577;  0.577;;
                12;
                3; 0, 1, 2;,
                3; 0, 2, 3;,
                3; 1, 5, 6;,
                3; 1, 6, 2;,
                3; 5, 4, 7;,
                3; 5, 7, 6;,
                3; 4, 0, 3;,
                3; 4, 3, 7;,
                3; 3, 2, 6;,
                3; 3, 6, 7;,
                3; 4, 5, 1;,
                3; 4, 1, 0;;
            }
        }
    }
}

// --- Animation ---
AnimationSet AnimationSet_Rotate {
    Animation Animation_Frame_Cube {
        { Frame_Cube }
        AnimationKey {
            0;          // rotation
            3;          // 3 keys
            0;  4;  0.0, 0.0, 0.0, 1.0;,
            96; 4;  0.0, 0.7071, 0.0, 0.7071;,
            192; 4; 0.0, 1.0, 0.0, 0.0;;
        }
    }
}
