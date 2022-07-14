#ifndef traits_h
#define traits_h

//Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

//declaração das classes criadas nos trabalhos devem ser colocadas aqui
class CPU; 
class Debug;
class Thread;
class System;
class Lists;

//declaração da classe Traits
template<typename T>
struct Traits {
	static const bool debugged = true;
};

template<> struct Traits<System> 
{
    static const bool debugged = true;
};

template<> struct Traits<Lists> 
{
    static const bool debugged = true;
};

template<> struct Traits<Thread> : public Traits<void>
{
    static const bool debugged = true;
};

template<> struct Traits<CPU>
{
    static const unsigned int STACK_SIZE = 64512;
	static const bool debugged = true;
};

template<> struct Traits<Debug>: public Traits<void>
{
    static const bool error = false;
    static const bool warning = false;
    static const bool info = false;
    static const bool trace = false;
};

__END_API

#endif
