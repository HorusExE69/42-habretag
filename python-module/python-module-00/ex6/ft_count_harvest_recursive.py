def	ft_count_harvest_recursive(i = 0, days = 0) :
	if (i == 0) :
		days = int(input("Days until harvest: "))
	if (days == 0) :
		print("Harvest time!")
		return
	i+=1
	if (i <= days) :
		print(f"Day {i}")
		ft_count_harvest_recursive(i, days)
	else :
		print("Harvest time!")