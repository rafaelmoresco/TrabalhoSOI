#include "thread.h"
#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include <iostream>

__BEGIN_API
    Thread * Thread::_running = nullptr;
    static unsigned int Thread::_thread_counter = 0;

    /*
     * MÃ©todo para trocar o contexto entre duas thread, a anterior (prev)
     * e a prÃ³xima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno Ã© negativo se houve erro, ou zero.
     */ 
    int Thread::switch_context(Thread * prev, Thread * next) {
        db<Thread>(TRC)<<"Thread::switch_context()\n";
        try {
            _running = next;
			CPU::switch_context(prev->_context, next->_context);
            //Thread::setRunning(next);
        } catch (...) {
            return -1;
        }
        return 0;
    }

    /*
     * Termina a thread.
     * exit_code Ã© o cÃ³digo de tÃ©rmino devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar Ã  main. 
     */  
    void Thread::thread_exit (int exit_code) {
        db<Thread>(TRC)<<"Thread::exit()\n";
        Thread::_thread_counter--;
        delete Thread::_context;
    }

    /*
     * Retorna o ID da thread.
     */ 
    int Thread::id() {
        db<Thread>(TRC)<<"Thread::id()\n";
        return Thread::_id;
    }

    /*
     * Qualquer outro mÃ©todo que vocÃª achar necessÃ¡rio para a soluÃ§Ã£o.
     */ 
    CPU::Context * volatile Thread::context() {
        db<Thread>(TRC)<<"Thread::context()\n";
        return Thread::_context;
    }


__END_API
