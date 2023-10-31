#pragma once
#include "Component.h"

enum class ProjectionType
{
    Perpective, //원근 투영
    Orthographic //직교 투영 //everything looks flattened on 2d
};

class Camera :
    public Component
{
    using Super = Component;
public:
    Camera();
    virtual ~Camera();

    virtual void Update() override;

    void SetProjectionType(ProjectionType type) { _type = type;  }
    ProjectionType getProjectionType() { return _type; }

    void UpdateMatrix(); 

private:
    ProjectionType _type = ProjectionType::Orthographic;

public:
    static Matrix S_MatView;
    static Matrix S_MatProjection;

};

