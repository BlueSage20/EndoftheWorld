/* Hanna Doerr - 5/5 */

/// INCLUDES + NAMESPACES
#include "bigTree.h"

/// CONSTRUCTOR DEFINITIONS
bigTree::bigTree(void)
{
}

bigTree::bigTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList, std::vector<float> objectSizes)
{
	isLeaf = false;
	treeLevel = 0;
	octID = 0;

	createTree(m_pMeshMngr, objectsList, objectSizes);
	octBO = new BoundingObjectClass(centroid, octSize);
	subdivideTree(m_pMeshMngr, objectsList);
	Render(m_pMeshMngr);
}

bigTree::bigTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList, int level, int ID, vector3 childCentroid, float childSize)
{
	isLeaf = false;
	treeLevel = level;
	octID = ID;
	centroid = childCentroid;
	octSize = childSize;

	octBO = new BoundingObjectClass(centroid, octSize);
	subdivideTree(m_pMeshMngr, objectsList);
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

	for(std::size_t i = 0; i < objectsList.size(); i++){
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

	if (octSize < glm::distance(vector3(minPos.x, 0, 0), vector3(maxPos.x, 0, 0))){
		octSize = glm::distance(vector3(minPos.x, 0, 0), vector3(maxPos.x, 0, 0));
	}
	if (octSize < glm::distance(vector3(minPos.y, 0, 0), vector3(maxPos.y, 0, 0))){
		octSize = glm::distance(vector3(minPos.y, 0, 0), vector3(maxPos.y, 0, 0));
	}
	if (octSize < glm::distance(vector3(minPos.z, 0, 0), vector3(maxPos.z, 0, 0))){
		octSize = glm::distance(vector3(minPos.z, 0, 0), vector3(maxPos.z, 0, 0));
	}
	
}

void bigTree::subdivideTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList)
{
	//Recursively divides the space in the world
	//Might as well check for collisions here, too
	//They only collide if they are in the same box

	for(std::size_t i = 0; i < objectsList.size(); i++){
		if (objectsList[i]->IsColliding(*octBO))
		{
			objectsInside.push_back(objectsList[i]);
		}
	}

	if (objectsInside.size() == maxObjects)
	{
		isLeaf = true;
	}

	else if (objectsInside.size() > maxObjects)
	{
		if (treeLevel < maxLevels && isLeaf == false)
		{
			vector3 childCentroid;
			float childSize = octSize/4.0f;

			//I believe collision calls would be made in here?
			for (int i = 0; i < 8; i++)
			{
				childCentroid = centroid;
				
				//	  Front
				//	---------
				//	| 3 | 2 |
				//	---------
				//	| 0 | 1 |
				//	---------  
				
				if(i == 0){
					childCentroid += vector3(-childSize, -childSize, childSize);
				}
				else if(i == 1){
					childCentroid += vector3(childSize, -childSize, childSize);
				}
				else if(i == 2){
					childCentroid += vector3(childSize, childSize, childSize); 
				}
				else if(i == 3){
					childCentroid += vector3(-childSize, childSize, childSize);
				}

				//	  Back
				//	---------
				//	| 7 | 6 |
				//	---------
				//	| 4 | 5 |
				//	---------	
				
				else if(i == 4){
					childCentroid += vector3(-childSize, -childSize, -childSize);
				}
				else if(i == 5){
					childCentroid += vector3(childSize, -childSize, -childSize);
				}
				else if(i == 6){
					childCentroid += vector3(childSize, childSize, -childSize);
				}
				else if(i == 7){
					childCentroid += vector3(-childSize, childSize, -childSize);
				}

				children[i] = new bigTree(m_pMeshMngr, objectsInside, treeLevel + 1, octID + i, childCentroid, childSize * 2.0f);
			}
		}
	}
}

std::vector<BoundingObjectClass*> bigTree::objectsInsideLeaf(){
	if (isLeaf == true || treeLevel == maxLevels)
	{
		return objectsInside;
	}
}

void bigTree::Render(MeshManagerSingleton* m_pMeshMngr)
{
	m_pMeshMngr->AddCubeToQueue(glm::translate(centroid) * glm::scale(vector3(octSize, octSize, octSize)), MERED, MERENDER::WIRE);
}

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

void bigTree::DeleteNode(Octants*& node)
{}