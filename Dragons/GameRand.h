// Class used to generate pseudorandom numbers using Mersenne twister engine
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMERAND
#define INCLUDED_GAMERAND

#include <random>

struct GameRand {
	typedef std::uniform_int_distribution<int> RNG;
	static void initialize();
	static int randomNumber(int min, int max);
	static bool randomPercentage(float percent);
};

#endif
