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

// 전역 변수 선언
static std::vector<Slime> slimes; 
static std::vector<Zombie1> zombie1;
static std::vector<Zombie2> zombie2;
static std::vector<Zombie3> zombie3;
static std::vector<Brain1> brain1;
static std::vector<Brain2> brain2;

#endif // GLOBALVARIABLES_H
