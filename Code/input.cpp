//====================================================================================================================
//	
//	���͏����@[input.cpp]
//	Author:AKIRA TANAKA
//	
//====================================================================================================================
#include "input.h"


//***********************************************************************************************************************
//	Macro��`
//***********************************************************************************************************************
#define	NUM_KEY_MAX					(256)		//	key�̍ő吔
#define	LIMIT_COUNT_REPEAT	(20)			//	repeat count LIMIT

//***********************************************************************************************************************
//		Prototype�錾
//***********************************************************************************************************************
HRESULT	InitInput(HINSTANCE hInstance, HWND hWnd);
//void				UninitInput(void);
//void				UpdateInput(void);
//HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
//void UninitKeyboard(void);
//HRESULT UpdateKeyboard(void);
//HRESULT InitMouse(HINSTANCE hInst, HWND hWnd);
//void UninitMouse(void);
//HRESULT UpdateMouse(void);

//***********************************************************************************************************************
//		Global�ϐ�
//***********************************************************************************************************************
LPDIRECTINPUT8					g_pDInput = NULL;												//	DirectInput interface�ւ�pointer
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;								//	����Device�ikeyboard�j�ւ�pointer
LPDIRECTINPUTDEVICE8	g_pDIDevMouse = NULL;										//	����Device�imouse�j�ւ�pointer
BYTE											g_aKeyState[NUM_KEY_MAX];							//	keyboard�̏�Ԃ��󂯎��Work
BYTE											g_aKeyStateTrigger[NUM_KEY_MAX];				//	keyboard�̏�Ԃ��󂯎��Work
BYTE											g_aKeyStateRepeat[NUM_KEY_MAX];				//	keyboard�̏�Ԃ��󂯎��Work
BYTE											g_aKeyStateRelease[NUM_KEY_MAX];				//	keyboard�̏�Ԃ��󂯎��Work
int												g_aKeyStateRepeatCnt[NUM_KEY_MAX];		//	keyboard��repeat counter
//DIMOUSESTATE2			g_mouseState;						// �}�E�X�̏�Ԃ��󂯎�郏�[�N
//DIMOUSESTATE2			g_mouseStateTrigger;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N
//POINT					g_MousePoint;						// �}�E�X�̌��ݍ��W
//HWND					g_hwnd;
//====================================================================================================================
//		���͏���������
//====================================================================================================================
HRESULT	InitInput(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	if (g_pDInput == NULL)
	{
		//		DirectInput Object�̍쐬
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);
		return hr;
	}

	return S_OK;
}

//====================================================================================================================
//		���͏����̏I������
//====================================================================================================================
void		UninitInput(void)
{
	if (g_pDInput != NULL)
	{//		DirectInput Object�̊J��
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//====================================================================================================================
//		���͏����̍X�V����
//====================================================================================================================
void UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	//// �}�E�X�̍X�V
	//UpdateMouse();
}

//====================================================================================================================
//		keyboard�̏�����
//====================================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;
	//		���͏����̏�����
	hr = InitInput(hInstance, hWnd);
	if (FAILED(hr))
	{
		MessageBox(hWnd, TEXT("DirectInput object����ꖳ���I"), TEXT("�x��"), MB_ICONWARNING);
		return hr;
	}

	//		Device object���쐬
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, TEXT("keyboard�������I"), TEXT("�x��"), MB_ICONWARNING);
		return hr;
	}

	//		data format��ݒ�
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd, TEXT("keyboard��data format��ݒ�o���܂���o���B"), TEXT("�x��"), MB_ICONWARNING);
		return hr;
	}

	//		����mode��ݒ�iforeground����r��mode�j
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, TEXT("keyboard�̋���mode��ݒ�o���܂���o���B"), TEXT("�x��"), MB_ICONWARNING);
		return hr;
	}

	//		keyboard��access�����l���i���͐���J�n�j
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//====================================================================================================================
//		keyboard�̏I������
//====================================================================================================================
void		UninitKeyboard(void)
{
	if (g_pDIDevKeyboard != NULL)
	{//		����Device�ikeyboard�j�̊J��
		//		keyboard�ւ�access�����J���i���͐���I���j
		g_pDIDevKeyboard->Unacquire();

		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}

	//		���͏����̏I������
	UninitInput();
}


