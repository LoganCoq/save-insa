#ifndef COPIE_H
#define COPIE_H

#define FICHIER_CLEF "copie.h" //fichier pour générer la clé avec num inode

#define PROJ_FTOK 'a' //permet de générer plusieurs clés (256)

#define TYPE_FIC1 1
#define TYPE_FIC2 2
#define TYPE_END1 3 //le client a t il fini?
#define TYPE_END2 4

#define SIZE_BUF 256

typedef struct data_s data_t;
struct data_s {
	long type;
	int taille;
	char buf[SIZE_BUF];
};
#endif
