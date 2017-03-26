#include "stdafx.h"



CDie_Effect::CDie_Effect(float x, float y, LPCWSTR img1, LPCWSTR img2, LPCWSTR img3, LPCWSTR img4,
	LPCWSTR img5, LPCWSTR img6, LPCWSTR img7, LPCWSTR img8, LPCWSTR img9, LPCWSTR img10)
{
	/*for (int a = 0; a < 10;a++)
	{
		effect[a] = NULL;
	}
*/
	this->x = x;
	this->y = y;
	angle = 0;
	i1_x = i2_x = i3_x = i4_x = i5_x = i6_x = i7_x = i8_x = i9_x = i10_x = x;
	i1_y = i2_y = i3_y = i4_y = i5_y = i6_y = i7_y = i8_y = i9_y = i10_y = y;

	i1s = i2s = i3s = i4s = i5s = i6s = i7s = i8s = i9s = i10s = true;

	i1_drop = one;
	i1_offset_x = 1.f;i1_offset_y = 20; i1_y_speed = 0.5f;

	i2_drop = one;
	i2_offset_x = 1.25f;i2_offset_y = 19; i2_y_speed = 0.6f;

	i3_drop = one;
	i3_offset_x = 1.5f;i3_offset_y = 18; i3_y_speed = 0.7f;

	i4_drop = one;
	i4_offset_x = 1.75f;i4_offset_y = 17; i4_y_speed = 0.8f;

	i5_drop = one;
	i5_offset_x = 2.f;i5_offset_y = 16; i5_y_speed = 0.9f;


	//////

	i6_drop = one;
	i6_offset_x = 1.f;i6_offset_y = 20; i6_y_speed = 0.5f;

	i7_drop = one;
	i7_offset_x = 1.25f;i7_offset_y = 19; i7_y_speed = 0.6f;

	i8_drop = one;
	i8_offset_x = 1.5f;i8_offset_y = 18; i8_y_speed = 0.7f;

	i9_drop = one;
	i9_offset_x = 1.75f;i9_offset_y = 17; i9_y_speed = 0.8f;

	i10_drop = one;
	i10_offset_x = 2.f;i10_offset_y = 16; i10_y_speed = 0.9f;



	i1 = new CUI_img(img1);
	i1->set_anchor(D3DXVECTOR3(i1->get_img_x() / 2, i1->get_img_y() / 2, 0));
	i1->set_pos(x, y);
	i1->set_sort(-3);
	i2 = new CUI_img(img2);
	i2->set_anchor(D3DXVECTOR3(i2->get_img_x() / 2, i2->get_img_y() / 2, 0));
	i2->set_pos(x, y);
	i2->set_sort(-3);
	i3 = new CUI_img(img3);
	i3->set_anchor(D3DXVECTOR3(i3->get_img_x() / 2, i3->get_img_y() / 2, 0));
	i3->set_pos(x, y);
	i3->set_sort(-3);
	i4 = new CUI_img(img4);
	i4->set_anchor(D3DXVECTOR3(i4->get_img_x() / 2, i4->get_img_y() / 2, 0));
	i4->set_pos(x, y);
	i4->set_sort(-3);
	i5 = new CUI_img(img5);
	i5->set_anchor(D3DXVECTOR3(i5->get_img_x() / 2, i5->get_img_y() / 2, 0));
	i5->set_pos(x, y);
	i5->set_sort(-3);
	i6 = new CUI_img(img6);
	i6->set_anchor(D3DXVECTOR3(i6->get_img_x() / 2, i6->get_img_y() / 2, 0));
	i6->set_pos(x, y);
	i6->set_sort(-3);
	i7 = new CUI_img(img7);
	i7->set_anchor(D3DXVECTOR3(i7->get_img_x() / 2, i7->get_img_y() / 2, 0));
	i7->set_pos(x, y);
	i7->set_sort(-3);
	i8 = new CUI_img(img8);
	i8->set_anchor(D3DXVECTOR3(i8->get_img_x() / 2, i8->get_img_y() / 2, 0));
	i8->set_pos(x, y);
	i8->set_sort(-3);
	i9 = new CUI_img(img9);
	i9->set_anchor(D3DXVECTOR3(i9->get_img_x() / 2, i9->get_img_y() / 2, 0));
	i9->set_pos(x, y);
	i9->set_sort(-3);
	i10 = new CUI_img(img10);
	i10->set_anchor(D3DXVECTOR3(i10->get_img_x() / 2, i10->get_img_y() / 2, 0));
	i10->set_pos(x, y);
	i10->set_sort(-3);
	CObj_management::Getinstance()->add(this);
}


