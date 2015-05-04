/// INCLUDE + NAMESPACE ///
#pragma once

#include <glm/glm.hpp>
#include "ME\Physics\BoundingObjectClass.h"
#include "MyEngine.h"
//using namespace std;

/// CLASS DECLARATION ///
class OctopusTree
{
public:
	
	bool hasChild; // are we subdivided
	bool isLeaf; // checking if THIS current node is a leaf

	int treeLevel; // keeping track of sublevels
	int octID; // index lookup for all octant subdivisions (will help determin which asteroid hit what planet)
	float octLWH; // octant size = octLWH^3; we don't care what dimension, just that it makes a cube

	MeshManagerSingleton* pMeshMngr = MeshManagerSingleton::GetInstance(); //keep this in here for now

	vector3 octCentroid; //

	std::vector<BoundingObjectClass*> objectsInside; // dynamically shifts; holds the BO currently inside the octant
	OctopusTree* children[8]; // always 0 or 8 subdivisions
	BoundingObject* octBO; // a bounding object of the (current?) octant; needed for rendering + collision (containment) tests

/// CONSTRUCTORS
	OctopusTree(void); // Constructor
	OctopusTree(OctopusTree const& other); // Copy Constructor
	OctopusTree& operator=(OctopusTree const& other); // Copy Assignment Op
	~OctopusTree(void); // Destructor

	
/// MEMBER FUNCTIONS ///
	void Render(); // Renders AABB if not empty
	void CalculateBounds(const unsigned int count); //should this be a void?

	// Did not create any helper/get/set methods because it's useless clutter
	// because all our variables right now are public. There isn't much cause for concern
	// to make them private, so they can remain this way.
};



/* Nick Code::

	void setSize(float size);
	glm::vec3 v3Centroid;
	float v3CPosition;
	//pass in objectbounding list and iterate through it when necessary
	//
	//kids
	OctopusTree* m_pChild[8];
	//List of bounding objects
	std::vector<BoundingObjectClass*> m_lBoundingObject;
	//is it a leaf? If so, then do not scope down further
	bool isItALeaf;
	//We need a 3-level deep box
	//this will check levels
	int levelsForDays;
	

	//METHODs
	//loop through object list, see if something is inside itself

	//calculate size inside each subdivision
*/