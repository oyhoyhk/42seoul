#include <iostream>
#include <utility>

#include "Character.hpp"

Character::Character()
{
}

Character::Character(std::string name)
{
	_name = name;
	_itemCount = 0;
	for (int i=0; i<4; i++)
		_inventory[i] = nullptr;
}

Character::Character(const Character& ref)
{
	this->_name = ref._name;
	this->_itemCount = ref._itemCount;
	for(int i=0;i<4;i++)
		this->_inventory[i] = ref._inventory[i];
}

Character::~Character()
{
	for(int i=0;i<4;i++)
		if (_inventory[i] != nullptr)
			delete _inventory[i];
}

Character&	Character::operator=(const Character& ref)
{
	if (this != &ref) {
		this->_name = ref._name;
		this->_itemCount = ref._itemCount;
		for(int i=0;i<4;i++)
		{
			if (this->_inventory[i]) delete this->_inventory[i];
			this->_inventory[i] = ref._inventory[i];
		}
	}
	return (*this);
}

std::string const &Character::getName() const
{
	return _name;
}

void	Character::equip(AMateria* m)
{
	if (m == nullptr || _itemCount == 4 || (m->getType() != "ice" && m->getType() != "cure"))
		return ;
	int idx = 0;
	for(int i=0;i<4;i++)
	{
		if (_inventory[i] == nullptr) {
			idx = i;
			break;
		}
	}
	_inventory[idx] = m;
	_itemCount += 1;
}

void	Character::unequip(int idx)
{
	if (_inventory[idx] == nullptr)
		return ;
	_inventory[idx] = nullptr;
}

void	Character::use(int idx , ICharacter& target)
{
	if (_inventory[idx] == nullptr)
		return ;
	_inventory[idx]->use(target);
}