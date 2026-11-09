import sys

class Inv() :
    def __init__(self, dic = {}) :
        self.dic = dic
        self.items = self.all_items()
        self.total_items = self.tot_items()

    def all_items(self) :
        lst = []
        for key in self.dic :
            lst.append(key)
        return lst

    def tot_items(self) :
        nb = 0
        for key in self.dic :
            nb += self.dic[key]
        return nb

    def add_item(self, item, quantity) :
        if item in self.dic :
            self.dic[item] += quantity
        else :
            self.dic[item] = quantity
        self.items = self.all_items()
        self.total_items = self.tot_items()

    def percentage(self, item) :
        perc = (self.dic[item] / self.total_items) * 100
        return perc

    @staticmethod
    def parse(lst):
        dic = {}

        for arg in lst:
            key = ""
            quantity = 0
            j = 0

            try:
                while arg[j] != ":":
                    key += arg[j]
                    j += 1
            except IndexError:
                print(f"Error - invalid parameter '{arg}'")
                continue

            try:
                quantity = int(arg[j + 1:])
            except ValueError:
                print(f"Quantity error for '{key}': invalid literal for int() with base 10: '{arg[j + 1:]}'")
                continue

            if key in dic:
                print(f"Redundant item '{key}' - discarding")
            else:
                dic[key] = quantity

        return dic
            
            
            

if __name__ == "__main__":
    print("=== Inventory System Analysis ===")
    dic = Inv.parse(sys.argv[1:])
    myinv = Inv(dic)
    print(f"Got inventory: {myinv.dic}")
    print(f"Item list: {myinv.items}")
    print(f"Total quantity of the 5 items: {myinv.total_items}")
    for key in myinv.dic :
        print(f"Item {key} represents {myinv.percentage(key):.1f}%")
    most = max(myinv.dic, key=myinv.dic.get)
    mini = min(myinv.dic, key=myinv.dic.get)
    print(f"Item most abundant: {most} with quantity {myinv.dic[most]}")
    print(f"Item least abundant: {mini} with quantity {myinv.dic[mini]}")
    myinv.add_item("magic_item", 1)
    print(f"Updated inventory: {myinv.dic}")

# python3 ft_inventory_system.py sword:1 potion:5 shield:2 armor:3 helmet:1 hello sword:2 key:value