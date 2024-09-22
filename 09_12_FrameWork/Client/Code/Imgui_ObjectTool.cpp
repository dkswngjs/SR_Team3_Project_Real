#include "pch.h"
#include "Imgui_ObjectTool.h"
#include "GraphicDev.h"
#include "Object.h"
#include "Define.h"
#include <sstream>
#include <commdlg.h>
#include <cwctype>
#include <cstring>


IMPLEMENT_SINGLETON(CImgui_ObjectTool);


CImgui_ObjectTool::CImgui_ObjectTool()
	: m_bShowObjectWindow(false)
	, m_bShowInstallObjectWindow(false)
	, m_pCurObjectTransform(nullptr)
	, m_sCurTextureData(L"")
	, m_sCurTextureKey(L"")
	, m_vecPickPos(0.f,0.f,0.f)
	, m_strCurObjectName(L"")
	, index(0)
	, deleteCount(0)
	, m_wCurReadTextureKey(L"Test")
{

}

CImgui_ObjectTool::~CImgui_ObjectTool()
{

}


wstring StringToTChar(const std::string& str)
{
	wstring wstr;
	wstr.assign(str.begin(), str.end());

	return wstr;
}


string WstringTostring(const std::wstring& wstr)
{
	string str;
	str.assign(wstr.begin(), wstr.end());

	return str;
}


std::wstring extractNumber(const std::wstring& input) {
	std::wstring result;
	for (wchar_t ch : input) {
		if (iswdigit(ch)) {
			result += ch; // �����̸� result�� �߰�
		}
	}
	return result;
}

std::wstring removeDigits(const std::wstring& input) {
	std::wstring result;
	for (wchar_t wch : input) {
		if (!std::iswdigit(wch)) {  // ���ڰ� �ƴ� ���
			result += wch;
		}
	}
	return result;
}

const wchar_t* findInVector(const std::vector<const wchar_t*>& vec, const wchar_t* target) {
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (wcscmp(*it, target) == 0) {  // ���� ��
			return *it;  // ��ġ�ϴ� ��� ��ȯ
		}
	}
	return nullptr;  // ��ġ�ϴ� ��Ұ� ���� ���
}

void CImgui_ObjectTool::init()
{
	m_vecObjectTexture.resize(20);
	//m_vecObjectList.resize(100);
	

	char filePath[256];
	sprintf_s(filePath, "../Bin/Resource/Texture/wall.png");

	// ���⼭ ������ 
	HRESULT hr = LoadTextureFromFile(CGraphicDev::GetInstance()->Get_GraphicDev(), filePath, &m_vecObjectTexture[0]);
	if (FAILED(hr))
	{
		MSG_BOX("Object Texutr load Failed");
	}

}

void CImgui_ObjectTool::update()
{

	if (ImGui::BeginMenuBar())
	{
		//����..
		if (ImGui::BeginMenu("Object"))
		{
			if (ImGui::MenuItem("Object Texture List"))
			{
				m_bShowObjectWindow = true;
			}

			if (ImGui::MenuItem("Installed Objects List"))
			{
				m_bShowInstallObjectWindow = true;
			}

			ImGui::EndMenu();
		}
		// 
		//������ End
		ImGui::EndMenuBar();
	}


	if(m_bShowObjectWindow)
	{
		ShowObjectWindow();	
		static bool wasLeftButtonDown = false;

		ImGuiIO& io = ImGui::GetIO();
		if (!io.WantCaptureMouse)
		{
			// ImGui â �ۿ����� ���콺 �Է� ó��
			if (LONG mouseState = Engine::Get_DIMouseState(DIM_LB) & 0x80)
			{
				// ����ٰ� ���ǽ����� ������Ʈ â�� ���������� �����ϵ��� �ϸ� �ǰڴ�.
				// ���̱��� ����Ϸ�
				// ���콺 ���� �ڵ� 
				

				 //= Get_DIMouseState(DIM_LB);	

				if (mouseState & 0x80) // ���콺 ���� ��ư�� ���ȴٸ�
				{
					// ���� ���°� ������ �ʾ��� ���� ó��
					if (!wasLeftButtonDown)
					{
						// Ŭ�� �̺�Ʈ ó��
						// ���⿡�� ���ϴ� �۾� ����
						m_vecPickPos = PickingOnTerrain();
						InstallObject(m_sCurTextureKey,m_strCurObjectName,m_sCurTextureData);

						m_pCurObjectTransform = dynamic_cast<CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", m_vecObjectList.back(), L"Com_Transform"));
						if (m_pCurObjectTransform == nullptr)
						{
							MSG_BOX("m_pCurObjectTransform is nullptr");
							//m_pCurObjectTransform = dynamic_cast<CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Imgui_Object1", m_strCurObjectName, L"Com_Transform"));
							//if (m_pCurObjectTransform == nullptr)
							//{
							//	MSG_BOX("m_pCurObjectTransform is nullptr");
							//}
						}

						if (m_pCurObjectTransform != nullptr)
							m_pCurObjectTransform->Set_Pos(m_vecPickPos.x, 0, m_vecPickPos.z);

						
					}

					// ���� ���¸� ������Ʈ
					wasLeftButtonDown = true;
					
				}
			}

			else
			{
				// ��ư�� ������ ������ ���¸� ������Ʈ
				wasLeftButtonDown = false;
			}
		}
		else
		{
			// ImGui â �ȿ����� ���콺 �Է� ó��
		}
	}

	if(m_bShowInstallObjectWindow)
	{
		ShowInstalledObjectWindow();

	}


	
}

