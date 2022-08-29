DIR2CHECK="$1"
FILTERS="-runtime/references,-build/c++11,-whitespace/comments,-whitespace/newline,-build/include_order,-readability/casting,-build/header_guard,-whitespace/indent,-runtime/arrays,-runtime/string,-build/include_subdir,-build/include"
cpplint --filter=$FILTERS --linelength 120 --recursive $DIR2CHECK

exitflag=$?
echo " "
echo " "
echo " "
echo "exitflag = $exitflag"
exit $exitflag
