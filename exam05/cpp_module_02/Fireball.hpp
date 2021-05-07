#pragma once

# include <string>
# include <iostream>

# include "ASpell.hpp"

class Fireball : public ASpell
{
	public:
		Fireball();
		virtual ~Fireball();

		Fireball* clone() const;
};
