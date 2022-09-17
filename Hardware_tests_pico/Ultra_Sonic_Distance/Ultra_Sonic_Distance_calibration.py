# import libraries
from statistics import mean
from turtle import color
import numpy as np
import matplotlib.pyplot as plt

x = 0.5 * np.array([ mean([ 602,608 ]) , mean([ 1165,1166,1160,1159]) , mean([ 1726,1727 ]) , mean([ 2238,2239 ]) , mean([ 2865,2866,2872 ]) , mean([ 3398,3395,3392 ]) , mean([ 3942,3941 ]) , mean([ 4570,4569,4543]) , mean([ 5116,5115,5110 ]) , mean([ 5635,5636,5642 ]) , mean([ 6255,6256,6250 ]) , mean([ 6854,6851,6855 ]) ] )

y = np.arange( 10 , 130 , 10 )

plt.scatter( x , y )
reg_data = np.polynomial.polynomial.polyfit( x , y , deg=1)
print( reg_data )
print("Speed = " , reg_data[1] , "cm/\u03BCs" , '\t' , reg_data[1]*10**4 , "m/s")
y_reg = np.polynomial.polynomial.polyval( x , reg_data)
plt.plot( x , y_reg , '--' , color = 'yellow' )
plt.xlabel("Time (\u03BCs)")
plt.ylabel("distance (cm)")
plt.show()


