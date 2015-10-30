
set -e


echo -e "Compilando a lib\n---------\n\n"
mkdir -p build
cd build
g++  -shared -fpic -o libMyWrapper.so -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux ../SampleLib.c
g++  -shared -fpic -o libOriginal.so -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux ../SampleLib_Boa.c


javac ../SampleLib.java -d .
javac ../Teste.java -d .

export LD_LIBRARY_PATH=$(pwd)

echo -e "\nSucesso\n---------\n"
java Teste 1

echo -e "\nException\n---------\n"
java Teste 2
