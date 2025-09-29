import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Cargar archivos
datos1 = np.genfromtxt("ValoresXeY.csv",
                       delimiter=",", skip_header=1, dtype=float)
datos2 = np.genfromtxt("RaicesyErrores.csv",
                       delimiter=",", skip_header=1, dtype=float)

# Separar columnas
xValues  = datos1[:, 0]
yValues  = datos1[:, 1]
xr       = datos2[:, 0]
errorAb  = datos2[:, 1]
errorRel = datos2[:, 2]

#Data frame para la gráfica
df1 = pd.DataFrame({"x": xValues, "f(x)": yValues})

#Data frame para mostrar las raíces y la gráfica de las raíces, Error Absoluto y Relativo.
df2 = pd.DataFrame({"xr": xr, "ErrorAbsoluto": errorAb, "ErrorRelativo": errorRel})

# -------- Figura 1: f(x) con raíces --------
fig1, ax1 = plt.subplots(figsize=(10, 6))
ax1.plot(df1["x"], df1["f(x)"], marker=".", label="f(x)")
ax1.scatter(df2["xr"], [0]*len(df2["xr"]),
            color="red", edgecolors="black", s=120, marker="o", label="Raíces")
ax1.set_title("Gráfico f(x) con raíces")
ax1.set_xlabel("x")
ax1.set_ylabel("f(x)")
ax1.grid(True)
ax1.legend()
ax1.autoscale()

# -------- Figura 2: Errores --------
fig2, ax2 = plt.subplots(2, 1, figsize=(14, 5))

# Error absoluto
ax2[0].plot(range(1, len(df2) + 1), df2["ErrorAbsoluto"],
            marker="o", color="blue", label="Error Absoluto")
ax2[0].set_title("Evolución del Error Absoluto")
ax2[0].set_xlabel("Iteración")
ax2[0].set_ylabel("Error")
ax2[0].grid(True)
ax2[0].legend()

# Error relativo
ax2[1].plot(range(1, len(df2) + 1), df2["ErrorRelativo"],
            marker="o", color="green", label="Error Relativo")
ax2[1].set_title("Evolución del Error Relativo")
ax2[1].set_xlabel("Iteración")
ax2[1].set_ylabel("Error")
ax2[1].grid(True)
ax2[1].legend()

plt.tight_layout()
plt.show()
