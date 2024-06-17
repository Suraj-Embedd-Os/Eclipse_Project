/*
 * tabtenn0.cpp
 *
 *  Created on: 14-Jun-2024
 *      Author: suraj
 */

#include <iostream>
#include "tabtenn0.h"


TableTennisPlayers::TableTennisPlayers(const string & fn ="none",
			const string & ln ="none",bool ht =false):firstname(fn),
			lastname(ln),hasTable(ht){}

void TableTennisPlayers::Name()const
{
	std::cout<<"lastname "<<", "<<firstname;
}

