cd sharedObjects;

for V in $(ls -d */);
do
	cd $V
	make
	cd ../
done
