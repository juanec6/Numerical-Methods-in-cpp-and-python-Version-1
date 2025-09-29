import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Cargar archivo CSV ignorando la primera fila (Encabezado)
datos = np.genfromtxt("resultados.csv", 
                      delimiter=", ", skip_header=1, dtype=float, filling_values=np.nan)

# Ahora podemos separar los datos por columnas
xValues  = datos[:, 0]
yValues  = datos[:, 1]
mValues  = datos[:, 2]
fmValues = datos[:, 3]
raiz     = datos[:, 4]
error    = datos[:, 5]

# Ahora simplemente se crea el data frame 
df = pd.DataFrame({
    "x": xValues,
    "f(x)": yValues,
    "m": mValues,
    "f(m)": fmValues,
    "raiz": raiz,
    "error": error
})

df_raices = df.dropna(subset=["raiz"])

# Esto sirve para ver todos los valores de salida.
# pd.set_option("display.max_rows", None)   # muestra todas las filas
# pd.set_option("display.max_columns", None)  # muestra todas las columnas
# pd.set_option("display.width", None)     # no cortar por ancho
# pd.set_option("display.max_colwidth", None)  # no cortar el contenido de las celdas

fig, ax = plt.subplots(figsize=(10,6))

# Graficar f(x)
ax.plot(df["x"], df["f(x)"], marker="o", label="f(x)")

# Graficar raíces como circulitos
ax.scatter(df_raices["raiz"], df_raices["f(m)"],
           color="red", edgecolor="black", s=120, marker="o", label="Raíces")

# Etiquetas y leyenda
ax.set_title("Gráfico de f(x) con raíces")
ax.set_xlabel("x")
ax.set_ylabel("f(x)")
ax.grid(True)
ax.legend()

# Dejar límites automáticos según los datos
ax.relim()           # recalcula límites
ax.autoscale()       # ajusta la escala automáticamente

plt.show()
