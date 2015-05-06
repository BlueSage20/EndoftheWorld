#pragma once
#include <glm/glm.hpp>
using namespace std;
#include "ME\Physics\BoundingObjectClass.h"
class OctopusTree
{
public:
	OctopusTree(void);
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

	//
	~OctopusTree(void);
};

