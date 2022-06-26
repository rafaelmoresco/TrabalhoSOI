#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include <ctime> 
#include <chrono>

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;
public:

    typedef Ordered_List<Thread> System_Queue;

    // Thread State
    enum State {
        RUNNING,
        READY,
        FINISHING,
        SUSPENDED,
        WAITING
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */ 
    Thread() { }

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada
     * e os parâmetros passados para a função, que podem variar.
     * Cria o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */ 
    template<typename ... Tn>
    Thread(void (* entry)(Tn ...), Tn ... an);

    /*
     * Retorna a Thread que está em execução.
     */ 
    static Thread * running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero.
     */ 
    static int switch_context(Thread *prev, Thread *next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main. 
     */  
    void thread_exit (int exit_code);

    /*
     * Retorna o ID da thread.
     */ 
    int id();

    /*
     * Daspachante (disptacher) de threads. 
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher(); 

    /*
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */ 
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield(); 

    /*
     * Qualquer outro método que você achar necessário para a solução.
     */

    /*
     * Espera a thread esperar a próxima.
     */ 
    int join();

    /*
     * Faz a thread voltar a atividade.
     */ 
    void resume();

    /*
     * Faz a thread parar.
     */ 
    void suspend();


    /*
     * Devolve o contexto da thread para a CPU.
    */
    Context * volatile context(); 

    /*
     * Define um novo estado para a thread.
     */ 
    void set_state(State state);

    /*
     * Devolve o estado da thread.
    */
    State state();

    /*
     * Adiciona thread na fila de prontos.
    */
    static void enqueue(Thread * thread, System_Queue &queue);

    /*
     * Remove thread na fila de prontos.
    */
    static void dequeue(Thread * thread, System_Queue &queue);

    /*
     * Devolve o elemento da fila.
    */
    System_Queue::Element * link();

    /*
     * Atualiza prioridade com timestamp.
    */
    void update_priority();

    /*
    * Escolhe a thread mais antiga diferente da main
    */
    static Thread * next();

    static void sleep(System_Queue &_sleeping);

    static void wakeup(System_Queue &_sleeping);

    static void wakeup_all(System_Queue &_sleeping);

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */ 
    ~Thread();

private:
    int _id;
    Context * volatile _context;
    static Thread * _running;
    
    static Thread _main; 
    static CPU::Context _main_context;
    static Thread _dispatcher;
    static System_Queue _ready;
    static System_Queue _suspend;
    System_Queue *_sleepOrder;
    System_Queue::Element _link;
    volatile State _state;
    Thread * _joined;
    Thread * _wait;
    volatile int _exit_code;

    /*
     * Qualquer outro atributo que você achar necessário para a solução.
     */ 
    static unsigned int _thread_counter;
};

template<typename ... Tn>
inline Thread::Thread(void (* entry)(Tn ...), Tn ... an) { /* inicialização de _link */
    db<Thread>(TRC)<<"Thread::Thread(void (* entry)(Tn ...), Tn ... an)\n";
    _id = _thread_counter;
    _thread_counter++;
    _context = new Context(entry, an...);

    new (&_link) System_Queue::Element(this,(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));
    enqueue(this, _ready);

    db<Thread>(INF)<<"Thread::Thread(void (* entry)(Tn ...), Tn ... an): Contador de threads: = " << _thread_counter << "\n";
    db<Thread>(TRC)<<"Thread::Thread(void (* entry)(Tn ...), Tn ... an): Thread " << _id << " criada\n";
}

__END_API

#endif