from math import sqrt
from math import fabs

# 1 Données, expressions, et fonctions

# 1.1 Prenons racines
def greatest_root(a,b,c):
    """
    This function compute the greatest root of a 2nd degre polynome.
    It returns None if there is no real root.

    CU : The first argument needs to be different than 0, otherwise the assert will throw an error
    """
    assert a != 0

    delta = b*b - 4 * a * c
    
    if delta > 0: 
        x1 = ( -b - sqrt(delta)) / (2*a)
        x2 = ( -b + sqrt(delta)) / (2*a)
        return max(x1,x2)
    elif delta == 0:
        x1 = ( -b) / ( 2*a )
        return x1
    return None


print(greatest_root(5,10,2))


# 1.2 Conversion Celcius <-> Fahrenheit
def celcius_to_fahrenheit(value):
    """
	This function convert a value in degres celcius to a value in degres fahrenheit
    """
    res = (9/5) * value + 32
    return res

print(celcius_to_fahrenheit(30))

def fahrenheit_to_celcius(value):
    """ 
	This function convert a value in degres fahrenheit to a value in degres celcius
    """
    res = value - 32
    res = res / (9/5)
    return res 

print(fahrenheit_to_celcius(83))



# 1.3 Comptons les secondes

def seconds_between(y1, m1, j1, y2, m2, j2):
    """
	This function compute the numbers of seconds between two dates ( date 1 and date 2 ).

	CU : The order of the two dates doesn't change the result.
	     Both months and dates need to be respectivly below 13 et 32.
    """
    assert m1 < 13 and m2 < 13
    assert j1 < 32 and j2 < 32

    daysPerYear = 365.2425
    daysPerMonths = daysPerYear / 12
    res = 0
    diffYear = fabs(y1 - y2)

    nbDaysD1 = daysPerMonths*m1 + j1
    nbDaysD2 = daysPerMonths*m2 + j2

    if diffYear == 0:
        res = fabs(nbDaysD1-nbDaysD2) 
    else:
        res = diffYear * daysPerYear + fabs(nbDaysD1-nbDaysD2) 
    return res * 24 * 60 * 60

print(seconds_between(2017,7,10,2017,7,11))
print(seconds_between(2018,7,10,2017,7,17))



# 1.4 Calendrier

# 1.4.1 Suis-je bissextile ?

def isBissextile(year):
    """
	This function tests if a year is bisextil or not.

        CU : The year needs to be higher than 1582 because it's the time where the Gregorian  	
	calendar took effect
    """
    assert year > 1582 , "The Gregorian calendar didn't exist before this date"

    if year % 4 == 0:
        return True
    else: 
        return False

print(isBissextile(2016))
#print(isBissextile(1200))



# 1.4.2 Le mois le plus long

def daysPerMonths(month, year):
    """
        This function tells how many days a month contains. 
        
        CU : The year needs to be higher than 1582 because it's the time where the Gregorian  	
	calendar took effect
    """
    m30 = [4,6,9,11]
    if month == 2:
       if isBissextile(year):
           return 29
       else:
           return 28
    elif month in m30:
        return 30
    return 31
    



