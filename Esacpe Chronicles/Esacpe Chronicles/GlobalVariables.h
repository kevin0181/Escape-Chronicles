#pragma once

// GlobalVariables.h
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <vector>
#include "Slime.h"
#include "Zombie1.h"
#include "Zombie2.h"
#include "Zombie3.h"
#include "Brain1.h"
#include "Brain2.h"
#include "Boss.h"
#include "Eye.h"

// 전역 변수 선언
//extern std::vector<Slime> slimes; 
//extern std::vector<Zombie1> zombie1;
//extern std::vector<Zombie2> zombie2;
//extern std::vector<Zombie3> zombie3;
//extern std::vector<Brain1> brain1;
//extern std::vector<Brain2> brain2;
//extern std::vector<Boss> boss;
extern StageManager stageManager;
extern std::vector<std::unique_ptr<Monster>> monsters;

#endif // GLOBALVARIABLES_H
