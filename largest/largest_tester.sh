#sg
declare -a file_sizes=(
'500' '5000' '50000' '500000' '5000000' '50000000' 
'400' '4000' '40000' '400000' '4000000' '40000000' 
'300' '3000' '30000' '300000' '3000000' '30000000' 
'200' '2000' '20000' '200000' '2000000' '20000000' 
'100' '1000' '10000' '100000' '1000000' '10000000' 
)
i=0
for test_file in `ls|sort -rn`
do
mpiexec -f ../f ../a.out  $test_file ${file_sizes[$i]}|tee -a $1
echo " executing : mpiexec .././a.out -f ../f $test_file ${file_sizes[$i]}|tee -a $1"
i=`expr $i + 1`
done

