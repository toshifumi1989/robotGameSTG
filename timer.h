#ifndef TIEMR_H
#define TIMER_H

class Timer {
public:
	Timer() :
		ms(0),
		second(0),
		minute(0),
		count(0)
	{}
	~Timer() {}

	void update();
	void draw();
private:
	float count;
	float ms;
	unsigned char second;
	unsigned char minute;
};


#endif