#include "bigTree.h"

bigTree::bigTree(void)
{
	octants = 8;
	
	maxObjects = 2; //placeholder value for now
   
	objectsInside = std::vector<BoundingObjectClass*>(); //initialize it
   
	//list (or collection) of squares?


}

bigTree* bigTree::getter()
{
	return pointer;
}

void bigTree::destroy(void)
{
	//essentially the destructor, can leave blank for now
}

OctopusTree* bigTree::GetOctant(int a_nOctantID)
{

}

void bigTree::InitTree(std::vector<BoundingObjectClass*> boundingObject, int maxSublevels = 4, int maxObjects = 2)
{
	vector<BoundingObjectClass*> newguy;

	//make new AABB
	//scale it
}

void bigTree::updatePosition(BoundingObjectClass* bo)
{

}

void bigTree::Render(void)
{

}

bigTree::bigTree(bigTree const& other)
{
	//copy constructor
}

bigTree::bigTree& operator=(bigTree const& other)
{
	//copy assignment operator
}

void bigTree::Release(void)
{

}

void bigTree::Init(void)
{

}

void bigTree::TraverseUpdatePosition(OctopusTree* node, BoundingObjectClass* pBO)
{

}

void bigTree::TraverseRender(OctopusTree* node)
{

}

void bigTree::TraverseInfo(OctopusTree* node)
{

}

void bigTree::TraverseGet(OctopusTree* node, OctopusTree*& output, int octoID)
{

}

void bigTree::GenerateSubTree(OctopusTree* node, bool resetCount = false)
{

}

void bigTree::DeleteNode(OctopusTree*& node)
{
	delete node;
}

bigTree::~bigTree(void)
{
}

//RECURSION LOGIG from Wikipedia
//Only for reference
/*% If this bin meets any exit conditions, do not divide it any further.
binPointCount = nnz(pointBins==binNo)
binEdgeLengths = binCorners(binNo,1:3) - binCorners(binNo,4:6)
binDepth = binDepths(binNo)
exitConditionsMet = binPointCount<value || min(binEdgeLengths)<value || binDepth>value
if exitConditionsMet
    return; % Exit recursive function
end
 
% Otherwise, split this bin into 8 new sub-bins with a new division point
newDiv = (binCorners(binNo,1:3) + binCorners(binNo,4:6)) / 2
for i = 1:8
    newBinNo = length(binDepths) + 1
    binDepths(newBinNo) = binDepths(binNo) + 1
    binParents(newBinNo) = binNo
    binCorners(newBinNo) = [one of the 8 pairs of the newDiv with minCorner or maxCorner]
    oldBinMask = pointBins==binNo
    ... Calculate which points in pointBins==binNo now belong in newBinNo 
    pointBins(newBinMask) = newBinNo
    % Recursively divide this newly created bin
    divide(newBinNo)
end*/
