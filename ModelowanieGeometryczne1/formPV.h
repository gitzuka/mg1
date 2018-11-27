#pragma once
#ifndef FORMPV_H
#define FORMPV_H
#include "ui_formPV.h"
#include <memory>
class DrawableObject;

class FormPV : public QWidget
{
	Q_OBJECT
public:
	explicit FormPV(QWidget *parent = 0);

	void initialize(std::shared_ptr<DrawableObject> surface1, std::shared_ptr<DrawableObject> surface2,
		const QVector4D& uvRange1, const QVector4D& uvRange2, const std::vector<QVector4D>& parametrization,
		QPair<bool, bool> s1Wrap, QPair<bool, bool> s2Wrap);

private:
	Ui::FormPV ui;
	std::vector<std::vector<bool>> m_map1;
	std::vector<std::vector<bool>> m_map2;
	std::shared_ptr<DrawableObject> m_surface1;
	std::shared_ptr<DrawableObject> m_surface2;

	private slots:
	void buttonTrim1Clicked();
	void buttonTrim2Clicked();
	void buttonTrimExt1Clicked();
	void buttonTrimExt2Clicked();
};

#endif