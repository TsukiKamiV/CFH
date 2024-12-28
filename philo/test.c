#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
/*void* myThreadFun(void* vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// write the new balance (after as simulated 1/4 second delay)
void write_balance(int *balance, int new_balance)
{
  usleep(250000);
  //printf("New balance: %d\n", new_balance);
  *balance = new_balance;
}

// returns the balance (after a simulated 1/4 seond delay)
int read_balance(int *balance)
{
  usleep(250000);
  return *balance;
}

// carry out a deposit
void* deposit(void *arg)
{
	int	*balance = ((int **)arg)[0];
	int	*amount = ((int **)arg)[1];
	pthread_mutex_t	*balance_mutex = ((pthread_mutex_t **)arg)[2];
	pthread_mutex_lock(balance_mutex);
  // retrieve the bank balance
  	int account_balance = read_balance(balance);
  	//printf("Account balance is: %d\n", account_balance);
  // make the update locally
  	account_balance += *amount;
  // write the new bank balance
  	write_balance(balance, account_balance);
  	return NULL;
}

int main()
{
	int	balance = 0;
	pthread_mutex_t	balance_mutex;//互斥锁声明
	pthread_mutex_init(&balance_mutex, NULL);//互斥锁初始化，第二个参数是以默认方式attribute
  
	// output the balance before the deposits
  	int before = read_balance(&balance);
  	printf("Before: %d\n", before);

  // we'll create two threads to conduct a deposit using the deposit function
  	pthread_t thread1;
  	pthread_t thread2;

  // the deposit amounts... the correct total afterwards should be 500
  	int deposit1 = 300;
  	int deposit2 = 200;

	void	*thread_args[] = {&balance, &deposit1, &balance_mutex};
	void	*thread_args[] = {&balance, &deposit2, &balance_mutex}; 
  // create threads to run the deposit function with these deposit amounts
  	pthread_create(&thread1, NULL, deposit, (void*) thread1_args);
  	pthread_create(&thread2, NULL, deposit, (void*) thread2_args);

  // join the threads
  	pthread_join(thread1, NULL);
  	pthread_join(thread2, NULL);

  // output the balance after the deposits
  	int after = read_balance();
  	printf("After: %d\n", after);

  	return 0;
}

