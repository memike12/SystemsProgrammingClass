#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <pthread.h>

#define SPIN 10000000

long counter;          //shared reource
pthread_mutex_t lock;  //resouce lock

time_t end_time; //how long should the program run

void *c_thread(void *args){
  int i;

  while(time(NULL) < end_time){
    

    pthread_mutex_lock(&lock);

    /*Critical Section*/

    for(i=0;i<SPIN;i++){
      counter++;
    }

    pthread_mutex_unlock(&lock);

  }

  printf("C_THREAD: Counter is %#lx\n", counter);
  return NULL;
}


void *m_thread(void *args){
  int misses = 0;

  while(time(NULL) < end_time){

    //sleep 250 miliseconds or .25 seconds
    usleep(250); 

    //try and grab lock
    if( pthread_mutex_trylock(&lock) == 0){
      //grabbed lock!
      
      printf("M_THREAD: Counter is %#lx\n", counter);

      pthread_mutex_unlock(&lock);

    }else{
      //missed lock
      misses++;
    }
      
  }

  printf("M_THREAD: Missed %d times\n", misses);

  return NULL;
}


int main(int argc, char * argv[]){

  pthread_t m_thread_id,c_thread_id;

  //run for 15 seconds
  end_time = time(NULL)+15;

  //initialize lock
  pthread_mutex_init(&lock, NULL);

  //spawn threads
  pthread_create(&c_thread_id, NULL, c_thread, NULL);
  pthread_create(&m_thread_id, NULL, m_thread, NULL);

  //join threads
  pthread_join(c_thread_id, NULL);
  pthread_join(m_thread_id, NULL);

  return 0;

}
