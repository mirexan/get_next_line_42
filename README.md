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
### Variables estáticas

<aside>

**Las variables estáticas son variables que conservan su valor entre diferentes llamadas a una función o durante la vida del programa, dependiendo del contexto en el que se declaren.**

</aside>

- **Alcance**: Una variable estática declarada dentro de una función tiene un alcance local, pero su valor persiste entre llamadas a la función. Una variable estática declarada fuera de cualquier función tiene un alcance global.
- **Duración**: Las variables estáticas se inician solo una vez y su duración abarca todo el tiempo de ejecución del programa.
- **Uso común**: Se utilizan para mantener el estado entre llamadas a funciones o para datos que deben ser compartidos entre funciones en un archivo, pero no necesitan ser accesibles desde otros archivos.

Una variable estática dentro de una función mantiene su valor entre llamadas a la función. Al contrario de las variables locales normales, que se crean y destruyen cada vez que la función se llama, las variables estáticas se inicializan solo una vez y persisten durante toda la ejecución del programa.
```
Ejemplo:
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
de reiniciarse a 0 cada vez._*/
```
### FileDescriptor

<aside>

**FD :Es un número entero no negativo que se utiliza para acceder a archivos o recursos de entrada/salida (I/O).**

</aside>

- **Asignación**: Cuando un proceso abre un archivo o crea un nuevo socket, el sistema operativo le asigna un file descriptor. Este descriptor se utiliza para referenciar el recurso abierto en futuras operaciones.
- **Valores comunes**: Los tres primeros file descriptors que se asignan por defecto son:
    - `0`: stdin (entrada estándar)
    - `1`: stdout (salida estándar)
    - `2`: stderr (error estándar)
- **Operaciones**: Los file descriptors se utilizan en varias llamadas al sistema para realizar operaciones como lectura (`read`), escritura (`write`), cierre (`close`), entre otras.
- **Manejo de recursos**: Los file descriptors permiten que el sistema operativo gestione de manera eficiente los recursos de I/O, asegurándose de que no haya conflictos entre diferentes procesos que intentan acceder al mismo recurso.
- **Herencia**: Cuando se crea un nuevo proceso (por ejemplo, mediante `fork`), los file descriptors abiertos en el proceso padre son heredados por el proceso hijo.
    - **Consideraciones**:
        - **Cierre de file descriptors**: Es importante que los procesos cierren los file descriptors que ya no necesitan, especialmente en el proceso hijo, para evitar fugas de recursos.
        - **Redirección**: El proceso hijo puede redirigir sus file descriptors antes de ejecutar un nuevo programa con `exec()`. Esto permite que el nuevo programa utilice diferentes fuentes de entrada y salida sin necesidad de conocer los detalles de redirección.

### Open

> **Se utiliza para abrir archivos. Devuelve un valor de asignación al archivo abierto, es el file descriptor (fd).**

Libreria: `#include <fcntl.h>`

```c
 sintaxis:
 int open(const char *ruta, int flags, mode_tmode);
 manual: 
 man 2 open 
```

- `ruta`: Es la ruta al archivo que se desea abrir, puede ser un argumento vector.
- `flags`: Especifica el modo de apertura del archivo (por ejemplo, lectura, escritura, etc.). Algunos valores comunes son:
    - `O_RDONLY`: Abre el archivo en modo solo lectura.
    - `O_WRONLY`: Abre el archivo en modo solo escritura.
    - `O_RDWR`: Abre el archivo en modo lectura y escritura.
    - `O_CREAT`: Crea el archivo si no existe (requiere un tercer argumento `mode`).
- `mode`: (Opcional) Especifica los permisos del archivo si se crea (se usa con `O_CREAT`).


**Pd: Requiere que se realice al final la función close.**

```c
sintaxis:
int close(fd);
```

### Read

> **La función read sirve para leer datos de un archivo abierto, devuelve los bytes leídos.**
Libreria : `#include <unistd.h>`

```c
sintaxis:
ssize_t read(int fd, void *buf, size_t count);
```

- `fd`: Es el descriptor de archivo (devuelto por `open`).
- `buf`: Es un puntero al buffer donde se almacenarán los datos leídos.
- `count`: Es el número máximo de bytes a leer. (puede ser el buffer_size)

