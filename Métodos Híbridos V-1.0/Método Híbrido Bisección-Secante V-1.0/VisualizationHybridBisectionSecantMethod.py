import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#Load files

data1 = np.genfromtxt("xValuesyValues.csv",
                       delimiter=", ", skip_header=1, dtype=float)

data2 = np.genfromtxt("roots.csv",
                       delimiter=", ", skip_header=1, dtype=float)