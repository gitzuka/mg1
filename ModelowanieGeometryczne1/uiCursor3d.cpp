#include "uiCursor3d.h"
#include "modelowaniegeometryczne1.h"
#include "cursor3d.h"

UiCursor3D::UiCursor3D(std::shared_ptr<Cursor3D> cursor3d) : m_cursor3d(cursor3d)
{
}

void UiCursor3D::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{

}

std::shared_ptr<DrawableObject> UiCursor3D::getObject()
{
	return m_cursor3d;
}

//no name required
void UiCursor3D::changeName(const QString& name, int id)
{
	/*if (id == m_cursor3d->)
	m_cursor3d->setName(name);*/
}
