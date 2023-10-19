#include <cstdio>
#include <emscripten.h>
#include <string>

#ifdef __EMSCRIPTEN_PTHREADS__
    #include <pthread.h>
#endif

#ifdef __EMSCRIPTEN_WASM_WORKERS__
    #include <emscripten/wasm_worker.h>
#endif




void Alert(std::string s)
{
    s = "alert('" + s + "');";
    emscripten_run_script(s.c_str());
}

void Info(std::string s)
{
    s = "Info('" + s + "');";
    emscripten_run_script(s.c_str());
}













int ThrCounter;
bool ThrWork;

#ifdef __EMSCRIPTEN_PTHREADS__
    pthread_t Thr;
#endif
#ifdef __EMSCRIPTEN_WASM_WORKERS__
    emscripten_wasm_worker_t Wrk;
#endif


void ThrTestProc()
{
    ThrCounter++;
}

void * ThrTestProc0(void *arg)
{
    ThrTestProc();
    return 0;
}


void ThrProc()
{
    ThrCounter = 0;
    ThrWork = true;
    while (ThrWork)
    {
        ThrCounter++;
    }
}

void * ThrProc0(void *arg)
{
    ThrProc();
    return 0;
}



EMSCRIPTEN_KEEPALIVE
void ThrTest()
{
    Info("Thread test invoke start");
    #ifdef __EMSCRIPTEN_PTHREADS__
        pthread_create(&Thr, NULL, ThrTestProc0, (void *)NULL);
    #endif
    #ifdef __EMSCRIPTEN_WASM_WORKERS__
        Wrk = emscripten_malloc_wasm_worker(1024);
        emscripten_wasm_worker_post_function_v(Wrk, ThrTestProc);
    #endif
    Info("Thread test invoke stop");
}


EMSCRIPTEN_KEEPALIVE
int ThrStart()
{
    int result = 0;
    #ifdef __EMSCRIPTEN_PTHREADS__
        result = pthread_create(&Thr, NULL, ThrProc0, (void *)NULL);
    #endif
    #ifdef __EMSCRIPTEN_WASM_WORKERS__
        Wrk = emscripten_malloc_wasm_worker(1024);
        emscripten_wasm_worker_post_function_v(Wrk, ThrProc);
    #endif
    return result;
}

EMSCRIPTEN_KEEPALIVE
int ThrStop()
{
    ThrWork = false;
    #ifdef __EMSCRIPTEN_PTHREADS__
        int result = pthread_join(Thr, NULL);
    #endif
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int ThrStatus()
{
    return ThrCounter;
}












int main()
{
    printf("Thread test\n");

#ifdef __EMSCRIPTEN_PTHREADS__
    printf("Posix thread\n");
#endif
    
#ifdef __EMSCRIPTEN_WASM_WORKERS__
    printf("Wasm worker\n");
#endif
    
    return 0;
}

