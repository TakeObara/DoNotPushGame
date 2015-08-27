#include "continue.h"
#include "Dxkeystate.h"
#include "DxLib.h"
Status continu(img_arr_t& img_arr) {

	/////////////

	//�t�H���g
	int Font_1;			//�I�����\���̕���
	Font_1 = CreateFontToHandle(NULL, 30, 1, DX_FONTTYPE_ANTIALIASING);

	//�֐�
	int select0_x = 200;	//�����̍��W�i����j
	int select0_y = 100;
	int select1_x = 200;
	int select1_y = 200;

	int color[2];
	color[0] = GetColor(255, 255, 255);		//�I�����Ă���z�̐F
	color[1] = GetColor(0,0,0);				//�I�����Ă��Ȃ��z�̐F

	int answer = 0;		//�R���e�B�j���[���邩�ǂ����i0:YES�@1:NO�j

	while (TRUE){
		ClearDrawScreen();

		//�\���L�[��t
		keystate state;
		state.update();
		if (state.up() || state.down()){
			answer = (answer + 1) % 2;
		}


		//�`��
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//�w�i

		DrawStringToHandle(select0_x + ((answer+1)%2)*40, select0_y, "CONTINUE !!", color[answer], Font_1);				//CONTINUE
		DrawStringToHandle(select1_x + answer*40		, select1_y, "RETIRE. . .", color[(answer+1)%2], Font_1);		//RETIRE


		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_Z) == 1){		//Z�L�[�Ō���
			switch (answer){
			case 0:
				return Status::GAME;
			case 1:
				return Status::TITLE;
			}
		}
	}

	return Status::EXIT; //��{�����ɂ͗��Ȃ��͂��B��O�����ŋ����I��

	///////////// by yuchu
}
