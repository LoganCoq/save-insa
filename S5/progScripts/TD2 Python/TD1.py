from math import sqrt


###EXO_1.1###

def greatest_root(a, b, c):
	assert a != 0 #It will automatically give us a second degree polynom
	d = b * b - 4 * a * c #Calculate the discriminant
	if d < 0 : 
		return None
	else : 
		return max((-b + sqrt(d)) / ( 2 * a), (-b - sqrt(d)) / (2 * a))


###EXO_1.2###

def celsius_to_fahrenheit(c) :
	assert c >= -273.15 #This is the absolute zero in celcius
	return c * (9 / 5) + 32


def fahrenheit_to_celsius(f) :
	assert f >= -459.67 #The same condition as the previous one but for fahrenheit
	return (f - 32) * (5 / 9)


###EXO_1.3###

def seconds_between(y1, m1, d1, y2, m2, d2) :
	nb_days = 365.2425/12
	assert m1>0 and m1<13 and d1>0 and d1<=nb_days and m2>0 and m2<13 and d2>0 and d2<=nb_days #Now we can have a valid date for every use of this function
	#In order to obtain the difference in seconds between two dates, we will convert a day, a month and a year in seconds
	day_sec = 60*60*24
	month_sec = nb_days * day_sec
	year_sec = 12 * month_sec
	return abs((abs(y1) * year_sec + (m1 - 1) * month_sec + day_sec * d1) - (abs(y2) * year_sec + (m2 - 1) * month_sec + day_sec * d2))  #We must use abs function to have a positive value
    

#1.4.1

def is_leap_year(y) :
	if y%4 == 0 and y%100 != 0 :
		return True
	elif y%400 == 0 :
		return True
	else :
		return False


#1.4.2

def number_of_day(y,m) :
        if not 0 < m < 13 :
                return 0
        elif m in [4, 6, 9, 11]:
                return 30
        elif m==2 :
                if is_leap_year(y):
                        return 29
                else:
                        return 28
        else :
                return 31


#1.4.3

def is_valid_date(y, m, d) :
	return number_of_day(y,m) >= d and d > 0 #We verify if the number of days is matching with the month and if the day is not 0 or under

#2.1.1

def day_of_week(y, m, d):
        assert is_valid_date(y, m, d)
        r = abs(y - 1900)
        nb_days = 0
        for i in range (0, r):
                if is_leap_year(y):
                        nb_days += 366
                else:
                        nb_days += 365
        for i in range (1, m):
                nb_days += number_of_day(y, i)
        nb_days += d
        return (nb_days + 1)%7

#2.1.2

def cal(y, m):
        actual_day = 1
        nb_days = number_of_day(y,m)
        first_day = day_of_week(y, m, 1)
        tab_month = ["January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
        tab_week = ["Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"]
        tab_day[6][7]
        for i in range (0, first_day - 1):
                tab_day[0][i] = " "
        for i in range (first_day - 1, 7):
                tab_day[0][i] = actual_day
                actual_day += 1
        for j in range (0, 6):
                for i in range (0, 7):
                        
        





































        
                
        
