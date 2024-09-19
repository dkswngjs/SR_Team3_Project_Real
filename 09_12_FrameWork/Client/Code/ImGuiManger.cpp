#include "pch.h"
#include "ImGuiManger.h"
#include "Define.h"
#include "iostream"

IMPLEMENT_SINGLETON(CImGuiManger)

CImGuiManger::CImGuiManger()
	:testbool(false)
	,inttest(10)
	,floattest(5.5f)
	,m_pTerrainTexture(nullptr)
	,m_bshowTileTextureWindow(false)
	,iTileX(0)
	,iTileY(0)
	,fVtxItv(0)
	,m_bTerrainOnOff(false)
	,m_bWireFrameModeOnOff(false)
	,m_pGraphicDev(nullptr)
	,m_pMapTex(nullptr)
	,m_vecPickPos(0.f,0.f,0.f)
	,m_bImageButtonClick(false)
	,m_pCurTerrainTexture(nullptr)
	,m_bshowObjectTextrueWindow(false)
	,m_bshowInstalledObjectList(false)
{

}


CImGuiManger::~CImGuiManger()
{
}

void CImGuiManger::init()
{
	//�ʱ�ȭ �ϱ� 

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

	m_pGraphicDev = CGraphicDev::GetInstance()->Get_GraphicDev();


    ImGui_ImplWin32_Init(g_hWnd);
    ImGui_ImplDX9_Init(m_pGraphicDev);

	//ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("../TTF/Pretendard-Regular.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());


	ImGui::SetNextWindowSize(ImVec2(400, 400)); // Imgui â ũ�� 
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	

	//�̹��� ���� ��� �ֱ� 
	//L"../Bin/Resource/Texture/SkyBox/burger%d.dds

	//IDirect3DTexture9* myTexture = nullptr;

	//m_mapComponent[ID_STATIC].insert({ L"Com_Animation", pComponent });
	//m_mapTexture.insert({L"Sand_Terrain",myTexture});

	m_vecTerrainTexture.resize(14);
	m_vecObjectTexture.resize(20);

	//LoadTextureFromFile(CGraphicDev::GetInstance()->Get_GraphicDev(), "../Bin/Resource/Texture/Map/Tile1.png", &myTexture);

	for(int i=1; i<m_vecTerrainTexture.size()+1; i++)
	{

		char filePath[256];
		sprintf_s(filePath, "../Bin/Resource/Texture/Map/Tile%d.png", i-1);

		HRESULT hr = LoadTextureFromFile(CGraphicDev::GetInstance()->Get_GraphicDev(), filePath, &m_vecTerrainTexture[i-1]);
		if (FAILED(hr))
		{
			MSG_BOX("Terrain Texture load failed");
		}
	}

	char filePath[256];
	sprintf_s(filePath, "../Bin/Resource/Texture/wall.png");
	
	// ���⼭ ������ 
	HRESULT hr = LoadTextureFromFile(CGraphicDev::GetInstance()->Get_GraphicDev(), filePath, &m_vecObjectTexture[0]);
	if(FAILED(hr))
	{
		MSG_BOX("Object Texutr load Failed");
	}
	
	

}