//====================================================================================================================
//		keyboard�̍X�V����
//====================================================================================================================

//HRESULT UpdateKeyboard(void)
//{
//	HRESULT hr;
//	BYTE keyStateOld[256];
//
//	// �O��̃f�[�^��ۑ�
//	memcpy(keyStateOld, g_aKeyState, NUM_KEY_MAX);
//
//	// �f�o�C�X����f�[�^���擾
//	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_aKeyState), g_aKeyState);
//	if (SUCCEEDED(hr))
//	{
//		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
//		{
//			// �g���K�[�ƃ����[�X���擾
//			g_aKeyStateTrigger[cnt] = (g_aKeyState[cnt] ^ keyStateOld[cnt]) & g_aKeyState[cnt];
//			g_aKeyStateRelease[cnt] = (g_aKeyState[cnt] ^ keyStateOld[cnt]) & keyStateOld[cnt];
//
//			// �L�[��������Ă���Ȃ烊�s�[�g�̔��菈��
//			if (g_aKeyState[cnt])
//			{
//				if (g_aKeyStateRepeatCnt[cnt] < 20)
//				{
//					g_aKeyStateRepeatCnt[cnt]++;
//					// �u������́v�������́u�{�^���������Ă���20�t���[���o�߁v
//					// �����ꍇ�A���s�[�g�p�z��̃f�[�^��L���ɂ���
//					// ��L�����ȊO�̓��s�[�g�p�z��̃f�[�^�𖳌��ɂ���
//					if (g_aKeyStateRepeatCnt[cnt] == 1 || g_aKeyStateRepeatCnt[cnt] >= 20) {
//						g_aKeyStateRepeat[cnt] = 0x80;
//					}
//					else {
//						g_aKeyStateRepeat[cnt] = 0;
//					}
//				}
//			}
//			else
//			{
//				g_aKeyStateRepeatCnt[cnt] = 0;
//				g_aKeyStateRepeat[cnt] = 0;
//			}
//		}
//	}
//	else
//	{
//		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
//		hr = g_pDIDevKeyboard->Acquire();
//	}
//
//	return hr;
//}

