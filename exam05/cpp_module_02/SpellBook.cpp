#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::SpellBook(const SpellBook& rhs) {
	*this = rhs;
}

SpellBook& SpellBook::operator=(const SpellBook& rhs) {
	(void)rhs;
	return *this;
}

SpellBook::~SpellBook() {
	for (std::map<std::string, ASpell*>::iterator it = _spellbook.begin(); it != _spellbook.end(); ++it)
		delete it->second;
}

void SpellBook::learnSpell(ASpell* spell) {
	_spellbook[spell->getName()] = spell->clone();
}

void SpellBook::forgetSpell(const std::string& spell) {
	std::map<std::string, ASpell*>::iterator it = _spellbook.find(spell);
	if (it != _spellbook.end()) {
		delete it->second;
		_spellbook.erase(spell);
	}
}

ASpell* SpellBook::createSpell(const std::string& spell) {
	std::map<std::string, ASpell*>::iterator it = _spellbook.find(spell);
	if (it != _spellbook.end())
		return it->second;
	return NULL;
}
