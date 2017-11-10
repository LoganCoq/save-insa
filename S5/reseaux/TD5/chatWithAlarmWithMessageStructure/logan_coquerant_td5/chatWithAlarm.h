/*
 A all in one chat server with a single activity (the process main thread), without active waiting or select usage,
 for helping to understand what is a network TIMEOUT, the related race conditions and
 how to standardize messages and protocol data unit structures.
 In short : all you wanted to know about network and system programming without knowing that you ignore important issues.
 (C) 2015 C. Toinard, All Rights Reserved, copying and distribution permitted with copyright intact.
 For support, send cash and check at Christian Toinard - INSA CVL 88 boulevard Lahitolle -  CS 60013 - 18022 BOURGES cedex (France).
 christian.toinard@insa-cvl.fr
 Any negative remark completly is forbidden and will be prosecuted by any possible persecution under the ability of the owner.
 */

#ifndef __CORRIGE_CHAT_AVEC_ALARM__
#define __CORRIGE_CHAT_AVEC_ALARM__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

/* Macros and define */
#define	ZERO                                          0
#define	SAVE_SIGMASK                                  1

#define FALSE                                         0
#define TRUE                                          1

#define KO                                            0
#define OK                                            1
#define DECONNECTED                                   2
#define DEPARTURE                                     3

#define NEW_ARRIVAL                                   1
#define DATA                                          2

#define SYNC_OUT                                      1

#define SET_MICROSECONDS                              1
#define TIMEOUT                                       50000 // microsecondes
#define STOP_TIMEOUT                                  0

#define END_OF_LINE                                   '\0'
#define NEW_LINE_RECEIVED                             "\r\n"
#define SIZE_NEW_LINE_RECEIVED_WITHOUT_NULL_CHAR(nlr)                          \
	(sizeof(nlr)-sizeof((char)END_OF_LINE))

#define RETURN_LONG_JUMP_ALARM                     1

#define MAX_USERS											             32
#define STATE_SIZE                                 32
#define CONDITION_SIZE                             32

#define FIRST_DESC											           0
#define FIRST_CONN                                 FIRST_DESC+1
#define END_OF_DESC(sizeOfDescList)                sizeOfDescList-1
#define NOT_REACHED_THE_END_OF_DESC(desc,size)     desc < END_OF_DESC(size)

#define PROGRAM_NAME(env)                          env[0]
#define	SERVER_PORT                                argv[1]
#define	ARGUMENT_IS_MISSING(envSize)               envSize==1

#define BEGIN_FOR_EVER                             while(TRUE) { printf("ForEver\n");
#define END_FOR_EVER                               };
#define LET_THE_OS_CHOSE_THE_RIGHT_PROTOCOL         0
#define SYSCALL_ERR_VALUE                          -1
#define	SYSCALL_NEVER_RETURN_THIS                  (SYSCALL_ERR_VALUE-1)
#define SYSCALL_ERR                                < (SYSCALL_ERR_VALUE+1)
#define SOCKET_ERR                                 SYSCALL_ERR
#define BIND_ERR                                   SYSCALL_ERR
#define GETSOCKNAME_ERR                            SYSCALL_ERR
#define	CONNECTION_QUEUE_SIZE                      1
#define READ_ERR(ret)                              ret<=0

#define INIT_RACING_TIMER(timer,raceBool,retSys,handler,act,oact)              \
	timerclear(&(timer.it_interval));                                            \
	timer.it_value.tv_sec = 0;                                                   \
	timer.it_value.tv_usec = TIMEOUT;                                            \
	if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {                            \
		/*perror("error calling setitimer()");*/ exit(__LINE__); }                 \
		retSys=SYSCALL_NEVER_RETURN_THIS;                                          \
		raceBool=TRUE;                                                             \
		act.sa_handler=handler;                                                    \
		sigemptyset(&act.sa_mask);                                                 \
		act.sa_flags = ZERO;                                                       \
		if (sigaction(SIGALRM, &act, &oact) SYSCALL_ERR) {                         \
			/*perror("error calling sigaction()");*/ exit(__LINE__);                 \
		}                                                                          \
		if (sigprocmask(SIG_UNBLOCK, &sigset_alarm, NULL) == -1) {                 \
			perror( "INIT_RACING_TIMER : sigprocmask" ); exit( __LINE__ );           \
	}

#define STOP_RACE(raceBool,retSyscall)                                         \
	raceBool=FALSE;                                                              \
	stopDescRun=TRUE;                                                            \
	if (sigprocmask(SIG_BLOCK, &sigset_alarm, NULL) == -1) {                     \
		perror( "STOP_RACE : sigprocmask" );                                       \
		exit( __LINE__ );                                                          \
	}

