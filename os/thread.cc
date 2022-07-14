#include "thread.h"
#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include <iostream>

__BEGIN_API
    Thread * Thread::_running = nullptr;
    unsigned int Thread::_thread_counter = 0;
    Thread Thread::_main; 
    CPU::Context Thread::_main_context; 
    Thread Thread::_dispatcher;
    Thread::System_Queue Thread::_ready;
    Thread::System_Queue Thread::_suspend;
    /*
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */ 
	void Thread::init(void (*main)(void *)){
		db<Thread>(TRC) << "Thread::init(void (*main)(void *))\n";

		new (&_main_context) Context();
		db<Thread>(TRC) << "Thread::init: Main context criado\n";
	
        new (&_main) Thread(main, (void *) "main"); 
		db<Thread>(TRC) << "Thread::init: Main thread criada\n";
		
		dequeue(&_main, _ready);
		_running = &_main;

        new (&_dispatcher) Thread((void (*) (void *)) &Thread::dispatcher, (void *) NULL);

        db<Thread>(TRC) << "Thread::init: Dispatcher thread foi criada\n";	

		CPU::switch_context(&_main_context, _main.context());
	}

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev)
     * e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno negativo se houve erro, ou zero.
     */ 
    int Thread::switch_context(Thread * prev, Thread * next) {
        db<Thread>(TRC)<<"Thread::switch_context()\n";
        if (prev != next) {
            _running = next;
            next->set_state(RUNNING);

            CPU::switch_context(prev->_context, next->_context);
        }
        return 0;
    }

    /*
     * Define um novo estado para a thread.
     */ 
    void Thread::set_state(Thread::State state){
        db<Thread>(TRC)<<"Thread::set_state(): Thread " << this->id() << " => ";

        switch(state){
            case 0:
                db<Thread>(TRC)<<"RUNNING\n";
                break;
            case 1:
                db<Thread>(TRC)<<"READY\n";
                break;
            case 2:
                db<Thread>(TRC)<<"FINISHING\n";
                break;
            case 3:
                db<Thread>(TRC)<<"SUSPENDED\n";
                break;
        }
        _state = state;
    }

    /*
     * Devolve o elemento da fila.
    */
    Thread::System_Queue::Element* Thread::link(){
        return &_link;
    }

    /*
     * Atualiza prioridade com timestamp.
    */
    void Thread::update_priority(){
		db<Thread>(TRC)<<"Thread::update_priority()\n";

		int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		link()->rank(now);
		db<Thread>(TRC)<<"Thread::update_priority: Thread " << id() << " prioridade atualizada para " << now << "\n";
    }

    /*
     * Adiciona thread na fila de prontos.
    */
    void Thread::enqueue(Thread * thread,Thread::System_Queue &queue){
	    db<Thread>(TRC)<<"Thread::enqueue(Thread * thread,Thread::System_Queue &queue)\n";

        if(thread == 0)
            return;

        if(thread == &_dispatcher)
            queue.insert_head(thread->link());
        else{
            thread->update_priority();
            queue.insert(thread->link());
        }

        db<Thread>(TRC)<<"Thread::insert_queue: Thread " << thread->id() << " inserida na fila ";
        if(&queue == &_ready){
            db<Thread>(TRC)<<" _ready\n";
            thread->set_state(READY);
        }
        else if (&queue == &_suspend){
            db<Thread>(TRC)<<" _suspend\n";
            thread->set_state(SUSPENDED);
        }
        else{
            db<Thread>(TRC)<<" _sleeping\n";
            thread->set_state(WAITING);
        }
    }

    /*
     * Remove thread na fila de prontos.
    */
	void Thread::dequeue(Thread * thread, Thread::System_Queue &queue){
		db<Thread>(TRC)<<"Thread::dequeue(Thread * thread, Thread::System_Queue &queue)\n";
		queue.remove(thread->link());

		db<Thread>(TRC)<<"Thread::remove_queue: Thread " << thread->id() << " removida da fila ";
		if(&queue == &_ready)
			db<Thread>(TRC)<<" _ready\n";
		else if (&queue == &_suspend)
			db<Thread>(TRC)<<" _suspend\n";
        else
			db<Thread>(TRC)<<" _sleeping\n";
	}

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
	void Thread::yield(){
		db<Thread>(TRC)<<"Thread::yield()\n";
		Thread *next_thread = next();
		if(next_thread != 0){
			if(_running->state() == RUNNING && _running != &_main) //se ela não estiver finishing e não for a main
				enqueue(_running,_ready); //insere no ready

			dequeue(next_thread, _ready);
			switch_context(_running, next_thread);
		}
	}

    /*
     * NOVO MÉTODO DESTE TRABALHO.
     * Daspachante (disptacher) de threads. 
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
	void Thread::dispatcher(){
        db<Thread>(TRC)<<"Thread::dispatcher()\n";
        while(!_ready.empty() && _ready.head()->object() != &_dispatcher) {

            Thread *next_thread = next(); //escolha uma próxima thread a ser executada
            Thread *prev_thread = _running;

            dequeue(next_thread, _ready);
            Thread::_thread_counter--;

            enqueue(&_dispatcher, _ready);
            _dispatcher.set_state(READY);
            switch_context(prev_thread, next_thread);
        }
        _dispatcher.set_state(FINISHING);
        dequeue(&_dispatcher, _ready);
        switch_context(&_dispatcher, &_main);
    }

    /*
    * Escolhe a thread mais antiga diferente da main.
    */
	Thread * Thread::next(){
		if(_ready.size() == 0){
			return 0;
		}
		return _ready.head()->object();
	}

    /*
     * Termina a thread.
     * exit_code Código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main. 
     */  
    void Thread::thread_exit(int exit_code) {
        db<Thread>(TRC)<<"Thread::exit()\n";

        set_state(FINISHING);
        this->_exit_code = exit_code;

        if(this->_joined != 0) {
            this->_joined->resume();
            this->_joined = 0;
        }
        Thread::yield();
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

    /*
     * Devolve o estado da thread.
    */
    Thread::State Thread::state() {
        return _state;
    }

    /*
     * Espera a thread acabar.
     */ 
    int Thread::join() {
        db<Thread>(TRC)<<"Thread::join()\n";
		if(this == _running) {
			db<Thread>(ERR)<<"Thread::join(): Thread " << this->id() << " tentou realizar join() em si mesma.\n";
			return -1;
        }

		if(this->_joined != 0) {
			db<Thread>(ERR)<<"Thread::join(): Thread " << this->id() << " recebeu join() de outra thread.\n";
			return -1;
        }
        if(this->state() == FINISHING) {
            return (this->_exit_code);
        }
        suspend();
        return (this->_exit_code);
    }

    /*
     * Faz a thread voltar a atividade.
     */ 
    void Thread::resume() {
        db<Thread>(TRC)<<"Thread::resume()\n";
        dequeue(this, _suspend);
        switch_context(_running, this);
    }

    void Thread::suspend() {
        db<Thread>(TRC)<<"Thread::suspend()\n";
		this->_joined = _running;
        _running->set_state(SUSPENDED);
        enqueue(_running, _suspend);    
        _running->yield();
    }

//vamo dormir porra
    void Thread::sleep(System_Queue &_sleeping){
		db<Thread>(TRC)<<"Thread::sleep()\n";

		enqueue(_running, _sleeping);
		_running->_sleepOrder = &_sleeping;
		yield();
	}

	void Thread::wakeup(System_Queue &_sleeping){
		db<Thread>(TRC)<<"Thread::wakeup()\n";
		if(_sleeping.size() != 0){
			Thread * thread = _sleeping.head()->object();
			Thread * prev = _running;

			dequeue(thread, _sleeping);
			enqueue(prev, _ready);
			
			thread->_sleepOrder = 0;

			switch_context(prev,thread);
		}
	}

	void Thread::wakeup_all(System_Queue &_sleeping){
		db<Thread>(TRC) << "Thread::wakeup_all()\n";
		Thread * thread = 0;
		while(_sleeping.size() > 0){
			thread = _sleeping.tail()->object();
			dequeue(thread, _sleeping);
			thread->set_state(READY);
			thread->_sleepOrder = 0;
			_ready.insert_head(thread->link());
		}
		yield();
	}

    /*
     * Destrutor de uma thread.
     */ 
	Thread::~Thread(){
		db<Thread>(TRC) << "Thread~Thread()\n";

        _ready.remove(this);

		if(_sleepOrder != 0){
			dequeue(this, *this->_sleepOrder);
		}
		delete _context;
	}
__END_API
