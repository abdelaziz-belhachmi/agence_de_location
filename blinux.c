#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//start structs

 typedef struct Persone {
  char cin[15] ;
  char name[20];
  char prenom[20];
  }Persone;

typedef struct voiture {
  char matricule[15];
  char marque[100];
  int prix_du_jour;
  int duree_location;
  struct voiture *nxt;
}voiture;

typedef struct location {
char Identifiacteur_location[25];
  voiture *voiture_louee ;
  Persone Client;
  struct location *next_location;
   //struct location *prev_location; for doubly 
 }location;

//end structs
//lkmala d l idea dftar
// functions

location *creat_lo_node();

voiture *creat_v_node();

location *Ajouter_location(location *Lc);

int calculer_prix_total(location *Lc);//it return what we need to print in the file

void find_print_prix(location *Lc);//additional fonction that print price for any given cin

void Afficher_liste_locations(location *Lc); // print all as given

void Enregistrer_location();// same as afficher jst in file use fprintf instead

void Rechercher_location(location *Lc);//easy already done

void Supprimer_location();//derefrence and free()

void Menu_general(){
  printf("1. ajouter une location.\n");
  printf("2. Afficher toutes les locations.\n");
  printf("3. Calculer puis afficher le prix total d'un client.\n");
  printf("4. Rechercher location.\n ");
  printf("5. Supprimer location.\n ");
  printf("6. Enregistrer une location existante dans un fichier.\n");
  printf("7. quiter le program.\n");
}
//end fonctions

int main(){
int m;

location *Lc= NULL;
// location *mp ;

while (1){
 Menu_general();
scanf("%d",&m);

switch (m){

case 1:
Lc =Ajouter_location(Lc);
break;

case 2:
Afficher_liste_locations(Lc);
break;

case 3 :
find_print_prix(Lc);
break;

case 4 :
Rechercher_location(Lc);
break;

case 5 :
//
break;

case 6 :
break;

case 7:
printf("\nAttention : si vous quitter le programe toutes les locations enregistre seront perdus !! \n");
printf("Vous voulez vraiment quitter ? :\n*tappez le nombre \"1\" si Oui \n*tappez le nombre \"2\" si Non\n:");
int fin;
scanf("%d",&fin);
if (fin == 1)
{
return 0;
}else{ fin = 0;}

break;

default:
printf("\n \n ****invalid choice***** \n \n"); 
}//end switch case

}//end while loop

return 0;// end main()
}

/***functions declaration****/

