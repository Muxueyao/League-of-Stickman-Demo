#include "stdafx.h"


Cmap *Cmap::instance = NULL;
Cmap * Cmap::Getinstance()
{
	if (!instance)
		instance = new Cmap;
	return instance;
}

void Cmap::update()
{
	if (is_snake)
	{
		static int speed = 4;
		snake += speed;
		static bool a = false;;
		if (snake >= 20)
		{
			speed = -speed;
		}

		if (snake <= -20)
		{
			speed = -speed;
			a = true;
		}
		if (snake == 0 && a)
		{
			is_snake = false;
			a = false;
		}
	}

	map_img->set_pos(offset_x, offset_y+280+snake);
}

void Cmap::set_lock_scene(int _scene)
{
	switch (_scene)
	{
	case 1:
		if (map_x < 1500)
		{
			map_x += 10;
		}
		break;
	case 2:
		if (map_x < 2500)
		{
			map_x += 10;
		}
		break;
	case 3:
		if (map_x < 3500)
		{
			map_x += 10;
		}

		break;
	case 4:
		if (map_x < 5500)
		{
			map_x += 10;
		}
		break;
	default:
		break;
	}
}

Cmap::Cmap()
{
	snake = 0;
	is_snake = false;
	map_img = new CUI_img(L"img/map.png");
	map_img->set_color(0, 0, 0);
	map_x = WIN_X;// map_img->get_img_x();
	map_y = map_img->get_img_y();

	offset_x = 0;
	offset_y = 280;
}


Cmap::~Cmap()
{
}
