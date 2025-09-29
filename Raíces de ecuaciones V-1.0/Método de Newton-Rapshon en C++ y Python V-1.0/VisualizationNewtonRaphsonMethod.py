import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Tolerancia para considerar raíces iguales
toleranciaRaiz = 1e-6 

# Se cargan los archivos para visualizar la gráfica
datos = np.genfromtxt("xValoresYvalores.csv",
                      delimiter=", ", skip_header=1, dtype=float, filling_values=np.nan)

datos2 = np.genfromtxt("RaicesYerrores.csv",
                      delimiter=", ", skip_header=1, dtype=float, filling_values=np.nan)

# Se separan los datos por columnas:
xValues  = datos[:, 0]
yValues  = datos[:, 1]
raices = datos2[:, 0]
errores = datos2[:, 1]

# DataFrames
df1 = pd.DataFrame({
    "x": xValues,
    "f(x)": yValues
})

df2 = pd.DataFrame({
    "raices": raices,
    "errores": errores
})


# ---- Gráfico ----
fig, ax = plt.subplots(figsize=(10,6))
ax.plot(df1["x"], df1["f(x)"], marker=".", label="f(x)")
ax.scatter(df2["raices"], [0]*len(df2["raices"]), 
           color="red", edgecolor="black", s=80, marker="o", label="Raíces")

ax.set_title("Gráfico f(x)")
ax.set_xlabel("x")
ax.set_ylabel("f(x)")
ax.grid(True)
ax.legend()

# Dejar límites automáticos según los datos
ax.relim()          # Recalcula límites
ax.autoscale()      # Ajusta la escala automáticamente
plt.show()
