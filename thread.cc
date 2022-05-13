#include "thread.h"
#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include <iostream>

__BEGIN_API


    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */ 
    int Thread::switch_context(Thread * prev, Thread * next) {
        db<Thread>(TRC)<<"Thread::switch_context()\n";
        CPU::switch_context(prev->_context, next->_context);
        Thread::setRunning(next);
        return 0;
    }

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main. 
     */  
    void Thread::thread_exit (int exit_code) {
        db<Thread>(TRC)<<"Thread::exit()\n";
        delete[] Thread::_context;
    }

    /*
     * Retorna o ID da thread.
     */ 
    int Thread::id() {
        db<Thread>(TRC)<<"Thread::id()\n";
        return Thread::_id;
    }

    /*
     * Qualquer outro método que você achar necessário para a solução.
     */ 
    CPU::Context * volatile Thread::context() {
        db<Thread>(TRC)<<"Thread::context()\n";
        return Thread::_context;
    }

    void Thread::setRunning(Thread * running) {
        Thread::_running = running;
    }

__END_API
