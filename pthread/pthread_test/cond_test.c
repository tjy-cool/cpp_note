
/***************************************************************
*  Copyright (C) 2016 chengonghao
*  All rights reserved.
*  原文：https://blog.csdn.net/chengonghao/article/details/51779279 
*  chengonghao@yeah.net
***************************************************************/
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define CONSUMERS_COUNT 1  	
#define PRODUCERS_COUNT 1
 
pthread_mutex_t g_mutex ;
pthread_cond_t g_cond ;
 
pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT] ;
int share_variable = 0 ;// this is the share variable, shared by consumer and producer
 
void* consumer( void* arg )
{
   int num = (int)arg ;
   while ( 1 ) 
   {
      /******* critical section begin *******/
      pthread_mutex_lock( &g_mutex ) ;
 
      // if share_variable == 0, means consumer shell stop here
      while ( share_variable == 0 )
      {
         printf("consumer %d begin wait a condition, share_variable: %d...\n", num, share_variable);
         // put a thread blocked ont a condition variable( here is g_cond),
         // and unlock the mutex( here is g_mutex )
         pthread_cond_wait( &g_cond, &g_mutex ) ;
      }
      // here means n != 0 and consumer can goes on
      // consumer consumed shared variable, so the number of shared variable shell minus
      printf( "consumer %d end wait a condition, share_variable: %d...\n", num, share_variable) ;
      printf( "consumer %d begin consume product, share_variable: %d\n", num, share_variable ) ;
      -- share_variable ;
 
      pthread_mutex_unlock( &g_mutex ) ;
      /******** critial section end *********/
      sleep( 1 ) ;
   }
   
   return NULL ;
}
 
void* producer( void* arg )
{
   int num = (int)arg ;
   while ( 1 )
   {
      /******* critical section begin *******/
      pthread_mutex_lock( &g_mutex ) ;
 
      // produce a shared variable
      printf( "producer %d begin produce product, share_variable: %d...\n", num, share_variable ) ;
      ++ share_variable ;
      printf( "producer %d end produce product, share_variable: %d...\n", num, share_variable ) ;
      // unblock threads blocked on a condition variable( here is g_cond )
      pthread_cond_signal( &g_cond ) ;
      printf( "producer %d notified consumer by condition variable, share_variable: %d...\n", num, share_variable ) ;
      ++ share_variable;
      printf( "producer %d before unlock, share_variable: %d...\n", num, share_variable ) ;
      pthread_mutex_unlock( &g_mutex ) ;
 
      /******** critial section end *********/
      sleep( 5 ) ;
   }
   
   return (void*)1 ;
}
 
 
int main( void )
{
   // initiate mutex
   pthread_mutex_init( &g_mutex, NULL ) ;
   // initiate condition
   pthread_cond_init( &g_cond, NULL ) ;
 
   // initiate consumer threads
   for ( int i = 0; i < CONSUMERS_COUNT; ++ i )
   {
      pthread_create( &g_thread[i], NULL, consumer, (void*)(long)i ) ;
   }
   sleep( 1 ) ;
   // initiate producer threads
   for ( int i = 0; i < PRODUCERS_COUNT; ++ i )
   {
      pthread_create( &g_thread[i], NULL, producer, (void*)(long)i ) ;
   }
   for ( int i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; ++ i ) 
   {
      pthread_join( g_thread[i], NULL ) ;
   }
 
   pthread_mutex_destroy( &g_mutex ) ;
   pthread_cond_destroy( &g_cond ) ;
}