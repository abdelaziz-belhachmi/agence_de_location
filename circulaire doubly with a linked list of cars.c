#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//circulaire doublement chainee
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
  struct location *prev_location;
 }location;

//fin de declaration structs

//les functions

location *creat_lo_node();

voiture *creat_v_node();

location *Ajouter_location(location *Lr);

int calculer_prix_total(location *Lr);//returne le prix a payer par le client cette fonction sera appeler dans enregistrer et afficher les locations

void find_print_prix(location *Lr);// fonction additionelle pour afficher le price pour quellque soit le cin 

void Afficher_liste_locations(location *Lr); // printf toutes les locations

FILE *Enregistrer_location(location *Lr);// comme afficher mais dans un fichier utilisant fprintf 

void Rechercher_location(location *Lr);//recherche une location et l'affiche.

location *location_return(location *Lr);//fonction recherche puis returne l'adress de location 

location *Supprimer_location(location *Lr);//derefrence and free()


void Menu_general(){
  printf("1. ajouter une location.\n");
  printf("2. Afficher toutes les locations.\n");
  printf("3. Calculer puis afficher le prix total d'un client.\n");
  printf("4. Rechercher location.\n ");
  printf("5. Enregistrer une location existante dans un fichier.\n ");
  printf("6. Supprimer location.\n");
  printf("7. quiter le program.\n");
}
//end fonctionsr
int main(){
int m;

location *Lr= NULL;
FILE *sps ;

while (1) /*on reste toujour dans while jusque l utulisateur choissisera case 7 pour quiter tous le programe*/ {  
 Menu_general();
scanf("%d",&m);

switch (m){

case 1:
Lr =Ajouter_location(Lr);
break;

case 2:
Afficher_liste_locations(Lr);
break;

case 3:
find_print_prix(Lr);
break;

case 4:
Rechercher_location(Lr);
break;

case 5:
sps = Enregistrer_location(Lr);
break;

case 6:
Lr = Supprimer_location(Lr);
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
location *Ajouter_location(location *Lr){
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
/*----
----
--
-*/
if (Lr == NULL){
h->next_location = h; // h est un node de struct location  plain mais seule qui point sur luis meme si c est la premier fois creant une location
 h->prev_location =h;
  Lr = h;
}
else {
  location *s=Lr;
while (s->next_location != Lr)
{
  s=s->next_location;
}
Lr->prev_location = h;
h->next_location = Lr;
h->prev_location =s;
s->next_location = h;
}
return Lr;//Lr est le head du list circular double
}
 
 
 /*
 *
 *
 *
 *
 */
 
 /* printf le prix a payer par un seul client */


 void find_print_prix(location *Lr) {
 
 location *Fc =Lr;
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
 int pj=vv->prix_du_jour;
 int dl =vv->duree_location;
 a = a + (pj)*(dl) ;
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
//return prix par un client
int calculer_prix_total(location *Lr ) {
 
 location *Fc =Lr;
 
 if (Fc == NULL ){
 printf("list vide == NULL");
 
 }
 else {

 int a=0;
 voiture *vv = NULL;
 vv = (struct voiture *) Fc->voiture_louee ;
 while ( vv != NULL  /*Fc->voiture_louee->nxt !=NULL*/){
 int pj=vv->prix_du_jour;
 int dl =vv->duree_location;
 a = a + (pj)*(dl) ;
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
 
void Afficher_liste_locations(location *Lr){
location *ff = Lr;

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

} while (ff != Lr);

}
/*
*
*
*/
//trouve une location et la printf 
void Rechercher_location(location *Lr){

 location *Fc =Lr;
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
//trouve une certainne location puis return la seulement
location *location_return(location *Lr){

 location *Fc =Lr;
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

FILE *Enregistrer_location(location *Lr){

location *ff =location_return(Lr) ;

char n[20];
    printf("\nEcrire le nome de fichier sans extention .txt si vous utilisez windows :");
    scanf("%s",n);

    FILE *fichier = NULL;
    fichier = fopen(n, "a");
    if (!fichier){
        printf("********************\nError de creation du fichier , svp nottez bien si vous utilisez windows le program ne peut pas cree le fichier , si vouz utilisez autre system d operation ca va bien marcher avec l extention .txt\n");
     }
    
   
    fprintf(fichier,"Identificateur de la location: %s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louées :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",ff->Identifiacteur_location,ff->Client.cin,ff->Client.name,ff->Client.prenom);
  
  voiture *vv ;
  vv = (struct voiture *) ff->voiture_louee ;
  
  while (vv != NULL)
  {
    fprintf(fichier," %s\t\t\t\t%s\t\t\t%d\t\t%d\n",vv->matricule,vv->marque,vv->prix_du_jour,vv->duree_location);
    vv = vv->nxt;

  }
  fprintf(fichier,"\n\nPrix total a payer par le client : %d DH \n\n",calculer_prix_total(ff));
    
  fclose(fichier);
    return fichier;
}


//supprimer
location *Supprimer_location(location *Lr){
printf("veuillez entrer le CIN d'utilisateur a supprimer ci-dessous:\n");
location *sp = location_return(Lr);// recherche node of cin then return it we need to delete it

if (sp==Lr)//if the sp == head
{
location *p= Lr;
// while (p->next_location != Lr)
// {
// p=p->next_location;
//     /* we need to find the node before sp wich is the last node or the node befor the *head Lc */
// }
p=p->prev_location;

p->next_location =p->next_location->next_location; // skipping the sp

Lr=p->next_location; // moving the head to the next if next null so the list have 1 node and the new head is null
Lr->prev_location =p;
free(sp);//free the sp

 }
 
 
 
 else{//if the sp not the head
location *p = sp;
//we jst took the node we need to delete

// while (p->next_location != sp)
// {
//   p=p->next_location;
//     /* we just found the node behind sp */
// }
p=p->prev_location;
//we will skipp it in the list
p->next_location =p->next_location->next_location;
p=p->next_location;
p->prev_location =sp->prev_location;
//now we  will free the sp
free(sp);
}
return Lr;
}
