/*********************************************************************************************************************
Copyright (c) 2025, Roldan Jesus Alejandro kechuroldanjesus@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/


/** @file calculadora.h
 ** @brief Interfaz pública para una calculadora extensible mediante funciones de operación.
 **
 ** Este archivo define el tipo de datos `calculadora_t`, un objeto que representa una calculadora a la cual
 ** se le pueden agregar operaciones aritméticas y realizar cálculos a partir de expresiones en formato "número operador número",
 ** como por ejemplo `"5+4"`, `"7*3"` o `"10-8"`.
 **
 ** La implementación sigue el patrón estrategia, permitiendo extender fácilmente con nuevas operaciones.
 **/

#ifndef CALCULADORA_H_
#define CALCULADORA_H_

/** @file calculadora.h
 ** @brief Plantilla para la creación de archivos de de cabeceras en lenguaje C
 **/

/* === Headers files inclusions ====================================================================================*/

#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions ===================================================================================*/

/* === Public data type declarations===============================================================================*/


typedef struct calculadora_s * calculadora_t; //<! tipo de dato para el objeto calculadora

typedef int (*operacion_func_t)(int, int); //<! tipo de dato para las funciones de operaciones

/* === Public variable declarations ================================================================================*/

/* === Public function declarations ================================================================================*/

/**
 * @brief Crea un nuevo objeto calculadora.
 *
 * @return Objeto calculadora válido o NULL en caso de error.
 */

calculadora_t CalculadoraCrear(void);

/**
 * @brief Agrega una nueva operación a la calculadora.
 *
 * @param calculator Objeto calculadora al que se le agregará la operación.
 * @param operador Carácter que representa la operación (por ejemplo '+', '-', '*').
 * @param funcion Función que implementa la operación.
 * @return true si la operación fue agregada con éxito, false en caso contrario (ya existe o error).
 */

bool CalculadoraAddOperacion(calculadora_t calculator, char sumador, operacion_func_t funcion);

/**
 * @brief Evalúa una expresión matemática simple (como "3+5").
 *
 * @param calculator Objeto calculadora con las operaciones definidas.
 * @param expresion Cadena con la expresión a evaluar (debe tener formato válido).
 * @return Resultado del cálculo. Si hay error, devuelve 0.
 */

int CalculadoraCalcula(calculadora_t calculator, const char * expresion);

/**
 * @brief Función para realizar una suma.
 *
 * @param a Primer sumando.
 * @param b Segundo sumando.
 * @return Resultado de a + b.
 */

int OperacionAdd (int a, int b);

/**
 * @brief Función para realizar una resta.
 *
 * @param a Minuendo.
 * @param b Sustraendo.
 * @return Resultado de a - b.
 */

int OperacionSub (int a, int b);


/**
 * @brief Función para realizar una multiplicación.
 *
 * @param a Primer factor.
 * @param b Segundo factor.
 * @return Resultado de a * b.
 */

int OperacionMul (int a, int b);

/**
 * @brief Función para realizar una división.
 *
 * @param a Dividendo.
 * @param b Divisor.
 * @return Resultado de a / b. Si b es 0, el comportamiento es indefinido.
 */

int OperacionDiv (int a, int b);

/* === End of conditional blocks ===================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* CALCULADORA_H_ */
