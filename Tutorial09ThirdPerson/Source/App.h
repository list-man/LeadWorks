#pragma once
#include "Leadwerks.h"

using namespace Leadwerks;

class App
{
public:
	Window* window;
	Context* context;
	World* world;
	Camera* camera;

	App();
	virtual ~App();
	
    virtual bool Start();
    virtual bool Loop();

protected:
	void Initialize();
	void UnInitialize();
protected:
	Vec3	mCameraRotation;
	Vec2	mViewCenterPos;
	Pivot*	mFPSPivot;
	Pivot*	mThirdPSPivot;
	Pivot*	mPlayerPivot;
	float	mMouseSensitivity;	//鼠标控制转向的敏感度
	float	mStrafeForce;		//左右移动的力度
	float	mMoveForce;			//前进后退的力度
	
	float	mMaxTopAngle;		//向上最大仰角角度
	float	mMaxBottomAngle;	//向下最大俯角角度

	bool	mFreelookmode;
	Model*	mPlayerMesh;

	bool	mCrouched;
	float	mPlayerHeight;
	float	mPlayerCrouchHeight;
	float	mCamSmoothing;

	float	mMaxCamOffset;
	float	mMinCamOffset;
};
