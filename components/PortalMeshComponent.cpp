//
// Created by Kyle Smith on 2026-06-12.
//

#include "PortalMeshComponent.h"

#include "Engine.h"

PortalMeshComponent::PortalMeshComponent(std::shared_ptr<glengine::world::mesh::StaticMesh> mesh) {
    pipeline = GetEngine()->GetRenderer()->GetRenderPipelineByName("portal");
    this->mesh = std::move(mesh);
}

void PortalMeshComponent::Render(const glengine::pipeline::wgpu::RenderBundle &bundle, glengine::MatrixStack &stack) {
    const mat4 transform = stack;

    pipeline->DrawMesh(bundle, *mesh->mesh, &transform);
}
