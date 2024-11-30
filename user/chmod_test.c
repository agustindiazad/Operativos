#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(void) {
    int fd;

    printf("Prueba: Crear archivo 'testfile' con permisos de lectura/escritura\n");
    fd = open("testfile", O_CREATE | O_RDWR);
    if (fd < 0) {
        printf("Error: No se pudo crear el archivo\n");
        exit(1);
    }
    printf("Archivo 'testfile' creado exitosamente\n");

    printf("Prueba: Escribir datos iniciales en 'testfile'\n");
    if (write(fd, "Datos iniciales", 15) != 15) {
        printf("Error: No se pudo escribir en el archivo\n");
        close(fd);
        exit(1);
    }
    printf("Escritura inicial completada exitosamente\n");
    close(fd);

    printf("Prueba: Cambiar permisos de 'testfile' a solo lectura\n");
    if (chmod("testfile", 1) < 0) {
        printf("Error: Fallo al cambiar permisos a solo lectura\n");
        exit(1);
    }
    printf("Permisos cambiados a solo lectura\n");

    printf("Prueba: Intentar escribir en 'testfile' (debería fallar)\n");
    fd = open("testfile", O_WRONLY);
    if (fd >= 0) {
        printf("Error: Archivo se abrió en modo escritura con permisos de solo lectura\n");
        close(fd);
        exit(1);
    }
    printf("Escritura bloqueada correctamente (como se esperaba)\n");

    printf("Prueba: Restaurar permisos de 'testfile' a lectura/escritura\n");
    if (chmod("testfile", 3) < 0) {
        printf("Error: Fallo al restaurar permisos a lectura/escritura\n");
        exit(1);
    }
    printf("Permisos restaurados a lectura/escritura\n");

    printf("Prueba: Escribir datos finales en 'testfile'\n");
    fd = open("testfile", O_RDWR);
    if (fd < 0 || write(fd, "Datos finales", 13) != 13) {
        printf("Error: Fallo al escribir datos finales\n");
        close(fd);
        exit(1);
    }
    printf("Escritura final completada exitosamente\n");
    close(fd);

    printf("Prueba: Cambiar permisos de 'testfile' a inmutable\n");
    if (chmod("testfile", 5) < 0) {
        printf("Error: Fallo al marcar archivo como inmutable\n");
        exit(1);
    }
    printf("Archivo marcado como inmutable\n");

    printf("Prueba: Intentar cambiar permisos de 'testfile' después de ser inmutable (debería fallar)\n");
    if (chmod("testfile", 3) == 0) {
        printf("Error: Permisos cambiados incorrectamente en un archivo inmutable\n");
        exit(1);
    }
    printf("Permisos bloqueados correctamente para archivo inmutable\n");

    printf("Pruebas completadas exitosamente\n");
    exit(0);
}