#define	IN_RACE(raceBool,retSyscall)                                           \
	(raceBool&&(retSyscall!=SYSCALL_NEVER_RETURN_THIS))

#define INIT_RACE()                                                            \
	raceAccept=TRUE;                                                             \
	raceRead=TRUE;                                                               \
	cxEstablished=SYSCALL_NEVER_RETURN_THIS;                                     \
	read_ret=SYSCALL_NEVER_RETURN_THIS

#define	NOT_YET(raceBool)			raceBool==TRUE

#define STOP_RUN()             stopDescRun==TRUE
#define CONTINUE_RUN()         stopDescRun=FALSE


#define BEGIN_ITERATOR_DESC(i)                                                 \
	printf("BEGIN_ITERATOR_DESC before for \n"); fflush(stdout);                 \
	for(i=FIRST_CONN; i<nbDesc; i++) {                                           \
	printf("for i=%d,tabNoDesc[i]=%d\n",i,tabNoDesc[i]);

#define END_ITERATOR_DESC				            };


#define WAITING(askCx)                      tabNoDesc[waitingDesc]==askCx

#define	INVITATION                          :

#define XSTR(s)                             STR(s)
#define STR(s)                              #s

#define	COND_ESTABLISHMENT_REQUESTED        0
#define	COND_DATA_ARRIVAL                   1

#define INITIAL_STATE                       0 // Starting state for the server, no clients connected
#define AT_LEAST_ONE_CLIENT                 1 // There is a number of clients connected to the server
#define TOO_MANY_CLIENTS                    2 // Server stops accepting new clients when in this state

#define WAITING_NICKNAME                    1 // Server is waiting for the client to send its nickname
#define SESSION_ESTABLISHED                 2 // nickname has been sent by the client, he can now join the chat

#define MESS_WELCOME(descIndice)            "\n Welcome %d\n", descIndice
#define MESS_NICKNAME_INVITATION(descIndice)  "\n Enter your nickname[%d] " XSTR(INVITATION) "\n", descIndice

#define NICKNAME_SIZE                       1024

/* Strctures */
typedef struct{
	char nickname[NICKNAME_SIZE];
	int state;
} stateType;

typedef struct{
	char type;
	int lg;
} header;

typedef struct{
	header head;
	char nickname[BUFSIZ];
} messNickname;

typedef struct{
	header head;
	char nickname[BUFSIZ];
	char data[BUFSIZ];
} messData;

typedef struct{
	header head;
	char big[BUFSIZ*BUFSIZ];
} messBig;

union messType {
	messNickname nickname;
	messData data;
	messBig big;
	header head;
};

typedef bool (*funcCondPtr)(char *argv[]);
typedef void (*funcAutoPtr)(char *argv[]);

extern void setupRace();

extern bool status(int waitingDesc, int state);

extern void initGlobalStateAutomata();

extern void initUsersStateAutomata();

extern void initAutomatas();

extern void initMessage();

extern void	defineGlobalStateAutomata();

extern void	defineUsersStateAutomata();

extern void defineAutomatas();

extern void computeGlobalAutomata(char *argv[]);

extern void initTabNoDesc();

extern void initusersState();

extern void initRacingIteratorOfDesc();

extern void initChat();

extern void racingIteratorOfDesc();

extern void setRacingAccept();

extern void setRacingRead();

extern void setNewParticipant(char *argv[]);

extern void computeMessageNewArrival();

extern void computeDeparture();

extern void computeMessageData();

extern void sendMessageNewArrival();

extern void sendMessageData();

extern void sendEveryoneExceptMyself(int i);

extern int processRequest(char *argv[]);

extern void racingAccept(char *argv[]);

extern void racingRead(char *argv[]);

extern int askCx;
extern struct sockaddr_in internetExtremity;	// struct sockaddr_in <=> internet extremity
extern socklen_t length;

extern int cxEstablished;
extern int read_ret;

extern bool raceAccept; // Not necessary with safe code
extern bool raceRead; // Not necessary with safe code

extern bool stopDescRun;

extern int messageType;

extern int tabNoDesc[MAX_USERS];

extern int nbDesc;
extern int nbUsers;
extern int waitingDesc;
extern char buf[BUFSIZ];
extern int sj;
extern union messType message;

extern funcCondPtr globalConditions[CONDITION_SIZE];
extern funcAutoPtr globalStateAutomata[STATE_SIZE][CONDITION_SIZE];
extern int globalState;

extern funcCondPtr usersStateConditions[CONDITION_SIZE];
extern funcAutoPtr usersStateAutomata[STATE_SIZE][CONDITION_SIZE][MAX_USERS];
extern stateType usersState[MAX_USERS];

#endif
