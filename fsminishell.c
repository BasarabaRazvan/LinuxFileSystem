#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
//creare radacina sistemului de fisiere
void createfs(Directory **rad)
{
	(*rad) = malloc(sizeof(Directory));
	(*rad)->name = strdup("/");
	(*rad)->directoare = NULL;
	(*rad)->fisiere = NULL;
	(*rad)->parentDir = NULL;
}
//stergere director radacina
void deletefs(Directory **rad)
{
	free((*rad)->name);
	free((*rad));
}
//functie de separare a unui sir in cuvinte si retinerea
//lor intr-o matrice de cuvinte
char **separare(char *s, int n)
{
	char **matrice;
	char *token = strtok(s, " ");
	int i = 0;

	matrice = (char **)malloc(n * sizeof(char *));
	while (token != NULL) {
		matrice[i] = strdup(token);
		i++;
		token = strtok(NULL, " ");
	}
	return matrice;
}
//functie de alocare memorie pentru un fisier si initializarea
//campurilor din structura File
File *touch(Directory *cap, char *nume, char *continut)
{
	File *f;

	f = malloc(sizeof(File));
	f->name = strdup(nume);
	f->data = strdup(continut);
	f->size = strlen(continut);
	f->dir = cap;
	return f;
}
//functie care intoduce un element de tip File intr-o
//lista simplu inlantuita de fisiere
TList_file *alocarefile(Directory *cap, char *nume, char *continut)
{
	File *x;

	x = touch(cap, nume, continut);
	TList_file *aux;

	aux = malloc(sizeof(TList_file));
	if (aux) {
		aux->file = x;
		aux->next = NULL;
	}
	return aux;
}
//functie de alocare memorie pentru un director si initializarea
//campurilor din structura Directory
Directory *alocaredirect(char *s, Directory *parent)
{
	Directory *a;

	a = malloc(sizeof(Directory));
	a->name = strdup(s);
	a->directoare = NULL;
	a->parentDir = parent;
	return a;
}
//functie care intoduce un element de tip Directory intr-o
//lista simplu inlantuita de directoare
Tlist_direct *mkdir(char *s, Directory *parent)
{
	Directory *x;

	x = alocaredirect(s, parent);
	Tlist_direct *aux;

	aux = malloc(sizeof(Tlist_direct));
	if (aux) {
		aux->directory = x;
		aux->next = NULL;
	}
	return aux;
}
//functie care intoarce 1 daca un director din lista de
//directoare se numeste s
int validare(char *s, Tlist_direct *cap)
{
	if (cap == NULL)
		return 0;
	while (cap != NULL) {
		if (strcmp(s, cap->directory->name) == 0)
			return 1;
		cap = cap->next;
	}
	return 0;
}
//functie care intoarce 1 daca un fisier din lista de
//fisiere se numeste s
int valfisiere(char *s, TList_file *cap)
{
	if (cap == NULL)
		return 0;
	while (cap != NULL) {
		if (strcmp(s, cap->file->name) == 0)
			return 1;
		cap = cap->next;
	}
	return 0;
}
//functie care intoarce directorul care se numeste s
Tlist_direct *gasire(char *s, Tlist_direct *cap)
{
	while (cap != NULL) {
		if (strcmp(s, cap->directory->name) == 0)
			return cap;
		cap = cap->next;
	}
	return 0;
}
//functie care intoarce pozitia la care se afla
//directorul cu numele s in lista de directoare
int gasiredirector(char *s, Tlist_direct *cap)
{
	int n = 0;

	while (cap != NULL) {
		if (strcmp(s, cap->directory->name) == 0)
			return n;
		cap = cap->next;
		n++;
	}
	return 0;
}
//functie care intoarce pozitia la care se afla
//fisierul cu numele s in lista de fisiere
int gasirefisiere(char *s, TList_file *cap)
{
	int n = 0;

	while (cap != NULL) {
		if (strcmp(s, cap->file->name) == 0)
			return n;
		cap = cap->next;
		n++;
	}
	return 0;
}
//functie care printeaza calea la care ma aflu
void pwdrec(Directory *current)
{
	if (current->parentDir == NULL)
		printf("/");
	else {
		pwdrec(current->parentDir);
		printf("%s/", current->name);
	}
}
//functie recursiva care afiseaza directoarele si fisierele
//in care se poate ajunge pornid din directorul current in
//forma de ierarhie
void p_tree(Directory *current, int nivel)
{
	int i;

	if (current->fisiere == NULL && current->directoare == NULL)
		return;
	TList_file *f;
	Tlist_direct *d;

	f = current->fisiere;
	while (f != NULL) {
		for (i = 0; i < nivel; i++)
			printf("    ");
		printf("%s\n", f->file->name);
		f = f->next;
	}
	d = current->directoare;
	while (d != NULL) {
		for (i = 0; i < nivel; i++)
			printf("    ");
		printf("%s\n", d->directory->name);
		nivel++;
		p_tree(d->directory, nivel);
		nivel--;
		d = d->next;
	}
}
//functie care sterge fisierul aflat pe pozitia n
void deletefisier(TList_file **cap, int n)
{
	if (n == 0) {
		TList_file *p;

		p = malloc(sizeof(TList_file));
		p = (*cap);
		(*cap) = p->next;
		free(p->file->name);
		free(p->file->data);
		free(p);
	} else {
		TList_file *p;

		p = malloc(sizeof(TList_file));
		p = (*cap);
		int k = 0;

		while (p != NULL && k < (n-1)) {
			p = p->next;
			k++;
		}
		if (p == NULL || p->next == NULL)
			return;
		p->next = p->next->next;
	}
}
//functie carevsterge directorul aflat pe pozitia n
void deletedir(Tlist_direct **cap, int n)
{
	if (n == 0) {
		Tlist_direct *p;

		p = malloc(sizeof(Tlist_direct));
		p = (*cap);
		(*cap) = p->next;
		free(p);
	} else {
		Tlist_direct *p;

		p = malloc(sizeof(Tlist_direct));
		p = (*cap);
		int k = 0;

		while (p != NULL && k < (n-1)) {
			p = p->next;
			k++;
		}
		if (p == NULL || p->next == NULL)
			return;
		p->next = p->next->next;
	}
}

