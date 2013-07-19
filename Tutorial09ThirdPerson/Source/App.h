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
	float	mMouseSensitivity;	//������ת������ж�
	float	mStrafeForce;		//�����ƶ�������
	float	mMoveForce;			//ǰ�����˵�����
	
	float	mMaxTopAngle;		//����������ǽǶ�
	float	mMaxBottomAngle;	//������󸩽ǽǶ�

	bool	mFreelookmode;
	Model*	mPlayerMesh;

	bool	mCrouched;
	float	mPlayerHeight;
	float	mPlayerCrouchHeight;
	float	mCamSmoothing;

	float	mMaxCamOffset;
	float	mMinCamOffset;
};
