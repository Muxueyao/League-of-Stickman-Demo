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
	//BASS_Init(�����豸-1��ʾĬ��,������,Ч������,���ھ��,0��ʾʹ��Ĭ�����ݳ�ʼ��DirectSound)
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

	//BASS_StreamCreateFile(�Ƿ���ڴ��м���,�ļ�·��,������ʼλ��,������ֹλ��,����Ч����־λ)
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
	//��ȡ�ļ����ĳ���, ��λ���ֽ�  ��ȡģʽ; ������ѡ��, ���� HSTREAM ��ֻ��ʹ�� BASS_POS_BYTE
	return ::BASS_ChannelGetLength(m_MusicList[index].hMusic,mode);
}

QWORD  CAudio4Bass::GetChannelPosition(int index, DWORD mode)
{
	//��ȡ���ĵ�ǰָ��λ��, ��λ���ֽ�  ��ȡģʽ; ������ѡ��, ���� HSTREAM ��ֻ��ʹ�� BASS_POS_BYTE
	return ::BASS_ChannelGetPosition(m_MusicList[index].hMusic,mode);
}

double  CAudio4Bass::ChannelBytes2Seconds(int index, QWORD pos)
{
	//��������ָ��λ������ȡʱ���, ��λ����, �Ƿǳ���ȷ�ĸ�����
	return ::BASS_ChannelBytes2Seconds(m_MusicList[index].hMusic,pos);
}

QWORD  CAudio4Bass::ChannelSeconds2Bytes(int index, double pos)
{
	//�� BASS_ChannelBytes2Seconds �෴, BASS_ChannelSeconds2Bytes ����ͨ��ʱ���ȡ����ָ��λ��.
	return ::BASS_ChannelSeconds2Bytes(m_MusicList[index].hMusic,pos);
}

BOOL  CAudio4Bass::SetChannelPosition(int index, QWORD pos, DWORD mode)
{
	//�� BASS_ChannelGetPosition �෴, BASS_ChannelSetPosition ������������ָ��λ��.
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