#pragma once

# include <string>
# include <iostream>
# include <map>

#include "ATarget.hpp"

class TargetGenerator
{
	private:
		std::map<std::string, ATarget*> _targetTypes;

		TargetGenerator(const TargetGenerator& rhs);
		TargetGenerator& operator=(const TargetGenerator& rhs);

	public:
		TargetGenerator();
		~TargetGenerator();

		void learnTargetType(ATarget* targetType);
		void forgetTargetType(const std::string& targetType);
		ATarget* createTarget(const std::string& targetType);
};