void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	
	//		Device����data���擾
	if (SUCCEEDED(g_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			//		key trigger�Erelease���𐶐�
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & ~aKeyState[nCnKey];

			//		key repeat���𐶐�
			if (aKeyState[nCnKey])
			{
				if (g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if (g_aKeyStateRepeatCnt[nCnKey] == 1
						|| g_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{//		key�������n�߂��ŏ���Frame�A���͈�莞�Ԍo�߂�����key repeat���ON
						g_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						g_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				g_aKeyStateRepeatCnt[nCnKey] = 0;
				g_aKeyStateRepeat[nCnKey] = 0;
			}

			//		key press����ۑ�
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		//		keyboard�ւ�access�����擾
		g_pDIDevKeyboard->Acquire();
	}
}

//====================================================================================================================
//		keyboard��press��Ԃ��擾
//====================================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//====================================================================================================================
//		keyboard��trigger��Ԃ��擾
//====================================================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//====================================================================================================================
//		keyboard��repeat��Ԃ��擾
//====================================================================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}


//====================================================================================================================
//		keyboard��release��Ԃ��擾
//====================================================================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//
//
////=============================================================================
//// �}�E�X�̏�����
////=============================================================================
//HRESULT InitMouse(HINSTANCE hInst, HWND hWnd)
//{
//	HRESULT hr;
//
//	// �f�o�C�X�I�u�W�F�N�g���쐬
//	hr = g_pDInput->CreateDevice(GUID_SysMouse, &g_pDIDevMouse, NULL);
//	if (FAILED(hr) || g_pDIDevMouse == NULL)
//	{
//		MessageBox(hWnd, TEXT("�}�E�X���˂��I"), TEXT("�x���I"), MB_ICONWARNING);
//		return hr;
//	}
//
//	// �f�[�^�t�H�[�}�b�g��ݒ�
//	hr = g_pDIDevMouse->SetDataFormat(&c_dfDIMouse2);
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, TEXT("�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B"), TEXT("�x���I"), MB_ICONWARNING);
//		return hr;
//	}
//
//	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
//	hr = g_pDIDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, TEXT("�}�E�X�̋������[�h��ݒ�ł��܂���ł����B"), TEXT("�x���I"), MB_ICONWARNING);
//		return hr;
//	}
//
//	// �f�o�C�X�̐ݒ�
//	{
//		DIPROPDWORD dipdw;
//
//		dipdw.diph.dwSize = sizeof(dipdw);
//		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
//		dipdw.diph.dwObj = 0;
//		dipdw.diph.dwHow = DIPH_DEVICE;
//		dipdw.dwData = DIPROPAXISMODE_REL;
//
//		hr = g_pDIDevMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
//	}
//
//	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
//	g_pDIDevMouse->Acquire();
//
//	return S_OK;
//}
//
////=============================================================================
//// �}�E�X�̏I������
////=============================================================================
//void UninitMouse(void)
//{
//	if (g_pDIDevMouse)
//	{
//		g_pDIDevMouse->Unacquire();
//
//		g_pDIDevMouse->Release();
//		g_pDIDevMouse = NULL;
//	}
//}
//
////=============================================================================
//// �}�E�X�̍X�V����
////=============================================================================
//HRESULT UpdateMouse(void)
//{
//	HRESULT hr;
//	DIMOUSESTATE2 mouseStateOld;
//
//	// �O��̃f�[�^��ۑ�
//	mouseStateOld = g_mouseState;
//
//	GetCursorPos(&g_MousePoint);
//	ScreenToClient(g_hwnd, &g_MousePoint);
//
//
//	// �f�o�C�X����f�[�^���擾
//	hr = g_pDIDevMouse->GetDeviceState(sizeof(g_mouseState), &g_mouseState);
//	if (SUCCEEDED(hr))
//	{
//		// �g���K�[�̎擾
//		//g_mouseStateTrigger.lX = 
//		//g_mouseStateTrigger.lY = 
//		//g_mouseStateTrigger.lZ = 
//		for (int cnt = 0; cnt < 8; cnt++)
//		{
//			g_mouseStateTrigger.rgbButtons[cnt] = ((mouseStateOld.rgbButtons[cnt] ^ g_mouseState.rgbButtons[cnt]) & g_mouseState.rgbButtons[cnt]);
//		}
//	}
//	else
//	{
//		g_pDIDevMouse->Acquire();
//	}
//
//	return S_OK;
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(���v���X)
////=============================================================================
//bool GetMouseLeftPress(void)
//{
//	return ((g_mouseState.rgbButtons[0] & 0x80) != 0);
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(���g���K�[)
////=============================================================================
//bool GetMouseLeftTrigger(void)
//{
//	return ((g_mouseStateTrigger.rgbButtons[0] & 0x80) != 0);
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(�E�v���X)
////=============================================================================
//bool GetMouseRightPress(void)
//{
//	return ((g_mouseState.rgbButtons[1] & 0x8) != 00);
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(�E�g���K�[)
////=============================================================================
//bool GetMouseRightTrigger(void)
//{
//	return ((g_mouseStateTrigger.rgbButtons[1] & 0x80) != 0);
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(�����v���X)
////=============================================================================
//bool GetMouseCenterPress(void)
//{
//	return ((g_mouseState.rgbButtons[2] & 0x80) != 0);
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(�����g���K�[)
////=============================================================================
//bool GetMouseCenterTrigger(void)
//{
//	return ((g_mouseState.rgbButtons[2] & 0x80) != 0);
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(�w���ړ�)
////=============================================================================
//long GetMouseAxisX(void)
//{
//	return g_mouseState.lX;
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(�x���ړ�)
////=============================================================================
//long GetMouseAxisY(void)
//{
//	return g_mouseState.lY;
//}
//
////=============================================================================
//// �}�E�X�f�[�^�擾(�y���ړ�)
////=============================================================================
//long GetMouseAxisZ(void)
//{
//	return g_mouseState.lZ;
//}
////=============================================================================
//// �}�E�X���W�擾(X)
////=============================================================================
//long GetMouseX(void)
//{
//	return g_MousePoint.x;
//}
//
////=============================================================================
//// �}�E�X���W�擾(Y)
////=============================================================================
//long GetMouseY(void)
//{
//	return g_MousePoint.y;
//}