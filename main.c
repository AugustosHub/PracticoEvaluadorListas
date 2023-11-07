#include <stdio.h>
#include <stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<conio.h>

struct Clientes{
    char nombre[20];
    long DNI;
    char tipo[20];
    char servicio[20];
    int ordenG, ordenP, ordenB;

    struct Clientes *sig;
};

struct Clientes *Inicio = NULL;
struct Clientes *Final = NULL;

 int ordenG = 0, ordenB = 0, ordenP = 0;

int vacia()
{
    if (Inicio == NULL)
        return 1;
    else
        return 0;
}

int existeDNI(long dni) {
    struct Clientes *actual = Inicio;

    while (actual != NULL) {
        if (actual->DNI == dni) {
            return 1;  // El DNI ya existe en la lista
        }
        actual = actual->sig;
    }

    return 0;
}

void agregarCliente(){
    char nom[20],cat[10],serv[20];
    int VordenG = 0, VordenB = 0, VordenP = 0;
    long doc;
    int op, op2, op3;

do{
    system("cls");
    fflush(stdin);
    printf("Ingrese el nombre del cliente: ");
    gets(nom);
    printf("Ingrese el DNI de '%s' (sin puntos ni comas): ",nom);
    scanf("%ld",&doc);
    while(existeDNI(doc)) {
        puts("-----------------------------------------------------");
        printf("¡El DNI '%ld' ya está en uso por otro cliente!\n", doc);
        puts("-----------------------------------------------------");
        printf("Ingrese el DNI de '%s' (sin puntos ni comas): ",nom);
        scanf("%ld",&doc);
    }
    printf("\nIngrese la categoria de '%s':\n",nom);
    puts("1.Black\n2.Gold\n3.Platino");
    puts("-----------------");
    printf("Elegir opción: ");
    scanf("%d",&op);
    while(op>3 || op<1){
        puts("------------------------------------");
        puts("¡Opción no valida, intente de nuevo!");
        puts("------------------------------------");
        printf("Elegir opción: ");
        scanf("%d",&op);
    }
    switch(op){
        case 1:
            strcpy(cat,"Black");
            puts("------------------------");
            printf("Su categoria es %s\n",cat);
            puts("------------------------");
            break;
        case 2:
            strcpy(cat,"Gold");
            puts("------------------------");
            printf("Su categoria es %s\n",cat);
            puts("------------------------");
            break;
        case 3:
            strcpy(cat,"Platino");
            puts("------------------------");
            printf("Su categoria es %s\n",cat);
            puts("------------------------");
            break;
    }
    printf("\nIngrese el servicio que necesita: \n");
    puts("1. Atención al Cliente\n2. Atención en Caja");
    puts("-----------------");
    printf("Elegir opción: ");
    scanf("%d",&op3);
    while(op3>2 || op3<1){
        puts("------------------------------------");
        puts("¡Opción no valida, intente de nuevo!");
        puts("------------------------------------");
        printf("Elegir opción: ");
        scanf("%d",&op3);
    }
    switch(op3){
        case 1:
            strcpy(serv,"Atencion al Cliente");
            puts("------------------------");
            printf("Número de orden: ");
            if(strcmp(cat,"Black")==0){
                printf("BC0%d\n",ordenB);
                ordenB = ordenB + 1;
                VordenB = 1;
            }else if(strcmp(cat,"Gold")==0){
                printf("GC0%d\n",ordenG);
                ordenG = ordenG + 1;
                VordenG = 1;
            }else if(strcmp(cat,"Platino")==0){
                printf("PC0%d\n",ordenP);
                ordenP = ordenP + 1;
                VordenP = 1;
            }
            printf("Espere en la fila %s y será atendido\n",cat);
            puts("------------------------");
            system("pause");
            break;
        case 2:
            strcpy(serv,"Atencion en Caja");
            puts("------------------------");
            printf("Número de orden: ");
            if(strcmp(cat,"Black")==0){
                printf("BC0%d\n",ordenB);
                ordenB = ordenB + 1;
                VordenB = 1;
            }else if(strcmp(cat,"Gold")==0){
                printf("GC0%d\n",ordenG);
                ordenG = ordenG + 1;
                VordenG = 1;
            }else if(strcmp(cat,"Platino")==0){
                printf("PC0%d\n",ordenP);
                ordenP = ordenP + 1;
                VordenP = 1;
            }
            printf("Espere en la fila %s y será atendido\n",cat);
            puts("------------------------");
            system("pause");
            break;
    }

    struct Clientes *nuevo;

    nuevo = malloc(sizeof(struct Clientes));

    strcpy(nuevo->nombre, nom);
    strcpy(nuevo->tipo, cat);
    strcpy(nuevo->servicio, serv);
    if(VordenB==1){
        nuevo->ordenB = ordenB;
        nuevo->ordenG = -1;
        nuevo->ordenP = -1;
        VordenB = 0;
    }else if(VordenG == 1){
        nuevo->ordenB = -1;
        nuevo->ordenG = ordenG;
        nuevo->ordenP = -1;
        VordenG = 0;
    }else if(VordenP == 1){
        nuevo->ordenB = -1;
        nuevo->ordenG = -1;
        nuevo->ordenP = ordenP;
        VordenP = 0;
    }
    nuevo->DNI = doc;

    nuevo->sig = NULL;

     if(vacia()){
        Inicio = nuevo;
        Final = nuevo;
    }else{
        Final->sig = nuevo;
        Final = nuevo;
    }
    system("cls");
    puts("¿Desea agregar otro cliente?\n1.Si\n2.No");
    puts("-----------------");
    printf("Elegir opción: ");
    scanf("%d",&op2);
    while(op2>2 || op2<1){
        puts("------------------------------------");
        puts("¡Opción no valida, intente de nuevo!");
        puts("------------------------------------");
        printf("Elegir opción: ");
        scanf("%d",&op2);
    }
    if(op2==2){
        puts("--------------------------------");
        puts("¡Cliente/s agregado con éxito!");
        puts("--------------------------------");
        system("pause");
    }
}while(op2!=2);

}

