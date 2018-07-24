#pragma once
#include <string>
#include <iostream>

class Zombie
{
public:
	Zombie();
	Zombie(int health);

	int getHealth();
	void z_initialise(int damage, std::string job);
	void damage(int damage);
	std::string getJob();
	int getDamage();
	void setHealth();

private:

	int z_health;
	int z_damage;
	std::string occupation;
};
