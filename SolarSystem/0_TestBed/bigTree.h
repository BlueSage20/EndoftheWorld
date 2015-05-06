/* Hanna Doerr - 5/5 */

/// INCLUDES + NAMESPACES
#pragma once
#include "Octants.h"

using namespace MyEngine;

/// CLASS
class bigTree
{
public:
	int octants; //Number of octants in the Tree
	int maxLevels; //Maximum sublevel of the tree
	int maxObjects; //Maximum number of objects per octant
	Octants* rootNode; //Root of the Tree. Stores all the vertices of the world. We want to subdivide this node into 8 parts.
	static bigTree* pointer; //Singleton pointer

/// FUNCTION DECLARATION
	// Gets instance of our tree
	static bigTree* getInstance();
	//destroys instance of our tree
	static void destroyInstance(void);

	//get it by id
	Octants* GetOctant(int octantID);

	//This is the method that will build the octree. Can we pass the root node into it?
	void InitTree(std::vector<BoundingObjectClass*> boundingObject, int maxSublevels = 4, int maxObjects = 2);
	
	//calculates octants (only if we have an object)
	void updatePosition(BoundingObjectClass* bObj);

	//actually render the tree
	void Render(void);

private:
	/* Constructor */
	bigTree(void);
	/* Copy Constructor */
	bigTree(bigTree const& other);
	/* Copy Assignment Operator */
	bigTree& operator=(bigTree const& other);
	/* Destructor */
	~bigTree(void);


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
	void Subdivide(Octants* node, bool resetCount = false);

	/* Deletes the specidied node and subtrees */
	void DeleteNode(Octants*& node);

};

