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


void checkArguments(char *env[],int envSize) {
	if (ARGUMENT_IS_MISSING(envSize)) {
		char s[BUFSIZ];
		sprintf( s, "%s: Argument is missing, might be port number", PROGRAM_NAME(env) );
		perror(s);
		exit(__LINE__);
	}
}
