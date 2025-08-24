import pandas as pd
import matplotlib.pyplot as plt

# Load CSV with no header
df = pd.read_csv("data.csv", header=None)

# Select column 2 (index 1), and rows 1 through 2722
y = df.iloc[1300:1700, 1]

# Plot
plt.plot(y)
plt.xlabel("Sample #")
plt.ylabel("12-bit encoding")
plt.title("~400 sound samples in 0.004 sec")
plt.show()