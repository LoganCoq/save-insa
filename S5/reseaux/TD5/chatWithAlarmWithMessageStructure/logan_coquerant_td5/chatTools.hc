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

void setupRace() {
	sigemptyset(&sigset_alarm);
	sigaddset(&sigset_alarm,SIGALRM);
	if (sigprocmask(SIG_BLOCK, &sigset_alarm, NULL) SYSCALL_ERR) {
		perror( "main : sigprocmask" );
		exit( __LINE__ );
	}
	INIT_RACE();
}

bool status(int waitingDesc, int state) {
	if (usersState[waitingDesc].state==state) {
		return TRUE;
	}
	return FALSE;
}

void initGlobalStateAutomata() {
	bzero(globalConditions, sizeof(globalConditions));
	bzero(globalStateAutomata, sizeof(globalStateAutomata));
	globalState=INITIAL_STATE;
}

void initUsersStateAutomata() {
	bzero(usersStateConditions, sizeof(globalConditions));
	bzero(usersStateAutomata, sizeof(globalStateAutomata));
	int user;
	for (user=0; user<MAX_USERS; user++) usersState[user].state=INITIAL_STATE;
}

void initAutomatas() {
	initGlobalStateAutomata();
	initUsersStateAutomata();
}

bool fGC_0(char *argv[]) {
	if(WAITING(askCx)) {
		return TRUE;
	}
	return FALSE;
}

bool fGC_1(char *argv[]) {
	return !fGC_0(argv);
}

void fGA_0(char *argv[]) {
	racingAccept(argv);
	setNewParticipant(argv);
	globalState=AT_LEAST_ONE_CLIENT; // At least one connexion to process.
}

void fGA_1(char *argv[]) {
	racingRead(argv);
	processRequest(argv);
	{
	  globalState = globalState; // Stay in the same state
	}
}

void fGA_NULL(char *argv[]) {
	// Vide
}

void computeDeparture() {
	tabNoDesc[waitingDesc]=ZERO;
  usersState[waitingDesc].state=ZERO;
  bzero(&(usersState[waitingDesc].nickname),NICKNAME_SIZE);
	nbUsers--;

	if (waitingDesc==nbDesc)
		nbDesc--;
}

int processRequest(char *argv[])
{
	int i;

	if(assertRead(argv) == DECONNECTED) {
		computeDeparture();
		return(DEPARTURE);
  }

	// We get a request
	if (status(waitingDesc,WAITING_NICKNAME)) {
		computeMessageNewArrival();
	} else {
		computeMessageData();
	}

	BEGIN_ITERATOR_DESC(i)
		sendEveryoneExceptMyself(i);
	END_ITERATOR_DESC

	return(OK);
}

void	defineGlobalStateAutomata() {
	globalConditions[COND_ESTABLISHMENT_REQUESTED]=fGC_0;
	globalConditions[COND_DATA_ARRIVAL]=fGC_1;

	globalStateAutomata[INITIAL_STATE][COND_ESTABLISHMENT_REQUESTED]=fGA_0;
	globalStateAutomata[INITIAL_STATE][COND_DATA_ARRIVAL]=fGA_1;

	globalStateAutomata[AT_LEAST_ONE_CLIENT][COND_ESTABLISHMENT_REQUESTED]=fGA_0;
	globalStateAutomata[AT_LEAST_ONE_CLIENT][COND_DATA_ARRIVAL]=fGA_1;
}

void	defineUsersStateAutomata() {
	// Oui la fonction ne fait rien
}

void defineAutomatas() {
	defineGlobalStateAutomata();
	defineUsersStateAutomata();
}

void computeGlobalAutomata(char *argv[]) {
	printf("computeGlobalAutomata : globalState=%d\n",globalState);
	int cond;
	for(cond=0; cond<STATE_SIZE; cond++) {
		if (globalConditions[cond]==NULL)
			break;

		printf("computeGlobalAutomata : for cond=%d\n",cond);
		if (globalConditions[cond](argv)) {
			printf("computeGlobalAutomata : cond=%d satisfied, fire the function globalStateAutomata[globalState(%d)][cond(%d)]\n",
			       cond, globalState, cond);
			globalStateAutomata[globalState][cond](argv);
		}
	}
}

void initTabNoDesc() {
	bzero(tabNoDesc, sizeof(tabNoDesc));
	tabNoDesc[FIRST_DESC]=askCx;
}

