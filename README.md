# get_next_line_42

## Enunciado
![captura del enunciado](https://github.com/user-attachments/assets/87806891-6a2f-4cc0-b496-a12d93e311c3)
* Llamar a tu función get_next_line de manera repetida (por ejemplo, usando un
bucle) te permitirá leer el contenido del archivo hacia el que apunta el file descriptor,
línea a línea, hasta el final.
* Tu función deberá devolver la línea que se acaba de leer.
Si no hay nada más que leer o si ha ocurrido un error, deberá devolver NULL.
* Asegúrate de que tu función se comporta adecuadamente cuando lea de un archivo
y cuando lea de stdin.
* Ten en cuenta que la línea devuelta debe terminar con el caracter
n, excepto si se ha llegado al final del archivo y esté no termina con un caracter
n.
* En el header get_next_line.h deberás tener como mínimo el prototipo de la fun-
ción get_next_line.
* Añade todas las funciones de ayuda que necesites en el archivo get_next_line_utils.c
## Conceptos Clave
## Variables estáticas

<aside>
🪶

Las variables estáticas son variables que conservan su valor entre diferentes llamadas a una función o durante la vida del programa, dependiendo del contexto en el que se declaren.

</aside>

- **Alcance**: Una variable estática declarada dentro de una función tiene un alcance local, pero su valor persiste entre llamadas a la función. Una variable estática declarada fuera de cualquier función tiene un alcance global.
- **Duración**: Las variables estáticas se inician solo una vez y su duración abarca todo el tiempo de ejecución del programa.
- **Uso común**: Se utilizan para mantener el estado entre llamadas a funciones o para datos que deben ser compartidos entre funciones en un archivo, pero no necesitan ser accesibles desde otros archivos.

Una variable estática dentro de una función mantiene su valor entre llamadas a la función. Al contrario de las variables locales normales, que se crean y destruyen cada vez que la función se llama, las variables estáticas se inicializan solo una vez y persisten durante toda la ejecución del programa.
```Ejemplo:
#include <stdio.h>

void contador() {
    static int count = 0; // Variable estática
    count++;
    printf("Contador: %d\n", count);
}

int main() {
    contador(); // Output: Contador: 1
    contador(); // Output: Contador: 2
    contador(); // Output: Contador: 3
    return 0;
}
/*_En este ejemplo, la variable count es una variable estática 
dentro de la función contador. Su valor se incrementa en cada 
llamada a la función y se conserva entre llamadas, en lugar 
de reiniciarse a 0 cada vez._*/```
