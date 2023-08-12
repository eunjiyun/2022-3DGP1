//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildDefaultLightsAndMaterials()
{
	m_nLights = 4;
	m_pLights = new LIGHT[m_nLights];
	::ZeroMemory(m_pLights, sizeof(LIGHT) * m_nLights);

	m_xmf4GlobalAmbient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);

	m_pLights[0].m_bEnable = true;
	m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights[0].m_fRange = 1000.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(30.0f, 30.0f, 30.0f);
	m_pLights[0].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	m_pLights[1].m_bEnable = true;
	m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights[1].m_fRange = 500.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_fFalloff = 8.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	m_pLights[2].m_bEnable = true;
	m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_pLights[3].m_bEnable = true;
	m_pLights[3].m_nType = SPOT_LIGHT;
	m_pLights[3].m_fRange = 600.0f;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.7f, 0.0f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(50.0f, 30.0f, 30.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[3].m_fFalloff = 8.0f;
	m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(30.0f));
}

void CScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{

	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);

	BuildDefaultLightsAndMaterials();

	m_nGameObjects = 3;

	m_ppObjects = new CGameObject * [m_nGameObjects];

	CGameObject* pApacheModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/OldCar.bin");
	CApacheObject* pApacheObject = NULL;

	pApacheObject = new CApacheObject();
	pApacheObject->SetChild(pApacheModel, true);
	pApacheObject->OnInitialize();
	//22.05.29
	pApacheObject->SetPosition(+110.0f, 0.0f, 160.0f);
	//pApacheObject->SetPosition(0.0f, 0.0f, 0.0f);
	//

	//22.05.26
	pApacheObject->SetScale(8.5f, 8.5f, 8.5f);
	//pApacheObject->Rotate(0.0f, 90.0f, 0.0f);
	pApacheObject->Rotate(0.0f, 0.0f, 0.0f);
	//
	m_ppObjects[0] = pApacheObject;


	//22.05.26
	CGameObject* pMi24Model = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/Tree.bin");//5
	//CGameObject* pMi24Model = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/Tree.bin");//5
	//


	pMi24Object = new CMi24Object();// *[wallNObj];
	pMi24Object->SetChild(pMi24Model, true);
	pMi24Object->OnInitialize();


	//22.05.28

	//float fHalfWidth = 100, fHalfHeight = 20.f, fHalfDepth = 200.0f;// fHalfDepth = m_pPlayer->GetPosition().z + 200.0f;
	float fHalfWidth = 160, fHalfHeight = 1000, fHalfDepth = 1000;// fHalfDepth = m_pPlayer->GetPosition().z + 200.0f;
	pMi24Object->m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//

	//22.05.26
	pMi24Object->SetPosition(150.0f, 0.0f, 160.0f);
	//pMi24Object->SetPosition(170.0f, 20.0f, 0.0f);
	//

	//22.05.25
	pMi24Object->SetScale(4.5f, 4.5f, 4.5f);
	//pMi24Object->SetScale(50.5f, 50.5f, 50.5f);
	//
	pMi24Object->Rotate(0.0f, -90.0f, 0.0f);
	m_ppObjects[1] = pMi24Object;


	CGameObject* pGunshipModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Models/RallyCar.bin");
	CGunshipObject* pGunshipObject = NULL;

	pGunshipObject = new CGunshipObject();
	pGunshipObject->SetChild(pGunshipModel, true);
	pGunshipObject->OnInitialize();
	//22.05.25
	pGunshipObject->SetPosition(.0f, 0.0f, 160.0f);
	////pGunshipObject->SetPosition(135.0f, 140.0f, 220.0f);
	pGunshipObject->SetScale(8.5f, 8.5f, 8.5f);
	//pGunshipObject->SetScale(30.5f, 30.5f, 30.5f);
	//
	pGunshipObject->Rotate(0.0f, 180.0f, 0.0f);
	m_ppObjects[2] = pGunshipObject;
	//

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppObjects)
	{
		for (int i = 0; i < m_nGameObjects; i++) if (m_ppObjects[i]) m_ppObjects[i]->Release();
		delete[] m_ppObjects;
	}

	ReleaseShaderVariables();

	if (m_pLights) delete[] m_pLights;
}