location *creat_lo_node(){
  location *t = malloc(sizeof(location));
  return t;
}
/*
*
*/
voiture *creat_v_node(){
voiture *tm = malloc(sizeof(voiture));
return tm;
}
/*
*
*/
location *Ajouter_location(location *Lc){
  int N,n=0;

  location *h = creat_lo_node();

  struct voiture *head =NULL;
  struct voiture *p ;


printf("\n Entrer un indentificateur pour cette location  \"un referance de 25 character au maximum\" :");
scanf("%s",h->Identifiacteur_location);

printf("\n Entrer le nom du client :");
scanf("%s",h->Client.name);

printf("\n Entrer le prenom du client :");
scanf("%s",h->Client.prenom);

printf("\n Entrer le CIN du client :");
scanf("%s",h->Client.cin);

printf("\n Combier de voiture ce client veut louer :");
scanf("%d",&N);

while (n != N)
{
  voiture *temp = creat_v_node();
printf("\n Entrer la matricule de la voiture N%d :",n+1);
scanf("%s",temp->matricule);

printf("\n Entrer la marque de la voiture N%d :",n+1);
scanf("%s",temp->marque);

printf("\n Entrer le prix du jours de la voiture N%d :",n+1);
scanf("%d",&(temp->prix_du_jour));

printf("\n Entrer Combien ce client va louer la voiture N%d :",n+1);
scanf("%d",&(temp->duree_location) );

temp->nxt = NULL;

if (head == NULL)
{
  head = temp;
} 
else{
  p=head; //take the head

  while (p->nxt != NULL){
  p=p->nxt; // if the next isnt null pass to the next node.
  }
  p->nxt= temp; // when the nxt is null take the node temp jst been made
}
n++; // repeat the number of cars rent
}
h->voiture_louee = head; // take the head pointer and store it in location.voiture_louee  db chaque location a un client et N voitures .
/*-----------
--*/
if (Lc == NULL){
h->next_location = h; // h is a struct location  full but alone and pointing to it self when first time
  Lc = h;
}
else {
  location *s=Lc;
while (s->next_location != Lc)
{
  /* code */
  s=s->next_location;
}
h->next_location = Lc;
s->next_location = h;
}
return Lc;//Lc just got the whole list
}
 
 
 /*
 *
 *
 *
 *
 */
 
 /* print only the price */


 void find_print_prix(location *Lc) {
 
 location *Fc =Lc;
 char c[15];
 
 if (Fc == NULL ){
 printf("Fc == NULL");
 
 }
 else {
 printf("entrer CIN :");
 scanf("%s",c);
 
 while (strcmp(Fc->Client.cin,c)!= 0){
 Fc =Fc->next_location; 
}
 //initialisation voiture incompatible with location !! voiture *Vs = Fc->next_location;
 if(Fc->voiture_louee == NULL){
 printf("Fc->voiture_louee ==NULL");
 }else {
 int a=0;
 voiture *vv = NULL;
 vv = (struct voiture *) Fc->voiture_louee ;
 while ( vv != NULL  /*Fc->voiture_louee->nxt !=NULL*/){
 int dd=vv->prix_du_jour;
 int bd =vv->duree_location;
 a = a + (dd)*(bd) ;
 vv = vv->nxt;
 //Fc->voiture_louee = Fc->voiture_louee->nxt;
 }
 printf("ce client doit payer %d\n",a);
 }
 }
 } // end prnt()

 /*
 *
 */

int calculer_prix_total(location *Lc ) {
 
 location *Fc =Lc;
 
 if (Fc == NULL ){
 printf("list vide == NULL");
 
 }
 else {

 int a=0;
 voiture *vv = NULL;
 vv = (struct voiture *) Fc->voiture_louee ;
 while ( vv != NULL  /*Fc->voiture_louee->nxt !=NULL*/){
 int dd=vv->prix_du_jour;
 int bd =vv->duree_location;
 a = a + (dd)*(bd) ;
 vv = vv->nxt;
 //Fc->voiture_louee = Fc->voiture_louee->nxt;
 }
 return a;
 
 }
 } // end prnt()

/*
*
*
*/
 
void Afficher_liste_locations(location *Lc){
location *ff = Lc;

do
{
  printf("%s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louées :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",ff->Identifiacteur_location,ff->Client.cin,ff->Client.name,ff->Client.prenom);
  voiture *vv = NULL;
  vv = (struct voiture *) ff->voiture_louee ;
  while (vv != NULL)
  {
    printf("%s\t%s\t%d\t%d\n",vv->matricule,vv->marque,vv->prix_du_jour,vv->duree_location);
    vv = vv->nxt;

  }
  printf("Prix total a payer par le client : %d DH \n\n",calculer_prix_total(ff));
  ff=ff->next_location;

} while (ff != Lc);

}
/*
*
*
*/
void Rechercher_location(location *Lc){


 location *Fc =Lc;
 char c[15];
 
 if (Fc == NULL ){
 printf("Fc == NULL");
 
 }
 else {
 printf("entrer CIN :");
 scanf("%s",c);
 
 while (strcmp(Fc->Client.cin,c)!= 0){
 Fc =Fc->next_location; 
}
  printf("%s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louees :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",Fc->Identifiacteur_location,Fc->Client.cin,Fc->Client.name,Fc->Client.prenom);

     voiture *vv = NULL;
  vv = (struct voiture *) Fc->voiture_louee ;
  while (vv != NULL)
  {
    printf("%s\t%s\t%d\t%d\n",vv->matricule,vv->marque,vv->prix_du_jour,vv->duree_location);
    vv = vv->nxt;

  }
  printf("Prix total a payer par le client : %d DH \n\n",calculer_prix_total(Fc));

}

}
