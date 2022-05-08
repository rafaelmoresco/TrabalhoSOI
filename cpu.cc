#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    // Salva o contexto atual no ponteiro recebido como parâmetro
    setcontext(&_context);
}

void CPU::Context::load()
{
    //Restaura o contexto salvo previamente no ponteiro recebido como parâmetro.
    getcontext(&_context);
}

CPU::Context::~Context()
{
    //Destrutor dos elementos de contexto contidos na pilha
    if(_stack != 0 ){
        delete[] _stack;
        _stack = 0;
    }
}

void CPU::switch_context(Context *from, Context *to)
{
    //Salva o contexto atual em "from" (primeiro argumento) e restaura o contexto previamente salvo em "to" (segundo argumento)
    swapcontext(&from->_context, &to->_context);	
}

__END_API
