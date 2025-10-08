import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#Load files

data1 = np.genfromtxt("XvaluesXvalues.csv",
                       delimiter=", ", skip_header=1, dtype=float)

data2 = np.genfromtxt("rootsAndSecRelErr.csv",
                       delimiter=", ", skip_header=1, dtype=float)

data3 = np.genfromtxt("bisectionErrors.csv", 
                      skip_header=1, dtype=float)

# Let's separate this into columns.
xValues = data1[:, 0]
yValues = data1[:, 1]
roots = data2[:, 0]
SecRelErr = data2[:, 1]
biError = data3[:]

#Data frame to create plot of the function
df1 = pd.DataFrame({
    "x": xValues,
    "f(x)": yValues
})

#Data frame for roots and relative error of the secant method
df2 = pd.DataFrame({
    "roots": roots,
    "SecRelErr": SecRelErr
})

df3 = pd.DataFrame({"biError": biError})


# ----- Function plotting and roots ------
fig1, ax1 = plt.subplots(figsize=(10, 6))

ax1.plot(df1["x"], df1["f(x)"], marker=".", label="f(x)")
ax1.scatter(
    df2["roots"],
    [0]*len(df2["roots"]),
    color="red", edgecolors="black", s=120,
    marker="o",
    label="Roots"
)

#Shows the values of the roots in the plot
for r in df2["roots"]:
    ax1.text(r, 0.05, f"{r:.3f}", fontsize=9, ha="center", color="black")

ax1.set_title("f(x) = 0 with Hybrid Bisection-Secant-Method")
ax1.set_xlabel("x")
ax1.set_ylabel("f(x)")
ax1.grid(True)
ax1.legend()
ax1.autoscale()

# ----- Errorrs -----

fig2, ax2 = plt.subplots(2, 1, figsize=(14, 5))

# Evolution of the relative error of the secant method
ax2[0].plot(range(1, len(df2) + 1), df2["SecRelErr"],
            marker="o", color="green", label="Secant Method Relative Error")
ax2[0].set_title("Secant Relative Error Evolution")
ax2[0].set_xlabel("Iteration")
ax2[0].set_ylabel("Error")
ax2[0].grid(True)
ax2[0].legend()

# Evolution of the relative error of the bisection method
ax2[1].plot(range(1, len(df3) + 1), df3["biError"],
            marker="o", color="blue", label="Bisection Relative Error")
ax2[1].set_title("Bisection Relative Error Evolution")
ax2[1].set_xlabel("Iteration")
ax2[1].set_ylabel("Error")
ax2[1].grid(True)
ax2[1].legend()

plt.tight_layout()
plt.show()
