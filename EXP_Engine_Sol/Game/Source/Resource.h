#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "Globals.h"
#include "Random.h"

#include <string>
#include <vector>

class JsonConfig;

enum class ResourceType
{
	Mesh,
	Material,
	Texture,
	Scene,
	Model,
	Folder,
	None
};

class Resource
{
public:
	ResourceType type = ResourceType::None;
	uint UID = 0;

	std::string assetsFile = "";
	std::string libraryFile = "";
	uint referenceCount = 0;

	std::string name = "";
	std::vector<uint> resourcesInModels;

protected:
	Random randomNum;

public:

	Resource();
	Resource(ResourceType type);
	Resource(ResourceType type, const char* assetsFile, const char* name = "", uint UID = 0);
	~Resource();

	inline const uint GetUID() const { return UID; }
	inline ResourceType GetType() const { return type; }

	inline std::string GetAssetsFile() const { return assetsFile; }
	inline std::string GetLibraryFile() const { return libraryFile; }

	inline uint GetReferenceCount() const { return referenceCount; }
};
#endif //__RESOURCE_H__