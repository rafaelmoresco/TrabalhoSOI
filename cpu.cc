#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    db<CPU>(TRC)<<"CPU::Context::save()\n";
    // Salva o contexto atual no ponteiro recebido como parâmetro
    setcontext(&_context);
}

void CPU::Context::load()
{
    db<CPU>(TRC)<<"CPU::Context::load()\n";
    //Restaura o contexto salvo previamente no ponteiro recebido como parâmetro.
    getcontext(&_context);
}

CPU::Context::~Context()
{
    db<CPU>(TRC)<<"CPU::Context::~Context()\n";
    //Destrutor dos elementos de contexto contidos na pilha
    if(_stack != 0 ){
        delete[] _stack;
        _stack = 0;
    }
}

void CPU::switch_context(Context *from, Context *to)
{
    db<CPU>(TRC)<<"CPU::Context::switch_context\n";
    //Salva o contexto atual em "from" (primeiro argumento) e restaura o contexto previamente salvo em "to" (segundo argumento)
    swapcontext(&from->_context, &to->_context);	
}

__END_API
