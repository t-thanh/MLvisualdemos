/*********************************************************************
MLDemos: A User-Friendly visualization toolkit for machine learning
Copyright (C) 2010  Basilio Noris
Contact: mldemos@b4silio.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*********************************************************************/
#include <QtSvg>
#include <QtGui>
#include <QWidget>
#include <QSize>
#include <QPixmap>
#include <QDebug>
#include <QMutexLocker>

#include "public.h"
#include "basicMath.h"
#include "drawSVG.h"

using namespace std;

DrawSVG::DrawSVG(Canvas *canvas, QMutex *mutex)
	: canvas(canvas),
	  classifier(0), regressor(0), dynamical(0), clusterer(0),
	  drawClass(0), drawRegr(0), drawDyn(0), drawClust(0),
	  mutex(mutex),
	  perm(0), w(0), h(0)
{
}

DrawSVG::~DrawSVG()
{

}

void DrawSVG::Write(QString filename)
{
	if(!canvas) return;
	QSvgGenerator generator;
	generator.setFileName(filename);
	generator.setSize(QSize(canvas->width(), canvas->height()));
	generator.setTitle("MLDemos screenshot");
	generator.setDescription("Generated with MLDemos");
	QPainter painter;
	painter.begin(&generator);
	// we need to paint the different layers:
	// confidence map
	// samples + trajectories + reward
	canvas->Paint(painter, true);

	if(canvas->bDisplayLearned)
	{
		// learned model
		if(classifier) drawClass->DrawModel(canvas, painter, classifier);
		if(regressor) drawRegr->DrawModel(canvas, painter, regressor);
		if(dynamical) drawDyn->DrawModel(canvas, painter, dynamical);
		if(clusterer) drawClust->DrawModel(canvas, painter, clusterer);
		if(dynamical)
		{
			int cnt = 10000; // not too many or it will make unreadable files
			int steps = 8;
			VectorsFast(cnt, steps, painter);
		}
		if(maximizer)
		{
			Maximization(painter);
		}
	}

	if(canvas->bDisplayInfo)
	{
		// model info
		if(classifier) drawClass->DrawInfo(canvas, painter, classifier);
		if(regressor) drawRegr->DrawInfo(canvas, painter, regressor);
		if(dynamical) drawDyn->DrawInfo(canvas, painter, dynamical);
		if(clusterer) drawClust->DrawInfo(canvas, painter, clusterer);
	}
	painter.end();
}

void DrawSVG::Vectors(int count, int steps, QPainter &painter)
{
	if(!dynamical) return;
	float dT = dynamical->dT;// * (dynamical->count/100.f);
	//float dT = 0.02f;
	fvec sample;
	sample.resize(2,0);
	int w = canvas->width();
	int h = canvas->height();

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
	vector<Obstacle> obstacles = canvas->data->GetObstacles();

	QPointF oldPoint(-FLT_MAX,-FLT_MAX);
	QPointF oldPointUp(-FLT_MAX,-FLT_MAX);
	QPointF oldPointDown(-FLT_MAX,-FLT_MAX);
	FOR(i, count)
	{
		QPointF samplePre(rand()/(float)RAND_MAX * w, rand()/(float)RAND_MAX * h);
		sample = canvas->toSampleCoords(samplePre);
		float color = (rand()/(float)RAND_MAX*0.7f)*255.f;
		color = 0;
		QPointF oldPoint = canvas->toCanvasCoords(sample);
		FOR(j, steps)
		{
			fvec res = dynamical->Test(sample);
			if(dynamical->avoid)
			{
				dynamical->avoid->SetObstacles(obstacles);
				fvec newRes = dynamical->avoid->Avoid(sample, res);
				res = newRes;
			}
			sample += res*dT;
			float speed = sqrtf(res[0]*res[0] + res[1]*res[1]);
			QPointF point = canvas->toCanvasCoords(sample);
			painter.setOpacity(speed);
			QColor c(color,color,color);
			painter.setPen(QPen(c, 0.25));
			painter.drawLine(point, oldPoint);
			oldPoint = point;
		}
	}
}

void DrawSVG::Maximization(QPainter &painter)
{
	if(!maximizer) return;
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
	maximizer->Draw(painter);
}

void DrawSVG::VectorsFast(int count, int steps, QPainter &painter)
{
	if(!dynamical) return;
	QPointF oldPoint(-FLT_MAX,-FLT_MAX);
	QPointF oldPointUp(-FLT_MAX,-FLT_MAX);
	QPointF oldPointDown(-FLT_MAX,-FLT_MAX);
	float dT = dynamical->dT;// * (dynamical->count/100.f);
	//float dT = 0.02f;
	fvec sample;
	sample.resize(2,0);
	int w = canvas->width();
	int h = canvas->height();

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
	vector<Obstacle> obstacles = canvas->data->GetObstacles();
	FOR(i, count)
	{
		QPointF samplePre(rand()/(float)RAND_MAX * w, rand()/(float)RAND_MAX * h);
		sample = canvas->toSampleCoords(samplePre);
		float color = (rand()/(float)RAND_MAX*0.7f)*255.f;
		color = 0;
		QPointF oldPoint = canvas->toCanvasCoords(sample);
		FOR(j, steps)
		{
			fvec res = dynamical->Test(sample);
			if(dynamical->avoid)
			{
				dynamical->avoid->SetObstacles(obstacles);
				fvec newRes = dynamical->avoid->Avoid(sample, res);
				res = newRes;
			}
			sample += res*dT;
			float speed = sqrtf(res[0]*res[0] + res[1]*res[1]);
			QPointF point = canvas->toCanvasCoords(sample);
			painter.setOpacity(speed);
			QColor c(color,color,color);
			painter.setPen(QPen(c, 0.25));
			painter.drawLine(point, oldPoint);
			oldPoint = point;
		}
	}
}
