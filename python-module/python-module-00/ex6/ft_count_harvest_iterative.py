def	ft_count_harvest_iterative() :
	days = int(input("Days until harvest: "))
	if (days == 0) :
			print("Harvest time!")
			return
	for i in range(1, days + 1) :
		print(f"Day {str(i)}")
	print("Harvest time!")