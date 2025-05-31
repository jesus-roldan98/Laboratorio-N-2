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

/** @file mainn.c
 ** @brief codigo fuente principal del proyecto
 **/

/* === Headers files inclusions ==================================================================================== */

#include "alumno.h"
#include <stdio.h>
#include <calculadora.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */

/**
 * @brief Función principal del programa.
 *
 * Se crea una instancia de calculadora, se registran las operaciones básicas (+, -, *) y luego
 * se evalúan tres expresiones aritméticas como ejemplo.
 *
 * @return 0 al finalizar correctamente.
 */

int main(void) {
    // Expresiones a evaluar
    static const char suma [] = "22+33";
    static const char resta [] = "5+4";
    static const char multiplicacion [] = "2*1";
    static const char division [] = "10/2"; 
     // Variable para almacenar los resultados (no necesaria si solo se imprime)
    int resultado;

    // Crear la calculadora
    calculadora_t calculadora = CalculadoraCrear();
    CalculadoraAddOperacion(calculadora, '+', OperacionAdd);
    CalculadoraAddOperacion(calculadora, '-', OperacionSub);
    CalculadoraAddOperacion(calculadora, '*', OperacionMul);
    CalculadoraAddOperacion(calculadora, '/', OperacionDiv);

    // Evaluar expresiones y mostrar resultados

    printf ("Resultado de la suma: %d\n", CalculadoraCalcula(calculadora, suma));
    printf ("Resultado de la resta: %d\n", CalculadoraCalcula(calculadora, resta));
    printf ("Resultado de la multiplicacion: %d\n", CalculadoraCalcula(calculadora, multiplicacion));
    printf ("Resultado de la division: %d\n", CalculadoraCalcula(calculadora, division));
    
    return 0;

}
/* === End of documentation ======================================================================================== */
