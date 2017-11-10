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

sigjmp_buf Env;

struct sigaction act, oact;
struct itimerval timer;
sigset_t mask;
sigset_t sigset_alarm;

void handle_alarm(int sig) {
	longjmp(Env, RETURN_LONG_JUMP_ALARM);
}