void CImgui_ObjectTool::render()
{

}

void CImgui_ObjectTool::ShowObjectWindow()
{

	if (m_bShowObjectWindow)
	{
		ImGui::Begin("Object Texture List", &m_bShowObjectWindow);

		ImVec2 imageSize(100, 100);  // ����� �̹��� ũ��

		if (ImGui::ImageButton("Wall", m_vecObjectTexture[0], imageSize))
		{

			//���Ⱑ ������ 
			m_sCurTextureData  = L"Wall";
			m_sCurTextureKey   = L"Wall";
			m_strCurObjectName = L"Wall";

		}

		//�ϴ� ������Ʈ �����غ��� 
		ImGui::End();

	}

}

void CImgui_ObjectTool::ShowInstalledObjectWindow()
{
	if (m_bShowInstallObjectWindow)
			{
				ImGui::Begin("Installed Obejct List", &m_bShowInstallObjectWindow);
		
				ImGui::BeginChild("LeftChild", ImVec2(200, 0), true); // ���� 200, ���� �ڵ�(ä��), �׵θ� ����
				ImGui::Text("Installed Obejct");

				//���⼭ ���� ������Ʈ�� �� ��������
				map<const _tchar*, CLayer*>& mapLayer = CManagement::GetInstance()->GetCurScenePtr()->GetLayerMapPtr();
				//CManagement::GetInstance()->GetCurScenePtr()->GetLayerMapPtr()

				for (auto iter = mapLayer.begin(); iter != mapLayer.end(); ++iter)
				{
					const _tchar* layerKey = iter->first;

					if (_tcscmp(layerKey, _T("Layer_GameLogic")) == 0)
					{
						for (auto objectIter = iter->second->GetLayerGameObjectPtr().begin(); objectIter != iter->second->GetLayerGameObjectPtr().end(); ++objectIter)
						{
							//if(ImGui::Selectable())

							
							//if (ImGui::Selectable(objectIter->second->GetObjectKey().c_str()))
							if(ImGui::Selectable(WstringTostring(objectIter->second->GetObjectKey()).c_str()))
							{
								// Ŭ�� �� ó���� ����
								for(auto iter = m_vecObjectList.begin(); iter!= m_vecObjectList.end(); iter++)
								{
									if(wcscmp(*iter,objectIter->second->GetObjectKey().c_str())==0)
									{
										// �׷� ����ٰ� ã���װ� �־����� 
										CurClickObject = *iter;	
									}
								}

								// ���⼭ ������
								m_pCurObjectTransform = dynamic_cast<CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", CurClickObject, L"Com_Transform"));	

								if (m_pCurObjectTransform == nullptr)
								{
									MSG_BOX("m_pCurObjectTransform is nullptr");
								}
							}
						}
					}
				}
				ImGui::EndChild();

				ImGui::SameLine(); // ���� �ٿ� ���� ��Ҹ� ��ġ�ϱ� ���� ���

				ImGui::BeginChild("RightChild", ImVec2(300, 0), true);
				ImGui::Text("Control Scale and Pos");

				if (!ImGui::CollapsingHeader("Setting"))	
				{
					if (m_pCurObjectTransform != nullptr)
					{
					
						if (m_pPreObjectTransform != m_pCurObjectTransform) {
							floatPosArrayTest[0] = m_pCurObjectTransform->Get_WorldMatrix()->_41;
							floatPosArrayTest[1] = m_pCurObjectTransform->Get_WorldMatrix()->_42;
							floatPosArrayTest[2] = m_pCurObjectTransform->Get_WorldMatrix()->_43;
							//m_pPreObjectTransform = m_pCurObjectTransform; // ���� Transform ������Ʈ
						}
						ImGui::Text(u8"��ġ ��ǥ");
						ImGui::SameLine(50.0f, 0.0f);
						
						ImGui::SliderFloat3("##1", floatPosArrayTest, 0.f, 10000.f);

						//static	float floatPosArray[3] = { m_pCurObjectTransform->Get_WorldMatrix()->_41,m_pCurObjectTransform->Get_WorldMatrix()->_42, m_pCurObjectTransform->Get_WorldMatrix()->_43 };
						//ImGui::SliderFloat3("##1", floatPosArray, 0.f, 10000.f);
						
						m_pCurObjectTransform->Set_Pos(floatPosArrayTest[0], floatPosArrayTest[1], floatPosArrayTest[2]);

						// ���� �����������̶� �Է��� ���ξȵ�
						ImGui::BeginChild("TestChild", ImVec2(200, 200), true);
						ImGui::Text(u8"ȸ��");
						//if (m_pPreObjectTransform != m_pCurObjectTransform)
						//{
						//	
						//}m_pPreObjectTransform != m_pCurObjectTransform
						if (m_pPreObjectTransform != m_pCurObjectTransform)
						{
							floatRotationArray[0] = m_pCurObjectTransform->Rotation_x;
							floatRotationArray[1] = m_pCurObjectTransform->Rotation_y;
							floatRotationArray[2] = m_pCurObjectTransform->Rotation_z;

							prevRotationArray[0] = m_pCurObjectTransform->Rotation_x;
							prevRotationArray[1] = m_pCurObjectTransform->Rotation_y;
							prevRotationArray[2] = m_pCurObjectTransform->Rotation_z;

							m_pPreObjectTransform = m_pCurObjectTransform;
						}
						//static float floatRotationArray[3] = { 0.f,0.f,0.f };
						//static float prevRotationArray[3] = { 0.f, 0.f, 0.f }; // ���� ȸ���� �����

						ImGui::SliderFloat3("##1", floatRotationArray, 0.f, 360.f);


						//���� ������Ʈ�� ���Ƽ� ��� ȸ���ϰԵ� �̷��� ��� ��������� �����ϱ� 
						//m_pTransformCom->Rotation(ROT_X, 90.f * 3.14f / 180.f);


						// x�� ȸ��
						if (floatRotationArray[0] != prevRotationArray[0])
						{
							m_pCurObjectTransform->Rotation(ROT_X, -prevRotationArray[0] * 3.14f / 180.f);
							m_pCurObjectTransform->Rotation(ROT_X, floatRotationArray[0] * 3.14f / 180.f);

							m_pCurObjectTransform->Rotation_x = floatRotationArray[0];
							prevRotationArray[0] = floatRotationArray[0];
						}

						// y�� ȸ��	
						if (floatRotationArray[1] != prevRotationArray[1])
						{
							m_pCurObjectTransform->Rotation(ROT_Y, -prevRotationArray[1] * 3.14f / 180.f);
							m_pCurObjectTransform->Rotation(ROT_Y, floatRotationArray[1] * 3.14f / 180.f);

							m_pCurObjectTransform->Rotation_y = floatRotationArray[1];
							prevRotationArray[1] = floatRotationArray[1];
						}

						// z�� ȸ��
						if (floatRotationArray[2] != prevRotationArray[2])
						{
							m_pCurObjectTransform->Rotation(ROT_Z, -prevRotationArray[2] * 3.14f / 180.f);
							m_pCurObjectTransform->Rotation(ROT_Z, floatRotationArray[2] * 3.14f / 180.f);

							m_pCurObjectTransform->Rotation_z = floatRotationArray[2];
							prevRotationArray[2] = floatRotationArray[2];
						}
						ImGui::EndChild();

						ImGui::BeginChild("Scale", ImVec2(200, 200), true);
						ImGui::Text(u8"ũ��");
						if (m_pPreObjectTransform != m_pCurObjectTransform)
						{
							floatScaleArray[0] = m_pCurObjectTransform->Get_WorldMatrix()->_11;
							floatScaleArray[1] = m_pCurObjectTransform->Get_WorldMatrix()->_22;
							floatScaleArray[2] = m_pCurObjectTransform->Get_WorldMatrix()->_33;

							prevScaleArray[0] = m_pCurObjectTransform->Get_WorldMatrix()->_11;
							prevScaleArray[1] = m_pCurObjectTransform->Get_WorldMatrix()->_22;
							prevScaleArray[2] = m_pCurObjectTransform->Get_WorldMatrix()->_33;

							m_pPreObjectTransform = m_pCurObjectTransform;
						}
						//static float floatScaleArray[3] = { 1.f,1.f,1.f };
						//static float prevScaleArray[3] = { 1.f, 1.f, 1.f }; // ���� ũ�Ⱚ �����

						ImGui::SliderFloat3("##1", floatScaleArray, 0.f, 100.f);

						// x�� ũ��
						if (floatScaleArray[0] != prevScaleArray[0])
						{
							m_pCurObjectTransform->m_vScale = { -prevScaleArray[0], floatScaleArray[1], floatScaleArray[2] };
							m_pCurObjectTransform->m_vScale = { floatScaleArray[0], floatScaleArray[1], floatScaleArray[2] };

							//m_pCurObjectTransform->Rotation_x = floatRotationArray[0];
							//m_pCurObjectTransform->Get_WorldMatrix()->_11 = floatScaleArray[0];
							prevScaleArray[0] = floatScaleArray[0];
						}

						// y�� ũ��
						if (floatScaleArray[1] != prevScaleArray[1])
						{
							m_pCurObjectTransform->m_vScale = { floatScaleArray[0], -prevScaleArray[1], floatScaleArray[2] };
							m_pCurObjectTransform->m_vScale = { floatScaleArray[0], floatScaleArray[1], floatScaleArray[2] };

							prevScaleArray[1] = floatScaleArray[1];
						}

						// z�� ũ�� 

						if (floatScaleArray[2] != prevScaleArray[2])
						{
							m_pCurObjectTransform->m_vScale = { floatScaleArray[0], floatScaleArray[1], -prevScaleArray[1] };
							m_pCurObjectTransform->m_vScale = { floatScaleArray[0], floatScaleArray[1], floatScaleArray[2] };

							prevScaleArray[2] = floatScaleArray[2];
						}

						ImGui::EndChild();

					}

				
				}

				//������ư ������ Ȱ��ȭ
				if(ImGui::Button(u8"����", ImVec2(100.f, 0.f)))
				{

					map<const _tchar*, CLayer*>& mapLayer = CManagement::GetInstance()->GetCurScenePtr()->GetLayerMapPtr();
					
					auto iter = mapLayer.find(L"Layer_GameLogic");

					if(iter == mapLayer.end())
					{
						MSG_BOX("Not Find");
					}

					else
					{
						CLayer* pLayer = iter->second;

						map<const _tchar*, CGameObject*>& mapObject = pLayer->GetLayerGameObjectPtr();

						auto iter = mapObject.find(CurClickObject);
						
								
						if(iter == mapObject.end())
						{
							MSG_BOX("Not_Find_Object");
						}

						else
						{
							
							// ���� ���� ���̳��� �̺�Ʈ �Ŵ��������� ���� ����ó���ϱ�. 
							mapObject.erase(CurClickObject);		
							
						}
					}

				}

				ImGui::EndChild();
				
			
				ImGui::End();
			}

}

