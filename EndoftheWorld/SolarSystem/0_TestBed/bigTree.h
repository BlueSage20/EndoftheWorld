#pragma once
#include "OctopusTree.h"

namespace MyEngine

class bigTree
{
public:
	bigTree(void);
	~bigTree(void);

	//Members
	int octants; //Number of octants in the Tree
	int maxSublevels; //Maximum sublevel of the tree
	int maxObjects; //Maximum number of objects per octant
	OctopusTree* rootNode; //Root of the Tree. Stores all the vertices of the world. We want to subdivide this node into 8 parts.
	static bigTree* pointer; //Singleton pointer

	//Methods
	//gets instance of our tree
	static bigTree* getter();
	//destroys instance of our tree
	static void destroy(void);

	//get it by id
	OctopusTree* GetOctant(int a_nOctantID);

	//This is the method that will build the octree. Can we pass the root node into it?
	void InitTree(std::vector<BoundingObjectClass*> boundingObject, int maxSublevels = 4, int maxObjects = 2);
	
	//calculates octants (only if we have an object)
	void updatePosition(BoundingObjectClass* bo);

	//actually render the tree
	void Render(void);

private:
	//(bigTree is our singleton)
	/* Constructor */
	bigTree(void);
	/* Copy Constructor */
	bigTree(bigTree const& other);
	/* Copy Assignment Operator */
	bigTree& operator=(bigTree const& other);
	/* Destructor */
	~bigTree(void);

	/* Releases the objects memory */
	void Release(void);
	/* Initializates the objects fields */
	void Init(void);

	/* Taverses the tree finding the octant nodes the provided Bounding Object collides with*/
	void TraverseUpdatePosition(OctopusTree* node, BoundingObjectClass* pBO);

	/* Traverse the tree for rendering */
	void TraverseRender(OctopusTree* node);

	/* Traverses the tree filling internal information */
	void TraverseInfo(OctopusTree* node);

	/* Traverses finding the node that contains the specidied ID, it will store it in a_pOutput */
	void TraverseGet(OctopusTree* node, OctopusTree*& output, int octoID);

	/* Generates the 8 octant nodes for the specified a_pNode with a maximum level of subdivisions and max objects per node */
	void GenerateSubTree(OctopusTree* node, bool resetCount = false);

	/* Deletes the specidied node and subtrees */
	void DeleteNode(OctopusTree*& node);


};