void verFila(){
    struct Clientes *actual = Inicio;

    puts("Lista de clientes: \n");
    while(actual!=NULL){
        printf("Nombre: %s\n",actual->nombre);
        printf("DNI: %ld\n",actual->DNI);
        printf("Categoría: %s\n",actual->tipo);
        printf("Servicio: %s\n",actual->servicio);
        if(actual->ordenB!=-1&&actual->ordenG==-1&&actual->ordenP==-1){
            printf("Orden N°: BC0%d\n",actual->ordenB);
        }else if(actual->ordenG!=-1&&actual->ordenB==-1&&actual->ordenP==-1){
            printf("Orden N°: GC0%d\n",actual->ordenG);
        }else if(actual->ordenP!=-1&&actual->ordenG==-1&&actual->ordenB==-1){
            printf("Orden N°: PC0%d\n",actual->ordenP);
        }
        puts("------------------------------");
        actual = actual->sig;
    }
    system("pause");
}

void verColaBlack(){
    int c = 0;

    struct Clientes *actual = Inicio;

    puts("Clientes 'Black' en espera: \n");
    puts("Próximo a atender: ");
    puts("------------------------------");
    while(actual!=NULL){
        if(strcmp(actual->tipo,"Black")==0){
            printf("Nombre: %s\n",actual->nombre);
            printf("DNI: %ld\n",actual->DNI);
            printf("Categoría: %s\n",actual->tipo);
            printf("Servicio: %s\n",actual->servicio);
            printf("Orden N°: BC0%d\n",actual->ordenB);
            puts("------------------------------");
            c = c + 1;
        }
        actual = actual->sig;
    }
    if(c==0){
        system("cls");
        puts("------------------------------------");
        puts("¡No hay clientes Black, ahora mismo!");
        puts("------------------------------------");
        system("pause");
    }else{
        system("pause");
    }
}

void verColaGold(){
    int c = 0;

    struct Clientes *actual = Inicio;

    puts("Clientes 'Gold' en espera: \n");
    puts("Próximo a atender: ");
    puts("------------------------------");
    while(actual!=NULL){
        if(strcmp(actual->tipo,"Gold")==0||strcmp(actual->tipo,"Black->Gold")==0){
            printf("Nombre: %s\n",actual->nombre);
            printf("DNI: %ld\n",actual->DNI);
            printf("Categoría: %s\n",actual->tipo);
            printf("Servicio: %s\n",actual->servicio);
            if(actual->ordenG==-1){
                printf("Orden N°: BC0%d\n",actual->ordenB);
            }else{
                printf("Orden N°: GC0%d\n",actual->ordenG);
            }
            puts("------------------------------");
            c = c + 1;
        }
        actual = actual->sig;
    }
    if(c == 0){
        struct Clientes *actual2 = Inicio;
        system("cls");
        puts("------------------------------------------------");
        puts("Cola Gold vacia, se atenderá a un cliente Black:");
        puts("------------------------------------------------");
        puts("Próximo a atender: ");
        puts("------------------------------");
        while(actual2!=NULL){
            if(strcmp(actual2->tipo,"Black")==0||strcmp(actual2->tipo,"Black->Gold")==0){
                printf("Nombre: %s\n",actual2->nombre);
                printf("DNI: %ld\n",actual2->DNI);
                printf("Categoría: %s\n",actual2->tipo);
                printf("Servicio: %s\n",actual2->servicio);
                printf("Orden N°: BC0%d\n",actual2->ordenB);
                puts("------------------------------");
                strcpy(actual2->tipo,"Black->Gold");
                system("pause");
                return;
            }
            actual2 = actual2->sig;
        }
    }else{
        system("pause");
        return;
    }
    system("cls");
    puts("--------------------------------------------");
    puts("¡No hay clientes Black ni Gold, ahora mismo!");
    puts("--------------------------------------------");
    system("pause");
}

