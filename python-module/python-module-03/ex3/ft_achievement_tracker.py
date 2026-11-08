import random

def gen_player_achievements(achievements) :
    res = set()
    nb = random.randint(0,len(achievements)-1)
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

    players = {
        "Horus":gen_player_achievements(achievements),
        "Ra":gen_player_achievements(achievements),
        "Anubis":gen_player_achievements(achievements),
        "Isis":gen_player_achievements(achievements),
        "Osiris":gen_player_achievements(achievements)
    }

    inter = set(achievements)
    print("=== Achievements Tracker System ===")
    for p in players :
        print(f"Player {p}: {players[p]}")
        inter.intersection(players[p])
    print("")
    print("All distinct achievements: ", achievements)
    print("")
    print("Common achievements: ", inter)

