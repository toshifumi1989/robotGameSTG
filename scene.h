#ifndef SCENE_H
#define SCENE_H

#include<assert.h>

template<class T>class Scene {
public:
	typedef void (T::*Process)(float);

	Scene() :
		_time(0),
		_prev(nullptr),
		_now(nullptr),
		_next(nullptr)
	{}

	~Scene(){}

	inline void run(T* obj, const float delta) {
		if (!_now && !_next)return;
		if (_next) {
			_prev = _now;
			_now = _next;
			_next = nullptr;
			_time = 0.0f;
		}
		(obj->*_now)(delta);
		_time += delta;
	}

	inline void change(const Process scene = nullptr) {
		if (!scene && !_next) {
			assert(0);
		}

		_next = scene;
		_time = 0.0f;
	}

	inline float getTime()const {
		return _time;
	}

private:
	float _time;
	Process _prev;
	Process _now;
	Process _next;

};



#endif
