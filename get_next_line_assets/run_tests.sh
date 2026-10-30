#!/bin/sh
# Teste get_next_line : norminette, puis compilation et tests avec plusieurs
# BUFFER_SIZE (partie obligatoire, puis bonus si les fichiers _bonus existent),
# avec détection des erreurs mémoire et des fuites.
#   sh run_tests.sh            tous les BUFFER_SIZE
#   sh run_tests.sh 1 42       seulement ceux-là
#
# Détection mémoire :
#   Linux : valgrind si installé (machines de l'école), sinon AddressSanitizer
#   Mac   : AddressSanitizer (crashs, débordements) + "leaks" (fuites)

GNL=../get_next_line
SIZES="${*:-1 2 3 5 42 9999 10000000}"
FLAGS="-Wall -Wextra -Werror"
OS=$(uname)
fails=0

# ---------- norminette ----------
if command -v norminette > /dev/null 2>&1; then
	norm=$(norminette $GNL 2>&1 | grep "Error")
	if [ -z "$norm" ]; then
		echo "norminette                       OK"
	else
		echo "norminette                       KO"
		echo "$norm" | head -20
		fails=$((fails + 1))
	fi
else
	echo "norminette                       (non installée, ignorée)"
fi

if [ "$OS" = "Linux" ] && command -v valgrind > /dev/null 2>&1; then
	MEM="valgrind"
elif [ "$OS" = "Darwin" ]; then
	MEM="asan+leaks"
else
	MEM="asan"
fi
echo "détection mémoire : $MEM"
echo

# compile ; $1 = flags supplémentaires, la suite = fichiers
build() {
	extra=$1; shift
	cc $FLAGS $extra $def -I$GNL test_gnl.c "$@" -o test_gnl_bin
}

run() {
	mode=$1; size=$2; shift 2
	if [ "$size" = "aucun" ]; then def=""; else def="-D BUFFER_SIZE=$size"; fi
	label=$(printf "%-12s BUFFER_SIZE=%-9s" "$mode" "$size")
	case $MEM in
		valgrind)
			build "-g" "$@" || { echo "$label compilation KO"; fails=$((fails + 1)); return; }
			out=$(valgrind -q --leak-check=full --errors-for-leak-kinds=all \
				--error-exitcode=42 ./test_gnl_bin 2>&1)
			status=$? ;;
		asan)
			build "-g -fsanitize=address" "$@" || { echo "$label compilation KO"; fails=$((fails + 1)); return; }
			out=$(./test_gnl_bin 2>&1)
			status=$? ;;
		asan+leaks)
			build "-g -fsanitize=address" "$@" || { echo "$label compilation KO"; fails=$((fails + 1)); return; }
			out=$(./test_gnl_bin 2>&1)
			status=$?
			if [ $status -eq 0 ]; then
				build "-g" "$@"
				out=$(MallocStackLogging=1 leaks -quiet --atExit -- ./test_gnl_bin 2>&1)
				status=$?
			fi ;;
	esac
	if [ $status -eq 0 ]; then
		echo "$label OK"
	else
		echo "$label KO"
		echo "$out" | grep -E "KO|obtenu|ERROR|SUMMARY|leak|Invalid|definitely|LEAK" | head -20
		fails=$((fails + 1))
	fi
}

for s in $SIZES aucun; do
	run "obligatoire" "$s" $GNL/get_next_line.c $GNL/get_next_line_utils.c
done
if [ -f $GNL/get_next_line_bonus.c ]; then
	for s in $SIZES aucun; do
		run "bonus" "$s" -DBONUS $GNL/get_next_line_bonus.c \
			$GNL/get_next_line_utils_bonus.c
	done
fi
rm -rf gnl_files
echo
if [ $fails -eq 0 ]; then
	echo "=> Tout est bon"
else
	echo "=> $fails vérification(s) KO (lance ./test_gnl_bin à la main pour le détail)"
fi
