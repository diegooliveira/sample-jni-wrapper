
set -e

export LD_LIBRARY_PATH=$(pwd)

echo -e "Compilando a lib\n---------\n\n"
g++  -shared -fpic -o libSampleLib.so -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux SampleLib.c
g++  -shared -fpic -o boa.so -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux SampleLib_Boa.c

javac Teste.java

echo -e "\nException\n---------\n"
java Teste 0

echo -e "\nSucesso\n---------\n"
java Teste 1

echo -e "\nDump\n---------\n"
java Teste 2
