#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include "traits.h"

__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
        public:
            Context() { _stack = 0; }

            template<typename ... Tn>
            // Construtor do contexto 
            Context(void (* func)(Tn ...), Tn ... an){
                getcontext(&_context);
                _stack = new char[STACK_SIZE]; // alocação da pilha
                _context.uc_stack.ss_sp = &_stack; // ponteiro para o topo da pilha
                _context.uc_stack.ss_size = STACK_SIZE; // tamanho da pilha
                _context.uc_link = 0;
                _context.uc_stack.ss_flags=0;

                // 3º parametro é um inteiro que representa o número de argumentos
                // 4º parametro "..." representa os argumentos que podem receber qualquer número
                makecontext(&_context, (void(*)())func, sizeof ...(an), an...);
            }

            ~Context();

            void save();
            void load();

        private:            
            char *_stack;
        public:
            ucontext_t _context;
        };

    public:

        static void switch_context(Context *from, Context *to);

};

__END_API

#endif

