﻿#include "title.h"
#include "DxLib.h"
#include "define.h"
#include "Dxkeystate.h"

Status title(const img_arr_t&, const sound_arr_t& sound) {
	sound.at("title").play(DxSoundMode::LOOP);//p0052r0のscope_exitがほしい
	//フォントの定義
	const int Font_title = CreateFontToHandle(nullptr, 70, 5, DX_FONTTYPE_EDGE);        //タイトルロゴ
	const int Font_1     = CreateFontToHandle(nullptr, 30, 1, DX_FONTTYPE_ANTIALIASING);//「Zキーを押してね」の奴
	keystate state;
	auto normal_con_f = []() -> bool { return -1 != ProcessMessage() && 0 == ScreenFlip() && 0 == ClearDrawScreen(); };
	volatile bool normal_flang;
	while (normal_flang = normal_con_f() && state.update() && !state[KEY_INPUT_Z] && !state.esc()) {
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 180, 250), TRUE);	//背景

		DrawStringToHandle(30 + 5, WINDOW_HEIGHT / 3 + 5, "D...DON'T PUSH!!", GetColor(255, 255, 255), Font_title);		//タイトル（影）
		DrawStringToHandle(30, WINDOW_HEIGHT / 3, "D...DON'T PUSH!!", GetColor(0, 0, 0), Font_title);					//タイトル
		DrawStringToHandle(180, WINDOW_HEIGHT - (WINDOW_HEIGHT / 3), "- Zキーを押してね -", GetColor(0, 0, 0), Font_1); //Zキー押してね
	}
	if (!normal_flang) throw std::runtime_error("");
	sound.at("title").stop();
	if (state.esc()) throw normal_exit();
	return Status::GAME;
}
