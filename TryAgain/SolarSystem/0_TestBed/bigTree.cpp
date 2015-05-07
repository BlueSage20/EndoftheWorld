/* Hanna Doerr - 5/5 */

/// INCLUDES + NAMESPACES
#include "bigTree.h"

/// CONSTRUCTOR DEFINITIONS
bigTree::bigTree(void)
{
}

bigTree::bigTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList)
{
	createTree(m_pMeshMngr, objectsList);
	Render(m_pMeshMngr);
}


bigTree::bigTree(bigTree const& other) // is this needed?
{
}

bigTree::~bigTree(void)
{
}

bigTree& bigTree::operator=(bigTree const& other)
{
	return *this;
}


/// PUBLIC FUNCTION DEFINITIONS
/*bigTree* bigTree::getInstance()
{
	// what is the instance?
}*/

void bigTree::destroyInstance()
{}

/*Octants* GetOctant(int octantID)
{}*/

void bigTree::createTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList)
{
	vector3 minPos;
	vector3 maxPos;

	for(int i = 0; i < objectsList.size(); i++){
		std::cout << objectsList[i]->GetInstanceName();
		std::cout << objectsList[i]->GetHalfWidth().x;
		std::cout << objectsList[i]->GetHalfWidth().y;
		std::cout << objectsList[i]->GetHalfWidth().z << std::endl;
	}

	minPos = objectsList[0]->GetCentroidGlobal() - objectsList[0]->GetHalfWidth();
	maxPos = objectsList[0]->GetCentroidGlobal() + objectsList[0]->GetHalfWidth();

	for(int i = 0; i < objectsList.size(); i++){
		if (minPos.x > objectsList[i]->GetCentroidGlobal().x - objectsList[i]->GetHalfWidth().x){
			minPos.x = objectsList[i]->GetCentroidGlobal().x - objectsList[i]->GetHalfWidth().x;
		}
		else if (maxPos.x < objectsList[i]->GetCentroidGlobal().x + objectsList[i]->GetHalfWidth().x){
			maxPos.x = objectsList[i]->GetCentroidGlobal().x + objectsList[i]->GetHalfWidth().x;
		}

		if (minPos.y > objectsList[i]->GetCentroidGlobal().y - objectsList[i]->GetHalfWidth().y){
			minPos.y = objectsList[i]->GetCentroidGlobal().y - objectsList[i]->GetHalfWidth().y;
		}
		else if (maxPos.y < objectsList[i]->GetCentroidGlobal().y + objectsList[i]->GetHalfWidth().y){
			maxPos.y = objectsList[i]->GetCentroidGlobal().y + objectsList[i]->GetHalfWidth().y;
		}

		if (minPos.z > objectsList[i]->GetCentroidGlobal().z - objectsList[i]->GetHalfWidth().z){
			minPos.z = objectsList[i]->GetCentroidGlobal().z - objectsList[i]->GetHalfWidth().z;
		}
		else if (maxPos.z < objectsList[i]->GetCentroidGlobal().z + objectsList[i]->GetHalfWidth().z){
			maxPos.z = objectsList[i]->GetCentroidGlobal().z + objectsList[i]->GetHalfWidth().z;
		}
	}
	
	centroid = (minPos + maxPos) / 2.0f;

	if (octLWH.x < glm::distance(vector3(minPos.x, 0, 0), vector3(maxPos.x, 0, 0))){
		octLWH.x = glm::distance(vector3(minPos.x, 0, 0), vector3(maxPos.x, 0, 0));
	}
	if (octLWH.y < glm::distance(vector3(minPos.y, 0, 0), vector3(maxPos.y, 0, 0))){
		octLWH.y = glm::distance(vector3(minPos.y, 0, 0), vector3(maxPos.y, 0, 0));
	}
	if (octLWH.z < glm::distance(vector3(minPos.z, 0, 0), vector3(maxPos.z, 0, 0))){
		octLWH.z = glm::distance(vector3(minPos.z, 0, 0), vector3(maxPos.z, 0, 0));
	}
}

void bigTree::Render(MeshManagerSingleton* m_pMeshMngr)
{
	m_pMeshMngr->AddCubeToQueue(glm::translate(centroid) * glm::scale(vector3(octLWH)), MERED, MERENDER::WIRE);
}

/*void bigTree::InitTree(std::vector<BoundingObjectClass*> boundingObject, int maxSublevels = 4, int maxObjects = 2)
{
}*/

void bigTree::updatePosition(BoundingObjectClass* bObj)
{	
}

/// PRIVATE FUNCTION DEFINITIONS
void bigTree::Release(void)
{}

void bigTree::Init(void)
{}

void bigTree::UpdatePosition(Octants* node, BoundingObjectClass* pBO)
{}

void bigTree::TraverseRender(Octants* node)
{}

void bigTree::TraverseInfo(Octants* node)
{}

void bigTree::TraverseGet(Octants* node, Octants*& output, int octoID)
{}

/*void bigTree::Subdivide(Octants* node, bool resetCount = false)
{}*/

void bigTree::DeleteNode(Octants*& node)
{}