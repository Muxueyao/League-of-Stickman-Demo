#pragma once

#include "bass.h"
#pragma comment(lib, "bass.lib")
#include <vector>
using namespace std;

class CAudio4Bass
{
	struct MUSICLIST
	{
		char  name[256];
		HSTREAM hMusic;
	};

public:
	CAudio4Bass(void);
	~CAudio4Bass(void);

	HRESULT		Initialize( HWND hWnd );
	int			LoadFile(char * sName,DWORD flags);
	BOOL		ChannelPlay(int index, BOOL restart);
	BOOL		ChannelStop(int index);
	BOOL		ChannelPause(int index);
	BOOL		SetVolume(float volume);
	BOOL		DeleteMusic(int index);
	QWORD		GetChannelLength(int index, DWORD mode);
	QWORD		GetChannelPosition(int index, DWORD mode);
	double		ChannelBytes2Seconds(int index , QWORD pos);
	QWORD		ChannelSeconds2Bytes(int index,double pos);
	BOOL		SetChannelPosition(int index , QWORD pos, DWORD mode);
	BOOL		GetMusicInfo(int index, BASS_CHANNELINFO *info);
	VOID		Release();
private:
	vector<MUSICLIST>   m_MusicList;
};
