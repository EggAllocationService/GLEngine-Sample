//
// Created by Kyle Smith on 2026-06-12.
//

#ifndef GLENGINE_SAMPLE_PORTALPYRAMID_H
#define GLENGINE_SAMPLE_PORTALPYRAMID_H
#include "../components/PortalMeshComponent.h"
#include "3d/Actor.h"


class PortalPyramid : public glengine::world::Actor {
public:
    PortalPyramid();
    void Update(double deltaTime) override;
private:
    std::shared_ptr<PortalMeshComponent> mesh;
};


#endif //GLENGINE_SAMPLE_PORTALPYRAMID_H
