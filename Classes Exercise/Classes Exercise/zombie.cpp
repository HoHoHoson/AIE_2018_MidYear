#include "zombie.h"


Zombie::Zombie()
{
	z_health = 100;
	std::cout << z_health << std::endl;
}

Zombie::Zombie(int hfnalth)
{
	z_health = hfnalth;
	std::cout << "Inside Knight overrided constructor" << std::endl;
}

int Zombie::getHealth()
{
	return z_health;
}

std::string Zombie::getJob()
{
	return occupation;
}

int Zombie::getDamage()
{
	return z_damage;
}

void Zombie::z_initialise(int setDmg, std::string setJob)
{
	z_damage = setDmg;
	occupation = setJob;
}

void Zombie::damage(int dmg)
{
	z_health -= dmg;
}