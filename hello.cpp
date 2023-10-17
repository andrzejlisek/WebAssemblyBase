#include <iostream> 
#include <cstdlib> 
#include <emscripten.h>
#include <string>

//#define UseThr
//#include <pthread.h>

//#define UseWrk
//#include <emscripten/wasm_worker.h>


const char * StrTest()
{
  return "Hello World";
}




EM_JS(void, callback1, (), {
  alert('hai');
  alert('bai');
});

EM_JS(int, callback2, (int x, float y), {
  console.log('I received: ' + [x, y]);
});

EM_JS(int, callback3, (const char * s), {
  console.log('I received: ' + [x, y]);
});


int CallbackTest(int n)
{
    switch (n)
    {
        case 1:
            callback1();
            return 555;
        case 2:
            return callback2(147, 85.25);
        case 3:
            return callback3("Hello from callback");
        case 4:
            emscripten_run_script("alert('hi')");
            return 0;
        default:
            return 0;
    }
}

int fib(int x)
{
  if (x < 1)
    return 0;
  if (x == 1)
    return 1;
  return fib(x-1)+fib(x-2);
}

int ThrCounter;
bool ThrWork;

#ifdef UseThr
    pthread_t Thr;
#endif
#ifdef UseWrk
    emscripten_wasm_worker_t Wrk;
#endif

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

int ThrStart()
{
    int result = 0;
    #ifdef UseThr
        result = pthread_create(&Thr, NULL, ThrProc0, (void *)NULL);
    #endif
    #ifdef UseWrk
        Wrk = emscripten_malloc_wasm_worker(1024);
        emscripten_wasm_worker_post_function_v(Wrk, ThrProc);
    #endif
    return result;
}

int ThrStop()
{
    /*ThrWork = false;
    #ifdef UseThr
        int result = pthread_join(Thr, NULL);
    #endif*/
    return 0;
}

int ThrStatus()
{
    //return ThrCounter;
    return 0;
}

