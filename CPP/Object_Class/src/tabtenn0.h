/*
 * tabtenn0.h
 *
 *  Created on: 14-Jun-2024
 *      Author: suraj
 */

#ifndef TABTENN0_H_
#define TABTENN0_H_
#include<string>

using std::string;

class TableTennisPlayers
{
private:
	string firstname;
	string lastname;
	bool hasTable;
public:
	TableTennisPlayers(const string & fn ="none",
			const string & ln ="none",bool ht =false);
	void Name()const;
	bool HasTable()const {return hasTable;}
	void resetTable(bool v) {hasTable=v;}

};


#endif /* TABTENN0_H_ */