void CImgui_ObjectTool::InstallObject(wstring _TextureKey, wstring _CurTextureData, wstring _forConvert)
{

	Engine::CLayer* pLayer = CLayer::Create();	
	if (pLayer == nullptr)	
	{
		MSG_BOX("pLayer nullptr Error");	
	}
	
	
	Engine::CGameObject* pGameObject = nullptr;	
	
	pGameObject = CObject::Create(CGraphicDev::GetInstance()->Get_GraphicDev());
	if (pGameObject == nullptr)
	{
		MSG_BOX("CObject nullptr Error");
	}
	
	auto iter = find(m_vecObjectList.begin(), m_vecObjectList.end(), m_strCurObjectName.c_str());
	
	map<const _tchar*, CLayer*>& pMapLayer = Engine::Get_CurScenePtr()->GetLayerMapPtr();	

	// ���ο� ��ü�� �������ϳ� ���
	wstring* dynamicWstring = new wstring(_forConvert + to_wstring(index));	
	//dynamicWstring = &_forConvert;		
	m_vecObjectList.push_back((*dynamicWstring).c_str());	
	pMapLayer[L"Layer_GameLogic"]->Add_GameObject((*dynamicWstring).c_str(), pGameObject);	
	pGameObject->SetObjectKey(*dynamicWstring);		// imgui â�� ���� �̸�				
	pGameObject->SetTextureKey(m_sCurTextureKey);       // imgui ������ �ؽ�ó
	index++;
}

