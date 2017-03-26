#include "stdafx.h"
#include "Audio4Bass.h"

CAudio4Bass::CAudio4Bass(void)
{
}

CAudio4Bass::~CAudio4Bass(void)
{
	Release();
}

HRESULT CAudio4Bass::Initialize( HWND hWnd )
{
	//BASS_Init(启用设备-1表示默认,采样率,效果参数,窗口句柄,0表示使用默认数据初始化DirectSound)
	return ::BASS_Init(-1, 44100, 0, 0, 0);
}

int CAudio4Bass::LoadFile(char * sName,DWORD flags)
{
	int nSize = m_MusicList.size();
	for (int i=0 ;i<nSize; ++i )
	{
		if(!strcmp(m_MusicList[i].name,sName))
			return i;
	}

	//BASS_StreamCreateFile(是否从内存中加载,文件路径,播放起始位置,播放终止位置,播放效果标志位)
	HSTREAM Sound = ::BASS_StreamCreateFile(FALSE, sName, 0, 0, flags); 
	if(Sound)
	{
		MUSICLIST musicinfo;
		strcpy(musicinfo.name,sName);
		musicinfo.hMusic = Sound;
		m_MusicList.push_back(musicinfo);
		return (int)m_MusicList.size()-1;
	}
	else
		return -1;
}

BOOL CAudio4Bass::ChannelPlay(int index, BOOL restart)
{
	if(NULL != m_MusicList[index].hMusic) 
		return ::BASS_ChannelPlay(m_MusicList[index].hMusic,true);
	else
		return FALSE;
}

BOOL CAudio4Bass::ChannelStop(int index)
{
	if(NULL != m_MusicList[index].hMusic) 
		return ::BASS_ChannelStop(m_MusicList[index].hMusic);
	else
		return FALSE;
}

BOOL CAudio4Bass::ChannelPause(int index)
{
	if(NULL != m_MusicList[index].hMusic) 
		return ::BASS_ChannelPause(m_MusicList[index].hMusic);
	else
		return FALSE;
}

BOOL  CAudio4Bass::SetVolume(float volume)
{
	return ::BASS_SetVolume(volume);
}

QWORD  CAudio4Bass::GetChannelLength(int index, DWORD mode)
{
	//获取文件流的长度, 单位是字节  获取模式; 有两种选择, 但对 HSTREAM 流只能使用 BASS_POS_BYTE
	return ::BASS_ChannelGetLength(m_MusicList[index].hMusic,mode);
}

QWORD  CAudio4Bass::GetChannelPosition(int index, DWORD mode)
{
	//获取流的当前指针位置, 单位是字节  获取模式; 有两种选择, 但对 HSTREAM 流只能使用 BASS_POS_BYTE
	return ::BASS_ChannelGetPosition(m_MusicList[index].hMusic,mode);
}

double  CAudio4Bass::ChannelBytes2Seconds(int index, QWORD pos)
{
	//根据流的指针位置来获取时间点, 单位是秒, 是非常精确的浮点数
	return ::BASS_ChannelBytes2Seconds(m_MusicList[index].hMusic,pos);
}

QWORD  CAudio4Bass::ChannelSeconds2Bytes(int index, double pos)
{
	//和 BASS_ChannelBytes2Seconds 相反, BASS_ChannelSeconds2Bytes 可以通过时间获取流的指针位置.
	return ::BASS_ChannelSeconds2Bytes(m_MusicList[index].hMusic,pos);
}

BOOL  CAudio4Bass::SetChannelPosition(int index, QWORD pos, DWORD mode)
{
	//和 BASS_ChannelGetPosition 相反, BASS_ChannelSetPosition 可以设置流的指针位置.
	return ::BASS_ChannelSetPosition(m_MusicList[index].hMusic,pos,mode);
}

VOID CAudio4Bass::Release()
{
	::BASS_Free();
}

BOOL CAudio4Bass::DeleteMusic(int index)
{
	bool b= ::BASS_StreamFree(m_MusicList[index].hMusic);
	m_MusicList.erase(m_MusicList.begin()+index);
	return b;
}