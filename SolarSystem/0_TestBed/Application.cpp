#include "ApplicationClass.h"

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
float randStartPluto;
void ApplicationClass::InitUserAppVariables()
{
	randStartMercury = rand();
	randStartVenus = rand();
	randStartEarth = rand();
	randStartMars = rand();
	randStartJupiter = rand();
	randStartSaturn = rand();
	randStartUranus = rand();
	randStartNeptune = rand();
	randStartPluto = rand();
	//Frustum = camera view. We MAY need to store this as a variable
	m_pCamera->SetPosition(vector3(0.0f, 0.0f, 65.0f));
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

	//m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Steve.obj", "Steve");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\01_Mercury.obj", "Mercury");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\02_Venus.obj", "Venus");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\04_Mars.obj", "Mars");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\05_Jupiter.obj", "Jupiter");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\06_Saturn.obj", "Saturn");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\07_Uranus.obj", "Uranus");
	m_pMeshMngr->LoadModelUnthreaded("Planets\\08_Neptune.obj", "Neptune");
	//m_pMeshMngr->LoadModelUnthreaded("Planets\\09_Pluto.obj", "Pluto");
	//Is this where we call the Octree's "Render" method?
	
}
void ApplicationClass::Update (void)
{
	m_pSystem->UpdateTime(); //Update the system
	m_pMeshMngr->SetModelMatrix(m_m4SelectedObject, m_sSelectedObject); //Setting up the Model Matrix
	m_pMeshMngr->Update(); //Update the mesh information

	static float fTotalTime = 0.0f;
	float fLapDifference = m_pSystem->StopClock();
	fTotalTime += fLapDifference;

	//Moon's day will last 28 seconds, 28 seconds will be 100%
	//static float fMoonDay = 0.0f; Static so it holds its value each call
	static float fMercuryDay = 0.0f; 
	static float fVenusDay = 0.0f; 
	static float fMarsDay = 0.0f; 
	static float fJupiterDay = 0.0f; 
	static float fSaturnDay = 0.0f; 
	static float fUranusDay = 0.0f; 
	static float fNeptuneDay = 0.0f; 
	static float fPlutoDay = 0.0f; 
	static float fEarthYear = 0.0f;

	//Part Two
	//fMoonDay += fLapDifference; increment depending on the calculated time span
	fMercuryDay += fLapDifference;
	fVenusDay += fLapDifference;
	fMarsDay += fLapDifference;
	fJupiterDay += fLapDifference;
	fSaturnDay += fLapDifference;
	fUranusDay += fLapDifference;
	fNeptuneDay += fLapDifference;
	fPlutoDay += fLapDifference;
	fEarthYear += fLapDifference;

	//Part Three
	//Days and hours based off of Earth time, all approximations
	/*if(fMoonDay > 28.0f)
		fMoonDay = 0.0f;*/
	if(fMercuryDay > 58.0f) //58 days
		fMercuryDay = 0.0f;
	if(fVenusDay > 243.0f) //243 days
		fVenusDay = 0.0f;
	if(fMarsDay > 1.04f) //25 hours
		fMarsDay = 0.0f;
	if(fJupiterDay > 0.42f) //10 hours
		fJupiterDay = 0.0f;
	if(fSaturnDay > 0.46f) //11 hours
		fSaturnDay = 0.0f;
	if(fUranusDay > 0.71f) //17 hours
		fUranusDay = 0.0f;
	if(fNeptuneDay > 0.66f) //16 hours
		fNeptuneDay = 0.0f;
	if(fPlutoDay > 6.0f) //6 days
		fPlutoDay = 0.0f;
	if(fEarthYear > 360.0f)
		fEarthYear = 0.0f;

	//Part 4
	//Then we need to map the value to get a percentage, it goes from 0 to 28 and we need it from 0 to 1
	//float fMoonDayPercent = MapValue( fMoonDay, 0.0f, 28.0f, 0.0f, 1.0f);

	//Earth's calculation is easier, day will last 1 second, 1 second will be 100%
	float fEarthDayPercent = fTotalTime - static_cast<int>(fTotalTime); 

	// Y number is how many seconds it takes for 1 full rotation. LOWER NUMBERS SPIN FASTER
	float fEarthYearPercent = MapValue( fEarthYear, 0.0f, 365.0f, 0.0f, 1.0f);

	float fMercuryDayPercent = MapValue( fMercuryDay, 0.0f, 5.8f, 0.0f, 1.0f);
	//
	float fVenusDayPercent = MapValue( fVenusDay, 0.0f, 2.43f, 0.0f, 1.0f);
	//
	float fMarsDayPercent = MapValue( fMarsDay, 0.0f, 1.04f, 0.0f, 1.0f);
	//
	float fJupiterDayPercent = MapValue( fJupiterDay, 0.0f, 0.42f, 0.0f, 1.0f);
	//
	float fSaturnDayPercent = MapValue( fSaturnDay, 0.0f, 0.46f, 0.0f, 1.0f);
	//
	float fUranusDayPercent = MapValue( fUranusDay, 0.0f, 0.71f, 0.0f, 1.0f);
	//
	float fNeptuneDayPercent = MapValue( fNeptuneDay, 0.0f, 0.66f, 0.0f, 1.0f);
	//
	float fPlutoDayPercent = MapValue( fPlutoDay, 0.0f, 6.0f, 0.0f, 1.0f);
	//
	//float container = (fEarthYearPercent * 360 * PI/180) * 2; maybe we need this?
	
	//I have to do this shit all over again
	//Earth translations 
	float EarthTranslationX = 6 * (glm::cos(fEarthYearPercent * 360 *  ((PI/180)))); 
	float EarthTranslationZ = 6 * (glm::sin(fEarthYearPercent * 360 * ((PI/180))));
	//
	float MarsTranslationX = 10 * (glm::cos(fMarsDayPercent * (360 *  ((PI/180))))); 
	float MarsTranslationZ = 10 * (glm::sin(fMarsDayPercent * (360 * ((PI/180)))));
	//
	float JupiterTranslationX = 18 * (glm::cos(fJupiterDayPercent * (360 *  ((PI/180))))); 
	float JupiterTranslationZ = 18 * (glm::sin(fJupiterDayPercent * (360 * ((PI/180)))));
	//
	float SaturnTranslationX = 21 * (glm::cos(fSaturnDayPercent * (360 *  ((PI/180))))); 
	float SaturnTranslationZ = 21 * (glm::sin(fSaturnDayPercent * (360 * ((PI/180)))));
	//
	float UranusTranslationX = 25 * (glm::cos(fUranusDayPercent * (360 *  ((PI/180))))); 
	float UranusTranslationZ = 25 * (glm::sin(fUranusDayPercent * (360 * ((PI/180)))));
	//
	float NeptuneTranslationX = 30 * (glm::cos(fNeptuneDayPercent * (360 *  ((PI/180))))); 
	float NeptuneTranslationZ = 30 * (glm::sin(fNeptuneDayPercent * (360 * ((PI/180)))));
	//
	float PlutoTranslationX = 33 * (glm::cos(fPlutoDayPercent * (360 *  ((PI/180))))); 
	float PlutoTranslationZ = 33 * (glm::sin(fPlutoDayPercent * (360 * ((PI/180)))));

	
	//m4Mercury = glm::rotate(m4Mercury, fMercuryDayPercent, vector3(1.0, 1.0f, 0.0f)) * glm::translate(3.0f, 0.0f, 0.0f);
	m4Mercury = glm::rotate(matrix4(IDENTITY), -27.0f*(fTotalTime+randStartMercury), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(3.6f, 0.0f, 0.0f) 
					* glm::rotate(matrix4(IDENTITY), fMercuryDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(0.29f, 0.29f, 0.29f);
	m_pMeshMngr->SetModelMatrix(m4Mercury, "Mercury");

	//m4Venus = glm::rotate(m4Venus, fVenusDayPercent, vector3(1.0, 1.0f, 0.0f)) * glm::translate(6.0f, 0.0f, 0.0f);
	m4Venus = glm::rotate(matrix4(IDENTITY), -24.0f*(fTotalTime + randStartVenus), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(6.7f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fVenusDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					   * glm::scale(0.71f, 0.71f, 0.71f);
	m_pMeshMngr->SetModelMatrix(m4Venus, "Venus");

	//m4Earth = glm::rotate(m4Earth, fEarthDayPercent, vector3(1.0, 1.0f, 0.0f)) * glm::translate(9.0f, 0.0f, 0.0f);

	//m4Earth = glm::translate(EarthTranslationX, 0.0f, EarthTranslationZ);
	//m4Earth = glm::rotate(m4Earth, fEarthDayPercent * 360, vector3(0.0f, 1.0f, 0.0f));

	m4Earth = glm::rotate(matrix4(IDENTITY), -21.0f*(fTotalTime + randStartEarth), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(9.3f, 0.0f, 0.0f) 
					*  glm::rotate(matrix4(IDENTITY), fEarthDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					    * glm::scale(0.75f, 0.75f, 0.75f);
	m_pMeshMngr->SetModelMatrix(m4Earth, "Earth");
	

	//m4Mars = glm::rotate(m4Mars, fMarsDayPercent, vector3(0.0f, 1.0f, 0.0f)); //negative % time 360
	m4Mars = glm::rotate(matrix4(IDENTITY), -18.0f*(fTotalTime + randStartMars), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(14.1f, 0.0f, 0.0f) 
					* glm::rotate(matrix4(IDENTITY), fMarsDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(0.4f, 0.4f, 0.4f);
	m_pMeshMngr->SetModelMatrix(m4Mars, "Mars");


	//m4Jupiter = glm::rotate(m4Jupiter, fJupiterDayPercent, vector3(0.0f, 1.0f, 0.0f));
	m4Jupiter = glm::rotate(matrix4(IDENTITY), -15.0f*(fTotalTime + randStartJupiter), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(19.32f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fJupiterDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					 * glm::scale(7.4f, 7.4f, 7.4f);
	m_pMeshMngr->SetModelMatrix(m4Jupiter, "Jupiter");

	
	//m4Saturn = glm::rotate(m4Saturn, fSaturnDayPercent, vector3(0.0f, 1.0f, 0.0f));
	m4Saturn = glm::rotate(matrix4(IDENTITY), -12.0f*(fTotalTime + randStartSaturn), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(35.44f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fSaturnDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(6.08f, 6.08f, 6.08f);
	m_pMeshMngr->SetModelMatrix(m4Saturn, "Saturn");

	
	//m4Uranus = glm::rotate(m4Uranus, fUranusDayPercent, vector3(0.0f, 1.0f, 0.0f));
	m4Uranus = glm::rotate(matrix4(IDENTITY), -9.0f*(fTotalTime + randStartUranus), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(50.0f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fUranusDayPercent * 360, vector3(0.0f, 1.0f, 0.0f)) 
					  * glm::scale(3.0f, 3.0f, 3.0f);
	m_pMeshMngr->SetModelMatrix(m4Uranus, "Uranus");


	//m4Neptune = glm::rotate(m4Neptune, fNeptuneDayPercent, vector3(0.0f, 1.0f, 0.0f));
	m4Neptune = glm::rotate(matrix4(IDENTITY), -6.0f*(fTotalTime + randStartNeptune), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(60.0f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fNeptuneDayPercent * 360, vector3(0.0f, 1.0f, 0.0f))
					  * glm::scale(2.91f, 2.91f, 2.91f);
	m_pMeshMngr->SetModelMatrix(m4Neptune, "Neptune");

	//Do we need Pluto?
	/*m4Pluto = glm::rotate(matrix4(IDENTITY), -3.0f*(fTotalTime + randStartPluto), vector3(0.0, 0.0f, 1.0f)) 
				* glm::translate(27.0f, 0.0f, 0.0f)
					* glm::rotate(matrix4(IDENTITY), fPlutoDayPercent * 360, vector3(0.0f, 1.0f, 0.0f));
	m_pMeshMngr->SetModelMatrix(m4Pluto, "Pluto");*/

	//push planets into octree
	/*for(int i = 0; i < baby->m_lBoundingObject.size; i++)
	{
		//Do stuff
		baby->m_lBoundingObject[0] = m_pMeshMngr->LoadModelUnthreaded("Planets\\03_Earth.obj", "Earth");

		//At the end, set IsEmpty to "false". I guess I can't access baby->m_bEmpty

	}*/
	//octree->GenerateOctree(baby->m_lBoundingObject, 4, 2);

	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	if(m_bArcBall == true)
	{
		ArcBall();
		//m_pMeshMngr->SetModelMatrix(m_m4SelectedObject, m_sSelectedObject); //Setting up the Model Matrix
	}

	printf("FPS: %d\r", m_pSystem->FPS);//print the Frames per Second	
}

