#pragma once

# include <string>
# include <iostream>
# include <map>

#include "ATarget.hpp"

class SpellBook
{
	private:
		std::map<std::string, ASpell*> _spellbook;

		SpellBook(const SpellBook& rhs);
		SpellBook& operator=(const SpellBook& rhs);

	public:
		SpellBook();
		~SpellBook();

		void learnSpell(ASpell* spell);
		void forgetSpell(const std::string& spell);
		ASpell* createSpell(const std::string& spell);
};
