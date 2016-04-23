#ifndef JOYSTIC_H
#define JOYSTIC_H

class Joystic {
public:

	Joystic() :
		buttonMask(0),
		x(0),
		y(0),
		z(0),
		lastkeys(0)
	{}

	~Joystic() {}

	void input(unsigned int _buttonMask, int _x, int _y, int _z);

	static Joystic* getInstance();
	
	unsigned int buttonMask;
	int x;
	int y;
	int z;
	

private:
	static Joystic* instance;
	int lastkeys;
};



#endif
