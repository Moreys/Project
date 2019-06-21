 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-08 10:55:15
 ///
 

#pragma once

namespace wd
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable() {}

	Noncopyable(const Noncopyable &) = delete;
	Noncopyable & operator=(const Noncopyable &) = delete;

};


}//end of namespace wd
