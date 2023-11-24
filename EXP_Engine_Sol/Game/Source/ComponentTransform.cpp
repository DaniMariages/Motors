#include "ComponentTransform.h"
#include "GameObject.h"

#include "Globals.h"
#include "../External/ImGui/imgui.h"

ComponentTransform::ComponentTransform(GameObject* parent) :
	Component(parent), position(float3(0.0f, 0.0f, 0.0f)), rotation(Quat::identity), scale(float3(0.0f, 0.0f, 0.0f))
{
	type = typeComponent::Transform;
	UpdateMatrix();
};

ComponentTransform::ComponentTransform(GameObject* parent, float3 position, float3 scale, Quat rotation) :
	Component(parent), scale(scale), rotation(rotation), position(position)
{
	transform = float4x4::FromTRS(position, rotation, scale);
	type = typeComponent::Transform;
};

void ComponentTransform::Enable() {	if (!this->active) this->active = true;	}

void ComponentTransform::Disable() { if (this->active) this->active = false; }

void ComponentTransform::Update() {}

void inline ComponentTransform::SetPosition(float3 position) 
{
	this->position = position;  
	UpdateMatrix(); 
};

void inline ComponentTransform::SetRotation(Quat rotation)
{ 
	this->rotation = rotation; 
	UpdateMatrix(); 
};

void inline ComponentTransform::SetScale(float3 scale)
{ 
	this->scale = scale; 
	UpdateMatrix(); 
};

void ComponentTransform::UpdateMatrix() {
	transform = float4x4::FromTRS(position, rotation, scale);
}

void ComponentTransform::DrawInspector() 
{
	if (ImGui::CollapsingHeader("Component Transform"))
	{
		float3 euler_rotation = rotation.ToEulerXYZ();
		float3 euler_degree = euler_rotation * RADTODEG;
		ImGui::DragFloat3("Position:", (float*)&position);
		ImGui::DragFloat3("Scale:", (float*)&scale);
		bool rot_change = ImGui::DragFloat3("Rotation:", (float*)&euler_degree);

		if (rot_change)
		{
			euler_rotation = euler_degree * DEGTORAD;
			rotation = Quat::FromEulerXYZ(euler_rotation.x, euler_rotation.y, euler_rotation.z);
		}

		UpdateMatrix();
	}
}
