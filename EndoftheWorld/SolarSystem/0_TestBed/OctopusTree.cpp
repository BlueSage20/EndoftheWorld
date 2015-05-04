#include "OctopusTree.h"


OctopusTree::OctopusTree(void)
{
}


OctopusTree::~OctopusTree(void)
{
}

OctopusTree::CalculateBounds(void)
{
	/*// What we'll give to the caller
      Bounds  b;

        // Determine min/max of the given set of points
        Point   min = *points[0];
        Point   max = *points[0];

        for (unsigned int i = 1; i < count; i++)
        {
                const Point &p = *points[i];
                if (p.x < min.x) min.x = p.x;
                if (p.y < min.y) min.y = p.y;
                if (p.z < min.z) min.z = p.z;
                if (p.x > max.x) max.x = p.x;
                if (p.y > max.y) max.y = p.y;
                if (p.z > max.z) max.z = p.z;
        }

        // The radius of the volume (dimensions in each direction)
        Point   radius = max - min;

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
        return b;*/
}
