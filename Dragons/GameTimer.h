// Class that represents a custom timer
// Author: Linus Esbj�rnsson || a12lines
// Mail: linuse93@hotmail.com || a12lines@student.his.se
// Department of Communication and Information
// H�gskolan i Sk�vde

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