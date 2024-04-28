import numpy as np
from scipy.integrate import odeint
from numpy import sin, cos, arctan
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

# # Начальные условия

N = 2

m = [1 for _ in range(N)]
# m[4] = 10
G = 1


X0 = [
    0, # x_1
    2, # Vx_1
    2, # y_1
    -1, # Vy_1
    0, # x_2
    -2, # Vx_2
    -3, # y_2
    1 # Vy_2
]


t = np.linspace(0,300,2501)


# # Решение

# ## Функция системы

def DE(X, t):
    dxdt = [0.0 for _ in range(N*4)] 
    
    for i in range(N * 4):
        if (i % 2) == 0:
            dxdt[i] = X[i+1]
        elif (i % 4) == 1:
            for j in range(1,N*4,4):
                if i != j:
                    dxdt[i] += G * m[j//4] * (X[j-1]-X[i-1]) * ((X[j-1]-X[i-1])**2 + (X[j+1]-X[i+1])**2)**(-3/2)
        elif (i%4) == 3:
            for j in range(3,N*4,4):
                if i != j:
                    dxdt[i] += G * m[j//4] * (X[j-1]-X[i-1]) * ((X[j-3]-X[i-3])**2 + (X[j-1]-X[i-1])**2)**(-3/2)
        else:
            print(i)
#     print(dxdt[1::2])
    return dxdt


# ## Интегрирование



Vcosm = np.sqrt(G*sum(m)/9)

X0 = [
    -2, # x_1
    0, # Vx_1
    0, # y_1
    0.2, # Vy_1
    
    2, # x_2
    0, # Vx_2
    0, # y_2
    -0.2, # Vy_2
    
    #2, # x_Vcosm
    #0, # Vx_Vcosm
    #0, # y_Vcosm
    #0, # Vy_Vcosm
    
    #0, # x_4
    #0, # Vx_4
    #-2, # y_4
    #0, # Vy_4
]

#X0 = [np.random.uniform(-100,100) for _ in range(N*4)]

res = odeint(DE, X0, t)
dists = np.zeros((len(t), N))

for i in range(N):
    dists[:, i] = res[:, i*4]**2 + res[:, (i)*4+2]**2
max_dist = dists.max(axis=None)

for i in range(N):
    res[:, i*4] /= np.sqrt(max_dist)
    res[:, i*4+2] /= np.sqrt(max_dist)

df = pd.DataFrame()
df["t"] = t
for i in range(N):
    df[f"X{i}"]  = res[:, i*4 + 0]
    df[f"Vx{i}"] = res[:, i*4 + 1]
    df[f"Y{i}"]  = res[:, i*4 + 2]
    df[f"Vy{i}"] = res[:, i*4 + 3]
df.to_csv("result.csv", index=False)