void verColaPlatino(){
    int c = 0;

    struct Clientes *actual = Inicio;

    puts("Clientes 'Platino' en espera: \n");
    puts("Próximo a atender: ");
    puts("------------------------------");
    while(actual!=NULL){
        if(strcmp(actual->tipo,"Platino")==0||strcmp(actual->tipo,"Gold->Platino")==0){
            printf("Nombre: %s\n",actual->nombre);
            printf("DNI: %ld\n",actual->DNI);
            printf("Categoría: %s\n",actual->tipo);
            printf("Servicio: %s\n",actual->servicio);
            if(actual->ordenP==-1){
                printf("Orden N°: GC0%d\n",actual->ordenG);
            }else{
                printf("Orden N°: PC0%d\n",actual->ordenP);
            }
            puts("------------------------------");
            c = c + 1;
        }
        actual = actual->sig;
    }
    if(c == 0){
        struct Clientes *actual2 = Inicio;
        system("cls");
        puts("--------------------------------------------------");
        puts("Cola Platino vacia, se atenderá a un cliente Gold:");
        puts("--------------------------------------------------");
        puts("Próximo a atender: ");
        puts("------------------------------");
        while(actual2!=NULL){
            if(strcmp(actual2->tipo,"Gold")==0||strcmp(actual2->tipo,"Gold->Platino")==0){
                printf("Nombre: %s\n",actual2->nombre);
                printf("DNI: %ld\n",actual2->DNI);
                printf("Categoría: %s\n",actual2->tipo);
                printf("Servicio: %s\n",actual2->servicio);
                printf("Orden N°: GC0%d\n",actual2->ordenG);
                strcpy(actual2->tipo,"Gold->Platino");
                puts("------------------------------");
                system("pause");
                return;
            }
            actual2 = actual2->sig;
        }
    }else{
        system("pause");
        return;
    }
    system("cls");
    puts("-----------------------------------------------");
    puts("¡No hay clientes Platinos ni Gold, ahora mismo!");
    puts("-----------------------------------------------");
    system("pause");
}

void atenderCliente(){

    long doc;

    printf("Ingrese el DNI del cliente a atender: ");
    scanf("%ld",&doc);

    struct Clientes *actual = Inicio;
    struct Clientes *anterior = NULL;

    while(actual!=NULL){
        if(actual->DNI==doc){
            system("cls");
            printf("\nAtendiendo al cliente: %s\n", actual->nombre);
            sleep(2);

            if (actual == Inicio) {
                Inicio = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }

            free(actual);
            system("cls");
            puts("¡Cliente atendido y eliminado de la cola!");
            puts("-----------------------------------------");
            system("pause");
            return;
        }
        anterior = actual;
        actual = actual->sig;
    }
    puts("--------------------------------------------------------");
    printf("Cliente con DNI '%ld' no encontrado en la cola.\n", doc);
    puts("--------------------------------------------------------");
    system("pause");
}

