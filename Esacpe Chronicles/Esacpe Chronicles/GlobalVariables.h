#pragma once

// GlobalVariables.h
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <vector>
#include "Slime.h"
#include "Brain1.h"
#include "Brain2.h"
#include "Boss.h"
#include "Eye.h"

// SoundManager 클래스 전방 선언
class SoundManager;

// 전역 변수 선언
extern StageManager stageManager;
extern std::vector<std::unique_ptr<Monster>> monsters;
extern SoundManager soundManager; // 포인터로 선언

#endif // GLOBALVARIABLES_H
