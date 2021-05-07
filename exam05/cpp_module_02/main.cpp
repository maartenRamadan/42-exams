#include "Warlock.hpp"
#include "Dummy.hpp"
#include "Fwoosh.hpp"
#include "Fireball.hpp"
#include "Polymorph.hpp"
#include "TargetGenerator.hpp"
#include "SpellBook.hpp"
#include "BrickWall.hpp"

int main()
{
	{
		Warlock const richard("Richard", "Mistress of Magma");
		richard.introduce();
		std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;

		Warlock* jack = new Warlock("Jack", "the Long");
		jack->introduce();
		jack->setTitle("the Mighty");
		jack->introduce();
  		
		delete jack;
	}

	{
		Warlock richard("Richard", "the Titled");

		Dummy bob;
		Fwoosh* fwoosh = new Fwoosh();

		richard.learnSpell(fwoosh);

		richard.introduce();
		richard.launchSpell("Fwoosh", bob);

		richard.forgetSpell("Fwoosh");
		richard.launchSpell("Fwoosh", bob);
	}
	{
		Warlock richard("Richard", "foo");
		richard.setTitle("Hello, I'm Richard the Warlock!");
		BrickWall model1;

		Polymorph* polymorph = new Polymorph();
		TargetGenerator tarGen;

		tarGen.learnTargetType(&model1);
		richard.learnSpell(polymorph);

		Fireball* fireball = new Fireball();

		richard.learnSpell(fireball);

		ATarget* wall = tarGen.createTarget("Inconspicuous Red-brick Wall");

		richard.introduce();
		richard.launchSpell("Polymorph", *wall);
		richard.launchSpell("Fireball", *wall);
	}
	// system("leaks a.out | grep bytes");
  return (0);
}