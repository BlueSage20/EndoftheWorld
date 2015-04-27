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




OctreeSingleton *octree;

void ApplicationClass::InitUserAppVariables()
{
	//Frustum = camera view. We may need to store this as a variable
	m_pCamera->SetPosition(vector3(0.0f, 0.0f, 65.0f));
	//OctantClass *octree;

	//Create a new octree
	//The singleton class contains the Octant.h
	//It holds the octants
	//Let's get the instance of it first
	octree->GetInstance();

	//It starts out as empty
	//octree->IsEmpty = true;

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
	m_pMeshMngr->LoadModelUnthreaded("Planets\\09_Pluto.obj", "Pluto");
	//Is this where we call the Octree's "Render" method?

	/*for (int nCreepers = 0; nCreepers  < 20; nCreepers ++)
	{
		//create 20 instances of one model
		//sharing memory
		//sphericalRand give random vector of sphere with specified radius
		m_pMeshMngr->LoadModelUnthreaded("Minecraft\\MC_Creeper.obj", "Creeper", glm::translate(glm::sphericalRand(5.0f)));
	}*/
	
}
void ApplicationClass::Update (void)
{
	m_pSystem->UpdateTime(); //Update the system
	m_pMeshMngr->SetModelMatrix(m_m4SelectedObject, m_sSelectedObject); //Setting up the Model Matrix
	m_pMeshMngr->Update(); //Update the mesh information

	static float fTotalTime = 0.0f;
	float fLapDifference = m_pSystem->StopClock();
	fTotalTime += fLapDifference;

	//m4Sun = glm::rotate(matrix4(IDENTITY), -15.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(0.0f, 0.0f, 0.0f);
	//m_pMeshMngr->SetModelMatrix(m4Sun, "Sun");

	m4Mercury = glm::rotate(matrix4(IDENTITY), -27.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(3.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Mercury, "Mercury");

	m4Venus = glm::rotate(matrix4(IDENTITY), -24.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(6.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Venus, "Venus");

	m4Earth = glm::rotate(matrix4(IDENTITY), -21.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(9.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Earth, "Earth");

	m4Mars = glm::rotate(matrix4(IDENTITY), -18.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(12.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Mars, "Mars");

	m4Jupiter = glm::rotate(matrix4(IDENTITY), -15.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(15.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Jupiter, "Jupiter");

	m4Saturn = glm::rotate(matrix4(IDENTITY), -12.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(18.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Saturn, "Saturn");

	m4Uranus = glm::rotate(matrix4(IDENTITY), -9.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(21.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Uranus, "Uranus");

	m4Neptune = glm::rotate(matrix4(IDENTITY), -6.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(24.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Neptune, "Neptune");

	m4Pluto = glm::rotate(matrix4(IDENTITY), -3.0f*fTotalTime, vector3(0.0, 0.0f, 1.0f)) * glm::translate(27.0f, 0.0f, 0.0f);
	m_pMeshMngr->SetModelMatrix(m4Pluto, "Pluto");

	//push planets into octree
	//if(octree->IsEmpty)
	//{
		//Do stuff

		//At the end, set IsEmpty to "false"

	//}

	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	if(m_bArcBall == true)
	{
		ArcBall();
		m_pMeshMngr->SetModelMatrix(m_m4SelectedObject, m_sSelectedObject); //Setting up the Model Matrix
	}

	printf("FPS: %d\r", m_pSystem->FPS);//print the Frames per Second	
}

