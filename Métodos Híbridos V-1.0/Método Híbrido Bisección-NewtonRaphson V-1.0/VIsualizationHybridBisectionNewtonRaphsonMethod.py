import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#Load files

data1 = np.genfromtxt("xValuesyValues.csv",
                       delimiter=", ", skip_header=1, dtype=float)

data2 = np.genfromtxt("roots.csv",
                       delimiter=", ", skip_header=1, dtype=float)

#We can separed into columns
xValues = data1[:, 0]
yValues = data1[:, 1]
roots = data2[:, 0]
relError = data2[:, 1]


#we can create a data frame to plot the function
df1 = pd.DataFrame({
    "x": xValues,
    "f(x)": yValues
})

#We can also create a data frame to plot the roots
df2 = pd.DataFrame({
    "roots": roots,
    "relError": relError
})

# Replace infinite relative errors (caused by division by zero when root = 0)
df2["relError"] = np.where(np.isinf(df2["relError"]), 0, df2["relError"])

#Here we are going to remove the duplicates since newton rapshon usually 
# grepeats the roots depeding on the step size
df2_cleaned = df2.drop_duplicates()
#Now let's plot the function and the roots of the function given
print(df2_cleaned.head(50))   # Revisando duplicados

fig1, ax1 = plt.subplots(figsize=(10,6))
ax1.plot(df1["x"], df1["f(x)"], marker=".", label="f(x)")
ax1.scatter(df2_cleaned["roots"], [0]*len(df2_cleaned["roots"]), color="red", 
            edgecolors="black", s=120, marker="o", label="Roots")

# 🔹 Etiquetas con los valores de las raíces:
for r in df2_cleaned["roots"]:
    ax1.text(r, 0.05, f"{r:.3f}", fontsize=9, ha="center", color="black")

ax1.set_title("f(x) = 0 with Hybrid Bisection-Newton-Raphson")
ax1.set_xlabel("x")
ax1.set_ylabel("f(x)")
ax1.grid(True)
ax1.legend()
ax1.autoscale()
plt.tight_layout()
plt.show()