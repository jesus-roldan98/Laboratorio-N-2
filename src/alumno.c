/*********************************************************************************************************************
Copyright (c) 2025, Roldan Jesus Alejandro kechuroldanjesus@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file alumno.c
 ** @brief codigo fuente del módulo para la gestión de alumnos
 **/

/* === Headers files inclusions ==================================================================================== */

#include "alumno.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

struct alumno_s {
    char nombre[20];    //!< Nombre del alumno
    char apellido[20];  //!< apellido del alumno
    uint32_t documento; //!< documento del alumno
#ifdef USAR_MEMORIA_ESTATICA
    
    bool ocupado;     //!< indica si la instancia esta ocupada

#endif
};

/* === Private function declarations =============================================================================== */

static alumno_t CrearInstancia(void);

/*
* @brief
*
*@param campo estruct de apellido, nombre y documento
*@param valor el valor del parametro a analizar en este caso nombre o apellido
*@param buffer donde escribira el puntero
*@param disponibles espacio disponible en la cadena
*@return int devuelve un -1 si el espacio asignado es menor de los que se escribio en la cadena, sino devuelve la suma de todos los caracteres que ocupan espacio en la cadena
*/

static int SerializarCadena(char campo[], const char valor[], char buffer[], uint32_t disponibles);

/*
* @brief
*
*@param campo estruct de apellido, nombre y documento
*@param valor el valor del parametro a analizar en este caso documento
*@param buffer donde escribira el puntero
*@param disponibles espacio disponible en la cadena
*@return int devuelve un -1 si el espacio asignado es menor de los que se escribio en la cadena, sino devuelve la suma de todos los caracteres que ocupan espacio en la cadena
*/

static int SerializarDocumento(char campo[], uint32_t valor, char buffer[], uint32_t disponibles);

/* === Private variable definitions ================================================================================ */

#ifdef USAR_MEMORIA_ESTATICA

static struct alumno_s instancias [ALUMNO_MAX] = {0}; //!< Instancia de la estructura alumno_s

#endif
/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */
#ifdef USAR_MEMORIA_ESTATICA
alumno_t CrearInstancia(void) {
    alumno_t self = NULL;

    for (int i = 0; i < ALUMNO_MAX; i++) {
        if (!instancias[i].ocupado) {
            instancias[i].ocupado = true;
            self = &instancias[i];
            break;
        }
    }
    return self;

}
#endif

int SerializarCadena(char campo[], const char valor[], char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":\"%s\",", campo, valor);
}

int SerializarDocumento(char campo[], uint32_t valor, char buffer[], uint32_t disponibles) {
    return snprintf(buffer, disponibles, "\"%s\":\"%u\"}", campo, valor);
}
/* === Public function definitions ============================================================================== */

alumno_t AlumnoCrear(char * nombre, char * apellido, uint32_t dni) {

#ifdef USAR_MEMORIA_ESTATICA 
    alumno_t self = CrearInstancia();
#else 
    alumno_t self = malloc(sizeof(struct alumno_s));
#endif
    if (self != NULL) {
        self ->documento = dni;
        strncpy(self ->nombre, nombre, sizeof(self ->nombre) - 1);
        strncpy(self ->apellido, apellido, sizeof(self ->apellido) - 1);
    }

    return self;
}

int AlumnoSerializar(alumno_t self, char buffer[], uint32_t size) {
    int escritos;
    int resultado;

    buffer[0] = '{';
    buffer++;
    escritos = 1;
    resultado = SerializarCadena("nombre", self->nombre, buffer, size - escritos);
    if (resultado < 0 || resultado >= size - escritos) {
        return -1;
    }

    buffer = buffer + resultado;
    escritos = escritos + resultado;
    resultado = SerializarCadena("apellido", self->apellido, buffer, size - escritos);
    if (resultado < 0 || resultado >= size - escritos) {
        return -1;
    }

    buffer = buffer + resultado;
    escritos = escritos + resultado;
    resultado = SerializarDocumento("documento", self->documento, buffer, size-escritos);
    if (resultado < 0 || resultado >= size - escritos) {
        return -1;
    }
    escritos = escritos + resultado;
    return escritos;
}

/* === End of documentation ======================================================================================== */
