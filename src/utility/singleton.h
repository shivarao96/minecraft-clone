#pragma once

class Singleton {
protected:
	Singleton()                            = default;
private:
	Singleton(const Singleton&)            = delete;
	Singleton(Singleton&&)                 = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&)      = delete;
};