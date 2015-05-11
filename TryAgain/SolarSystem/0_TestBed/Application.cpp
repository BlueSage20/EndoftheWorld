#include "ApplicationClass.h"
#include "bigTree.h"

//OCTREE NOTES
//Look at the OctantClass.h and OctreeSingleton.h files. They have all methods needed
//See what data structures are being used
//Get the box (by the root node), and find out how many times to subdivide root.
//Then display the box. Subdivisions are dependent on amount of things in the scene.
//Collision check: a list of lists?
//------------------------------------------------------------------------------------------
//An Octant uses a list of bounding objects
//Data you will want to query is stored in leaf nodes
//Make 'n' calls to whatever is the insert method (one for each point)
//So, we need to get the points of the models
//--------------------------------------------------------------------------------------------
//We do build the octree in this .cpp file
//MapValue hte camera XY into pixels (into Alberto's coordinate system?)
//Check the code of the LERP/SLERP list for help



//OctreeSingleton *octree;
//OctantClass *baby; //this guy is inserted into the tree
float randStartMercury;
float randStartVenus;
float randStartEarth;
float randStartMars;
float randStartJupiter;
float randStartSaturn;
float randStartUranus;
float randStartNeptune;

void ApplicationClass::InitUserAppVariables()
{	
	randStartMercury = (float)rand();
	randStartVenus = (float)rand();
	randStartEarth = (float)rand();
	randStartMars = (float)rand();
	randStartJupiter = (float)rand();
	randStartSaturn = (float)rand();
	randStartUranus = (float)rand();
	randStartNeptune = (float)rand();
	//Frustum = camera view. We MAY need to store this as a variable
	m_pCamera->SetPosition(vector3(0.0f, 0.0f, 120.0f));
	//OctantClass *octree;
	
	//Create a new octree
	//The singleton class contains the Octant.h
	//It holds the octants
	//Let's get the instance of it first
	//octree->GetInstance();
	//octree->Init(); //inaccessible

	//It starts out as empty
	//octree->IsEmpty = true;

	//Try to get the root
	//octree->m_pRoot->IsEmpty = true;
	

	m4Sun = matrix4(IDENTITY); //we need this, maybe?
	//Mercury
	//Venus
	m4Earth = matrix4(IDENTITY); //we need this, maybe?
	//m4Mars = matrix4(IDENTITY);

	m_pMeshMngr->LoadModelUnthreaded("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\01_Mercury.obj", "Mercury");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\02_Venus.obj", "Venus");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\04_Mars.obj", "Mars");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\05_Jupiter.obj", "Jupiter");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\06_Saturn.obj", "Saturn");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\07_Uranus.obj", "Uranus");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\08_Neptune.obj", "Neptune");
	//Is this where we call the Octree's "Render" method?

	//stand-in comet
	m_pMeshMngr->LoadModelUnthreaded("Planets\\09_Pluto.obj", "Pluto");
	m_sSelectedObject = "Pluto";

	int instances = m_pMeshMngr->GetNumberOfInstances();

	for (int i = 0; i < instances; i++){
		planets.push_back(m_pMeshMngr->GetBoundingObject(i));
	}

	objectSizes.push_back(15.0f);
	objectSizes.push_back(0.2552f);
	objectSizes.push_back(0.6349f);
	objectSizes.push_back(0.6682f);
	objectSizes.push_back(0.3545f);
	objectSizes.push_back(7.4989f);
	objectSizes.push_back(6.1067f);
	objectSizes.push_back(2.4618f);
	objectSizes.push_back(2.3827f);
	objectSizes.push_back(1.0f);

	//PlaySound("Zarathrustra.mp3", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
}

//std::vector<BoundingObjectClass*> objList
//list<BoundingObjectClass*> objList
//BoundingObjectClass** objArr

