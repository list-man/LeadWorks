#include "App.h"

using namespace Leadwerks;

App::App() : window(NULL), context(NULL), world(NULL), camera(NULL) {}

App::~App() { delete world; delete window; }

bool App::Start()
{
	//Create a window
	window = Window::Create("Tutorial09ThridPersonCharacterControl");
	
	//Create a context
	context = Context::Create(window);
	
	//Create a world
	world = World::Create();
	
	//Create a camera
	camera = Camera::Create();
	camera->Move(0,2,-5);
	
	//Hide the mouse cursor
	window->HideMouse();
	
	std::string mapname = System::GetProperty("map","Maps/start.map");
	Map::Load(mapname);
	
	//Move the mouse to the center of the screen
	window->SetMousePosition(context->GetWidth()/2,context->GetHeight()/2);

	Initialize();
	
	return true;
}

bool App::Loop()
{
	//Close the window to end the program
	if (window->Closed() || window->KeyHit(Key::Escape)) {
		return false;
	}

	if (window->KeyHit(Key::C)) {
		mCrouched = !mCrouched;
	}

	if (window->KeyHit(Key::P)) {
		mFreelookmode = !mFreelookmode;
	}

	// do camera rotation.
	Vec3 curMousePositon = window->GetMousePosition();
	Vec2 mouseDifference = Vec2(curMousePositon.x - mViewCenterPos.x, curMousePositon.y - mViewCenterPos.y);

	float UpDownRotation = mCameraRotation.x + mouseDifference.y / mMouseSensitivity;
	mCameraRotation.y += mouseDifference.x / mMouseSensitivity;
	mCameraRotation.x = min(max(UpDownRotation, mMaxTopAngle), mMaxBottomAngle);
	mFPSPivot->SetRotation(mCameraRotation);

	// do movement.
	Vec3 playerMovement;
	playerMovement.x = (window->KeyDown(Key::D) - window->KeyDown(Key::A)) * Time::GetSpeed() * mStrafeForce;
	playerMovement.y = (window->KeyDown(Key::E) - window->KeyDown(Key::Q)) * Time::GetSpeed() * mStrafeForce;
	playerMovement.z = (window->KeyDown(Key::W) - window->KeyDown(Key::S)) * Time::GetSpeed() * mMoveForce;
	mFPSPivot->Move(playerMovement);

	// set camera at correct height and playerPosition.
	mPlayerPivot->SetInput(mCameraRotation.y, playerMovement.z, playerMovement.x, 0);

	// store player some information.
	Vec3 fpsPos = mFPSPivot->GetPosition();
	Vec3 playerPos = mPlayerPivot->GetPosition();
	playerPos.y += (mCrouched ? mPlayerCrouchHeight:mPlayerHeight);
	fpsPos.y = Math::Curve(playerPos.y, fpsPos.y, mCamSmoothing * Time::GetSpeed());
	fpsPos = Vec3(playerPos.x, fpsPos.y, playerPos.z);
	mFPSPivot->SetPosition(fpsPos);

	camera->SetPosition(mFPSPivot->GetPosition());
	camera->SetRotation(mFPSPivot->GetRotation());

	mThirdPSPivot->SetRotation(mFPSPivot->GetRotation());
	mThirdPSPivot->SetPosition(mFPSPivot->GetPosition());
	mThirdPSPivot->Move(0, 0, mMaxCamOffset, false);
	camera->SetPosition(mThirdPSPivot->GetPosition());

	// restore mouse position the center of view.
	window->SetMousePosition(mViewCenterPos.x, mViewCenterPos.y);

	Time::Update();
	world->Update();
	world->Render();
	context->Sync(false);

	return true;
}

//////////////////////////////////////////////////////////////////////////
// protected member functions.
void App::Initialize()
{
	mMouseSensitivity = 15.0f;

	mStrafeForce = 0.2f;
	mMoveForce = 0.3f;

	mMaxTopAngle = -45.0f;
	mMaxBottomAngle = 80.0f;

	mCrouched = false;
	mPlayerHeight = 1.8f;
	mPlayerCrouchHeight = 0.8f;
	mCamSmoothing = 8.0f;

	mMinCamOffset = 1.5f;
	mMaxCamOffset = -8.0f;

	mViewCenterPos = Vec2(window->GetWidth() / 2, window->GetHeight() / 2);

	mFreelookmode = false;

	// create camera pivot.
	mFPSPivot = Pivot::Create();
	mThirdPSPivot = Pivot::Create();

	// create player pivot. a pivot is an invisible entity with no special characteristics.
	mPlayerPivot = Pivot::Create();
	mPlayerPivot->SetPosition(0, 4, 0);
	mPlayerPivot->SetMass(5);
	mPlayerPivot->SetPhysicsMode(Entity::CharacterPhysics);

	// create a visible mesh.
	mPlayerMesh = Model::Cylinder(16, mFPSPivot);
	mPlayerMesh->SetPosition(0, 1, 0);
	mPlayerMesh->SetScale(1, 2, 1);
}

void App::UnInitialize()
{

}
