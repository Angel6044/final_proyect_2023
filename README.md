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

