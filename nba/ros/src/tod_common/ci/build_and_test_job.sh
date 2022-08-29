cd ../..
MODULE2BUILD="$1"
source /opt/ros/melodic/setup.bash
# build
catkin clean -y
catkin build $MODULE2BUILD -DTEST=ON
# tests
shift
TESTS="$@"
for val in $TESTS; do
    echo ""
    echo $val
    ./devel/lib/$MODULE2BUILD/$val
done
