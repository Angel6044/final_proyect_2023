##Escenario
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

##Requerimientos del sistema:
1. El dispositivo requiere de que se le suministre la información por medio de archivos
de tipo csv "Comma Separated Values", que no es más que valores separados por
coma. Hay que generar dichos archivos.
2. El dispositivo a la hora de bajar las tomas de estado realizadas, baja la información en el
mismo tipo de archivo (csv), con lo cual el sistema deberá poder leer dichos archivos e
ingresarlos al sistema para poder procesarlos a posterior.
3. El sistema deberá procesar la información descargada de los dispositivos, almacenando
el movimiento en el sistema y generando las facturas correspondientes.

##Consignas
● Crear las estructuras y los algoritmos/códigos necesarios para almacenar datos
requeridos y representar el escenario.
● Generar un árbol de búsqueda binaria que contenga los usuarios deudores al mes
de mayo ordenado por apellido y nombre. A partir del árbol creado mostrar quienes
son.
