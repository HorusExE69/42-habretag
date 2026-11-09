import random

if __name__ == "__main__":
    print("=== Game Data Alchemist ===\n")

    players = [
        "HERMES",
        "athena",
        "Ares",
        "Apollon",
        "artemis",
        "Dionysos",
        "Hades",
        "demeter",
        "hera",
        "POSEIDON",
        "ZEUS",
        "Hephaistos",
        "aphrodite",
        "Prometheus"
    ]

    print(f"Initial list of players: {players}")

    first_comp = [player.capitalize() for player in players]

    print(f"New list with all names capitalized: {first_comp}")
    
    second_comp = [player for player in players if player.capitalize() == player]

    print(f"New list of capitalized names only: {second_comp}\n")

    score_dict = {player: random.randint(0, 1000) for player in players}

    print(f"Score dict: {score_dict}")

    score_avg = sum(score_dict.values()) / len(score_dict)

    print(f"Score average is: {score_avg:.2f}")

    score_dict2 = {player: score for player, score in score_dict.items() if score > score_avg}

    print(f"High scores: {score_dict2}")