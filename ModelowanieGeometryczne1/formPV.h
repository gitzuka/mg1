#pragma once
#ifndef FORMPV_H
#define FORMPV_H
#include "ui_formPV.h"

class FormPV : public QWidget
{
	Q_OBJECT
public:
	explicit FormPV(QWidget *parent = 0);

	void initialize(const QString& name1, const QString& name2, const QVector4D& uvRange1, const QVector4D& uvRange2, const std::vector<QVector4D> &parametrization);

private:
	Ui::FormPV ui;
};

#endif