void modificarCliente(){
    long doc;
    char cat[10],serv[20];
    int VordenG = 0, VordenB = 0, VordenP = 0;
    int op, op2, op3;

    printf("Ingrese el DNI del cliente a atender: ");
    scanf("%ld",&doc);

    struct Clientes *actual = Inicio;
    struct Clientes *anterior = NULL;

    while(actual!=NULL){
        if(actual->DNI==doc){
            system("cls");

            printf("Ingrese el servicio que neccesita cambiar: \n");
            puts("1. Atención al Cliente\n2. Atención en Caja");
            puts("-----------------");
            printf("Elegir opción: ");
            scanf("%d",&op3);
            while(op3>2 || op3<1){
                puts("------------------------------------");
                puts("¡Opción no valida, intente de nuevo!");
                puts("------------------------------------");
                printf("Elegir opción: ");
                scanf("%d",&op3);
            }
            switch(op3){
                case 1:
                    strcpy(actual->servicio,"Atencion al Cliente");
                    puts("------------------------");
                    printf("Número de orden: ");
                    if(strcmp(actual->tipo,"Black")==0){
                        ordenB = ordenB + 1;
                        printf("BC0%d\n",ordenB);
                        VordenB = 1;
                    }else if(strcmp(actual->tipo,"Gold")==0){
                        ordenG = ordenG + 1;
                        printf("GC0%d\n",ordenG);
                        VordenG = 1;
                    }else if(strcmp(actual->tipo,"Platino")==0){
                        ordenP = ordenP + 1;
                        printf("PC0%d\n",ordenP);
                        VordenP = 1;
                    }
                    printf("Espere en la fila %s y será atendido\n",actual->tipo);
                    puts("------------------------");
                    system("pause");
                    break;
                case 2:
                    strcpy(actual->servicio,"Atencion en Caja");
                    puts("------------------------");
                    printf("Número de orden: ");
                    if(strcmp(actual->tipo,"Black")==0){
                        ordenB = ordenB + 1;
                        printf("BC0%d\n",ordenB);
                        VordenB = 1;
                    }else if(strcmp(actual->tipo,"Gold")==0){
                        ordenG = ordenG + 1;
                        printf("GC0%d\n",ordenG);
                        VordenG = 1;
                    }else if(strcmp(actual->tipo,"Platino")==0){
                        ordenP = ordenP + 1;
                        printf("PC0%d\n",ordenP);
                        VordenP = 1;
                    }
                    puts("--------------------------------------------");
                    printf("Espere en la fila %s y será atendido\n",cat);
                    puts("--------------------------------------------");
                    system("pause");
                    break;
            }
            if(VordenB==1){
                actual->ordenB = ordenB;
                actual->ordenG = -1;
                actual->ordenP = -1;
                VordenB = 0;
            }else if(VordenG == 1){
                actual->ordenB = -1;
                actual->ordenG = ordenG;
                actual->ordenP = -1;
                VordenG = 0;
            }else if(VordenP == 1){
                actual->ordenB = -1;
                actual->ordenG = -1;
                actual->ordenP = ordenP;
                VordenP = 0;
            }

            if (actual == Inicio) {
                Inicio = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }

            // Agrega al cliente al final de la cola
            if (Final != NULL) {
                Final->sig = actual;
                actual->sig = NULL;
                Final = actual;
            } else {
                // Si Final es NULL, estaba vacia
                Inicio = actual;
                Final = actual;
                actual->sig = NULL;
            }
            system("cls");
            puts("------------------------------");
            puts("¡Cliente modificado con éxito!");
            puts("------------------------------");
            system("pause");
            return;
        }
        anterior = actual;
        actual = actual->sig;
    }
    puts("--------------------------------------------------------");
    printf("Cliente con DNI '%ld' no encontrado en la cola.\n", doc);
    puts("--------------------------------------------------------");
    system("pause");
}

void Menu(){
    puts("Menú: \n");
    puts("1. Agregar Cliente");
    puts("2. Atender Cliente");
    puts("3. Modificar Cliente");
    puts("4. Ver todos los clientes");
    puts("5. Ver cola usuarios Black");
    puts("6. Ver cola usuarios Gold");
    puts("7. Ver cola usuarios Platino");
    puts("8. Salir del programa");
    puts("----------------------------");
    printf("Elegir opción: ");
}

int main()
{
    int op,op3;

    setlocale(LC_ALL, "");
    srand(time(NULL));

    do{
        system("cls");
        Menu();
        scanf("%d",&op);
        while(op>8 || op<1){
            puts("------------------------------------");
            puts("¡Opción no valida, intente de nuevo!");
            puts("------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&op);
        }
        switch(op){
            case 1:
                system("cls");
                agregarCliente();
                break;
            case 2:
                system("cls");
                atenderCliente();
                break;
            case 3:
                system("cls");
                modificarCliente();
                break;
            case 4:
                system("cls");
                verFila();
                break;
            case 5:
                system("cls");
                verColaBlack();
                break;
            case 6:
                system("cls");
                verColaGold();
                break;
            case 7:
                system("cls");
                verColaPlatino();
                break;
            case 8:
                system("cls");
                puts("¿Está seguro que desea salir?\n1.Si\n2.No");
                puts("-----------------");
                printf("Elegir opción: ");
                scanf("%d",&op3);
                while(op3>2 || op3<1){
                    puts("------------------------------------");
                    puts("¡Opción no valida, intente de nuevo!");
                    puts("------------------------------------");
                    printf("Elegir opción: ");
                    scanf("%d",&op3);
                }
                switch(op3){
                case 1:
                    system("cls");
                    puts("Saliendo del programa...");
                    sleep(2);
                    break;
                case 2:
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    op=1;
                    break;
                }
                break;
        }
    }while(op!=8);

    return 0;
}
