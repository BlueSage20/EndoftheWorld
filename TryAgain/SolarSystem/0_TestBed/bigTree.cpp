/* Hanna Doerr - 5/5 */

/// INCLUDES + NAMESPACES
#include "bigTree.h"

/// CONSTRUCTOR DEFINITIONS
bigTree::bigTree(void)
{
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
static bigTree* getInstance()
{
	// what is the instance?
}

static void destroyInstance()
{}

/*Octants* GetOctant(int octantID)
{}*/

void InitTree(std::vector<BoundingObjectClass*> boundingObject, int maxSublevels = 4, int maxObjects = 2)
{
}

void updatePosition(BoundingObjectClass* bObj)
{	
}

void Render()
{
}

/// PRIVATE FUNCTION DEFINITIONS
void Release(void)
{}

void Init(void)
{}

void UpdatePosition(Octants* node, BoundingObjectClass* pBO)
{}

void TraverseRender(Octants* node)
{}

void TraverseInfo(Octants* node)
{}

void TraverseGet(Octants* node, Octants*& output, int octoID)
{}

void Subdivide(Octants* node, bool resetCount = false)
{}

void DeleteNode(Octants*& node)
{}