void main(void)
{
	char buf[1000];
	int i;
	Directory *direct, *current;

	while (fgets(buf, 1000, stdin)) {
		char *sir;
		char **matrice;
		sir = strdup(buf);
		sir[strlen(sir) - 1] = '\0';
			if (strcmp(sir, "delete fs") == 0) {
				deletefs(&direct);
				break;
		} else
			if (strcmp(sir, "create fs") == 0) {
				createfs(&direct);
				current = direct;
		} else
		//bagarea in lista inlantuita care ii corespunde directorului
		//current a fisierelor in ordine lexicografica
			if (strstr(sir, "touch")) {
				TList_file *aux,*initial = NULL;

				matrice = separare(sir, 3);
				aux = alocarefile(current, matrice[1],
						matrice[2]);
				if (current->fisiere == initial) {
					current->fisiere = aux;
			} else {
				if (strcmp(current->fisiere->file->name,
						aux->file->name) > 0) {
					aux->next = current->fisiere;
					current->fisiere = aux;
			} else {
				TList_file *p = current->fisiere, *q;

				while ((strcmp(p->file->name,
						aux->file->name) < 0)
							&& (p->next != NULL)) {
					q = p;
					p = p->next;
				}
				if (p->next == NULL
						&& strcmp(p->file->name,
							aux->file->name) < 0) {
					p->next = aux;
			} else
				if (q->next != NULL) {
					aux->next = q->next;
					q->next = aux;
				}
			}
			}
			for (i = 0; i < 3; i++)
				free(matrice[i]);
			free(matrice);
	} else
	//bagarea in lista inlantuita care ii corespunde directorului
	//current a directoarelor in ordine lexicografica
		if (strstr(sir, "mkdir")) {
			Tlist_direct *aux;

			matrice = separare(sir, 2);
			aux = mkdir(matrice[1], current);
			if (current->directoare == NULL) {
				current->directoare = aux;
		} else {
			if (strcmp(current->directoare->directory->name,
					 aux->directory->name) > 0) {
				aux->next = current->directoare;
				current->directoare = aux;
			} else {
				Tlist_direct *p = current->directoare, *q;

				while ((strcmp(p->directory->name,
						aux->directory->name) < 0)
							&& (p->next != NULL)) {
					q = p;
					p = p->next;
				}
				if (p->next == NULL
						&& strcmp(p->directory->name,
							aux->directory->name)
								 < 0) {
					p->next = aux;
			} else
				if (q->next != NULL) {
					aux->next = q->next;
					q->next = aux;
				}
			}
			}
			for (i = 0; i < 2; i++)
				free(matrice[i]);
			free(matrice);
	} else
	//listarea fisierelor si directoarelor corespunzatoare
	//directorului current
		if (strcmp(sir, "ls") == 0) {
			TList_file *l;

			l = current->fisiere;
			while (l != NULL) {
				printf("%s ", l->file->name);
				l = l->next;
			}
			Tlist_direct *d;

			d = current->directoare;
			while (d != NULL) {
				printf("%s ", d->directory->name);
				d = d->next;
			}
			printf("\n");
	} else
	//schimbarea directorului current daca acest lucru este
	//posibil si retinerea parintelui acestuia
		if (strstr(sir, "cd")) {
			Tlist_direct *d;
			Directory *last;

			last = current;
			matrice = separare(sir, 2);
			if (validare(matrice[1],
					current->directoare) == 0
						&& strcmp(matrice[1], "..")
							 != 0)
				printf(
					"Cannot move to '%s': No such directory!\n",
					 matrice[1]);
		else
			if (strcmp(matrice[1], "..") == 0) {
				current = last->parentDir;
			} else {
				d = gasire(matrice[1], current->directoare);
				current = d->directory;
				current->parentDir = last;
			}
			for (i = 0; i < 2; i++)
				free(matrice[i]);
			free(matrice);
	} else
	//aflarea caii unde ma aflu
		if (strcmp(sir, "pwd") == 0) {
			Directory *parcurgere;

			parcurgere = current;
			if (parcurgere->parentDir == NULL)
				printf("/");
			else {
				pwdrec(parcurgere->parentDir);
				printf("%s", parcurgere->name);
			}
			printf("\n");
	} else
	//functia tree
		if (strcmp(sir, "tree") == 0) {
			Directory *nou;

			nou = current;
			printf("%s\n", nou->name);
			p_tree(nou, 1);
		}
	else
	//functia rm si rmdir
		if (strstr(sir, "rm")) {
			int pozitie;

			matrice = separare(sir, 2);
			if (strcmp(matrice[0], "rm") == 0) {
				if (valfisiere(matrice[1],
					current->fisiere) == 0)
					printf(
					"Cannot remove '%s': No such file!\n",
					 matrice[1]);
				else {
					pozitie = gasirefisiere(matrice[1],
							current->fisiere);
					deletefisier(&current->fisiere,
						pozitie);
				}
		} else {
			if (strcmp(matrice[0], "rmdir") == 0) {
				if (validare(matrice[1],
					current->directoare) == 0)
					printf(
					"Cannot remove '%s': No such directory!\n",
					 matrice[1]);
				else {
					pozitie = gasiredirector(matrice[1],
							current->directoare);
					deletedir(&current->directoare,
						pozitie);
				}
			}
			}
			for (i = 0; i < 2; i++)
				free(matrice[i]);
			free(matrice);
		}
		free(sir);
	}
}