void initusersState() {
	bzero(usersState, sizeof(usersState));
}

void initRacingIteratorOfDesc() {
	waitingDesc=FIRST_DESC;
	nbDesc++;
}

void initMessage() {
	messageType=ZERO;
}

void initChat() {
	initTabNoDesc();
	initusersState();
	initRacingIteratorOfDesc();
	initAutomatas();
	initMessage();

	defineAutomatas();

	setupRace();
}

void racingIteratorOfDesc() {
	printf("Before NOT_REACHED_THE_END_OF_DESC: waitingDesc=%d, nbDesc=%d, askCx=%d, cxEstablished=%d, read_ret=%d, raceAccept=%d, raceRead=%d, stopDescRun=%d\n",
	       waitingDesc, nbDesc, askCx, cxEstablished, read_ret, raceAccept, raceRead, stopDescRun);

	if (NOT_REACHED_THE_END_OF_DESC(waitingDesc,nbDesc)) {
		if (STOP_RUN()) {
			waitingDesc++;
		} else {
			CONTINUE_RUN();
		}
	} else {
		waitingDesc=FIRST_DESC;
	}

	printf("After NOT_REACHED_THE_END_OF_DESC: waitingDesc=%d, nbDesc=%d, askCx=%d, cxEstablished=%d, read_ret=%d, raceAccept=%d, raceRead=%d\n",
	       waitingDesc, nbDesc, askCx, cxEstablished, read_ret, raceAccept, raceRead);
	fflush(stdout);
}

void setRacingAccept() {
	printf("waitingDesc(%d): tabNoDesc[waitingDesc](%d)=askCx(%d)\n",
	       waitingDesc,tabNoDesc[waitingDesc], askCx);
	printf("Try accept, before INIT_RACING_TIMER : raceAccept(%d), askCx(%d)\n",raceAccept,askCx);
	fflush(stdout);
	fsync(SYNC_OUT);
	INIT_RACING_TIMER(timer, raceAccept, cxEstablished, handle_alarm, act, oact);
}

void setRacingRead() {
	printf("waitingDesc(%d): tabNoDesc[waitingDesc](%d)=askCx(%d)\n",
	waitingDesc,tabNoDesc[waitingDesc], askCx);
	printf("Try read, before INIT_RACING_TIMER : raceRead(%d), read_ret(%d)\n",raceRead,read_ret);
	fflush(stdout);
	fsync(SYNC_OUT);
	INIT_RACING_TIMER(timer, raceRead, read_ret, handle_alarm, act, oact);
}

void setNewParticipant(char *argv[]) {
	int i;
  int newParticipant = nbDesc; // By default the new participant is nbDesc
	printf("setNewParticipant : nbDesc(%d), cxEstablished(%d)\n", nbDesc, cxEstablished);

	tabNoDesc[newParticipant] = cxEstablished; // The new participant is newParticipant and his descriptor number is cxEstablished

	char s1[BUFSIZ];
	sprintf(s1, MESS_WELCOME(newParticipant)); // Compute the beginning of welcome message for the new participant newParticipant
	int nw1=write(tabNoDesc[newParticipant],s1,strlen(s1)); // Send the beginning of welcome message to the new participant

	char s2[BUFSIZ];
	sprintf(s2, MESS_NICKNAME_INVITATION(newParticipant)); // Compute the end of welcome message for the new participant
	int nw2=write(tabNoDesc[newParticipant],s2,strlen(s2)); // Send the beginning of welcome message to the new participant

	usersState[newParticipant].state=WAITING_NICKNAME;
	if (newParticipant==nbDesc) { // We did not find any empty spot in the array
	    nbDesc++;
	    printf("Increase nbDesc : nbDesc(%d), cxEstablished(%d)\n",nbDesc,cxEstablished);
	}
	nbUsers++;
}

void computeMessageNewArrival() {
  messageType=NEW_ARRIVAL;
	printf("computeMessageNewArrival\n"); fflush(stdout);
	// Compute the message NewArrival in message.nickname
	strncpy(usersState[waitingDesc].nickname,message.nickname.nickname,read_ret); // Store in usersState the nickname from the incoming message
	usersState[waitingDesc].nickname[read_ret-SIZE_NEW_LINE_RECEIVED_WITHOUT_NULL_CHAR(NEW_LINE_RECEIVED)]=END_OF_LINE; // Remove \r\n
	bzero(&message,sizeof(message));
	strncat(message.nickname.nickname,usersState[waitingDesc].nickname,strlen(usersState[waitingDesc].nickname));
	message.head.lg=sizeof(messNickname)-sizeof(header); // Ne sert à rien à se stade...
	printf("MessageNewArrival=%s\n",message.nickname.nickname);
}

