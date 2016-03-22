/*******************************************************************************************/
/*                              Willkommen zur 5.Aufgabe                                   */
/*            Dieses Programm zielt darauf ab den Umgang mit fopen zu erlernen             */
/*                       sowie eine besseres Handling mit strings                          */
/*                                    zu erreichen                                         */
/*******************************************************************************************/



/*******************************************************************************************/
/*                               Author: Stefan Hermeter                                   */
/*                                  Klasse:5/6 ABETI                                       */
/*                                 Datum:  07.03.2016                                      */
/*******************************************************************************************/


/*****************************************/
/*      Die verwendeten Libaries         */
/* bzw. die maximale Anzahl der Vektoren */
/*****************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#define N 2048
#define M 200


/**********************************************/
/*             Funktion xml_tag               */
/*  Zeilenweise abfragen des Files + Ausgabe  */
/**********************************************/

int xml_tag(int len, char text[N]){
  
  int i = 0;
  int j = 0;
  char buff1[N];

  /* Umsortieren auf buffer(text) */
  for(; i < len; i++){
    buff1[i] = text[i];
    if(text[i] == '\0')break;
    
  }
  
  /* Auslagern des Inhalt und des tags in einen String */
  char *ptr;;
  const char s1[]= "<>";
  char tag[M], inhalt[len];
  ptr = strtok(buff1, s1);
  j = 0;
  while(ptr != NULL){
    if(j == 0)strncpy(tag, ptr, len);     // Pointerstring auslagern
    if(j == 1)strncpy(inhalt, ptr, len);  // -----------||----------
    ptr = strtok(NULL, s1);
    j++;
  }
  /* Ausgabe des Namen sowie des Inhaltes */
  if(tag[0] != '\0'){
    printf("Elementname: %s\nInhalt: %s\n\n",tag, inhalt);
  }
  return 0;
}


/**********************************************/
/*           Funktion xml_finder              */
/* durch vergleichen der tags und des headers */
/**********************************************/

int xml_finder(int len, const char text[N]){

  /* initialisierung const char xml header */
  const char buff1[6] = {'<','?','x','m','l','\0'};
  int check = -1;                   //checksumme
  int i = 0;
  size_t t = 5;

  /* Vergleich des headers mit text(buff) */
  i = strncmp(text, buff1, t);

  /* erster check ob es eine xml-Datei sein könnte */
  if(i == 0){
    check++;
  }else{
    return -1;
  }

  int j = 0;
  int k = 0;
  char buff2[len];

  /* umsortieren auf buffer */
  for(i = 0; i < len; i++){
    if(text[i] == '\n')j++;
    if(j == 2){
      buff2[k] = '\0';
      break;
    }
    if(j == 1){
      buff2[k] = text[i];
      k++;
    }
  }
  /* Überprüfung des tags */
  char *ptr;
  char *tag1, *tag2;
  const char s1[] = "</>";
  ptr = strtok(buff2,"</>");
  i = 0;
  while(ptr != NULL){
    if(i == 1)tag1 = ptr;       // Pointerstring auslagern
    if(i == 3)tag2 = ptr;       // -----------||----------
    ptr = strtok(NULL, s1);
    i++;
  }
  /* Zweiter check ob es eine xml Datei ist */

  return strcmp(tag1,tag2) == 0;
}

/*****************************************/
/*         Das Hauptprogramm             */
/*****************************************/
int main(int argc, char *argv[])
{
  /* zähler für Fehler und Argumenteneingabe */
  int stder = 0;
  int opt;
  extern int optopt;
  
  /* getopt: Initialisierung der Argumenteneingabe  minimiert auf Falscheingabe und Hilfe*/
  while ((opt = getopt(argc, argv, "h")) != -1) {
    switch (opt) {

      /* Aufruf der Hilfe mit '-h' */
    case 'h':
      printf("Dieses Programm liest die Datei \'uebtext.txt\' ein und überprüft ob es sich um eine xml-Datei handelt.\nDesweiteren sucht es nach xml-tags und diese werden dann auf der stdout ausgegeben.\n\nWarnung:In diesem Programm ist der header der Datei zwingend erforderlich.\nEs muss mindestens \'<?xml>\' vorhanden sein.");
      return 0;

      /* Wenn ein Falsches Argument aufgerufen wurde  */
      case'?':
      if (isprint (optopt)){
	printf ("Please Type %s, -h for more information.\n", argv[0]);
      }
      stder++;
      break;
    }
  }

  if(stder == 1){
    return 0;
  }
  
  char text[N];
  char *ptr;
  ptr = malloc(sizeof(char));
  
  /* initialisierung des Filepointers */
  FILE *fp;
  int i = 0;

  /* Oeffnen des Files */
  fp = fopen("uebtext.txt","r");
    
  /* Kontrolle ob die Datei geöffnet werden kann */
  if(fp == NULL)
    {
      printf("Fehler beim Oeffnen.");
      return 1;
    }
  
  /* einlesen des Inhalts der Datei */
  while(1){
    *ptr = fgetc(fp);
    // EndofFile beendigung der Schleife
    if (feof(fp))break;
    text[i] = *ptr;
    i++;
  }
  fclose(fp);

  /* kontrolle der groesze der Textdatei */
  int len;
  int check;
  len = strlen(text);

  /* Aufruf der Funktion xml_finder */
  check = xml_finder(len, text);

  /* Checksumme der Funktion xml_finder */
  if(check == -1){
    printf("Es handelt sich nicht um eine \'xml\'-Datei\n\n");
    return 1;
  }else{
    printf("Es handelt sich um eine \'xml\'-Datei\n\n");
  }  

  /* Algorithmus zur zeilenweiseübergabe des Strngs(text) */
  char buff[len];
  int j = 0;
  int k = 0;
  for(i = 0; i < len; i++){
    if(text[i] == '\n'){
      j++;
      if(j > 0 && text[i] == '\n'){
	check = xml_tag(len, buff);
      }
    }
    if(text[i] == '\0')break;
    if(j > 0){
      buff[k] = text[i];
      k++;
      if(text[i] == '\n')k = 0;
    }
  }

  /* ENDE + Checksumme */
  printf("ENDE\n");
  return check;
}
