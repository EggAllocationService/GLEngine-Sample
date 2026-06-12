//
// Created by Kyle Smith on 2026-06-12.
//

#include "PortalPyramid.h"

#include "Engine.h"

PortalPyramid::PortalPyramid() {
    auto model = GetEngine()
        ->GetResourceManager()
        ->GetResource<glengine::world::mesh::StaticMesh>("/assets/pyramid.obj");

    mesh = CreateComponent<PortalMeshComponent>(model);
}

void PortalPyramid::Update(double deltaTime) {
}
