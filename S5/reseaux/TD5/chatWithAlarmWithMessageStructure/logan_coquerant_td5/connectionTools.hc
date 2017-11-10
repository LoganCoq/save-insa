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

void SocketTCP(int *sD,char *env[]) {
  if ((*sD = socket( AF_INET, SOCK_STREAM, LET_THE_OS_CHOSE_THE_RIGHT_PROTOCOL )) SOCKET_ERR) {
  	char s[BUFSIZ];
  	sprintf(s, "%s: can't assign fd for socket", PROGRAM_NAME(env));
  	perror(s);
  	exit(__LINE__);
  }
}

void tryAccept(char *argv[]) {
	cxEstablished = accept(tabNoDesc[waitingDesc],(struct sockaddr *) &internetExtremity,(socklen_t *) &length);
	STOP_RACE(raceAccept,cxEstablished);
	printf("STOP_RACE : raceAccept(%d), askCx(%d), cxEstablished(%d)\n",raceAccept, askCx, cxEstablished);
	if (cxEstablished SYSCALL_ERR) {
		char s[BUFSIZ];
		sprintf( s, "%s: accept error %d, errno=%d", PROGRAM_NAME(argv), cxEstablished, errno);
		perror(s);
		exit(__LINE__);
	}
	printf("After accept: waitingDesc=%d,tabNoDesc[waitingDesc]=%d,cxEstablished=%d\n",waitingDesc,tabNoDesc[waitingDesc],cxEstablished);
	fflush(stdout);
}

void tryRead(char *argv[]) {
	bzero(message.big.big,sizeof(message.big.big));

	read_ret=read(tabNoDesc[waitingDesc],message.big.big,sizeof(message.big.big)); // Attente d'une requête
	STOP_RACE(raceRead,read_ret);
	printf("STOP_RACE(raceRead,%d)\n",read_ret);

	printf("After read: waitingDesc=%d,tabNoDesc[waitingDesc]=%d, read_ret=%d\n",waitingDesc,tabNoDesc[waitingDesc], read_ret);

	fflush(stdout);
	fsync(SYNC_OUT);
}

int assertRead(char *argv[]) {
	if (READ_ERR(read_ret)) {
	  char s[BUFSIZ];
	  printf("Erreur read_ret:%d\n",read_ret);
	  perror(s);
	  sprintf( s, "%s: can't read tabNoDesc[waitingDesc](%d) in tabNoDesc[%d]", PROGRAM_NAME(argv), tabNoDesc[waitingDesc], waitingDesc);
    if (read_ret == 0) {
	    return(DECONNECTED);
    } else {
	    return(KO);
	  }
	} else {
	  printf("Message:%s\n",message.big.big);
	  message.head.lg=read_ret;
	  printf("Pas d'erreur read_ret:%d\n",read_ret); fflush(stdout);
	}
	return(OK);
}

void BindListenTCP(int askCx,char *argv[]) {
  internetExtremity.sin_family = AF_INET;
  internetExtremity.sin_addr.s_addr = INADDR_ANY;
  internetExtremity.sin_port = htons(atoi(SERVER_PORT));

  if (bind(askCx, (struct sockaddr *) &internetExtremity, sizeof internetExtremity) BIND_ERR) {
  	char s[BUFSIZ];
  	sprintf( s, "%s: can't bind socket (%d)", PROGRAM_NAME(argv), askCx );
  	perror(s);
  	exit(__LINE__);
  }

  printf("opened socket as fd (%d) on port (%d) for stream i/o\n",
	askCx, ntohs(internetExtremity.sin_port));

  if (getsockname(askCx, (struct sockaddr *) &internetExtremity, &length) GETSOCKNAME_ERR) {
  	char s[BUFSIZ];
  	sprintf(s, "%s: can't bind socket (%d)", PROGRAM_NAME(argv), askCx);
  	perror(s);
  	exit(__LINE__);
  }

	printf("struct sockaddr_in {\n\tsin_family		= %d\n\tsin_addr.s_addr	= %s\n\tsin_port		= %d\n} sockaddr;\n",
        internetExtremity.sin_family, inet_ntoa(internetExtremity.sin_addr), ntohs(internetExtremity.sin_port));

	listen(askCx,CONNECTION_QUEUE_SIZE);
}