void CImGuiManger::update()
{

	// ������Ʈ 

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Our state

	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//bool testbool = false;
	//int  inttest = 10;
	//float floattest = 5.5f;


	
	if (ImGui::Begin("Map Editor", NULL, ImGuiWindowFlags_MenuBar))
	{
		// File �޴���
		if (ImGui::BeginMenuBar())
		{
			//����..
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
					int a = 4;

				ImGui::EndMenu();
			}
			// 
			//������ End
			ImGui::EndMenuBar();
		}


		//Tile MenuBar
		if (ImGui::BeginMenuBar())
		{
			//����..
			if (ImGui::BeginMenu("Tile"))
			{
				if (ImGui::MenuItem("Tile Texture List"))
				{
					m_bshowTileTextureWindow = true;
				}

				ImGui::EndMenu();
			}
			// 
			//������ End
			ImGui::EndMenuBar();
		}


		//Terrain MenuBar
		if (ImGui::BeginMenuBar())
		{
			// Terrain ���� Ű�� 
			if (ImGui::BeginMenu("Terrain"))
			{
				if (ImGui::MenuItem("On"))
				{
					m_bTerrainOnOff = true;
				}

				else if(ImGui::MenuItem("Off"))
				{
					m_bTerrainOnOff = false; 
				}


				else if(ImGui::MenuItem("WireFrameOn"))
				{
					m_bWireFrameModeOnOff = true;
				}

				else if (ImGui::MenuItem("WireFrameOff"))
				{
					m_bWireFrameModeOnOff = false;
				}

				ImGui::EndMenu();
			}
			// 
			//������ End
			ImGui::EndMenuBar();
		}


		//Object MenuBar
		if (ImGui::BeginMenuBar())
		{
			//����..
			if (ImGui::BeginMenu("Object"))
			{
				if (ImGui::MenuItem("Object Texture List"))
				{
					m_bshowObjectTextrueWindow = true;
				}

				if (ImGui::MenuItem("Installed Objects List"))
				{
					m_bshowInstalledObjectList = true; 
				}

				ImGui::EndMenu();
			}
			// 
			//������ End
			ImGui::EndMenuBar();
		}
		

		if (!ImGui::CollapsingHeader("Setting"))
		{
			ImGui::Text(u8"��ǥ");
			ImGui::SameLine(50.0f, 0.0f);
			static float floatarray[3] = { 100.f,100.f,100.f };
			ImGui::SliderFloat3("##1", floatarray, -800.f, 800.f);
		}
			//return;

		// �� �ؿ��ٰ� ������� �߰�
		
		

		ImGui::Checkbox("Test Bool", &testbool);
		if (ImGui::Button("Click me!"))
		{
			testbool = true;
		}
		ImGui::SliderInt("Chose Int", &inttest, 1, 25);
		ImGui::SliderFloat("Chose Float", &floattest, 0.1f, 15.5f);


	}ImGui::End();


	// �߰��� ������Ʈ ����Ʈ�� ��������

	



	if (m_bshowTileTextureWindow)	
	{
		ShowTileMenuWindow();	
	}

	if (m_bshowObjectTextrueWindow)
	{
		ShowObjectMenuWindow();
	}


	if(m_bshowInstalledObjectList)
	{
		ShowInstalledObjectWindow();
	}




	ImGuiIO& io = ImGui::GetIO();
	if (!io.WantCaptureMouse)
	{
		// ImGui â �ۿ����� ���콺 �Է� ó��
		if (Engine::Get_DIMouseState(DIM_LB) & 0x80)
		{

			// ����ٰ� ���ǽ����� ������Ʈ â�� ���������� �����ϵ��� �ϸ� �ǰڴ�.
			// ���̱��� ����Ϸ�
			// ���콺 ���� �ڵ� 
			//m_vecPickPos = PickingOnTerrain();


			
		}
	}
	else
	{
		// ImGui â �ȿ����� ���콺 �Է� ó��
	}
	
	


}

void CImGuiManger::Render()
{
	ImGui::Render();	
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());	
	ImGui::EndFrame();	
}

void CImGuiManger::Release()
{
	// ������ 
}

