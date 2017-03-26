#include "stdafx.h"


CNpc_Management *CNpc_Management::Instance = NULL;
CNpc_Management * CNpc_Management::Get_instance()
{
	if (!Instance)
		Instance = new CNpc_Management;
	return Instance;
}

void CNpc_Management::add(CNpc * Obj)
{
	Npc_list.push_back(Obj);
}

void CNpc_Management::update()
{
	list<CNpc*>::iterator itea;
	for (itea = Npc_list.begin();itea != Npc_list.end();)
	{
		if ((*itea)->get_del())
		{
			(*itea)->Release();
			delete (*itea);
			Npc_list.erase(itea++);
		}
		else
		{
			if (CPlatForm::Getinstance()->get_pause())
			{
				(*itea)->show();
			}
			else
			{
				(*itea)->update();
				(*itea)->show();
				switch (CPlayer::Get_Instance()->get_act())
				{
				case Q:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_q_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				case W:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_w_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();

					}
					break;
				case E:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_e_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				case R:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_r_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				case A1:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_a1_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				case A2:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_a2_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				case A3:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_a3_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				case A4:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_a4_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				case A5:
					if (CPlayer::Get_Instance()->Get_spx()->collidesWith((*itea)->get_spx(), 0, 1, COLLISION_AABB))
					{
						(*itea)->set_hurted(rand() % 100 + CPlayer::Get_Instance()->get_a5_hurted());
						npchurted_Audio.ChannelPlay(0, true);
						CPlayer::Get_Instance()->set_hits();
					}
					break;
				default:
					break;
				}
			}
			
			itea++;
		}
	}
}

void CNpc_Management::Release()
{
	list<CNpc*>::iterator itea;
	for (itea = Npc_list.begin();itea != Npc_list.end();)
	{
		(*itea)->Release();
		delete (*itea);
		Npc_list.erase(itea++);
	}
}



CNpc_Management::CNpc_Management()
{
	int m_MusicIndex;//ÁÙÊ±±äÁ¿£¬ÅäÖÃÒôÆµ
	npchurted_Audio.Initialize(CPlatForm::Getinstance()->Get_hwnd());
	m_MusicIndex = npchurted_Audio.LoadFile("audio/monster/hurted.mp3", BASS_MUSIC_MONO);
	npchurted_Audio.ChannelBytes2Seconds(m_MusicIndex, npchurted_Audio.GetChannelLength(m_MusicIndex, BASS_POS_BYTE));
}


CNpc_Management::~CNpc_Management()
{
}
