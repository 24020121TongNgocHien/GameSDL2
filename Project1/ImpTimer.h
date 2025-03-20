#ifndef IMP_TIMER_H_
#define	IMP_TIMER_H_

#include"CommonFunc.h"
class ImpTimer {
public:
	ImpTimer();
	~ImpTimer();

	void start();
	void stop();
	void pause();
	void unpause();
	int getTicks();
	bool is_Pause();
	bool is_Start();

private:
	int startTick;
	int pauseTick;

	bool isPause;
	bool isStarted;


};
#endif // !IMP_TIMER_H_