void computeMessageData() {
  messageType=DATA;
	printf("computeMessageData\n"); fflush(stdout);
	// Compute the message NewArrival in message.data

	messData d; // For temporary storage of the received message

	bzero(d.data,sizeof(d.data));
	// Store the nickname from usersState and the data from the received message message.big into the temporary message d
	sprintf(d.nickname, "%d,%s", waitingDesc , usersState[waitingDesc].nickname);
	strncat(d.data,message.big.big,strlen(message.big.big));
	//printf("d.data(1)=%s\n",d.data);
	d.data[strlen(d.data)-SIZE_NEW_LINE_RECEIVED_WITHOUT_NULL_CHAR(NEW_LINE_RECEIVED)]=END_OF_LINE; // supprime \r\n
	//printf("d.data(2)=%s\n",d.data);

	bzero(&message,sizeof(message));
	strncat(message.data.nickname,d.nickname,strlen(d.nickname));
	strncat(message.data.data,d.data,strlen(d.data));
	message.head.lg = sizeof(messData)-sizeof(header); // Useless at this stage...
	printf("Data=%s>%s\n",message.data.nickname,message.data.data);
}

void sendMessageNewArrival(int i) {
	char s1[BUFSIZ] = {">"};
	printf("for1 1%s\n",s1); fflush(stdout);
	int nw1 = write(tabNoDesc[i],s1,strlen(s1));

	printf("for1 2%s\n",message.nickname.nickname); fflush(stdout);
	int nw2 = write(tabNoDesc[i],message.nickname.nickname,strlen(message.nickname.nickname));

	char s3[BUFSIZ] = {" arrived\n"};
	printf("for1 3%s\n",s3); fflush(stdout);
	int nw3 = write(tabNoDesc[i],s3,strlen(s3));

	usersState[waitingDesc].state=SESSION_ESTABLISHED;
	printf("for1 end waitingDesc(%d),usersState[waitingDesc].state(%d);\n",
	       waitingDesc,usersState[waitingDesc].state); fflush(stdout);
}

void sendMessageData(int i) {
	printf("For2 1\n"); fflush(stdout);
	int nw1=write(tabNoDesc[i],message.data.nickname,strlen(message.data.nickname));

	printf("For2 2\n"); fflush(stdout);
	char s2[BUFSIZ]={">"};
	int nw2=write(tabNoDesc[i],s2,strlen(s2));

	printf("For2 3\n"); fflush(stdout);
	int nw3=write(tabNoDesc[i],message.data.data,strlen(message.data.data));

	printf("For2 4\n"); fflush(stdout);
	char s4[BUFSIZ]={"\n"};
	int nw4=write(tabNoDesc[i],s4,strlen(s4));

	printf("For2 5\n"); fflush(stdout);
}

void sendEveryoneExceptMyself(int i) {
	if (tabNoDesc[waitingDesc] == ZERO) // Do not send to an invalid descriptor
	  return;

	if (i != waitingDesc) { // Do not send to me
		if (messageType == NEW_ARRIVAL){
			sendMessageNewArrival(i);
			printf("sendEveryoneExceptMyself : send new arrival since waiting nickname\n");
			fflush(stdout);
		} else {
			sendMessageData(i);
			printf("sendEveryoneExceptMyself : send message data since no waiting nickname\n");
			fflush(stdout);
		}
	} else {
		if (usersState[waitingDesc].state==WAITING_NICKNAME) {
	    usersState[waitingDesc].state=SESSION_ESTABLISHED;
		  printf("Set the waitingDesc state : waitingDesc(%d),usersState[waitingDesc].state(%d);\n",
		         waitingDesc,usersState[waitingDesc].state);
			fflush(stdout);
		}	else {
			printf("sendEveryoneExceptMyself : nothing to do since no waiting nickname\n"); fflush(stdout);
		}
	}
}

void racingAccept(char *argv[]) {
	setRacingAccept();

	if (NOT_YET(raceAccept)) {
		tryAccept(argv);
	}
}

void racingRead(char *argv[]) {
	setRacingRead();

	if (NOT_YET(raceRead)) {
		tryRead(argv);
	}
}
