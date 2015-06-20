import pandas as pd
import numpy as np
#Read the input csv file 
# df is the dataframe we'd be working on 

df = pd.read_csv('test_data.csv',usecols = ['newsId','interval'])
grouped = df.groupby('newsId')
mean_df = grouped.aggregate(np.mean)
mean_df['count'] = grouped.size()

print mean_df.to_csv('means.csv')


