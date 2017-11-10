/*
 A all in one chat server with a single activity (the process main thread), without active waiting or select usage,
 for helping to understand what is a network TIMEOUT, the related race conditions and
 how to standardize messages, protocol data unit structures and how to compute a protocol automata.
 In short : all you wanted to know about network and system programming without knowing that you ignore important issues.
 (C) 2015 C. Toinard, All Rights Reserved, copying and distribution permitted with copyright intact.
 For support, send cash, check or even encouragement to a poor french Professor in Computer Sciences at :
 Christian Toinard  - INSA CVL 88 boulevard Lahitolle -  CS 60013 - 18022 BOURGES cedex (France).
 christian.toinard@insa-cvl.fr
 Any negative remark completly is forbidden and will be prosecuted by any possible persecution under the ability of the owner.
*/

#include "chatWithAlarm.h"
#include "alarm.hc"
#include "arguments.hc"
#include "connectionTools.hc"
#include "chatTools.hc"

int askCx;
struct sockaddr_in internetExtremity;	// struct sockaddr_in <=> internet extremity
socklen_t length = sizeof(struct sockaddr_in);

int cxEstablished = SYSCALL_NEVER_RETURN_THIS;
int read_ret = SYSCALL_NEVER_RETURN_THIS;

bool raceAccept = FALSE; // Not necessary with safe code
bool raceRead = FALSE; // Not necessary with safe code

bool stopDescRun = FALSE;

int tabNoDesc[MAX_USERS];

int nbDesc = ZERO;
int nbUsers = ZERO;
int waitingDesc;
char buf[BUFSIZ];
int sj;
int messageType;
union messType message;

funcCondPtr globalConditions[CONDITION_SIZE];
funcAutoPtr globalStateAutomata[STATE_SIZE][CONDITION_SIZE];
int globalState;

funcCondPtr usersStateConditions[CONDITION_SIZE];
funcAutoPtr usersStateAutomata[STATE_SIZE][CONDITION_SIZE][MAX_USERS];
stateType usersState[MAX_USERS];


int main(int argc, char *argv[]) {
	checkArguments(argv,argc);

	SocketTCP(&askCx,argv);
	BindListenTCP(askCx,argv);

  initChat();

	BEGIN_FOR_EVER
		setjmp(Env);

		racingIteratorOfDesc();

		computeGlobalAutomata(argv);
	END_FOR_EVER

	return 0;
}
