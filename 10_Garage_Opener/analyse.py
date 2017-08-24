import pandas as pd
import numpy as np

df = pd.read_csv('C:/Projekte/1_Project_a_Month/10_Garage_Opener/NewFile2.csv', header=0)
print df
df['Logic'] = df['Volt']>5.0
df['Logic_n-1'] = df['Logic'].shift(1)
df['Change'] = df['Logic'].diff()
print df
df['Switching'] = np.where(df['Logic'] != df['Logic'].shift(1),df['Second'],np.nan)
df['Timing'] = df['Switching'].fillna(method='pad')
df['Duration'] = df['Timing'].diff()

print df
ds = df.iloc[::50,:]
ds.to_csv('C:/Projekte/1_Project_a_Month/10_Garage_Opener/msrmt_opt.csv', index = False)
