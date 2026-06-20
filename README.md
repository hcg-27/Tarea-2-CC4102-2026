# Tarea 2: Árboles AVL vs Splay Trees

**Alumnos**:
- Hernán Cisternas García
- Lya Díaz
- Tomás León

## Requisitos

> [!IMPORTANT]
> Esta tarea a sido probada en Fedora 43 (Workstation edition) y Ubuntu 22.04.5 LTS, en donde todo el software requerido viene instalado por default. Si usa Windows, o no cumple los requisitos en Ubuntu o Fedora, tendra que seguir las instrucción de la sección **Instalación de Software Requerido**

- GCC (>=13)
- make
- bash

## Instrucciones

> [!WARNING]
> Si usa Windows debe ejecutar los comandos en la consola *MSYS2 UCRT64*

Ejecute las siguientes instrucciones en el directorio donde se encuentra el Makefile

1. Verificar requisitos
```bash
make check
```

2. Preparar directorios
```bash
make setup
```

3. Compilar los ejecutables
```bash
make build
```

4. Ejecutar los experimentos
```bash
make run_all
``` 

5. Ayuda
```bash
make help
```


## Formato del output


## Instalación de Software Requerido

### Windows

Para ejecutar la tarea en Windows existen dos posibilidades WSL y MSYS2+MinGW. Esta tarea solo fue probada con MSYS2+MingW.

1. Siga los pasos 1-4 del siguiente link: [Instalación de MSYS2](https://www.msys2.org/)
2. En la consola de **MSYS2 UCRT64**, ejecute lo siguiente:
```bash
# Actualizar repositorios
pacman -Syu
# Instalar el toolchain de GCC (g++, make, etc)
pacman -S --needed mingw-w64-ucrt-x86_64-toolchain
```

### Ubuntu

```bash
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-14 g++-14 -y
```

### Fedora

```bash
sudo dnf install gcc14 gcc14-c++ -y
```
