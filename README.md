# Proyecto 01
## Introducción
### Objetivo
- Simular usando el terminal de window
- Comparar las dos técnicas para ver en que caso es más favorable usar una que la otra.
- Definir una complejidad de accesos a memoria para cada técnica
### Dominio usado
La data fue extraídade kaggle. Una página web donde se actualiza diariamente diferentes dataset que pueden usarse de manera libre. En este caso, usaremos una base de datos de los rankings de los equipos de fútbol según la FIFA.
### Resultados esperados
El ExtendibleHash al ser una estrategia para optimizar la busqueda , la inserción y eliminación de un record de acuerdo a buckets, se espera que sea O(1) sin tomar en consideración los overflows que pueden llegar a ocurrir. Por otro lado, el sequential file se espera que su complejidad no sea superior al ExtendibleHash, excepto cuando esté en overflow.
## Marco Teórico
### Extendible Hash
#### Definición
Tecnica optimizada del Statich Hash donde definimos una profundidad (Arboles) para la busqueda por las ramas de dónde se insertará el record. A parte de eso, este crece de manera que se ingresen más records, pero su límite es cuando llega a la **profundidad global**. Para nuestro proyecto definimos el parámetro como 8.
#### Insert
- La inserción de un registro es mediante la profundidad. Entonces para esto convertimos el número otorgado por la función hash y lo convertimos a binario. La cantidad de bits depende de la profundidad global.
- Procedemos a buscar usando la profundidad local del nodo para encontrar el bucket correspondiente donde se insertará. Si está lleno, se crean dos nuevas ramas donde reorganizaremos el bucket desmantelado. Para esto primero incrementamos la profundidad local en 1 y repetimos el paso número 1.
- Finalmente si se encuentra en overflow lo único que haremos será incrementar el depth en 1 e insertar todos los records que corresponden ahi.
#### Search
- Buscamos usando la función hash para encontrar la posición con la llave pasada(ranking en este caso). Transformamos a binario y procedemos a buscar en que rama se encuentra.
- Encontrada la rama verificamos que se encuentre ahi. Devolvemos un true si se encuentra y un false si no está en el bucket.
#### Delete
- Buscamos usando la función hash y lo convertimos a binario. Procedemos a usar la busqueda para encontrar el bucket donde se encuentra el record. Si no lo encuentra se bota una excepción.
- Una vez encontrado el bucket, iteramos sobre él para encontrarlo. Una vez encontrado, usamos la función erase de la librería vector y procedemos a eliminarlo. Cabe resaltar que esto solo lo hacemos en la RAM y no se ven los cambios en el archivo.
### Sequential File
#### Definición
El sequential file es un método que mantiene ordenado los records físicamente pero sino se encuentra ordenado el archivo, necesita un tiempo extra para ordenarlo dependiendo de la llave que pasemos.
#### Insert
- Depende de la ubicación que mantiene en el archivo ordenado, es decir, por ejemplo si tenemos el record ordenado por el nombre como Susan y queremos insertar Ana. Ana va antes que Susan; entonces, solo ponemos primero a Ana y luego Susan. Sin embargo en el otro caso, tenemos que dirigir un puntero de Susan a Ursula para mantenerlo ordenado pero creando un nuevo espacio auxiliar.
- Terminado ese proceso debemos reorganizar el archivo original cada tiempo. En nuestro caso será después que el programa deje de estar corriendo y se llamen a los métodos DESTRUCTOR de la clase.
#### Search
- Usamos el algoritmo de busqueda binaria para localizar un registro en el archivo con un valor k.
- La busqueda necesita O(logn) accesos a memoria secundaria.
- Debemos descartar los elementos eliminados.
#### Delete
- Utilizamos los punteros del registro para saltar de un elemento a otro.
- Los records eliminados lo ponemos con -1 y actualizamos el archivo.
- Cuando termine de ejecutarse el programa, reorganizamos el archivo principal llamando al DESTRUCTOR.
## Resultados experimentales
![](https://i.imgur.com/dMesSbD.png)
## Link del video
## Cuadro de participación
|Lista de actividades realizadas|Responsable|Nota|
|-------------------------------|-----------|----|
|Escritura del informe          |SalvadorH. |    |
|Codeo del Extendible Hash      |SH. y E.Car|    |
|Codeo del Sequential File      |Neft. Calix|    |
|Codeo del menu en el Terminal  |Eros Car.  |    |
