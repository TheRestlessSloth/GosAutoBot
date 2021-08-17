# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 14:08:21 2021

@author: Abkerimov Timur
"""

import pandas as pd
import numpy as np

clearConsole = lambda: print('\n' * 150)

print("Составление кинематической модели робота-манипулятора по принципу Денавита-Хартенберга")

n = int(input("Сколько звеньев? (моторов) "))
clearConsole()

DH = np.zeros(shape=(n,4))

for i in range(n):
    print("Сочленение ", i+1)
    DH[i,0] = int(input("Расстояние вдоль оси X{} от Z{} до Z{} (в мм) ".format(i+1,i,i+1)))
    DH[i,1] = int(input("Угол вокруг оси X{} от Z{} до Z{} (в градусах) ".format(i+1,i,i+1)))
    DH[i,2] = int(input("Расстояние вдоль Z{} от X{} до X{} (в мм) ".format(i,i,i+1)))
    DH[i,3] = int(input("Угол вокруг оси Z{} от X{} до X{} (в градусах) ".format(i,i,i+1)))
    clearConsole()

df = pd.DataFrame(data=DH, dtype=np.int16)
df.columns = ['a','alpha','d','tetha']
df.index = (df.index +1)
print(df)

df.to_csv(r'.\csv.csv')