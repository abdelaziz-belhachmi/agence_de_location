#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaration des structures

 typedef struct Persone {
  char cin[15] ;
  char name[20];
  char prenom[20];
  }Persone;

typedef struct voiture {
  char matricule[25];
  char marque[50];
  int prix_du_jour;
  int duree_location;
  struct voiture *nxt;
}voiture;

typedef struct location {
char Identifiacteur_location[25];
  voiture *voiture_louee ;
  Persone Client;
  struct location *next_location;
   //struct location *prev_location; pour doublement chainee
 }location;

//fin de declaration structs

//les functions

location *creat_lo_node();

voiture *creat_v_node();

location *Ajouter_location(location *Lc);

int calculer_prix_total(location *Lc);//returne le prix a payer par le client cette fonction sera appeler dans enregistrer et afficher les locations

void find_print_prix(location *Lc);// fonction additionelle pour afficher le price pour quellque soit le cin 

void Afficher_liste_locations(location *Lc); // printf toutes les locations

FILE *Enregistrer_location(location *Lc);// comme afficher mais dans un fichier utilisant fprintf 

void Rechercher_location(location *Lc);//recherche une location et l'affiche.

location *location_return(location *Lc);//fonction recherche puis returne l'adress de location 

location *Supprimer_location(location *Lc);//derefrence and free()


void Menu_general(){
  printf("1. ajouter une location.\n");
  printf("2. Afficher toutes les locations.\n");
  printf("3. Calculer puis afficher le prix total d'un client.\n");
  printf("4. Rechercher location.\n ");
  printf("5. Enregistrer une location existante dans un fichier.\n ");
  printf("6. Supprimer location.\n");
  printf("7. quiter le program.\n");
}
//end fonctions

int main(){
int m;

location *Lc= NULL;
FILE *sps ;

while (1) /*on reste toujour dans while jusque l utulisateur choissisera case 7 pour quiter tous le programe*/ {  
 Menu_general();
scanf("%d",&m);

switch (m){

case 1:
Lc =Ajouter_location(Lc);
break;

case 2:
Afficher_liste_locations(Lc);
break;

case 3:
find_print_prix(Lc);
break;

case 4:
Rechercher_location(Lc);
break;

case 5:
sps = Enregistrer_location(Lc);
break;

case 6:
Lc = Supprimer_location(Lc);
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

return 0;
}// end main()

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
  p=head; //p copy temporaire de head

  while (p->nxt != NULL){
  p=p->nxt; // if the next isnt null pass to the next node.
  }
  p->nxt= temp; // when the nxt is null take the node temp jst been made
}
n++; // repeter selon le nombre de voiture le client va louer
}
h->voiture_louee = head; // enregistrant head dans location.voiture_louee  maintenant chaque location a un client et N voitures (les voitures sont simplement chainee !!) .
/*-----------
--*/
if (Lc == NULL){
h->next_location = h; // h est un node de struct location  plain mais seule qui point sur luis meme si c est la premier fois creant une location
  Lc = h;
}
else {
  location *s=Lc;
while (s->next_location != Lc)
{
  s=s->next_location;
}
h->next_location = Lc;
s->next_location = h;
}
return Lc;//Lc est le head du list
}
 
 
 /*
 *
 *
 *
 *
 */
 
 /* printf le prix a payer par un seul client */


 void find_print_prix(location *Lc) {
 
 location *Fc =Lc;
 char c[15];
 
 if (Fc == NULL ){
 printf("Fc == NULL");
 
 }
 else {
 printf("\nEntrer CIN :");
 scanf("%s",c);
 
 while (strcmp(Fc->Client.cin,c)!= 0){
 Fc =Fc->next_location; 
}
 
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
 printf("\n**Ce client doit payer %d DH\n",a);
 }
 }
 } // end find_print_prix()

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
 } // end ()

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
//trouve une location et la printf 
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
/*
*
*
* 
*/
//trouve une certainne location puis return la 
location *location_return(location *Lc){

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
}
return Fc;
}


/*
enregistre location dans un fichier
*/

FILE *Enregistrer_location(location *Lc){

location *ff =location_return(Lc) ;

char n[20];
    printf("\nwrite the file name with the extention .txt");
    scanf("%s",n);

    FILE *regularTxt = NULL;
    regularTxt = fopen(n, "a");
    if (!regularTxt){
        printf("****error with regtxt");
     }
    
   
    fprintf(regularTxt,"Identificateur de la location: %s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louées :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",ff->Identifiacteur_location,ff->Client.cin,ff->Client.name,ff->Client.prenom);
  
  voiture *vv ;
  vv = (struct voiture *) ff->voiture_louee ;
  
  while (vv != NULL)
  {
    fprintf(regularTxt," %s\t\t\t\t%s\t\t\t%d\t\t%d\n",vv->matricule,vv->marque,vv->prix_du_jour,vv->duree_location);
    vv = vv->nxt;

  }
  fprintf(regularTxt,"\n\nPrix total a payer par le client : %d DH \n\n",calculer_prix_total(ff));
    
  fclose(regularTxt);
    return regularTxt;
}



location *Supprimer_location(location *Lc){
printf("veuillez entrer le CIN d'utilisateur a supprimer ci-dessous:\n");
location *sp = location_return(Lc);// recherche node of cin then return it we need to delete it

if (sp==Lc)//if the sp == head
{
location *p= Lc;
while (p->next_location != Lc)
{
p=p->next_location;
    /* we need to find the node before sp wich is the last node or the node befor the *head Lc */
}

p->next_location=p->next_location->next_location; // skipping the sp

Lc=p->next_location; // moving the head to the next if next null so the list have 1 node and the new head is null
free(sp);//free the sp

 }else{//if the sp not the head
location *p = sp;
//we jst took the node we need to delete

while (p->next_location != sp)
{
  p=p->next_location;
    /* we just found the node behind sp */
}
//we will skipp it in the list
p->next_location =p->next_location->next_location;
//now we  will free the sp
free(sp);
}

return Lc;
}