void CDie_Effect::update()
{
	angle += 0.05f;
	int offset_x = Cmap::Getinstance()->get_offset_x();
	if (i1s)
	{
		i1_x += i1_offset_x;
		i1_y -= i1_offset_y;
		i1_offset_y -= i1_y_speed;
		if (i1_y > 350)
		{
			if (i1_drop == one)
			{
				i1_offset_y = 10.f;
				i1_y_speed = 0.25f;
				i1_drop = two;
			}
			else if (i1_drop == two)
			{
				i1_offset_y = 5.f;
				i1_y_speed = 0.125f;
				i1_drop = three;
			}
			else if (i1_drop == three)
			{
				i1_offset_y = 0;
				i1_y_speed = 0.0f;
				i1_offset_x = 0.f;

				i1->set_show(false);
				i1s = false;
				//i1 = NULL;
			}
		}
		i1->set_angle(angle);
		i1->set_pos(i1_x + offset_x, i1_y);
	}

	if (i2s)
	{
		i2_x += i2_offset_x;
		i2_y -= i2_offset_y;
		i2_offset_y -= i2_y_speed;
		if (i2_y > 350)
		{
			if (i2_drop == one)
			{
				i2_offset_y = 9.5f;
				i2_y_speed = 0.3f;
				i2_drop = two;
			}
			else if (i2_drop == two)
			{
				i2_offset_y = 4.75f;
				i2_y_speed = 0.2f;
				i2_drop = three;
			}
			else if (i2_drop == three)
			{
				i2_offset_y = 0;
				i2_y_speed = 0.0f;
				i2_offset_x = 0.f;
				i2->set_show(false);
				i2s = false;
			}
		}
		i2->set_angle(angle);
		i2->set_pos(i2_x + offset_x, i2_y);
	}




	if (i3s)
	{
		i3_x += i3_offset_x;
		i3_y -= i3_offset_y;
		i3_offset_y -= i3_y_speed;
		if (i3_y > 350)
		{
			if (i3_drop == one)
			{
				i3_offset_y = 9.f;
				i3_y_speed = 0.35f;
				i3_drop = two;
			}
			else if (i3_drop == two)
			{
				i3_offset_y = 4.5f;
				i3_y_speed = 0.175f;
				i3_drop = three;
			}
			else if (i3_drop == three)
			{
				i3_offset_y = 0;
				i3_y_speed = 0.0f;
				i3_offset_x = 0.f;
				i3->set_show(false);
				i3s = false;
			}
		}
		i3->set_angle(angle);
		i3->set_pos(i3_x + offset_x, i3_y);
	}




	if (i4s)
	{
		i4_x += i4_offset_x;
		i4_y -= i4_offset_y;
		i4_offset_y -= i4_y_speed;
		if (i4_y > 350)
		{
			if (i4_drop == one)
			{
				i4_offset_y = 8.5f;
				i4_y_speed = 0.4f;
				i4_drop = two;
			}
			else if (i4_drop == two)
			{
				i4_offset_y = 4.25f;
				i4_y_speed = 0.2f;
				i4_drop = three;
			}
			else if (i4_drop == three)
			{
				i4_offset_y = 0;
				i4_y_speed = 0.0f;
				i4_offset_x = 0.f;
				i4->set_show(false);
				i4s = false;
			}
		}
		i4->set_angle(angle);

		i4->set_pos(i4_x + offset_x, i4_y);
	}


	if (i5s)
	{
		i5_x += i5_offset_x;
		i5_y -= i5_offset_y;
		i5_offset_y -= i5_y_speed;
		if (i5_y > 350)
		{
			if (i5_drop == one)
			{
				i5_offset_y = 8.f;
				i5_y_speed = 0.45f;
				i5_drop = two;
			}
			else if (i5_drop == two)
			{
				i5_offset_y = 4.f;
				i5_y_speed = 0.225f;
				i5_drop = three;
			}
			else if (i5_drop == three)
			{
				i5_offset_y = 0;
				i5_y_speed = 0.0f;
				i5_offset_x = 0.f;
				i5->set_show(false);
				i5s = false;
			}
		}
		i5->set_angle(angle);
		i5->set_pos(i5_x + offset_x, i5_y);
	}


	if (i6s)
	{
		i6_x -= i6_offset_x;
		i6_y -= i6_offset_y;
		i6_offset_y -= i6_y_speed;
		if (i6_y > 350)
		{
			if (i6_drop == one)
			{
				i6_offset_y = 10.f;
				i6_y_speed = 0.25f;
				i6_drop = two;
			}
			else if (i6_drop == two)
			{
				i6_offset_y = 5.f;
				i6_y_speed = 0.125f;
				i6_drop = three;
			}
			else if (i6_drop == three)
			{
				i6_offset_y = 0;
				i6_y_speed = 0.0f;
				i6_offset_x = 0.f;
				i6->set_show(false);
				i6s = false;
			}
		}
		i6->set_angle(angle);
		i6->set_pos(i6_x + offset_x, i6_y);
	}


	if (i7s)
	{
		i7_x -= i7_offset_x;
		i7_y -= i7_offset_y;
		i7_offset_y -= i7_y_speed;
		if (i7_y > 350)
		{
			if (i7_drop == one)
			{
				i7_offset_y = 9.5f;
				i7_y_speed = 0.3f;
				i7_drop = two;
			}
			else if (i7_drop == two)
			{
				i7_offset_y = 4.75f;
				i7_y_speed = 0.2f;
				i7_drop = three;
			}
			else if (i7_drop == three)
			{
				i7_offset_y = 0;
				i7_y_speed = 0.0f;
				i7_offset_x = 0.f;
				i7->set_show(false);
				i7s = false;
			}
		}
		i7->set_angle(angle);
		i7->set_pos(i7_x + offset_x, i7_y);
	}

	if (i8s)
	{
		i8_x -= i8_offset_x;
		i8_y -= i8_offset_y;
		i8_offset_y -= i8_y_speed;
		if (i8_y > 350)
		{
			if (i8_drop == one)
			{
				i8_offset_y = 9.f;
				i8_y_speed = 0.35f;
				i8_drop = two;
			}
			else if (i8_drop == two)
			{
				i8_offset_y = 4.5f;
				i8_y_speed = 0.175f;
				i8_drop = three;
			}
			else if (i8_drop == three)
			{
				i8_offset_y = 0;
				i8_y_speed = 0.0f;
				i8_offset_x = 0.f;
				i8->set_show(false);
				i8s = false;
			}
		}
		i8->set_angle(angle);
		i8->set_pos(i8_x + offset_x, i8_y);
	}

	if (i9s)
	{
		i9_x -= i9_offset_x;
		i9_y -= i9_offset_y;
		i9_offset_y -= i9_y_speed;
		if (i9_y > 350)
		{
			if (i9_drop == one)
			{
				i9_offset_y = 8.5f;
				i9_y_speed = 0.4f;
				i9_drop = two;
			}
			else if (i9_drop == two)
			{
				i9_offset_y = 4.25f;
				i9_y_speed = 0.2f;
				i9_drop = three;
			}
			else if (i9_drop == three)
			{
				i9_offset_y = 0;
				i9_y_speed = 0.0f;
				i9_offset_x = 0.f;
				i9->set_show(false);
				i9s = false;
			}
		}
		i9->set_angle(angle);
		i9->set_pos(i9_x + offset_x, i9_y);
	}

	if (i10s)
	{
		i10_x -= i10_offset_x;
		i10_y -= i10_offset_y;
		i10_offset_y -= i10_y_speed;
		if (i10_y > 350)
		{
			if (i10_drop == one)
			{
				i10_offset_y = 8.f;
				i10_y_speed = 0.45f;
				i10_drop = two;
			}
			else if (i10_drop == two)
			{
				i10_offset_y = 4.f;
				i10_y_speed = 0.225f;
				i10_drop = three;
			}
			else if (i10_drop == three)
			{
				i10_offset_y = 0;
				i10_y_speed = 0.0f;
				i10_offset_x = 0.f;
				i10->set_show(false);
				i10s = false;
			}
		}
		i10->set_angle(angle);
		i10->set_pos(i10_x + offset_x, i10_y);

	}
	if (!i1s && !i2s && !i3s && !i4s && !i5s && !i6s && !i7s && !i8s && !i9s && !i10s)
	{
		set_del(true);
	}
}

void CDie_Effect::show()
{
}

void CDie_Effect::Release()
{
	i1->set_del(true);
	i2->set_del(true);
	i3->set_del(true);
	i4->set_del(true);
	i5->set_del(true);
	i6->set_del(true);
	i7->set_del(true);
	i8->set_del(true);
	i9->set_del(true);
	i10->set_del(true);
}

CDie_Effect::~CDie_Effect()
{
}
