# kdtree-weather

Simple aplicación de la estructura Kdtree en el cual usamos datos del clima de una ciudad para predecir el clima en una una fecha x dandole ciertos parametros.

## Compilar
Para compilar se hace uso de CMake.
### EN LINUX
Primero creamos la carpeta buil, una vez dentro ejecutamos lo siguiente:
```bash
cmake ..
```
```bash
make
./Weather
```

## Nota
El valor referencial es la cantidad de puntos cercanos a los que consultará con los cuales promediará y obtendrá el clima.
