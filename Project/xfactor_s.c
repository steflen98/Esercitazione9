#include <stdio.h>
#include <string.h>
#include "xfactor.h"
static int inizializzato=0;
static Candidati candidati;

void inizializza(){
    int i;
    
    if(inizializzato == 1) return;
    
    for(i=0; i<NUMCANDIDATI; i++){
        strcpy(candidati.candidato[i].nome.nome_val, "L");
        strcpy(candidati.candidato[i].giudice.giudice_val, "L");
        strcpy(candidati.candidato[i].nomefile.nomefile_val, "L");
        candidati.candidato[i].categoria = 'L';
        candidati.candidato[i].fase = 'L';
        candidati.candidato[i].voto = -1;
    }

    //inizializzo Secondo e Terzo come da Proposta
    strcpy(candidati.candidato[1].nome.nome_val, "Brasco");
    strcpy(candidati.candidato[1].giudice.giudice_val, "Bowie");
    strcpy(candidati.candidato[1].nomefile.nomefile_val, "BrascoProfile.txt");
    candidati.candidato[1].categoria = 'U';
    candidati.candidato[1].fase = 'A';
    candidati.candidato[1].voto = 100;
    
    strcpy(candidati.candidato[2].nome.nome_val, "Viga");
    strcpy(candidati.candidato[2].giudice.giudice_val, "Winehouse");
    strcpy(candidati.candidato[2].nomefile.nomefile_val, "VigaProfile.txt");
    candidati.candidato[2].categoria = 'D';
    candidati.candidato[2].fase = 'S';
    candidati.candidato[2].voto = 50;
    
    inizializzato = 1;
}

void scambia(Giudice giudice1, Giudice giudice2){
    Giudice temp = giudice1;
    giudice1 = giudice2;
    giudice2 = temp;
}

void ordinaGiudici(Giudici giudici, int n){
    int i; int ordinato = 0;
    while (n>1 && ordinato==0){
        ordinato = 1;
        for (i=0; i<n-1; i++)
            if (giudici.giudice[i].punteggio>giudici.giudice[i+1].punteggio) {
                scambia(giudici.giudice[i], giudici.giudice[i+1]);
                ordinato = 0; 
            }
        n--;
    }
}

Giudici * classifica_giudici_1_svc(void *in, struct svc_req *rqstp){
    static Giudici giudici;
    int i, j, n=0, esiste; // n: numero giudici
    inizializza();
    
    for(i=0; i<NUMCANDIDATI; i++){
        esiste = 0;
        for(j=0; j<n && !esiste; j++){
            if(strcmp(candidati.candidato[i].giudice.giudice_val, giudici.giudice[j].nome.nome_val)==0){
                esiste=1;
                giudici.giudice[j].punteggio += candidati.candidato[i].voto;
            }
        }
        
        if(!esiste){
            n++;
            giudici.giudice[n].punteggio += candidati.candidato[i].voto;
        }
    }
    ordinaGiudici(giudici, n);
    return &giudici;
}

int * esprimi_voto_1_svc(Input *input, struct svc_req *rqstp){
    static int result;
    int i;
    inizializza();
    
    for(i=0; i<NUMCANDIDATI; i++){
        if(strcmp(input->nome.nome_val, candidati.candidato[i].nome.nome_val)==0){
            if(input->operazione == '+'){
                candidati.candidato[i].voto++;
                result = 0;
                return &result;
            }
            else if(input->operazione == '-'){
                candidati.candidato[i].voto--;
                result = 0;
                return &result;
            }
            else{
                result = -1;
                return &result; //errore operatore
            }
        }
    }
    result = -2;
    return &result; //candidato non esistente
}