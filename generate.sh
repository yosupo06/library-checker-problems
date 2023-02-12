
problemCate="math"
problemName="stern_brocot_tree"

python generate.py -p $problemName --dev 2>log.txt
# rm $problemCate"/"$problemName"/in" -R
# rm $problemCate"/"$problemName"/out" -R
# rm $problemCate"/"$problemName"/task.html"
# rm $problemCate"/"$problemName"/params.h"
for i in $(find ${problemCate}"/"${problemName}/* -maxdepth 1 -name "*.exe")
do
    rm $i
done
