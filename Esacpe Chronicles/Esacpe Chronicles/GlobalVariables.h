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

// SoundManager Ŭ���� ���� ����
class SoundManager;

// ���� ���� ����
extern StageManager stageManager;
extern std::vector<std::unique_ptr<Monster>> monsters;
extern SoundManager soundManager; // �����ͷ� ����

#endif // GLOBALVARIABLES_H
