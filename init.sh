#!/bin/bash
CONFIGP=~/.config/eco #this is the config path, it case you're debugging again, whatever you do, do not put this in quotes, you're going to create a path in the working directory with the root of that path as ~, the only way to delete is using \~ please fucking notice the blackslash. 
FILEP=~/.config/eco/.profiles
if [ ! -d $CONFIGP ]; then
echo "Verified that the path indeed does not exist..."
mkdir -pv $CONFIGP
touch $FILEP
echo "Created the config..."
echo "Done."
exit 0
else
echo "wtf, this shouldn't be happening."
exit -1
fi
