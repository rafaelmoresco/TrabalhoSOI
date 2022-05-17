#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;

public:
    Thread() {
        db<Thread>(TRC) << "Thread::Thread()\n";
        _id = -1;
        db<Thread>(TRC) << "Thread::Thread: Criou thread" << _id << "\n";
    }

    /*
     * Cria uma Thread passando um ponteiro para a funÃ§Ã£o a ser executada
     * e os parÃ¢metros passados para a funÃ§Ã£o, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este mÃ©todo deve ser implementado neste mesmo arquivo .h
     */ 
    template<typename ... Tn>
    inline Thread(void (* entry)(Tn ...), Tn ... an) {
        db<Thread>(TRC) << "Thread::Thread(void (* entry)(Tn ...), Tn ... an)\n";
        _context = new Context(entry, (char *) an...);
        _id = _thread_counter++;
		if (!(_context)) {
            throw "falha em criar contexto";
        }
    }

    /*
     * Retorna a Thread que estÃ¡ em execuÃ§Ã£o.
     */ 
    static Thread * running() { 
        db<Thread>(TRC)<<"Thread::running()\n";
        return _running; 
    }

    /*
     * MÃ©todo para trocar o contexto entre duas thread, a anterior (prev)
     * e a prÃ³xima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno Ã© negativo se houve erro, ou zero.
     */ 
    static int switch_context(Thread * prev, Thread * next);

    /*
     * Termina a thread.
     * exit_code Ã© o cÃ³digo de tÃ©rmino devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar Ã  main. 
     */  
    void thread_exit (int exit_code);

    /*
     * Retorna o ID da thread.
     */ 
    int id();

    /*
     * Qualquer outro mÃ©todo que vocÃª achar necessÃ¡rio para a soluÃ§Ã£o.
     */

    Context * volatile context(); 

private:
    int _id;
    Context * volatile _context;
    static Thread * _running;
    static unsigned int _thread_counter;

    /*
     * Qualquer outro atributo que vocÃª achar necessÃ¡rio para a soluÃ§Ã£o.
     */ 
};

__END_API

#endif
