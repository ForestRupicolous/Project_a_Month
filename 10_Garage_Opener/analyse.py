import pandas as pd
import numpy as np

df = pd.read_csv('C:/Projekte/1_Project_a_Month/10_Garage_Opener/NewFile2.csv', header=0)
print df
df['Logic'] = df['Volt']>5.0
print df
df['Switching'] = np.where(df['Logic'] != df['Logic'].shift(1),df['Second'],np.nan)
df['Timing'] = df['Switching'].fillna(method='pad')
df['Duration'] = df['Timing'].diff()
ds = df[df['Duration']!=0]
conditions = [
	(ds['Duration'].shift(1).between(0.000090, 0.000093, inclusive=True)) & 
		(ds['Duration'].between(0.000350, 0.000354, inclusive=True)),
	(ds['Duration'].shift(1).between(0.000090, 0.000093, inclusive=True)) & 
		(ds['Duration'].between(0.000173, 0.000176, inclusive=True)),
	(ds['Duration'].shift(1).between(0.000267, 0.000270, inclusive=True)) & 
		(ds['Duration'].between(0.000350, 0.000354, inclusive=True)),
	(ds['Duration'].shift(1).between(0.000267, 0.000270, inclusive=True)) & 
		(ds['Duration'].between(0.000173, 0.000176, inclusive=True))]
choices = [1, 0, 1, 0]
ds['Real_Bits'] = np.select(conditions,choices,default = np.nan)
print ds
ds.to_csv('C:/Projekte/1_Project_a_Month/10_Garage_Opener/msrmt_opt.csv', index = False)
