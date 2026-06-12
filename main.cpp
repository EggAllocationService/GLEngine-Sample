#include <iostream>

#include "Colors.h"
#include "Engine.h"
#include "GLMath.h"
#include "3d/actors/StaticMeshActor.h"
#include "3d/actors/DirectionalLightActor.h"
#include "DemoShaders.h"
#include "3d/texture/StaticTexture2D.h"
#include "actors/PortalPyramid.h"

using namespace glengine;
using namespace glengine::world;
using namespace glengine::world::components;
using namespace glengine::world::actors;


void addPortalPipeline(Engine* engine) {
    auto portalShaders = engine->GetRenderer()->CompileShader(embed_portal_wgsl);

    auto entries = new WGPUBindGroupLayoutEntry[4]{
            WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT,
            WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT,
            WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT,
            WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT,
    };

    auto bindGroup = WGPUBindGroupLayoutDescriptor {
        .nextInChain = nullptr,
        .label = {},
        .entryCount = 4,
        .entries = entries 
    };

    {
        // textures
        entries[0].texture = {
            .nextInChain = nullptr,
            .sampleType = WGPUTextureSampleType_Float,
            .viewDimension = WGPUTextureViewDimension_2D,
            .multisampled = WGPU_FALSE
        };
        entries[0].visibility = WGPUShaderStage_Fragment;
        entries[2] = entries[0];
        entries[2].binding = 2;
    }
    {
        // samplers
        entries[1].sampler = {
            .nextInChain = nullptr,
            .type = WGPUSamplerBindingType_Filtering
        };
        entries[1].binding = 1;
        entries[1].visibility = WGPUShaderStage_Fragment;
		entries[3] = entries[1];
		entries[3].binding = 3;
    }

    auto pipeline = engine->GetRenderer()->BuildRenderPipeline(
        "portal",
        portalShaders,
        nullptr,
        std::span(&bindGroup, 1),
        sizeof(mat4),
        nullptr
    );

    auto samplerDesc = WGPUSamplerDescriptor {
        .nextInChain = nullptr,
        .label = {},
        .addressModeU = WGPUAddressMode_Repeat,
        .addressModeV = WGPUAddressMode_Repeat,
        .addressModeW = WGPUAddressMode_ClampToEdge,
        .magFilter = WGPUFilterMode_Nearest,
        .minFilter = WGPUFilterMode_Nearest,
        .mipmapFilter = WGPUMipmapFilterMode_Linear,
        .lodMinClamp = 0,
        .lodMaxClamp = 1,
        .compare = WGPUCompareFunction_Undefined,
        .maxAnisotropy = 1
    };
    WGPUBindGroupEntry sampler = WGPU_BIND_GROUP_ENTRY_INIT;
    sampler.binding = 1;
    sampler.sampler = wgpuDeviceCreateSampler(engine->GetRenderer()->GetDevice(), &samplerDesc);
    pipeline->SetBinding(1, sampler);

    samplerDesc.magFilter = WGPUFilterMode_Linear;
    samplerDesc.minFilter = WGPUFilterMode_Linear;

    sampler.binding = 3;
	sampler.sampler = wgpuDeviceCreateSampler(engine->GetRenderer()->GetDevice(), &samplerDesc);
	pipeline->SetBinding(1, sampler);

    auto portalTex = engine->GetResourceManager()->GetResource<texture::StaticTexture2D>("/assets/portal.png");

    WGPUBindGroupEntry texture = WGPU_BIND_GROUP_ENTRY_INIT;
    texture.textureView = wgpuTextureCreateView(*portalTex->GetGPUTexture(), nullptr);
    pipeline->SetBinding(1, texture);

	auto noiseTex = engine->GetResourceManager()->GetResource<texture::StaticTexture2D>("/assets/noise.png");
	texture.textureView = wgpuTextureCreateView(*noiseTex->GetGPUTexture(), nullptr);
    texture.binding = 2;
    pipeline->SetBinding(1, texture);
    
    pipeline->CommitBindings();
}

int main() {
    auto engine = new Engine("GLEngine Sample", int2(1280, 720));

    // mount assets
    engine->GetResourceManager()->MountPak("/assets", "assets.pak");
    addPortalPipeline(engine);
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

    auto pyramid = engine->SpawnActor<PortalPyramid>();
    pyramid->GetTransform()->SetPosition({0, 2, 5});

    engine->MainLoop();
    return 0;
}