void CImGuiManger::ShowTileMenuWindow()
{
	// Tile Texture List â ����
	if (m_bshowTileTextureWindow)
	{
		// ���ο� â ����
		ImGui::Begin("Tile Texture List", &m_bshowTileTextureWindow);
		// ���⿡ â�� ������ �߰�
		// 
		//���� â ������ �������� 
		ImVec2 CurrentWindowSize = ImGui::GetWindowSize();


		ImVec2 imageSize(100, 100);  // ����� �̹��� ũ��

		
		for (int i = 1; i < m_vecTerrainTexture.size() + 1; i++)
		{

			char label[16];
			sprintf_s(label, "Tile%d", i);
			// �̹��� ���
			//ImGui::Image((void*)m_vecTexture[i - 1], imageSize);
			if (ImGui::ImageButton(label, (void*)m_vecTerrainTexture[i - 1], imageSize)) 
			{
				// ImageButton�� Ŭ���� ��� ȣ���� �Լ�
				OnTileImageButtonClick(i);  // ����: Ŭ���� Ÿ���� �ε����� �Լ��� ����
			};

			// ���� â���� ���� ���� ���� Ȯ��
			//ImVec2 availableSpace = ImGui::GetContentRegionAvail();

			// ���� ������ �̹��� ũ�⺸�� ũ�ٸ� ���� �ٿ� �̹��� ���
			if (i % (int)(CurrentWindowSize.x/100) != 0)
			{
				ImGui::SameLine();  // ���� �ٿ� ���
			}

			else if (i % (int)(CurrentWindowSize.x/100) == 0)
			{
				// ������ �����ϸ� ���� �ٷ� �̵�
				ImGui::NewLine();
			}
		}

		ImGui::NewLine();
		//ImGui::Text("Tile Texture List Content Here");

		if (!ImGui::CollapsingHeader(u8"Ÿ�� ����"))
		{	
			
			ImGui::Text(u8"������ Ÿ���� ��� ���� �� ����");
			ImGui::NewLine();


			ImGui::PushItemWidth(100.0f);  // �ʺ� 100�ȼ��� ����
			
			ImGui::Text("Tile X");  // ���̺� ���
			ImGui::SameLine();
			ImGui::InputInt("##Tile X", &iTileX);
			ImGui::SameLine(170.0f, 0.0f);
			ImGui::Text("Tile Y");  // ���̺� ���
			ImGui::SameLine();
			ImGui::InputInt("##Tile Y", &iTileY);
			ImGui::NewLine();
			ImGui::Text(u8"�� ����");  // ���̺� ���
			ImGui::SameLine();
			ImGui::InputFloat("##VtxItv" ,&fVtxItv);

			ImGui::NewLine();	
			if(ImGui::Button(u8"��������"))
			{
				
			}
			//ImGui::PopStyleColor(3);
			ImGui::PopItemWidth();  // ������ �ʺ� ������� ����
		}


		

		ImGui::End();
	}

}

void CImGuiManger::ShowObjectMenuWindow()
{

	if (m_bshowObjectTextrueWindow)
	{
		ImGui::Begin("Object Texture List", &m_bshowObjectTextrueWindow);

		ImVec2 imageSize(100, 100);  // ����� �̹��� ũ��

		if (ImGui::ImageButton("Wall", m_vecObjectTexture[0], imageSize))
		{

			Engine::CLayer* pLayer = CLayer::Create();
			if (pLayer == nullptr)
			{
				MSG_BOX("pLayer nullptr Error");
			}


			Engine::CGameObject* pGameObject = nullptr;

			pGameObject = CObject::Create(m_pGraphicDev);
			if (pGameObject == nullptr)
			{
				MSG_BOX("CObject nullptr Error");
			}

			pLayer->Add_GameObject(L"Wall", pGameObject);

			pGameObject->SetObjectKey("Wall"); // ������Ʈ �̸� �߰��Ѱ�

			CManagement::GetInstance()->GetCurScenePtr()->GetLayerMapPtr().insert({ L"Wall" , pLayer });

		}

		//�ϴ� ������Ʈ �����غ��� 
		ImGui::End();

	}
}

void CImGuiManger::ShowInstalledObjectWindow()
{

	if(m_bshowInstalledObjectList)
	{
		ImGui::Begin("Installed Obejct List", &m_bshowInstalledObjectList);

		//���⼭ ���� ������Ʈ�� �� ��������
		map<const _tchar*, CLayer*>& mapLayer = CManagement::GetInstance()->GetCurScenePtr()->GetLayerMapPtr();
		//CManagement::GetInstance()->GetCurScenePtr()->GetLayerMapPtr()
		
		auto iter = mapLayer.begin();

		for(auto iter2 = iter->second->GetLayerGameObjectPtr().begin(); iter2 != iter->second->GetLayerGameObjectPtr().end(); iter2++)
		{
			ImGui::BulletText("%s",iter2->second->GetObjectKey());
		}

		//for (auto iter = mapLayer.begin(); iter != mapLayer.end(); iter++)
		//{
		//	
		//}


		ImGui::End();
	}



}

