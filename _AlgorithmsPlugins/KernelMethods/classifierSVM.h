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
#ifndef _CLASSIFIER_SVM_H_
#define _CLASSIFIER_SVM_H_

#include <vector>
#include <map>
#include <classifier.h>
#include "svm.h"

class ClassifierSVM : public Classifier
{
private:
	svm_model *svm;
	svm_node *node;
	svm_node *x_space;
	int classCount;
public:
	std::map<int,int> classes;
	svm_parameter param;

	ClassifierSVM();
	~ClassifierSVM();
	void Train(std::vector< fvec > samples, ivec labels);
	float Test(const fvec &sample);
	float Test(const fVec &sample);
	fvec TestMulti(const fvec &sample);
	char *GetInfoString();
	void SetParams(int svmType, float svmC, u32 kernelType, float kernelParam);
	svm_model *GetModel(){return svm;};
};

#endif // _CLASSIFIER_SVM_H_
