//PenaltyFunction.h

#pragma once
#include <iostream>
#include <string>
#include "PiecewiseLinearFunction.h"
#include "CustomerTemplateForm.h"
#include "SettingsGenerator.h"
using namespace std;

class PenaltyFunction : public PiecewiseLinearFunction {

	public :
		PenaltyFunction() {}
		PenaltyFunction(const CustomerTemplateForm& filledOutTemplateForm, const SettingsGenerator& settings);	
	private :

};
