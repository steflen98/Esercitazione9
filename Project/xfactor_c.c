#include <stdio.h>

void main(int argc, char *argv[]){
    char *host, CLIENT *cl;
    char ok[256];
    Giudici *giudici;
    Input *input;
    void *in;
    char op;
    int *ris;
    
    if(argc!=2){
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    
    cl = clnt_create(host, XFACTOR, XFACTORVERS, "udp");
    if(cl == NULL){
        clnt_pcreateerror (host);
        exit(1);
    }
    
    printf("Inserire: \nC) per vedere la classifica giudici\tV) Per Dare/Togliere un voto ad un candidato\t^D per terminare: ");
    
    while(gets(ok)){
        if(strcmp(ok, "C")==0){
            giudici = classifica_giudici_1(in, cl);
            if(giudici == NULL){
                clnt_perror(cl, host);
                exit(1);
            }
            printf("Classifica GIUDICI: \n");
            for(i=0; i<NUMGIUDICI; i++){
                printf("%d: %s (%d)\n", i+1, giudici.giudice[i].nome, giudici.giudice[i].punteggio);
            }
        } // if C
        else if(strcmp(ok, "V")==0){
            printf("Inserirsi il nome del candidato: ");
            scanf("%s", input.nome);
            
            printf("Vuoi aggiungere (+) o togliere (-) un voto al candidato?\n");
            getchar(op);
            
            if(op!='+' || op!='-'){
                printf("Errore: Inserire + o -\n");
                getchar(op);
            }
            input.operazione = op;
            
            ris = esprimi_esito_1(input, cl);
            
            if(ris == NULL){
                clnt_perror(cl, host);
                exit(1);
            }
            
            if(*ris==0) printf("Operazione riuscita!\n");
            else printf("Operazione fallita :(\n");
        } // if V
        else
            printf("Argomento di ingresso errato!!\n");
        printf("Inserire: \nC) per vedere la classifica giudici\tV) Per Dare/Togliere un voto ad un candidato\t^D per terminare: ");
    } //while
    
    //Libero le risorse, distruggendo il gestore di trasporto
    clnt_destroy(cl);
    exit(0);
} //main