/*******************************************************************************************/
/*                           Willkommen zur 5.Aufgabe                                      */
/*            Dieses Programm zielt darauf ab den Umgang mit der Verwaltung                */
/*                      des dynamischen Speichers zu erlernenn                             */
/*******************************************************************************************/


/*******************************************************************************************/
/*                               Author: Stefan Hermeter                                   */
/*                                  Klasse:5/6 ABETI                                       */
/*                                 Datum:  07.03.2016                                      */
/*******************************************************************************************/


/*****************************************/
/*      Die verwendeten Libaries         */
/*****************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#define N 300

int main(int argc, char *argv[])
{
  // zähler für Fehler und Argumenteneingabe
  int stder = 0;
  int opt;

  extern int optopt;
  
  while ((opt = getopt(argc, argv, "h")) != -1) {
    switch (opt) {

      /* Aufruf der Hilfe mit '-h'*/
    case 'h':
      printf("Dies ist die Hilfe des Programmes.\nDieses Programm liest \'uebtext.txt\'ein.\nSie werden danach abgefragt welche Zeile sie auf der Commandozeile ausgeben möchten.\n\t-h\t...\tgibt die Hilfe des Programms aus.\nDas Programm beendet sich nach der Ausgabe.\n");
      return 0;

      /* Wenn ein falsches Argument aufgerufen wurde */
      case'?':
      if (isprint (optopt)){
	printf ("Please Type %s, -h for more information.\n", argv[0]);
      }
      stder++;
      break;
    }
  }

  /* Abfangen eines Fehlers bei flasche Argumenteneingabe */
  if(stder == 1){
    return 1;
  }

  FILE * fp;
  char line[N];
  
  /* initialisierung des Arraypointers */
  char ** ptr2p = NULL;
  int len;
  int i = 0;

  /* Oeffnen der Datei */
  fp = fopen("uebtext.txt","r");

  /**************************************/
  /*   Zeilenweise einlesen der Datei   */
  /* mit dynamischer Speicherverwaltung */
  /**************************************/
  while (fgets(line,N,fp)) {

    /* Abfangen eines Fehlers wenn es beim oeffnen der Datei probleme gibt. */
    if(fp == NULL){
      printf("Fehler beim Oeffnen der Datei.\n");
      return 1;
    }

    ptr2p = realloc(ptr2p,(i+1) * sizeof(char *));
    len = strlen(line);
    ptr2p[i] = calloc(sizeof(char),len+1);

    strcpy(ptr2p[i],line);
    i++;
  }

  int j, a;

  /* Inhalt der Datei auf 'cli' ausgeben */
  for(j = 0; j < i; j++) {
    printf("%s",ptr2p[j]);
  }
  /* Abfrage welche Zeile ausgegeben werden soll */
   printf("Bitte geben sie die Zeile an welche sei ausgeben möchten:");
  do{
    scanf("%d", &a);
    if(a < 2 || a > j){
      printf("\nDie Zahl muss größer als 2 sein und kleiner als %d:",j+1);
    }
  }while(a < 2 || a > j);

  /* löschen des Eingabepuffers */
  fflush(stdin);

  int b = a - 3;
  a = a - 3;

  /* Ausgabe der 5 Zeilen ('\033[31m' Code bei Debian für färbige Ausgabe) */
  while(b != a +5) {
    if( b > j)break;
    if(b == a + 2){
      printf("\033[31m%s", ptr2p[b]);
    }else{
      printf("\033[m%s", ptr2p[b]);
    }
    b++;
    if(b == a + 5)break;
  }

  /* ENDE */
  return 0;
}
