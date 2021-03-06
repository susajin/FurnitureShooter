#include "camera.h"
#include "common.h"
#include "mydirect3d.h"
#include "input.h"
#include "sceneManagement.h"



// globals
Camera* g_pCam;
POINT g_curPos, g_fixedPos = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

// function def
void CameraInput();

// operator overload
POINT operator - (POINT o1, POINT o2) { return POINT{ o1.x - o2.x, o1.y - o2.y }; }


void InitCamera()
{
	// init camera
	g_pCam = new Camera(D3DXVECTOR3(0, 3, 0), D3DXVECTOR3(0, 0, 1));

	// init cursor pos
	g_curPos = g_fixedPos;
}

void SetCameraPos(D3DXVECTOR3 lookAt, D3DXVECTOR3 position, int rotX, int rotY, int rotZ)
{
	// look at position by setting forward vector
	g_pCam->LookAt(lookAt);

	// rotate offset pos
	D3DXMATRIX xRot, yRot, zRot;

	D3DXMatrixRotationX(&xRot, D3DXToRadian(rotX));
	D3DXMatrixRotationY(&yRot, D3DXToRadian(rotY));
	D3DXMatrixRotationZ(&zRot, D3DXToRadian(rotZ));

	D3DXVECTOR3 temp;
	D3DXVECTOR3 diff = position - lookAt;
	D3DXVec3TransformCoord(&temp, &diff, &(xRot * yRot * zRot));

	// set camera position
	g_pCam->position = lookAt + temp;
}

void UpdateCamera()
{
	g_pCam->lastPosition = g_pCam->position;

	if (!GetScene() == SCENE_TITLESCREEN)
	{
		// move camera with WASD and mouse for debug purposes
		CameraInput();
	}

	// clamp
	if (g_pCam->position.x >= 35)
	{
		g_pCam->position.x = g_pCam->lastPosition.x;
	}
	if (g_pCam->position.x <= -35)
	{
		g_pCam->position.x = g_pCam->lastPosition.x;
	}
	if (g_pCam->position.y >= 37)
	{
		g_pCam->position.y = g_pCam->lastPosition.y;
	}
	if (g_pCam->position.y <= 2)
	{
		g_pCam->position.y = g_pCam->lastPosition.y;
	}
	if (g_pCam->position.z >= 35)
	{
		g_pCam->position.z = g_pCam->lastPosition.z;
	}
	if (g_pCam->position.z <= -35)
	{
		g_pCam->position.z = g_pCam->lastPosition.z;
	}


	// init matrix and get device
	auto device = MyDirect3D_GetDevice();
	D3DXMATRIX matView, matProjection;

	// set view
	D3DXMatrixLookAtLH(&matView, &g_pCam->position, &(g_pCam->forward + g_pCam->position), &g_pCam->up);
	device->SetTransform(D3DTS_VIEW, &matView);

	// set projection
	D3DXMatrixPerspectiveFovLH(&matProjection, g_pCam->fov, g_pCam->aspect, g_pCam->nearClip, g_pCam->farClip);
	device->SetTransform(D3DTS_PROJECTION, &matProjection);
}

void UninitCamera()
{
	SAFE_DELETE(g_pCam);
}

void CameraInput()
{ 
	// camera mouse look
	GetCursorPos(&g_curPos);
	POINT diffPoint = g_curPos - g_fixedPos;

 	g_pCam->Rotate(diffPoint.x, diffPoint.y);

	// set cursor back to a fixed point
	SetCursorPos(g_fixedPos.x, g_fixedPos.y);
	g_curPos = g_fixedPos;

	// camera movement
	if (Keyboard_IsPress(DIK_W))
	{
		// move cam forward
		g_pCam->position += g_pCam->forward * g_pCam->moveSpeed;
		g_pCam->lookDirection += g_pCam->forward * g_pCam->moveSpeed;
	}
	if (Keyboard_IsPress(DIK_A))
	{
		// move cam left
		g_pCam->position += -g_pCam->right * g_pCam->moveSpeed;
		g_pCam->lookDirection += -g_pCam->right * g_pCam->moveSpeed;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		// move cam backward
		g_pCam->position += -g_pCam->forward * g_pCam->moveSpeed;
		g_pCam->lookDirection += -g_pCam->forward * g_pCam->moveSpeed;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		// move cam right
		g_pCam->position += g_pCam->right * g_pCam->moveSpeed;
		g_pCam->lookDirection += g_pCam->right * g_pCam->moveSpeed;
	}
	if (Keyboard_IsPress(DIK_Q))
	{
		// move cam up
		g_pCam->position.y += g_pCam->moveSpeed;
		g_pCam->lookDirection.y += g_pCam->moveSpeed;
	}
	if (Keyboard_IsPress(DIK_E))
	{
		// move cam down
		g_pCam->position.y += -g_pCam->moveSpeed;
		g_pCam->lookDirection.y += -g_pCam->moveSpeed;
	}
}

Camera* GetCamera()
{
	return g_pCam;
}
