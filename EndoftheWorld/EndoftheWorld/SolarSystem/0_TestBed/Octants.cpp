/* Hanna Doerr - 5/5 */

/// INCLUDE + NAMESPACES
#include "Octants.h"

/// CONSTRUCTOR DEFINITIONS
Octants::Octants(void)
{
	hasChild = false;
	isLeaf = true;

	pMeshMngr = MeshManagerSingleton::GetInstance();
	//octBO = new BoundingObjectClass(octCentroid, octLWH);
}

Octants::Octants(Octants const& other)
{
}

Octants& Octants::operator=(Octants const& other)
{
	// return dereferenced pointer; returns a reference to the calling object itself
	return *this;
}

Octants::~Octants(void)
{
}


/// FUNCTION DEFINITIONS
void Octants::Render()
{
	octBO->Render(true);
}

void Octants::CalculateBounds(void)
{
	//float bounds = 
	octBO = new BoundingObjectClass(octCentroid, octLWH);
	//octBO->CalculateAABB(); //private function

	/*
	// What we'll give to the caller
    //Bounds  b;
	BoundingObjectClass* b;
	
	// Determine min/max of the given set of points
        //Point   min = *points[0];
       // Point   max = *points[0];
	   b.m_v3minAABBG = 
       b.m_v3maxAABBG = 

        for (unsigned int i = 1; i < count; i++)
        {
            //this looks eerily similar to the code from the midterm
			//and several other assignments
			const Point &p = *points[i];
                if (p.x < min.x) min.x = p.x;
                if (p.y < min.y) min.y = p.y;
                if (p.z < min.z) min.z = p.z;
                if (p.x > max.x) max.x = p.x;
                if (p.y > max.y) max.y = p.y;
                if (p.z > max.z) max.z = p.z;
        }

        // The radius of the volume (dimensions in each direction)
        //Point   radius = max - min;
		b.m_fRadius = max - min;

        // Find the center of this space
        b.center = min + radius * 0.5;

        // We want a CUBIC space. By this, I mean we want a bounding cube, not
        // just a bounding box. We already have the center, we just need a
        // radius that contains the entire volume. To do this, we find the
        // maxumum value of the radius' X/Y/Z components and use that
        b.radius = radius.x;
        if (b.radius < radius.y) b.radius = radius.y;
        if (b.radius < radius.z) b.radius = radius.z;

        // Done
        return b;
		*/
}
