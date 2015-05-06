#include "OctopusTree.h"


OctopusTree::OctopusTree(void)
{
}

OctopusTree::OctopusTree(OctopusTree const& other)
{
	//copy constructor
}

OctopusTree::OctopusTree& operator=(OctopusTree const& other)
{
	//copy assignment operator
}

OctopusTree::~OctopusTree(void)
{
	//Destructor. We can leave blank for now.
}

void OctopusTree::Render()
{

}

void OctopusTree::CalculateBounds(const unsigned int count) //should it be void instead?
{
	//SHOULD WE use properties of the BoundingObject, or the OctopusTree?
	//See the code below
	
	
	// What we'll give to the caller
    //Bounds  b;
	//We could also use this class's BoundingObject* octBO;???
	BoundingObjectClass* b;
        
	
	// Determine min/max of the given set of points
        //Point   min = *points[0];
       //Point   max = *points[0];
	  //In our older code, v3_Min/Max = lVertices[0];
	 //lVertices = a_lVertex (found in BO class)
	   b.m_v3minAABBG = *a_lVertex[0];
       b.m_v3maxAABBG = *a_lVertex[0];

	   //beugh

        for (unsigned int i = 1; i < count; i++)
        {
            //this looks eerily similar to the code from the midterm
			//and several other assignments
			const Point &p = *a_lVertex[i];
                if (p.x < b.m_v3minAABBG.x) b.m_v3minAABBG.x = p.x;
                if (p.y < b.m_v3minAABBG.y) b.m_v3minAABBG.y = p.y;
                if (p.z < b.m_v3minAABBG.z) b.m_v3minAABBG.z = p.z;
                if (p.x > b.m_v3maxAABBG.x) b.m_v3maxAABBG.x = p.x;
                if (p.y > b.m_v3maxAABBG.y) b.m_v3maxAABBG.y = p.y;
                if (p.z > b.m_v3maxAABBG.z) b.m_v3maxAABBG.z = p.z;
        }

        // The radius of the volume (dimensions in each direction)
        //Point   radius = max - min;
		b.m_fRadius = b.m_v3maxAABBG - b.m_v3minAABBG;

        // Find the center of this space
		//do we use b.center, or this class's vector3 octCentroid?
        b.center = b.m_v3minAABBG + b.m_fRadius * 0.5;

        // We want a CUBIC space. By this, I mean we want a bounding cube, not
        // just a bounding box. We already have the center, we just need a
        // radius that contains the entire volume. To do this, we find the
        // maxumum value of the radius' X/Y/Z components and use that
        b.radius = b.radius.x;
        if (b.radius < b.radius.y) b.radius = b.radius.y;
        if (b.radius < b.radius.z) b.radius = b.radius.z;

        // Done
        return b;
}
