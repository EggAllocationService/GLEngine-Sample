//
// Created by Kyle Smith on 2026-06-12.
//

#include "PortalPyramid.h"

#include "Engine.h"
#include "GLMath.h"
#include "3d/text/Font.h"
#include "3d/text/SlugTextComponent.h"

PortalPyramid::PortalPyramid() {
    auto model = GetEngine()
        ->GetResourceManager()
        ->GetResource<glengine::world::mesh::StaticMesh>("/assets/pyramid.obj");

    mesh = CreateComponent<PortalMeshComponent>(model);

    auto font = GetEngine()
        ->GetResourceManager()
        ->GetResource<glengine::world::font::Font>("/builtin/fonts/quattrocento.ttf");

    auto text = CreateComponent<glengine::world::font::SlugTextComponent>();
    text->SetFont(font);
    text->SetText("portal.wgsl");
    text->GetTransform()->SetScale({0.25, 0.25 ,0.25});
    text->GetTransform()->SetPosition({0.0, -0.5, -1});

    rotation = 0;
}

void PortalPyramid::Update(double deltaTime) {
    rotation += deltaTime * PI * 0.25;
    GetTransform()->SetRotation({0, rotation, 0});
}
