#pragma once
#include <QObject.h>
#include <memory>
#include "drawableObject.h"

class Ui_ModelowanieGeometryczne1Class;

class UiConnector : public QObject
{
	Q_OBJECT
public:
	virtual ~UiConnector() {}

	virtual void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const = 0;
	virtual std::shared_ptr<DrawableObject> getObject() = 0;

public slots:
	virtual void changeName(const QString &name, int id) = 0;
};
