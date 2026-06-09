#include <iostream>

#include "Colors.h"
#include "Engine.h"
#include "GLMath.h"
#include "3d/actors/StaticMeshActor.h"
#include "3d/actors/DirectionalLightActor.h"

using namespace glengine;
using namespace glengine::world;
using namespace glengine::world::components;
using namespace glengine::world::actors;

int main() {
    auto engine = new Engine("GLEngine Sample", int2(1280, 720));
    engine->SetAllowNonFocusedPawnInput(true);

    // add sphere
    auto sphere = engine->SpawnActor<StaticMeshActor>("/builtin/models/sphere.obj");
    sphere->Material->Diffuse = Colors::BLUE;
    sphere->GetTransform()->SetPosition({1.5, 0, 5});

    // add cube
    auto cube = engine->SpawnActor<StaticMeshActor>("/builtin/models/cube.obj");
    cube->Material->Diffuse = Colors::RED;
    cube->GetTransform()->SetPosition({-1.5, 0, 5});

    // add environment
    auto sun = engine->SpawnActor<DirectionalLightActor>();
    sun->Ambient = float4(0.1, 0.1, 0.1, 1);
    sun->GetTransform()->SetRotation({-3 * PI / 4, PI/4, PI/8});

    engine->MainLoop();
    return 0;
}
