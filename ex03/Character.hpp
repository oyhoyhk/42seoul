#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include "AMateria.hpp"

class Character : public ICharacter
{
private:
	std::string _name;
	int	_itemCount;
	AMateria *_inventory[4];
public:
	Character();
	Character(std::string name);
	Character(const Character& ref);
	~Character();

	Character&	operator=(const Character& ref);

	std::string const & getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);
	AMateria *getInventory(void);
};

#endif
