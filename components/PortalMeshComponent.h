//
// Created by Kyle Smith on 2026-06-12.
//

#ifndef GLENGINE_SAMPLE_PORTALMESHCOMPONENT_H
#define GLENGINE_SAMPLE_PORTALMESHCOMPONENT_H
#include "3d/ActorSceneComponent.h"
#include "3d/mesh/StaticMesh.h"


class PortalMeshComponent : public glengine::world::ActorSceneComponent {
public:
    PortalMeshComponent(std::shared_ptr<glengine::world::mesh::StaticMesh> mesh);
    void Render(const glengine::pipeline::wgpu::RenderBundle &, glengine::MatrixStack &stack) override;
private:
    std::shared_ptr<glengine::world::mesh::StaticMesh> mesh;
    std::shared_ptr<glengine::pipeline::wgpu::RenderPipeline> pipeline;
};


#endif //GLENGINE_SAMPLE_PORTALMESHCOMPONENT_H