void CImgui_ObjectTool::Save()
{
	// ���� ���̺� ��� �����Ϸ� 
	OPENFILENAME ofn;       // OPENFILENAME ����ü ����
	wchar_t szFile[260];       // ���� �̸��� ������ ���� (�ִ� 260��)

	// ����ü �ʱ�ȭ
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = g_hWnd;   // �θ� ������ �ڵ� (���⼱ �ܼ� â�� ���)
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0'; // �ʱ� ���� �̸� (�� ���ڿ�)
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Text Files\0*.txt\0All Files\0*.*\0";  // ���� ���� ���� (�ؽ�Ʈ ���ϰ� ��� ����)
	ofn.nFilterIndex = 1;   // �⺻ ���� ���� ���� (1 = Text Files)
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = L"C:\\Users\\tjsgh\\Desktop\\9�� 19�� �����ӿ�ũ �۾�\\Client\\Map";  // �ʱ� ���丮 (NULL�̸� �⺻ ���丮 ���)
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

	// ���� ���� ��ȭ ���� ǥ��
	if (GetSaveFileName(&ofn) == TRUE) {
		// ���� ��ΰ� ���õǸ� �޽��� �ڽ��� ���� ��θ� ǥ��
		 
		HANDLE hFile = CreateFile(ofn.lpstrFile,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MSG_BOX("hFile not open");
		}

		// ���⼭ ������Ʈ�� SetTextureKey�� object�� ���� ��Ʈ���� ���� �����ϸ�ɵ� 

		map<const _tchar*, CLayer*>& pLayerMap = CManagement::GetInstance()->GetCurScenePtr()->GetLayerMapPtr();
		
		for (auto iter = pLayerMap.begin(); iter != pLayerMap.end(); ++iter)
		{
			const _tchar* layerKey = iter->first;

		
			if (_tcscmp(layerKey, _T("Layer_GameLogic")) == 0)
			{
				// ���⼭ �۾� ���ϳ��뿡 ���͵�
			
				
				//�̰� �ش� ���̾� ������ 
				map<const _tchar*, CGameObject*>& pMapObject = iter->second->GetLayerGameObjectPtr();
				
				for(auto iter2 = pMapObject.begin(); iter2 != pMapObject.end(); ++iter2)
				{
					wstring TextureInfo = iter2->second->GetTextureKey();
					DWORD bytesToWrite = 100;
					//DWORD bytesToWrite = sizeof(wstring);
					DWORD bytesWritten = 0;	
					//
					if (!WriteFile(hFile, TextureInfo.c_str(), bytesToWrite, &bytesWritten, NULL))
					{
						MSG_BOX("FAILED TO WRITE TO TextureKey TO FILE");	
						CloseHandle(hFile);	
					}
					
					wstring ObjectName = iter2->second->GetObjectKey();
					CTransform* pTransform =  dynamic_cast<CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", ObjectName.c_str(), L"Com_Transform"));
					const D3DXMATRIX* WorldMatrix = pTransform->Get_WorldMatrix();	
					D3DXMATRIX Test = *WorldMatrix;

					bytesToWrite = sizeof(D3DXMATRIX);
					bytesWritten = 0;	

					if(!WriteFile(hFile, Test, bytesToWrite, &bytesWritten,NULL))
					{
						MSG_BOX("FAILED TO WRITE TO MATRIX TO FILE");
						CloseHandle(hFile);
					}
				}
			}
		}

		MSG_BOX("SUCCESS");
		 
	}
	else {
		// ������ ��� ��, ���� �ڵ带 Ȯ��
		DWORD error = CommDlgExtendedError();
		if (error != 0) {
			MSG_BOX("Error");
			//char errorMsg[100];
			//sprintf(errorMsg, "Error code: %lu", error);
			//MessageBox(g_hWnd, errorMsg, "Error", MB_OK | MB_ICONERROR);
		}
	}
}

