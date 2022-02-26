# set up paths, the paths move around on repl
replrootpath=$PWD
cdate=$(date +%Y%m%dT%H%M%s)
backuptargetname=$target_file$cdate
backupsourcename=$source_file$cdate
examplebasepath=$replrootpath/freeglut-3.2.1/progs/demos/

# name your files here - this is your own thing to edit/complile in C++ 
source_file=$replrootpath/'main.cpp'
target_file=$replrootpath/'compiled'

# check if freeglut3-dev is installed on host
# install it if one of the library files isnt missing
# see output of >ldd triangle< from shell for more info
if [ ! -f ~/.apt/usr/lib/x86_64-linux-gnu/libglut.so.3 ]
then
  install-pkg freeglut3-dev
fi

# performs versioning, checks mtime on file to see
# if cpp src file is modified newer than compiled binary
#if so then move it to backup dir and remake with g++
if [ "$source_file" -nt "$target_file" ]
then
    g++ $source_file -lglut -lGL -lGLU -o $target_file
    # chmod u+x .$target_file
fi

if [ $? -eq 0 ]; then
   chmod u+x $target_file
   $target_file
else
   echo "Compile failed"
fi

# if we made it this far, start your program
# $target_file