ID3D12RootSignature* CScene::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
{
	ID3D12RootSignature* pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[3];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob* pd3dSignatureBlob = NULL;
	ID3DBlob* pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void**)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void**)&m_pcbMappedLights);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	::memcpy(m_pcbMappedLights->m_pLights, m_pLights, sizeof(LIGHT) * m_nLights);
	::memcpy(&m_pcbMappedLights->m_xmf4GlobalAmbient, &m_xmf4GlobalAmbient, sizeof(XMFLOAT4));
	::memcpy(&m_pcbMappedLights->m_nLights, &m_nLights, sizeof(int));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nGameObjects; i++) m_ppObjects[i]->ReleaseUploadBuffers();
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W': m_ppObjects[0]->MoveForward(+1.0f); break;
			//22.05.30
			//case 'S': m_ppObjects[0]->MoveForward(-1.0f); break;
			//
		case 'A': m_ppObjects[0]->MoveStrafe(-1.0f); break;
		case 'D': m_ppObjects[0]->MoveStrafe(+1.0f); break;
			//22.05.30
		//case 'Q': m_ppObjects[0]->MoveUp(+1.0f); break;
		//case 'R': m_ppObjects[0]->MoveUp(-1.0f); break;
			//
		default:
			break;
		}
		break;

	default:
		break;
	}
	return(false);
}

bool CScene::ProcessInput(UCHAR* pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	m_fElapsedTime = fTimeElapsed;

	for (int i = 0; i < m_nGameObjects; i++) m_ppObjects[i]->Animate(fTimeElapsed, NULL);

	if (m_pLights)
	{
		m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition();
		m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
	}

	//22.05.09
	srand((unsigned int)time(NULL));

	mpTime += fTimeElapsed;
	if (mpTime > 2.f)
	{
		tmp._41 = -150.f;//고정
		tmp._42 = 0.0f;//고정
		tmp._43 = m_pPlayer->GetPosition().z + 160;

		mpObjDeq.push_back(tmp);

		switch (rand() % 5 + 1)//-120 -60 0 60 120
		{
		case 1:
			obsTmp.x = 0.f;
			break;
		case 2:
			obsTmp.x = 60.0f;
			break;
		case 3:
			obsTmp.x = 120.0f;
			break;
		case 4:
			obsTmp.x = 180.0f;
			break;
		case 5:
			obsTmp.x = 240.0f;
			break;
		}
		obsTmp.y = 0.0f;
		obsTmp.z = m_pPlayer->GetPosition().z + 160;
		obsPos.push_back(obsTmp);

		mpTime = 0.f;
	}
	//

	//22.05.28
	//pMi24Object->Animate(fTimeElapsed);
	m_ppObjects[1]->Animate(fTimeElapsed);

	CheckPlayerByWallCollision();

	CheckPlayerByObjectCollisions();

	//22.05.30
	//if (true == m_pPlayer->go[0])
	/*{
		switch (m_pPlayer->track)
		{
		case 1:
			m_pPlayer->SetPosition(-60.f, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z);
			m_pPlayer->goRight = FALSE;
			break;
		case 2:
			m_pPlayer->SetPosition(0.f, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z);
			m_pPlayer->goRight = FALSE;
			break;
		case 3:
			m_pPlayer->SetPosition(60.f, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z);
			m_pPlayer->goRight = FALSE;
			break;
		case 4:
			m_pPlayer->SetPosition(120.f, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z);
			m_pPlayer->goRight = FALSE;
			break;
		}
	}*/
	//
}

void CScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbLightsGpuVirtualAddress); //Lights

	//22.05.26
	//for (int i = 0; i < m_nGameObjects-1; i++)
	//for (int i = 0; i < m_nGameObjects - 1; i++)
	//{
	if (m_ppObjects[0])
	{
		m_ppObjects[0]->Animate(m_fElapsedTime, NULL);
		m_ppObjects[0]->UpdateTransform(NULL);
		m_ppObjects[0]->Render(pd3dCommandList, pCamera);
	}
	//}
	//


	//22.05.09
	for (const XMFLOAT4X4& pos : mpObjDeq)
	{
		//m_ppObjects[1]->SetPosition(pos.x+150,pos.y,pos.z+160);
		m_ppObjects[1]->SetPosition(150, 0, pos._43);
		/*m_ppGameObjects[1]->Animate(m_fElapsedTime, NULL);
		m_ppGameObjects[1]->UpdateTransform(NULL);*/
		m_ppObjects[1]->Render(pd3dCommandList, pCamera);

		//22.05.26
		//m_ppObjects[1]->SetPosition(pos.x-150, pos.y, pos.z+160);
		m_ppObjects[1]->SetPosition(-150, 0, pos._43);
		m_ppObjects[1]->Render(pd3dCommandList, pCamera);
		//
	}

	for (const XMFLOAT3& obstacle : obsPos)
	{
		m_ppObjects[2]->SetPosition(obstacle.x, 0, obstacle.z);
		m_ppObjects[2]->Render(pd3dCommandList, pCamera);
	}
}


void CScene::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_nGameObjects; i++)
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
}


//void CScene::CheckPlayerByWallCollision()
//{
//	BoundingOrientedBox xmOOBBPlayerMoveCheck;
//	
//	//22.05.29
//	//for (const XMFLOAT4X4& pos : mpObjDeq)
//	//{
//		m_ppObjects[1]->m_xmOOBB.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&m_ppObjects[1]->m_xmf4x4World));//4x4이거 언제 변경되는지가 문제인거같은데
//		//pMi24Object->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&pos));//4x4이거 언제 변경되는지가 문제인거같은데
//		//pMi24Object->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&pos));//4x4이거 언제 변경되는지가 문제인거같은데
//		XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));
//
//		
//		if (!xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB))
//		{//if (m_ppObjects[1]->m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
//		//if (xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB))
//				//pMi24Object->SetPosition(m_pPlayer->m_xmf3Position);
//			m_pPlayer->SetPosition(0, 0, m_ppObjects[1]->GetPosition().z - 160);
//			//m_pPlayer->SetPosition(0, 0, pos._43-160);
//		}
//		cout <<boolalpha<< !xmOOBBPlayerMoveCheck.Intersects(m_pPlayer->m_xmOOBB)<< endl;
//	//}
//	//
//}



void CScene::CheckPlayerByWallCollision()
{
	if (m_pPlayer->GetPosition().x >= 160)
		m_pPlayer->SetPosition(150, 0, m_pPlayer->GetPosition().z);
	else if (m_pPlayer->GetPosition().x <= -160)
		m_pPlayer->SetPosition(-150, 0, m_pPlayer->GetPosition().z);
}

void CScene::CheckPlayerByObjectCollisions()
{
	for (const XMFLOAT3& obstacle : obsPos)
	{

		if (sqrt(pow(m_pPlayer->GetPosition().x - obstacle.x + 120, 2) + pow(m_pPlayer->GetPosition().z - obstacle.z, 2)) < 10)
		{
			if (m_pPlayer->GetPosition().x - obstacle.x + 120 > 0)
				m_pPlayer->SetPosition(m_pPlayer->GetPosition().x + 5, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z - 5);
			else
				m_pPlayer->SetPosition(m_pPlayer->GetPosition().x - 5, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z - 5);
		}
	}
}

void CMi24Object::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CGameObject::Render(pd3dCommandList, pCamera);
}
void CWallsObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CGameObject::Render(pd3dCommandList, pCamera);
}

