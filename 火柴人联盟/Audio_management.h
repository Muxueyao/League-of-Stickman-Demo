#pragma once
class CAudio_management
{
	static CAudio_management *Instance;
	CAudio4Bass		player_Run_audio;
	CAudio4Bass		player_Q_Audio;
	CAudio4Bass		player_W_Audio;
	CAudio4Bass		player_E_Audio;
	CAudio4Bass		player_R_Audio;
	CAudio4Bass		player_a1_Audio;
	CAudio4Bass		player_a2_Audio;
	CAudio4Bass		player_a3_Audio;
	CAudio4Bass		player_a4_Audio;
	CAudio4Bass		player_a5_Audio;
	CAudio4Bass		player_die_Audio;
	CAudio4Bass		player_cd_Audio;

	CAudio4Bass		UI_press_audio;

	CAudio4Bass		back_Audio;

	CAudio4Bass		main_audio;

	CAudio4Bass		lose_Audio;
	CAudio4Bass		win_Audio;

	


	
public:
	static CAudio_management *Get_instance();




	void player_Run_audio_play() { player_Run_audio.ChannelPlay(0, true); }
	void player_Q_Audio_play() { player_Q_Audio.ChannelPlay(0, true); }
	void player_W_Audio_play() { player_W_Audio.ChannelPlay(0, true); }
	void player_E_Audio_play() { player_E_Audio.ChannelPlay(0, true); }
	void player_R_Audio_play() { player_R_Audio.ChannelPlay(0, true); }
	void player_R_Audio_stop() { player_R_Audio.ChannelStop(0); }
	void player_a1_Audio_play() { player_a1_Audio.ChannelPlay(0, true); }
	void player_a2_Audio_play() { player_a2_Audio.ChannelPlay(0, true); }
	void player_a3_Audio_play() { player_a3_Audio.ChannelPlay(0, true); }
	void player_a4_Audio_play() { player_a4_Audio.ChannelPlay(0, true); }
	void player_a5_Audio_play() { player_a5_Audio.ChannelPlay(0, true); }
	void player_die_Audio_play() { player_die_Audio.ChannelPlay(0, true); }
	void player_cd_Audio_play() { player_cd_Audio.ChannelPlay(0, true); }

	void UI_press_audio_play() { UI_press_audio.ChannelPlay(0, true); }

	void back_Audio_play() { back_Audio.ChannelPlay(0, true); };
	void back_Audio_stop() { back_Audio.ChannelStop(0); };
	void back_Audio_pause() { back_Audio.ChannelPause(0); };

	void lose_audio_play() { lose_Audio.ChannelPlay(0, true); }
	void win_audio_play() { win_Audio.ChannelPlay(0, true); }
	//void back_Audio_go() { back_Audio. };
	void main_audio_play() { main_audio.ChannelPlay(0, true); }
	void main_audio_stop() { main_audio.ChannelStop(0); }


	CAudio_management();
	~CAudio_management();
};

