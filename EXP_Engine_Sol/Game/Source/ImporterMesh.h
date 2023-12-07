#pragma once
#include "Globals.h"
#include "ModuleImport.h"

struct aiScene;
struct aiNode;
struct aiMesh;
class ResourceMesh;
class mesh;

namespace Importer
{
	namespace MeshImporter
	{
		void LoadMeshes(ResourceMesh* mesh, const aiMesh* aiMesh);
		uint Save(const ResourceMesh* mesh, char** buffer); //Save with ResourceMesh
		uint Save(const mesh* mesh, char** buffer); //Save with mesh
		void Load(ResourceMesh* mesh, const char* buffer); //Load mesh from ResourceMesh
		void Load(mesh* mesh, const char* buffer); //Load mesh from mesh
	}
}