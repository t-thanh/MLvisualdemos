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
#ifndef _INTERFACEKMCLUSTER_H_
#define _INTERFACEKMCLUSTER_H_

#include <vector>
#include <interfaces.h>
#include "clustererKM.h"
#include "ui_paramsKM.h"

class ClustKM : public QObject, public ClustererInterface
{
	Q_OBJECT
	Q_INTERFACES(ClustererInterface)
private:
	QWidget *widget;
	Ui::ParametersKM *params;
public:
	ClustKM();
	// virtual functions to manage the algorithm creation
	Clusterer *GetClusterer();
	void DrawInfo(Canvas *canvas, QPainter &painter, Clusterer *clusterer);
	void DrawModel(Canvas *canvas, QPainter &painter, Clusterer *clusterer);

	// virtual functions to manage the GUI and I/O
	QString GetName(){return QString("KMeans");};
	QString GetAlgoString(){return GetName();};
	QString GetInfoFile(){return "kmeans.html";};
	QWidget *GetParameterWidget(){return widget;};
	void SetParams(Clusterer *clusterer);
	void SaveOptions(QSettings &settings);
	bool LoadOptions(QSettings &settings);
	void SaveParams(QTextStream &stream);
	bool LoadParams(QString name, float value);
};

#endif // _INTERFACEKMCLUSTER_H_
