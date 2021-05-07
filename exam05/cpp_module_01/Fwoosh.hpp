#pragma once

# include <string>
# include <iostream>

# include "ASpell.hpp"

class Fwoosh : public ASpell
{
	public:
		Fwoosh();
		virtual ~Fwoosh();

		Fwoosh* clone() const;
};
