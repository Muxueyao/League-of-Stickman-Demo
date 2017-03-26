#include "stdafx.h"



void CLoading::update()
{
	if (animate->get_end())
	{
		is_end = true;
	}
}

void CLoading::Release()
{
	img->set_del(true);
	animate->set_del(true);
}

CLoading::CLoading()
{
	is_end = false;
	img = new CUI_img(L"img/loadb.png");
	img->set_sort(-10);
	animate = new CAnimate(L"img/load.png", 10, 1, 1, 10);
	animate->set_pos(910, 490);
	animate->set_sort(-11);

}


CLoading::~CLoading()
{
}
