#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::TargetGenerator(const TargetGenerator& rhs) {
	*this = rhs;
}

TargetGenerator& TargetGenerator::operator=(const TargetGenerator& rhs) {
	(void)rhs;
	return *this;
}

TargetGenerator::~TargetGenerator() {
	for (std::map<std::string, ATarget*>::iterator it = _targetTypes.begin(); it != _targetTypes.end(); ++it)
		delete it->second;
}

void TargetGenerator::learnTargetType(ATarget* targetType) {
	_targetTypes[targetType->getType()] = targetType->clone();
}

void TargetGenerator::forgetTargetType(const std::string& TargetType) {
	std::map<std::string, ATarget*>::iterator it = _targetTypes.find(TargetType);
	if (it != _targetTypes.end()) {
		delete it->second;
		_targetTypes.erase(TargetType);
	}
}

ATarget* TargetGenerator::createTarget(const std::string& targetType) {
	std::map<std::string, ATarget*>::iterator it = _targetTypes.find(targetType);
	if (it != _targetTypes.end())
		return it->second;
	return NULL;
}
