#include "stdafx.h"


CObj_management *CObj_management::instance = NULL;
CObj_management * CObj_management::Getinstance()
{
	if (!instance)
		instance = new CObj_management;
	return instance;
}

void CObj_management::add(CObj * Obj)
{
	obj_list.push_back(Obj);
}

void CObj_management::update()
{
	obj_list.sort(sort());
	list<CObj*>::iterator itea;
	for (itea = obj_list.begin();itea != obj_list.end();)
	{
		if ((*itea)->get_del())
		{
			(*itea)->Release();
			delete (*itea);
			(*itea) = NULL;
			obj_list.erase(itea++);
		}
		else
		{
			if ((*itea)->get_show())
			{
				(*itea)->show();
				(*itea)->update();
				itea++;
			}
			else
			{
				itea++;
			}
			
		}
	}
}

int CObj_management::get_class_obj_num(CObj::class_id classid)
{
	list<CObj*>::iterator itea;
	int class_size = 0;
	for (itea = obj_list.begin();itea != obj_list.end();itea++)
	{
		
		if ((*itea)->id == classid)
		{
			class_size++;
		}
	}
	return class_size;
}

void CObj_management::clean_class(CObj::class_id classid)
{
	list<CObj*>::iterator itea;
	for (itea = obj_list.begin();itea != obj_list.end();)
	{
		//const char *name = typeid(*itea).name();
		if ((*itea)->id == classid)
		{
			(*itea)->Release();
			delete (*itea);
			(*itea) = NULL;
			obj_list.erase(itea++);
		}
		else
		{
			itea++;
		}


	}
}

CObj_management::CObj_management()
{

}


CObj_management::~CObj_management()
{
}

bool CObj_management::sort::operator()(CObj *a, CObj *b)
{
	if (a->get_sort() > b->get_sort())
		return true;
	return false;
}