void CImgui_ObjectTool::Read()
{
	OPENFILENAME ofn;       // OPENFILENAME ����ü ����
	wchar_t szFile[260];   // ���� �̸��� ������ ���� (�ִ� 260��)

	// ����ü �ʱ�ȭ
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = g_hWnd;   // �θ� ������ �ڵ�
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';  // �ʱ� ���� �̸� (�� ���ڿ�)
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Text Files\0*.txt\0All Files\0*.*\0";  // ���� ���� ����
	ofn.nFilterIndex = 1;      // �⺻ ���� ���� ����
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = L"C:\\Users\\tjsgh\\Desktop\\9�� 19�� �����ӿ�ũ �۾�\\Client\\Map";  // �ʱ� ���丮
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

	// ���� ���� ��ȭ���� ǥ��
	if (GetOpenFileName(&ofn)) {
		// ���� ����
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);	
		if (hFile != INVALID_HANDLE_VALUE) {
			
			

			// ���� ���ڿ��� �б� -> �ش� �����Ʈ������ �������� 
			//wstring	teststring = L"";

			DWORD bytesRead = 0;


			if(!ReadFile(hFile,	&m_wCurReadTextureKey,sizeof(wstring),&bytesRead,NULL))
			{
				MSG_BOX("FAILED TO READ TextrueKey");
				CloseHandle(hFile);
			}

		

			
			D3DXMATRIX worldmatrix;
			bytesRead = 0; 
			
			if(!ReadFile(hFile, worldmatrix, sizeof(D3DXMATRIX),&bytesRead,NULL))	
			{
				MSG_BOX("FAILED TO READ WORLDMAXTIRX");
				CloseHandle(hFile);
			}


			CloseHandle(hFile);  // ���� �ڵ� �ݱ�	
		}
		else {
			MSG_BOX("������ �� �� �����ϴ�.");
			//std::cerr << "������ �� �� �����ϴ�." << std::endl;
		}
	}

	MSG_BOX("SUCCESS");
	

}


