
/* INTEGRANTES DEL GRUPO 1TUP10: */
/* Diez, Paula */
/* Fabi, Victoria */
/* Creamos un archivo txt, para guardar la base de datos de clientes.
   Utilizamos Struct,funciones,busqueda secuencial,estructuras while y do-while,estructuras If y Switch. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------//
//----------------TIPOS DE DATOS DECLARADOS POR EL PROGRAMADOR--------------------//
//--------------------------------------------------------------------------------//

struct Cliente // la información que voy a almacenar en el vector (relleno)
{
    int numCuenta;
    int clave;
    float saldo;
    int estado; // 0 para Activo, 1 para Bloqueado
    char nombre[100];
};

//--------------------------------------------------------------------------------//
//----------------PROTOTIPOS DE FUNCIONES-----------------------------------------//
//--------------------------------------------------------------------------------//
void iniciarSesion(struct Cliente clientes[]);
void cargarVector(struct Cliente clientes[]);
int BuscarEnVector(struct Cliente clientes[], int numCuentaIngresado, int clave);

int BuscarCuentaDestinoEnVector(struct Cliente clientes[], int numCuentaIngresado);
int MenuPrincipal();
void operaciones(struct Cliente clientes[], int pos);
//--------------------------------------------------------------------------------//
//----------------PROGRAMA PRINCIPAL----------------------------------------------//
//--------------------------------------------------------------------------------//
int main()
{
    struct Cliente clientes[10]; //  arreglo de 10 clientes y en cada posición hay un struct Cliente
    int opcion;

    //  cargar en total 10 clientes inventados subproceso funcion-
    cargarVector(clientes);
    opcion = MenuPrincipal();
    while (opcion != 2)
    {
        iniciarSesion(clientes);
        opcion = MenuPrincipal();
    }

    return 0;
}

//-----------------------------------------------------------------------------------------------//
int MenuPrincipal() // la función  devuelve un nro entero (int)
{
    int opcion;

    do
    {   
        printf("\nBienvenido a Camel Bank.\n");
        printf("--------------------------\n");
        printf("MENU PRINCIPAL\n");
        printf("--------------\n");
        printf("1- Inicio de sesion\n");
        printf("2- Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        if (opcion != 1 && opcion != 2)
        {
            printf("\nError! Debe ser 1 o 2\n");
        }
    } while (opcion != 1 && opcion != 2);

    // la función devuelve la opcion elegida
    return opcion;
}
//------------------------------------------------------------------------------------------------//
void iniciarSesion(struct Cliente clientes[])
{
    int numCuentaIngresado;
    int clave;
    int pos;
    int intentos = 0;

    do
    {
        printf("...............................................................\n");
        printf("\nIngrese su N%cmero de Cuenta :", 163);
        scanf("%d", &numCuentaIngresado);

        printf("Ingrese su Clave: ");
        scanf("%d", &clave);

        intentos = intentos + 1;
        pos = BuscarEnVector(clientes, numCuentaIngresado, clave);
        if (pos == -1)
        {
            printf("\nNumero de Cuenta o Password incorrecta..\n");
        }
    } while (pos == -1 && intentos < 3);

    if (intentos == 3)
    {
        printf("\nNo se permiten mas intentos. Su cuenta ha sido bloqueada; comun%cquese con la Entidad Bancaria.\n", 161);
        clientes[pos].estado = 1;
    }
    else
    {
        if (clientes[pos].estado == 1)
        {
            printf("\nSu cuenta est%c bloqueada; comuniquese con la Entidad Bancaria.\n", 160);
        }
        else
        {
            operaciones(clientes, pos);
        }
    }
}

void operaciones(struct Cliente clientes[], int pos)
{
    int opcion;
    float monto;
    int numCuentaDestino;
    int posDestino;
    int contOperaciones = 0;

    do
    {
        printf("...............................................................\n");
        printf("\nMen%c:\n", 163);
        printf("...............................................................\n");
        printf("1. Realizar un Dep%csito.\n", 162);
        printf("2. Realizar una Extracci%cn.\n", 162);
        printf("3. Consultar el Saldo de la Cuenta.\n");
        printf("4. Realizar una Transferencia entre Cuentas.\n");
        printf("5. Mostrar cantidad de Operaciones Realizadas y Saldo Actual.\n");
        printf("6. Salir de la Sesi%cn.\n", 162);
        printf("...............................................................\n");
        printf("Seleccione una opci%cn: ", 162);
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            // Realizar un Depósito

            printf("Ingrese el monto a depositar: ");
            scanf("%f", &monto);
            printf("...............................................................\n");
            if (monto > 0)
            {
                clientes[pos].saldo += monto;
                printf("Dep%csito exitoso.\n", 162);
                printf("Su Nuevo Saldo es: %.2f\n", clientes[pos].saldo);
            }
            else
            {
                printf("Monto de dep%csito no v%clido.\n", 162, 160);
            }
            contOperaciones++;
            break;

        case 2:
            // Realizar una Extracción

            printf("Ingrese el monto a extraer: ");
            scanf("%f", &monto);

            if (monto > 0 && monto <= clientes[pos].saldo)
            {
                clientes[pos].saldo -= monto;
                printf("Extracci%cn exitosa.\n", 162);
                printf("Su nuevo saldo es : %.2f\n", clientes[pos].saldo);
            }
            else
            {
                printf("Monto de extracci%cn no v%clido o saldo insuficiente.\n", 162, 160);
            }
            contOperaciones++;
            break;

        case 3:
            // Consultar el Saldo de la Cuenta
            printf("Su saldo actual es: %.2f\n", clientes[pos].saldo);
            contOperaciones++;
            break;

        case 4:
            // Realizar una Transferencia entre Cuentas

            printf("Ingrese el n%cmero de cuenta de destino: ", 163);
            scanf("%d", &numCuentaDestino);

            // Validar que el número de cuenta de destino sea válido
            posDestino = BuscarCuentaDestinoEnVector(clientes, numCuentaDestino);
            if (posDestino == -1)
            {
                printf("\nCuenta Inexistente.\n");
            }
            else
            {
                // Validar que el monto de transferencia sea válido
                do
                {
                    printf("Ingrese el monto a transferir: ");
                    scanf("%f", &monto);
                    if (monto <= 0)
                    {
                        printf("\nDebe ingresar un valor mayor a cero.\n");
                    }
                } while (monto <= 0);

                //  validar que el cliente tenga saldo suficiente
                if (monto <= clientes[pos].saldo)
                {
                    // Actualizar los saldos de ambas cuentas
                    clientes[pos].saldo -= monto;
                    clientes[posDestino].saldo += monto;
                    printf("\nTransferencia exitosa.\n");
                    printf("Su nuevo saldo: %.2f\n", clientes[pos].saldo);
                }
            }
            contOperaciones++;
            break;

        case 5:
            // Mostrar cantidad de Operaciones Realizadas y Saldo Actual
            printf("Cantidad de operaciones realizadas : %d\n", contOperaciones);
            printf("Saldo Actual : %.2f\n", clientes[pos].saldo);

            break;
        }
    } while (opcion != 6 && contOperaciones < 10);
    if (contOperaciones == 10)
    {
        printf("Ha alcanzado el l%cmite de operaciones. Para continuar,  debe iniciar sesión nuevamente.\n", 161);
    }
}
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
void cargarVector(struct Cliente clientes[])
{
    int i = 0;
    FILE *archTXT = fopen("clientes.txt", "rt");
    if (archTXT == NULL)
    {
        printf("Error! No existe el archivo.\n");
    }
    else
    {
        while (fscanf(archTXT, "%d,%d,%f,%d,%s\n", &clientes[i].numCuenta, &clientes[i].clave, &clientes[i].saldo, &clientes[i].estado, &clientes[i].nombre) != EOF)
        {
            i++;
        }
        fclose(archTXT);
    }
}

//-----------------------------------------------------------------------------------------------//
// La función busca en el vector clientes (BÚSQUEDA SECUENCIAL)
// EN DONDE BUSCO: en el vector clientes
// LO QUE BUSCO: busco al numCuentaIngresado y la clave
// QUE DEVUELVE LA FUNCION = -1 si no lo encontró o el "i" en donde lo encontró

int BuscarEnVector(struct Cliente clientes[], int numCuentaIngresado, int clave)
{
    int pos;
    int i;

    pos = -1;
    i = 0;
    while (i < 10 && pos == -1)
    {
        if (numCuentaIngresado == clientes[i].numCuenta && clave == clientes[i].clave)
        {
            pos = i;
        }
        else
        {
            i = i + 1;
        }
    }
    return pos;
}

//------------------------------------------------------------------------------------//
int BuscarCuentaDestinoEnVector(struct Cliente clientes[], int numCuentaIngresado)
{
    int pos;
    int i;

    pos = -1;
    i = 0;
    while (i < 10 && pos == -1)
    {
        if (numCuentaIngresado == clientes[i].numCuenta)
        {
            pos = i;
        }
        else
        {
            i = i + 1;
        }
    }
    return pos;
}