#include "intersectableObject.h"

IntersectableObject::IntersectableObject(bool uWrapped, bool vWrapped) :
		m_uWrapped(uWrapped), m_vWrapped(vWrapped)
{
	
}

bool IntersectableObject::isUWrapped() const
{
	return m_uWrapped;
}

bool IntersectableObject::isVWrapped() const
{
	return m_vWrapped;
}
