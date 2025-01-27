echo " --- asm-example --- "
cd asm-example
make clean 
make sim
cd ..

echo " --- c-example --- "
cd c-example
make clean 
make sim 
cd ..

echo " --- multiplication-add --- "
cd multiplication-add
make clean 
make sim 
cd ..

echo " --- multiplication-mul --- "
cd multiplication-mul
make clean 
make sim 
cd ..

echo " --- factorize-custom --- "
cd factorize-custom
make clean 
make sim 
cd ..

echo " --- asm-print --- "
cd asm-print
make clean 
make sim
cd ..

echo " --- c-print --- "
cd c-print
make clean 
make sim
cd ..

echo " --- c-print-no-functions --- "
cd c-print-no-functions
make clean 
make sim
cd ..

echo " --- c-peripheral --- "
cd c-peripheral
make clean 
make sim 
cd ..