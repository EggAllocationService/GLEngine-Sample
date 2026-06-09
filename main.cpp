#include <iostream>

#include "Engine.h"
#include "GLMath.h"
#include "3d/actors/StaticMeshActor.h"
#include "3d/components/DirectionalLightComponent.h"

using namespace glengine;
using namespace glengine::world;
using namespace glengine::world::components;
using namespace glengine::world::actors;

// Use for lighting, skybox, world geometry, etc
class Environment : public Actor {
public:
    Environment() {
        auto sun = CreateComponent<DirectionalLightComponent>();
        sun->GetTransform()->SetRotation({-3 * PI / 4, PI/4, PI/8});

        sun->Ambient = float4(0.1, 0.1, 0.1, 1);
        sun->Diffuse = float4(1, 1, 1, 1);
    }

    void Update(double deltaTime) override {};
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto engine = new Engine("GLEngine Sample", int2(1280, 720));
    engine->SetAllowNonFocusedPawnInput(true);

    // add sphere
    auto sphere = engine->SpawnActor<StaticMeshActor>("/builtin/models/sphere.obj");
    sphere->GetTransform()->SetPosition({1.5, 0, 5});

    // add cube
    auto cube = engine->SpawnActor<StaticMeshActor>("/builtin/models/cube.obj");
    cube->GetTransform()->SetPosition({-1.5, 0, 5});

    // add environment
    engine->SpawnActor<Environment>();

    engine->MainLoop();
    return 0;
}
