
eo_dir=~/code/eodev/eodev/eo
descarwin_trunk=~/code/descarwin/trunk/

today=`date --iso-8601`
# make a directory of the current date
mkdir $today
cd $today

mkdir seq-sat-dae_yahsp
cd seq-sat-dae_yahsp 

here=`pwd`

echo "archive current version of EO"
cd $eo_dir
mkdir -p $here/eo
git archive --format zip master > $here/eo/eo_${today}.zip
cd $here/eo
unzip -qq eo_${today}.zip
cd $here

echo "archive current version of DAE/YAHSP"
svn export $descarwin_trunk $here/dae_yahsp

echo "copy the IPC build and plan file"
cp $descarwin_trunk/scripts/build $here
cp $descarwin_trunk/scripts/plan $here

cd ..

echo "duplicate seq to tempo"
cp -r seq-sat-dae_yahsp tempo-sat-dae_yahsp

echo "archive everything"
tar cjf dae_yahsp.tar.bz2 seq-sat-dae_yahsp tempo-sat-dae_yahsp