_vec3 CImgui_ObjectTool::PickingOnTerrain()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse); // Ŭ���̾�Ʈ ��ǥȭ

	_vec3 vMousePos;

	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	CGraphicDev::GetInstance()->Get_GraphicDev()->GetViewport(&ViewPort);

	// �� ��Ʈ -> ����
	vMousePos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;


	// ���� -> �� �����̽� 
	_matrix matProj;
	CGraphicDev::GetInstance()->Get_GraphicDev()->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

	_vec3 vRayPos, vRayDir;

	vRayPos = { 0.f, 0.f, 0.f };
	vRayDir = vMousePos - vRayPos;

	// �佺���̽� -> ���� 
	_matrix matView;
	CGraphicDev::GetInstance()->Get_GraphicDev()->GetTransform(D3DTS_VIEW, &matView); // ���⼭ ���� �䰡 ������Ʈ���ȵ�
	D3DXMatrixInverse(&matView, NULL, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView); // ��ġ ���� �̵�
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	// ���� ��ǥ���� �ҰŴϱ� �ͷ����� ������ǥ ������ �����;��� 
	CMapTex* pTerrainBufferCom = dynamic_cast<CMapTex*>(Engine::Get_Component(ID_STATIC, L"Layer_Environment", L"Map", L"Com_Buffer"));
	if (pTerrainBufferCom == nullptr)
	{
		MSG_BOX("pTerrainBufferCom is nullptr");
	}

	CTransform* pTerrainTransCom = dynamic_cast<CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_Environment", L"Map", L"Com_Transform"));
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