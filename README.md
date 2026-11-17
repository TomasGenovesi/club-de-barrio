# TP Recuperatorio AyED 2026 — El Club de Barrio

**Nombre:** _(completar)_
**Comisión:** _(completar)_

## Cómo se compila y se corre

```
g++ -o club club.cpp
./club          (en Windows: club.exe)
```

Es un solo programa con menú. Si `socios.dat` y `pagos.dat` no existen, los crea vacíos al arrancar (modo `"ab"`), así que se puede correr desde una carpeta vacía.

## Cómo resolví el PUP

El socio con número `idSocio` está siempre en la posición `idSocio - 1` de `socios.dat`:

- El **alta** va siempre al final y el número nuevo es la cantidad de registros más 1 (`ftell / sizeof(Socio)` + 1).
- La **baja nunca borra**: solo pone `activo = false`. Por eso los números no se corren ni se reutilizan.
- Para llegar a un socio hago `fseek` a `(id - 1) * sizeof(Socio)` y leo con un solo `fread`, sin recorrer el archivo.

La función `buscarSocioPUP` lo hace una sola vez y la usan modificar, baja, registrar pago y el reporte. Si el número es menor que 1 o mayor que el último socio, `fread` no devuelve 1 y el socio se considera inexistente.

Modificar y dar de baja siguen el ciclo apuntar, leer, modificar, apuntar de nuevo y grabar: la lectura corre el puntero, así que antes de grabar vuelvo a posicionarme con `fseek`.

## Cómo inserto un pago sin desordenar `pagos.dat`

Copio `pagos.dat` a un archivo auxiliar en una sola pasada. Apenas aparece un pago de un socio **mayor** al del pago nuevo, escribo primero el nuevo. Si no aparece ninguno, el nuevo va al final. Al terminar borro el original y renombro el auxiliar. Uso `>` y no `>=` para que el pago nuevo quede después de los que ya tenía ese socio.

## Cómo resolví el corte de control

El reporte recorre `pagos.dat` una sola vez. Como está ordenado por socio, los pagos de cada socio vienen juntos: leo anticipadamente el primer registro y, por cada socio, un ciclo interno acumula la cantidad de cuotas y el total mientras `idSocio` no cambie. Al salir del ciclo interno imprimo el socio (el nombre lo traigo por PUP y agrego «(dado de baja)» si corresponde) y acumulo los totales del club. Como la impresión ocurre al salir del ciclo interno, el último socio también se imprime.

## Reglas del enunciado

- Archivos binarios con `fopen`, `fread`, `fwrite`, `fseek`, `ftell` y `fclose` (más `remove` y `rename` para reemplazar `pagos.dat` con el auxiliar).
- Entrada y salida solo con `cin` y `cout`.
- Sin `vector`, `list`, `sort`, `stringstream` ni `string`: solo arrays, structs y `char[]`.
