#!/bin/sh
#   sh run_tests.sh            tous les BUFFER_SIZE
#   sh run_tests.sh 1 42       seulement ceux-là

GNL=../get_next_line
SIZES="${*:-1 2 3 5 42 9999 10000000}"
FLAGS="-Wall -Wextra -Werror"
if [ "$(uname)" = "Linux" ]; then
	FLAGS="$FLAGS -g -fsanitize=address"
fi

fails=0
run() {
	mode=$1; size=$2; shift 2
	if [ "$size" = "aucun" ]; then
		def=""
	else
		def="-D BUFFER_SIZE=$size"
	fi
	if ! cc $FLAGS $def -I$GNL test_gnl.c "$@" -o test_gnl_bin; then
		echo "=> la compilation a échoué ($mode, BUFFER_SIZE=$size)"
		fails=$((fails + 1))
		return
	fi
	out=$(./test_gnl_bin 2>&1)
	status=$?
	if [ $status -eq 0 ]; then
		printf "%-12s BUFFER_SIZE=%-9s OK\n" "$mode" "$size"
	else
		printf "%-12s BUFFER_SIZE=%-9s KO\n" "$mode" "$size"
		echo "$out" | grep -E "KO|obtenu|ERROR|SUMMARY|leak" | head -20
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
if [ $fails -eq 0 ]; then
	echo "=> Tout est bon"
else
	echo "=> $fails configuration(s) KO (lance ./test_gnl_bin à la main pour le détail)"
fi
