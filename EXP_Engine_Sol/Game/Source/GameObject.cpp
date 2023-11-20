#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentTexture.h"
#include "ComponentMesh.h"
#include <vector>

GameObject::GameObject(std::string name, GameObject* parent)
{
	Name = name;
	Parent = parent;
}

GameObject::~GameObject() {}

bool GameObject::Enable() //Start up + bool toggle
{
	if (!active) {
		active = true;
		return true;
		//StartUp here...
	}
	return false;
}

bool GameObject::Disable()
{
	if (active) {
		active = false;
		return true;
	}
	return false;
}

void GameObject::ToggleActive()
{
	this->active = !this->active;
}

void GameObject::EnableDisableParent()
{
	this->active = !this->active;
	for (unsigned int i = 0; i < this->children.size(); i++)
	{
		children[i]->EnableDisableParent();
	}
}


void GameObject::Update() 
{
	std::vector<Component*>::iterator item = components.begin();
	bool ret = true;
}

void GameObject::SetParent(GameObject* parent)
{
	Parent = parent;
}

Component* GameObject::AddComponent(Component* component)
{
	Component* ret = nullptr;

	switch (component->type)
	{
	case(typeComponent::Error):
		//LOG("Component Type Error! Something broke...");
		break;
	case(typeComponent::Transform):
		ret = new ComponentTransform(this);
		LOG("Component Transform added to %s", component->parent->Name.c_str());
		break;
	case(typeComponent::Material):
		if (this->GetComponent(typeComponent::Material) != nullptr) {
			return nullptr;
		}
		ret = new ComponentTexture(this);
		LOG("Component Texture added to %s", component->parent->Name.c_str());
		break;
	case(typeComponent::Mesh):
		ret = new ComponentMesh(this);
		LOG("Component mesh added to %s", component->parent->Name.c_str());
		break;

	}

	components.push_back(component);
	return ret;
}

GameObject* GameObject::AddChildren(GameObject* children) 
{
	this->children.push_back(children);
	return children;
}

Component* GameObject::GetComponent(typeComponent type)
{
	std::vector<Component*>::iterator item = components.begin();

	for (; item != components.end(); ++item) 
	{
		if ((*item)->type == type) 
		{
			return (*item);
		}
	}
	return nullptr;
}

std::vector<Component*> GameObject::GetComponents(typeComponent type)
{
	std::vector<Component*>::iterator item = components.begin();

	std::vector<Component*> ret;

	for (; item != components.end(); ++item) 
	{
		if ((*item)->type == type) {
			ret.push_back((*item));
		}
	}

	return ret;
}
