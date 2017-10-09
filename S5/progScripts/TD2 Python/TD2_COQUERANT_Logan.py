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
    r = y - 1900
    nb_days = 0
    if r > 0 :
        for i in range (0, r):
            if is_leap_year(1900+i):
                nb_days += 366
            else:
                nb_days += 365
        for i in range (1, m):
            nb_days += number_of_day(y, i)
        nb_days += d
    elif r == 0:
        for i in range (1, m):
            nb_days += number_of_day(y, i)
        nb_days += d
    else:
        r = abs(r)
        curMonth = m
        if r == 1 :
            nb_days += number_of_day(1899, curMonth) - (d - 1)
            curMonth += 1
            while curMonth < 13 :
                nb_days += number_of_day (1899 , curMonth)
                curMonth += 1
        else :
            for i in range(0, r - 1):
                if is_leap_year(1900 - i):
                    nb_days += 366
                else:
                    nb_days += 365
            nb_days += number_of_day(1900 - r, curMonth) - (d - 1)
            curMonth += 1
            while curMonth < 13 :
                nb_days += number_of_day (1900 - r , curMonth)
                curMonth += 1
        tab_month = [1,0,6,5,4,3,2]
        return tab_month[nb_days%7]
    return (nb_days)%7

print(day_of_week(2017,9,24))
print(day_of_week(1997,7,28))
print(day_of_week(1899,12,31))

#2.1.2

def cal(y, m):
    actual_day = 1
    nb_days = number_of_day(y,m)
    first_day = day_of_week(y, m, 1)
    tab_month = ["January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    tab_week = ["Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"]
    cal = "   " + tab_month[m-1] + " " + str(y) + "\n"
    for d in tab_week:
        cal += str(d) + " "
    cal += "\n"
    for i in range (0, first_day - 1):
        cal += "   "
    for i in range (first_day - 1, 7):
        cal += " " + str(actual_day) + " "
        actual_day += 1
    cal += "\n"
    weekDay = 1
    while actual_day  < nb_days+1 :
        if actual_day < 10:
            cal += " " + str(actual_day) + " "
        else :
            cal += str(actual_day) + " "
        if weekDay != 0 and (weekDay)%7 == 0:
            cal += "\n"
        weekDay += 1
        actual_day += 1
    return cal

print(cal(2017,9))

# 2.1.3

def day_of_week_Delambre(y,m,d):
    assert 1899 < y < 2101
    is_leap = is_leap_year(y)
    tab_month_normal = [4,0,0,3,5,1,3,6,2,4,0,2]
    tab_month_leap = [3,6,0,3,5,1,3,6,2,4,0,2]
    if is_leap :
        res = (d + tab_month_leap[m-1] + ((21/4) * (y/100)) + ((5/4) * (y%100)) + 2)%7
    else :
        res = (d + tab_month_normal[m-1] + ((21/4) * (y/100)) + ((5/4) * (y%100)) + 2)%7
    return int(res)

print(day_of_week_Delambre(2017,9,24))
print(day_of_week_Delambre(1997,7,28))

def cal_optionnal(y,m, weekday="weekday_delambre"):
    assert weekday == "weekday_delambre" or weekday == "weekday_hardway"
    actual_day = 1
    nb_days = number_of_day(y,m)
    if weekday == "weekday_hardway" :
        first_day = day_of_week(y, m, 1)
    else :
        first_day = day_of_week_Delambre(y,m,1)
    tab_month = ["January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    tab_week = ["Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"]
    cal = "   " + tab_month[m-1] + " " + str(y) + "\n"
    for d in tab_week:
        cal += str(d) + " "
    cal += "\n"
    for i in range (0, first_day - 1):
        cal += "   "
    test_retour = False
    for i in range (first_day - 1, 7):
        cal += " " + str(actual_day) + " "
        if actual_day == 7 :
            cal += "\n"
            test_retour = True
        actual_day += 1
    if not test_retour:
        cal += "\n"
    weekDay = 1
    while actual_day  < nb_days+1 :
        if actual_day < 10:
            cal += " " + str(actual_day) + " "
        else :
            cal += str(actual_day) + " "
        if weekDay != 0 and (weekDay)%7 == 0:
            cal += "\n"
        weekDay += 1
        actual_day += 1
    return cal

print(cal_optionnal(2017, 9))

# 2.1.4

def seconds_between_deluxe(y1, m1, d1, y2, m2, d2):
    """
	This function compute the numbers of seconds between two dates ( date 1 and date 2 ).

	CU : The order of the two dates doesn't change the result.
	     Both months and dates need to be respectivly below 13 et 32.
    """
    assert m1 < 13 and m2 < 13
    assert d1 < 32 and d2 < 32

    r = abs(y1 - y2)

    nb_days = 0
    if r > 0 :
        for i in range (0, r):
            if is_leap_year(min(y1,y2)+i):
                nb_days += 366
            else:
                nb_days += 365

    if y1 < y2 :
        for i in range (1, m1):
            nb_days -= number_of_day(y1, i)
        nb_days -= d1
        for j in range (1, m2):
            nb_days += number_of_day(y2, i)
        nb_days += d2
    else :
        for i in range (1, m2):
            nb_days -= number_of_day(y2, i)
        nb_days -= d2
        for j in range (1, m1):
            nb_days += number_of_day(y2, i)
        nb_days += d1

    return (nb_days-1) * 24 * 60 * 60

print(seconds_between_deluxe(2017,9,24,2017,9,26))
