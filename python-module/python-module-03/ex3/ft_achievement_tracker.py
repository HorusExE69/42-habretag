import random


def gen_player_achievements(achievements):
    res = set()
    nb = random.randint(0, len(achievements)-1)
    res = random.sample(achievements, nb)
    return res


if __name__ == "__main__":
    achievements = [
        "Greatest Swordman In The World",
        "Surgeon Of Death",
        "King Of Hell",
        "Mr. Prince",
        "Heavenly Demon",
        "Soul King",
        "Devil Child",
        "First Son Of The Sea",
        "Flame Emperor",
        "Dark King",
        "King Of Beasts"
        "Humanity's Strongest Soldier",
        "The Hope Of Humanity",
        "The Honored One",
        "The Symbol Of Peace",
        "The Hero Killer",
        "Dragon's Sin of Wrath",
        "Lion's Sin of Pride",
        "Fox's Sin of Greed",
        "Serpent's Sin of Envy",
        "Boar's Sin of Gluttony",
        "Goat's Sin of Lust",
        "Grizzly's Sin of Sloth",
    ]

    p1 = "Horus"
    p2 = "Ra"
    p3 = "Anubis"
    p4 = "Isis"
    p5 = "Osiris"

    players = {
        p1: gen_player_achievements(achievements),
        p2: gen_player_achievements(achievements),
        p3: gen_player_achievements(achievements),
        p4: gen_player_achievements(achievements),
        p5: gen_player_achievements(achievements)
    }

    inter = set(achievements)

    uni = set(achievements)

    dif1 = set(players[p1])
    dif2 = set(players[p2])
    dif3 = set(players[p3])
    dif4 = set(players[p4])
    dif5 = set(players[p5])

    print("=== Achievements Tracker System ===")
    for p in players:
        print(f"Player {p}: {set(players[p])}")
        if p1 != p:
            dif1 = dif1.difference(players[p])
        if p2 != p:
            dif2 = dif2.difference(players[p])
        if p3 != p:
            dif3 = dif3.difference(players[p])
        if p4 != p:
            dif4 = dif4.difference(players[p])
        if p5 != p:
            dif5 = dif5.difference(players[p])
        inter = inter.intersection(players[p])
        uni = uni.union(players[p])
    print("")
    print("All distinct achievements: ", uni)
    print("")
    print("Common achievements: ", inter)
    print("")
    print(f"Only {p1} has: ", dif1)
    print(f"Only {p2} has: ", dif2)
    print(f"Only {p3} has: ", dif3)
    print(f"Only {p4} has: ", dif4)
    print(f"Only {p5} has: ", dif5)
    print("")
    print(f"{p1} is missing: ", set(achievements).difference(players[p1]))
    print(f"{p2} is missing: ", set(achievements).difference(players[p2]))
    print(f"{p3} is missing: ", set(achievements).difference(players[p3]))
    print(f"{p4} is missing: ", set(achievements).difference(players[p4]))
    print(f"{p5} is missing: ", set(achievements).difference(players[p5]))

