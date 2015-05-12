/* Hanna Doerr - 5/5 */

/// INCLUDES + NAMESPACES
#pragma once
#include "Octants.h"

using namespace MyEngine;

const int maxLevels = 3; //Maximum sublevel of the tree
const int maxObjects = 2; //Maximum number of objects per octant

/// CLASS
class bigTree
{
public:
	int octants; //Number of octants in the Tree
	Octants* rootNode; //Root of the Tree. Stores all the vertices of the world. We want to subdivide this node into 8 parts.
	static bigTree* pointer; //Singleton pointer
	vector3 centroid; //Center of the Octant in world coordinates
	bool isLeaf; // checking if THIS current node is a leaf
	int treeLevel; // keeping track of sublevels
	int octID; // index lookup for all octant subdivisions (will help determine which asteroid hit what planet)
	BoundingObjectClass* octBO; // a bounding object of the (current?) octant needed for rendering + collision (containment) tests
	float octSize; // octant size = octSize^3 we don't care what dimension, just that it makes a cube
	std::vector<BoundingObjectClass*> objectsInside; // dynamically shifts; holds the BO currently inside the octant
	bigTree* children[8]; //Children of the octant

	/* Constructor */
	bigTree(void);
	/* Copy Constructor */
	bigTree(bigTree const& other);
	/* Copy Assignment Operator */
	bigTree& operator=(bigTree const& other);
	/* Destructor */
	~bigTree(void);

	bigTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList, std::vector<float> objectSizes);
	bigTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList, int level, int ID, vector3 childCentroid, float childSize);
	
/// FUNCTION DECLARATION
	// Gets instance of our tree
	static bigTree* getInstance();
	//destroys instance of our tree
	static void destroyInstance(void);

	//get it by id
	Octants* GetOctant(int octantID);

	//This is the method that will build the octree. Can we pass the root node into it?
	void createTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList, std::vector<float> objectSizes);
	void subdivideTree(MeshManagerSingleton* m_pMeshMngr, std::vector<BoundingObjectClass*> objectsList);
	std::vector<BoundingObjectClass*> objectsInsideLeaf();
	
	//calculates octants (only if we have an object)
	void updatePosition(BoundingObjectClass* bObj);

	//actually render the tree
	void Render(MeshManagerSingleton* m_pMeshMngr);

private:
/// FUNCTION DECLARATION
	/* Releases the objects memory */
	void Release(void);
	/* Initializates the objects fields */
	void Init(void);

	/* Taverses the tree finding the octant nodes the provided Bounding Object collides with*/
	void UpdatePosition(Octants* node, BoundingObjectClass* pBO);

	/* Traverse the tree for rendering */
	void TraverseRender(Octants* node);

	/* Traverses the tree filling internal information */
	void TraverseInfo(Octants* node);

	/* Traverses finding the node that contains the specidied ID, it will store it in a_pOutput */
	void TraverseGet(Octants* node, Octants*& output, int octoID);

	/* Generates the 8 octant nodes for the specified Node with a maximum level of subdivisions and max objects per node */
	//void Subdivide(Octants* node, bool resetCount = false);

	/* Deletes the specidied node and subtrees */
	void DeleteNode(Octants*& node);

};