// Takes in a reference to a list of objects withing an octantaa
void PlanetBounce(std::vector<BoundingObjectClass*>& objects)
{
	//bool collision = false; //?

	// loop through the array of objects
	for( int i = 0; i < objects.size() - 1; i++)
	{
		for(int j = i + 1; j < objects.size(); j++){
		//We need min and maxes to be checked
		//Accessing matrix of each object in the list and making mins/maxes
	    vector3 v1Min = static_cast<vector3>(objects[i]->m_m4ToWorld * vector4(objects[i]->m_v3MinAABBG,1));
        vector3 v1Max = static_cast<vector3>(objects[i]->m_m4ToWorld * vector4(objects[i]->m_v3MaxAABBG,1));
		// i against i+1, making sure i+1 is never greater than size
		vector3 v2Min = static_cast<vector3>(objects[j]->m_m4ToWorld * vector4(objects[j]->m_v3MinAABBG,1));
        vector3 v2Max = static_cast<vector3>(objects[j]->m_m4ToWorld * vector4(objects[j]->m_v3MaxAABBG,1));

	    //vector3 v1Min = static_cast<vector3>(objects[i]->m_mAABB * vector4(objects[i]->m_v3MinAABBG,1));
        //vector3 v1Max = static_cast<vector3>(objects[i]->m_mAABB * vector4(objects[i]->m_v3MaxAABBG,1));
		//
		//vector3 v2Min = static_cast<vector3>(objects[j]->m_mAABB * vector4(objects[j]->m_v3MinAABBG,1));
        //vector3 v2Max = static_cast<vector3>(objects[j]->m_mAABB * vector4(objects[j]->m_v3MaxAABBG,1));

		//I don't think this is checking all the collisions...
		//Can't we use glm::distance to check?
		
		//collision = objects[i]->IsColliding(*objects[i+1], false); // No idea what this second parameter is
		
		bool collision = true;	
		if(v1Max.x < v2Min.x || v1Min.x > v2Max.x)
				collision = false;
			else if(v1Max.y < v2Min.y || v1Min.y > v2Max.y)
				collision = false;
			else if(v1Max.z < v2Min.z || v1Min.z > v2Max.z)
				collision = false;
		
		if(collision){
			//m_lColor[i] = m_lColor[j] = MEBLUE; //We make the Boxes blue
			objects[i]->m_bVisibleAABB = objects[j]->m_bVisibleAABB = true; //First, turn on box visibility
			objects[i]->m_v3ColorAABB = objects[j]->m_v3ColorAABB = MEBLUE; //Then, we make the Boxes blue
			//Then just increase pluto's z and have it bounce
		}

		std::cout << "Colliding?: " << collision << std::endl;
		std::cout << "Visible?: " << objects[i]->m_bVisibleAABB << std::endl;
	}
 }

}

