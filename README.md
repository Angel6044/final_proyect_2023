# 💧 Sistema de Gestión de Toma de Estado y Facturación de Medidores de Agua

Proyecto desarrollado en **Lenguaje C**, orientado a la optimización del proceso de toma de estado, facturación y gestión de usuarios en una empresa proveedora de agua potable.

---

## 🏗️ Escenario del proyecto

La empresa encargada de la **potabilización y distribución de agua potable** enfrenta problemas debido a la **duplicación de tareas** y errores al registrar manualmente los datos de consumo. Para solucionarlo, se desarrolló un software capaz de:

- Generar archivos CSV con rutas e información de medidores para dispositivos móviles.
- Leer archivos CSV devueltos por dichos dispositivos con las lecturas.
- Procesar lecturas, calcular consumos y generar facturas.
- Identificar y organizar usuarios deudores.

---

## ⚙️ Características principales

- 🗃️ **Manejo de estructuras en C** para representar medidores, usuarios, rutas y facturas.
- 📥 **Importación de archivos CSV** para rutas y lecturas.
- 📤 **Exportación de archivos CSV** con rutas para los dispositivos móviles.
- 📊 **Procesamiento de lecturas** y cálculo de consumo.
- 💰 **Generación de facturas** automáticamente a partir del consumo registrado.
- 🌳 **Árbol binario de búsqueda (ABB)** para almacenar y listar usuarios deudores (ordenado por apellido y nombre).

---

## 🌳 Árbol de búsqueda binaria

Se implementa un **ABB (árbol binario de búsqueda)** para:

- Registrar los **usuarios deudores al mes de mayo**.
- Ordenarlos por **apellido y nombre**.
- Mostrar la lista de deudores ordenadamente (inorden).

---

## 📝 Requisitos funcionales

- Lectura y escritura de archivos `.csv`.
- Generación de rutas de medidores.
- Cálculo de consumo por usuario.
- Almacenamiento de facturas emitidas.
- Identificación automática de usuarios deudores.
- Visualización ordenada de deudores.

---

## 🚀 Cómo ejecutar el proyecto

Ejecutar main.exe que se encuentra en output.

---

## 💡 Posibles mejoras futuras

- Incorporar una interfaz gráfica o versión web.
- Integrar base de datos para persistencia real.
- Implementar cifrado y control de acceso para datos sensibles.
- Automatizar envío de facturas por correo electrónico.

---

## 📄 Licencia

Este proyecto es de uso académico y está disponible bajo la licencia [MIT](LICENSE).

---

¡Gracias por visitar el proyecto! 😊
=======
## Escenario

Una empresa a cargo del servicio de potabilización y distribución de agua potable en la
ciudad, debe realizar la inspección de los medidores para determinar cuánto consumo hubo.
Para ello hace uso de unas libretas donde se registra el número de medidor y el estado del
reloj (número que representa la cantidad m3 de agua). Dicha libreta es completada y traída
hasta la central donde el personal del área de medición y facturación, carga todo en una
planilla de cálculos para determinar el consumo que tuvo dicho medidor en ese período de
tiempo. Todo esto con el objetivo de imprimir la factura que se distribuirá posteriormente
entre los usuarios.
Este proceso se ha vuelto muy engorroso, a su vez ha llevado a generar muchos errores, ya
que la carga del estado del medidor se hace más de una vez, facilitando la generación de
los mismos.
Por otro lado, el caudal de medidores a relevar es grande y continúa creciendo, por lo que
dificulta el doble trabajo de carga (de medidor a libreta y de libreta a planilla de cálculo).
Por los motivos mencionados, la empresa decidió comprar dispositivos especiales para la
toma de estado; dichos dispositivos pueden importar información con las “rutas” a realizar.
Se llaman rutas a la agrupación de medidores que comparten ubicación geográfica
aproximada, por ende lo que se hace es agrupar medidores para distribuir la toma de
estados, asignando un conjunto de rutas a cada “caminante”. El caminante es el empleado
que se encarga de hacer la toma de estado.
La empresa sabe que no alcanza solo con mejorar el proceso de toma de estado, también
requiere de un sistema de facturación que optimice el trabajo y genere los archivos
necesarios para la toma de estado, como así también procese los archivos devueltos por
dichos dispositivos.

## Requerimientos del sistema:
1. El dispositivo requiere de que se le suministre la información por medio de archivos
de tipo csv "Comma Separated Values", que no es más que valores separados por
coma. Hay que generar dichos archivos.
2. El dispositivo a la hora de bajar las tomas de estado realizadas, baja la información en el
mismo tipo de archivo (csv), con lo cual el sistema deberá poder leer dichos archivos e
ingresarlos al sistema para poder procesarlos a posterior.
3. El sistema deberá procesar la información descargada de los dispositivos, almacenando
el movimiento en el sistema y generando las facturas correspondientes.

## Consignas
● Crear las estructuras y los algoritmos/códigos necesarios para almacenar datos
requeridos y representar el escenario.
● Generar un árbol de búsqueda binaria que contenga los usuarios deudores al mes
de mayo ordenado por apellido y nombre. A partir del árbol creado mostrar quienes
son.
>>>>>>> 021990cf52082115f691ff362aa6613df3ef1332
