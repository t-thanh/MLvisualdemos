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
#include "pluginMaximizers.h"
#include "interfaceBasic.h"
#include "interfaceGA.h"
#include "interfaceParticles.h"

using namespace std;

PluginMaximizer::PluginMaximizer()
{
	maximizers.push_back(new MaximizeBasic());
	maximizers.push_back(new MaximizeInterfaceGA());
	maximizers.push_back(new MaximizeInterfaceParticles());
}

#ifndef PLUGIN_MAXIMIZE
Q_EXPORT_PLUGIN2(mld_Maximizer, PluginMaximizer)
#endif
