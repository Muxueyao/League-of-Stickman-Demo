#include "stdafx.h"


CAudio_management *CAudio_management::Instance = NULL;
CAudio_management * CAudio_management::Get_instance()
{
	if (!Instance)
		Instance = new CAudio_management;
	return Instance;
}

CAudio_management::CAudio_management()
{
	int m_MusicIndex;
	TiXmlDocument *Document = new TiXmlDocument;
	Document->LoadFile("Xml/audio.xml");
	TiXmlElement *Root_Element = Document->RootElement();
	TiXmlElement *FirstChild_Element = Root_Element->FirstChildElement();
	TiXmlElement *Text = FirstChild_Element->FirstChildElement();

	char *player_a1 = new char[strlen(Text->FirstChildElement("player_a1")->GetText()) + 1];
	strcpy(player_a1, Text->FirstChildElement("player_a1")->GetText());
	player_a1_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_a1_Audio.LoadFile(player_a1, BASS_MUSIC_MONO);
	player_a1_Audio.ChannelBytes2Seconds(m_MusicIndex, player_a1_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_a2 = new char[strlen(Text->FirstChildElement("player_a2")->GetText()) + 1];
	strcpy(player_a2, Text->FirstChildElement("player_a2")->GetText());
	player_a2_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_a2_Audio.LoadFile(player_a2, BASS_MUSIC_MONO);
	player_a2_Audio.ChannelBytes2Seconds(m_MusicIndex, player_a2_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_a3 = new char[strlen(Text->FirstChildElement("player_a3")->GetText()) + 1];
	strcpy(player_a3, Text->FirstChildElement("player_a3")->GetText());
	player_a3_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_a3_Audio.LoadFile(player_a3, BASS_MUSIC_MONO);
	player_a3_Audio.ChannelBytes2Seconds(m_MusicIndex, player_a3_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_a4 = new char[strlen(Text->FirstChildElement("player_a4")->GetText()) + 1];
	strcpy(player_a4, Text->FirstChildElement("player_a4")->GetText());
	player_a4_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_a4_Audio.LoadFile(player_a4, BASS_MUSIC_MONO);
	player_a4_Audio.ChannelBytes2Seconds(m_MusicIndex, player_a4_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_a5 = new char[strlen(Text->FirstChildElement("player_a5")->GetText()) + 1];
	strcpy(player_a5, Text->FirstChildElement("player_a5")->GetText());
	player_a5_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_a5_Audio.LoadFile(player_a5, BASS_MUSIC_MONO);
	player_a5_Audio.ChannelBytes2Seconds(m_MusicIndex, player_a5_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_run = new char[strlen(Text->FirstChildElement("player_run")->GetText()) + 1];
	strcpy(player_run, Text->FirstChildElement("player_run")->GetText());
	player_Run_audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_Run_audio.LoadFile(player_run, BASS_MUSIC_MONO);
	player_Run_audio.ChannelBytes2Seconds(m_MusicIndex, player_Run_audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_q = new char[strlen(Text->FirstChildElement("player_q")->GetText()) + 1];
	strcpy(player_q, Text->FirstChildElement("player_q")->GetText());
	player_Q_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_Q_Audio.LoadFile(player_q, BASS_MUSIC_MONO);
	player_Q_Audio.ChannelBytes2Seconds(m_MusicIndex, player_Q_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_w = new char[strlen(Text->FirstChildElement("player_w")->GetText()) + 1];
	strcpy(player_w, Text->FirstChildElement("player_w")->GetText());
	player_W_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_W_Audio.LoadFile(player_w, BASS_MUSIC_MONO);
	player_W_Audio.ChannelBytes2Seconds(m_MusicIndex, player_W_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_e = new char[strlen(Text->FirstChildElement("player_e")->GetText()) + 1];
	strcpy(player_e, Text->FirstChildElement("player_e")->GetText());
	player_E_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_E_Audio.LoadFile(player_e, BASS_MUSIC_MONO);
	player_E_Audio.ChannelBytes2Seconds(m_MusicIndex, player_E_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_r = new char[strlen(Text->FirstChildElement("player_r")->GetText()) + 1];
	strcpy(player_r, Text->FirstChildElement("player_r")->GetText());
	player_R_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_R_Audio.LoadFile(player_r, BASS_MUSIC_MONO);
	player_R_Audio.ChannelBytes2Seconds(m_MusicIndex, player_R_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_die = new char[strlen(Text->FirstChildElement("player_die")->GetText()) + 1];
	strcpy(player_die, Text->FirstChildElement("player_die")->GetText());
	player_die_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_die_Audio.LoadFile(player_die, BASS_MUSIC_MONO);
	player_die_Audio.ChannelBytes2Seconds(m_MusicIndex, player_die_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *player_cd = new char[strlen(Text->FirstChildElement("player_cd")->GetText()) + 1];
	strcpy(player_cd, Text->FirstChildElement("player_cd")->GetText());
	player_cd_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = player_cd_Audio.LoadFile(player_cd, BASS_MUSIC_MONO);
	player_die_Audio.ChannelBytes2Seconds(m_MusicIndex, player_cd_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *UI_button = new char[strlen(Text->FirstChildElement("ui_button")->GetText()) + 1];
	strcpy(UI_button, Text->FirstChildElement("ui_button")->GetText());
	UI_press_audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = UI_press_audio.LoadFile(UI_button, BASS_SAMPLE_MONO);
	UI_press_audio.ChannelBytes2Seconds(m_MusicIndex, UI_press_audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *back_audio = new char[strlen(Text->FirstChildElement("back_audio")->GetText()) + 1];
	strcpy(back_audio, Text->FirstChildElement("back_audio")->GetText());
	back_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = back_Audio.LoadFile(back_audio, BASS_SAMPLE_LOOP);
	back_Audio.ChannelBytes2Seconds(m_MusicIndex, back_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *Main_audio = new char[strlen(Text->FirstChildElement("main_audio")->GetText()) + 1];
	strcpy(Main_audio, Text->FirstChildElement("main_audio")->GetText());
	main_audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = main_audio.LoadFile(Main_audio, BASS_MUSIC_MONO);
	main_audio.ChannelBytes2Seconds(m_MusicIndex, main_audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));


	char *lose = new char[strlen(Text->FirstChildElement("lose")->GetText()) + 1];
	strcpy(lose, Text->FirstChildElement("lose")->GetText());
	lose_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = lose_Audio.LoadFile(lose, BASS_SAMPLE_MONO);
	lose_Audio.ChannelBytes2Seconds(m_MusicIndex, lose_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	char *win = new char[strlen(Text->FirstChildElement("win")->GetText()) + 1];
	strcpy(win, Text->FirstChildElement("win")->GetText());
	win_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = win_Audio.LoadFile(win, BASS_SAMPLE_MONO);
	win_Audio.ChannelBytes2Seconds(m_MusicIndex, win_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));

	

	
	

}


CAudio_management::~CAudio_management()
{
}
