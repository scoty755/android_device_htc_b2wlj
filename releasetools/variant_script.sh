#!/sbin/sh

set -e

# Detect variant and create symlinks to its specific-blobs
modelid=`getprop ro.boot.mid`

case $modelid in
    "0PAG20000") variant="b2ul" ;;
esac

# Skip symlink creation for Dual SIM variants because blobs are already in the proper location
if [ "$variant" == "b2ul" ]; then
  basedir="/system/blobs/$variant/"
  cd $basedir
  chmod 755 bin/*
  find . -type f | while read file; do ln -s $basedir$file /system/$file ; done
fi

exit 0