void ApplicationClass::Update (void)
{
	m_pSystem->UpdateTime(); //Update the system
	m_pMeshMngr->SetModelMatrix(m_m4SelectedObject, m_sSelectedObject); //Setting up the Model Matrix
	m_pMeshMngr->Update(); //Update the mesh information

	static float fTotalTime = 0.0f;
	float fLapDifference = m_pSystem->StopClock();
	fTotalTime += fLapDifference;

	//Do this first
	if(m_bFPC == true)
		CameraRotation();
	
	//First Person Camera Movement
	/*if(m_bArcBall == true)
	{
		ArcBall();
		m_pMeshMngr->SetModelMatrix(m4AsteroidTrans * m4AsteroidOrient, m_sSelectedObject); //Setting up the Model Matrix
	}*/

	//Static so it holds its value each call
	static float fEarthYear = 0.0f;
	static float fMercuryDay = 0.0f; 
	static float fVenusDay = 0.0f; 
	static float fMarsDay = 0.0f; 
	static float fJupiterDay = 0.0f; 
	static float fSaturnDay = 0.0f; 
	static float fUranusDay = 0.0f; 
	static float fNeptuneDay = 0.0f;
	static float fSunDay = 0.0f;

	//Part Two
	//increment depending on the calculated time span
	fEarthYear += fLapDifference;
	fMercuryDay += fLapDifference;
	fVenusDay += fLapDifference;
	fMarsDay += fLapDifference;
	fJupiterDay += fLapDifference;
	fSaturnDay += fLapDifference;
	fUranusDay += fLapDifference;
	fNeptuneDay += fLapDifference;
	fSunDay += fLapDifference;

	//Part Three
	//Days and hours based off of Earth time, all approximations
	if(fEarthYear > 360.0f) fEarthYear = 0.0f;
	if(fMercuryDay > 58.0f) fMercuryDay = 0.0f; //58 days
	if(fVenusDay > 243.0f) fVenusDay = 0.0f; //243 days
	if(fMarsDay > 1.04f) fMarsDay = 0.0f; //25 hours
	if(fJupiterDay > 0.42f) fJupiterDay = 0.0f; //10 hours
	if(fSaturnDay > 0.46f) fSaturnDay = 0.0f; //11 hours
	if(fUranusDay > 0.71f) fUranusDay = 0.0f; //17 hours
	if(fNeptuneDay > 0.66f) fNeptuneDay = 0.0f; //16 hours
	if(fSunDay > 30.0f) fSunDay = 0.0f; //30 days
		

	//Part 4
	//Then we need to map the value to get a percentage, it goes from 0 to 28 and we need it from 0 to 1

	//Earth's calculation is easier, day will last 1 second, 1 second will be 100%
	float fEarthDayPercent = fTotalTime - static_cast<int>(fTotalTime); 

	// Y number is how many seconds it takes for 1 full rotation. LOWER NUMBERS SPIN FASTER
	float fEarthYearPercent = MapValue(fEarthYear, 0.0f, 365.0f, 0.0f, 1.0f);
	float fMercuryDayPercent = MapValue(fMercuryDay, 0.0f, 58.0f, 0.0f, 1.0f); //5.8f?
	float fVenusDayPercent = MapValue(fVenusDay, 0.0f, 243.0f, 0.0f, 1.0f); //2.43f?
	float fMarsDayPercent = MapValue(fMarsDay, 0.0f, 1.04f, 0.0f, 1.0f);
	float fJupiterDayPercent = MapValue(fJupiterDay, 0.0f, 0.42f, 0.0f, 1.0f);
	float fSaturnDayPercent = MapValue(fSaturnDay, 0.0f, 0.46f, 0.0f, 1.0f);
	float fUranusDayPercent = MapValue(fUranusDay, 0.0f, 0.71f, 0.0f, 1.0f);
	float fNeptuneDayPercent = MapValue(fNeptuneDay, 0.0f, 0.66f, 0.0f, 1.0f);
	float fSunDayPercent = MapValue(fSunDay, 0.0f, 30.0f, 0.0f, 1.0f);

	//float container = (fEarthYearPercent * 360 * PI/180) * 2; maybe we need this?
	
	/* Planet orbit speeds (relative to earth)
	mercury - 4.00000000
	venus - 1.71428572
	earth - 1.00000000
	mars - 0.52173913
	jupiter - 0.08450704
	saturn - 0.03389831
	uranus - 0.01189296
	neptune - 0.00606367 */

	/* Planet scales
	sun - 73.0000
	mercury - 0.2552
	venus - 0.6349
	earth - 0.6682
	mars - 0.3545
	jupiter - 7.4989
	saturn - 6.1067
	uranus - 2.4618
	neptune - 2.3827 */
	

#pragma region
	// 0 - SUN
	m4Sun = glm::rotate(matrix4(IDENTITY), fSunDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					 * glm::scale(15.0f, 15.0f, 15.0f);
	m_pMeshMngr->SetModelMatrix(m4Sun, "Sun");

	// 1 - MERCURY
	m4Mercury = glm::rotate(matrix4(IDENTITY), -80.0f*(fTotalTime+randStartMercury), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(18.6f, 0.0f, 0.0f) 
					* glm::rotate(matrix4(IDENTITY), fMercuryDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(0.2552f, 0.2552f, 0.2552f);
	m_pMeshMngr->SetModelMatrix(m4Mercury, "Mercury");

	// 2 - VENUS
	m4Venus = glm::rotate(matrix4(IDENTITY), -34.2857144f*(fTotalTime + randStartVenus), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(21.7f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fVenusDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					   * glm::scale(0.6349f, 0.6349f, 0.6349f);
	m_pMeshMngr->SetModelMatrix(m4Venus, "Venus");

	// 3 - EARTH
	m4Earth = glm::rotate(matrix4(IDENTITY), -20.0f*(fTotalTime + randStartEarth), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(25.3f, 0.0f, 0.0f) 
					*  glm::rotate(matrix4(IDENTITY), fEarthDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					    * glm::scale(0.6682f, 0.6682f, 0.6682f);
	m_pMeshMngr->SetModelMatrix(m4Earth, "Earth");
	
	// 4 - MARS
	m4Mars = glm::rotate(matrix4(IDENTITY), -10.4347826f*(fTotalTime + randStartMars), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(28.6f, 0.0f, 0.0f) 
					* glm::rotate(matrix4(IDENTITY), fMarsDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(0.3545f, 0.3545f, 0.3545f);
	m_pMeshMngr->SetModelMatrix(m4Mars, "Mars");

	// 5 - JUPITER
	m4Jupiter = glm::rotate(matrix4(IDENTITY), -1.6901408f*(fTotalTime + randStartJupiter), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(39.32f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fJupiterDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					 * glm::scale(7.4989f, 7.4989f, 7.4989f);
	m_pMeshMngr->SetModelMatrix(m4Jupiter, "Jupiter");

	// 6 - SATURN
	m4Saturn = glm::rotate(matrix4(IDENTITY), -0.6779662f*(fTotalTime + randStartSaturn), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(54.44f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fSaturnDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(6.1067f, 6.1067f, 6.1067f);
	m_pMeshMngr->SetModelMatrix(m4Saturn, "Saturn");

	// 7 - URANUS
	m4Uranus = glm::rotate(matrix4(IDENTITY), -0.2378592f*(fTotalTime + randStartUranus), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(65.0f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fUranusDayPercent * 360, vector3(0.0f, 1.0f, 0.0f)) 
					  * glm::scale(2.4618f, 2.4618f, 2.4618f);
	m_pMeshMngr->SetModelMatrix(m4Uranus, "Uranus");

	// 8 - NEPTUNE
	m4Neptune = glm::rotate(matrix4(IDENTITY), -0.1212734f*(fTotalTime + randStartNeptune), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(71.0f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fNeptuneDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(2.3827f, 2.3827f, 2.3827f);
	m_pMeshMngr->SetModelMatrix(m4Neptune, "Neptune");
#pragma endregion

	if(didIClick == true)
	{
		//printThing = true;
		m_m4SelectedObject = glm::translate(0.0f, 0.0f, -0.2f) * m_m4SelectedObject;
		m_pMeshMngr->SetModelMatrix(m_m4SelectedObject, m_sSelectedObject);
		PlanetBounce(planets);
		//std::cout << didIClick << std::endl;
		//std::cout << "Moving" << std::endl;]
		
	}

	//if(printThing == true)
	//{
		//std::cout << glm::to_string(m_m4SelectedObject) << std::endl;
		//system("PAUSE");
	//}
	
	//m_pMeshMngr->SetModelMatrix(m4AsteroidTrans * m4AsteroidOrient, m_sSelectedObject);
	//m_pMeshMngr->SetModelMatrix(m_pCamera->m_m4View, m_sSelectedObject);
	//m_pMeshMngr->AddAxisToQueue(m4AsteroidTrans * m4AsteroidOrient * glm::scale(vector3(3.0f)));

	//Push planets into octree
	Octants *oo = new Octants();
	bigTree *octree = new bigTree(m_pMeshMngr, planets, objectSizes);

	//Subdivide the octree
    //octree->Subdivide(oo, false);
	

	printf("FPS: %d\r", m_pSystem->FPS);//print the Frames per Second	
}

