# MiniKernel - Schedulers

El proyecto es una simulacion de un SO basico escrito en C, implementando un planificador de procesos (*Round Robin*)
y gestion de concurrencia mediante hilos POSIX (`pthreads`) y exclusion mutua (`mutex`)

**Institucion:** Escuela Politecnica Nacional
**Autor:** Astudillo Josue

## Caracteristicas 

* **Cola de Procesos Listos(ready_queue):**Estructura de datos circular que ayuda a prevenir fugas de memoria

* **Control Concurrencia:**Sincronizacion mediante `pthread_mutex_lock` y`pthread_mutex_unlock` para garantizar de forma segura el acceso a memoria compartida

* **Round Robin:**Planificacion equitativa de CPU mediante *Quantum* fijo y *Context_Switch* 

* **Monito de Rendimiento:**Hilo que reporta metricas del scheduler(*Throghput* y *Tiempo de respuesta*) en los 10 segundos definidos

* **Pruebas Unitarias:**Entorno de prueba unitaria implementado con la biblioteca `assert.h`
para validar la integridad de la CC

## Estructura del Proyecto

```
MiniKernel/
├── include/  # Archivos de cabecera (.h) con definiciones de estructuras
├── src/      # Código fuente principal (.c)
├── test/     # Pruebas unitaria de código (ColaCircular)
├── Makefile  # Automatización 
└── README.md # Documentación