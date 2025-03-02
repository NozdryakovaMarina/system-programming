mkdir ROOT
mkdir ROOT/a_1
mkdir ROOT/a_0
mkdir ROOT/a_1/b_1
mkdir ROOT/a_0/b_0
mkdir ROOT/a_0/b_0/c_0

echo "pig" > ROOT/a_3.txt
echo "horse" > ROOT/a_1/b_3.txt
echo "parrot" > ROOT/a_0/b_0/c_1.txt

dd if=/dev/urandom of=ROOT/a_1/b_1/c_2.bin bs=1 count=293

ln -s b_3.txt ROOT/a_2.txt

ln ROOT/a_1/b_1/c_2.bin ROOT/a_1/b_2.bin