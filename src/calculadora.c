/*********************************************************************************************************************
Copyright (c) 2025, Roldan JesusAlejandro <kechuroldanjesus@gmail.com>

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

/** @file calculadora.c
 ** @brief Plantilla para la creación de archivos de código fuente en lenguaje C
 **/

/* === Headers files inclusions ==================================================================================== */

#include "calculadora.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/**
 * @brief Estructura interna para representar una operación matemática.
 */

typedef struct operacion_s * operacion_t; 

struct operacion_s {
    char operador;            /**< Símbolo que representa la operación, por ejemplo '+', '-' o '*'. */
    operacion_func_t funcion; /**< Función que implementa la operación. */
    operacion_t siguiente;     /**< Puntero a la siguiente operación en la lista. */
};

struct calculadora_s {
    operacion_t operaciones; //<! lista de operaciones
};

/* === Private function declarations =============================================================================== */

/**
 * @brief Busca una operación registrada en la calculadora por su símbolo.
 *
 * @param calculadora Puntero a la calculadora.
 * @param operador Símbolo de la operación a buscar.
 * @return Puntero a la operación encontrada, o NULL si no existe.
 */

static operacion_t EncontrarOperacion(calculadora_t calculadora, char operador);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static operacion_t EncontrarOperacion(calculadora_t calculadora, char operador) {
    operacion_t actual = calculadora->operaciones;
    while (actual != NULL) {
        if (actual->operador == operador) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

/* === Public function implementation ============================================================================== */

/**
 * @brief Crea una nueva instancia de calculadora.
 *
 * @return Un puntero a la nueva calculadora o NULL si no se pudo asignar memoria.
 */

calculadora_t CalculadoraCrear(void) {
    calculadora_t nueva_calculadora = malloc(sizeof(struct calculadora_s));
    if (nueva_calculadora) {
        nueva_calculadora->operaciones = NULL;
    }

    return nueva_calculadora;
}


/**
 * @brief Agrega una nueva operación a la calculadora.
 *
 * No se permite registrar dos operaciones con el mismo símbolo.
 *
 * @param calculator Calculadora a la que se agregará la operación.
 * @param sumador Carácter que representa el operador (por ejemplo '+').
 * @param funcion Puntero a la función que implementa la operación.
 * @return true si la operación se agregó correctamente, false si ya existía o hubo error.
 */

bool CalculadoraAddOperacion(calculadora_t calculator, char sumador, operacion_func_t funcion) {
    if (!calculator || !funcion || EncontrarOperacion(calculator, sumador)) {
        return false;
    }

    operacion_t operacion = malloc(sizeof(struct operacion_s));
    if (operacion) {

        operacion->operador = sumador;
        operacion->funcion = funcion;
        operacion->siguiente = calculator->operaciones;
        calculator->operaciones = operacion;
        return true;
    }

    return false;
}


/**
 * @brief Evalúa una expresión en formato "a operador b".
 *
 * La función analiza la expresión, extrae los operandos y el operador, y ejecuta la operación correspondiente
 * registrada previamente en la calculadora.
 *
 * @param calculator Calculadora con operaciones registradas.
 * @param expresion Cadena de texto con la expresión a evaluar (por ejemplo "3+5").
 * @return Resultado de la operación, o 0 si hay error o no se encuentra el operador.
 */

int CalculadoraCalcula(calculadora_t calculator, const char * expresion) {
    int a = 0, b = 0;
    char operador = 0;
    int resultado = 0;

    if (!calculator || !expresion) {
        return 0; // Error: calculadora o expresión nula
    }

    for (int i = 0; i < strlen(expresion); i++) {
        if ((expresion[i] < '0') || (expresion[i] > '9')) {
        operador = expresion[i];
        a = atoi(expresion);
        b = atoi(expresion + i + 1);
        break;
        }
    }

    operacion_t operacion = EncontrarOperacion(calculator, operador);
    if (operacion) {
        resultado = operacion->funcion(a, b);
    }

    return resultado;
}


/**
 * @brief Implementa la operación de suma.
 *
 * @param a Primer operando.
 * @param b Segundo operando.
 * @return Resultado de a + b.
 */

int OperacionAdd(int a, int b) {
    return a + b;
}


/**
 * @brief Implementa la operación de resta.
 *
 * @param a Primer operando.
 * @param b Segundo operando.
 * @return Resultado de a - b.
 */

int OperacionSub(int a, int b) {
    return a - b;
}

/**
 * @brief Implementa la operación de multiplicación.
 *
 * @param a Primer operando.
 * @param b Segundo operando.
 * @return Resultado de a * b.
 */

int OperacionMul(int a, int b) {
    return a * b;
}

/**
 * @brief Implementa la operación de división.
 *
 * Maneja el caso de división por cero imprimiendo un mensaje de error.
 *
 * @param a Dividendo.
 * @param b Divisor.
 * @return Resultado de a / b. Si b es 0, se imprime un error y se retorna 0.
 */
int OperacionDiv(int a, int b) {
    if (b == 0) {
       printf ("error divison por cero/n");// Comportamiento indefinido si se intenta dividir por cero
        return 0; // O se podría manejar de otra forma, como lanzar un error
    }
    return a / b;
}

/* === End of documentation ======================================================================================== */
