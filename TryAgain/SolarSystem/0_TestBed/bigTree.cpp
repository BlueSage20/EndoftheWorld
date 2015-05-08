/* Hanna Doerr - 5/5 */

/// INCLUDES + NAMESPACES
#include "bigTree.h"

/// CONSTRUCTOR DEFINITIONS
bigTree::bigTree(void)
{
}

bigTree::bigTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList, std::vector<float> objectSizes)
{
	createTree(m_pMeshMngr, objectsList, objectSizes);
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

void bigTree::createTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList, std::vector<float> objectSizes)
{
	vector3 minPos;
	vector3 maxPos;

	minPos = objectsList[0]->GetCentroidGlobal() - objectSizes[0];
	maxPos = objectsList[0]->GetCentroidGlobal() + objectSizes[0];

	for(int i = 0; i < objectsList.size(); i++){
		if (minPos.x > objectsList[i]->GetCentroidGlobal().x - objectSizes[i]){
			minPos.x = objectsList[i]->GetCentroidGlobal().x - objectSizes[i];
		}
		else if (maxPos.x < objectsList[i]->GetCentroidGlobal().x + objectSizes[i]){
			maxPos.x = objectsList[i]->GetCentroidGlobal().x + objectSizes[i];
		}

		if (minPos.y > objectsList[i]->GetCentroidGlobal().y - objectSizes[i]){
			minPos.y = objectsList[i]->GetCentroidGlobal().y - objectSizes[i];
		}
		else if (maxPos.y < objectsList[i]->GetCentroidGlobal().y + objectSizes[i]){
			maxPos.y = objectsList[i]->GetCentroidGlobal().y + objectSizes[i];
		}

		if (minPos.z > objectsList[i]->GetCentroidGlobal().z - objectSizes[i]){
			minPos.z = objectsList[i]->GetCentroidGlobal().z - objectSizes[i];
		}
		else if (maxPos.z < objectsList[i]->GetCentroidGlobal().z + objectSizes[i]){
			maxPos.z = objectsList[i]->GetCentroidGlobal().z + objectSizes[i];
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

void bigTree::Subdivide(Octants* node, bool resetCount)
{
   //int* howManyKids = node->children.size();
	//Onode->children->size();
	
	for(int i=0; i < 8; i++)
   {
    if(node->isLeaf && node->children != NULL){
	vector3 minBB;
	vector3 maxBB;
	vector3 avgBB;

	minBB = node->objectsInside[0]->GetCentroidGlobal() - node->objectsInside[0]->GetHalfWidth();
	maxBB = node->objectsInside[0]->GetCentroidGlobal() + node->objectsInside[0]->GetHalfWidth();
	avgBB = (minBB + maxBB)/2.0f;
	   
	//AABB aabb;
	//aabb.minBB.z = minBB.z;
	//aabb.maxBB.z = avgBB.z;
	//aabb.minBB.y = minBB.y;
	//aabb.maxBB.y = avgBB.y;
	//aabb.minBB.x = minBB.x;
	//aabb.maxBB.x = avgBB.x;
	BoundingObjectClass* aabb = node->octBO;
	aabb->m_v3MinAABBG.z = minBB.z;
	aabb->m_v3MaxAABBG.z = avgBB.z;
	aabb->m_v3MinAABBG.y = minBB.y;
	aabb->m_v3MaxAABBG.y = avgBB.y;
	aabb->m_v3MinAABBG.x = minBB.x;
	aabb->m_v3MaxAABBG.x = avgBB.x;
 
	//if(i & 4){ // greater z
		//aabb.minBB.z = avgBB.z;
		//aabb.maxBB.z = maxBB.z;	
	//}
	//if(i & 2){ // greater y
		//aabb.minBB.y = avgBB.y;
		//aabb.maxBB.y = maxBB.y;
	//}
	//if(i & 1){ // greater x
		//aabb.minBB.x = avgBB.x;
		//aabb.maxBB.x = maxBB.x;
	//}
	if(i & 4){ // greater z
		aabb->m_v3MinAABBG.z = avgBB.z;
		aabb->m_v3MaxAABBG.z = maxBB.z;	
	}
	if(i & 2){ // greater y
		aabb->m_v3MinAABBG.y = avgBB.y;
		aabb->m_v3MaxAABBG.y = maxBB.y;	
	}
	if(i & 1){ // greater x
		aabb->m_v3MinAABBG.x = avgBB.x;
		aabb->m_v3MaxAABBG.x = maxBB.x;	
	}

	//node->hasChild = true;
	//node->treeLevel++
	node->Render(); //render
	//what do we do with resetCount?
	   
	}

  }

}



void bigTree::DeleteNode(Octants*& node)
{}