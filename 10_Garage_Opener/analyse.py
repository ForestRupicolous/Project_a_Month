import pandas as pd
import numpy as np

df = pd.read_csv('C:/Projekte/1_Project_a_Month/10_Garage_Opener/NewFile3.csv', header=1)
print df
df = df.round(6)
Logic_Level = df['Volt'].mean()
df['Logic'] = df['Volt']>Logic_Level
print df
df['Switching'] = np.where(df['Logic'] != df['Logic'].shift(1),df['Second'],np.nan)
df['Timing'] = df['Switching'].fillna(method='pad')
df['Duration'] = df['Timing'].diff()
ds = df[df['Duration']!=0]
conditions = [
	(ds['Duration'].shift(1).between(0.000088, 0.000096, inclusive=True)) & 
		(ds['Duration'].between(0.000340, 0.000360, inclusive=True)),
	(ds['Duration'].shift(1).between(0.000088, 0.000096, inclusive=True)) & 
		(ds['Duration'].between(0.000170, 0.000180, inclusive=True)),
	(ds['Duration'].shift(1).between(0.000260, 0.000275, inclusive=True)) & 
		(ds['Duration'].between(0.000340, 0.000360, inclusive=True)),
	(ds['Duration'].shift(1).between(0.000260, 0.000275, inclusive=True)) & 
		(ds['Duration'].between(0.000170, 0.000180, inclusive=True)),
    (ds['Duration'].shift(1).between(0.000088, 0.000096, inclusive=True)) & 
		(ds['Duration']>0.005)]
choices = [1, 0, 1, 0, -1]
ds['Real_Bits'] = np.select(conditions,choices,default = 'X')
dx = ds[ds['Real_Bits']!='X']
print dx
print Logic_Level
dx.to_csv('C:/Projekte/1_Project_a_Month/10_Garage_Opener/msrmt_opt.csv', index = False)

#TODO:abfragen checken!