void CImGuiManger::OnTileImageButtonClick(int tileIndex)
{
	// ���⼭ Ÿ�� �̹����� ������ 
	// ���⼭ ���� ������ �ͼ� �ش� ���콺��ǥ�� �������ǰ� �ؾ���. 

	//m_pGraphicDev->SetTexture(0, m_vecTexture[tileIndex]);
	m_bImageButtonClick = true; 
	m_pCurTerrainTexture = m_vecTerrainTexture[tileIndex - 1];

}

_vec3 CImGuiManger::PickingOnTerrain()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse); // Ŭ���̾�Ʈ ��ǥȭ

	_vec3 vMousePos;

	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	m_pGraphicDev->GetViewport(&ViewPort);

	// �� ��Ʈ -> ����
	vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;


	// ���� -> �� �����̽� 
	_matrix matProj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

	_vec3 vRayPos, vRayDir;

	vRayPos = { 0.f, 0.f, 0.f };
	vRayDir = vMousePos - vRayPos;

	// �佺���̽� -> ���� 
	_matrix matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView); // ���⼭ ���� �䰡 ������Ʈ���ȵ�
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView); // ��ġ ���� �̵�
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	// ���� ��ǥ���� �ҰŴϱ� �ͷ����� ������ǥ ������ �����;��� 
	CMapTex* pTerrainBufferCom = dynamic_cast<CMapTex*>(Engine::Get_Component(ID_STATIC, L"Layer_GameLogic", L"Map", L"Com_Buffer"));
	if (pTerrainBufferCom == nullptr)
	{
		MSG_BOX("pTerrainBufferCom is nullptr");
	}

	CTransform* pTerrainTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", L"Map", L"Com_Transform"));
	if (pTerrainBufferCom == nullptr)
	{
		MSG_BOX("pTerrainTransCom is nullptr");
	}


	const _vec3* pTerrainTexPos = pTerrainBufferCom->Get_VtxPos(); // ���⵵ ������ ����( �� 0,0,0)�� ��������
	_vec3* pWorldTerrainTexPos = new _vec3[VTXCNTX2 * VTXCNTZ2];

	// �ͷ����� ���� ��Ʈ������ �����;��ϴµ�
	_matrix matWorld;
	//Engine::CTransform* pTerrainTransform = dynamic_cast<Engine::CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", L"Terrain", L"Com_Transform"));
	pTerrainTransCom->Get_WorldMatrix(&matWorld);


	for (int i = 0; i < VTXCNTX2 * VTXCNTZ2; i++)
	{
		D3DXVec3TransformCoord(&pWorldTerrainTexPos[i], &pTerrainTexPos[i], &matWorld);
	}

	//����� ���Ǵ��� ( ���� �׵������ ��������̹Ƿ� �״���� ���� ���;���)
	// if(*pWorldTerrainTexPos[1] == *pTerrainTexPos[1])
	//{
	//    int a = 4; 
	//}

	_ulong dwVtxId[3]{};
	_ulong dwVtexId_LeftUnder[3]{};
	_float fU, fV, fDist;

	for (_ulong i = 0; i < VTXCNTZ2 - 1; ++i)
	{
		for (_ulong j = 0; j < VTXCNTX2 - 1; ++j)
		{
			_ulong	dwIndex = i * VTXCNTX2 + j;

			// ������ ��
			dwVtxId[0] = dwIndex + VTXCNTX2;
			dwVtxId[1] = dwIndex + VTXCNTX2 + 1;
			dwVtxId[2] = dwIndex + 1;

			


			if (D3DXIntersectTri(&pWorldTerrainTexPos[dwVtxId[1]],
				&pWorldTerrainTexPos[dwVtxId[2]],
				&pWorldTerrainTexPos[dwVtxId[0]],
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{

				return _vec3(
					pWorldTerrainTexPos[dwVtxId[0]].x + fU * (pWorldTerrainTexPos[dwVtxId[1]].x - pWorldTerrainTexPos[dwVtxId[0]].x) +
					fV * (pWorldTerrainTexPos[dwVtxId[2]].x - pWorldTerrainTexPos[dwVtxId[0]].x),
					0.f, // Z ��ǥ�� �ʿ信 ���� ���
					pWorldTerrainTexPos[dwVtxId[0]].z + fU * (pWorldTerrainTexPos[dwVtxId[1]].z - pWorldTerrainTexPos[dwVtxId[0]].z) +
					fV * (pWorldTerrainTexPos[dwVtxId[2]].z - pWorldTerrainTexPos[dwVtxId[0]].z)
				);


				// �ش� �簢���� ���� �̴ϱ� �ﰢ�� 2���𿩼� ���� �簢���� ������ �����ϸ�ɵ�

				//return _vec3(pWorldTerrainTexPos[dwVtxId[1]].x + fU * (pWorldTerrainTexPos[dwVtxId[2]].x - pWorldTerrainTexPos[dwVtxId[1]].x),
				//	0.f,
				//	pWorldTerrainTexPos[dwVtxId[1]].z + fV * (pWorldTerrainTexPos[dwVtxId[0]].z - pWorldTerrainTexPos[dwVtxId[1]].z));


				//Test (�簢���� ���� ��ǥ ����) 
				//return _vec3(pWorldTerrainTexPos[dwVtxId[0]].x+0.5f, 0.f, pWorldTerrainTexPos[dwVtxId[0]].z-0.5f);
			}

			// ���� �Ʒ�
			dwVtxId[0] = dwIndex + VTXCNTX2;
			dwVtxId[1] = dwIndex + 1;
			dwVtxId[2] = dwIndex;

			


			if (D3DXIntersectTri(&pWorldTerrainTexPos[dwVtxId[2]],
				&pWorldTerrainTexPos[dwVtxId[0]],
				&pWorldTerrainTexPos[dwVtxId[1]],
				&vRayPos, &vRayDir, &fU, &fV, &fDist))
			{
				// V1 + U(V2 - V1) + V(V3 - V1)
				return _vec3(
					pWorldTerrainTexPos[dwVtxId[0]].x + fU * (pWorldTerrainTexPos[dwVtxId[1]].x - pWorldTerrainTexPos[dwVtxId[0]].x) +
					fV * (pWorldTerrainTexPos[dwVtxId[2]].x - pWorldTerrainTexPos[dwVtxId[0]].x),
					0.f, // Z ��ǥ�� �ʿ信 ���� ���
					pWorldTerrainTexPos[dwVtxId[0]].z + fU * (pWorldTerrainTexPos[dwVtxId[1]].z - pWorldTerrainTexPos[dwVtxId[0]].z) +
					fV * (pWorldTerrainTexPos[dwVtxId[2]].z - pWorldTerrainTexPos[dwVtxId[0]].z)
				);
	


				//return _vec3(pWorldTerrainTexPos[dwVtxId[2]].x + fU * (pWorldTerrainTexPos[dwVtxId[0]].x - pWorldTerrainTexPos[dwVtxId[2]].x),
				//	0.f,
				//	pWorldTerrainTexPos[dwVtxId[2]].z + fV * (pWorldTerrainTexPos[dwVtxId[1]].z - pWorldTerrainTexPos[dwVtxId[2]].z));
			}
		}
	}

	return _vec3(0.f, 0.f, 0.f);
}


//IDirect3DTexture9* CImGuiManger::FindTexture(wstring _wstr, map<wstring, IDirect3DTexture9*> _map)
//{
//
//	//auto iter = m_mapTexture.find(_wstr);	
//	//
//	//if (iter == m_mapTexture.end())
//	//{
//	//	MSG_BOX("no that texutre insert at m_mapTexture");
//	//}
//	//
//	//else if (iter != m_mapTexture.end())
//	//{
//	//	return iter->second;
//	//}
//
//
//	
//}


