/*********************************************************************
MLDemos: A User-Friendly visualization toolkit for machine learning
Copyright (C) 2010  Basilio Noris
Contact: mldemos@b4silio.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License,
version 3 as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*********************************************************************/
#ifndef _INTERFACEMLPDYNAMIC_H_
#define _INTERFACEMLPDYNAMIC_H_

#include <vector>
#include <interfaces.h>
#include "dynamicalMLP.h"
#include "ui_paramsMLPDynamic.h"

class DynamicMLP : public QObject, public DynamicalInterface
{
	Q_OBJECT
	Q_INTERFACES(DynamicalInterface)
private:
	QWidget *widget;
	Ui::ParametersMLPDynamic *params;
public:
	DynamicMLP();
	// virtual functions to manage the algorithm creation
	Dynamical *GetDynamical();
	void DrawInfo(Canvas *canvas, QPainter &painter, Dynamical *dynamical){};
	void DrawModel(Canvas *canvas, QPainter &painter, Dynamical *dynamical){};

	// virtual functions to manage the GUI and I/O
	QString GetName(){return QString("MLP");};
	QString GetAlgoString(){return GetName();};
	QString GetInfoFile(){return "mlp.html";};
	bool UsesDrawTimer(){return true;};
	QWidget *GetParameterWidget(){return widget;};
	void SetParams(Dynamical *dynamical);
	void SaveOptions(QSettings &settings);
	bool LoadOptions(QSettings &settings);
	void SaveParams(QTextStream &stream);
	bool LoadParams(QString name, float value);
};

#endif // _INTERFACEMLPDYNAMIC_H_
