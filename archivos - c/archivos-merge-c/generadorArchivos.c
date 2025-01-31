#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"
#include <string.h>

void genrarArchivos()
{
    FILE* arcProd;
    FILE* arcMov;

    PRODUCTO productos[] = {
        {"BAN","Banana",150.90,80},
        {"MAN","Manzana",150.90,80},
        {"NAR","Naranja",150.90,80},
        {"PER","Pera",150.90,80},
        {"ZAN","Zandia",150.90,80}

    };

    MOVIMIENTO movimientos[] = {
        {"BAN",90},
        {"MAN",-10},
        {"MAN",-30},
        {"NAR",40},
        {"PER",-10},


    };



    //printf("\nCE: %d",sizeof(productos));

    arcProd =fopen("Productos.dat","wb");


    fwrite(productos,sizeof(PRODUCTO),sizeof(productos)/sizeof(PRODUCTO),arcProd);


    fclose(arcProd);


    arcMov = fopen("Movimientos.dat","wb");


    fwrite(movimientos,sizeof(MOVIMIENTO),sizeof(movimientos)/sizeof(MOVIMIENTO),arcMov);


    fclose(arcMov);
}

void mostrarArchivos()
{
    FILE* arcProd;
    FILE* arcMov;

    PRODUCTO prodLeido;
    MOVIMIENTO movLeido;


    //LEO Y IMPRIMO PRODUCTOS
    arcProd =fopen("Productos.dat","rb");

    if(arcProd==NULL)
    {
        printf("\nNo se pudo leer archivo producto");
        exit(1);
    }

    fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);
    printf("\n=============================");
    printf("\n ARCHIVO PRODUCTOS:");
    while(!feof(arcProd))
    {

        printf("\n%s  -  %s  -  %2.f  -  %d",prodLeido.cod,prodLeido.descripcion,prodLeido.precio,prodLeido.cant);
        fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);



    }
    printf("\n=============================");


    fclose(arcProd);


    //LEO Y IMPRIMO MOVIMIENTOS
    arcMov =fopen("Movimientos.dat","rb");

    if(arcMov==NULL)
    {
        printf("\nNo se pudo leer archivo movimientos");
        exit(1);
    }

    fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);
    printf("\n=============================");
    printf("\n ARCHIVO PRODUCTOS:");
    //printf("\n%s  -   %d",movLeido.cod,movLeido.cant);
    while(!feof(arcMov))
    {

        printf("\n%s  -   %d",movLeido.cod,movLeido.cant);
        fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);

    }
    printf("\n=============================");


    fclose(arcMov);




}


void mostrarArchivoTMP(){

    FILE* arcTmp;

    PRODUCTO prodLeido;


    //LEO Y IMPRIMO PRODUCTOS
    arcTmp =fopen("temporario.tmp","rb");

    if(arcTmp==NULL)
    {
        printf("\nNo se pudo leer archivo producto");
        exit(1);
    }

    fread(&prodLeido,sizeof(PRODUCTO),1,arcTmp);
    printf("\n=============================");
    printf("\n ARCHIVO PRODUCTOS:");
    while(!feof(arcTmp))
    {

        printf("\n%s  -  %s  -  %.2f  -  %d",prodLeido.cod,prodLeido.descripcion,prodLeido.precio,prodLeido.cant);
        fread(&prodLeido,sizeof(PRODUCTO),1,arcTmp);



    }
    printf("\n=============================");


    fclose(arcTmp);


}

void mergeAlgoritmo1(char* prod,char* mov)
{
    FILE* arcProd;
    FILE* arcMov;
    FILE* tmpProd;

    PRODUCTO prodLeido={"","",0,0}, prodNuevo;
    MOVIMIENTO movLeido;

    int comp;


    arcProd =fopen(prod,"rb");
    arcMov =fopen(mov,"rb");
    tmpProd = fopen("temporario.tmp","wb");

    if(arcProd==NULL || arcMov==NULL)
    {
        printf("\nNo Leer alguno de los archivos");
        exit(1);
    }


    //COMIENZO DE LA ITERACIÓN SOBRE LOS ARCHIVOS
    fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);
    fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);



    while(!feof(arcMov) && !feof(arcProd))
    {
        comp = strcmp(prodLeido.cod,movLeido.cod);
        //printf("\nresult comp: %d",comp);

        if(comp<0){

            strcpy(prodNuevo.cod,prodLeido.cod);
            strcpy(prodNuevo.descripcion,prodLeido.descripcion);
            prodNuevo.cant= prodLeido.cant;
            prodNuevo.precio = prodLeido.precio;
            fwrite(&prodNuevo,sizeof(PRODUCTO),1,tmpProd);
            fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);

        }

        if(comp==0){
            //printf("\n COINCIDENCIA DE CODIGOS");
            prodLeido.cant+=movLeido.cant;
            if(prodLeido.cant<0) prodLeido.cant = 0;
            fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);
        }

        if(comp>0){
            prodLeido.cant=0;
            fread(&movLeido,sizeof(MOVIMIENTO),1,arcMov);


        }



    }



    while(!feof(arcProd)){

        strcpy(prodNuevo.cod,prodLeido.cod);
        strcpy(prodNuevo.descripcion,prodLeido.descripcion);
        prodNuevo.cant= prodLeido.cant;
        prodNuevo.precio = prodLeido.precio;
        fwrite(&prodNuevo,sizeof(PRODUCTO),1,tmpProd);
        fread(&prodLeido,sizeof(PRODUCTO),1,arcProd);
    }



    fclose(arcProd);
    fclose(arcMov);
    fclose(tmpProd);


    remove(prod);
    rename("temporario.tmp",prod);


}
