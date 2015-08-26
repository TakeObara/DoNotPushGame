#include "DxLib.h"
#include "DxGraphicHandle.h"
#include "define.h"
#include "load.h"
#include <exception>
using img_arr_t = std::unordered_map < std::string, DxGHandle > ;
//�������֐�
int init(){
	SetMainWindowText("�A�v���P�[�V����");
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(255, 255, 255);
	if (DxLib_Init() == -1)return -1;// �G���[���N�����璼���ɏI��
	//SetTransColor(0, 0, 254);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	return 0;
}

//��ԊǗ�
enum class Status{
	TITLE,
	GAME,
	END
};

//�^�C�g������
Status title(img_arr_t& img_arr){
	ClearDrawScreen();
	img_arr["title"].DrawGraph(0, 0, false);
	ScreenFlip();
	while (CheckHitKey(KEY_INPUT_Z) != 1);
	return Status::GAME;
}

//GAME����
Status game(img_arr_t& img_arr){
	ClearDrawScreen();
	img_arr["game"].DrawGraph(0, 0, false);
	ScreenFlip();
	while (CheckHitKey(KEY_INPUT_D) != 1);
	return Status::END;
}

//���U���g����
Status end(img_arr_t& img_arr){
	img_arr["end"].DrawGraph(0, 0, false);
	ScreenFlip();
	while (CheckHitKey(KEY_INPUT_A) != 1);
	return Status::TITLE;
}

//main
#pragma warning (push)
#pragma warning (disable: 4100)
//warning C4100 : 'nCmdShow' : unreferenced formal parameter
//warning C4100 : 'lpCmdLine' : unreferenced formal parameter
//warning C4100 : 'hPrevInstance' : unreferenced formal parameter
//warning C4100 : 'hInstance' : unreferenced formal parameter
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	init();

	//�ϐ���`------------------------------------------------------

	Status status_ = Status::TITLE;
	auto img_arr = make_image_array();


	//����-----------------------------------------------------------

	try{
		while (1){
			switch (status_)
			{
			case Status::TITLE:
				status_ = title(img_arr);
				break;
			case Status::GAME:
				status_ = game(img_arr);
				break;
			case Status::END:
				status_ = end(img_arr);
				break;
			default:
				DxLib_End();
				return -1;
				break;
			}
			ScreenFlip();//����ʕ\��
		}
	}
	catch (std::exception&){
		DxLib_End();
		return -1;
	}

	//�I������--------------------------------------------------------------

	DxLib_End();

	return 0;   
}
#pragma warning (pop)
///