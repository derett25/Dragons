// Class that represents a custom timer
// Author: Linus Esbjörnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// Högskolan i Skövde

#ifndef INCLUDED_GAMETIMER
#define INCLUDED_GAMETIMER

class GameTimer {
public:
	GameTimer();
	GameTimer(long ms);
	~GameTimer();
	void setTimer(long ms);
	bool isExpired() const;
	void restartTimer();
private:
	long mEndTicks;
	long mTimerLength;
};

#endif